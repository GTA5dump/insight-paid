

#include "cheat/features/tasks.hpp"
#include "cheat/features/globals.hpp"
#include "cheat/features/features.hpp"
#include "cheat/features/scripted_globals.hpp"
#include "util/notify/notify.hpp"
#include "util/security/xorstr.hpp"


namespace insight {
	void network::n_auto_heal(int player, int selection) {
		if (NETWORK::NETWORK_IS_PLAYER_CONNECTED(player))
		{
			Ped p = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player);
			if (!ENTITY::IS_ENTITY_DEAD(p, 0))
			{
				if (selection == 0 || selection == 2)
				{
					if (int health = ENTITY::GET_ENTITY_HEALTH(p))
					{
						if (health < ENTITY::GET_ENTITY_MAX_HEALTH(p)) {
							insight::pointers::get()->g_give_pickup_rewards(1 << player, "REWARD_HEALTH"_joaat);

						}
					}
				}
				if (selection == 1 || selection == 2)
				{
					int aromor = PED::GET_PED_ARMOUR(p);
					if (aromor < 50)
					{
						insight::pointers::get()->g_give_pickup_rewards(1 << player, "REWARD_ARMOUR"_joaat);
					}
				}

			}


		}
		else
		{
			player_options::get()->n_auto_heal_value[player] = false;
		}
	}
	bool was_n_auto_heal_all_on = false;
	void network::n_auto_heal_all(toggle_int_feature* feature, bool& value, int& value2) {
		if (!value) {
			if (was_n_auto_heal_all_on) {
				for (int i = 0; i < 32; i++) {
					player_options::get()->n_auto_heal_value[i] = false;
				}
				was_n_auto_heal_all_on = false;
			}
			return;
		}
		was_n_auto_heal_all_on = true;
		for (int i = 0; i < 32; i++)
		{
			if (tasks::get_all_players_w_include_ex(i)) {
				player_options::get()->n_auto_heal_value[i] = true;
				player_options::get()->n_auto_heal_selection[i] = value2;
			}
			else {
				player_options::get()->n_auto_heal_value[i] = false;
			}
		}
	}
	void network::n_kill_godmode(int player)
	{
		Ped ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player);
		Vector3 pos = ENTITY::GET_ENTITY_COORDS(ped, 1);
		Vehicle khanjali = "khanjali"_joaat;
		STREAMING::REQUEST_MODEL(khanjali);
		Vector3 v = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(ped, { 0.0f, 2.f, 3.8f });
		Vehicle vehicle1 = VEHICLE::CREATE_VEHICLE(khanjali, v, ENTITY::GET_ENTITY_HEADING(ped), true, 1, 0);
		Vehicle vehicle2 = VEHICLE::CREATE_VEHICLE(khanjali, pos, 0, true, 1, 0);
		Vehicle vehicle3 = VEHICLE::CREATE_VEHICLE(khanjali, pos, 0, true, 1, 0);
		Vehicle vehicle4 = VEHICLE::CREATE_VEHICLE(khanjali, pos, 0, true, 1, 0);
		Vehicle spawned_vehs[4] = { vehicle1, vehicle2, vehicle3, vehicle4 };
		ENTITY::ATTACH_ENTITY_TO_ENTITY(vehicle2, vehicle1, 0, { 0.0, 3.0, 0.0 }, { 0.0, 0.0, -180.0 }, 0, false, true, false, 0, true, 0);
		ENTITY::ATTACH_ENTITY_TO_ENTITY(vehicle3, vehicle1, 0, { 3.0, 3.0, 0.0 }, { 0.0, 0.0, -180.0 }, 0, false, true, false, 0, true, 0);
		ENTITY::ATTACH_ENTITY_TO_ENTITY(vehicle4, vehicle1, 0, { 3.0, 0.0, 0.0 }, { 0.0, 0.0, 0.0} ,0, false, true, false, 0, true, 0);
		ENTITY::SET_ENTITY_VISIBLE(vehicle1, false, 0);
		script::get_current()->yield(8000ms);
		for (std::uint32_t i = 0; i < 4; ++i)
			tasks::delete_entity(spawned_vehs[i]);
	}
}