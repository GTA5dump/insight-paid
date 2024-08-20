#include "cheat/features/tasks.hpp"
#include "cheat/features/globals.hpp"
#include "cheat/features/features.hpp"
#include "cheat/features/scripted_globals.hpp"
#include "util/notify/notify.hpp"
#include "util/security/xorstr.hpp"



namespace insight {
	void network::n_karama(int target)
	{
		if (NETWORK::NETWORK_IS_PLAYER_CONNECTED(target))
		{
				Ped ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(target);
				Entity killer = PED::GET_PED_SOURCE_OF_DEATH(ped);
				bool is_player = PED::IS_PED_A_PLAYER(killer);
				if (player_options::get()->n_karama_selection[target] == 1 ? (is_player && killer != 0) :  killer) {
					{
						if (!ENTITY::IS_ENTITY_DEAD(killer, 1) && ENTITY::IS_ENTITY_DEAD(ped, 1)) {
							Vector3 coords = ENTITY::GET_ENTITY_COORDS(killer, true);
								FIRE::ADD_EXPLOSION(coords, 1, 100.f, true, false, 0.f, false);
						}
					}
				}
		}
		else
		{
			player_options::get()->n_karama_value[target] = false;
		}
	}
	bool was_n_karama_loop_all_on = false;
	void network::n_karama_loop_all(toggle_feature* feature, bool& value)
	{
		if (!value) {
			if (was_n_karama_loop_all_on) {
				for (int i = 0; i < 32; i++) {
					player_options::get()->n_karama_value[i] = false;
				}
				was_n_karama_loop_all_on = false;
			}
			return;
		}
		was_n_karama_loop_all_on = true;
		for (int i = 0; i < 32; i++) {
			if (tasks::get_all_players_w_include_ex(i))
				player_options::get()->n_karama_value[i] = true;
			else
				player_options::get()->n_karama_value[i] = false;
		}
	}

}