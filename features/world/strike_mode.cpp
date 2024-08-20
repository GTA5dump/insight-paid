

#include "cheat/features/features.hpp"
#include "cheat/features/globals.hpp"
#include "cheat/features/tasks.hpp"
#include "cheat/features/features/features_utility.hpp"
#include "util/input/input.hpp"
#include "util/math/math.hpp"


namespace insight {
	Vector3 FUC_AIRSTIKE_FROM;
	Vector3 FUC_AIRSTIKE_AT;
	int	 AIRSTRIKE_MOD_STRIKE_DAMAGE = 100;
	bool AIRSTRIKE_MOD_STRIKE_VISIBLE = true;
	int AIRSTRIKE_MOD_SHOOT_SPEED = 100;
}
namespace insight {
	void FUC_AIRSTIKE(int VEHICLE , Hash strike_type,bool audio,int speed) {
		FUC_AIRSTIKE_AT = ENTITY::GET_ENTITY_COORDS(VEHICLE, 1);
		MISC::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(FUC_AIRSTIKE_FROM, FUC_AIRSTIKE_AT, AIRSTRIKE_MOD_STRIKE_DAMAGE, false, strike_type, NULL, audio,
		AIRSTRIKE_MOD_STRIKE_VISIBLE, speed);
	}
	static timer Local_Misc_Airstike_Modd_TIMER(0ms);
	void world::strike_mode(toggle_int_feature* feature, bool& value, int& value2) {
		if (!value) {
			return;
		}
		if ("airstike_mode_speed"_tf->m_value.integer == 0)
			AIRSTRIKE_MOD_SHOOT_SPEED = 100;
		else   if ("airstike_mode_speed"_tf->m_value.integer == 1)
			AIRSTRIKE_MOD_SHOOT_SPEED = 500;
		else   if ("airstike_mode_speed"_tf->m_value.integer == 2)
			AIRSTRIKE_MOD_SHOOT_SPEED = 1000;

		Local_Misc_Airstike_Modd_TIMER.setdelay(std::chrono::milliseconds("airstike_mode_delay"_if->m_value.integer));
		if (Local_Misc_Airstike_Modd_TIMER.update()) {
			if (!WEAPON::HAS_PED_GOT_WEAPON(globals::h_local_ped(), features_utility::get()->airstrike_Hash, 0)) {
				WEAPON::GIVE_DELAYED_WEAPON_TO_PED(globals::h_local_ped(), features_utility::get()->airstrike_Hash, 1, 0);
			}
			int Any_State_ = MISC::GET_RANDOM_INT_IN_RANGE(0, 1);
			if (value2 == 0) {
				if (Any_State_ == 0) {//SKY 				
					FUC_AIRSTIKE_FROM = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(globals::h_local_ped(), Vector3(MISC::GET_RANDOM_FLOAT_IN_RANGE(-100, 100), MISC::GET_RANDOM_FLOAT_IN_RANGE(-100, 100), MISC::GET_RANDOM_FLOAT_IN_RANGE(50, 100)));
					//rage::joaat(list::Krox_Projectile_List_F[list::AIRSTRIKE_MOD_SHOOT_PROJECTILES]) ;

				}
				else if (Any_State_ == 1) {
					FUC_AIRSTIKE_FROM = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(globals::h_local_ped(), Vector3(-MISC::GET_RANDOM_FLOAT_IN_RANGE(-100, 100), -MISC::GET_RANDOM_FLOAT_IN_RANGE(-100, 100), MISC::GET_RANDOM_FLOAT_IN_RANGE(50, 100)));
				}
			}
			else if (value2 == 1) { //GROUND
				if (Any_State_ == 0) {
					FUC_AIRSTIKE_FROM = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(globals::h_local_ped(), Vector3(MISC::GET_RANDOM_FLOAT_IN_RANGE(-100, 100), MISC::GET_RANDOM_FLOAT_IN_RANGE(-100, 100), MISC::GET_RANDOM_FLOAT_IN_RANGE(0, 10)));

				}
				else if (Any_State_ == 1) {
					FUC_AIRSTIKE_FROM = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(globals::h_local_ped(), Vector3(-MISC::GET_RANDOM_FLOAT_IN_RANGE(-100, 100), -MISC::GET_RANDOM_FLOAT_IN_RANGE(-100, 100), MISC::GET_RANDOM_FLOAT_IN_RANGE(0, 10)));
				}
			}

			if ("airstike_mode_shoot_at"_if->m_value.integer == 0) {//AT CARS
				for (auto entity : tasks::get_world_entities(true, false, false))
				{
					FUC_AIRSTIKE(entity, features_utility::get()->airstrike_Hash, true, AIRSTRIKE_MOD_SHOOT_SPEED);
				}
			}
			if ("airstike_mode_shoot_at"_if->m_value.integer == 1) {// AT PEDS 
				for (auto entity : tasks::get_world_entities(false, true, false)) {
					FUC_AIRSTIKE(entity, features_utility::get()->airstrike_Hash, true, AIRSTRIKE_MOD_SHOOT_SPEED);
				}
			}
			else if ("airstike_mode_shoot_at"_if->m_value.integer == 2) {// AT SKY 
 				int Any_State_2 = MISC::GET_RANDOM_INT_IN_RANGE(0, 1);
				Vector3 Coords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(globals::h_local_ped(), Vector3(0, 0, 0));
				if (Any_State_2 == 0) {
					MISC::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(FUC_AIRSTIKE_FROM, Vector3(Coords.x + MISC::GET_RANDOM_FLOAT_IN_RANGE(0, 100), Coords.y + MISC::GET_RANDOM_FLOAT_IN_RANGE(0, 100), Coords.z + MISC::GET_RANDOM_INT_IN_RANGE(50, 100)), AIRSTRIKE_MOD_STRIKE_DAMAGE, false, features_utility::get()->airstrike_Hash, NULL, true, AIRSTRIKE_MOD_STRIKE_VISIBLE, AIRSTRIKE_MOD_SHOOT_SPEED);
				}
				else if (Any_State_2 == 1) {
					MISC::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(FUC_AIRSTIKE_FROM, Vector3(Coords.x - MISC::GET_RANDOM_FLOAT_IN_RANGE(0, 100), Coords.y - MISC::GET_RANDOM_FLOAT_IN_RANGE(0, 100), Coords.z + MISC::GET_RANDOM_INT_IN_RANGE(50, 100)), AIRSTRIKE_MOD_STRIKE_DAMAGE, false, features_utility::get()->airstrike_Hash, NULL, true, AIRSTRIKE_MOD_STRIKE_VISIBLE, AIRSTRIKE_MOD_SHOOT_SPEED);
				}

			}
			else if ("airstike_mode_shoot_at"_if->m_value.integer == 3) { // AT GROUND
				int Any_State_2 = MISC::GET_RANDOM_INT_IN_RANGE(0, 1);
				Vector3 Coords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(globals::h_local_ped(), Vector3(0, 0, 0));
				if (Any_State_2 == 0)  {
					MISC::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(FUC_AIRSTIKE_FROM, Vector3(Coords.x + MISC::GET_RANDOM_FLOAT_IN_RANGE(0, 100), Coords.y + MISC::GET_RANDOM_FLOAT_IN_RANGE(0, 100), Coords.z), AIRSTRIKE_MOD_STRIKE_DAMAGE, false, features_utility::get()->airstrike_Hash, NULL, true, AIRSTRIKE_MOD_STRIKE_VISIBLE, AIRSTRIKE_MOD_SHOOT_SPEED);
				}
				else if (Any_State_2 == 1) {
					MISC::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(FUC_AIRSTIKE_FROM, Vector3(Coords.x - MISC::GET_RANDOM_FLOAT_IN_RANGE(0, 100), Coords.y - MISC::GET_RANDOM_FLOAT_IN_RANGE(0, 100), Coords.z), AIRSTRIKE_MOD_STRIKE_DAMAGE, false, features_utility::get()->airstrike_Hash, NULL,true, AIRSTRIKE_MOD_STRIKE_VISIBLE, AIRSTRIKE_MOD_SHOOT_SPEED);

				}
			}
		}

	}
}