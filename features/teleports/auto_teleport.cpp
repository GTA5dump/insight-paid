
#include "cheat/features/tasks.hpp"
#include "cheat/features/globals.hpp"
#include "cheat/features/features.hpp"

#include "util/math/math.hpp"
#include "game/gta/enums.hpp"
namespace insight {
	static timer auto_teleport_timer(std::chrono::milliseconds(50));
	void teleport::auto_teleport(toggle_int_feature* feature, bool& value, int& value2) {
		if (!value) {
			return;
		}
		if (value2 == 0) {
			if (HUD::IS_WAYPOINT_ACTIVE() && !globals::is_game_paused()) {
				if (auto_teleport_timer.update()) {
					Vector3 waypoint = vectors::get()->get_waypoint_coordinates();
					Vector3 result = vectors::get()->get_ground_coordinates(Vector2(waypoint.x, waypoint.y));
					tasks::teleport_animation(true);
					PED::SET_PED_COORDS_KEEP_VEHICLE(globals::h_local_ped(), result);
					tasks::teleport_animation(false);
				}
			}
		}
		else if (value == 1) {
			if (!globals::is_game_paused() && auto_teleport_timer.update())
			{
				std::map<int, int> blips = {
					{ eBlipSprite::SpriteStandard, eBlipColor::ColorYellow },
					{ eBlipSprite::SpriteStandard, eBlipColor::ColorYellowMission2 },
					{ eBlipSprite::SpriteRaceFinish, 0 },
					{ eBlipSprite::SpriteStandard, eBlipColor::ColorGreen },
					{ eBlipSprite::SpriteStandard, eBlipColor::ColorBlue },
					{ eBlipSprite::SpriteCrateDrop, 0 }
				};
				for (auto& blip : blips) {
					if (HUD::DOES_BLIP_EXIST(blip.first))
						if (HUD::GET_BLIP_COLOUR(blip.first) == blip.second) {
							Vector3 waypoint = vectors::get()->get_blip_coordinates(blip.first);
							Vector3 result = vectors::get()->get_ground_coordinates(Vector2(waypoint.x, waypoint.y));
							tasks::teleport_animation(true);
							PED::SET_PED_COORDS_KEEP_VEHICLE(globals::h_local_ped(), result);
							tasks::teleport_animation(false);
							return;
						}
				}
			}
		}
	}
}
