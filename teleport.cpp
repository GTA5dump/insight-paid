
#include "cheat/script/script.hpp"
#include "cheat/menu/helper/ui.hpp"
#include "cheat/features/globals.hpp"
#include "util/panels/panels.hpp"
#include "util/config/config.hpp"
#include "cheat/features/globals.hpp"
#include "cheat/features/features/features_utility.hpp"
#include "util/math/math.hpp"
#include "cheat/menu/xml/xml.hpp"
#include "util/script/fiber_pool.hpp"
#include "cheat/script/script_utility.hpp"
namespace insight {

    std::string m_auto_teleport_[] = {
       "Waypoint",
       "Missions"
    };
}
namespace insight { // FUCK should have done this for others also.  SLAVESS WORK WOULD HAVE BEEN SAVED
    void script_ui::teleports() {
        render::push<sub>("Insight", "Teleports"_joaat, [](sub* ui) {
            //auto_teleport
            ui->push(button(xorstr_("Instant Waypoint Travel"))
                .set_action([=] {
                    insight::g_fiber_pool->queue_job([] {
                        if (HUD::IS_WAYPOINT_ACTIVE()) {
                            Vector3 waypoint = vectors::get()->get_waypoint_coordinates();
                            Vector3 result = vectors::get()->get_ground_coordinates(Vector2(waypoint.x, waypoint.y));
                            tasks::teleport_animation(true);
                            PED::SET_PED_COORDS_KEEP_VEHICLE(globals::h_local_ped(), result);
                            tasks::teleport_animation(false);
                        }
                        });
                    }));
            ui->push(submenu("Smooth Teleporting").add_target("Teleports_Smooth"_joaat).set_action([=] {}));
            ui->push(submenu("Options").add_target("Teleports_Options"_joaat).set_action([=] {}));

            ui->push(info("Locations"));
            for (size_t i = 0; i < xml::get()->teleportData_category.size(); i++) {
                std::string submenuId = "Teleports_" + xml::get()->teleportData_category[i].name;
                ui->push(submenu(xml::get()->teleportData_category[i].name).add_target("Teleports_List"_joaat).set_action([=] { script_utility::get()->teleport_sub = i;script_utility::get()->teleport_type = 0; }));
            }
            });

        render::push<sub>("Insight", "Teleports_List"_joaat, [](sub* ui) {
            int i = script_utility::get()->teleport_sub;
            if (xml::get()->teleportData_category.size() != 0) {
                const std::string currentCategory = xml::get()->teleportData_category[i].name;
                for (const auto& data : xml::get()->teleportData) {
                    if (data.category == currentCategory) {
                        bool is_same = data.pos.x == features_utility::get()->spoofed_pos_coordinates.x && features_utility::get()->spoofed_pos_coordinates.y == data.pos.y &&
                        features_utility::get()->spoofed_pos_coordinates.z == data.pos.z;

                        ui->push(button(script_utility::get()->teleport_type == 1 ? is_same ? "~r~" + data.name : data.name : data.name).set_action([=] {
                            insight::g_fiber_pool->queue_job([data] {
                                if (script_utility::get()->teleport_type == 0)
                                    tasks::teleport_local_ped_to_pos(0, globals::h_local_ped(), data.pos); 
                                else if (script_utility::get()->teleport_type == 1)
                                {
                                    features_utility::get()->spoofed_pos_coordinates = data.pos;
                                }
                                }); 
                            }));
                    }
                }
            }
            });       
        render::push<sub>("Insight", "Teleports_Smooth"_joaat, [](sub* ui) {
            ui::push()->feature_toggle(ui, "teleport_settings_animation"_tf);
          //  ui::push()->feature_float(ui, "teleport_settings_animation_ease_in"_FF, 0.f, 5000.f,100.f); does not really matter
            ui::push()->feature_float(ui, "teleport_settings_animation_ease_out"_FF, 0.f, 5000.f, 100.f);

            });
        render::push<sub>("Insight", "Teleports_Options"_joaat, [](sub* ui) {
            ui::push()->feature_toggle(ui, "teleporting_ability"_tf);
            ui::push()->array_feature_toggle(ui, "auto_teleport"_tif, m_auto_teleport_, 2);

            });
 
    }
}