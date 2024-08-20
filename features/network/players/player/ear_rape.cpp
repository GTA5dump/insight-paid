#include "cheat/features/tasks.hpp"
#include "cheat/features/globals.hpp"
#include "cheat/features/features.hpp"
#include "cheat/features/scripted_globals.hpp"
#include "util/notify/notify.hpp"
#include "util/security/xorstr.hpp"



namespace insight {
	void network::ear_rape(int p, int type)
	{
		Vector3 plyrCoords = ENTITY::GET_ENTITY_COORDS(p, false);
		if (type == 0) // wasted earrape
		{
			AUDIO::PLAY_SOUND_FROM_COORD(1, xorstr_("BED"), plyrCoords, xorstr_("WASTEDSOUNDS"), true, 0, false);
			AUDIO::PLAY_SOUND_FROM_COORD(2, xorstr_("BED"), plyrCoords, xorstr_("WASTEDSOUNDS"), true, 0, false);
			AUDIO::PLAY_SOUND_FROM_COORD(3, xorstr_("BED"), plyrCoords, xorstr_("WASTEDSOUNDS"), true, 0, false);
			AUDIO::PLAY_SOUND_FROM_COORD(4, xorstr_("BED"), plyrCoords, xorstr_("WASTEDSOUNDS"), true, 0, false);
			AUDIO::PLAY_SOUND_FROM_COORD(5, xorstr_("BED"), plyrCoords, xorstr_("WASTEDSOUNDS"), true, 0, false);
			AUDIO::PLAY_SOUND_FROM_COORD(6, xorstr_("BED"), plyrCoords, xorstr_("WASTEDSOUNDS"), true, 0, false);
			return;

		}
		if (type == 1) // yass
		{

			AUDIO::PLAY_SOUND_FROM_COORD(std::rand() % (100 + 1 - 1) + 1, xorstr_("Air_Defences_Activated"), plyrCoords, xorstr_("DLC_sum20_Business_Battle_AC_Sounds"), true, 999999, false);
			script::get_current()->yield(2000ms);								  								  															  
			AUDIO::PLAY_SOUND_FROM_COORD(std::rand() % (100 + 1 - 1) + 1, xorstr_("Air_Defences_Activated"), plyrCoords, xorstr_("DLC_sum20_Business_Battle_AC_Sounds"), true, 999999, false);
			AUDIO::PLAY_SOUND_FROM_COORD(std::rand() % (100 + 1 - 1) + 1, xorstr_("Air_Defences_Activated"), plyrCoords, xorstr_("DLC_sum20_Business_Battle_AC_Sounds"), true, 999999, false);
			AUDIO::PLAY_SOUND_FROM_COORD(std::rand() % (100 + 1 - 1) + 1, xorstr_("Air_Defences_Activated"), plyrCoords, xorstr_("DLC_sum20_Business_Battle_AC_Sounds"), true, 999999, false);		
			script::get_current()->yield(1000ms);								  								  				 											  
			script::get_current()->yield(900ms);								  								  				 											  
			AUDIO::PLAY_SOUND_FROM_COORD(std::rand() % (100 + 1 - 1) + 1, xorstr_("Air_Defences_Activated"), plyrCoords, xorstr_("DLC_sum20_Business_Battle_AC_Sounds"), true, 999999, false);
			AUDIO::PLAY_SOUND_FROM_COORD(std::rand() % (100 + 1 - 1) + 1, xorstr_("Air_Defences_Activated"), plyrCoords, xorstr_("DLC_sum20_Business_Battle_AC_Sounds"), true, 999999, false);
			AUDIO::PLAY_SOUND_FROM_COORD(std::rand() % (100 + 1 - 1) + 1, xorstr_("Air_Defences_Activated"), plyrCoords, xorstr_("DLC_sum20_Business_Battle_AC_Sounds"), true, 999999, false);
			AUDIO::PLAY_SOUND_FROM_COORD(std::rand() % (100 + 1 - 1) + 1, xorstr_("Air_Defences_Activated"), plyrCoords, xorstr_("DLC_sum20_Business_Battle_AC_Sounds"), true, 999999, false);
			AUDIO::PLAY_SOUND_FROM_COORD(std::rand() % (100 + 1 - 1) + 1, xorstr_("Air_Defences_Activated"), plyrCoords, xorstr_("DLC_sum20_Business_Battle_AC_Sounds"), true, 999999, false);
			script::get_current()->yield(800ms);								 								  				 								  
			AUDIO::PLAY_SOUND_FROM_COORD(std::rand() % (100 + 1 - 1) + 1, xorstr_("Air_Defences_Activated"), plyrCoords, xorstr_("DLC_sum20_Business_Battle_AC_Sounds"), true, 999999, false);
			AUDIO::PLAY_SOUND_FROM_COORD(std::rand() % (100 + 1 - 1) + 1, xorstr_("Air_Defences_Activated"), plyrCoords, xorstr_("DLC_sum20_Business_Battle_AC_Sounds"), true, 999999, false);
			AUDIO::PLAY_SOUND_FROM_COORD(std::rand() % (100 + 1 - 1) + 1, xorstr_("Air_Defences_Activated"), plyrCoords, xorstr_("DLC_sum20_Business_Battle_AC_Sounds"), true, 999999, false);
			AUDIO::PLAY_SOUND_FROM_COORD(std::rand() % (100 + 1 - 1) + 1, xorstr_("Air_Defences_Activated"), plyrCoords, xorstr_("DLC_sum20_Business_Battle_AC_Sounds"), true, 999999, false);
			AUDIO::PLAY_SOUND_FROM_COORD(std::rand() % (100 + 1 - 1) + 1, xorstr_("Air_Defences_Activated"), plyrCoords, xorstr_("DLC_sum20_Business_Battle_AC_Sounds"), true, 999999, false);
			AUDIO::PLAY_SOUND_FROM_COORD(std::rand() % (100 + 1 - 1) + 1, xorstr_("Air_Defences_Activated"), plyrCoords, xorstr_("DLC_sum20_Business_Battle_AC_Sounds"), true, 999999, false);
			AUDIO::PLAY_SOUND_FROM_COORD(std::rand() % (100 + 1 - 1) + 1, xorstr_("Air_Defences_Activated"), plyrCoords, xorstr_("DLC_sum20_Business_Battle_AC_Sounds"), true, 999999, false);
			AUDIO::PLAY_SOUND_FROM_COORD(std::rand() % (100 + 1 - 1) + 1, xorstr_("Air_Defences_Activated"), plyrCoords, xorstr_("DLC_sum20_Business_Battle_AC_Sounds"), true, 999999, false);
			AUDIO::PLAY_SOUND_FROM_COORD(std::rand() % (100 + 1 - 1) + 1, xorstr_("Air_Defences_Activated"), plyrCoords, xorstr_("DLC_sum20_Business_Battle_AC_Sounds"), true, 999999, false);
			script::get_current()->yield(500ms);								  								  				 											  
			AUDIO::PLAY_SOUND_FROM_COORD(std::rand() % (100 + 1 - 1) + 1, xorstr_("Air_Defences_Activated"), plyrCoords, xorstr_("DLC_sum20_Business_Battle_AC_Sounds"), true, 999999, false);
			AUDIO::PLAY_SOUND_FROM_COORD(std::rand() % (100 + 1 - 1) + 1, xorstr_("Air_Defences_Activated"), plyrCoords, xorstr_("DLC_sum20_Business_Battle_AC_Sounds"), true, 999999, false);
			AUDIO::PLAY_SOUND_FROM_COORD(std::rand() % (100 + 1 - 1) + 1, xorstr_("Air_Defences_Activated"), plyrCoords, xorstr_("DLC_sum20_Business_Battle_AC_Sounds"), true, 999999, false);
			AUDIO::PLAY_SOUND_FROM_COORD(std::rand() % (100 + 1 - 1) + 1, xorstr_("Air_Defences_Activated"), plyrCoords, xorstr_("DLC_sum20_Business_Battle_AC_Sounds"), true, 999999, false);
			AUDIO::PLAY_SOUND_FROM_COORD(std::rand() % (100 + 1 - 1) + 1, xorstr_("Air_Defences_Activated"), plyrCoords, xorstr_("DLC_sum20_Business_Battle_AC_Sounds"), true, 999999, false);
			AUDIO::PLAY_SOUND_FROM_COORD(std::rand() % (100 + 1 - 1) + 1, xorstr_("Air_Defences_Activated"), plyrCoords, xorstr_("DLC_sum20_Business_Battle_AC_Sounds"), true, 999999, false);
			script::get_current()->yield(200ms);
			script::get_current()->yield(9000ms);
			Vector3 Coords = ENTITY::GET_ENTITY_COORDS(p, 0);
			FIRE::ADD_EXPLOSION(Coords, (int)37, 100, true, false, 0, true);
			FIRE::ADD_EXPLOSION(Coords, (int)37, 100, true, false, 0, true);
			FIRE::ADD_EXPLOSION(Coords, (int)37, 100, true, false, 0, true);
			FIRE::ADD_EXPLOSION(Coords, (int)37, 100, true, false, 0, true);
			FIRE::ADD_EXPLOSION(Coords, (int)37, 100, true, false, 0, true);
			while (!WEAPON::HAS_WEAPON_ASSET_LOADED(0x63AB0442))
			{
				WEAPON::REQUEST_WEAPON_ASSET(0x63AB0442, 32, 26);
				script::get_current()->yield();

			}

			MISC::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(Vector3(Coords.x + MISC::GET_RANDOM_INT_IN_RANGE(0, 50), Coords.y + MISC::GET_RANDOM_INT_IN_RANGE(0, 50), Coords.z + MISC::GET_RANDOM_INT_IN_RANGE(55, 65)), Coords, 50, false, 0x63AB0442, NULL, true, true, 1000);
			MISC::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(Vector3(Coords.x + MISC::GET_RANDOM_INT_IN_RANGE(0, 50), Coords.y + MISC::GET_RANDOM_INT_IN_RANGE(0, 50), Coords.z + MISC::GET_RANDOM_INT_IN_RANGE(55, 65)), Coords, 50, false, 0x63AB0442, NULL, true, true, 1000);
			MISC::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(Vector3(Coords.x + MISC::GET_RANDOM_INT_IN_RANGE(0, 50), Coords.y + MISC::GET_RANDOM_INT_IN_RANGE(0, 50), Coords.z + MISC::GET_RANDOM_INT_IN_RANGE(55, 65)), Coords, 50, false, 0x63AB0442, NULL, true, true, 1000);
			MISC::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(Vector3(Coords.x + MISC::GET_RANDOM_INT_IN_RANGE(0, 50), Coords.y + MISC::GET_RANDOM_INT_IN_RANGE(0, 50), Coords.z + MISC::GET_RANDOM_INT_IN_RANGE(55, 65)), Coords, 50, false, 0x63AB0442, NULL, true, true, 1000);

			script::get_current()->yield(100ms);

			AUDIO::PLAY_SOUND_FROM_COORD(std::rand() % (100 + 1 - 1) + 1,xorstr_("BED"), plyrCoords, xorstr_("WASTEDSOUNDS"), true, 999999, false);
			AUDIO::PLAY_SOUND_FROM_COORD(std::rand() % (100 + 1 - 1) + 1,xorstr_("BED"), plyrCoords, xorstr_("WASTEDSOUNDS"), true, 999999, false);
			AUDIO::PLAY_SOUND_FROM_COORD(std::rand() % (100 + 1 - 1) + 1,xorstr_("BED"), plyrCoords, xorstr_("WASTEDSOUNDS"), true, 999999, false);
			AUDIO::PLAY_SOUND_FROM_COORD(std::rand() % (100 + 1 - 1) + 1,xorstr_("BED"), plyrCoords, xorstr_("WASTEDSOUNDS"), true, 999999, false);
			AUDIO::PLAY_SOUND_FROM_COORD(std::rand() % (100 + 1 - 1) + 1,xorstr_("BED"), plyrCoords, xorstr_("WASTEDSOUNDS"), true, 999999, false);
			AUDIO::PLAY_SOUND_FROM_COORD(std::rand() % (100 + 1 - 1) + 1,xorstr_("BED"), plyrCoords, xorstr_("WASTEDSOUNDS"), true, 999999, false);

			return;

		}
		if (type == 2) // ok
		{
			AUDIO::PLAY_SOUND_FROM_COORD(1, xorstr_("Lester_Laugh_Phone"), plyrCoords, xorstr_("DLC_HEIST_HACKING_SNAKE_SOUNDS"), true, 0, false);
			return;

		}
		return;

	}
	bool train_momente_ = true;
	float tain_momente_last = 0.0f;
	void network::train_moment(int i) {
		if (i == -1) {
			tain_momente_last = 0.0f;
			train_momente_ = true;
			return;
		}
		Player player = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i);
		if (Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(player)) {
			if (veh) {
				if (train_momente_) {
					tain_momente_last = tain_momente_last + 3.0f;
					train_momente_ = false;
				} else if (!train_momente_) {					
					train_momente_ = true;
				}
				if (tasks::request_control(veh))
				ENTITY::ATTACH_ENTITY_TO_ENTITY(veh, globals::h_local_vehicle(), 0, Vector3(0, train_momente_ ? tain_momente_last : -tain_momente_last, 0), Vector3(0, 0, 0), 1, 1, 0, 1, 2, 1, 0);
			}
			return;
		}
	}
}