#include "cheat/features/tasks.hpp"
#include "cheat/render/render.hpp"
#include "cheat/features/features.hpp"
#include "cheat/features/globals.hpp"
#include "util/notify/notify.hpp"
#include "util/math/math.hpp"
#include "util/gta_util.hpp"
#include "util/caller.hpp"
#include "util/http/http.hpp"
#include <future>
#include "game/gta/net_object_mgr.hpp"
#include "cheat/features/scripted_globals.hpp"
#include "cheat/script/script_utility.hpp"
#include "cheat/features/features/features_utility.hpp"
#include "util/input/input.hpp"
namespace insight {
	int tasks::get_closest_vehicle(Vector3 pos, std::vector<int> ignored_ent, bool include_boats, bool include_planes, bool include_cars) {
		float closest_distance = std::numeric_limits<float>::max();
		int closest_entity = -1;

		for (auto vehicle : tasks::get_world_entities(true, false, false)) {
			bool ignore_vehicle = false;

			for (size_t i = 0; i < ignored_ent.size(); i++) {
				if (ignored_ent[i] == vehicle) {
					ignore_vehicle = true;
					break;
				}
			}

			if (ignore_vehicle)
				continue;

			if (ENTITY::IS_ENTITY_DEAD(vehicle, 0))
				continue;

			float distance = SYSTEM::VDIST(ENTITY::GET_ENTITY_COORDS(vehicle, 0), pos);

			if (distance < closest_distance) {
				closest_distance = distance;
				closest_entity = vehicle;
			}
		}

		return closest_entity;
	}

	int tasks::get_closest_ped(Vector3 pos, std::vector<int> ignored_ent) {
		float closest_distance = std::numeric_limits<float>::max();
		int closest_entity = -1;

		for (auto pedestrian : tasks::get_world_entities(false, true, false)) {
			bool ignore_ped = false;

			for (size_t i = 0; i < ignored_ent.size(); i++) {
				if (ignored_ent[i] == pedestrian) {
					ignore_ped = true;
					break;
				}
			}

			if (ignore_ped)
				continue;

			if (ENTITY::IS_ENTITY_DEAD(pedestrian, 0))
				continue;

			float distance = SYSTEM::VDIST(ENTITY::GET_ENTITY_COORDS(pedestrian, 0), pos);

			if (distance < closest_distance) {
				closest_distance = distance;
				closest_entity = pedestrian;
			}
		}

		return closest_entity;
	}
	int tasks::get_random_vehicle_w_clearsight(Entity ent, std::vector<int> ignored_ent) {
		for (auto vehicle : tasks::get_world_entities(false, true, false)) {
			bool ignore_ped = false;

			for (size_t i = 0; i < ignored_ent.size(); i++) {
				if (ignored_ent[i] == vehicle) {
					ignore_ped = true;
					break;
				}
			}

			if (ignore_ped)
				continue;

			if (ENTITY::IS_ENTITY_DEAD(vehicle, 0))
				continue;

			if (ENTITY::HAS_ENTITY_CLEAR_LOS_TO_ENTITY(vehicle, ent, 4294967295)) {
				int random = MISC::GET_RANDOM_INT_IN_RANGE(0, 1);
				if (random == 0)
					return vehicle;
				else
					continue;
			}
		}

		return 0;
	}
	int tasks::get_random_ground_vehicle_w_clearsight(Entity ent, std::vector<int> ignored_ent) {
		for (auto vehicle : tasks::get_world_entities(false, true, false)) {
			bool ignore_ped = false;

			for (size_t i = 0; i < ignored_ent.size(); i++) {
				if (ignored_ent[i] == vehicle) {
					ignore_ped = true;
					break;
				}
			}

			if (ignore_ped)
				continue;

			if (ENTITY::IS_ENTITY_DEAD(vehicle, 0))
				continue;

			if (ENTITY::HAS_ENTITY_CLEAR_LOS_TO_ENTITY(vehicle, ent, 4294967295) && ENTITY::GET_ENTITY_HEIGHT_ABOVE_GROUND(ent) < 5.f) {
				int random = MISC::GET_RANDOM_INT_IN_RANGE(0, 1);
				if (random == 0)
					return vehicle;
				else
					continue;
			}
		}

		return 0;
	}
	int tasks::get_random_air_vehicle_w_clearsight(Entity ent, std::vector<int> ignored_ent) {
		for (auto vehicle : tasks::get_world_entities(false, true, false)) {
			bool ignore_ped = false;

			for (size_t i = 0; i < ignored_ent.size(); i++) {
				if (ignored_ent[i] == vehicle) {
					ignore_ped = true;
					break;
				}
			}

			if (ignore_ped)
				continue;

			if (ENTITY::IS_ENTITY_DEAD(vehicle, 0))
				continue;

			if (ENTITY::HAS_ENTITY_CLEAR_LOS_TO_ENTITY(vehicle, ent, 4294967295) && ENTITY::GET_ENTITY_HEIGHT_ABOVE_GROUND(ent) > 5.f)
				return vehicle;
		}

		return 0;
	}
	int tasks::get_random_ped_w_clearsight(Entity ent, std::vector<int> ignored_ent) {
		for (auto pedestrian : tasks::get_world_entities(false, true, false)) {
			bool ignore_ped = false;

			for (size_t i = 0; i < ignored_ent.size(); i++) {
				if (ignored_ent[i] == pedestrian) {
					ignore_ped = true;
					break;
				}
			}

			if (ignore_ped)
				continue;

			if (ENTITY::IS_ENTITY_DEAD(pedestrian, 0))
				continue;

			if (ENTITY::HAS_ENTITY_CLEAR_LOS_TO_ENTITY(ent, pedestrian, 4294967295))
				return pedestrian;
		}

		return 0;
	}
	int tasks::get_closest_object(Vector3 pos, std::vector<int> ignored_ent) {
		float closest_distance = std::numeric_limits<float>::max();
		int closest_entity = -1;

		for (auto object : tasks::get_world_entities(false, false, true)) {
			bool ignore_object = false;

			for (size_t i = 0; i < ignored_ent.size(); i++) {
				if (ignored_ent[i] == object) {
					ignore_object = true;
					break;
				}
			}

			if (ignore_object)
				continue;

			float distance = SYSTEM::VDIST(ENTITY::GET_ENTITY_COORDS(object, 0), pos);

			if (distance < closest_distance) {
				closest_distance = distance;
				closest_entity = object;
			}
		}

		return closest_entity;
	}

	int tasks::get_closest_entity(Vector3 pos, std::vector<int> ignored_ent) {
		float closest_distance = std::numeric_limits<float>::max();
		int closest_entity = -1;

		for (auto entity : tasks::get_world_entities(true, true, true)) {
			bool ignore_entity = false;

			for (size_t i = 0; i < ignored_ent.size(); i++) {
				if (ignored_ent[i] == entity) {
					ignore_entity = true;
					break;
				}
			}

			if (ignore_entity)
				continue;

			float distance = SYSTEM::VDIST(ENTITY::GET_ENTITY_COORDS(entity, 0), pos);

			if (distance < closest_distance) {
				closest_distance = distance;
				closest_entity = entity;
			}
		}

		return closest_entity;
	}

	double distance_to_middle_of_screen(const rage::fvector2& screen_pos) {
		double cumulative_distance{};
		if (screen_pos.x > 0.5)
			cumulative_distance += screen_pos.x - 0.5;
		else
			cumulative_distance += 0.5 - screen_pos.x;
		if (screen_pos.y > 0.5)
			cumulative_distance += screen_pos.y - 0.5;
		else
			cumulative_distance += 0.5 - screen_pos.y;
		return cumulative_distance;
	}
	int tasks::get_closest_screen_entity() {
		Entity closest_entity{};
		float distance = 1;
		auto replayInterface = *insight::pointers::get()->g_replay_interface;
		auto vehicleInterface = replayInterface->m_vehicle_interface;
		auto pedInterface = replayInterface->m_ped_interface;

		for (auto veh : vehicleInterface->m_vehicle_list->m_vehicles) {
			if (veh.m_entity_ptr) {
				Vehicle handle = insight::pointers::get()->g_pointer_to_handle(veh.m_entity_ptr);
				Vector3 pos = ENTITY::GET_ENTITY_COORDS(handle, 1);
				rage::fvector2 screenpos;
				HUD::GET_HUD_SCREEN_POSITION_FROM_WORLD_POSITION(pos, &screenpos.x, &screenpos.y);

				if (distance_to_middle_of_screen(screenpos) < distance &&
					ENTITY::HAS_ENTITY_CLEAR_LOS_TO_ENTITY(globals::h_local_ped(), handle, 17)) {
					closest_entity = handle;
					distance = distance_to_middle_of_screen(screenpos);
				}
			}
		}

		for (auto ped : pedInterface->m_ped_list->m_peds) {
			if (ped.m_entity_ptr) {
				Vehicle handle = insight::pointers::get()->g_pointer_to_handle(ped.m_entity_ptr);
				Vector3 pos = ENTITY::GET_ENTITY_COORDS(handle, 1);
				rage::fvector2 screenpos;
				HUD::GET_HUD_SCREEN_POSITION_FROM_WORLD_POSITION(pos, &screenpos.x, &screenpos.y);

				if (distance_to_middle_of_screen(screenpos) < distance &&
					ENTITY::HAS_ENTITY_CLEAR_LOS_TO_ENTITY(globals::h_local_ped(), handle, 17) && handle != globals::h_local_ped()) {
					closest_entity = handle;
					distance = distance_to_middle_of_screen(screenpos);
				}
			}
		}

		return closest_entity;
	}

	void tasks::clean_ped(Ped ped)
	{
		PED::CLEAR_PED_BLOOD_DAMAGE(ped);
		PED::RESET_PED_VISIBLE_DAMAGE(ped);
		PED::CLEAR_PED_WETNESS(ped);
	}

	bool tasks::get_control_of_entity_tick(Entity entity)
	{
		if (NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(entity))
		{
			return true;
		}
		else
		{
			NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(entity);
		}
		return false;
	}

	float tasks::get_distance_between(Entity entity, Entity entity2) {
		float dx = ENTITY::GET_ENTITY_COORDS(entity, 0).x - ENTITY::GET_ENTITY_COORDS(entity2, 0).x;
		float dy = ENTITY::GET_ENTITY_COORDS(entity, 0).y - ENTITY::GET_ENTITY_COORDS(entity2, 0).y;
		float dz = ENTITY::GET_ENTITY_COORDS(entity, 0).z - ENTITY::GET_ENTITY_COORDS(entity2, 0).z;
		float distance = std::sqrt(dx * dx + dy * dy + dz * dz);
		return distance;
	}
	float tasks::get_distance_between(Vector3 coord1, Vector3 coord) {
		float dx = coord1.x - coord.x;
		float dy = coord1.y - coord.y;
		float dz = coord1.z - coord.z;
		float distance = std::sqrt(dx * dx + dy * dy + dz * dz);
		return distance;
	}
	float tasks::get_distance_between(Entity entity, Vector3 coord) {
		float dx = ENTITY::GET_ENTITY_COORDS(entity, 0).x - coord.x;
		float dy = ENTITY::GET_ENTITY_COORDS(entity, 0).y - coord.y;
		float dz = ENTITY::GET_ENTITY_COORDS(entity, 0).z - coord.z;
		float distance = std::sqrt(dx * dx + dy * dy + dz * dz);
		return distance;
	}
	float tasks::get_distance_between(Vector3 coord, Entity entity) {
		float dx = ENTITY::GET_ENTITY_COORDS(entity, 0).x - coord.x;
		float dy = ENTITY::GET_ENTITY_COORDS(entity, 0).y - coord.y;
		float dz = ENTITY::GET_ENTITY_COORDS(entity, 0).z - coord.z;
		float distance = std::sqrt(dx * dx + dy * dy + dz * dz);
		return distance;
	}

