


#include "cheat/features/tasks.hpp"
#include "cheat/features/globals.hpp"
#include "cheat/features/features.hpp"
#include "cheat/features/scripted_globals.hpp"
#include "util/notify/notify.hpp"
#include "util/security/xorstr.hpp"
#include "cheat/features/scripted_globals/scr_globals.hpp"
#include "script/globals/GPBD_FM_3.hpp"
#include "util/gta_util.hpp"
namespace insight {
	void network::n_remote_wanted(int target)
	{
		constexpr size_t arg_count = 3;
		int64_t args[arg_count] = { static_cast<int64_t>(eRemoteEvent::ClearWantedLevel),
		   globals::player_id,
		   (int64_t)scr_globals::gpbd_fm_3.as<GPBD_FM_3*>()->Entries[target].ScriptEventReplayProtectionCounter };
	    	pointers::get()->g_trigger_script_event(1, args, arg_count, 1 << target);
	}
	void network::n_remote_wanted_loop(int target)
	{
		if (NETWORK::NETWORK_IS_PLAYER_CONNECTED(target)) {
			if (PLAYER::GET_PLAYER_WANTED_LEVEL(target) > 0) {
				n_remote_wanted(target);
			}
		}
		else {
			player_options::get()->n_remote_wanted_loop_value[target] = false;
		}
	}
	void network::n_remote_wanted_loop_all(toggle_feature* feature, bool& value)
	{
		if (!value) {			
			return;
		}
		for (int i = 0; i < 32; i++) {
			if (tasks::get_all_players_w_include_ex(i))
				if (PLAYER::GET_PLAYER_WANTED_LEVEL(i) > 0) {
					n_remote_wanted(i);
				}
		}
	}

}