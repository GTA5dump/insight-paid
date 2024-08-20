#include "cheat/features/features.hpp"
#include "cheat/features/globals.hpp"
#include "cheat/features/tasks.hpp"
#include "util/input/input.hpp"
#include "util/math/math.hpp"
#include "util/notify/notify.hpp"

namespace insight {
	static timer nuke_timer(std::chrono::seconds(1s));
}
namespace insight {

	void world::nuke_waypoint(toggle_int_feature* feature, bool& value, int& value2) {
		if (!value)
		{
			return;
		}

		if ("auto_teleport"_tif->m_toggle_value.toggle) {
			notify::send("Nuke Waypoint", "Turned Off Auto Teleportation.");
			"auto_teleport"_tif->m_toggle_value.toggle = false;
		}
		if (HUD::IS_WAYPOINT_ACTIVE())
		{
			if (nuke_timer.update())
			{
				if (value2 == 0)
				{
					tasks::nuke_real(vectors::get()->get_waypoint_coordinates(), true);
				}
				else if (value2 == 1)
				{
					tasks::nuke_normal(vectors::get()->get_waypoint_coordinates());
				}
				else if (value2 == 2)
				{
					tasks::nuke_x(vectors::get()->get_waypoint_coordinates());
				}
			}
		}

	}
}