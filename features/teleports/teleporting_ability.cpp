#include "cheat/features/tasks.hpp"
#include "cheat/features/globals.hpp"
#include "cheat/features/features.hpp"
#include "util/math/math.hpp"
#include "cheat/render/render.hpp"
#include "util/notify/notify.hpp"
namespace insight {
	bool was_key_teleporting_ability_pressed = false;
	bool was_teleporting_ability_on = false;
	void teleport::teleporting_ability(toggle_feature* feature, bool& value) {
		if (!value) {
			was_teleporting_ability_on = false;
			return;
		}
		if (!was_teleporting_ability_on) {
			notify::send("teleporting_ability"_tf->m_name,
				globals::is_using_controller() ?
				"Use Right D-Pad For Teleporting."
				:
				"Use Right E Key For Teleporting.");
				was_teleporting_ability_on = true;
		}
		if (!globals::is_game_paused())
		{
			if (PAD::IS_DISABLED_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_TALK))
			{
				was_key_teleporting_ability_pressed = true;
				Vector3 laser = tasks::get_laser_ending_coordinates();
				Vector3 head = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(globals::h_local_ped(),Vector3(0,0,1.2));
				tasks::draw_marker(eMarkerType::MarkerTypeDebugSphere, head, 0.1, 0, 120, 200, 200, true);
				tasks::draw_marker(eMarkerType::MarkerTypeHorizontalCircleFat, laser, 1, 0, 120, 200, 200, true);
				float height = 25.0f;
				tasks::draw_marker(eMarkerType::MarkerTypeDebugSphere, Vector3(laser.x, laser.y, laser.z+ height), 2, 0, 120, 200, 200);
				GRAPHICS::DRAW_LINE(Vector3(laser.x, laser.y, laser.z+ height), laser, 0, 120, 200, 255);
				GRAPHICS::DRAW_LINE(Vector3(laser.x, laser.y, laser.z+ height), Vector3(laser.x, laser.y+2.0f, laser.z + height), 0, 120, 200, 255);
				GRAPHICS::DRAW_LINE(Vector3(laser.x, laser.y, laser.z+ height), Vector3(laser.x, laser.y-2, laser.z + height), 0, 120, 200, 255);
				float distanceInFeet = SYSTEM::VDIST(laser,globals::h_local_ped_pos()) * 3.28084f;
				float roundedDistance = std::roundf(distanceInFeet * 100) / 100;
				std::ostringstream oss;
				oss << std::fixed << std::setprecision(2) << roundedDistance;
				std::string formattedDistance = oss.str();				
				render::get()->draw_text_coordinates(std::string(formattedDistance + " ft").c_str(), laser, 0, 120, 200, 200);
			}
			else
			{
				if (was_key_teleporting_ability_pressed)
				{
					Vector3 laser = tasks::get_laser_ending_coordinates();
					tasks::teleport_animation(true);
					PED::SET_PED_COORDS_KEEP_VEHICLE(globals::h_local_ped(), laser);
					tasks::teleport_animation(false);
					was_key_teleporting_ability_pressed = false;
				}
			}
		}
	}
}
