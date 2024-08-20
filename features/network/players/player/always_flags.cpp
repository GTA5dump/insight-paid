

#include "cheat/features/tasks.hpp"
#include "cheat/features/globals.hpp"
#include "cheat/features/features.hpp"


#include "cheat/features/scripted_globals.hpp"
#include "util/notify/notify.hpp"
#include "util/security/xorstr.hpp"

namespace insight {
	std::vector<timer> n_always_on_fire_timer(32, timer(std::chrono::seconds(1s)));
	void network::n_always_on_fire(int target) {
		if (NETWORK::NETWORK_IS_PLAYER_CONNECTED(target))
		{
			if (n_always_on_fire_timer[target].update())
			{
				Vector3 pos = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(target), 0);
				pos.z = pos.z - 2;
				FIRE::ADD_EXPLOSION(pos, 12,
					1.0f, false, true, 0, true);
			}

		}
		else
		{
			player_options::get()->n_always_on_fire_value[target] = false;
		}
	}	
	std::vector<timer> n_always_ragdoll_timer(32, timer(std::chrono::seconds(1s)));
	void network::n_always_ragdoll(int target) {
		if (NETWORK::NETWORK_IS_PLAYER_CONNECTED(target))
		{
			if (n_always_ragdoll_timer[target].update())
			{
				Vector3 pos = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(target), 0);
				pos.z = pos.z - 2;
				FIRE::ADD_EXPLOSION(pos, 11,
					1.0f, false, true, 0, true);
			}

		}
		else
		{
			player_options::get()->n_always_ragdoll_value[target] = false;
		}
	}
	bool was_n_always_ragdoll_all_on = false;
	void network::n_always_ragdoll_all(toggle_feature* feature, bool& value)
	{
		if (!value) {
			if (was_n_always_ragdoll_all_on) {
				for (int i = 0; i < 32; i++) {
					player_options::get()->n_always_ragdoll_value[i] = false;
				}
				was_n_always_ragdoll_all_on = false;
			}
			return;
		}
		was_n_always_ragdoll_all_on = true;
		for (int i = 0; i < 32; i++) {
			if (tasks::get_all_players_w_include_ex(i))
				player_options::get()->n_always_ragdoll_value[i] = true;
			else
				player_options::get()->n_always_ragdoll_value[i] = false;
		}
	}
	bool was_n_always_on_fire_all_on = false;
	void network::n_always_on_fire_all(toggle_feature* feature, bool& value)
	{
		if (!value) {
			if (was_n_always_on_fire_all_on) {
				for (int i = 0; i < 32; i++) {
					player_options::get()->n_always_on_fire_value[i] = false;
				}
				was_n_always_on_fire_all_on = false;
			}
			return;
		}
		was_n_always_on_fire_all_on = true;
		for (int i = 0; i < 32; i++) {
			if (tasks::get_all_players_w_include_ex(i))
				player_options::get()->n_always_on_fire_value[i] = true;
			else
				player_options::get()->n_always_on_fire_value[i] = false;
		}
	}


}
