#include "cheat/features/features.hpp"
#include "cheat/features/globals.hpp"
#include "cheat/features/tasks.hpp"
#include "util/input/input.hpp"
#include "util/math/math.hpp"
#include "cheat/features/features/features_utility.hpp"
namespace insight {
	std::vector<Object> Meteors;
	Object meteorite_shower_obj = 0;
	Hash meteorite_shower_hash = 0;
}
namespace insight {
	bool was_meteorite_shower_on = false;
	void world::meteorite_shower(toggle_int_feature* feature, bool& value, int& value2) {
		if (!value) {
			if (was_meteorite_shower_on) {
				for (int i = 0; i < Meteors.size(); i++) {
					if (ENTITY::DOES_ENTITY_EXIST(Meteors[i])) {
						tasks::delete_entity(Meteors[i]);
					}
					
				}
				Meteors.clear();
				was_meteorite_shower_on = false;
			}
			return;
		}
		was_meteorite_shower_on = true;

		if (Meteors.size() < value2) {
			meteorite_shower_obj = 0;
			Vector3 pos = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(globals::h_local_ped(), Vector3(MISC::GET_RANDOM_FLOAT_IN_RANGE(-250.f, 250.f), MISC::GET_RANDOM_FLOAT_IN_RANGE(-250.f, 250.f), 250));
			Vector3 pos2 = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(globals::h_local_ped(), Vector3(MISC::GET_RANDOM_FLOAT_IN_RANGE(-250.f, 250.f), MISC::GET_RANDOM_FLOAT_IN_RANGE(-250.f, 250.f), 0));
			if (features_utility::get()->m_meteor_world_selected == 0) {
				meteorite_shower_hash = rage::joaat(xorstr_("prop_rock_4_big"));
			}
			else if (features_utility::get()->m_meteor_world_selected == 1) {
				meteorite_shower_hash = rage::joaat(xorstr_("prop_rock_4_big2"));
			}		
			else if (features_utility::get()->m_meteor_world_selected == 2) {
				meteorite_shower_hash = rage::joaat(xorstr_("prop_asteroid_01"));
			}			
			else if (features_utility::get()->m_meteor_world_selected == 3) {
				int random = MISC::GET_RANDOM_INT_IN_RANGE(0, 2);
				if (random == 0) {
					meteorite_shower_hash = rage::joaat(xorstr_("prop_rock_4_big"));
				}
				else if (random == 1){
					meteorite_shower_hash = rage::joaat(xorstr_("prop_rock_4_big2"));
				}		
				else if (random == 2){
					meteorite_shower_hash = rage::joaat(xorstr_("prop_asteroid_01"));
				}
			}
			while (!STREAMING::HAS_MODEL_LOADED(meteorite_shower_hash)) {
				STREAMING::REQUEST_MODEL(meteorite_shower_hash);
				script::get_current()->yield();
			}
			if (STREAMING::HAS_MODEL_LOADED(meteorite_shower_hash)) {
				meteorite_shower_obj = OBJECT::CREATE_OBJECT(meteorite_shower_hash, Vector3(pos.x, pos.y, pos.z), globals::in_multiplayer(), 0, TRUE);
				Meteors.push_back(meteorite_shower_obj);
				STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(meteorite_shower_hash);
			}
			if (globals::in_multiplayer()) {
				DECORATOR::DECOR_SET_INT(meteorite_shower_obj, xorstr_("MPBitset"), 0);
				ENTITY::SET_ENTITY_SHOULD_FREEZE_WAITING_ON_COLLISION(meteorite_shower_obj, TRUE);
				auto networkId = NETWORK::OBJ_TO_NET(meteorite_shower_obj);
				if (NETWORK::NETWORK_GET_ENTITY_IS_NETWORKED(meteorite_shower_obj))
					NETWORK::SET_NETWORK_ID_EXISTS_ON_ALL_MACHINES(networkId, true);
			}
			Vector3 meteore = ENTITY::GET_ENTITY_COORDS(meteorite_shower_obj, 0);
			Vector3 results = pos2 - meteore;
			Vector3 results_Vec = ENTITY::GET_ENTITY_VELOCITY(meteorite_shower_obj);
			tasks::apply_force_to_position(meteorite_shower_obj, results, results_Vec, 9.5* "metorite_strike_speed"_FF->m_value.floating_point , 0.3);

		}
		for (size_t i = 0; i < Meteors.size(); i++) {
			if (ENTITY::DOES_ENTITY_EXIST(Meteors[i])) {
				Vector3 meteore = ENTITY::GET_ENTITY_COORDS(Meteors[i], 0);
				tasks::play_ptfx_bone_tick(Meteors[i], 0, (char*)"scr_agencyheistb", (char*)"scr_agencyheistb", (char*)"scr_agency3b_heli_expl", 1.f * "metorite_strike_fx_size"_FF->m_value.floating_point);
				if (ENTITY::GET_ENTITY_HEIGHT_ABOVE_GROUND(Meteors[i]) < 5.f) {
					if ("metorite_strike_fx_size"_FF->m_value.floating_point > 4) {
						for (auto entity : tasks::get_world_entities(true, true, false)) {
							if (tasks::get_distance_between(entity, Meteors[i]) < 100.f) {
								Vector3 force = ENTITY::GET_ENTITY_COORDS(entity,0) - ENTITY::GET_ENTITY_COORDS(Meteors[i], 0);
								if (tasks::get_control_of_entity_tick(entity))
									ENTITY::APPLY_FORCE_TO_ENTITY(entity, 3, force, { 0, 0, 0 }, 0, false, true, true, false, true);
							}
						}
					}
					ENTITY::SET_ENTITY_AS_NO_LONGER_NEEDED(&Meteors[i]);
					FIRE::ADD_EXPLOSION(meteore, 29, 100, true, true, 0, false);
					tasks::delete_entity(Meteors[i]);
				}
				else {
					FIRE::ADD_EXPLOSION(meteore, 29, 100, false, true, 0, false);
				}
			}
			else {
				auto it = std::find(Meteors.begin(), Meteors.end(), Meteors[i]);
				if (it != Meteors.end()) {
					Meteors.erase(it);
				}
			}
		}
	}
}