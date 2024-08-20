#include "cheat/features/features.hpp"
#include "cheat/features/globals.hpp"
#include "cheat/features/tasks.hpp"
#include "util/input/input.hpp"
#include "util/math/math.hpp"

namespace insight {
	inline std::string riot_weapons[] = {
	"weapon_raypistol", "weapon_ceramicpistol", "weapon_navyrevolver",
	"weapon_microsmg", "weapon_smg", "weapon_smg_mk2", "weapon_assaultsmg",
	"weapon_combatpdw", "weapon_machinepistol", "weapon_minismg", "weapon_raycarbine",
	"weapon_assaultrifle", "weapon_assaultrifle_mk2", "weapon_carbinerifle",
	"weapon_carbinerifle_mk2", "weapon_advancedrifle", "weapon_specialcarbine", "weapon_specialcarbine_mk2",
	"weapon_bullpuprifle", "weapon_bullpuprifle_mk2", "weapon_compactrifle", "weapon_mg",
	"weapon_combatmg", "weapon_combatmg_mk2", "weapon_gusenberg", "weapon_sniperrifle",
	"weapon_heavysniper", "weapon_heavysniper_mk2", "weapon_marksmanrifle", "weapon_marksmanrifle_mk2",
	"weapon_rpg", "weapon_grenadelauncher", "weapon_grenadelauncher_smoke", "weapon_minigun",
	"weapon_firework", "weapon_railgun", "weapon_hominglauncher", "weapon_compactlauncher",
	"weapon_rayminigun", "weapon_grenade"
	};
}
namespace insight {

	static timer riot_timer(std::chrono::seconds(5s));
	bool was_riot_on = false;
	
	void world::riot(toggle_feature* feature, bool& value) {
		if (!value)
		{
			was_riot_on = false;
			return;
		}
			if (!was_riot_on)
			{
				was_riot_on = true;
			}
			if (riot_timer.update())
			{
				int last_entity = 0;
				for (auto entity : tasks::get_world_entities(false, true, false))
				{
					if (last_entity != 0)
					{
						if (!PED::IS_PED_A_PLAYER(entity))
						{
							tasks::get_control_of_entity_tick(entity);
							if (PED::IS_PED_IN_ANY_VEHICLE(entity, 0))
							{

								TASK::CLEAR_PED_TASKS_IMMEDIATELY(entity);
							}
							else
							{

								WEAPON::GIVE_DELAYED_WEAPON_TO_PED(entity, rage::joaat(riot_weapons[MISC::GET_RANDOM_INT_IN_RANGE(0, 40)]), 999, true);
								TASK::TASK_SHOOT_AT_ENTITY(entity, last_entity, 999, "FIRING_PATTERN_FULL_AUTO"_joaat);

							}
						}
					}

					last_entity = entity;
				}
			}
	}
}