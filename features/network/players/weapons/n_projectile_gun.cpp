

#include "cheat/features/tasks.hpp"
#include "cheat/features/globals.hpp"
#include "cheat/features/features.hpp"


#include "cheat/features/scripted_globals.hpp"
#include "util/notify/notify.hpp"
#include "util/security/xorstr.hpp"



namespace insight {
	void network::n_projectile_gun(int player, int type) {		
		if (NETWORK::NETWORK_IS_PLAYER_CONNECTED(player)) {
			Ped player_ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player);
			Vector3 cor;
			if (WEAPON::GET_PED_LAST_WEAPON_IMPACT_COORD(player_ped, &cor)) {
				Vector3 start_coords_of_projectile = tasks::get()->get_weapon_bone_coords(xorstr_("gun_muzzle"), player_ped);
				Hash weapon_hash = rage::joaat(eVehicleWeapons[type].first);
				WEAPON::REQUEST_WEAPON_ASSET(weapon_hash, 31, 0);
				while (!WEAPON::HAS_WEAPON_ASSET_LOADED(weapon_hash)) {
					WEAPON::REQUEST_WEAPON_ASSET(weapon_hash, 31, 0);
					script::get_current()->yield();
				}
				MISC::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(start_coords_of_projectile, cor, 250, 1, weapon_hash, NULL, 1, 0, 12500);

			}
		}
		else
		{
			player_options::get()->n_projectile_gun_value[player] = false;
		}
	}
	bool was_n_projectile_gun_all_on = false;
	void network::n_projectile_gun_all(toggle_int_feature* feature, bool& value, int& value2)
	{
		if (!value) {
			if (was_n_projectile_gun_all_on) {
				for (int i = 0; i < 32; i++) {
					player_options::get()->n_projectile_gun_value[i] = false;
				}
				was_n_projectile_gun_all_on = false;
			}
			return;
		}
		was_n_projectile_gun_all_on = true;
		for (int i = 0; i < 32; i++) {
			if (tasks::get_all_players_w_include_ex(i)) {
				player_options::get()->n_projectile_gun_type_value[i] = value2;
				player_options::get()->n_projectile_gun_value[i] = true;
			}
			else
				player_options::get()->n_projectile_gun_value[i] = false;
		}
	}

}