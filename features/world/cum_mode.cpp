#include "cheat/features/features.hpp"
#include "cheat/features/globals.hpp"
#include "cheat/features/tasks.hpp"
#include "util/input/input.hpp"
#include "util/math/math.hpp"


namespace insight {

}
namespace insight {
	void fuc_cum_peds(int i)
	{
		if (!PED::IS_PED_A_PLAYER(i))
			if (tasks::get_control_of_entity_tick(i)) {
				tasks::play_animation_tick(i, xorstr_("switch@trevor@jerking_off"), xorstr_("trev_jerking_off_loop"), 48);
				tasks::play_ptfx_bone_tick(i, 0, xorstr_("scr_fbi5a"), xorstr_("scr_fbi5a"), xorstr_("scr_fbi5_ped_water_splash"), 0.5);
			}
	}
	void world::cum_mode(toggle_feature* feature, bool& value) {
		if (!value) {
			return;
		}
		for (auto entity : tasks::get_world_entities(false, true, false)) {
			fuc_cum_peds(entity);
		}
	}
}