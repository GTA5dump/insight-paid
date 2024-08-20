
#include "cheat/features/tasks.hpp"
#include "cheat/features/globals.hpp"
#include "cheat/features/features.hpp"
#include "cheat/features/scripted_globals.hpp"
#include "util/notify/notify.hpp"
#include "util/security/xorstr.hpp"
#include "game/gta/net_object_mgr.hpp"
namespace insight {

	void network::n_action_deny_bicycle(int target) {
		if (NETWORK::NETWORK_IS_PLAYER_CONNECTED(target)) {
			Ped player_ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(target);
			Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(player_ped, false);
			Hash model = ENTITY::GET_ENTITY_MODEL(veh);
			if (VEHICLE::IS_THIS_MODEL_A_BICYCLE(model) && veh) {
				if (auto vehicle = insight::pointers::get()->g_handle_to_pointer(PED::GET_VEHICLE_PED_IS_USING(player_ped)))
				(*insight::pointers::get()->g_network_object_mgr)->ChangeOwner(vehicle->m_net_object, insight::pointers::get()->g_netplayer(globals::player_id), 0);
			}
		}
		else {
			player_options::get()->n_action_denying_bicycle_value[target] = false;
		}
	}
	void network::n_action_deny_bike(int target) {
		if (NETWORK::NETWORK_IS_PLAYER_CONNECTED(target)) {
			Ped player_ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(target);
			Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(player_ped, false);
			Hash model = ENTITY::GET_ENTITY_MODEL(veh);
			if (VEHICLE::IS_THIS_MODEL_A_BIKE(model) && veh) {
				if (auto vehicle = insight::pointers::get()->g_handle_to_pointer(PED::GET_VEHICLE_PED_IS_USING(player_ped)))
				(*insight::pointers::get()->g_network_object_mgr)->ChangeOwner(vehicle->m_net_object, insight::pointers::get()->g_netplayer(globals::player_id), 0);
			}
		}
		else {
			player_options::get()->n_action_denying_bike_value[target] = false;

		}
	}
	void network::n_action_deny_boat(int target) {
		if (NETWORK::NETWORK_IS_PLAYER_CONNECTED(target)) {
			Ped player_ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(target);
			Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(player_ped, false);
			Hash model = ENTITY::GET_ENTITY_MODEL(veh);
			if (VEHICLE::IS_THIS_MODEL_A_BOAT(model) && veh) {
				if (auto vehicle = insight::pointers::get()->g_handle_to_pointer(PED::GET_VEHICLE_PED_IS_USING(player_ped)))
				(*insight::pointers::get()->g_network_object_mgr)->ChangeOwner(vehicle->m_net_object, insight::pointers::get()->g_netplayer(globals::player_id), 0);

			}
		}
		else {
			player_options::get()->n_action_denying_boat_value[target] = false;
		}
	}
	void network::n_action_deny_car(int target) {
		if (NETWORK::NETWORK_IS_PLAYER_CONNECTED(target)) {
			Ped player_ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(target);
			Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(player_ped, false);
			Hash model = ENTITY::GET_ENTITY_MODEL(veh);
			if (VEHICLE::IS_THIS_MODEL_A_CAR(model) && veh) {
				if (auto vehicle = insight::pointers::get()->g_handle_to_pointer(PED::GET_VEHICLE_PED_IS_USING(player_ped)))
				(*insight::pointers::get()->g_network_object_mgr)->ChangeOwner(vehicle->m_net_object, insight::pointers::get()->g_netplayer(globals::player_id), 0);
			}
		}
		else {
			player_options::get()->n_action_denying_car_value[target] = false;

		}
	}
	void network::n_action_deny_heli(int target) {
		if (NETWORK::NETWORK_IS_PLAYER_CONNECTED(target)) {
			Ped player_ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(target);
			Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(player_ped, false);
			Hash model = ENTITY::GET_ENTITY_MODEL(veh);
			if (VEHICLE::IS_THIS_MODEL_A_HELI(model) && veh) {
				if (auto vehicle = insight::pointers::get()->g_handle_to_pointer(PED::GET_VEHICLE_PED_IS_USING(player_ped)))
				(*insight::pointers::get()->g_network_object_mgr)->ChangeOwner(vehicle->m_net_object, insight::pointers::get()->g_netplayer(globals::player_id), 0);
			}
		}
		else {
			player_options::get()->n_action_denying_heli_value[target] = false;
		}
	}
	void network::n_action_deny_jetski(int target) {
		if (NETWORK::NETWORK_IS_PLAYER_CONNECTED(target)) {
			Ped player_ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(target);
			Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(player_ped, false);
			Hash model = ENTITY::GET_ENTITY_MODEL(veh);
			if (VEHICLE::IS_THIS_MODEL_A_JETSKI(model) && veh) {
				if (auto vehicle = insight::pointers::get()->g_handle_to_pointer(PED::GET_VEHICLE_PED_IS_USING(player_ped)))
				(*insight::pointers::get()->g_network_object_mgr)->ChangeOwner(vehicle->m_net_object, insight::pointers::get()->g_netplayer(globals::player_id), 0);
			}
		}
		else {
			player_options::get()->n_action_denying_jetski_value[target] = false;
		}
	}
	void network::n_action_deny_plane(int target) {
		if (NETWORK::NETWORK_IS_PLAYER_CONNECTED(target)) {
			Ped player_ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(target);
			Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(player_ped, false);
			Hash model = ENTITY::GET_ENTITY_MODEL(veh);
			if (VEHICLE::IS_THIS_MODEL_A_PLANE(model) && veh) {
				if (auto vehicle = insight::pointers::get()->g_handle_to_pointer(PED::GET_VEHICLE_PED_IS_USING(player_ped)))
				(*insight::pointers::get()->g_network_object_mgr)->ChangeOwner(vehicle->m_net_object, insight::pointers::get()->g_netplayer(globals::player_id), 0);
			}
		}
		else {
			player_options::get()->n_action_denying_plane_value[target] = false;
		}
	}
	void network::n_action_deny_quadbike(int target) {
		if (NETWORK::NETWORK_IS_PLAYER_CONNECTED(target)) {
			Ped player_ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(target);
			Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(player_ped, false);
			Hash model = ENTITY::GET_ENTITY_MODEL(veh);
			if (VEHICLE::IS_THIS_MODEL_A_QUADBIKE(model) && veh) {
				if (auto vehicle = insight::pointers::get()->g_handle_to_pointer(PED::GET_VEHICLE_PED_IS_USING(player_ped)))
				(*insight::pointers::get()->g_network_object_mgr)->ChangeOwner(vehicle->m_net_object, insight::pointers::get()->g_netplayer(globals::player_id), 0);
			}
		}
		else {
			player_options::get()->n_action_denying_quadbike_value[target] = false;
		}
	}
	void network::n_action_deny_jumping(int target) {
		if (NETWORK::NETWORK_IS_PLAYER_CONNECTED(target)) {
			Ped player_ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(target);
			if (PED::IS_PED_JUMPING(player_ped)) {
				if (auto pedo = (CPed*)insight::pointers::get()->g_handle_to_pointer(player_ped))
			 insight::pointers::get()->g_clear_ped_tasks_network(pedo, true);	
			}
		}
		else {
			player_options::get()->n_action_denying_jumping_value[target] = false;
		}
	}
	void network::n_action_deny_aiming(int target) {
		if (NETWORK::NETWORK_IS_PLAYER_CONNECTED(target)) {
			Ped player_ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(target);
			if (PED::GET_PED_CONFIG_FLAG(player_ped,CPED_CONFIG_FLAG_IsAimingGun,0)) {
				if (auto pedo = (CPed*)insight::pointers::get()->g_handle_to_pointer(player_ped))
					insight::pointers::get()->g_clear_ped_tasks_network(pedo, true);	
			}
		}
		else {
			player_options::get()->n_action_denying_aiming_value[target] = false;
		}
	}
	void network::n_action_deny_holding_gun(int target) {
		if (NETWORK::NETWORK_IS_PLAYER_CONNECTED(target)) {
			Ped player_ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(target);
			Hash wephash;
			WEAPON::GET_CURRENT_PED_WEAPON(player_ped, &wephash, 0);
			if (wephash != "weapon_unarmed"_joaat) {
				if (auto pedo = (CPed*)insight::pointers::get()->g_handle_to_pointer(player_ped))
					insight::pointers::get()->g_clear_ped_tasks_network(pedo, true);		
			}
		}
		else {
			player_options::get()->n_action_denying_holding_gun_value[target] = false;
		}
	}
	void network::n_action_deny_running(int target) {
		if (NETWORK::NETWORK_IS_PLAYER_CONNECTED(target)) {
			Ped player_ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(target);
			if (TASK::IS_PED_RUNNING(player_ped)) {
				if (auto pedo = (CPed*)insight::pointers::get()->g_handle_to_pointer(player_ped))
				insight::pointers::get()->g_clear_ped_tasks_network(pedo, true);		
			}
		}
		else {
			player_options::get()->n_action_denying_running_value[target] = false;
		}
	}
	void network::n_action_deny_sprinting(int target) {
		if (NETWORK::NETWORK_IS_PLAYER_CONNECTED(target)) {
			Ped player_ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(target);
			if (TASK::IS_PED_SPRINTING(player_ped)) {
				if (auto pedo = (CPed*)insight::pointers::get()->g_handle_to_pointer(player_ped))
				insight::pointers::get()->g_clear_ped_tasks_network((CPed*)insight::pointers::get()->g_handle_to_pointer(player_ped), true);			
			}
		}
		else {
			player_options::get()->n_action_denying_sprinting_value[target] = false;
		}
	}
	void network::n_action_deny_walking(int target) {
		if (NETWORK::NETWORK_IS_PLAYER_CONNECTED(target)) {
			Ped player_ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(target);
			if (TASK::IS_PED_WALKING(player_ped)) {
				if (auto pedo = (CPed*)insight::pointers::get()->g_handle_to_pointer(player_ped))
				insight::pointers::get()->g_clear_ped_tasks_network(pedo, true);
				
			}
		}
		else {
			player_options::get()->n_action_denying_walking_value[target] = false;
		}
	}
	bool was_lobby_deny_bicycle_on = false;
	void network::lobby_deny_bicycle(toggle_feature* feature, bool& value) {
		if (!value) {
			if (was_lobby_deny_bicycle_on) {
				for (int i = 0; i < 32; i++)
				player_options::get()->n_action_denying_bicycle_value[i] = false;
				was_lobby_deny_bicycle_on = false;
			}
			return;
		}
		was_lobby_deny_bicycle_on = true;
		for (int i = 0; i < 32; i++) {
			if (tasks::get_all_players_w_include_ex(i)) {
				player_options::get()->n_action_denying_bicycle_value[i] = true;
			}
		}
	}
	bool was_lobby_deny_bike_on = false;

