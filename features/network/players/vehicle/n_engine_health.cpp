

#include "cheat/features/tasks.hpp"
#include "cheat/features/globals.hpp"
#include "cheat/features/features.hpp"


#include "cheat/features/scripted_globals.hpp"
#include "util/notify/notify.hpp"
#include "util/security/xorstr.hpp"



namespace insight {
	std::vector<Entity> n_engine_health_last(32, 0);
	std::vector<int> n_engine_health_last_selection(32, 0);
	std::vector<timer> n_engine_health_last_timer(32, timer(std::chrono::seconds(30s)));
	void network::n_engine_health(int player) {
		if (NETWORK::NETWORK_IS_PLAYER_CONNECTED(player))
		{
			Ped PLAYER_PED = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player);
			Vehicle Veh = PED::GET_VEHICLE_PED_IS_USING(PLAYER_PED);
			if (ENTITY::DOES_ENTITY_EXIST(Veh))
			{
				if (n_engine_health_last_selection[player] != player_options::get()->n_engine_health_selection[player])
				{
					n_engine_health_last_timer[player].restart();
					n_engine_health_last[player] = 0;
					n_engine_health_last_selection[player] = player_options::get()->n_engine_health_selection[player];
				}
				if (n_engine_health_last_timer[player].update())
				{
					n_engine_health_last[player] = 0;
				}
				if (n_engine_health_last[player] != Veh)
				{
					if (tasks::request_control(Veh))
					tasks::set_vehicle_engine_health(Veh, player_options::get()->n_engine_health_selection[player]);
					n_engine_health_last[player] = Veh;
				}

			}
		}
		else
		{
			player_options::get()->n_engine_health_value[player] = false;
		}
	}
}