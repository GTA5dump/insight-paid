



#include "cheat/features/features.hpp"
#include "cheat/features/globals.hpp"
#include "cheat/features/tasks.hpp"

#include "util/input/input.hpp"

#include "util/math/math.hpp"


namespace insight {
	struct angry_plane_data {
		Entity plane;
		Entity pilot;
	};
	std::vector <angry_plane_data> angry_planes_dat;
	const char* planes_hashes[] = { "shamal" ,"nimbus" , "velum2" ,"velum","lazer","titan","duster" };
	Entity angry_planes_pilot = 0;
	Entity angry_planes_plane = 0;
}
namespace insight {

	void world::angry_planes(toggle_int_feature* feature, bool& value, int& value2) {
		if (!value)
		{
			for (int i = 0; i < angry_planes_dat.size(); i++)
			{
				if (ENTITY::DOES_ENTITY_EXIST(angry_planes_dat[i].pilot))
					tasks::delete_entity(angry_planes_dat[i].pilot);
				if (ENTITY::DOES_ENTITY_EXIST(angry_planes_dat[i].plane))
					tasks::delete_entity(angry_planes_dat[i].plane);
			}
			return;
		}
		if (angry_planes_dat.size() < value2)
		{
			const auto pos = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(globals::h_local_ped(), Vector3(MISC::GET_RANDOM_FLOAT_IN_RANGE(0.f, 250.f), MISC::GET_RANDOM_FLOAT_IN_RANGE(0.f, 250.f), 500));
			Hash hash = rage::joaat(planes_hashes[MISC::GET_RANDOM_INT_IN_RANGE(0,6)]);
			Hash pedHash = rage::joaat("s_m_y_blackops_01");
			while (!STREAMING::HAS_MODEL_LOADED(hash) && !STREAMING::HAS_MODEL_LOADED(pedHash))
			{
				STREAMING::REQUEST_MODEL(hash);
				STREAMING::REQUEST_MODEL(pedHash);
				script::get_current()->yield();
			}			
			angry_planes_plane = VEHICLE::CREATE_VEHICLE(hash, pos, 0.f, TRUE, globals::in_multiplayer(), 0);
			VEHICLE::SET_VEHICLE_ENGINE_ON(angry_planes_plane, true, true, false);
			VEHICLE::CONTROL_LANDING_GEAR(angry_planes_plane, 3);
			angry_planes_pilot = PED::CREATE_PED_INSIDE_VEHICLE(angry_planes_plane, 26, pedHash, -1, true, true);
			angry_planes_dat.push_back(angry_plane_data(angry_planes_plane, angry_planes_pilot));
			int random = MISC::GET_RANDOM_INT_IN_RANGE(0, 360);
			TASK::TASK_PLANE_MISSION(angry_planes_pilot, angry_planes_plane, globals::h_local_vehicle(), globals::h_local_ped(), vectors::get()->get_360_iterator_vec_around_coord(globals::h_local_ped_pos(), 50, 0, random, 360), 6, 30.00, 0.f, 90.f, 0, 0, 0);
			PED::SET_PED_FIRING_PATTERN(angry_planes_pilot, 0xC6EE6B4C);			
			if (globals::in_multiplayer())
			{
				DECORATOR::DECOR_SET_INT(angry_planes_plane, xorstr_("MPBitset"), 0);
				ENTITY::SET_ENTITY_SHOULD_FREEZE_WAITING_ON_COLLISION(angry_planes_plane, TRUE);
				auto networkId = NETWORK::VEH_TO_NET(angry_planes_plane);
				if (NETWORK::NETWORK_GET_ENTITY_IS_NETWORKED(angry_planes_plane))
					NETWORK::SET_NETWORK_ID_EXISTS_ON_ALL_MACHINES(networkId, true);
				VEHICLE::SET_VEHICLE_IS_STOLEN(angry_planes_plane, FALSE);
			}

		}

		for (int i = 0; i < angry_planes_dat.size(); i++)
		{
			if (!ENTITY::DOES_ENTITY_EXIST(angry_planes_dat[i].plane))
			{
				auto it = std::find_if(angry_planes_dat.begin(), angry_planes_dat.end(), [planeEntity = angry_planes_dat[i].plane](const angry_plane_data& data) {
					return data.plane == planeEntity;
					});
		
				if (it != angry_planes_dat.end()) {
					angry_planes_dat.erase(it);
				}
			}
			if (ENTITY::IS_ENTITY_DEAD(angry_planes_dat[i].pilot,0))
			{
				ENTITY::SET_ENTITY_AS_NO_LONGER_NEEDED(&angry_planes_dat[i].pilot);
				auto it = std::find_if(angry_planes_dat.begin(), angry_planes_dat.end(), [planeEntity = angry_planes_dat[i].plane](const angry_plane_data& data) {
					return data.plane == planeEntity;
					});
		
				if (it != angry_planes_dat.end()) {
					angry_planes_dat.erase(it);
				}
			}		
			if (ENTITY::IS_ENTITY_DEAD(angry_planes_dat[i].plane,0))
			{
				ENTITY::SET_ENTITY_AS_NO_LONGER_NEEDED(&angry_planes_dat[i].plane);
				auto it = std::find_if(angry_planes_dat.begin(), angry_planes_dat.end(), [planeEntity = angry_planes_dat[i].plane](const angry_plane_data& data) {
					return data.plane == planeEntity;
					});
		
				if (it != angry_planes_dat.end()) {
					angry_planes_dat.erase(it);
				}
			}			
		}
	}
}