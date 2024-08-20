#include "cheat/features/globals.hpp"
#include "cheat/pointers/pointers.hpp"
#include "util/gta_util.hpp"
#include "natives.hpp"
#include <player/CPlayerAngles.hpp>
namespace insight {
	CPed* globals::c_local_ped() {		
		return insight::gta_util::get_local_ped();
	}
	Ped globals::h_local_ped() {
		if (auto ped = c_local_ped()) {
			return insight::pointers::get()->g_pointer_to_handle(ped);
		}
		return 0;
	}

	bool globals::is_player_loaded_in = false;

	Vector3 globals::h_local_ped_pos() {
		if (globals::h_local_ped()) {
			return ENTITY::GET_ENTITY_COORDS(globals::h_local_ped(),0);
		}
		return Vector3(0.f, 0.f, 0.f);
	}

	Player globals::player_id;

	bool globals::in_multiplayer() {
		return NETWORK::NETWORK_IS_SESSION_ACTIVE();
	}

	CVehicle* globals::c_local_vehicle() {
		return insight::gta_util::get_local_vehicle();
	}
	
	Vehicle globals::h_local_vehicle(bool last_vehicle) {
		if (last_vehicle)
		{
			if (!PED::IS_PED_IN_ANY_VEHICLE(globals::h_local_ped(), true))
			{
				return 0;
			}
		}
		if (auto vehicle = c_local_vehicle()) {
			return insight::pointers::get()->g_pointer_to_handle(vehicle);
		}
		return 0;
	}

	CPedWeaponManager* globals::c_local_weapon() {
		CPed* local_ped = insight::gta_util::get_local_ped();

		if (local_ped && local_ped->m_weapon_manager) {
			return local_ped->m_weapon_manager;
		}

		return nullptr;
	}
	CPlayerAngles* globals::c_local_cam() {
		uintptr_t camAddress = insight::pointers::get()->g_player_angles;
		if (camAddress)
			return *(CPlayerAngles**)(camAddress + 0x0);
		return 0;
	}

	bool globals::is_using_controller() {
		return !PAD::IS_USING_KEYBOARD_AND_MOUSE(2);
	}

	bool globals::is_game_paused() {
		return HUD::IS_PAUSE_MENU_ACTIVE();
	}

	Cam globals::m_freecam_handle = 0;

	Network* globals::get_network() {
		return insight::gta_util::get_network();
	}

	CNetworkPlayerMgr* globals::get_player_mgr() {
		return insight::gta_util::get_network_player_mgr();
	}

	CCommunications* globals::get_communications() {
		return *insight::pointers::get()->g_communications;
	}

	CFriendRegistry* globals::get_friend_registry() {
		return insight::pointers::get()->g_friend_registry;
	}

	CNetGamePlayer* selected_player;

	void globals::set_selected_player(CNetGamePlayer* i) {
		selected_player = i;
	}

	CNetGamePlayer* globals::get_selected_player() {
		return selected_player;
	}

	int globals::get_selected_id() {
		if (selected_player) {
			return selected_player->m_player_id;
		}
		return 0;
	}

	Ped  globals::get_selected_ped() {
		return PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(globals::get_selected_id());
	}

	Vehicle  globals::get_selected_vehicle() {
		return PED::GET_VEHICLE_PED_IS_USING(globals::get_selected_ped());
	}
}