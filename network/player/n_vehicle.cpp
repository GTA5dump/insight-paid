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
	int m_godmode_player_vehicle = 0;
	int m_visible_player_vehicle = 0;
	int m_freeze_player_vehicle = 0;
	int m_collision_player_vehicle = 0;
	std::string m_enable_disable[] = {
		"Enable",
		"Disable"
	};
	std::string m_player_boost_car[] = {
		"Forward",
		"Backward",
		"Up",
		"Down"
	};
	int m_player_engine_car_selection = 0;
	std::string m_player_engine_car[] = {
	"Kill","On Fire","Smoking","Revive","Turn Off"
	};
	int m_player_prostitute_car_selection = 0;
	std::string m_player_prostitute_car[] = {
	"Blow Job","Sex"
	};

	std::string m_player_vehicle_attachments[] = {
	"UFO", "GTA VC Tires","Tree Roller","Front Ramp","Back Ramp"
	};	
	std::string m_player_attach_veh[] = {
	"Front Of You", "Behind You","Top Of You","Bottom Of You","Left Of You", "Right Of You"
	};
}
namespace insight {
	void script_ui::network_vehicle_options() {
		render::push<sub>("Vehicle", "Network_Players_Selected_Vehicle"_joaat, [](sub* ui) {
			tasks::draw_player_info(globals::get_selected_id());
			ui->push(submenu("Customize").add_target("Player_Vehicle_LosSantosCustom"_joaat).set_action([=] {
				script_utility::get()->lsc_sub = 1;
				}));
			ui->push(submenu("Boost").add_target("Network_Players_Selected_Boost"_joaat));
			ui->push(submenu("Engine").add_target("Network_Players_Selected_Engine"_joaat));
			ui->push(submenu("Attachments").add_target("Network_Players_Selected_Attachments"_joaat));
			ui->push(submenu("Attach Player's Vehicle").add_target("Network_Players_Selected_PlayerVehicleAttachments"_joaat));

			ui::feature_toggle_player(ui, "network_auto_fix"_tf, &player_options::get()->n_auto_fix_value[globals::get_selected_id()]);
			ui::feature_toggle_player(ui, "network_slipperyveh"_tf, &player_options::get()->n_slippery_veh_value[globals::get_selected_id()]);

			ui->push(array<std::string, int>(xorstr_("God Mode")).add_array(&m_enable_disable).add_position(&m_godmode_player_vehicle).set_use_enter_only(true).set_action([=] {
				insight::g_fiber_pool->queue_job([&] {
					if (globals::get_selected_vehicle())
						if (tasks::get()->request_control(globals::get_selected_vehicle())) {
							ENTITY::SET_ENTITY_INVINCIBLE(globals::get_selected_vehicle(), m_godmode_player_vehicle == 1 ? false : true);
						}
					});
				}));
			ui->push(array<std::string, int>(xorstr_("Visible")).add_array(&m_enable_disable).add_position(&m_visible_player_vehicle).set_use_enter_only(true).set_action([=] {
				insight::g_fiber_pool->queue_job([&] {
					if (globals::get_selected_vehicle())
						if (tasks::get()->request_control(globals::get_selected_vehicle())) {
							ENTITY::SET_ENTITY_VISIBLE(globals::get_selected_vehicle(), m_visible_player_vehicle == 1 ? false : true, m_visible_player_vehicle == 1 ? false : true);
						}
					});
				}));
			ui->push(array<std::string, int>(xorstr_("Freeze")).add_array(&m_enable_disable).add_position(&m_freeze_player_vehicle).set_use_enter_only(true).set_action([=] {
				insight::g_fiber_pool->queue_job([&] {
					if (globals::get_selected_vehicle())
						if (tasks::get()->request_control(globals::get_selected_vehicle())) {
							ENTITY::FREEZE_ENTITY_POSITION(globals::get_selected_vehicle(), m_freeze_player_vehicle == 1 ? false : true);
						}
					});
				}));
			ui->push(array<std::string, int>(xorstr_("Collision")).add_array(&m_enable_disable).add_position(&m_collision_player_vehicle).set_use_enter_only(true).set_action([=] {
				insight::g_fiber_pool->queue_job([&] {
					if (globals::get_selected_vehicle())
						if (tasks::get()->request_control(globals::get_selected_vehicle())) {
							ENTITY::SET_ENTITY_COLLISION(globals::get_selected_vehicle(), m_collision_player_vehicle == 1 ? false : true, m_collision_player_vehicle == 1 ? false : true);
							ENTITY::SET_ENTITY_COMPLETELY_DISABLE_COLLISION(globals::get_selected_vehicle(), m_collision_player_vehicle == 1 ? false : true, m_collision_player_vehicle == 1 ? false : true);
						}
					});
				}));
			ui->push(array<std::string, int>(xorstr_("Prostitute")).add_array(&m_player_prostitute_car).add_position(&m_player_prostitute_car_selection).set_use_enter_only(true).set_action([=] {
				insight::g_fiber_pool->queue_job([&] {
					if (globals::get_selected_vehicle())
						tasks::stripper_car(globals::get_selected_vehicle(), m_player_prostitute_car_selection);
					});
				}));

			ui->push(button(xorstr_("Brust Tyres"))
				.set_action([=] {
					insight::g_fiber_pool->queue_job([&] {
						if (globals::get_selected_vehicle())
							if (tasks::get()->request_control(globals::get_selected_vehicle()))
								VEHICLE::SET_VEHICLE_TYRES_CAN_BURST(globals::get_selected_vehicle(), true);
						for (size_t i = 0; i < 6; i++) {
							VEHICLE::SET_VEHICLE_TYRE_BURST(globals::get_selected_vehicle(), i, true, 1000.0);
						}
						});
					}));

			ui->push(button(xorstr_("Flip"))
				.set_action([=] {
					insight::g_fiber_pool->queue_job([&] {
						if (globals::get_selected_vehicle())
							if (tasks::get()->request_control(globals::get_selected_vehicle())) {
								Vector3 rot = ENTITY::GET_ENTITY_ROTATION(globals::get_selected_vehicle(), 2);
								float y = rot.y;
								if (y < -150.0f || y > 150.0f) {
									ENTITY::SET_ENTITY_ROTATION(globals::get_selected_vehicle(), rot.x, 0, rot.z, 2, 1);
								}
								else {
									ENTITY::SET_ENTITY_ROTATION(globals::get_selected_vehicle(), rot.x, 180.f, rot.z, 2, 1);
								}
							}
						});
					}));
			ui->push(button(xorstr_("Gift Vehicle")).add_description(xorstr_("Makes Vehicle Saveable In Garage."))
				.set_action([=] {
					insight::g_fiber_pool->queue_job([&] {
						if (globals::get_selected_vehicle())
							if (tasks::get()->request_control(globals::get_selected_vehicle()))
								tasks::get()->gift_vehicle(globals::get_selected_vehicle(), globals::get_selected_id());
						});
					}));
			ui->push(button(xorstr_("Delete"))
				.set_action([=] {
					insight::g_fiber_pool->queue_job([&] {
						if (globals::get_selected_vehicle())
							if (tasks::get()->request_control(globals::get_selected_vehicle()))
								tasks::get()->delete_entity(globals::get_selected_vehicle());
						});
					}));
			ui->push(button(xorstr_("Repair"))
				.set_action([=] {
					insight::g_fiber_pool->queue_job([&] {
						if (globals::get_selected_vehicle())
							if (tasks::get()->request_control(globals::get_selected_vehicle()))
								tasks::get()->fix_vehicle(globals::get_selected_vehicle());
						});
					}));
			ui->push(button(xorstr_("Pimp Ride"))
				.set_action([=] {
					insight::g_fiber_pool->queue_job([&] {
						if (globals::get_selected_vehicle())
							if (tasks::get()->request_control(globals::get_selected_vehicle()))
								tasks::upgrade_vehicle(globals::get_selected_vehicle());
						});
					}));
			});

		render::push<sub>(xorstr_("Boost"), "Network_Players_Selected_Boost"_joaat, [](sub* ui) {
			tasks::draw_player_info(globals::get_selected_id());
			ui->push(array<std::string, int>(xorstr_("Boost")).add_array(&m_player_boost_car)
				.add_position(&player_options::get()->hold_horn_boost_value_Selection[globals::get_selected_id()])
				.set_use_enter_only(true).set_action([=] {
					insight::g_fiber_pool->queue_job([&] {
						if (globals::get_selected_vehicle())
							if (tasks::get()->request_control(globals::get_selected_vehicle()))
							{
								if (player_options::get()->hold_horn_boost_value_Selection[globals::get_selected_id()] == 0 ||
									player_options::get()->hold_horn_boost_value_Selection[globals::get_selected_id()] == 1) {

									float speed = ENTITY::GET_ENTITY_SPEED(globals::get_selected_vehicle());
									VEHICLE::SET_VEHICLE_FORWARD_SPEED(globals::get_selected_vehicle(),
										player_options::get()->hold_horn_boost_value_Selection[globals::get_selected_id()] == 1 ?
										-speed - player_options::get()->hold_horn_boost_value_Speed[globals::get_selected_id()] :
										speed + player_options::get()->hold_horn_boost_value_Speed[globals::get_selected_id()]);
								}
								else {
									if (player_options::get()->hold_horn_boost_value_Selection[globals::get_selected_id()] == 2 ||
										player_options::get()->hold_horn_boost_value_Selection[globals::get_selected_id()] == 3) {
										ENTITY::APPLY_FORCE_TO_ENTITY(globals::get_selected_id(), 1, Vector3(0.0f, player_options::get()->hold_horn_boost_value_Selection[globals::get_selected_id()] == 2 ? 0.6f * player_options::get()->hold_horn_boost_value_Speed[globals::get_selected_id()] : -0.6f * player_options::get()->hold_horn_boost_value_Speed[globals::get_selected_id()], 0.f), Vector3(0.0f, 0.0f, 0.0f), 0, 1, 1, 1, 0, 1);
									}
								}
							}
						});
					}));

			ui->push(number<float>(xorstr_("Speed")).add_number(&player_options::get()->hold_horn_boost_value_Speed[globals::get_selected_id()]).
				add_min(-100).add_max(100).add_precision(0).add_step(5).add_description(xorstr_("Sets Speed Of Boost Bruh.")));
			ui::feature_toggle_player(ui, "network_hold_hornboost"_tf, &player_options::get()->hold_horn_boost_value[globals::get_selected_id()]);
			});
		render::push<sub>("Engine", "Network_Players_Selected_Engine"_joaat, [](sub* ui) {
			tasks::draw_player_info(globals::get_selected_id());

			ui->push(button(xorstr_("Apply Once")).set_action([=] {
				insight::g_fiber_pool->queue_job([&] {
					if (globals::get_selected_vehicle())
						if (tasks::get()->request_control(globals::get_selected_vehicle()))
							tasks::get()->set_vehicle_engine_health(globals::get_selected_vehicle(), player_options::get()->n_engine_health_selection[globals::get_selected_id()]);
					});
				}));
			ui::feature_toggle_player(ui, "network_engine_health_set"_tf, &player_options::get()->n_engine_health_value[globals::get_selected_id()]);

			ui->push(info(xorstr_("Settings")));

			for (int i = 0; i < std::size(m_player_engine_car); i++)
			{
				bool selected = player_options::get()->n_engine_health_selection[globals::get_selected_id()] == i;
				ui->push(button(selected ? "~r~" + std::string(m_player_engine_car[i]) : m_player_engine_car[i]).set_action([=] {
					player_options::get()->n_engine_health_selection[globals::get_selected_id()] = i;
					}));
			}
			});
		render::push<sub>("Attachments", "Network_Players_Selected_Attachments"_joaat, [](sub* ui) {
			tasks::draw_player_info(globals::get_selected_id());
			for (int i = 0; i < std::size(m_player_vehicle_attachments); i++)
			{
				ui->push(button(m_player_vehicle_attachments[i]).set_action([=] {
					insight::g_fiber_pool->queue_job([&] {
						tasks::vehicle_attachments(globals::get_selected_vehicle(), i);
						});
					}));
			}
			ui->push(button("Clear All Attachments").set_action([=] {
				insight::g_fiber_pool->queue_job([&] {
					tasks::clear_vehicle_attachments(globals::get_selected_vehicle());
					});
				}));
			});
		render::push<sub>("Attachments", "Network_Players_Selected_PlayerVehicleAttachments"_joaat, [](sub* ui) {
			tasks::draw_player_info(globals::get_selected_id());
			for (int i = 0; i < std::size(m_player_attach_veh); i++)
			{
				ui->push(button(m_player_attach_veh[i]).set_action([=] {
					insight::g_fiber_pool->queue_job([&] {
						network::n_attach_veh(globals::get_selected_id(), i);
						});
					}));
			}
			ui->push(button("Clear All Attachments").set_action([=] {
				insight::g_fiber_pool->queue_job([&] {
					tasks::clear_vehicle_attachments(globals::h_local_ped(),true);
					});
				}));
			});
	}	
}	