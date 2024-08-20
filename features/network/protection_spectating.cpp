#include "cheat/features/features/features_utility.hpp"
#include "cheat/features/globals.hpp"
#include "cheat/features/features.hpp"
#include "cheat/features/tasks.hpp"
#include "util/notify/notify.hpp"

namespace insight {
	void network::protection_spectating(toggle_int_feature* feature, bool& value, int& value2) {
		detour::protections::g_spectating_toggle = value;
		detour::protections::g_spectating_integer = value2;
		if (!value)
			return;
		if (value) {
			float detect_at = 7.4f;
			for (int i = 0; i < 32; ++i) {
				if (NETWORK::NETWORK_IS_PLAYER_CONNECTED(i))
					if (features_utility::get()->players_cam_data[i] != (Vector3(0, 0, 0)))
					{
						Ped player_ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i);
						float distance_between_self_n_player = tasks::get_distance_between(globals::h_local_ped(), player_ped) * 2;
						float distance = SYSTEM::VDIST(globals::h_local_ped_pos(),features_utility::get()->players_cam_data[i]);
						bool is_distance_less_than = distance_between_self_n_player > 20.f;
						bool detected = distance < detect_at && !is_distance_less_than;
						std::string player_name = std::string(PLAYER::GET_PLAYER_NAME(i));
						if (detected) {
							if (value2 == 0 || value2 == 2) {
								notify::send_anti_spam(xorstr_("Protection"), player_name + xorstr_(" is spectating you."));
							}
							features_utility::get()->is_player_spectating[i] = true;
						}
						else {
							features_utility::get()->is_player_spectating[i] = false;
						}
					}
					else {
						features_utility::get()->is_player_spectating[i] = false;
				}
			}
		}
	}
}
