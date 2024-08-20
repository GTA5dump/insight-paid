#include "cheat/features/features.hpp"
const char* restricted_area_scripts[] = {
	"am_armybase",
	"restrictedareas",
	"re_armybase",
	"re_lossantosintl",
	"re_prison",
	"re_prisonvanbreak"
};

namespace insight {
	bool was_restriced;

	void miscellaneous::bypass_restricted_areas(toggle_feature* feature, bool& value) {
		if (!value) {
			if (was_restriced) {
				was_restriced = false;
			}
			return;
		}
		if (STREAMING::IS_PLAYER_SWITCH_IN_PROGRESS()) {
			if (STREAMING::GET_PLAYER_SWITCH_STATE() == 8) {
				was_restriced = false;
			}
		}

		if (!was_restriced) {
			for (auto& str : restricted_area_scripts) {
				if (SCRIPT::DOES_SCRIPT_EXIST(str))
					MISC::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME(str);
			}
		}

		was_restriced = true;
	}
}