

#include "cheat/features/tasks.hpp"
#include "cheat/features/globals.hpp"
#include "cheat/features/features.hpp"


#include "cheat/features/scripted_globals.hpp"
#include "util/notify/notify.hpp"
#include "util/security/xorstr.hpp"



namespace insight {
	std::vector<int> delay_hold_horn_boost(32, 0);

	void network::hold_horn_boost(int player) {
		if (NETWORK::NETWORK_IS_PLAYER_CONNECTED(player))
		{
			Ped PLAYER_PED = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player);
			Vehicle Veh = PED::GET_VEHICLE_PED_IS_USING(PLAYER_PED);
			if (ENTITY::DOES_ENTITY_EXIST(Veh))
			{
				if (AUDIO::IS_HORN_ACTIVE(Veh))
				{
					if (delay_hold_horn_boost[player] > 100) {
						float speed = ENTITY::GET_ENTITY_SPEED(Veh);
						if (player_options::get()->hold_horn_boost_value_Selection[player] == 0 || player_options::get()->hold_horn_boost_value_Selection[player] == 1) {
							if (tasks::request_control(Veh)) {
								VEHICLE::SET_VEHICLE_FORWARD_SPEED(Veh, player_options::get()->hold_horn_boost_value_Selection[player] == 1 ?
									-speed + -player_options::get()->hold_horn_boost_value_Speed[player] :
									speed + player_options::get()->hold_horn_boost_value_Speed[player]);
								delay_hold_horn_boost[player] = 0;
							}
						}
						else if (player_options::get()->hold_horn_boost_value_Selection[player] == 2 || player_options::get()->hold_horn_boost_value_Selection[player] == 3) {
							ENTITY::APPLY_FORCE_TO_ENTITY(Veh, 1, Vector3(0.0f, player_options::get()->hold_horn_boost_value_Selection[player] == 2 ? 0.6f * speed : -0.6f * speed, 0.f), Vector3(0.0f, 0.0f, 0.0f), 0, 1, 1, 1, 0, 1);
						}
					}
					else { delay_hold_horn_boost[player]++; }
				}

			}
		}
		else
		{
			player_options::get()->hold_horn_boost_value[player] = false;
		}
	}
	bool was_hold_horn_boost_all_on = false;
	void network::hold_horn_boost_all(toggle_int_feature* feature, bool& value, int& value2)
	{
		if (!value) {
			if (was_hold_horn_boost_all_on) {
				for (int i = 0; i < 32; i++) {
					player_options::get()->hold_horn_boost_value[i] = false;
				}
				was_hold_horn_boost_all_on = false;
			}
			return;
		}
		was_hold_horn_boost_all_on = true;
		for (int i = 0; i < 32; i++) {
			if (tasks::get_all_players_w_include_ex(i)) {
				player_options::get()->hold_horn_boost_value[i] = true;
				player_options::get()->hold_horn_boost_value_Selection[i] = value2;
				player_options::get()->hold_horn_boost_value_Speed[i] = 100;
			}
			else
				player_options::get()->hold_horn_boost_value[i] = false;
		}
	}

}