


#include "cheat/features/features.hpp"
#include "cheat/features/globals.hpp"
#include "cheat/features/tasks.hpp"

#include "util/input/input.hpp"

#include "util/math/math.hpp"


namespace insight {
	Vector3 MISC_MAG_FIELD_COR = { 0,0,0 };
	bool  MISC_MAG_FIELD_TOR_BOOL = false;
	static timer MISC_MAG_FIELD_TIMER(0ms);
	void MISC_MAG_FIELD_FUC(int enty, float MISC_MAG_FIELD_DISTANCE,float MISC_MAG_FIELD_FAR,float MISC_MAG_FIELD_FUNCTION_GROUND_DISTANCE,int type,int delay, bool super_mode,float force_intsty) {
		if (tasks::get()->get_distance_between(enty, globals::h_local_ped())  <MISC_MAG_FIELD_DISTANCE) {
			Vector3 Dev_Veh_C = ENTITY::GET_ENTITY_COORDS(enty, 0);
			Vector3 Forword_coordsof_me = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::PLAYER_PED_ID(), Vector3(0, 0, 5));
			if (type == 0) { 
				MISC_MAG_FIELD_COR = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(globals::h_local_ped(),
					Vector3(0, 0, 10 * MISC_MAG_FIELD_FAR + MISC_MAG_FIELD_FUNCTION_GROUND_DISTANCE)); }//Top
			if (type == 1) { 
				MISC_MAG_FIELD_COR = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(globals::h_local_ped(),
					Vector3(0, 0, -10 * MISC_MAG_FIELD_FAR + MISC_MAG_FIELD_FUNCTION_GROUND_DISTANCE)); }//Down
			if (type == 2) { 
				MISC_MAG_FIELD_COR = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(globals::h_local_ped(),
					Vector3(-10 * MISC_MAG_FIELD_FAR, 0, 0 + MISC_MAG_FIELD_FUNCTION_GROUND_DISTANCE)); }//Left
			if (type == 3) { 
				MISC_MAG_FIELD_COR = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(globals::h_local_ped(),
					Vector3(10 * MISC_MAG_FIELD_FAR, 0, 0 + MISC_MAG_FIELD_FUNCTION_GROUND_DISTANCE)); }//Right
			if (type == 4) { 
				MISC_MAG_FIELD_COR = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(globals::h_local_ped(),
					Vector3(0, 10 * MISC_MAG_FIELD_FAR, 0 + MISC_MAG_FIELD_FUNCTION_GROUND_DISTANCE)); }//Front
			if (type == 5) { 
				MISC_MAG_FIELD_COR = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(globals::h_local_ped(),
					Vector3(0, -10 * MISC_MAG_FIELD_FAR, 0 + MISC_MAG_FIELD_FUNCTION_GROUND_DISTANCE)); }//Behind
			if (type == 6) { 
				MISC_MAG_FIELD_TOR_BOOL = true;
			}//Tornado
			else { 
				MISC_MAG_FIELD_TOR_BOOL = false; 
			}
			if (MISC_MAG_FIELD_TOR_BOOL) {
				MISC_MAG_FIELD_TIMER.setdelay(std::chrono::milliseconds(delay));
				if (MISC_MAG_FIELD_TIMER.update())
				MISC_MAG_FIELD_COR = vectors::get()->get_360_vec_around_coord(ENTITY::GET_ENTITY_COORDS(globals::h_local_ped(), 0), MISC_MAG_FIELD_FAR, MISC_MAG_FIELD_FUNCTION_GROUND_DISTANCE, 360);
			}
			Vector3 Sub_Vect = MISC_MAG_FIELD_COR- Dev_Veh_C;
			Vector3 Vecoloty_k = ENTITY::GET_ENTITY_VELOCITY(enty);
			if (tasks::get_control_of_entity_tick(enty)) {
				if (super_mode)
					ENTITY::APPLY_FORCE_TO_ENTITY(enty, 3, Sub_Vect, Vector3(0.0f, 0.f, 0.f), 0, 0, 1, 1, 0, 1);
				else
					tasks::apply_force_to_position(enty, Sub_Vect, Vecoloty_k, force_intsty, 0.3f);
			}
		}
	}
}
namespace insight {
	void fuc_magnet(Entity entity) {
		MISC_MAG_FIELD_FUC(entity, "magneto_mode_entites_attract_range"_FF->m_value.floating_point,
			"magneto_mode_range"_FF->m_value.floating_point,
			"magneto_mode_up_down"_FF->m_value.floating_point,
			"magneto_mode_type"_if->m_value.integer, "magneto_mode_delay"_if->m_value.integer,
			"magneto_mode_super_force"_tf->m_value.toggle, "magneto_mode_force_intensity"_FF->m_value.floating_point);
	}

	static timer magnetmode_Arange_timer(std::chrono::seconds(1s));
	float magnetmode_Arange = 0.0f;
	bool magnetmode_Arange_sphere = false;

	void world::magnet_mode(toggle_int_feature* feature, bool& value, int& value2) {
		if (!value)
		{
			return;
		}

		if (magnetmode_Arange != "magneto_mode_entites_attract_range"_FF->m_value.floating_point) {
			magnetmode_Arange_sphere = true;
			magnetmode_Arange = "magneto_mode_entites_attract_range"_FF->m_value.floating_point;
			magnetmode_Arange_timer.restart();
		}
		if (magnetmode_Arange_sphere) {
			tasks::draw_marker(eMarkerType::MarkerTypeDebugSphere, globals::h_local_ped_pos(), "magneto_mode_entites_attract_range"_FF->m_value.floating_point, 0, 120, 200, 100, true, true, true);
			if (magnetmode_Arange_timer.update()) {
				magnetmode_Arange_sphere = false;
			}
		}

		if (value2 == 0) { for (auto entity : tasks::get_world_entities(false, true, false)) {
				fuc_magnet(entity);
			}
		}
		if (value2 == 1) { for (auto entity : tasks::get_world_entities(true, false, false)) {
				fuc_magnet(entity);
			}
		}
		if (value2 == 2) { for (auto entity : tasks::get_world_entities(true, true, false)) {
			fuc_magnet(entity);
			}
		}
	}
}