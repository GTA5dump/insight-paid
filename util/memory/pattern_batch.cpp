#include "common.hpp"
#include "util/logger.hpp"
#include "pattern_batch.hpp"
#include "range.hpp"

namespace memory
{

    void pattern_batch::add(std::string name, pattern pattern, std::function<void(handle)> callback)
    {
        auto it = std::find_if(m_entries.begin(), m_entries.end(), [&name, &pattern](const entry& e) {
            return e.m_name == name && e.m_pattern == pattern;
            });

        if (it != m_entries.end()) {
            it->m_callbacks.push_back(std::move(callback));
        }
        else {
            m_entries.emplace_back(std::move(name), std::move(pattern), std::move(callback));
        }
    }
    bool pattern_batch::run(range region)
    {
        bool all_found = true;
        std::vector<std::thread> threads;
        std::mutex completion_mutex;
        std::condition_variable completion_cv;
        int num_completed = 0;

        for (auto& entry : m_entries)
        {
            if (auto result = region.scan(entry.m_pattern))
            {
                for (const auto& callback : entry.m_callbacks) {
                    threads.emplace_back(std::thread([this, &callback, result, &completion_mutex, &completion_cv, &num_completed]() {
                        std::invoke(callback, result);

                        {
                            std::unique_lock<std::mutex> lock(completion_mutex);
                            num_completed++;
                        }
                        completion_cv.notify_one();
                        }));
                }
            }
            else
            {
                all_found = false;
                LOG(WARNING) << "Failed :" << entry.m_name;
            }
        }

        // Main thread sleeps until all threads complete
        {
            std::unique_lock<std::mutex> lock(completion_mutex);
            completion_cv.wait(lock, [&]() {
                return num_completed == threads.size();
                });
        }

        for (auto& thread : threads)
        {
            thread.detach();
        }

        if (m_entries.size() > 2) {
            LOG(INFO) << "Found " << m_entries.size() << " Memory Addresses";
        }
        m_entries.clear();

        if (!all_found) {
            throw std::runtime_error(xorstr_("Failed to find some patterns."));
            insight::g_running = false;
            return false;
        }

        return true;
    }
}