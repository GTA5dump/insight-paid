#pragma once
#include <chrono>
namespace insight
{
    class rate_limiter
    {
        std::uint32_t m_attempts_allowed_in_time_period;
        std::chrono::milliseconds m_time_period;
        std::chrono::system_clock::time_point m_last_event_time{};
        std::uint32_t m_num_attempts_allowed = 0;

    public:
        rate_limiter() = default;
        rate_limiter(std::chrono::milliseconds time_period, std::uint32_t num_allowed_attempts) :
            m_attempts_allowed_in_time_period(num_allowed_attempts),
            m_time_period(time_period)
        {
        }
        bool process()
        {
            if (std::chrono::system_clock::now() - m_last_event_time < m_time_period)
            {
                if (++m_num_attempts_allowed > m_attempts_allowed_in_time_period)
                    return true;
            }
            else
            {
                m_last_event_time = std::chrono::system_clock::now();
                m_num_attempts_allowed = 1;
            }
            return false;
        }
        bool exceeded_last_process()
        {
            return (m_num_attempts_allowed - 1) == m_attempts_allowed_in_time_period;
        }
    };
}