	void network::lobby_deny_bike(toggle_feature* feature, bool& value) {
		if (!value) {
			if (was_lobby_deny_bike_on) {
				for (int i = 0; i < 32; i++) {
					player_options::get()->n_action_denying_bike_value[i] = false;
				}
				was_lobby_deny_bike_on = false;
			}
			return;
		}
		was_lobby_deny_bike_on = true;
		for (int i = 0; i < 32; i++) {
			if (tasks::get_all_players_w_include_ex(i)) {
				player_options::get()->n_action_denying_bike_value[i] = true;
			}
		}
	}
	bool was_lobby_deny_boat_on = false;

	void network::lobby_deny_boat(toggle_feature* feature, bool& value) {
		if (!value) {
			if (was_lobby_deny_boat_on) {
				for (int i = 0; i < 32; i++) {
					player_options::get()->n_action_denying_boat_value[i] = false;
				}
				was_lobby_deny_boat_on = false;
			}
			return;
		}
		was_lobby_deny_boat_on = true;
		for (int i = 0; i < 32; i++) {
			if (tasks::get_all_players_w_include_ex(i)) {
				player_options::get()->n_action_denying_boat_value[i] = true;
			}
		}
	}
	bool was_lobby_deny_car_on = false;

	void network::lobby_deny_car(toggle_feature* feature, bool& value) {
		if (!value) {
			if (was_lobby_deny_car_on) {
				for (int i = 0; i < 32; i++) {
					player_options::get()->n_action_denying_car_value[i] = false;
				}
				was_lobby_deny_car_on = false;
			}
			return;
		}
		was_lobby_deny_car_on = true;
		for (int i = 0; i < 32; i++) {
			if (tasks::get_all_players_w_include_ex(i)) {
				player_options::get()->n_action_denying_car_value[i] = true;
			}
		}
	}
	bool was_lobby_deny_heli_on = false;

