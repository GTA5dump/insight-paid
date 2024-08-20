#include "cheat/features/features.hpp"
namespace insight {
	bool was_enabledd;
	void miscellaneous::potato_pc_mode(toggle_feature* feature, bool& value) {
		if (!value) {
			if (was_enabledd) {
				STREAMING::SET_FOCUS_ENTITY(globals::h_local_ped());
				was_enabledd = false;
			}
			return;
		}
		if (STREAMING::IS_PLAYER_SWITCH_IN_PROGRESS()) {
			if (STREAMING::GET_PLAYER_SWITCH_STATE() == 8) {
				was_enabledd = false;
			}
		}

		STREAMING::SET_FOCUS_POS_AND_VEL({ 9999.0f, 9999.0f, -9999.0f }, { 0.0f, 0.0f, 0.0f });

		was_enabledd = true;
		
	}
}