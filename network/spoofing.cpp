#include "cheat/script/script.hpp"
#include "cheat/menu/helper/ui.hpp"
#include "util/panels/panels.hpp"
#include "util/config/config.hpp"
#include "cheat/menu/xml/xml.hpp"
#include "cheat/script/script_utility.hpp"
namespace insight {
	std::string m_spoof_onoff_type[] = {
	"Off",
	"On"
	};	
	std::string m_spoof_pos_player[] = {
	"Custom",
	"No Where"
	};

}
namespace insight {
	
	void script_ui::network_spoofing()
	{
		render::push<sub>("Spoofing", "Network_Spoofing"_joaat, [](sub* ui) {
			ui->push(submenu("Stats").add_target("Network_Spoofing_Stats"_joaat));
			ui->push(submenu("Rotation").add_target("Network_Spoofing_Rotation"_joaat));
			//ui->push(submenu("Host Token").add_target("Network_Spoofing_Host_Token"_joaat)); = crashing
			ui->push(submenu("Health").add_target("Network_Spoofing_Health"_joaat));
			ui->push(submenu("Camera").add_target("Network_Spoofing_Camera"_joaat));
			ui->push(submenu("Player Position").add_target("Network_Spoofing_Player_Pos"_joaat));
			ui::push()->array_feature_toggle(ui, "network_spoof_super_jump"_tif, m_spoof_onoff_type, 2);
			ui::push()->array_feature_toggle(ui, "network_spoof_collision"_tif, m_spoof_onoff_type, 2);


		});
		render::push<sub>("Spoofing", "Network_Spoofing_Health"_joaat, [](sub* ui) {
			ui::push()->array_feature_toggle(ui, "network_spoof_god_mode"_tif, m_spoof_onoff_type, 2);
			ui::push()->array_feature_toggle(ui, "network_spoof_default_health_armor"_tif, m_spoof_onoff_type, 2);
			ui::push()->feature_toggle_int(ui, "network_spoof_max_health"_tif, 0, 1000, 1, 0);
			ui::push()->feature_toggle_int(ui, "network_spoof_max_armor"_tif, 0, 1000, 1, 0);


		});
		render::push<sub>("Camera", "Network_Spoofing_Camera"_joaat, [](sub* ui) {
			ui::push()->feature_toggle(ui, "network_spoof_camera_pos"_tf);
			ui::push()->array_feature_toggle(ui, "network_spoof_camera_freecam"_tif, m_spoof_onoff_type, 2);
			ui::push()->array_feature_toggle(ui, "network_spoof_spectating"_tif, m_spoof_onoff_type, 2);
			});
		render::push<sub>("Player Position", "Network_Spoofing_Player_Pos"_joaat, [](sub* ui) {
			ui::push()->array_feature_toggle(ui, "network_player_pos_pos"_tif, m_spoof_pos_player, 2);
			if ("network_player_pos_pos"_tif->m_number_value.integer == 0) {			
				for (size_t i = 0; i < xml::get()->teleportData_category.size(); i++) {
					std::string submenuId = "Teleports_" + xml::get()->teleportData_category[i].name;
					ui->push(submenu(xml::get()->teleportData_category[i].name).add_target("Teleports_List"_joaat).set_action([=] {
					script_utility::get()->teleport_sub = 1; script_utility::get()->teleport_type = 1; }));
				}
			}

		});

	}

}