	void tasks::set_entity_damage_bits(CPed* entity, bool toggle) {
		if (!entity) {
			return;
		}
		if (toggle) {
			entity->m_damage_bits |= static_cast<uint32_t>(eEntityProofs::BULLET)
				| static_cast<uint32_t>(eEntityProofs::FIRE)
				| static_cast<uint32_t>(eEntityProofs::COLLISION)
				| static_cast<uint32_t>(eEntityProofs::MELEE)
				| static_cast<uint32_t>(eEntityProofs::GOD)
				| static_cast<uint32_t>(eEntityProofs::EXPLOSION)
				| static_cast<uint32_t>(eEntityProofs::STEAM)
				| static_cast<uint32_t>(eEntityProofs::DROWN)
				| static_cast<uint32_t>(eEntityProofs::WATER);
		}
		else {
			entity->m_damage_bits = 0; 
		}
	}

	std::vector<Entity> tasks::get_world_entities(bool vehicles, bool peds, bool objects)
	{
		std::vector<Entity> target_entities;
		target_entities.clear();
		const auto replay_interface = *insight::pointers::get()->g_replay_interface;
		if (!replay_interface)
			return target_entities;

		if (vehicles)
		{
			const auto vehicle_interface = replay_interface->m_vehicle_interface;
			for (int i = 0; i < vehicle_interface->m_max_vehicles; i++)
			{
				const auto vehicle_ptr = vehicle_interface->get_vehicle(i);
				if (!vehicle_ptr)
					continue;

				if (vehicle_ptr == gta_util::get_local_vehicle())
					continue;

				const auto veh = pointers::get()->g_pointer_to_handle(vehicle_ptr);
				if (!veh)
					break;

				target_entities.push_back(veh);
			}
		}

		if (peds)
		{
			const auto ped_interface = replay_interface->m_ped_interface;
			for (int i = 0; i < ped_interface->m_max_peds; i++)
			{
				const auto ped_ptr = ped_interface->get_ped(i);
				if (!ped_ptr)
					continue;
				if (ped_ptr == gta_util::get_local_ped())
					continue;

				const auto ped = pointers::get()->g_pointer_to_handle(ped_ptr);
				if (!ped)
					break;

				target_entities.push_back(ped);
			}
		}
		if (objects)
		{
			const auto ped_interface = replay_interface->m_object_interface;
			for (int i = 0; i < ped_interface->m_max_objects; i++)
			{
				const auto objectptr = ped_interface->get_object(i);
				if (!objectptr)
					continue;


				const auto ped = insight::pointers::get()->g_pointer_to_handle(objectptr);
				if (!ped)
					break;

				target_entities.push_back(ped);
			}
		}
		return target_entities;
	}
	float tasks::speed_to_kmh(float speed)
	{
		return floor(speed * 3.6);
	}

	EntityPosition tasks::get_entity_position_from_entity(Entity entity1, Entity entity2) {
		Vector3 pos1 = ENTITY::GET_ENTITY_COORDS(entity1, true);
		Vector3 pos2 = ENTITY::GET_ENTITY_COORDS(entity2, true);
		Vector3 forward1 = ENTITY::GET_ENTITY_FORWARD_VECTOR(entity1);
		Vector3 forward2 = ENTITY::GET_ENTITY_FORWARD_VECTOR(entity2);

		Vector3 relativePos = pos2 - pos1;

		float forward1Magnitude = sqrt(forward1.x * forward1.x + forward1.y * forward1.y + forward1.z * forward1.z);
		float relativePosMagnitude = sqrt(relativePos.x * relativePos.x + relativePos.y * relativePos.y + relativePos.z * relativePos.z);

		Vector3 forward1Normalized = { forward1.x / forward1Magnitude, forward1.y / forward1Magnitude, forward1.z / forward1Magnitude };
		Vector3 relativePosNormalized = { relativePos.x / relativePosMagnitude, relativePos.y / relativePosMagnitude, relativePos.z / relativePosMagnitude };

		float dotProductForward = forward1Normalized.x * relativePosNormalized.x + forward1Normalized.y * relativePosNormalized.y + forward1Normalized.z * relativePosNormalized.z;
		float dotProductRight = forward1Normalized.x * forward2.y - forward1Normalized.y * forward2.x;

		if (dotProductForward > 0.0f) {
			if (std::abs(dotProductRight) < std::abs(dotProductForward)) {
				return (dotProductRight > 0.0f) ? EntityPosition::Left : EntityPosition::Right;
			}
			else {
				return EntityPosition::Front;
			}
		}
		else {
			return EntityPosition::Behind;
		}

		return EntityPosition::Invalid;
	}

	void tasks::apply_force_to_position(Entity entity, Vector3 pos, Vector3 velocity, float frequency, float ratio, bool direc)
	{
		float random = MISC::GET_RANDOM_FLOAT_IN_RANGE(0.00002f, 0.00008f);
		ENTITY::APPLY_FORCE_TO_ENTITY(
			entity,
			3,
			Vector3((pos.x * (frequency * frequency)) - ((2.045f + random) * frequency * ratio * velocity.x),
				(pos.y * (frequency * frequency)) - ((2.035f + random) * frequency * ratio * velocity.y),
				(pos.z * (frequency * frequency)) - ((2.025f + random) * frequency * ratio * velocity.z)),
			Vector3(0.0f,
				0.0f,
				0.0f),
			0,
			direc,
			1,
			1,
			0,
			1
		);
	}

	void tasks::set_vehicle_engine_health(Vehicle veh, int health_s)
	{		//"Kill","On Fire","Smoking","Revive","Turn Off"
		if (health_s == 0)
		{
			VEHICLE::SET_VEHICLE_ENGINE_HEALTH(veh, -4000);
		}
		if (health_s == 1)
		{
			VEHICLE::SET_VEHICLE_ENGINE_HEALTH(veh, 0);
		}
		if (health_s == 2)
		{
			VEHICLE::SET_VEHICLE_ENGINE_HEALTH(veh, 300);
		}
		if (health_s == 3)
		{
			VEHICLE::SET_VEHICLE_ENGINE_HEALTH(veh, 1000);
		}
		if (health_s == 4)
		{
			if (VEHICLE::GET_IS_VEHICLE_ENGINE_RUNNING(veh))
				VEHICLE::SET_VEHICLE_ENGINE_ON(veh, false, true, true);
		}
	}
	void tasks::entity_never_delete(Entity ent, bool toggle)
	{
		ENTITY::SET_ENTITY_SHOULD_FREEZE_WAITING_ON_COLLISION(ent, toggle);
		if (globals::in_multiplayer())
		{
			int netHandle = NETWORK::NETWORK_GET_NETWORK_ID_FROM_ENTITY(ent);
			NETWORK::SET_NETWORK_ID_CAN_MIGRATE(netHandle, toggle);
		}
		ENTITY::SET_ENTITY_LOD_DIST(ent, 0xFFFF);

	}
	Vector3 tasks::get_weapon_bone_coords(const char* bone, Ped ped) {
		auto weaponEntity = WEAPON::GET_CURRENT_PED_WEAPON_ENTITY_INDEX(ped, 0);
		auto coords = ENTITY::GET_WORLD_POSITION_OF_ENTITY_BONE(weaponEntity, ENTITY::GET_ENTITY_BONE_INDEX_BY_NAME(weaponEntity, bone));
		return coords;
	}

	float deg_to_rad(float deg)
	{
		double radian = (3.14159265359 / 180) * deg;
		return (float)radian;
	}

	Vector3 rotation_to_direction(Vector3 rotation)
	{
		float x = deg_to_rad(rotation.x);
		float z = deg_to_rad(rotation.z);

		float num = abs(cos(x));

		return Vector3
		{
			-sin(z) * num,
			cos(z) * num,
			sin(x)
		};
	}


