#include "cheat/features/tasks.hpp"
#include "cheat/features/globals.hpp"
#include "cheat/features/features.hpp"
#include "cheat/features/scripted_globals.hpp"
#include "util/notify/notify.hpp"
#include "util/security/xorstr.hpp"
#include "util/math/math.hpp"

namespace insight {

	void network::n_create_airstrike(int target, Vector3 shootpos, uint32_t hash, bool owned, int speed) {
		if (NETWORK::NETWORK_IS_PLAYER_CONNECTED(target))
		{
			WEAPON::GIVE_WEAPON_TO_PED(globals::h_local_ped(), hash, 99, 0, 0);// avoid online buggy
			MISC::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(shootpos,
				ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(target),0), 999, true, hash, owned ? globals::h_local_ped() : NULL, true, false, (float)speed);
		}
	}
	void network::n_create_airstrike_tick(int target) {
		if (NETWORK::NETWORK_IS_PLAYER_CONNECTED(target))
		{
			Vector3 shootpos;
			int speed = 0;
			if (player_options::get()->n_create_airstrike_360[target])
			{
				shootpos = vectors::get()->get_360_vec_around_coord(ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(target), 0), 60, 60, 180);
			}
			else
			{
				shootpos = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(target), 0);
				shootpos.x = shootpos.x + MISC::GET_RANDOM_FLOAT_IN_RANGE(-5, 5);
				shootpos.y = shootpos.y + MISC::GET_RANDOM_FLOAT_IN_RANGE(-5, 5);
				shootpos.z = shootpos.z + MISC::GET_RANDOM_FLOAT_IN_RANGE(50, 60);
			}
			if (player_options::get()->n_create_airstrike_speed[target] == 0)
				speed = 100;
			else   if (player_options::get()->n_create_airstrike_speed[target] == 1)
				speed = 500;
			else   if (player_options::get()->n_create_airstrike_speed[target] == 2)
				speed = 1000;
			network::n_create_airstrike(target, shootpos,
				player_options::get()->n_create_airstrike_exp[target], player_options::get()->n_create_airstrike_owned[target],
				speed);
		}
		else
		{
			player_options::get()->n_explosion_value[target] = false;
		}
	}
}

