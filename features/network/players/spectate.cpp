

#include "cheat/features/tasks.hpp"
#include "cheat/features/globals.hpp"
#include "cheat/features/features.hpp"


#include "cheat/features/scripted_globals.hpp"
#include "util/notify/notify.hpp"
#include "util/security/xorstr.hpp"

namespace insight {
	bool was_spectate_on = false;
	timer focus(std::chrono::seconds(5));
	void reset_spectate(Ped target)
	{
		NETWORK::NETWORK_SET_IN_SPECTATOR_MODE(false, target);
		HUD::SET_MINIMAP_IN_SPECTATOR_MODE(false, -1);
		ENTITY::FREEZE_ENTITY_POSITION(globals::h_local_ped(), false);
		ENTITY::FREEZE_ENTITY_POSITION(globals::h_local_vehicle(), false);
		STREAMING::SET_FOCUS_ENTITY(globals::h_local_ped());
		scripted_globals::get()->func_7329(false);
	}
	u8 spectate_player;
	void network::spectate(toggle_feature* feature, bool& value) {
		if (!value) {
			if (was_spectate_on)
			{
				reset_spectate(globals::get_selected_ped());
				was_spectate_on = false;
			}
			spectate_player = -1;
			return;
		}
		if (NETWORK::NETWORK_IS_PLAYER_CONNECTED(globals::get_selected_id()))
		{
			if (!was_spectate_on)
			{

				spectate_player = globals::get_selected_id();
				was_spectate_on = true;
			}
			if (spectate_player == globals::player_id)
			{
				notify::send(xorstr_("Spectate"), xorstr_("Turning OFF Spectating"));
				const auto target = globals::get_selected_ped();
				reset_spectate(target);
				feature->m_value.toggle = false;
			}
			if (spectate_player != globals::get_selected_id())
			{
				notify::send(xorstr_("Spectate"), xorstr_("Switching To ") + (std::string)PLAYER::GET_PLAYER_NAME(globals::get_selected_id()));
				spectate_player = globals::get_selected_id();
			}
			const auto target = globals::get_selected_ped();
			NETWORK::NETWORK_SET_IN_SPECTATOR_MODE(true, target);
			HUD::SET_MINIMAP_IN_SPECTATOR_MODE(true, target);
			ENTITY::FREEZE_ENTITY_POSITION(globals::h_local_ped(), true);
			ENTITY::FREEZE_ENTITY_POSITION(globals::h_local_vehicle(), true);
			scripted_globals::get()->func_7329(true);
			//if (focus.update())
			//{
			//	STREAMING::SET_FOCUS_ENTITY(globals::h_local_ped());
			//}
			//else { STREAMING::SET_FOCUS_ENTITY(target); }
			STREAMING::SET_FOCUS_ENTITY(target);
			if (ENTITY::IS_ENTITY_DEAD(globals::h_local_ped(), 0))
			{
				reset_spectate(target);
				feature->m_value.toggle = false;
			}
		}
	}
}