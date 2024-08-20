#include "cheat/features/tasks.hpp"
#include "cheat/features/globals.hpp"
#include "cheat/features/features.hpp"
#include "cheat/features/scripted_globals.hpp"
#include "util/notify/notify.hpp"
#include "util/security/xorstr.hpp"
#include "cheat/pointers/pointers.hpp"
#include "game/gta/net_object_mgr.hpp"
namespace insight {
	bool kidnap_player_wait = false;
	void  network::kidnap_player(int i, const char* carname, const char* pedname, float y, bool you) {
		if (!kidnap_player_wait) {
			kidnap_player_wait = true;
			Ped ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i);
			Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(ped);
			if (veh) {
				auto vehicle = insight::pointers::get()->g_handle_to_pointer(PED::GET_VEHICLE_PED_IS_USING(ped));
				(*insight::pointers::get()->g_network_object_mgr)->ChangeOwner(vehicle->m_net_object, insight::pointers::get()->g_netplayer(globals::player_id), 0);
			}
			script::get_current()->yield(500ms);

			Vector3 playerPos = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(ped, Vector3(0, y, 0));
			Hash stockadeHash = MISC::GET_HASH_KEY(carname);
			Hash stockadeHash_OBj = MISC::GET_HASH_KEY("lr_prop_supermod_door_01");
			while (!STREAMING::HAS_MODEL_LOADED(stockadeHash) && !STREAMING::HAS_MODEL_LOADED(stockadeHash_OBj)) {
				STREAMING::REQUEST_MODEL(stockadeHash);
				STREAMING::REQUEST_MODEL(stockadeHash_OBj);
				script::get_current()->yield();
			}
			Vehicle stockade = VEHICLE::CREATE_VEHICLE(stockadeHash, playerPos, ENTITY::GET_ENTITY_HEADING(ped), globals::in_multiplayer(), 0, 0);
			Object obj = OBJECT::CREATE_OBJECT(stockadeHash_OBj, playerPos, globals::in_multiplayer(), 0, 1);
			ENTITY::SET_ENTITY_VISIBLE(obj, 0, 1);
		    ENTITY::ATTACH_ENTITY_TO_ENTITY(obj, stockade, 0, Vector3(0.0, -3.0, 0.5), Vector3(0, 0, 0), 0, true, true, false, 1, 1, 0);
			ENTITY::SET_ENTITY_AS_MISSION_ENTITY(stockade, true, true);
			VEHICLE::SET_VEHICLE_ENGINE_ON(stockade, true, true, 0);
			if (you) {
				PED::SET_PED_INTO_VEHICLE(globals::h_local_ped(), stockade, -1);
			}
			else {
				Hash pedhash = MISC::GET_HASH_KEY(pedname);
				while (!STREAMING::HAS_MODEL_LOADED(pedhash)) {
					STREAMING::REQUEST_MODEL(pedhash);
					script::get_current()->yield();
				}
				Ped driver = PED::CREATE_PED_INSIDE_VEHICLE(stockade, 26, pedhash, -1, true, true);
				PED::SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(driver, true);

				ENTITY::SET_ENTITY_INVINCIBLE(driver, 1);
				PED::SET_PED_COMBAT_ATTRIBUTES(driver, 17, true);
				PED::SET_PED_COMBAT_ATTRIBUTES(driver, 46, true);
				TASK::TASK_VEHICLE_DRIVE_WANDER(driver, stockade, 30.0f, 262144);
				PED::SET_DRIVER_ABILITY(driver, 100.0f);
				PED::SET_DRIVER_AGGRESSIVENESS(driver, 0.0f);
			}
			ENTITY::SET_ENTITY_INVINCIBLE(stockade, 1);
		}
		kidnap_player_wait = false;
	}
	const char* fuc_strippers_moaning_peds[3] = {
	"s_f_y_hooker_01", "s_f_y_hooker_02","s_f_y_hooker_03"
	};

	static timer fuc_strippers_moaning_timer(std::chrono::milliseconds(1ms));
	void fuc_strippers_moaning(int i, Player index)
	{
		Player player = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(index);
		if (tasks::get_control_of_entity_tick(i) && !ENTITY::IS_ENTITY_STATIC(i)) {
			Hash model_i = ENTITY::GET_ENTITY_MODEL(i);
			bool is_stripper = model_i == rage::joaat(fuc_strippers_moaning_peds[0]) || model_i == rage::joaat(fuc_strippers_moaning_peds[1]) || model_i == rage::joaat(fuc_strippers_moaning_peds[2]);
			if (is_stripper) {
				//GENERIC_CURSE_HIGH_07
				//lamar_1_normal.awc n word alert
				PED::SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(i, true);
				static const char* speeches[] = { "SEX_GENERIC_FEM", "SEX_HJ", "SEX_ORAL_FEM", "SEX_CLIMAX", "SEX_GENERIC" };
				static const char* voice_name[] = { "S_F_Y_HOOKER_01_WHITE_FULL_01", "S_F_Y_HOOKER_01_WHITE_FULL_02", "S_F_Y_HOOKER_01_WHITE_FULL_03", "S_F_Y_HOOKER_02_WHITE_FULL_01", "S_F_Y_HOOKER_02_WHITE_FULL_02", "S_F_Y_HOOKER_02_WHITE_FULL_03", "S_F_Y_HOOKER_03_BLACK_FULL_01", "S_F_Y_HOOKER_03_BLACK_FULL_03" };
				int random_index = 0 + (rand() % 2);
				int random_index2 = 0 + (rand() % 7);
				AUDIO::PLAY_PED_AMBIENT_SPEECH_WITH_VOICE_NATIVE(i, speeches[random_index], voice_name[random_index2], "SPEECH_PARAMS_FORCE", true);
			if (fuc_strippers_moaning_timer.update())
				TASK::TASK_GO_TO_ENTITY(i, player, 5000, 4.0, 100, 1073741824, 1);
			}
			else {
				Hash Swap_model = rage::joaat(fuc_strippers_moaning_peds[0 + (rand() % 2)]);
				tasks::get()->swap_ped(ePedType::PED_TYPE_PROSTITUTE, i, Swap_model);
			}
		}
	}
	void network::n_strippers_moaning_tick(int target) {
		std::vector<Entity> nearbyEntities = tasks::get_world_entities(false, true, false);
		for (const auto& entity : nearbyEntities) {
			if (tasks::get_distance_between(ENTITY::GET_ENTITY_COORDS(entity, 0), ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(target), 0)) <	140.f) {
				
				fuc_strippers_moaning(entity, target);
			}
		}

	 }
} 