	void network::lobby_deny_heli(toggle_feature* feature, bool& value) {
		if (!value) {
			if (was_lobby_deny_heli_on) {
				for (int i = 0; i < 32; i++) {
					player_options::get()->n_action_denying_heli_value[i] = false;
				}
				was_lobby_deny_heli_on = false;
			}
			return;
		}
		was_lobby_deny_heli_on = true;
		for (int i = 0; i < 32; i++) {
			if (tasks::get_all_players_w_include_ex(i)) {
				player_options::get()->n_action_denying_heli_value[i] = true;
			}
		}
	}
	bool was_lobby_deny_jetski_on = false;

	void network::lobby_deny_jetski(toggle_feature* feature, bool& value) {
		if (!value) {
			if (was_lobby_deny_jetski_on) {
				for (int i = 0; i < 32; i++) {
					player_options::get()->n_action_denying_jetski_value[i] = false;
				}
				was_lobby_deny_jetski_on = false;
			}
			return;
		}
		was_lobby_deny_jetski_on = true;
		for (int i = 0; i < 32; i++) {
			if (tasks::get_all_players_w_include_ex(i)) {
				player_options::get()->n_action_denying_jetski_value[i] = true;
			}
		}
	}
	bool was_lobby_deny_plane_on = false;

	void network::lobby_deny_plane(toggle_feature* feature, bool& value) {
		if (!value) {
			if (was_lobby_deny_plane_on) {
				for (int i = 0; i < 32; i++) {
					player_options::get()->n_action_denying_plane_value[i] = false;
				}
				was_lobby_deny_plane_on = false;
			}
			return;
		}
		was_lobby_deny_plane_on = true;
		for (int i = 0; i < 32; i++) {
			if (tasks::get_all_players_w_include_ex(i)) {
				player_options::get()->n_action_denying_plane_value[i] = true;
			}
		}
	}
	bool was_lobby_deny_quadbike_on = false;

