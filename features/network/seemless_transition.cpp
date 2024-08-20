#include "cheat/features/globals.hpp"
#include "cheat/features/features.hpp"
#include "cheat/features/tasks.hpp"
#include "util/script/fiber_pool.hpp"
#include "util/gta_util.hpp"
#include "game/gta/script_handler.hpp"

namespace insight {
	bool was_seemless_transition_off = false;
	void network::seemless_transition(toggle_feature* feature, bool& value) {
		if (!value)
			return;
		if (STREAMING::GET_PLAYER_SWITCH_STATE() == 6) {
		auto hash = SCRIPT::GET_HASH_OF_THIS_SCRIPT_NAME();
		insight::g_fiber_pool->queue_job([hash] {
				tasks::force_host_of_script(hash);
				if (auto script = insight::gta_util::find_script_thread(hash); script && script->m_net_component)
					((CGameScriptHandlerNetComponent*)script->m_net_component)->block_host_migration(true);
				});
		}
		//if (STREAMING::GET_PLAYER_SWITCH_STATE() <= (int)eTransitionState::TRANSITION_STATE_FM_FINAL_SETUP_PLAYER) {
		//	PLAYER::SET_PLAYER_CONTROL(globals::player_id, true, 0);
		//	if (STREAMING::IS_PLAYER_SWITCH_IN_PROGRESS()) {
		//	//	STREAMING::STOP_PLAYER_SWITCH();
		//		ENTITY::FREEZE_ENTITY_POSITION(globals::get_selected_ped(), 0);
		//	}
		//}
	}
}