#pragma once
#include <functional>
#include <vector>
#include "pattern.hpp"

namespace memory
{
    class pattern_batch
    {
    public:
        explicit pattern_batch() = default;
        ~pattern_batch() noexcept = default;

        void add(std::string name, pattern pattern, std::function<void(memory::handle)> callback);
        bool run(range region);

        struct entry
        {
            std::string m_name;
            pattern m_pattern;
            std::vector<std::function<void(memory::handle)>> m_callbacks;

            explicit entry(std::string name, pattern pattern, std::function<void(memory::handle)> callback) :
                m_name(std::move(name)),
                m_pattern(std::move(pattern))
            {
                m_callbacks.push_back(std::move(callback));
            }
        };

    private:
        std::vector<entry> m_entries;
    };
}