	void network::lobby_deny_quadbike(toggle_feature* feature, bool& value) {
		if (!value) {
			if (was_lobby_deny_quadbike_on) {
				for (int i = 0; i < 32; i++) {
					player_options::get()->n_action_denying_quadbike_value[i] = false;
				}
				was_lobby_deny_quadbike_on = false;
			}
			return;
		}
		was_lobby_deny_quadbike_on = true;
		for (int i = 0; i < 32; i++) {
			if (tasks::get_all_players_w_include_ex(i)) {
				player_options::get()->n_action_denying_quadbike_value[i] = true;
			}
		}
	}

	bool was_lobby_deny_jumping_on = false;

	void network::lobby_deny_jumping(toggle_feature* feature, bool& value) {
		if (!value) {
			if (was_lobby_deny_jumping_on) {
				for (int i = 0; i < 32; i++) {
					player_options::get()->n_action_denying_jumping_value[i] = false;
				}
				was_lobby_deny_jumping_on = false;
			}
			return;
		}
		was_lobby_deny_jumping_on = true;
		for (int i = 0; i < 32; i++) {
			if (tasks::get_all_players_w_include_ex(i)) {
				player_options::get()->n_action_denying_jumping_value[i] = true;
			}
		}
	}
	bool was_lobby_deny_aiming_on = false;

	void network::lobby_deny_aiming(toggle_feature* feature, bool& value) {
		if (!value) {
			if (was_lobby_deny_aiming_on) {
				for (int i = 0; i < 32; i++) {
					player_options::get()->n_action_denying_aiming_value[i] = false;
				}
				was_lobby_deny_aiming_on = false;
			}
			return;
		}
		was_lobby_deny_aiming_on = true;
		for (int i = 0; i < 32; i++) {
			if (tasks::get_all_players_w_include_ex(i)) {
				player_options::get()->n_action_denying_aiming_value[i] = true;
			}
		}
	}

