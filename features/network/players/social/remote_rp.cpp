#include "cheat/features/tasks.hpp"
#include "cheat/features/globals.hpp"
#include "cheat/features/features.hpp"
#include "cheat/features/scripted_globals.hpp"
#include "util/notify/notify.hpp"
#include "util/security/xorstr.hpp"


namespace insight {
	std::vector<bool> remote_rp_auto_boolems(32, false);
	void network::remote_rp(int player) {
		if (NETWORK::NETWORK_IS_PLAYER_CONNECTED(player))
		{
			remote_rp_auto_boolems[player] = !remote_rp_auto_boolems[player];
			const size_t arg_count = 7;
			int64_t args[arg_count] = {
				(int64_t)eRemoteEvent::GiveCollectible,
				(int64_t)player,
				(int64_t)eCollectibleType(MISC::GET_RANDOM_INT_IN_RANGE(0, 10)),
				(int64_t)0,
				remote_rp_auto_boolems[player],
				true,
				0 };
			insight::pointers::get()->g_trigger_script_event(1, args, arg_count, 1 << player);
		}
		else
		{
			player_options::get()->remote_rp_value[player] = false;
		}
	}
	void network::remote_rp_all(toggle_feature* feature, bool& value)
	{
		if (!value) {
			return;
		}
		for (int i = 0; i < 32; i++) {
			if (tasks::get_all_players_w_include_ex(i)) {
				remote_rp(i);
			}
		}

	}
}