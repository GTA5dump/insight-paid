

#include "cheat/features/tasks.hpp"
#include "cheat/features/globals.hpp"
#include "cheat/features/features.hpp"
#include "util/math/math.hpp"

#include "cheat/features/scripted_globals.hpp"
#include "util/notify/notify.hpp"
#include "util/security/xorstr.hpp"



namespace insight {
	void network::n_magnet_gun(int player) {
		if (NETWORK::NETWORK_IS_PLAYER_CONNECTED(player)) {
			Ped player_ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player);
			if (PED::GET_PED_CONFIG_FLAG(player_ped, CPED_CONFIG_FLAG_IsAimingGun, 0)) {
				Vector3 worldcor = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(player_ped, Vector3(0.f, tasks::is_player_shooting(player) ? 200.f : 15.f, 0.f));
				std::vector<Entity> nearbyEntities = tasks::get_world_entities(true, true, false);
				for (const auto& entity : nearbyEntities) {
					if (tasks::get_control_of_entity_tick(entity)) {
						Vector3 ent_cor = ENTITY::GET_ENTITY_COORDS(entity, 0);
						if (SYSTEM::VDIST(ent_cor,worldcor) < 50.f)
							if (!ENTITY::IS_ENTITY_STATIC(entity))
							tasks::apply_force_to_position(entity, worldcor - ent_cor, ENTITY::GET_ENTITY_VELOCITY(entity), 0.8f, 0.3f);

					}
				}
			}
		}
		else
		{
			player_options::get()->n_magnet_gun_value[player] = false;
		}
	}
	bool was_n_magnet_gun_all_on = false;
	void network::n_magnet_gun_all(toggle_feature* feature, bool& value)
	{
		if (!value) {
			if (was_n_magnet_gun_all_on) {
				for (int i = 0; i < 32; i++) {
					player_options::get()->n_magnet_gun_value[i] = false;
				}
				was_n_magnet_gun_all_on = false;
			}
			return;
		}
		was_n_magnet_gun_all_on = true;
		for (int i = 0; i < 32; i++) {
			if (tasks::get_all_players_w_include_ex(i))
				player_options::get()->n_magnet_gun_value[i] = true;
			else
				player_options::get()->n_magnet_gun_value[i] = false;
		}
	}

}