	bool was_lobby_deny_holding_gun_on = false;

	void network::lobby_deny_holding_gun(toggle_feature* feature, bool& value) {
		if (!value) {
			if (was_lobby_deny_holding_gun_on) {
				for (int i = 0; i < 32; i++) {
					player_options::get()->n_action_denying_holding_gun_value[i] = false;
				}
				was_lobby_deny_holding_gun_on = false;
			}
			return;
		}
		was_lobby_deny_holding_gun_on = true;
		for (int i = 0; i < 32; i++) {
			if (tasks::get_all_players_w_include_ex(i)) {
				player_options::get()->n_action_denying_holding_gun_value[i] = true;
			}
		}
	}
	bool was_lobby_deny_running_on = false;

	void network::lobby_deny_running(toggle_feature* feature, bool& value) {
		if (!value) {
			if (was_lobby_deny_running_on) {
				for (int i = 0; i < 32; i++) {
					player_options::get()->n_action_denying_running_value[i] = false;
				}
				was_lobby_deny_running_on = false;
			}
			return;
		}
		was_lobby_deny_running_on = true;
		for (int i = 0; i < 32; i++) {
			if (tasks::get_all_players_w_include_ex(i)) {
				player_options::get()->n_action_denying_running_value[i] = true;
			}
		}
	}

	bool was_lobby_deny_sprinting_on = false;

	void network::lobby_deny_sprinting(toggle_feature* feature, bool& value) {
		if (!value) {
			if (was_lobby_deny_sprinting_on) {
				for (int i = 0; i < 32; i++) {
					player_options::get()->n_action_denying_sprinting_value[i] = false;
				}
				was_lobby_deny_sprinting_on = false;
			}
			return;
		}
		was_lobby_deny_sprinting_on = true;
		for (int i = 0; i < 32; i++) {
			if (tasks::get_all_players_w_include_ex(i)) {
				player_options::get()->n_action_denying_sprinting_value[i] = true;
			}
		}
	}

	bool was_lobby_deny_walking_on = false;

	void network::lobby_deny_walking(toggle_feature* feature, bool& value) {
		if (!value) {
			if (was_lobby_deny_walking_on) {
				for (int i = 0; i < 32; i++) {
					player_options::get()->n_action_denying_walking_value[i] = false;
				}
				was_lobby_deny_walking_on = false;
			}
			return;
		}
		was_lobby_deny_walking_on = true;
		for (int i = 0; i < 32; i++) {
			if (tasks::get_all_players_w_include_ex(i)) {
				player_options::get()->n_action_denying_walking_value[i] = true;
			}
		}
	}
	bool was_lobby_command_ped_spawning_on = false;

	void network::network_command_ped_spawning(toggle_feature* feature, bool& value) {
		if (!value) {
			if (was_lobby_command_ped_spawning_on) {
				for (int i = 0; i < 32; i++) {
					player_options::get()->ped_spawning_chat_command[i] = false;
				}
				was_lobby_command_ped_spawning_on = false;
			}
			return;
		}
		was_lobby_command_ped_spawning_on = true;
		for (int i = 0; i < 32; i++) {
			if (tasks::get_all_players_w_include_ex(i)) {
				player_options::get()->ped_spawning_chat_command[i] = true;
			}
		}
	}
	bool was_lobby_command_vehicle_spawning_on = false;

	void network::network_command_vehicle_spawning(toggle_feature* feature, bool& value) {
		if (!value) {
			if (was_lobby_command_vehicle_spawning_on) {
				for (int i = 0; i < 32; i++) {
					player_options::get()->vehicle_spawning_chat_command[i] = false;
				}
				was_lobby_command_vehicle_spawning_on = false;
			}
			return;
		}
		was_lobby_command_vehicle_spawning_on = true;
		for (int i = 0; i < 32; i++) {
			if (tasks::get_all_players_w_include_ex(i)) {
				player_options::get()->vehicle_spawning_chat_command[i] = true;
			}
		}
	}

	bool was_lobby_command_object_spawning_on = false;

