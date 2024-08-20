#include "cheat/script/script.hpp"
#include "cheat/menu/helper/ui.hpp"
#include "util/panels/panels.hpp"
#include "util/config/config.hpp"
#include "cheat/features/globals.hpp"
#include "cheat/features/features/features_utility.hpp"
#include "util/script/script_global.hpp"
#include <network/Network.hpp>
#include "cheat/pointers/pointers.hpp"
#include"cheat/features/features.hpp"
#include "util/script/fiber_pool.hpp"
#include "cheat/features/features/features_utility.hpp"
#include "cheat/script/script_utility.hpp"
#include "game/gta/enums.hpp"

namespace insight {
    int m_tpto_him_player_selected = 0;
    std::string m_tpto_him_player[] = {
        "Instanly",
        "Nearby",
        "Into Closed Vehicle",
        "Closed Ped",
        "Sky Drive",
        "Parachute"
    };
}
namespace insight {
	void script_ui::network_teleport_options() {
        tasks::draw_player_info(globals::get_selected_id());
        render::push<sub>("Teleport", "Network_Players_Selected_Teleport"_joaat, [](sub* ui) {
            ui->push(array<std::string, int>(xorstr_("To Him"))
                .add_position(&m_tpto_him_player_selected)
                .add_array2(m_tpto_him_player, 6).set_use_enter_only(true).set_action([=] {
                    insight::g_fiber_pool->queue_job([&] {
                        int entity = globals::get_selected_ped();
                        if (m_tpto_him_player_selected == 2)  {
                            entity = globals::get_selected_vehicle();
                        }
                        tasks::get()->teleport_local_ped_to_pos(m_tpto_him_player_selected,globals::h_local_ped(),ENTITY::GET_ENTITY_COORDS(globals::get_selected_ped(),0), entity);
                        });
                    }));
            ui->push(button(xorstr_("Teleport Into Vehicle"))
                .set_action([=] {
                    insight::g_fiber_pool->queue_job([&] {
                        if (globals::get_selected_vehicle()) {
                            int seat;
                            if (tasks::get_vehicle_free_seat(globals::get_selected_vehicle(), seat)) {
                                PED::SET_PED_INTO_VEHICLE(globals::h_local_ped(), globals::get_selected_vehicle(), seat);
                            }
                        }
                        });
                    }));
            ui->push(button(xorstr_("Teleport To You"))
                .set_action([=] {
                    insight::g_fiber_pool->queue_job([&] {
                        tasks::force_teleport_player(globals::get_selected_id(), globals::h_local_ped_pos());
                        });
                    }));
            ui->push(submenu("To Apartments").add_target("Network_Players_Selected_Teleport_Apartments"_joaat));
            ui->push(button(xorstr_("To Casino"))
                .set_action([=] {
                    network::send_to_interior(globals::get_selected_id(), 123);
                    }));
            });

		render::push<sub>("Apartments", "Network_Players_Selected_Teleport_Apartments"_joaat, [](sub* ui) {
            tasks::draw_player_info(globals::get_selected_id());
			for (size_t i = 0; i < eApartementsLocations.size(); i++)
			{
				ui->push(button(eApartementsLocations[i].first)
					.set_action([=] {
						network::send_to_apartments(globals::get_selected_id(), eApartementsLocations[i].second);
						}));
			}
			});
	}
}
