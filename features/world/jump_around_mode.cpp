#include "cheat/features/features.hpp"
#include "cheat/features/globals.hpp"
#include "cheat/features/tasks.hpp"
#include "util/input/input.hpp"
#include "util/math/math.hpp"
#include "cheat/features/features/features_utility.hpp"

namespace insight {
	static timer jump_around_mode_timer(std::chrono::seconds(2s));
}
namespace insight {
	void jump_around_ped(int i)
	{
		if (ENTITY::IS_ENTITY_A_PED(i))
		if (!PED::IS_PED_A_PLAYER(i))
			if (tasks::get_control_of_entity_tick(i)) {
				ENTITY::APPLY_FORCE_TO_ENTITY(i, 3, Vector3(0.0f, 0.f, 5.f), Vector3(0.0f, 0.f, 0.f), 0, 0, 1, 1, 0, 1);
			}
	}	
	void jump_around_vehicle(int i)
	{
		if (ENTITY::IS_ENTITY_A_VEHICLE(i))
			if (tasks::get_control_of_entity_tick(i)) {
				tasks::vehicle_acrobatics(i, MISC::GET_RANDOM_INT_IN_RANGE(0,5), 1.0);
			}
	}
	void world::jump_around_mode(toggle_feature* feature, bool& value) {
		if (!value) {
			return;
		}
		if (jump_around_mode_timer.update())
		for (auto entity : tasks::get_world_entities(true, true, false)) {
			jump_around_ped(entity);
			jump_around_vehicle(entity);
		}
	}
	static timer map_mods_toggle_remover_timer(std::chrono::seconds(6s));
	bool map_mods_toggle_remover_reset_trigger = false;
	void world::map_mods_toggle_remover(toggle_feature* feature, bool& value) {
		if (map_mods_toggle_remover_reset_trigger) {
			if (map_mods_toggle_remover_timer.update()) {
				features_utility::get()->spawn_placement_from_xml_node_first_time = false;
				features_utility::get()->load_placements_from_xml_file_in_progress = false;
			}
		}
		else {
			if (features_utility::get()->spawn_placement_from_xml_node_first_time || features_utility::get()->load_placements_from_xml_file_in_progress) {
				map_mods_toggle_remover_reset_trigger = true;
			}
		}
	}
}