

#include "cheat/script/script.hpp"
#include "cheat/menu/helper/ui.hpp"
#include "cheat/features/globals.hpp"

#include "util/panels/panels.hpp"
#include "util/config/config.hpp"
std::string face_direction[] = {
	"Left",
	"Right",
	"Back"
};

/*
* 			feature_manager::add(toggle_int_feature("network_spoof_ped_face_direction", "Face Direction", "Spoofs Player Face Direction", null_feature_int_toggle));
			feature_manager::add(toggle_feature("network_spoof_player_rotation", "Player Rotation", "Fucks Your Ped Rotation For Other Players", null_feature_toggle));
			feature_manager::add(toggle_feature("network_spoof_ped_relative", "Relative", "Relative To Your Current Ped Heading", null_feature_toggle));
*/
namespace insight {
	void script_ui::network_spoofing_rotation() {
		render::push<sub>("Rotation", "Network_Spoofing_Rotation"_joaat, [](sub* ui) {
			ui::push()->feature_toggle(ui, "network_spoof_ped_jitter"_tf);
			ui::push()->feature_toggle(ui, "network_spoof_player_rotation"_tf);
			ui::push()->array_feature_toggle(ui, "network_spoof_ped_face_direction"_tif, face_direction, 3);
			ui::push()->feature_toggle(ui, "network_spoof_ped_relative"_tf);
		});
	}
}