	ray_cast tasks::create_cast(Entity* entity) {
		BOOL hit;
		rage::scrVector end_coords;
		rage::scrVector surface;

		Vector3 cam_coords = CAM::GET_GAMEPLAY_CAM_COORD();
		Vector3 rot = CAM::GET_GAMEPLAY_CAM_ROT(2);
		Vector3 dir = rotation_to_direction(rot);
		Vector3 far_coords;

		far_coords.x = cam_coords.x + dir.x * 1000;
		far_coords.y = cam_coords.y + dir.y * 1000;
		far_coords.z = cam_coords.z + dir.z * 1000;

		int ray = SHAPETEST::START_EXPENSIVE_SYNCHRONOUS_SHAPE_TEST_LOS_PROBE(cam_coords, far_coords, -1, globals::h_local_vehicle(true) ? globals::h_local_vehicle(true) : globals::h_local_ped(), 7);
		auto handle = SHAPETEST::GET_SHAPE_TEST_RESULT(ray, &hit, &end_coords, &surface, entity);

		return { {end_coords.x, end_coords.y, end_coords.z}, (bool)hit };


	}	
	bool tasks::point_to_point_cast(Vector3 v1, Vector3 b2) {
		Vector3 raycastHit, raycastHitZ;
		Entity raycastHitEntity;
		BOOL hasRaycastHit;
		Vector3 camRotation = CAM::GET_GAMEPLAY_CAM_ROT(2);
		Vector3 camCoords = CAM::GET_GAMEPLAY_CAM_COORD();
		Vector3 camCoordsFromHead = vectors::get()->get_front_camera_coordinates_local(0);
		Vector3 camCoordsTo = camCoords + (vectors::get()->get_cam_direction(camRotation) * 1000);
		int rayHandle = SHAPETEST::START_EXPENSIVE_SYNCHRONOUS_SHAPE_TEST_LOS_PROBE(v1, b2, 4294967295, globals::h_local_vehicle(true) ? globals::h_local_vehicle(true) : globals::h_local_ped(), 7);
		int rayResult = SHAPETEST::GET_SHAPE_TEST_RESULT(rayHandle, &hasRaycastHit, &raycastHit, &raycastHitZ, &raycastHitEntity);

		if (hasRaycastHit) {
			return true;
		}
		return false;
	}
	Vector3 tasks::get_laser_ending_coordinates(float distance)
	{
		Vector3 raycastHit, raycastHitZ;
		Entity raycastHitEntity;
		BOOL hasRaycastHit;
		Vector3 camRotation = CAM::GET_GAMEPLAY_CAM_ROT(2);
		Vector3 camCoords = CAM::GET_GAMEPLAY_CAM_COORD();
		Vector3 camCoordsFromHead = vectors::get()->get_front_camera_coordinates_local(0);
		Vector3 camCoordsTo = camCoords + (vectors::get()->get_cam_direction(camRotation) * 1000);
		int rayHandle = SHAPETEST::START_EXPENSIVE_SYNCHRONOUS_SHAPE_TEST_LOS_PROBE(camCoordsFromHead, camCoordsTo, 4294967295, globals::h_local_vehicle(true) ? globals::h_local_vehicle(true) : globals::h_local_ped(), 7);
		int rayResult = SHAPETEST::GET_SHAPE_TEST_RESULT(rayHandle, &hasRaycastHit, &raycastHit, &raycastHitZ, &raycastHitEntity);

		if (hasRaycastHit) {
			if (distance != 0) {
				Vector3 direction = vectors::get()->get_cam_direction(camRotation);
				float adjustment = (distance >= 0) ? distance : -distance;
				raycastHit.x -= direction.x * adjustment;
				raycastHit.y -= direction.y * adjustment;
				raycastHit.z -= direction.z * adjustment;
			}
			return raycastHit;
		}
		return vectors::get()->get_front_camera_coordinates_local(200);
	}
	ray_cast tasks::create_cast_intersect_all(Entity* entity) {
		BOOL hit;
		rage::scrVector end_coords;
		rage::scrVector surface;

		Vector3 cam_coords = CAM::GET_GAMEPLAY_CAM_COORD();
		Vector3 rot = CAM::GET_GAMEPLAY_CAM_ROT(2);
		Vector3 dir = rotation_to_direction(rot);
		Vector3 far_coords;

		far_coords.x = cam_coords.x + dir.x * 1000;
		far_coords.y = cam_coords.y + dir.y * 1000;
		far_coords.z = cam_coords.z + dir.z * 1000;

		int ray = SHAPETEST::START_EXPENSIVE_SYNCHRONOUS_SHAPE_TEST_LOS_PROBE(cam_coords, far_coords, 4294967295, 0, 4);
		auto handle = SHAPETEST::GET_SHAPE_TEST_RESULT(ray, &hit, &end_coords, &surface, entity);



		return { {end_coords.x, end_coords.y, end_coords.z}, (bool)hit };


	}
	enum EntityType {
		PedEntity,
		VehicleEntity,
		ObjectEntity
	};

	std::int32_t tasks::create_cast_entites(int entityType, bool drawRay) {
		Vector3 raycastStart, raycastEnd;
		Entity hitEntity;
		BOOL didHit;

		Vector3 cameraRotation = CAM::GET_GAMEPLAY_CAM_ROT(2);
		Vector3 cameraPosition = CAM::GET_GAMEPLAY_CAM_COORD();
		Vector3 cameraHeadPosition = vectors::get()->get_front_camera_coordinates_local(0);
		Vector3 cameraDirection = cameraPosition + (rotation_to_direction(cameraRotation) * 1000);
		int shapeFlag = 0;
		switch (entityType) {
		case PedEntity:
			shapeFlag = 8;
			break;
		case VehicleEntity:
			shapeFlag = 2;
			break;
		case ObjectEntity:
			shapeFlag = 16;
			break;
		}

		int raycastHandle = SHAPETEST::START_EXPENSIVE_SYNCHRONOUS_SHAPE_TEST_LOS_PROBE(cameraHeadPosition, cameraDirection, shapeFlag, globals::h_local_vehicle(true) ? globals::h_local_vehicle(true) : globals::h_local_ped(), 4
		);

		int raycastResult = SHAPETEST::GET_SHAPE_TEST_RESULT( raycastHandle, &didHit, &raycastStart, &raycastEnd, &hitEntity);

		if (drawRay) {
			GRAPHICS::DRAW_LINE(cameraHeadPosition,raycastEnd,255, 0, 0, 255 );
		}

		return hitEntity;
	}

	std::int32_t tasks::create_cast_entites() {
		Entity ent_ped = tasks::create_cast_entites(0, 0);
		Entity ent_veh = tasks::create_cast_entites(1, 0);
		Entity ent_obj = tasks::create_cast_entites(2, 0);
		if (ENTITY::DOES_ENTITY_EXIST(ent_ped)) {
			return ent_ped;
		}
		else if (ENTITY::DOES_ENTITY_EXIST(ent_veh)) {
			return ent_veh;
		}
		else if (ENTITY::DOES_ENTITY_EXIST(ent_obj)) {
			return ent_obj;
		}
		return 0;
	}
	Cam draw_cam_around_entity_camera;
	void remove_draw_cam_around_entity()
	{
		if (CAM::DOES_CAM_EXIST(draw_cam_around_entity_camera))
		{
			CAM::RENDER_SCRIPT_CAMS(false, true, 700, 1, 1, 1);
			CAM::SET_CAM_ACTIVE(draw_cam_around_entity_camera, false);
			CAM::DESTROY_CAM(draw_cam_around_entity_camera, true);
		}
	}
	timer draw_cam_rotating_cam_around_entity_delay(std::chrono::milliseconds(800ms));
	Vector3 entvec360;
	void tasks::draw_cam_rotating_cam_around_entity(Entity entity, float distance, float fov)
	{
		Vector3 entvec = ENTITY::GET_ENTITY_COORDS(entity, 0);
		entvec360 = vectors::get()->get_360_vec_around_coord(entvec, distance, 0, 360);
		if (!CAM::DOES_CAM_EXIST(draw_cam_around_entity_camera)) {
			draw_cam_around_entity_camera = CAM::CREATE_CAM("DEFAULT_SCRIPTED_CAMERA", 1);
			CAM::SET_CAM_COORD(draw_cam_around_entity_camera, entvec360);
			CAM::SET_CAM_FOV(draw_cam_around_entity_camera, fov);
			CAM::RENDER_SCRIPT_CAMS(true, true, 700, 1, 1, 0);
			CAM::SET_CAM_ACTIVE(draw_cam_around_entity_camera, true);
		}
		else
		{
			Vector3 entvec = ENTITY::GET_ENTITY_COORDS(entity, 0);
			if (draw_cam_rotating_cam_around_entity_delay.update())
			{
				entvec360 = vectors::get()->get_360_vec_around_coord(entvec, distance, 0, 360);
			}
			CAM::SET_CAM_COORD(draw_cam_around_entity_camera, entvec360);
			CAM::POINT_CAM_AT_ENTITY(draw_cam_around_entity_camera, entity, 0, 0, 0, 1);
		}

	}
	int anti_bug_draw_cam_around_entity_tick = 0;
	void tasks::draw_cam_around_entity_tick()
	{
		if (anti_bug_draw_cam_around_entity_tick < 200) {
			anti_bug_draw_cam_around_entity_tick++;
		}
		if (anti_bug_draw_cam_around_entity_tick > 198) {
			if (features_utility::get()->player_info_line.update()) {
				features_utility::get()->player_info_line_vec = globals::h_local_ped_pos();
			}
			if (render::get()->m_opened) {

				if (render::get()->m_submenu_stack.top()->get_id() == "World_Sentry"_joaat) {
					if (render::get()->m_submenu_stack.top()->get_selected_option() == 1 || render::get()->m_submenu_stack.top()->get_selected_option() == 2) {
						Vector3 marker = vectors::get()->get_front_camera_coordinates_local(10);
						tasks::draw_marker(eMarkerType::MarkerTypeVerticalCylinder, marker, 1.5f, 100, 100, 100, 170, true);
					}
				}

				if (render::get()->m_submenu_stack.top()->get_id() == "Wardrobe"_joaat) {
					tasks::draw_cam_rotating_cam_around_entity(globals::h_local_ped(), 2.0f);
				}
				else if (render::get()->m_submenu_stack.top()->get_id() == "Wardrobe_Editor"_joaat) {
					tasks::draw_cam_rotating_cam_around_entity(globals::h_local_ped(), 2.0f);
				}
				else {
					remove_draw_cam_around_entity();
				}

			}
			else {
				remove_draw_cam_around_entity();
			}
		}
	}

	bool tasks::is_ped_on_seat(Ped ped, Vehicle vehicle, eSeatPosition seat)
	{
		Ped get_ped = VEHICLE::GET_PED_IN_VEHICLE_SEAT(vehicle, seat, false);
		if (get_ped == ped)
		{
			return true;
		}
		return false;
	}

	void tasks::break_vehicle_wheels(int veh)
	{
		if (veh) {
			if (tasks::request_control(veh)) {
				VEHICLE::SET_VEHICLE_WHEELS_CAN_BREAK(veh, true);
				ENTITY::SET_ENTITY_MAX_SPEED(veh, -INT_MAX);
				VEHICLE::MODIFY_VEHICLE_TOP_SPEED(veh, -INT_MAX);
				VEHICLE::SET_VEHICLE_FORWARD_SPEED(veh, -INT_MAX);
			}
			return;

		}
	}

	void tasks::fix_vehicle(int veh)
	{
		if (globals::in_multiplayer())
			NETWORK::NETWORK_FADE_OUT_ENTITY(veh, false, true);
		VEHICLE::SET_VEHICLE_FIXED(veh);
		VEHICLE::SET_VEHICLE_DIRT_LEVEL(veh, 0.f);
		if (globals::in_multiplayer())
			NETWORK::NETWORK_FADE_IN_ENTITY(veh, 1, true);

	}

	void tasks::upgrade_vehicle(Vehicle veh)
	{
		if (ENTITY::DOES_ENTITY_EXIST(veh)) {
			if (globals::in_multiplayer())
				NETWORK::NETWORK_FADE_OUT_ENTITY(veh, false, true);

			VEHICLE::SET_VEHICLE_MOD_KIT(veh, 0);
			for (int i = 0; i < 49; i++)
			{

				if (VEHICLE::GET_NUM_VEHICLE_MODS(veh, i) != 0) {
					if (i == MOD_TURBO)
					{
						VEHICLE::TOGGLE_VEHICLE_MOD(veh, MOD_TURBO, true);
					}
					else
						if (i == MOD_XENONLIGHTS)
						{
							VEHICLE::TOGGLE_VEHICLE_MOD(veh, MOD_XENONLIGHTS, true);

						}
					if (i == MOD_ROOF || MOD_RIGHTFENDER || MOD_HOOD || MOD_GRILLE || MOD_CHASSIS || MOD_EXHAUST || MOD_SIDESKIRT || MOD_REARBUMPER || MOD_FRONTBUMPER || MOD_SPOILER)
					{
						int random_select = MISC::GET_RANDOM_INT_IN_RANGE(0, VEHICLE::GET_NUM_VEHICLE_MODS(veh, i));
						VEHICLE::SET_VEHICLE_MOD(veh, i, random_select, false);
					}
					else
					{
						VEHICLE::SET_VEHICLE_MOD(veh, i, VEHICLE::GET_NUM_VEHICLE_MODS(veh, i), false);
					}
				}
			}
			VEHICLE::SET_VEHICLE_TYRES_CAN_BURST(veh, false);
			VEHICLE::SET_VEHICLE_WINDOW_TINT(veh, 1);

			if (globals::in_multiplayer())
				NETWORK::NETWORK_FADE_IN_ENTITY(veh, 1, true);
		}
	}

