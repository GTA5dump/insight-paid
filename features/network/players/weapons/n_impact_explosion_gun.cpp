

#include "cheat/features/tasks.hpp"
#include "cheat/features/globals.hpp"
#include "cheat/features/features.hpp"


#include "cheat/features/scripted_globals.hpp"
#include "util/notify/notify.hpp"
#include "util/security/xorstr.hpp"



namespace insight {
	void network::n_impactexp_gun(int player, int type) {
		if (NETWORK::NETWORK_IS_PLAYER_CONNECTED(player)) {
			Ped player_ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player);
			Vector3 cor;
			if (WEAPON::GET_PED_LAST_WEAPON_IMPACT_COORD(player_ped, &cor)) {
				FIRE::ADD_EXPLOSION(cor, type, 1000.f, true, false, 0.f, false);
			}
		}
		else
		{
			player_options::get()->n_exp_gun_value[player] = false;
		}
	}
	bool was_n_impactexp_gun_all_on = false;
	void network::n_impactexp_gun_all(toggle_int_feature* feature, bool& value, int& value2)
	{
		if (!value) {
			if (was_n_impactexp_gun_all_on) {
				for (int i = 0; i < 32; i++) {
					player_options::get()->n_exp_gun_value[i] = false;
				}		
				was_n_impactexp_gun_all_on = false;
			}
			return;
		}
		was_n_impactexp_gun_all_on = true;
		for (int i = 0; i < 32; i++) {
			if (tasks::get_all_players_w_include_ex(i)) {
				player_options::get()->n_exp_gun_type_value[i] = value2;
				player_options::get()->n_exp_gun_value[i] = true;
			}
			else
				player_options::get()->n_exp_gun_value[i] = false;
		}
	}

}