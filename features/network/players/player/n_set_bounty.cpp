#include "cheat/features/tasks.hpp"
#include "cheat/features/globals.hpp"
#include "cheat/features/features.hpp"
#include "cheat/features/scripted_globals.hpp"
#include "util/notify/notify.hpp"
#include "util/security/xorstr.hpp"
#include "cheat/features/scripted_globals/scr_globals.hpp"
#include <script/globals/GSBD_FM.hpp>

namespace insight {

	void network::n_setbounty(int target, int bvalue, bool unknow) {
		if (NETWORK::NETWORK_IS_PLAYER_CONNECTED(target))
		{
				const size_t arg_count = 22;
				int64_t args[arg_count] = {
					(int64_t)eRemoteEvent::Bounty,
					globals::player_id,
					target,
					1,
					bvalue,
					0,
					unknow ? 1 : 0,
					0,
					0,
					0,
					0,
					0,
					0,
					0,
					0,
					0,
					0,
					0,
					0,
					0,
					*scr_globals::gsbd_fm_events.at(9).as<int*>(),
					*scr_globals::gsbd_fm_events.at(10).as<int*>()
				};
				if (pointers::get()->g_netplayer(target))
				pointers::get()->g_trigger_script_event(1, args, arg_count, -1);
			}	
	}
	void network::n_setbounty_loop(int target) {
		if (NETWORK::NETWORK_IS_PLAYER_CONNECTED(target))
		{
			bool hasBounty = scr_globals::gsbd_fm.as<GSBD_FM*>()->PlayerBounties[target].HasBounty;
			if (!hasBounty) {
				network::n_setbounty(target, player_options::get()->n_bounty_selection[target],
					player_options::get()->n_bounty_unknow[target]);
			}
		}
		else
		{
			player_options::get()->n_bounty_loop[target] = false;
		}
	}
	void network::n_setbounty_loop_all(toggle_feature* feature, bool& value) {
		if (!value) {
			return;
		}
		for (int i = 0; i < 32; i++) {
			if (tasks::get_all_players_w_include_ex(i))
			n_setbounty_loop(i);
		}
	}
}
