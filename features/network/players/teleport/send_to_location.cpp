
#include "cheat/features/tasks.hpp"
#include "cheat/features/globals.hpp"
#include "cheat/features/features.hpp"
#include "util/math/math.hpp"
#include "cheat/features/scripted_globals.hpp"
#include "util/notify/notify.hpp"
#include "util/security/xorstr.hpp"




namespace insight {

	void network::send_to_interior(int target, int location)
	{
		if (!globals::globals::is_player_loaded_in) {
			return;
		}

		if (NETWORK::NETWORK_IS_PLAYER_CONNECTED(target))		{
				float max = 1e+38f;
				auto coords = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(target), FALSE);
				const size_t arg_count = 15;
				int64_t args[arg_count] = { (int64_t)eRemoteEvent::InteriorControl,
					(int64_t)globals::player_id,
					(int64_t)(int)location,
					(int64_t)globals::player_id,
					(int64_t)false,
					(int64_t)true,
					(int64_t) * (uint32_t*)&coords.x,
					(int64_t) * (uint32_t*)&coords.y,
					(int64_t) * (uint32_t*)&coords.z,
					0,
					0,
					1,
					(int64_t) * (uint32_t*)&max,
					(int64_t)true,
					-1 };
				if (pointers::get()->g_netplayer(target))
				pointers::get()->g_trigger_script_event(1, args, arg_count, 1 << target);
		}
		return;
	}
	void network::send_to_apartments(int p, int location)
	{
		if (NETWORK::NETWORK_IS_PLAYER_CONNECTED(p))
		{
				const size_t arg_count = 9;
				int64_t args[arg_count] = { (int64_t)eRemoteEvent::Teleport, globals::player_id, (int64_t)p, (int64_t)(int)-1, 1, (int64_t)location, 1, 1, 1 };
				if (pointers::get()->g_netplayer(p))
				pointers::get()->g_trigger_script_event(1, args, arg_count, 1 << p);
		}
		return;
	}	
	void network::jump_scare_player(int p)
	{
		if (NETWORK::NETWORK_IS_PLAYER_CONNECTED(p))
		{
			Vector3 LAST_POS = globals::h_local_ped_pos();
			Ped ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(p);
		//	AUDIO::PLAY_SOUND_FROM_ENTITY(99, "SIRENS_AIRHORN", ped, "", globals::in_multiplayer(), 999.F);
			AUDIO::PLAY_SOUND_FROM_COORD(99, "SIRENS_AIRHORN", ENTITY::GET_ENTITY_COORDS(ped, 0), "", globals::in_multiplayer(), 999.F, 1);

			//AUDIO::PLAY_SOUND_FROM_COORD(99, "SIRENS_AIRHORN", ENTITY::GET_ENTITY_COORDS(ped, 0), "", globals::in_multiplayer(), 999.F, 1);
			//AUDIO::PLAY_SOUND_FROM_COORD(99, "SCREAMS", ENTITY::GET_ENTITY_COORDS(ped, 0), "NIGEL_02_SOUNDSET", globals::in_multiplayer(), 999.F, 0);
			//AUDIO::PLAY_SOUND_FROM_COORD(99, "SCREAMS", ENTITY::GET_ENTITY_COORDS(ped, 0), "NIGEL_02_SOUNDSET", globals::in_multiplayer(), 999.F, 0);
			//AUDIO::PLAY_SOUND_FROM_COORD(99, "VEHICLES_HORNS_AMBULANCE_WARNING", ENTITY::GET_ENTITY_COORDS(ped, 0), "NIGEL_02_SOUNDSET", globals::in_multiplayer(), 999.F, 0);
			for (int i = 0; i < 360; i++)
			{
				Vector3 set =vectors::get()->get_custom_angle_vec_around_coord(ENTITY::GET_ENTITY_COORDS(ped, 0), 5.f, MISC::GET_RANDOM_FLOAT_IN_RANGE(0, 2), 360, MISC::GET_RANDOM_INT_IN_RANGE(0, 360));
				FIRE::ADD_EXPLOSION(set, 3, 0, 0, 0, 1, 1);
				ENTITY::SET_ENTITY_COORDS_NO_OFFSET(globals::h_local_ped(), set, 1, 1, 0);
				script::get_current()->yield();
			}
			AUDIO::STOP_SOUND(99);
			AUDIO::PLAY_SOUND_FROM_COORD(99, "", ENTITY::GET_ENTITY_COORDS(ped, 0), "", globals::in_multiplayer(), 999.F, 1);
			ENTITY::SET_ENTITY_COORDS_NO_OFFSET(globals::h_local_ped(), LAST_POS, 1, 1, 0);

		}
		return;
	}
	void network::jump_scare_lobby()
	{
		for (int i = 0; i < 32; i++)
		{
			if (NETWORK::NETWORK_IS_PLAYER_CONNECTED(i))
			{
				if (i == globals::player_id)
					continue;
				Vector3 LAST_POS = globals::h_local_ped_pos();
				Ped ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i);
				AUDIO::PLAY_SOUND_FROM_ENTITY(99, "SIRENS_AIRHORN", ped, "", globals::in_multiplayer(), 999.F);

			}

		}
		return;
	}
}