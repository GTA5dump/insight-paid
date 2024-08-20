

#include "cheat/features/tasks.hpp"
#include "cheat/features/globals.hpp"
#include "cheat/features/features.hpp"


#include "cheat/features/scripted_globals.hpp"
#include "util/notify/notify.hpp"
#include "util/security/xorstr.hpp"



namespace insight {
	timer n_auto_fix_timer(std::chrono::milliseconds(100ms));
	void network::n_auto_fix(int player) {
		if (NETWORK::NETWORK_IS_PLAYER_CONNECTED(player))
		{
			Ped PLAYER_PED = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player);
			Vehicle Veh = PED::GET_VEHICLE_PED_IS_USING(PLAYER_PED);
			if (n_auto_fix_timer.update())
			{
				if (ENTITY::DOES_ENTITY_EXIST(Veh))
				{
					if ((VEHICLE::GET_VEHICLE_BODY_HEALTH(Veh) < 1000) || VEHICLE::GET_DOES_VEHICLE_HAVE_DAMAGE_DECALS(Veh))
					{
						if (tasks::request_control(Veh))
						{
							tasks::fix_vehicle(Veh);
						}
					}
				}
			}
		}
		else
		{
			player_options::get()->hold_horn_boost_value[player] = false;
		}
	}
	bool was_n_auto_fix_all_on = false;
	void network::n_auto_fix_all(toggle_feature* feature, bool& value)
	{
		if (!value) {
			if (was_n_auto_fix_all_on) {
				for (int i = 0; i < 32; i++) {
					player_options::get()->n_auto_fix_value[i] = false;
				}
				was_n_auto_fix_all_on = false;
			}
			return;
		}
		was_n_auto_fix_all_on = true;
		for (int i = 0; i < 32; i++) {
			if (tasks::get_all_players_w_include_ex(i))
				player_options::get()->n_auto_fix_value[i] = true;
			else
				player_options::get()->n_auto_fix_value[i] = false;
		}
	}

}