	void network::network_command_object_spawning(toggle_feature* feature, bool& value) {
		if (!value) {
			if (was_lobby_command_object_spawning_on) {
				for (int i = 0; i < 32; i++) {
					player_options::get()->object_spawning_chat_command[i] = false;
				}
				was_lobby_command_object_spawning_on = false;
			}
			return;
		}
		was_lobby_command_object_spawning_on = true;
		for (int i = 0; i < 32; i++) {
			if (tasks::get_all_players_w_include_ex(i)) {
				player_options::get()->object_spawning_chat_command[i] = true;
			}
		}
	}

	bool was_lobby_command_kill_player_on = false;

	void network::network_command_kill_player(toggle_feature* feature, bool& value) {
		if (!value) {
			if (was_lobby_command_kill_player_on) {
				for (int i = 0; i < 32; i++) {
					player_options::get()->kill_player_chat_command[i] = false;
				}
				was_lobby_command_kill_player_on = false;
			}
			return;
		}
		was_lobby_command_kill_player_on = true;
		for (int i = 0; i < 32; i++) {
			if (tasks::get_all_players_w_include_ex(i)) {
				player_options::get()->kill_player_chat_command[i] = true;
			}
		}
	}
	bool was_lobby_command_explode_player_on = false;

	void network::network_command_explode_player(toggle_feature* feature, bool& value) {
		if (!value) {
			if (was_lobby_command_explode_player_on) {
				for (int i = 0; i < 32; i++) {
					player_options::get()->explode_player_chat_command[i] = false;
				}
				was_lobby_command_explode_player_on = false;
			}
			return;
		}
		was_lobby_command_explode_player_on = true;
		for (int i = 0; i < 32; i++) {
			if (tasks::get_all_players_w_include_ex(i)) {
				player_options::get()->explode_player_chat_command[i] = true;
			}
		}
	}

	bool was_lobby_command_kill_my_self_on = false;

	void network::network_command_kill_my_self(toggle_feature* feature, bool& value) {
		if (!value) {
			if (was_lobby_command_kill_my_self_on) {
				for (int i = 0; i < 32; i++) {
					player_options::get()->kill_my_self_command[i] = false;
				}
				was_lobby_command_kill_my_self_on = false;
			}
			return;
		}
		was_lobby_command_kill_my_self_on = true;
		for (int i = 0; i < 32; i++) {
			if (tasks::get_all_players_w_include_ex(i)) {
				player_options::get()->kill_my_self_command[i] = true;
			}
		}
	}

	bool was_lobby_command_money_rp_on = false;

	void network::network_command_money_rp(toggle_feature* feature, bool& value) {
		if (!value) {
			if (was_lobby_command_money_rp_on) {
				for (int i = 0; i < 32; i++) {
					player_options::get()->money_n_rp_command[i] = false;
				}
				was_lobby_command_money_rp_on = false;
			}
			return;
		}
		was_lobby_command_money_rp_on = true;
		for (int i = 0; i < 32; i++) {
			if (tasks::get_all_players_w_include_ex(i)) {
				player_options::get()->money_n_rp_command[i] = true;
			}
		}
	}

	bool was_lobby_command_fix_on = false;

	void network::network_command_fix(toggle_feature* feature, bool& value) {
		if (!value) {
			if (was_lobby_command_fix_on) {
				for (int i = 0; i < 32; i++) {
					player_options::get()->fix_command[i] = false;
				}
				was_lobby_command_fix_on = false;
			}
			return;
		}
		was_lobby_command_fix_on = true;
		for (int i = 0; i < 32; i++) {
			if (tasks::get_all_players_w_include_ex(i)) {
				player_options::get()->fix_command[i] = true;
			}
		}
	}
	bool was_lobby_command_upgrade_on = false;

	void network::network_command_upgrade(toggle_feature* feature, bool& value) {
		if (!value) {
			if (was_lobby_command_upgrade_on) {
				for (int i = 0; i < 32; i++) {
					player_options::get()->fix_command[i] = false;
				}
				was_lobby_command_upgrade_on = false;
			}
			return;
		}
		was_lobby_command_upgrade_on = true;
		for (int i = 0; i < 32; i++) {
			if (tasks::get_all_players_w_include_ex(i)) {
				player_options::get()->fix_command[i] = true;
			}
		}
	}
}
