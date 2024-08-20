

#include "cheat/features/tasks.hpp"
#include "cheat/features/globals.hpp"
#include "cheat/features/features.hpp"

#include "cheat/features/scripted_globals.hpp"
#include "util/notify/notify.hpp"
#include "util/security/xorstr.hpp"



namespace insight {
	void network::n_try_hard_gun(int player) {
		if (NETWORK::NETWORK_IS_PLAYER_CONNECTED(player)) {
			if (tasks::is_player_shooting(player)) {
				Ped player_ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player);
				Vector3 cor = ENTITY::GET_ENTITY_COORDS(player_ped,1);
				FIRE::ADD_EXPLOSION(cor, 18, 1, false, true, 0, false);
			}
		}
		else
		{
			player_options::get()->n_try_hard_gun_value[player] = false;
		}
	}
	bool was_n_try_hard_gun_all_on = false;
	void network::n_try_hard_gun_all(toggle_feature* feature, bool& value)
	{
		if (!value) {
			if (was_n_try_hard_gun_all_on) {
				for (int i = 0; i < 32; i++) {
					player_options::get()->n_try_hard_gun_value[i] = false;
				}
				was_n_try_hard_gun_all_on = false;
			}
			return;
		}
		was_n_try_hard_gun_all_on = true;
		for (int i = 0; i < 32; i++) {
			if (tasks::get_all_players_w_include_ex(i))
				player_options::get()->n_try_hard_gun_value[i] = true;
			else
				player_options::get()->n_try_hard_gun_value[i] = false;
		}
	}

}