	void tasks::gift_vehicle(int veh, Player player)
	{
		if (globals::in_multiplayer())
			NETWORK::NETWORK_FADE_OUT_ENTITY(veh, false, true);
		Ped SELECTED_PLAYER = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player);
		ENTITY::SET_ENTITY_AS_MISSION_ENTITY(veh, TRUE, TRUE);
		DECORATOR::DECOR_REGISTER("PV_Slot", 3);
		DECORATOR::DECOR_REGISTER("Player_Vehicle", 3);
		DECORATOR::DECOR_SET_BOOL(veh, "IgnoredByQuickSave", FALSE);
		DECORATOR::DECOR_SET_INT(veh, "Player_Vehicle", NETWORK::NETWORK_HASH_FROM_PLAYER_HANDLE(player));
		VEHICLE::SET_VEHICLE_IS_STOLEN(veh, FALSE);
		if (globals::in_multiplayer())
			NETWORK::NETWORK_FADE_IN_ENTITY(veh, 1, true);

	}

	void tasks::vehicle_apply_force(Vehicle veh, int force, float multiplier)
	{
		if (force == Front)
		{
			ENTITY::APPLY_FORCE_TO_ENTITY(veh, true, Vector3(0, 0, 0.1), Vector3(0, 0.3 * multiplier, 0), true, true, true, true, false, true);
		}
		else if (force == Back)
		{
			ENTITY::APPLY_FORCE_TO_ENTITY(veh, true, Vector3(0, 0, 0.1), Vector3(0, -0.3 * multiplier, 0), true, true, true, true, false, true);

		}
		else if (force == Left)
		{
			ENTITY::APPLY_FORCE_TO_ENTITY(veh, true, Vector3(0, 0, 0.1), Vector3(0.3 * multiplier, 0, 0), true, true, true, true, false, true);

		}
		else if (force == Right)
		{
			ENTITY::APPLY_FORCE_TO_ENTITY(veh, true, Vector3(0, 0, 0.1), Vector3(-0.3 * multiplier, 0, 0), true, true, true, true, false, true);

		}
		else if (force == Up)
		{
			ENTITY::APPLY_FORCE_TO_ENTITY(veh, true, Vector3(0, 0, 0.3 * multiplier), Vector3(0, 0, 0), true, true, true, true, false, true);

		}
		else if (force == Down)
		{
			ENTITY::APPLY_FORCE_TO_ENTITY(veh, true, Vector3(0, 0, -0.3 * multiplier), Vector3(0, 0, 0), true, true, true, true, false, true);

		}

	}

	void tasks::vehicle_acrobatics(Vehicle veh, int force, float multiplier)
	{
		if (force == Front)
		{
			for (int i = 0; i < 4; i++)
			{
				ENTITY::APPLY_FORCE_TO_ENTITY(veh, true, Vector3(0, 0, 6.0f * multiplier), Vector3(0, -2.0f * multiplier, 0), true, true, true, true, false, true);

			}
		}
		else if (force == Back)
		{
			for (int i = 0; i < 4; i++)
			{
				ENTITY::APPLY_FORCE_TO_ENTITY(veh, true, Vector3(0, 0, 6.0f * multiplier), Vector3(0, 2.0f * multiplier, 0), true, true, true, true, false, true);
			}
		}
		else if (force == Left)
		{
			for (int i = 0; i < 4; i++)
			{
				ENTITY::APPLY_FORCE_TO_ENTITY(veh, true, Vector3(0, 0, 5.0f * multiplier), Vector3(2.0f * multiplier, 0, 0), true, true, true, true, false, true);
			}

		}
		else if (force == Right)
		{
			for (int i = 0; i < 4; i++)
			{
				ENTITY::APPLY_FORCE_TO_ENTITY(veh, true, Vector3(0, 0, 5.0f * multiplier), Vector3(-2.0f * multiplier, 0, 0), true, true, true, true, false, true);
			}

		}
		else if (force == Up)
		{
			for (int i = 0; i < 4; i++)
			{
				ENTITY::APPLY_FORCE_TO_ENTITY(veh, true, Vector3(0, 0, 1.0f * multiplier), Vector3(0, 0, 0), true, true, true, true, false, true);
			}

		}
		else if (force == Down)
		{
			for (int i = 0; i < 4; i++)
			{
				ENTITY::APPLY_FORCE_TO_ENTITY(veh, true, Vector3(0, 0, -1.0f * multiplier), Vector3(0, 0, 0), true, true, true, true, false, true);
			}

		}

	}

	void v_drive_task_set(Ped ped, Vehicle veh, float speed, int drivestyple, bool to_coords, Vector3 coords, float stop_range)
	{
		DRIVING_STYLE drive_anim_set;
		PED::SET_DRIVER_ABILITY(ped, 1.0);
		PED::SET_DRIVER_AGGRESSIVENESS(ped, 1.0);
		if (drivestyple == 0)
		{
			drive_anim_set = DRIVING_STYLE::AVOID_TRAFFIC_EXTREMELY;
		}
		if (drivestyple == 1)
		{
			drive_anim_set = DRIVING_STYLE::NORMAL;
		}
		if (drivestyple == 2)
		{
			drive_anim_set = DRIVING_STYLE::RUSHED;
		}
		if (!to_coords) {
			TASK::TASK_VEHICLE_DRIVE_WANDER(ped, veh, speed, drive_anim_set);
		}
		else
		{
			TASK::TASK_VEHICLE_DRIVE_TO_COORD_LONGRANGE(ped, veh, coords, speed, drive_anim_set, stop_range);
		}
	}

	void tasks::drive_wander(Ped ped, Vehicle veh, float speed, int drivestyple)
	{

		v_drive_task_set(ped, veh, speed, drivestyple, false, Vector3(0, 0, 0), 0);
	}
	void tasks::drive_to_coordinates(Ped ped, Vehicle veh, float speed, int drivestyple, Vector3 coords, float stop_range)
	{
		v_drive_task_set(ped, veh, speed, drivestyple, true, coords, stop_range);
	}

	void tasks::plane_attacker(const char* vehiclehash, int ped, int vehicle)
	{
		Ped playerr = ped;

		const auto pos = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(playerr, Vector3(MISC::GET_RANDOM_FLOAT_IN_RANGE(0.f, 170), MISC::GET_RANDOM_FLOAT_IN_RANGE(0.f, 170), 170));
		Hash hash = rage::joaat(vehiclehash);
		Hash pedHash = rage::joaat("s_m_y_blackops_01");
		while (!STREAMING::HAS_MODEL_LOADED(hash) && !STREAMING::HAS_MODEL_LOADED(pedHash))
		{
			STREAMING::REQUEST_MODEL(hash);
			STREAMING::REQUEST_MODEL(pedHash);
			script::get_current()->yield();
		}
		if (STREAMING::HAS_MODEL_LOADED(hash) && STREAMING::HAS_MODEL_LOADED(pedHash))
		{
			Vehicle Created_Veh = VEHICLE::CREATE_VEHICLE(hash, Vector3(pos.x, pos.y, pos.z + 170), 0.f, TRUE, TRUE, TRUE);
			VEHICLE::SET_VEHICLE_ENGINE_ON(Created_Veh, true, true, false);
			VEHICLE::CONTROL_LANDING_GEAR(Created_Veh, 3);
			Ped Created_Ped = PED::CREATE_PED_INSIDE_VEHICLE(Created_Veh, 26, pedHash, -1, true, true);
			TASK::TASK_PLANE_MISSION(Created_Ped, Created_Veh, vehicle, playerr, Vector3(0, 0, 0), 6, 30.00, 0.f, 90.f, 0, 0, 0);
			PED::SET_PED_FIRING_PATTERN(Created_Ped, 0xC6EE6B4C);
			STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(hash);
			STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(pedHash);
			tasks::upgrade_vehicle(Created_Veh);
			if (globals::in_multiplayer())
			{
				DECORATOR::DECOR_SET_INT(Created_Veh, "MPBitset", 0);
				ENTITY::SET_ENTITY_SHOULD_FREEZE_WAITING_ON_COLLISION(Created_Veh, TRUE);
				auto networkId = NETWORK::VEH_TO_NET(Created_Veh);
				if (NETWORK::NETWORK_GET_ENTITY_IS_NETWORKED(Created_Veh))
					NETWORK::SET_NETWORK_ID_EXISTS_ON_ALL_MACHINES(networkId, true);
				VEHICLE::SET_VEHICLE_IS_STOLEN(Created_Veh, FALSE);
			}
		}

	}

	void tasks::spawn_custom_attacker(int ped, Hash ped_hash, Hash weapon, int health, bool godmode)
	{
		while (!STREAMING::HAS_MODEL_LOADED(ped_hash)) {
			STREAMING::REQUEST_MODEL(ped_hash);
			script::get_current()->yield();
		}
		Vector3 pos = ENTITY::GET_ENTITY_COORDS(ped, 0);
		Ped attacker = PED::CREATE_PED(26, ped_hash, pos, 0, globals::in_multiplayer(), 0);
		if (tasks::request_control(attacker))
		{
			PED::SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(attacker, 1);
			PED::REGISTER_TARGET(attacker, ped);

			TASK::TASK_COMBAT_PED(attacker, ped, 0, 16);
			PED::SET_PED_CAN_SWITCH_WEAPON(attacker, true);
			WEAPON::GIVE_DELAYED_WEAPON_TO_PED(attacker, weapon, 1000, true);
			if (!godmode)
			{
				ENTITY::SET_ENTITY_HEALTH(attacker, health, 1);

			}
			else
			{
				ENTITY::SET_ENTITY_INVINCIBLE(attacker, true);
			}
			PED::SET_PED_COMBAT_ATTRIBUTES(attacker, eCombatAttribute::CA_ALWAYS_FIGHT, TRUE);
			PED::SET_PED_COMBAT_ATTRIBUTES(attacker, eCombatAttribute::CA_CAN_FIGHT_ARMED_PEDS_WHEN_NOT_ARMED, TRUE);
			PED::SET_PED_COMBAT_ATTRIBUTES(attacker, eCombatAttribute::CA_QUIT_WHEN_TARGET_FLEES_INTERACTION_FIGHT, false);
		}
	}
	void tasks::spawn_formation_vehicle(int target, const char* car, const char* ped, int number_spawn, float miniumdistance, float minimumheight, float noroadsdistance)
	{
		Vector3 pos = ENTITY::GET_ENTITY_COORDS(target, 0);
		Hash vehicle_hash = rage::joaat(car);
		Hash ped_hash = rage::joaat(ped);
		for (int i = 0; i < number_spawn; i++)
		{
			while (!STREAMING::HAS_MODEL_LOADED(vehicle_hash) || !STREAMING::HAS_MODEL_LOADED(ped_hash))
			{
				STREAMING::REQUEST_MODEL(vehicle_hash);
				STREAMING::REQUEST_MODEL(ped_hash);
				script::get_current()->yield();
			}
			Vehicle v = VEHICLE::CREATE_VEHICLE(vehicle_hash,
				Vector3(pos.x + MISC::GET_RANDOM_FLOAT_IN_RANGE(-20, 20)
					, pos.y + MISC::GET_RANDOM_FLOAT_IN_RANGE(-20, 20)
					, pos.z + 5)
				, 100.f, globals::in_multiplayer(), 0, 0);
			Ped p = PED::CREATE_PED_INSIDE_VEHICLE(v, 26, ped_hash, -1, globals::in_multiplayer(), 0);
			PED::SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(p, 1);
			ENTITY::SET_ENTITY_INVINCIBLE(p, 1);
			ENTITY::SET_ENTITY_INVINCIBLE(v, 1);
			ENTITY::SET_ENTITY_MAX_SPEED(v, 9999);
			VEHICLE::SET_VEHICLE_CHEAT_POWER_INCREASE(v, 999.f);
			//	PED::SET_DRIVER_AGGRESSIVENESS(p, 100.f);
			//	TASK::TASK_VEHICLE_FOLLOW(p, v, target, 0, 1000.0f, 0);
			PED::SET_PED_KEEP_TASK(p, true);
			TASK::TASK_VEHICLE_ESCORT(p, v, target, MISC::GET_RANDOM_INT_IN_RANGE(-1, 4), 999, 16777216, miniumdistance, minimumheight, noroadsdistance);
		}
	}
	void tasks::delete_entity(Entity id) {
		if (tasks::request_control(id)) {
			ENTITY::SET_ENTITY_AS_MISSION_ENTITY(id, 0, 0);
			ENTITY::DELETE_ENTITY(&id);
		}
	}
	void tasks::spawn_n_play_sound(Hash ped_hash, Vector3 pos, const char* speeche, const char* voice_name)
	{
		while (!STREAMING::HAS_MODEL_LOADED(ped_hash)) {
			STREAMING::REQUEST_MODEL(ped_hash);
			script::get_current()->yield();
		}
		Ped ped = PED::CREATE_PED(26, ped_hash, pos, 0, globals::in_multiplayer(), 0);
		AUDIO::PLAY_PED_AMBIENT_SPEECH_WITH_VOICE_NATIVE(ped, speeche, voice_name, xorstr_("SPEECH_PARAMS_FORCE"), globals::in_multiplayer());
		//	notify::send("fgf", "econdence");
		script::get_current()->yield(8s);
		tasks::delete_entity(ped);
	}
	void tasks::clear_tasks(Ped ped) {
		if (PED::IS_PED_A_PLAYER(ped) && globals::in_multiplayer()) {
			if (PED::IS_PED_IN_ANY_VEHICLE(ped, 0)) {
				rage::CDynamicEntity* vehicle = (rage::CDynamicEntity*)insight::pointers::get()->g_handle_to_pointer(PED::GET_VEHICLE_PED_IS_USING(ped));
				(*insight::pointers::get()->g_network_object_mgr)->ChangeOwner(vehicle->m_net_object, insight::pointers::get()->g_netplayer(globals::player_id), 0);
			}
			else
			{
				insight::pointers::get()->g_clear_ped_tasks_network((CPed*)insight::pointers::get()->g_handle_to_pointer(ped), true);
			}
		}
		else {
			TASK::CLEAR_PED_TASKS_IMMEDIATELY(ped);
		}
	}
	int tasks::get_vehicle_non_free_seats(int veh)
	{
		for (int seatnum = -1; seatnum < 6; ++seatnum) {
			if (!VEHICLE::IS_VEHICLE_SEAT_FREE(veh, seatnum, 0))
			{
				if (Ped p = VEHICLE::GET_PED_IN_VEHICLE_SEAT(veh, seatnum, 0))
				{
					if (PED::IS_PED_IN_VEHICLE(p, veh, 0) && (!PED::IS_PED_DEAD_OR_DYING(p, 1)))
					{
						return seatnum;
					}
				}
			}
		}
		return 0;
	}	
	bool tasks::get_vehicle_free_seat(int veh,int &seat_out)
	{
		for (int seatnum = -1; seatnum < 6; ++seatnum) {
			if (VEHICLE::IS_VEHICLE_SEAT_FREE(veh, seatnum, 0)) {
				seat_out = seatnum;
				return true;
			}
		}
		return false;
	}
	void tasks::vehicle_attachments(Vehicle veh, int type) {
		{
			if (type == 0)
			{
				Vector3 pos = ENTITY::GET_ENTITY_COORDS(veh, 0);
				pos.x = pos.x + 10.f;
				tasks::request_model("apa_mp_apa_yacht_radar_01a"_joaat);
				Object main_radar = OBJECT::CREATE_OBJECT(rage::joaat("apa_mp_apa_yacht_radar_01a"), pos, globals::in_multiplayer(), 0, 0);
				tasks::request_model(-1268267712);
				Object obj_ufo = OBJECT::CREATE_OBJECT(-1268267712, pos, globals::in_multiplayer(), 0, 0);
				script::get_current()->yield(100ms);
				ENTITY::ATTACH_ENTITY_TO_ENTITY(main_radar, veh, 1, Vector3(0.0, 0, 5.0), Vector3(0.0, 0.0, 180), 0, true, false, false, 1, false, 0);
				ENTITY::ATTACH_ENTITY_TO_ENTITY(obj_ufo, main_radar, 1, Vector3(0.0, 0, 0.0), Vector3(0.0, 0.0, 180), 0, true, false, false, 1, true, 0);
				ENTITY::SET_ENTITY_VISIBLE(main_radar, false, false);


				while (!ENTITY::IS_ENTITY_VISIBLE(obj_ufo))
				{
					ENTITY::SET_ENTITY_VISIBLE(obj_ufo, 1, 0);

					script::get_current()->yield();

				}
				return;
			}
			if (type == 1)
			{
				Vector3 pos = ENTITY::GET_ENTITY_COORDS(veh, 0);
				pos.x = pos.x + 10.f;
				int boneindex = ENTITY::GET_ENTITY_BONE_INDEX_BY_NAME(veh, "wheel_lf");
				Vector3 posbone = ENTITY::GET_WORLD_POSITION_OF_ENTITY_BONE(veh, boneindex);
				if (posbone.x != 0)
				{
					Object tire1 = OBJECT::CREATE_OBJECT(rage::joaat("prop_rub_tyre_03"), pos, globals::in_multiplayer(), 0, 0);
					ENTITY::ATTACH_ENTITY_TO_ENTITY(tire1, veh, boneindex, Vector3(-1.0, 0, 0.0), Vector3(0, 0, 0), 0, true, false, false, 1, 1, 0);
					tasks::entity_never_delete(tire1);

				}
				boneindex = ENTITY::GET_ENTITY_BONE_INDEX_BY_NAME(veh, "wheel_lr");
				posbone = ENTITY::GET_WORLD_POSITION_OF_ENTITY_BONE(veh, boneindex);
				if (posbone.x != 0)
				{
					Object tire1 = OBJECT::CREATE_OBJECT(rage::joaat("prop_rub_tyre_03"), pos, globals::in_multiplayer(), 0, 0);
					ENTITY::ATTACH_ENTITY_TO_ENTITY(tire1, veh, boneindex, Vector3(-1.0, 0, 0.0), Vector3(0, 0, 0), 0, true, false, false, 1, 1, 0);
					tasks::entity_never_delete(tire1);
				}
				boneindex = ENTITY::GET_ENTITY_BONE_INDEX_BY_NAME(veh, "wheel_rf");
				posbone = ENTITY::GET_WORLD_POSITION_OF_ENTITY_BONE(veh, boneindex);
				if (posbone.x != 0)
				{
					Object tire1 = OBJECT::CREATE_OBJECT(rage::joaat("prop_rub_tyre_03"), pos, globals::in_multiplayer(), 0, 0);
					ENTITY::ATTACH_ENTITY_TO_ENTITY(tire1, veh, boneindex, Vector3(-1.0, 0, 0.0), Vector3(0, 0, 0), 0, true, false, false, 1, 1, 0);
					tasks::entity_never_delete(tire1);
				}
				boneindex = ENTITY::GET_ENTITY_BONE_INDEX_BY_NAME(veh, "wheel_rr");
				posbone = ENTITY::GET_WORLD_POSITION_OF_ENTITY_BONE(veh, boneindex);
				if (posbone.x != 0)
				{
					Object tire1 = OBJECT::CREATE_OBJECT(rage::joaat("prop_rub_tyre_03"), pos, globals::in_multiplayer(), 0, 0);
					ENTITY::ATTACH_ENTITY_TO_ENTITY(tire1, veh, boneindex, Vector3(-1.0, 0, 0.0), Vector3(0, 0, 0), 0, true, false, false, 1, 1, 0);
					tasks::entity_never_delete(tire1);
				}
				return;
			}
			if (type == 2)
			{
				Vector3 pos = ENTITY::GET_ENTITY_COORDS(veh, 0);
				pos.x = pos.x + 10.f;
				int boneindex = ENTITY::GET_ENTITY_BONE_INDEX_BY_NAME(veh, "wheel_lf");
				Vector3 posbone = ENTITY::GET_WORLD_POSITION_OF_ENTITY_BONE(veh, boneindex);
				if (posbone.x != 0)
				{
					Object tire1 = OBJECT::CREATE_OBJECT(rage::joaat("prop_tree_fallen_01"), pos, globals::in_multiplayer(), 0, 0);
					ENTITY::ATTACH_ENTITY_TO_ENTITY(tire1, veh, boneindex, Vector3(-1.0, 0, 0.0), Vector3(0, 0, 0), 0, true, false, false, 1, 1, 0);
					tasks::entity_never_delete(tire1);
				}
				boneindex = ENTITY::GET_ENTITY_BONE_INDEX_BY_NAME(veh, "wheel_rf");
				posbone = ENTITY::GET_WORLD_POSITION_OF_ENTITY_BONE(veh, boneindex);
				if (posbone.x != 0)
				{
					Object tire1 = OBJECT::CREATE_OBJECT(rage::joaat("prop_tree_fallen_01"), pos, globals::in_multiplayer(), 0, 0);
					ENTITY::ATTACH_ENTITY_TO_ENTITY(tire1, veh, boneindex, Vector3(-1.0, 0, 0.0), Vector3(0, 0, 0), 0, true, false, false, 1, 1, 0);
					tasks::entity_never_delete(tire1);
				}return;
			}
			if (type == 3)
			{
				Vector3 pos = ENTITY::GET_ENTITY_COORDS(veh, 0);
				pos.z = pos.z + 10.f;
				tasks::request_model("lts_prop_lts_ramp_01"_joaat);
				Object ramp = OBJECT::CREATE_OBJECT("lts_prop_lts_ramp_01"_joaat, pos, globals::in_multiplayer(), 0, 0);
				ENTITY::ATTACH_ENTITY_TO_ENTITY(ramp, veh, 0, Vector3(0, tasks::get_model_length(ENTITY::GET_ENTITY_MODEL(veh)) + 2, -0.4), Vector3(14.00f, 0, 180.f), 0, 0, true, 0, 2, 1, false);
				return;
			}
			if (type == 4)
			{
				Vector3 pos = ENTITY::GET_ENTITY_COORDS(veh, 0);
				pos.z = pos.z + 10.f;
				tasks::request_model("lts_prop_lts_ramp_01"_joaat);
				Object ramp = OBJECT::CREATE_OBJECT("lts_prop_lts_ramp_01"_joaat, pos, globals::in_multiplayer(), 0, 0);
				ENTITY::ATTACH_ENTITY_TO_ENTITY(ramp, veh, 0, Vector3(0, -tasks::get_model_length(ENTITY::GET_ENTITY_MODEL(veh)) - 2, -0.4), Vector3(14.00f, 0, 0.f), 0, 0, true, 0, 2, 1, false);
				return;
			}
		}
	}
	void tasks::clear_vehicle_attachments(Vehicle veh,bool self) {
		{
			if (self) {
				for (auto entity : tasks::get_world_entities(true, true, true))
				{
					if (globals::h_local_vehicle(true)) {
						if (ENTITY::IS_ENTITY_ATTACHED_TO_ENTITY(entity, globals::h_local_vehicle(true))) {
							if (tasks::request_control(entity))
								ENTITY::DETACH_ENTITY(entity, 0, 1);
						}
					}
					else {
						if (ENTITY::IS_ENTITY_ATTACHED_TO_ENTITY(entity, globals::h_local_ped())) {
							if (tasks::request_control(entity))
								ENTITY::DETACH_ENTITY(entity, 0, 1);
						}
					}
				}
			}
			else {
				for (auto entity : tasks::get_world_entities(true, true, true))
				{
					if (ENTITY::IS_ENTITY_A_PED(entity))
					{
						if (!PED::IS_PED_SITTING_IN_VEHICLE(entity, veh))
						{
							tasks::delete_entity(entity);
						}
					}
					else
					{
						tasks::delete_entity(entity);
					}
				}
			}
		}
	}
	void tasks::slip_vehicle(Vehicle veh) {
		Hash hassh = ENTITY::GET_ENTITY_MODEL(veh);
		if (!VEHICLE::IS_THIS_MODEL_A_BOAT(hassh) && !VEHICLE::IS_THIS_MODEL_A_PLANE(hassh))
			FIRE::ADD_EXPLOSION(ENTITY::GET_ENTITY_COORDS(veh, 0),
				67, 1.0f, false, true, 0.0f, true);
	}
	void tasks::spawn_money(int amount, Vector3 pos) {  ///*THANK YOU KING LOKO/// 
		request_model("s_f_y_hooker_02"_joaat);
		pos.z = pos.z + 3;
		Ped ped_money = PED::CREATE_PED(26, "s_f_y_hooker_02"_joaat, pos, 0.0f, globals::in_multiplayer(), 0);
		PED::SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(ped_money, true);
		ENTITY::SET_ENTITY_VISIBLE(ped_money, 0, 0);
		PED::SET_PED_MONEY(ped_money, amount);
		TASK::CLEAR_PED_TASKS_IMMEDIATELY(ped_money);
		TASK::CLEAR_PED_TASKS(ped_money);
		TASK::CLEAR_PED_SECONDARY_TASK(ped_money);
		PED::SET_PED_MONEY(ped_money, amount);
		FIRE::ADD_OWNED_EXPLOSION(globals::h_local_ped(), pos, 18, 1, 0, 1, 0);
		script::get_current()->yield(200ms);
		ENTITY::SET_ENTITY_AS_MISSION_ENTITY(ped_money, 0, 0);
		ENTITY::DELETE_ENTITY(&ped_money);
		script::get_current()->yield(2000ms);

	}
	void tasks::request_model(u32 hash) {
		if (STREAMING::HAS_MODEL_LOADED(hash)) {
			return;
		}

		while (!STREAMING::HAS_MODEL_LOADED(hash)) {
			STREAMING::REQUEST_MODEL(hash);
			script::get_current()->yield();
		}
	}
	bool tasks::request_control(Entity script_index, int timeout) {
		if (NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(script_index))
			return true;
		for (int32_t i{}; !NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(script_index) && !NETWORK::NETWORK_REQUEST_CONTROL_OF_NETWORK_ID(script_index) && i != timeout; ++i) {
			NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(script_index);
			NETWORK::NETWORK_HAS_CONTROL_OF_NETWORK_ID(script_index);
			script::get_current()->yield(1ms);
		}
		if (!NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(script_index))
			return false;
		NETWORK::SET_NETWORK_ID_CAN_MIGRATE(NETWORK::NETWORK_GET_NETWORK_ID_FROM_ENTITY(script_index), true);
		return true;
	}
	std::string batch_weapons[]{
		xorstr_("weapon_pumpshotgun"),
		xorstr_("weapon_pumpshotgun_mk2"),
		xorstr_("weapon_sawnoffshotgun"),
		xorstr_("weapon_assaultshotgun"),
		xorstr_("weapon_bullpupshotgun"),
		xorstr_("weapon_heavyshotgun"),
		xorstr_("weapon_dbshotgun"),
		xorstr_("weapon_autoshotgun"),
		xorstr_("weapon_combatshotgun")
	};
	int tasks::get_weapon_type(Hash hash) {
		for (size_t i = 0; i < sizeof(batch_weapons) / sizeof(batch_weapons[0]); i++)
		{
			if (hash == rage::joaat(batch_weapons[i]))
				return 1;
		}
		return 0;
	}
	bool tasks::is_ped_shooting(Ped id) {
		Vector3 coords = ENTITY::GET_ENTITY_COORDS(id, 1);
		return PED::IS_PED_SHOOTING_IN_AREA(id, coords, coords, true, true);
	}

	bool tasks::is_player_shooting(Player id) {
		return tasks::is_ped_shooting(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(id));
	}
	Vehicle tasks::spawn_vehicle_locally(u32 hash) {
		if (!STREAMING::IS_MODEL_VALID(hash)) {
			return 0;
		}
		tasks::request_model(hash);
		float forward = 5.f;
		Vector3 coords = ENTITY::GET_ENTITY_COORDS(globals::h_local_ped(), false);
		float heading = ENTITY::GET_ENTITY_HEADING(globals::h_local_ped());
		float x = forward * sin(mathfloat::get()->dtr(heading)) * -1.f;
		float y = forward * cos(mathfloat::get()->dtr(heading));
		float speed = ENTITY::GET_ENTITY_SPEED(globals::h_local_ped());
		
		if ("spawner_delete_last"_tf->m_value.toggle) {
			if (auto Entity = PED::GET_VEHICLE_PED_IS_IN(globals::h_local_ped(), true); Entity) {
				tasks::delete_entity(Entity);
			}
		}

		Vehicle the_vehicle = VEHICLE::CREATE_VEHICLE(hash, script_utility::get()->sponner_cam_running == true ? script_utility::get()->sponner_spawn_entity_pos :
		Vector3(coords.x + x, coords.y + y, coords.z), heading, globals::in_multiplayer(), false, false);

		if ("spawner_fade"_tf->m_value.toggle) {
			NETWORK::NETWORK_FADE_IN_ENTITY(the_vehicle, true, false);
		}

		i32 net_id = NETWORK::VEH_TO_NET(the_vehicle);
		NETWORK::SET_NETWORK_ID_EXISTS_ON_ALL_MACHINES(net_id, true);

		if ("spawner_add_blip"_tf->m_value.toggle) {
			Blip blip = HUD::ADD_BLIP_FOR_ENTITY(the_vehicle);
			HUD::SET_BLIP_SPRITE(blip, 227);
			HUD::SET_BLIP_DISPLAY(blip, 8);
			HUD::SET_BLIP_CATEGORY(blip, 4);
		}

		if ("spawner_in_vehicle"_tf->m_value.toggle  && !script_utility::get()->sponner_cam_running) {
			PED::SET_PED_INTO_VEHICLE(globals::h_local_ped(), the_vehicle, -1);
			VEHICLE::SET_VEHICLE_ENGINE_ON(the_vehicle, true, true, false);
			VEHICLE::SET_VEHICLE_FORWARD_SPEED(the_vehicle, speed);
		}

		if ("spawner_invincible"_tf->m_value.toggle) {
			ENTITY::SET_ENTITY_INVINCIBLE(the_vehicle, true);
			ENTITY::SET_ENTITY_PROOFS(the_vehicle, true, true, true, true, true, true, true, true);
			VEHICLE::SET_VEHICLE_CAN_BE_VISIBLY_DAMAGED(the_vehicle, false);
			VEHICLE::SET_VEHICLE_ENGINE_ON(the_vehicle, true, true, true);
		}

		if ("spawner_gifted"_tf->m_value.toggle) {
			if (tasks::request_control(the_vehicle))
				tasks::gift_vehicle(the_vehicle, globals::player_id);
		}

		if ("spawner_notification"_tf->m_value.toggle) {
			notify::send("Spawner", std::format("Spawned {}", HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(hash))));
		}

		if ("spawner_maxed_out"_tf->m_value.toggle) {
			tasks::upgrade_vehicle(the_vehicle);
		}

		if (ENTITY::IS_ENTITY_VISIBLE_TO_SCRIPT(the_vehicle)) {
			float speed = ENTITY::GET_ENTITY_SPEED(the_vehicle);
			VEHICLE::SET_VEHICLE_FORWARD_SPEED(the_vehicle, speed);
			VEHICLE::SET_VEHICLE_ENGINE_ON(the_vehicle, TRUE, TRUE, TRUE);
			DECORATOR::DECOR_SET_INT(the_vehicle, "MPBitset", (1 << 10));
			return the_vehicle;
		}
		return 0;
	}
	Object tasks::spawn_object_locally(u32 hash) {
		if (!STREAMING::IS_MODEL_VALID(hash)) {
			return 0;
		}
		tasks::request_model(hash);

		float forward = 5.f;
		Vector3 coords = ENTITY::GET_ENTITY_COORDS(globals::h_local_ped(), false);
		float heading = ENTITY::GET_ENTITY_HEADING(globals::h_local_ped());
		float x = forward * sin(mathfloat::get()->dtr(heading)) * -1.f;
		float y = forward * cos(mathfloat::get()->dtr(heading));


		Object The_Object = OBJECT::CREATE_OBJECT(hash, script_utility::get()->sponner_cam_running == true ? script_utility::get()->sponner_spawn_entity_pos :
			Vector3(coords.x + x, coords.y + y, coords.z), globals::in_multiplayer(), false, false);
		return The_Object;
		return 0;
	}
	Vehicle tasks::spawn_ped_locally(u32 hash) {
		if (!STREAMING::IS_MODEL_VALID(hash)) {
			return 0;
		}
		tasks::request_model(hash);

		float forward = 5.f;
		Vector3 coords = ENTITY::GET_ENTITY_COORDS(globals::h_local_ped(), false);
		float heading = ENTITY::GET_ENTITY_HEADING(globals::h_local_ped());
		float x = forward * sin(mathfloat::get()->dtr(heading)) * -1.f;
		float y = forward * cos(mathfloat::get()->dtr(heading));


		Vehicle the_vehicle = PED::CREATE_PED(26, hash, script_utility::get()->sponner_cam_running == true ? script_utility::get()->sponner_spawn_entity_pos :
			Vector3(coords.x + x, coords.y + y, coords.z), heading, globals::in_multiplayer(), false);
		return the_vehicle;
	}
	const char* stripper_car_dict[] = { "mini@prostitutes@sexnorm_veh" ,"mini@prostitutes@sexnorm_veh" };
	const char* stripper_car_anim[] = { "bj_loop_prostitute" ,"sex_loop_prostitute" };
	const char* stripper_car_hookers[3] = {
		"s_f_y_hooker_01", "s_f_y_hooker_02","s_f_y_hooker_03"
	};
	void tasks::stripper_car(int i, int type)
	{
		if (i)
		{
			Hash model = rage::joaat(stripper_car_hookers[MISC::GET_RANDOM_INT_IN_RANGE(0, 2)]);
			while (!STREAMING::HAS_MODEL_LOADED(model))
			{
				STREAMING::REQUEST_MODEL(model);
				STREAMING::REQUEST_ANIM_DICT(stripper_car_dict[type]);
				script::get_current()->yield();
			}
			Ped ped = PED::CREATE_PED_INSIDE_VEHICLE(i, 26, model, eSeatPosition::SF_FrontPassengerSide, true, true);
			ENTITY::SET_ENTITY_INVINCIBLE(ped, true);
			TASK::TASK_SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(ped, true);
			ENTITY::SET_ENTITY_COLLISION(ped, false, false);
			tasks::play_animation_tick(ped, stripper_car_dict[type], stripper_car_anim[type], 1);
			STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(model);
		}
	}
	void tasks::teleport_local_ped_to_pos(int type, int ped, Vector3 pos, int ignoreent) {
		bool in_vehicle = PED::GET_VEHICLE_PED_IS_USING(ped);
		if (type == 0) // directly_to_pos
		{
			if (in_vehicle)
			{
				ped = PED::GET_VEHICLE_PED_IS_USING(ped);
			}
			if (ped == globals::h_local_ped())
			{
				tasks::teleport_animation(true);
			}
			ENTITY::SET_ENTITY_COORDS(ped, pos, false, true, true, false);
			if (ped == globals::h_local_ped())
			{
				tasks::teleport_animation(false);
			}
			return;
		}
		if (type == 1) // nearby player
		{
			if (in_vehicle)
			{
				ped = PED::GET_VEHICLE_PED_IS_USING(ped);
			}
			int random = MISC::GET_RANDOM_INT_IN_RANGE(0, 360);
			Vector3 res = vectors::get()->get_360_iterator_vec_around_coord(pos, 60, 0, random, 360);
			Vector3 result = vectors::get()->get_ground_coordinates(Vector2(res.x, res.y));
			ENTITY::SET_ENTITY_COORDS(ped, result, false, true, true, false);
			return;
		}
		if (type == 2) // closed vehicle
		{
			int entity = tasks::get()->get_closest_vehicle(pos, std::vector<int>(ped));
			ENTITY::SET_ENTITY_COORDS(ped, ENTITY::GET_ENTITY_COORDS(entity, 0), false, true, true, false);

			PED::SET_PED_INTO_VEHICLE(ped, entity, -1);
			return;
		}
		if (type == 3) // closed ped
		{
			int entity = tasks::get()->get_closest_ped(pos, std::vector<int>(ignoreent));
			ENTITY::SET_ENTITY_COORDS(ped, ENTITY::GET_ENTITY_COORDS(entity, 0), false, true, true, false);
			return;
		}
		if (type == 4) // skydrive ped
		{
			WEAPON::GIVE_DELAYED_WEAPON_TO_PED(globals::h_local_ped(), "gadget_parachute"_joaat, 1, true);
			int random = MISC::GET_RANDOM_INT_IN_RANGE(0, 360);
			int sky = MISC::GET_RANDOM_INT_IN_RANGE(400, 500);
			Vector3 res = vectors::get()->get_360_iterator_vec_around_coord(pos, 60, sky, random, 360);
			ENTITY::SET_ENTITY_COORDS(ped, res, false, true, true, false);
			TASK::TASK_SKY_DIVE(ped, true);
			return;
		}
		if (type == 5) // parachute ped
		{
			WEAPON::GIVE_DELAYED_WEAPON_TO_PED(globals::h_local_ped(), "gadget_parachute"_joaat, 1, true);
			int random = MISC::GET_RANDOM_INT_IN_RANGE(0, 360);
			int sky = MISC::GET_RANDOM_INT_IN_RANGE(400, 500);
			Vector3 res = vectors::get()->get_360_iterator_vec_around_coord(pos, 60, sky, random, 360);
			ENTITY::SET_ENTITY_COORDS(ped, res, false, true, true, false);
			TASK::TASK_SKY_DIVE(ped, true);
			TASK::TASK_PARACHUTE(ped, true, true);
			return;
		}
	}
	void create_vehicle_n_delete(Hash hash) {
		tasks::request_model(hash);
		Vector3 pos = globals::h_local_ped_pos();
		pos.z -= 50.f;
		Vehicle veh = VEHICLE::CREATE_VEHICLE(hash, pos, 0, globals::in_multiplayer(), 0, 0);
		tasks::delete_entity(veh);
	}
	void tasks::set_vehicle_weapon(Hash hash, int offset1, int offset2) {
		auto ped_factory = *reinterpret_cast<std::add_pointer_t<std::uint64_t>>(insight::pointers::get()->g_ped_factory);
		if (!ped_factory) return;
		auto player_ped = *reinterpret_cast<std::add_pointer_t<std::uint64_t>>(ped_factory + 0x8);
		if (!player_ped) return;
		auto vehicle_fac = *reinterpret_cast<std::add_pointer_t<std::uint64_t>>(player_ped + 0xD10);
		if (!vehicle_fac) return;
		auto handling = *reinterpret_cast<std::add_pointer_t<std::uint64_t>>(vehicle_fac + 0x918);
		if (!handling) return;
		auto ptr1 = *reinterpret_cast<std::add_pointer_t<std::uint64_t>>(handling + 0x158);
		if (!ptr1) return;
		auto ptr2 = *reinterpret_cast<std::add_pointer_t<std::uint64_t>>(ptr1 + offset1);
		*reinterpret_cast<std::add_pointer_t<std::uint32_t>>(ptr2 + offset2) = hash;
		//shitty gta moment
		if (hash == 3003147322 || 2182329506) {
			create_vehicle_n_delete("CERBERUS3"_joaat);
		}
	}
	Hash tasks::get_vehicle_weapon(int offset1, int offset2) {
		auto ped_factory = *reinterpret_cast<std::add_pointer_t<std::uint64_t>>(insight::pointers::get()->g_ped_factory);
		if (!ped_factory) return 0 ;
		auto player_ped = *reinterpret_cast<std::add_pointer_t<std::uint64_t>>(ped_factory + 0x8);
		if (!player_ped) return 0;
		auto vehicle_fac = *reinterpret_cast<std::add_pointer_t<std::uint64_t>>(player_ped + 0xD10);
		if (!vehicle_fac) return 0;
		auto handling = *reinterpret_cast<std::add_pointer_t<std::uint64_t>>(vehicle_fac + 0x918);
		if (!handling) return 0;
		auto ptr1 = *reinterpret_cast<std::add_pointer_t<std::uint64_t>>(handling + 0x158);
		if (!ptr1) return 0;
		auto ptr2 = *reinterpret_cast<std::add_pointer_t<std::uint64_t>>(ptr1 + offset1);
		return *reinterpret_cast<std::add_pointer_t<std::uint32_t>>(ptr2 + offset2);
	}
	Vector3 last_waypoint_pos{};
	Vehicle chopper_e;
	Ped chopper_ped;
	void tasks::heli_chauffeur(float maxspeed,int flag,float max_height, float min_height,float slow_down_distance,bool raple) {
		if (raple) {
			if (PED::GET_VEHICLE_PED_IS_USING(globals::h_local_ped()) == chopper_e) {
				TASK::TASK_RAPPEL_FROM_HELI(globals::h_local_ped(), 0);
				return;
			}		
		}
		else {
			if (HUD::IS_WAYPOINT_ACTIVE()) {
				last_waypoint_pos = vectors::get()->get_waypoint_coordinates();
				if (ENTITY::DOES_ENTITY_EXIST(chopper_e)) {
					ENTITY::DELETE_ENTITY(&chopper_e);
					chopper_e = 0;
				}
				if (!ENTITY::DOES_ENTITY_EXIST(chopper_e)) {
					Hash chopper = "maverick"_joaat;
					tasks::request_model(chopper);
					chopper_e = VEHICLE::CREATE_VEHICLE(chopper,
						{ globals::h_local_ped_pos().x,globals::h_local_ped_pos().y,globals::h_local_ped_pos().z + 50 },
						ENTITY::GET_ENTITY_HEADING(globals::h_local_ped()), globals::in_multiplayer(), 0, 0);
					tasks::request_model("s_m_y_airworker"_joaat);
					chopper_ped = PED::CREATE_PED_INSIDE_VEHICLE(chopper_e, 26,
						"s_m_y_airworker"_joaat, -1, globals::in_multiplayer(), 0);
					VEHICLE::SET_VEHICLE_ENGINE_ON(chopper_e, 1, 1, 0);

					PED::SET_PED_INTO_VEHICLE(globals::h_local_ped(), chopper_e, 2);
					ENTITY::APPLY_FORCE_TO_ENTITY(chopper_e, 3, Vector3(0.0f, 0.f, 50.f), Vector3(0.0f, 0.f, 0.f), 0, 0, 1, 1, 0, 1);
					TASK::TASK_HELI_MISSION(chopper_ped, chopper_e, 0, 0, last_waypoint_pos, flag, maxspeed, -1.0, -1.0,
						max_height, min_height, slow_down_distance, 0);
				}
				else {
					if (PED::GET_VEHICLE_PED_IS_USING(globals::h_local_ped()) != chopper_e) {
						ENTITY::DELETE_ENTITY(&chopper_e);
					}
				}
			}
			else {
				if (PED::GET_VEHICLE_PED_IS_USING(globals::h_local_ped()) == chopper_e) {
					TASK::TASK_HELI_MISSION(chopper_ped, chopper_e, 0, 0, last_waypoint_pos, flag, maxspeed, -1.0, -1.0,
						max_height, min_height, slow_down_distance, 0);
					notify::send("Chauffeur", "Chauffeur settings updated.");
				}
				else
					notify::send("Chauffeur", "Please set waypoint before use.");
				return;

			}
		}
	}
	inline Vector3 get_v3_vehicle_scale(auto offset)
	{
		return Vector3(*reinterpret_cast<float*>(offset), *reinterpret_cast<float*>(offset + 0x4),
			*reinterpret_cast<float*>(offset + 0x8));
	}
	inline void set_v3_vehicle_scale(auto offset, Vector3 vec)
	{
		*reinterpret_cast<float*>(offset) = vec.x;
		*reinterpret_cast<float*>(offset + 0x4) = vec.y;
		*reinterpret_cast<float*>(offset + 0x8) = vec.z;
	}
	void tasks::set_vehicle_scale(Vehicle veh, float scaleMultiplier) //Orignally by ChaosMod. 
	{
		DWORD64  baseAddr = (DWORD64)pointers::get()->g_handle_to_pointer(veh);

		if (!baseAddr)
		{
			return;
		}
		
		auto passengerMatrixAddress = baseAddr + 0x60;
		Vector3 passengerForwardVec = get_v3_vehicle_scale(passengerMatrixAddress + 0x00);
		Vector3 passengerRightVec = get_v3_vehicle_scale(passengerMatrixAddress + 0x10);
		Vector3 passengerUpVec = get_v3_vehicle_scale(passengerMatrixAddress + 0x20);

		auto vehicleMatrixAddress = *reinterpret_cast<uintptr_t*>(baseAddr + 0x30) + 0x20;
		Vector3 vehicleForwardVec = get_v3_vehicle_scale(vehicleMatrixAddress + 0x00);
		Vector3 vehicleRightVec = get_v3_vehicle_scale(vehicleMatrixAddress + 0x10);
		Vector3 vehicleUpVec = get_v3_vehicle_scale(vehicleMatrixAddress + 0x20);

		set_v3_vehicle_scale(passengerMatrixAddress + 0x00, passengerForwardVec * scaleMultiplier);
		set_v3_vehicle_scale(passengerMatrixAddress + 0x10, passengerRightVec * scaleMultiplier);
		set_v3_vehicle_scale(passengerMatrixAddress + 0x20, passengerUpVec * scaleMultiplier);

		set_v3_vehicle_scale(vehicleMatrixAddress + 0x00, vehicleForwardVec * scaleMultiplier);
		set_v3_vehicle_scale(vehicleMatrixAddress + 0x10, vehicleRightVec * scaleMultiplier);
		set_v3_vehicle_scale(vehicleMatrixAddress + 0x20, vehicleUpVec * scaleMultiplier);
	}
	
	void tasks::spawn_guard(Hash hash,std::string name, bodyguard_dat g) {
		if (!STREAMING::IS_MODEL_VALID(hash)) {
			return;
		}
		LOG(INFO) << hash;
		tasks::request_model(hash);
		Ped ped = PED::CREATE_PED(26, hash, globals::h_local_ped_pos(), 0, globals::in_multiplayer(), 0);
		PED::SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(ped, 1);
		ENTITY::SET_ENTITY_MAX_HEALTH(ped, g.max_health);
		PED::SET_PED_ARMOUR(ped, g.armor);
		ENTITY::SET_ENTITY_HEALTH(ped,g.health,0);
		features_utility::get()->m_bodyguards.push_back({ name, ped ,g.godmode,100416529,g.autokill_when_near,g.autokill_when_near_range,
		g.keep_guards_near,g.keep_guards_near_range ,timer(std::chrono::milliseconds(10000)),1,timer(std::chrono::milliseconds(10000))
		,0,0,0,g.attack_player,g.freeze,g.combat_ability,g.accuracy});
	}
	void tasks::tick_bodyguards() {
		for (int i = 0; i < features_utility::get()->m_bodyguards.size(); i++) {
			bodyguard_dat& guard = features_utility::get()->m_bodyguards[i];
			if (ENTITY::DOES_ENTITY_EXIST(guard.ent) && !ENTITY::IS_ENTITY_DEAD(guard.ent, 0)) {
				guard.getting_in_timer.setdelay(std::chrono::milliseconds(1000));
				if (guard.getting_in_timer.update()) {
					if (globals::h_local_vehicle(true) && !PED::IS_PED_IN_ANY_VEHICLE(guard.ent, 1)) {
						int free_seat = -10;
						for (int i = 0; i < 10; i++) {
							if (VEHICLE::IS_VEHICLE_SEAT_FREE(globals::h_local_vehicle(true), i, 1)) {
								free_seat = i;
							}
						}
						if (free_seat != -10)
							TASK::TASK_ENTER_VEHICLE(guard.ent, globals::h_local_vehicle(true), 99.f, free_seat, 99.f, 3, 0);
					}
					else
					{
						if (PED::IS_PED_IN_ANY_VEHICLE(guard.ent, 1) && !globals::h_local_vehicle(true)) {
							TASK::TASK_LEAVE_ANY_VEHICLE(guard.ent, 0, 0);
						}
					}
				}
				if (guard.godmode) {
					ENTITY::SET_ENTITY_INVINCIBLE(guard.ent, 1);
				}
				else {
					ENTITY::SET_ENTITY_INVINCIBLE(guard.ent, 0);
				}
				if (guard.freeze) {
					ENTITY::FREEZE_ENTITY_POSITION(guard.ent, 1);
				}
				else {
					ENTITY::FREEZE_ENTITY_POSITION(guard.ent, 0);
				}
				PED::SET_PED_COMBAT_ABILITY(guard.ent, guard.combat_ability);

				PED::SET_PED_ACCURACY(guard.ent, guard.accuracy);

				if (WEAPON::HAS_PED_GOT_WEAPON(guard.ent, guard.weapon, 0)) {
					WEAPON::SET_CURRENT_PED_WEAPON(guard.ent, guard.weapon, 1);
					WEAPON::SET_PED_INFINITE_AMMO(guard.ent, guard.weapon, guard.weapon);
				}
				else {
					WEAPON::GIVE_DELAYED_WEAPON_TO_PED(guard.ent, guard.weapon, 999, 1);
				}
				if (guard.keep_guards_near) {
					guard.keep_guards_near_range_timer.setdelay(std::chrono::milliseconds(1000ms));
					if (guard.keep_guards_near_range_timer.update()) {
						if (tasks::get_distance_between(globals::h_local_ped(), guard.ent) > guard.keep_guards_near_range) {
							TASK::TASK_GO_TO_ENTITY(guard.ent, globals::h_local_ped(), -1, guard.keep_guards_near_range, 100, 1073741824, 0);

						}
						if (tasks::get_distance_between(globals::h_local_ped(), guard.ent) > guard.keep_guards_near_range + 50.f) {
							Vector3 pos = vectors::get()->get_front_camera_coordinates_local(-10.f);
							ENTITY::SET_ENTITY_COORDS_NO_OFFSET(guard.ent, vectors::get()->get_ground_coordinates({ pos.x , pos.y }), 0, 0, 0);
						}
					}
				}
				std::vector<Entity> targetting_entities;
				if (guard.aim_to_kill) {
					if (input::get()->is_input_aim_pressed())
					if (auto enti = tasks::create_cast_entites()) {
						if (ENTITY::IS_ENTITY_A_PED(enti))
						targetting_entities.push_back(enti);
					}
				}
				for (auto ped : tasks::get_world_entities(0, true, 0)) {
					bool break_it = false;
					for (int b = 0; b < features_utility::get()->m_bodyguards.size(); b++) {
						if (features_utility::get()->m_bodyguards[b].ent == ped) {
							break_it = true;
							break;
						}
					}
					if (!break_it) {
						if (guard.ent != ped) {
							if (guard.autokill_when_near) {
								if (tasks::get_distance_between(globals::h_local_ped(), ped) < guard.autokill_when_near_range) {
									if (!ENTITY::IS_ENTITY_DEAD(ped, 0)) {
										if (guard.attack_player) {
											if (!PED::IS_PED_A_PLAYER(ped)) {
												targetting_entities.push_back(ped);
											}
										}
										else {
											targetting_entities.push_back(ped);
										}
									}
								}
							}
							if (PED::IS_PED_IN_COMBAT(ped, globals::h_local_ped())) {
								if (!ENTITY::IS_ENTITY_DEAD(ped, 0)) {
									if (guard.attack_player) {
										if (!PED::IS_PED_A_PLAYER(ped)) {
											targetting_entities.push_back(ped);
										}
									}
									else {
										targetting_entities.push_back(ped);
									}
								}
							}if (ENTITY::HAS_ENTITY_BEEN_DAMAGED_BY_ENTITY(ped, globals::h_local_ped(),1)) {
								if (!ENTITY::IS_ENTITY_DEAD(ped, 0)) {
									if (guard.attack_player) {
										if (!PED::IS_PED_A_PLAYER(ped)) {
											targetting_entities.push_back(ped);
										}
									}
									else {
										targetting_entities.push_back(ped);
									}
								}
							}
						}
					}
				}
				int target_size = targetting_entities.size();
				if (target_size > 2) {
					int getting_random_ped = MISC::GET_RANDOM_INT_IN_RANGE(0, target_size);
					if (PED::IS_PED_IN_ANY_VEHICLE(guard.ent, 1)) {
						TASK::TASK_COMBAT_PED(guard.ent, targetting_entities[getting_random_ped], 0, 16);
					}
					else {
						if (!WEAPON::IS_PED_ARMED(guard.ent, 1))
							TASK::TASK_SHOOT_AT_ENTITY(guard.ent, targetting_entities[getting_random_ped], 5000, "FIRING_PATTERN_FULL_AUTO"_joaat);
						else
							TASK::TASK_COMBAT_PED(guard.ent, targetting_entities[getting_random_ped], 0, 16);
					}
				}
				else if (target_size){
					if (PED::IS_PED_IN_ANY_VEHICLE(guard.ent, 1) && !globals::h_local_vehicle(true)) {
						TASK::TASK_COMBAT_PED(guard.ent, targetting_entities[0], 0, 16);
					}
					else {
						if (!WEAPON::IS_PED_ARMED(guard.ent, 1))
							TASK::TASK_SHOOT_AT_ENTITY(guard.ent, targetting_entities[0], 5000, "FIRING_PATTERN_FULL_AUTO"_joaat);
						else
							TASK::TASK_COMBAT_PED(guard.ent, targetting_entities[0], 0, 16);
					}
					
				}
			} else 
			{ features_utility::get()->m_bodyguards.erase(features_utility::get()->m_bodyguards.begin() + i); }
		}
	}
}
	