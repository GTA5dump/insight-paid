#include "cheat/features/tasks.hpp"
#include "cheat/features/globals.hpp"
#include "cheat/features/features.hpp"
#include "cheat/features/scripted_globals.hpp"
#include "util/notify/notify.hpp"
#include "util/security/xorstr.hpp"

namespace insight {
	std::vector<timer>n_slippery_veh_timer(32, timer(std::chrono::milliseconds(100ms)));
	void network::n_slippery_veh(int player) {
		if (NETWORK::NETWORK_IS_PLAYER_CONNECTED(player))
		{
			Vehicle Veh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player));
			if (n_slippery_veh_timer[player].update())
			{
				if (ENTITY::DOES_ENTITY_EXIST(Veh))
				{
					Hash hash = ENTITY::GET_ENTITY_MODEL(Veh);
					if (!VEHICLE::IS_THIS_MODEL_A_PLANE(hash) && !VEHICLE::IS_THIS_MODEL_A_BOAT(hash))
						tasks::slip_vehicle(Veh);
				}
			}
		}
		else
		{
			player_options::get()->hold_horn_boost_value[player] = false;
		}
	}
	bool was_n_slippery_veh_all_on = false;
	void network::n_slippery_veh_all(toggle_feature* feature, bool& value)
	{
		if (!value) {
			if (was_n_slippery_veh_all_on) {
				for (int i = 0; i < 32; i++) {
					player_options::get()->n_slippery_veh_value[i] = false;
				}
				was_n_slippery_veh_all_on = false;
			}
			return;
		}
		was_n_slippery_veh_all_on = true;
		for (int i = 0; i < 32; i++) {
			if (tasks::get_all_players_w_include_ex(i))
				player_options::get()->n_slippery_veh_value[i] = true;
			else
				player_options::get()->n_slippery_veh_value[i] = false;
		}
	}
	void network::n_slamming_veh(int player) {
		if (NETWORK::NETWORK_IS_PLAYER_CONNECTED(player)) {
			Ped player_ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player);
			std::vector<Entity> nearbyEntities = tasks::get_world_entities(false, true, false);
			for (const auto& p : nearbyEntities) {
				if (tasks::get_distance_between(ENTITY::GET_ENTITY_COORDS(p, 0), ENTITY::GET_ENTITY_COORDS(player_ped, 0)) < 140.f) {
					Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(p);
					if (veh) {
						if (tasks::get_control_of_entity_tick(veh)) {
							PED::SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(p, 1);
							ENTITY::SET_ENTITY_MAX_SPEED(veh, 9999);
							VEHICLE::SET_VEHICLE_CHEAT_POWER_INCREASE(veh, 999.f);
							PED::SET_PED_KEEP_TASK(p, true);
							TASK::TASK_VEHICLE_ESCORT(p, veh, player_ped, MISC::GET_RANDOM_INT_IN_RANGE(-1, 4), 999, 16777216, 0, 0, 0);
						}
					}

				}
			}
		}
		else
		{
			player_options::get()->n_slamming_veh_value[player] = false;
		}
	}
	void network::n_attach_veh(int player, int type) {
		Vector3 pos;
		if (NETWORK::NETWORK_IS_PLAYER_CONNECTED(player)) {
			Ped player_ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player);
			Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(player_ped);
			if (veh) {
				if (type == 0)
				pos = {0,4,0};
				if (type == 1)
				pos = {0,-4,0};
				if (type == 2)
				pos = {0,0,2};		
				if (type == 3)
				pos = {0,0,-2};
				if (type == 4)
				pos = {4,0,0};
				if (type == 5)
				pos = {-4,0,0};

				if (tasks::request_control(veh))
					ENTITY::ATTACH_ENTITY_TO_ENTITY(veh, globals::h_local_vehicle(true) ? globals::h_local_vehicle(true) : globals::h_local_ped(),
					0, pos, Vector3(0, 0, 0), 1, 1, 0, 1, 2, 1, 0);

			}
		}
	}

}