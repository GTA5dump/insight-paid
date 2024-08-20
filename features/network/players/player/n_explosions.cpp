#include "cheat/features/tasks.hpp"
#include "cheat/features/globals.hpp"
#include "cheat/features/features.hpp"
#include "cheat/features/scripted_globals.hpp"
#include "util/notify/notify.hpp"
#include "util/security/xorstr.hpp"







namespace insight {

	void network::n_create_explosion(int target, int blamer,int explosion, bool visible, bool audio,bool damage, float cam_shake,float scale) {
		if (NETWORK::NETWORK_IS_PLAYER_CONNECTED(target))
		{
				Vector3 coords = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(target),0);
				bool damagee = !damage;
				if (blamer == -1)
				{
					FIRE::ADD_EXPLOSION(coords,
						explosion, damagee ? scale : 0, audio, !visible, cam_shake, !damage);
				}
				else
				{
					FIRE::ADD_OWNED_EXPLOSION(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(blamer),
						coords
						, explosion, damagee ? scale : 0, audio, !visible, cam_shake);
				}
		}
	}
	void network::n_create_explosion_tick(int target) {
		if (NETWORK::NETWORK_IS_PLAYER_CONNECTED(target))
		{
			if (player_options::get()->n_explosion_blamer[target] == -1)
			{
				network::n_create_explosion(target, player_options::get()->n_explosion_blamer[target],
					player_options::get()->n_explosion[target], player_options::get()->n_explosionvisible[target],
					player_options::get()->n_explosionaudio[target], player_options::get()->n_explosiondamage[target],
					player_options::get()->n_explosion_shakeness[target]);
			}
			else if (player_options::get()->n_explosion_blamer[target] == -2)
			{
				network::n_create_explosion(player_options::get()->n_explosion_blam[target], target,
					player_options::get()->n_explosion[target], player_options::get()->n_explosionvisible[target],
					player_options::get()->n_explosionaudio[target], player_options::get()->n_explosiondamage[target],
					player_options::get()->n_explosion_shakeness[target]);
			}
			else if (player_options::get()->n_explosion_blam[target] == -2)
			{
				network::n_create_explosion(target, player_options::get()->n_explosion_blamer[target],
					player_options::get()->n_explosion[target], player_options::get()->n_explosionvisible[target],
					player_options::get()->n_explosionaudio[target], player_options::get()->n_explosiondamage[target],
					player_options::get()->n_explosion_shakeness[target]);
			}
			else
			{
				player_options::get()->n_explosion_blamer[target] = -1;
			}		
		}
		else
		{
			player_options::get()->n_explosion_value[target] = false;
		}
	}
}
