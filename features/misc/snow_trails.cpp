#include "cheat/features/features.hpp"

namespace insight {
	bool was_enabled;
	void miscellaneous::snow_trails(toggle_feature* feature, bool& value) {
		if (!value) {
			if (was_enabled) {
				GRAPHICS::USE_SNOW_FOOT_VFX_WHEN_UNSHELTERED(false);
				GRAPHICS::USE_SNOW_WHEEL_VFX_WHEN_UNSHELTERED(false);
				was_enabled = false;
			}
			return;
		}
		if (STREAMING::IS_PLAYER_SWITCH_IN_PROGRESS()) {
			if (STREAMING::GET_PLAYER_SWITCH_STATE() == 8) {
				was_enabled = false;
			}
		}

		if (!was_enabled) {
			GRAPHICS::USE_SNOW_FOOT_VFX_WHEN_UNSHELTERED(true);
			GRAPHICS::USE_SNOW_WHEEL_VFX_WHEN_UNSHELTERED(true);
		}

		was_enabled = true;
	}
}