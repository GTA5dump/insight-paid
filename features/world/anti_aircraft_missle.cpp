

#include "cheat/features/features.hpp"
#include "cheat/features/globals.hpp"
#include "cheat/features/tasks.hpp"

#include "util/input/input.hpp"

#include "util/math/math.hpp"


namespace insight {
	int GET_FUC_AIR_DEFENSE_SYS = 0;
	void FUC_AIR_DEFENSE_SYS(int ent,int range) {
		if ((ENTITY::GET_ENTITY_HEIGHT_ABOVE_GROUND(ent) > 20) && VEHICLE::GET_IS_VEHICLE_ENGINE_RUNNING(ent) && ENTITY::HAS_COLLISION_LOADED_AROUND_ENTITY(ent) &&
			ENTITY::HAS_ENTITY_CLEAR_LOS_TO_ENTITY(globals::h_local_ped(), ent, 4294967295)) {
			if (SYSTEM::VDIST(globals::h_local_ped_pos(),ENTITY::GET_ENTITY_COORDS(ent,0)) < range) {
				Vector3 vec3 = ENTITY::GET_ENTITY_COORDS(ent, true);
				Vector3 vec3self = globals::h_local_ped_pos();
				int randomx = MISC::GET_RANDOM_INT_IN_RANGE(1, 3);
				int randomy = MISC::GET_RANDOM_INT_IN_RANGE(1, 3);
				int randomz = MISC::GET_RANDOM_INT_IN_RANGE(6, 10);
				if (ENTITY::DOES_ENTITY_EXIST(GET_FUC_AIR_DEFENSE_SYS)) {
					Vector3 veC = ENTITY::GET_ENTITY_COORDS(GET_FUC_AIR_DEFENSE_SYS, 0);			
					Vector3 results = vec3 - veC;
					if (SYSTEM::VDIST(ENTITY::GET_ENTITY_COORDS(GET_FUC_AIR_DEFENSE_SYS, 0),ENTITY::GET_ENTITY_COORDS(ent, 0)) > 5) {
						tasks::apply_force_to_position(GET_FUC_AIR_DEFENSE_SYS, results, ENTITY::GET_ENTITY_VELOCITY(GET_FUC_AIR_DEFENSE_SYS), 9.5, 0.3);
					}
					else {
						tasks::get()->delete_entity(GET_FUC_AIR_DEFENSE_SYS);
						FIRE::ADD_EXPLOSION(ENTITY::GET_ENTITY_COORDS(ent, 0), (int)eExplosionTag::EXP_TAG_SUBMARINE_BIG, 1.0f, true, true, 1.0, false);
						script::get_current()->yield(1000ms);
					}

				}
				else
				{
					Hash asset = 0xB1CA77B1;
					while (!WEAPON::HAS_WEAPON_ASSET_LOADED(asset)) {
						WEAPON::REQUEST_WEAPON_ASSET(asset, 32, 26);
						script::get_current()->yield();

					}
					MISC::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(Vector3(vec3self.x + randomx, vec3self.y + randomy, vec3self.z + randomz), Vector3(vec3.x, vec3.y, vec3.z), 100, true, asset, NULL, true, false, 5000);
					GET_FUC_AIR_DEFENSE_SYS = OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(Vector3(vec3self.x + randomx, vec3self.y + randomy, vec3self.z + randomz), 10, 2586970039, 0, 0, 1);
					if (!WEAPON::HAS_PED_GOT_WEAPON(globals::h_local_ped(), 0xB1CA77B1, 0)) {
						WEAPON::GIVE_DELAYED_WEAPON_TO_PED(globals::h_local_ped(), 0xB1CA77B1, 1, 0);
					}
				}
			}
		}
	}
}
namespace insight {
	//FUC_AIR_DEFENSE_SYS
	float anti_aircraft_missle_range = 0;
	static timer anti_aircraft_missle_timer(std::chrono::seconds(2s));
	bool anti_aircraft_missle_sphere = false;
	void world::anti_aircraft_missle(toggle_float_feature* feature, bool& value, float& value2) {
		if (!value) {
			return;
		}
		if (anti_aircraft_missle_range != value2) {
			anti_aircraft_missle_sphere = true;
			anti_aircraft_missle_range = value2;
		}
		if (anti_aircraft_missle_sphere) {
			tasks::draw_marker(eMarkerType::MarkerTypeDebugSphere, globals::h_local_ped_pos(), value2, 0, 120, 200, 100, true, true, true);
			if (anti_aircraft_missle_timer.update()) {
				anti_aircraft_missle_sphere = false;
			}
		}
		for (auto ent : tasks::get_world_entities(true, false, false)) {
			FUC_AIR_DEFENSE_SYS(ent, value2);
		}

	}
}

