#include "cheat/features/features.hpp"
#include "cheat/features/scripted_globals.hpp"

namespace insight {
	bool was_off_radar_on = false;
	void network::off_radar(toggle_feature* feature, bool& value) {
		if (!value) {
			if (was_off_radar_on)
			{
				scripted_globals::local_set_player_otr_flag(false);
				was_off_radar_on = false;
			}
			return;
		}
		was_off_radar_on = true;
		scripted_globals::local_set_player_otr_flag(true);
		scripted_globals::local_set_player_otr_time();
	}
}