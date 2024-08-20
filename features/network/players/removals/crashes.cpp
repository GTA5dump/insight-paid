#include "cheat/features/tasks.hpp"
#include "cheat/features/globals.hpp"
#include "cheat/features/features.hpp"
#include "cheat/features/features/features_utility.hpp"
#include "cheat/features/scripted_globals.hpp"
#include "util/notify/notify.hpp"
#include "util/security/xorstr.hpp"
#include "rage/Joaat.hpp"
#include "util/math/math.hpp"
#include "util/script/fiber_pool.hpp"
namespace insight {
	void network::woops_crash(int i) {
		std::vector<Entity> woops_crash_entity;
	    std::string models[] = { "player_zero" ,"player_two","player_one" };
		if (NETWORK::NETWORK_IS_PLAYER_CONNECTED(i)) {
			woops_crash_entity.clear();
			Ped playerped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i);
			Vector3 cor = ENTITY::GET_ENTITY_COORDS(playerped, 0);
			for (int i = 0; i < 50; i++)
			{
				Hash model = rage::joaat(models[MISC::GET_RANDOM_INT_IN_RANGE(0, 2)]);
				tasks::request_model(model);
				Ped ped = PED::CREATE_PED(26, model, cor, 0, true, 0);
				TASK::TASK_SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(ped, true);
				woops_crash_entity.push_back(ped);
			}
			script::get_current()->yield(8000ms);
			for (int i = 0; i < woops_crash_entity.size(); i++)
			{
				tasks::delete_entity(woops_crash_entity[i]);
			}
			woops_crash_entity.clear();
		}
	}
	void network::mods_crash(int i) {
		Hash hash = 1349725314;
		Player playerPed = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i);
		Vector3 playerCoords = ENTITY::GET_ENTITY_COORDS(playerPed, false);
		while (!STREAMING::HAS_MODEL_LOADED(hash))
		{
			STREAMING::REQUEST_MODEL(hash);
			script::get_current()->yield();
		}
		Vehicle veh = VEHICLE::CREATE_VEHICLE(hash, playerCoords, ENTITY::GET_ENTITY_HEADING(playerPed), true, false, false);
		int net_id = NETWORK::VEH_TO_NET(veh);
		NETWORK::SET_NETWORK_ID_ALWAYS_EXISTS_FOR_PLAYER(net_id, i, TRUE);
		NETWORK::SET_NETWORK_ID_CAN_MIGRATE(net_id, false);
		VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
		VEHICLE::SET_VEHICLE_MOD(veh, 34, 3, false);
		VEHICLE::TOGGLE_VEHICLE_MOD(veh, 34, true);
		NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(veh);
		VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
		VEHICLE::SET_VEHICLE_MOD(veh, 0, 0, false);
		VEHICLE::TOGGLE_VEHICLE_MOD(veh, 0, true);
		script::get_current()->yield(8000ms);
		tasks::delete_entity(veh);

	}
	void network::vehicle_temp_crash(int i) {
		Player playerPed = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i);
		Vehicle vehicle = PED::GET_VEHICLE_PED_IS_IN(playerPed, FALSE);
		TASK::TASK_VEHICLE_TEMP_ACTION(playerPed, vehicle, 15, 100);
		TASK::TASK_VEHICLE_TEMP_ACTION(playerPed, vehicle, 16, 100);
		TASK::TASK_VEHICLE_TEMP_ACTION(playerPed, vehicle, 17, 100);
		TASK::TASK_VEHICLE_TEMP_ACTION(playerPed, vehicle, 18, 100);

	}
	void network::fragment_crash(int i) {
		Player playerPed = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i);
		Hash obj_hash = rage::joaat("prop_fragtest_cnst_04");
		Vector3 playerCoords = ENTITY::GET_ENTITY_COORDS(playerPed, false);
		while (!STREAMING::HAS_MODEL_LOADED(obj_hash))
		{
			STREAMING::REQUEST_MODEL(obj_hash);
			script::get_current()->yield();
		}
		Object ob = OBJECT::CREATE_OBJECT(obj_hash, playerCoords, true, 0, 0);
		NETWORK::SET_ENTITY_LOCALLY_INVISIBLE(ob);
		OBJECT::BREAK_OBJECT_FRAGMENT_CHILD(ob, 1, false);
		script::get_current()->yield(1000ms);
		tasks::delete_entity(ob);

	}
	void network::object_crash(int i) {
		Player playerPed = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i);
		Hash obj_hash = -930879665;
		Hash obj_hash1 = 3613262246;
		Hash obj_hash2 = 452618762;
		Hash obj_hash3 = 3613262246;
		Vector3 playerCoords = ENTITY::GET_ENTITY_COORDS(playerPed, 1);
		if (tasks::get()->get_distance_between(playerCoords, globals::h_local_ped() < 10)) {
		}
		while (!STREAMING::HAS_MODEL_LOADED(obj_hash) && !STREAMING::HAS_MODEL_LOADED(obj_hash1) && !STREAMING::HAS_MODEL_LOADED(obj_hash2) && !STREAMING::HAS_MODEL_LOADED(obj_hash3))
		{
			STREAMING::REQUEST_MODEL(obj_hash);
			STREAMING::REQUEST_MODEL(obj_hash1);
			STREAMING::REQUEST_MODEL(obj_hash2);
			STREAMING::REQUEST_MODEL(obj_hash3);
			script::get_current()->yield();
		}
		Object o1 = OBJECT::CREATE_OBJECT(obj_hash, playerCoords, true, 0, 0);
		NETWORK::SET_ENTITY_LOCALLY_INVISIBLE(o1);

		Object o2 = OBJECT::CREATE_OBJECT(obj_hash1, playerCoords, true, 0, 0);
		NETWORK::SET_ENTITY_LOCALLY_INVISIBLE(o2);

		Object o3 = OBJECT::CREATE_OBJECT(obj_hash2, playerCoords, true, 0, 0);
		NETWORK::SET_ENTITY_LOCALLY_INVISIBLE(o3);

		Object o4 = OBJECT::CREATE_OBJECT(obj_hash3, playerCoords, true, 0, 0);
		NETWORK::SET_ENTITY_LOCALLY_INVISIBLE(o4);
		tasks::delete_entity(o1);
		tasks::delete_entity(o2);
		tasks::delete_entity(o3);
		tasks::delete_entity(o4);

	}

	std::int32_t spawn_vehicle(std::uint32_t hash, std::int32_t on_entity) {
		if (STREAMING::IS_MODEL_VALID(hash)) {
			std::float_t speed = 0.0f;

			STREAMING::REQUEST_MODEL(hash);
			while (!STREAMING::HAS_MODEL_LOADED(hash))
				script::get_current()->yield();

			if (on_entity == PLAYER::PLAYER_PED_ID()) {
				if (PED::IS_PED_IN_ANY_VEHICLE(on_entity, FALSE)) {
					std::int32_t current_vehicle = PED::GET_VEHICLE_PED_IS_IN(on_entity, FALSE);
					speed = ENTITY::GET_ENTITY_SPEED(current_vehicle);
					ENTITY::SET_ENTITY_AS_MISSION_ENTITY(current_vehicle, TRUE, TRUE);
					VEHICLE::DELETE_VEHICLE(&current_vehicle);
				}
			}

			Vector3 l_coords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(on_entity, { 0.0f, 0.0f, 0.0f });
			std::int32_t net_id = NETWORK::VEH_TO_NET(VEHICLE::CREATE_VEHICLE(hash, { l_coords.x, l_coords.y, l_coords.z }, ENTITY::GET_ENTITY_HEADING(on_entity), TRUE, FALSE, 0));
		
			NETWORK::NETWORK_FADE_IN_ENTITY(NETWORK::NET_TO_VEH(net_id), 0, 0);
			NETWORK::SET_NETWORK_ID_EXISTS_ON_ALL_MACHINES(net_id, TRUE);
			if (ENTITY::IS_ENTITY_VISIBLE_TO_SCRIPT(NETWORK::NET_TO_VEH(net_id))) {
				VEHICLE::SET_VEHICLE_FORWARD_SPEED(NETWORK::NET_TO_VEH(net_id), speed);
				VEHICLE::SET_VEHICLE_ENGINE_ON(NETWORK::NET_TO_VEH(net_id), TRUE, TRUE, TRUE);
				DECORATOR::DECOR_SET_INT(NETWORK::NET_TO_VEH(net_id), "MPBitset", (1 << 10));
				return NETWORK::NET_TO_VEH(net_id);
			}
		}
		return NULL;
	}

	std::uint64_t get_model_info(std::uint32_t hash) {
		DWORD index = 0xFFFF;
		return insight::pointers::get()->g_get_model_info(hash, &index);
	}
	void network::on_god_crash(int id) {
		features_utility::get()->ong_crash = true;
		std::int32_t ped = PLAYER::GET_PLAYER_PED(id);	
		if (ENTITY::DOES_ENTITY_EXIST(ped)) {
			{
					std::uint32_t hash = MISC::GET_HASH_KEY("adder");
					std::uint64_t model_info = get_model_info(hash);
					if (model_info != NULL) {
						*(std::int32_t*)(model_info + 0x340) = 8;
						std::int32_t vehicle = spawn_vehicle(hash, ped);
						if (ENTITY::DOES_ENTITY_EXIST(vehicle)) {
							ENTITY::SET_ENTITY_VISIBLE(vehicle, true, NULL);
							VEHICLE::SET_VEHICLE_ON_GROUND_PROPERLY(vehicle, FALSE);
							VEHICLE::SET_VEHICLE_FORWARD_SPEED(vehicle, 0.f);
							script::get_current()->yield(1000ms);
							ENTITY::SET_ENTITY_AS_MISSION_ENTITY(vehicle, 0, 1);
							VEHICLE::DELETE_VEHICLE(&vehicle);
						}
						*(std::int32_t*)(model_info + 0x340) = 0;
						script::get_current()->yield(1000ms);
						tasks::delete_entity(vehicle);

					}
			}
			{
					std::uint32_t hash = MISC::GET_HASH_KEY("roosevelt");
					std::uint64_t model_info = get_model_info(hash);
					if (model_info != NULL) {
						*(std::int32_t*)(model_info + 0x340) = 11;
						std::int32_t vehicle = spawn_vehicle(hash, ped);
						if (ENTITY::DOES_ENTITY_EXIST(vehicle)) {
							ENTITY::SET_ENTITY_VISIBLE(vehicle, true, NULL);
							VEHICLE::SET_VEHICLE_ON_GROUND_PROPERLY(vehicle, FALSE);
							VEHICLE::SET_VEHICLE_FORWARD_SPEED(vehicle, 0.f);
							NETWORK::NETWORK_FADE_OUT_ENTITY(vehicle, 0, 0);
							script::get_current()->yield(1000ms);
							ENTITY::SET_ENTITY_AS_MISSION_ENTITY(vehicle, 0, 1);
							VEHICLE::DELETE_VEHICLE(&vehicle);
						}
						*(std::int32_t*)(model_info + 0x340) = 3;
						script::get_current()->yield(1000ms);
						tasks::delete_entity(vehicle);

					}
			}
			{
					std::uint32_t hash = MISC::GET_HASH_KEY("dinghy");
					std::uint64_t model_info = get_model_info(hash);
					if (model_info != NULL) {
						*(std::int32_t*)(model_info + 0x340) = 1;
						std::int32_t vehicle = spawn_vehicle(hash, ped);
						if (ENTITY::DOES_ENTITY_EXIST(vehicle)) {
							ENTITY::SET_ENTITY_VISIBLE(vehicle, true, NULL);
							VEHICLE::SET_VEHICLE_ON_GROUND_PROPERLY(vehicle, FALSE);
							VEHICLE::SET_VEHICLE_FORWARD_SPEED(vehicle, 0.f);
							NETWORK::NETWORK_FADE_OUT_ENTITY(NETWORK::NET_TO_VEH(vehicle), 0, 0);
							script::get_current()->yield(1000ms);
							NETWORK::NETWORK_FADE_OUT_ENTITY(vehicle, 0, 0);
							NETWORK::NETWORK_FADE_OUT_ENTITY(NETWORK::NET_TO_VEH(vehicle), 0, 0);
							ENTITY::SET_ENTITY_AS_MISSION_ENTITY(vehicle, 0, 1);
							VEHICLE::DELETE_VEHICLE(&vehicle);
						}
						*(std::int32_t*)(model_info + 0x340) = 13;
						script::get_current()->yield(1000ms);
						tasks::delete_entity(vehicle);

					}
			}
		}

		features_utility::get()->ong_crash = false;
	}

	void network::parachute_crash(int i) {
		Player playerPed = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i);
		Vector3 playerCoords = ENTITY::GET_ENTITY_COORDS(playerPed, false);
		tasks::get()->play_ptfx_on_coordinates(nullptr,nullptr, playerCoords);

		features_utility::get()->parachute_crash = false;
	}

	void network::parachute_crash2(int i) {
		Player playerPed = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i);
		Vector3 playerCoords = ENTITY::GET_ENTITY_COORDS(playerPed, false);
		Hash ruiner = "ruiner2"_joaat;
		tasks::request_model(ruiner); playerCoords.z = playerCoords.z + 100;
		Vehicle veh = VEHICLE::CREATE_VEHICLE(ruiner, playerCoords, 0, true, 0, 0);
		ENTITY::SET_ENTITY_VISIBLE(ruiner, false, false);
		VEHICLE::VEHICLE_SET_PARACHUTE_MODEL_OVERRIDE(veh, "apa_mp_apa_crashed_usaf_01a"_joaat);
		PED::SET_PED_INTO_VEHICLE(globals::h_local_ped(), veh, -1);
		VEHICLE::VEHICLE_START_PARACHUTING(veh, true);
		script::get_current()->yield(5000ms);
		tasks::delete_entity(veh);

	}
}
