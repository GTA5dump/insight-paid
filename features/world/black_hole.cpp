

#include "cheat/features/features.hpp"
#include "cheat/features/globals.hpp"
#include "cheat/features/tasks.hpp"

#include "util/input/input.hpp"

#include "util/math/math.hpp"


#include "cheat/features/features/features_utility.hpp"
namespace insight {
	
	static timer blackhole_timer(std::chrono::milliseconds(200));
	int blackhole_addr_spiral = 0;
	int blackhole_range = 0;
	bool draw_blackhole_range = false;
	static timer draw_blackhole_range_sphere(std::chrono::seconds(2));

}
namespace insight {

	void world::blackhole(toggle_int_feature* feature, bool& value, int& value2) {
		if (!value)
		{
			return;
		}
		Vector3 force_pos = Vector3(features_utility::get()->blackhole_pos.x, features_utility::get()->blackhole_pos.y,
		features_utility::get()->blackhole_pos.z + "black_hole_z"_FF->m_value.floating_point);
		tasks::draw_marker(eMarkerType::MarkerTypeDebugSphere, force_pos, 5, 10, 10, 10, 255, true, true, true);
		int range = "black_hole_range"_FF->m_value.floating_point;
		if ("black_hole_range"_FF->m_value.floating_point != blackhole_range)
		{
			draw_blackhole_range = true;
			draw_blackhole_range_sphere.restart();
			blackhole_range = "black_hole_range"_FF->m_value.floating_point;
		}
		if (draw_blackhole_range)
		{
			tasks::draw_marker(eMarkerType::MarkerTypeDebugSphere, force_pos, "black_hole_range"_FF->m_value.floating_point, 0, 120, 200, 100, true, true, true);
			if (draw_blackhole_range_sphere.update())
			{
				draw_blackhole_range = false;
			}
		}
		if (value2 == 0) // super
		{
			for (auto handle : tasks::get_world_entities(true, true, false))
			{
				if (SYSTEM::VDIST(force_pos,ENTITY::GET_ENTITY_COORDS(handle, 0)) < range)
				{
					Vector3 force = force_pos - ENTITY::GET_ENTITY_COORDS(handle, 0);
					if (tasks::get_control_of_entity_tick(handle))
						ENTITY::APPLY_FORCE_TO_ENTITY(handle, 3, force, { 0, 0, 0 }, 0, false, true, true, false, true);
				}
			}

		}
		if (value2 == 1) //super w delete
		{
			for (auto handle : tasks::get_world_entities(true, true, false))
			{
				if (SYSTEM::VDIST(force_pos,ENTITY::GET_ENTITY_COORDS(handle, 0)) < range)
				{
					Vector3 force = force_pos - ENTITY::GET_ENTITY_COORDS(handle, 0);
					if (tasks::get_control_of_entity_tick(handle))
					{
						ENTITY::APPLY_FORCE_TO_ENTITY(handle, 3, force, { 0, 0, 0 }, 0, false, true, true, false, true);
						if (SYSTEM::VDIST(ENTITY::GET_ENTITY_COORDS(handle, 0),force_pos) < 5.f)
						{
							tasks::delete_entity(handle);
						}
					}
				}
			}

		}
		if (value2 == 2) //spiral
		{
			if (blackhole_timer.update())
			{
				int distance = 0;
				if (blackhole_addr_spiral >= 180)
				{
					blackhole_addr_spiral = 0;
				}
				else
				{
					for (size_t i = 0; i < 4; i++)
					{
						blackhole_addr_spiral++;
					}
				}
				for (auto entityIndex : tasks::get_world_entities(true, true, false))
				{
					if (SYSTEM::VDIST(force_pos,ENTITY::GET_ENTITY_COORDS(entityIndex, 0)) < range)
					{
						int pos = blackhole_addr_spiral + distance;
						Vector3 pos360 = vectors::get()->get_360_iterator_vec_around_coord(force_pos, 40, 25, pos, 180);
						Vector3 entityPos = ENTITY::GET_ENTITY_COORDS(entityIndex, 0);
						Vector3 forceVec = pos360 - entityPos;
						if (tasks::get_control_of_entity_tick(entityIndex))
						{
							tasks::apply_force_to_position(entityIndex, forceVec, ENTITY::GET_ENTITY_VELOCITY(entityIndex), 0.8f, 0.2);
							distance++;
						}
					}
				}
			}
		}
	}
}