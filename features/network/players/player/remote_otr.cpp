

#include "cheat/features/tasks.hpp"
#include "cheat/features/globals.hpp"
#include "cheat/features/features.hpp"
#include "cheat/features/scripted_globals.hpp"
#include "util/notify/notify.hpp"
#include "util/security/xorstr.hpp"
#include "cheat/features/scripted_globals/scr_globals.hpp"
#include "script/globals/GPBD_FM_3.hpp"

namespace insight {


	void network::n_remote_otr(int target)
	{
			constexpr size_t arg_count = 7;
			int64_t args[arg_count] = { static_cast<int64_t>(eRemoteEvent::RemoteOffradar),
			   (int64_t)globals::player_id,
			   (int64_t)(NETWORK::GET_NETWORK_TIME() + 1),
			   0,
			   true,
			   false,
			   (int64_t)scr_globals::gpbd_fm_3.as<GPBD_FM_3*>()->Entries[target].ScriptEventReplayProtectionCounter };
			  pointers::get()->g_trigger_script_event(1, args, arg_count, 1 << target);
	}

	void network::n_remote_otr_loop(int target)
	{
		if (NETWORK::NETWORK_IS_PLAYER_CONNECTED(target)) {
			n_remote_otr(target);
		}
		else {
			player_options::get()->n_remote_otr_value[target] = false;
		}
	}
	void network::n_remote_otr_loop_all(toggle_feature* feature, bool& value)
	{
		if (!value) {
			return;
		}
		for (int i = 0; i < 32; i++) {
			if (tasks::get_all_players_w_include_ex(i))
				n_remote_otr(i);
			
		}
	}
}