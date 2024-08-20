

#include "cheat/features/tasks.hpp"
#include "cheat/features/globals.hpp"
#include "cheat/features/features.hpp"


#include "cheat/features/scripted_globals.hpp"
#include "util/notify/notify.hpp"
#include "util/security/xorstr.hpp"



namespace insight {
	void network::n_flamming_ammo_gun(int player) {
		if (NETWORK::NETWORK_IS_PLAYER_CONNECTED(player)) {
			Ped player_ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player);
			Vector3 cor;
			if (WEAPON::GET_PED_LAST_WEAPON_IMPACT_COORD(player_ped, &cor)) {
				std::vector<Entity> nearbyEntities = tasks::get_world_entities(true, true, true);
				for (const auto& entity : nearbyEntities) {
					if (ENTITY::HAS_ENTITY_BEEN_DAMAGED_BY_ENTITY(entity, player_ped, 0)) {
						if (tasks::get_control_of_entity_tick(entity)) {
							FIRE::START_ENTITY_FIRE(entity);
							ENTITY::CLEAR_ENTITY_LAST_DAMAGE_ENTITY(entity);
						}
					}
				}
			}
		}
		else
		{
			player_options::get()->n_flammingammo_gun_value[player] = false;
		}
	}
	bool was_n_flamming_ammo_gun_all_on = false;
	void network::n_flamming_ammo_gun_all(toggle_feature* feature, bool& value)
	{
		if (!value) {
			if (was_n_flamming_ammo_gun_all_on) {
				for (int i = 0; i < 32; i++) {
					player_options::get()->n_flammingammo_gun_value[i] = false;
				}
				was_n_flamming_ammo_gun_all_on = false;
			}
			return;
		}
		was_n_flamming_ammo_gun_all_on = true;
		for (int i = 0; i < 32; i++) {
			if (tasks::get_all_players_w_include_ex(i))
				player_options::get()->n_flammingammo_gun_value[i] = true;
			else
				player_options::get()->n_flammingammo_gun_value[i] = false;
		}
	}

}