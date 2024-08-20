
#include "cheat/features/features.hpp"
#include "cheat/features/globals.hpp"
#include "cheat/features/tasks.hpp"
#include "cheat/features/features/features_utility.hpp"
#include "util/input/input.hpp"
#include "util/math/math.hpp"

namespace insight {
	void world::freeze_time(toggle_feature* feature, bool& value) {
		CLOCK::PAUSE_CLOCK(value);
	}

	void world::sync_local_time(toggle_feature* feature, bool& value) {
		if (!value)
			return;
		time_t now = time(0);
		tm t;
		localtime_s(&t, &now);
		CLOCK::SET_CLOCK_TIME(t.tm_hour, t.tm_min, t.tm_sec);
	}

	void world::always_day(toggle_feature* feature, bool& value) {
		if (!value)
			return;
		"always_night"_tf->m_value.toggle = false;
		NETWORK::NETWORK_OVERRIDE_CLOCK_TIME(12, 0, 0);
	}

	void world::always_night(toggle_feature* feature, bool& value) {
		if (!value)
			return;
		"always_day"_tf->m_value.toggle = false;
		NETWORK::NETWORK_OVERRIDE_CLOCK_TIME(1, 0, 0);
	}


	void world::time_lapse(toggle_float_feature* feature, bool& value, float& value2) {
		if (!value)
			return;
		static bool timer_reset = true;
		static std::chrono::system_clock::time_point timer_Start;

		if (timer_reset) {
			timer_Start = std::chrono::system_clock::now();
			timer_reset = false;
		}

		std::chrono::duration<double> elapsed_seconds = std::chrono::system_clock::now() - timer_Start;
		if (elapsed_seconds.count() >= (float)CLOCK::GET_MILLISECONDS_PER_GAME_MINUTE() / 60.f / 1000.f) {
			if ("time_minute"_if->m_value.integer < 60) {
				"time_minute"_if->m_value.integer += value2;
			}
			if ("time_minute"_if->m_value.integer >= 60) {
				"time_minute"_if->m_value.integer = 0;
				"time_hour"_if->m_value.integer++;
			}
			if ("time_hour"_if->m_value.integer == 24) {
				"time_hour"_if->m_value.integer = 0;
			}

			NETWORK::NETWORK_OVERRIDE_CLOCK_TIME("time_hour"_if->m_value.integer, "time_minute"_if->m_value.integer, "time_second"_if->m_value.integer);
			timer_reset = true;
		}
	}
}