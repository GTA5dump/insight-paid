#include "cheat/script/script.hpp"
#include "cheat/menu/helper/ui.hpp"
#include "util/panels/panels.hpp"
#include "util/config/config.hpp"
#include "cheat/features/scripted_globals.hpp"
#include "cheat/features/globals.hpp"
#include "cheat/features/features/features_utility.hpp"
#include "util/script/script_global.hpp"
#include <network/Network.hpp>
#include "cheat/pointers/pointers.hpp"
#include"cheat/features/features.hpp"
#include "util/script/fiber_pool.hpp"
std::string m_region_types[] = {
"Australia",
"Europe",
"Hong Kong",
"Japan",
"Latin America",
"North America",
"USA, East",
"USA, West",
};
void copy_to_clipboard(const std::string& text) {
	// Open the clipboard
	if (!OpenClipboard(nullptr)) {
		// Handle error if unable to open clipboard
		return;
	}

	// Empty the clipboard
	if (!EmptyClipboard()) {
		// Handle error if unable to empty clipboard
		CloseClipboard();
		return;
	}

	// Allocate global memory for the string
	HGLOBAL hData = GlobalAlloc(GMEM_MOVEABLE, (text.length() + 1) * sizeof(char));
	if (hData == nullptr) {
		// Handle error if unable to allocate memory
		CloseClipboard();
		return;
	}

	// Lock the memory and get a pointer to the data
	char* pData = static_cast<char*>(GlobalLock(hData));
	if (pData != nullptr) {
		// Copy the string to the allocated memory
		strcpy_s(pData, text.length() + 1, text.c_str());

		// Unlock the memory
		GlobalUnlock(hData);

		// Set the data to the clipboard
		if (SetClipboardData(CF_TEXT, hData) == nullptr) {
			// Handle error if unable to set clipboard data
			CloseClipboard();
			return;
		}
	}

	// Close the clipboard
	CloseClipboard();
}

namespace insight {
	std::string m_name_to_join_holder;
	std::string m_rid_to_join_holder_string;
	u64 m_rid_to_join_holder;

	std::string m_join_rid_array[] = {
		"Name",
		"Scid"
	};

	int holder_1;

	std::string session_types[] = {
		"Solo",
		"Invite Only",
		"Closed Friend",
		"Closed Crew",
		"Crew",
		"Public"
	};
	int session_type;

	std::string force_host[]{
		"Script Host",
		"Host"
	};
	std::string Protecton_Status[]{
	"Notify","Block","Block & Notify"
	};
	std::string Protecton_Status_Chat[]{
	"Detect","Block","Detect & Block"
	};
	std::string Lobby_Logger[]{
	"On Join","On Leave","On Join & Leave"
	};
	int force_host_int;

	void display_tunables(std::vector<tunables_data> t, sub* ui) {
		for (int i = 0; i < t.size(); i++)
		{
			if (t[i].type == "bool") {
				bool& tunable = *script_global(t[i].global_base).at(t[i].global).as<bool*>();
				ui->push(toggle(t[i].name).add_toggle(&tunable));
			}
			else if (t[i].type == "int") {
				int& tunable = *script_global(t[i].global_base).at(t[i].global).as<int*>();
				ui->push(number<int>(t[i].name).add_number(&tunable).add_min(t[i].min).add_max(t[i].max).add_precision(1).add_step(1).set_action([] {}));
			}
		}
	}
}

namespace insight {
	void script_ui::network() {
		render::push<sub>("Network", "Network"_joaat, [](sub* ui) {
			ui->push(submenu("Players").add_target("Network_Players"_joaat));
			ui->push(submenu("All Players").add_target("Network_All_Players"_joaat));
			ui->push(submenu("Indicators").add_target("Network_Lobby_Logging"_joaat));
			ui->push(submenu("Social").add_target("Network_Social"_joaat));
			ui->push(submenu("Tunables").add_target("Network_Tunables"_joaat));
			ui->push(submenu("Protections").add_target("Network_Protections"_joaat));
			ui->push(submenu("Recovery").add_target("Network_Recovery"_joaat));
			ui->push(submenu("Spoofing").add_target("Network_Spoofing"_joaat));
			ui->push(submenu("Globals").add_target("Network_Globals"_joaat));
			ui->push(submenu("Transitions").add_target("Network_Transitions"_joaat));
			ui->push(info("Quick Actions"));
			ui->push(button("Force Script Host").add_function([=] {
				tasks::force_host_of_script("freemode"_joaat);
				}));
			ui->push(button("Force Host").add_description("This Might Get You Desynced, We Working On It Tho").add_function([] {
				tasks::force_host_token_change(00);
				}));
			if (globals::get_player_mgr() && globals::in_multiplayer()) {
				panel network_info(0.15f, 0.025f, 0.022f);
				network_info.start_panel("Session Info");
				std::stringstream host_token;
				host_token << "0x" << std::hex << (u64)globals::c_local_ped()->m_player_info->m_net_player_data.m_host_token;
				std::stringstream session_token;
				session_token << "0x" << std::hex << (u64)globals::get_network()->m_game_session.m_rline_session.m_session_info.m_session_token;
				network_info.push("Current Host Token", host_token.str());
				network_info.push("Crrent ID", std::to_string(globals::player_id));
				network_info.push("Player Count", std::to_string(NETWORK::NETWORK_GET_NUM_CONNECTED_PLAYERS()));
				network_info.push("Session Token", session_token.str());
				network_info.end_panel();
			}
			});

		render::push<sub>("Players", "Network_Players"_joaat, [](sub* ui) {
			if (globals::in_multiplayer()) {
				for (int id = 0; id < 32; id++) {
					if (auto netplayer = insight::pointers::get()->g_netplayer(id); netplayer) {
						if (ui->get_selected_option() == ui->get_number_of_options()) {
							tasks::draw_player_info(id);
						}
						ui->push(submenu(tasks::get_player_name(netplayer->m_player_id, true)).
							add_target("Network_Players_Selected"_joaat).set_action([id, netplayer] {
								globals::set_selected_player(netplayer);
								}));
					}
				}
			}
			});

		render::push<sub>("Network", "Network_Players_Selected"_joaat, [](sub* ui) {
			tasks::draw_player_info(globals::get_selected_id());
			ui::push()->feature_toggle(ui, "network_player_spectate"_tf);
			ui->push(submenu("Player").add_target("Network_Players_Selected_Player"_joaat));
			ui->push(submenu("Vehicle").add_target("Network_Players_Selected_Vehicle"_joaat));
			ui->push(submenu("Weapon").add_target("Network_Players_Selected_Weapon"_joaat));
			ui->push(submenu("Removal").add_target("Network_Players_Selected_Removal"_joaat));
			ui->push(submenu("Teleport").add_target("Network_Players_Selected_Teleport"_joaat));
			ui->push(submenu("Social").add_target("Network_Players_Selected_Social"_joaat));
			ui->push(submenu("Chat Commands").add_target("Network_Players_Selected_Chat_Commands"_joaat));
			ui->push(toggle("network_player_timeout"_tf->m_name).add_toggle(&player_options::get()->timeout_full[globals::get_selected_id()]).add_description("network_player_timeout"_tf->m_description));
			});

		render::push<sub>("Protections", "Network_Protections"_joaat, [](sub* ui) {
			ui->push(submenu("Removal").add_target("Network_Protections_Removal"_joaat));
			ui->push(submenu("Movement").add_target("Network_Protections_Movement"_joaat));
			ui->push(submenu("Activity").add_target("Network_Protections_Activity"_joaat));
			ui->push(submenu("Scripted Events").add_target("Network_Protections_ScriptedEvents"_joaat));
			ui->push(submenu("Chat").add_target("Network_Protections_Chat"_joaat));
			ui->push(info("General"));
			ui::push()->array_feature_toggle(ui, "network_protection_report"_tif, Protecton_Status, 3);
			ui::push()->array_feature_toggle(ui, "network_protection_desync"_tif, Protecton_Status, 3);
			ui::push()->array_feature_toggle(ui, "network_protection_cage"_tif, Protecton_Status, 3);
			ui::push()->array_feature_toggle(ui, "network_protection_spectating"_tif, Protecton_Status, 3);
			ui::push()->array_feature_toggle(ui, "network_protection_explosion"_tif, Protecton_Status, 3);
			ui::push()->feature_toggle_int(ui, "network_protection_entities_spam"_tif, 1, 30, 1);
			ui::push()->feature_toggle(ui, "network_protection_ptfx"_tf);
			});
		render::push<sub>("Removal", "Network_Protections_Removal"_joaat, [](sub* ui) {
			ui::push()->array_feature_toggle(ui, "network_protection_kick"_tif, Protecton_Status, 3);
			ui::push()->array_feature_toggle(ui, "network_protection_crash"_tif, Protecton_Status, 3);
			ui::push()->array_feature_toggle(ui, "network_protection_remove_weapons"_tif, Protecton_Status, 3);
			ui::push()->array_feature_toggle(ui, "network_protection_vehicle_kick"_tif, Protecton_Status, 3);
			});
		render::push<sub>("Movement", "Network_Protections_Movement"_joaat, [](sub* ui) {
			ui::push()->array_feature_toggle(ui, "network_protection_freeze"_tif, Protecton_Status, 3);
			ui::push()->array_feature_toggle(ui, "network_protection_ragdoll"_tif, Protecton_Status, 3);
			ui::push()->array_feature_toggle(ui, "network_protection_request_control"_tif, Protecton_Status, 3);
			});
		render::push<sub>("Activity", "Network_Protections_Activity"_joaat, [](sub* ui) {
			ui::push()->array_feature_toggle(ui, "network_protection_force_mission"_tif, Protecton_Status, 3);
			ui::push()->array_feature_toggle(ui, "network_protection_vehicle_activity"_tif, Protecton_Status, 3);
			ui::push()->feature_toggle(ui, "network_protection_money_drops"_tf);
			});
		render::push<sub>("Scripted Events", "Network_Protections_ScriptedEvents"_joaat, [](sub* ui) {
			ui::push()->array_feature_toggle(ui, "network_protection_bounty"_tif, Protecton_Status, 3);
			ui::push()->array_feature_toggle(ui, "network_protection_sound_spam"_tif, Protecton_Status, 3);
			ui::push()->array_feature_toggle(ui, "network_protection_ceo_money"_tif, Protecton_Status, 3);
			ui::push()->array_feature_toggle(ui, "network_protection_clear_wanted"_tif, Protecton_Status, 3);
			ui::push()->array_feature_toggle(ui, "network_protection_fake_deposit"_tif, Protecton_Status, 3);
			ui::push()->array_feature_toggle(ui, "network_protection_collectibles"_tif, Protecton_Status, 3);
			ui::push()->array_feature_toggle(ui, "network_protection_banner"_tif, Protecton_Status, 3);
			ui::push()->array_feature_toggle(ui, "network_protection_teleport"_tif, Protecton_Status, 3);
			ui::push()->array_feature_toggle(ui, "network_protection_vehicle_damage"_tif, Protecton_Status, 3);
			ui::push()->array_feature_toggle(ui, "network_protection_offradar"_tif, Protecton_Status, 3);
			ui::push()->array_feature_toggle(ui, "network_protection_camera"_tif, Protecton_Status, 3);
			ui::push()->array_feature_toggle(ui, "network_protection_inf_loading"_tif, Protecton_Status, 3);
			ui::push()->feature_toggle(ui, "network_protection_label_sms"_tf);
			});
		render::push<sub>("Chat", "Network_Protections_Chat"_joaat, [](sub* ui) {
			ui::push()->array_feature_toggle(ui, "network_protection_spammers"_tif, Protecton_Status_Chat, 3);
			ui->push(info("Actions"));
			ui::push()->feature_toggle(ui, "network_protection_spammers_kick"_tf);
			ui::push()->feature_toggle(ui, "network_log_chat"_tf);
			});

		render::push<sub>("Network", "Network_Transitions"_joaat, [](sub* ui) {
			ui::push()->feature_toggle(ui, "seemless_transition"_tf);
			ui::push()->feature_toggle_int(ui, "network_player_magnet"_tif, 0, 32, 1);
			ui::push()->array_feature_toggle(ui, "network_player_matchmaking_region"_tif, m_region_types, std::size(m_region_types));
			ui->push(info("Transitions"));
			for (const auto& session_type : sessions_transitions_data)
			{
				ui->push(button(session_type.name)
					.set_action([=] {
					insight::g_fiber_pool->queue_job([&] {
							network::quick_transitions(session_type.id);
							});
						}));
			}
			});

		render::push<sub>("Globals", "Network_Globals"_joaat, [](sub* ui) {
			ui::push()->feature_toggle(ui, "player_show_invisible_players"_tf);
			ui::push()->feature_toggle(ui, "reveal_off_the_radar_map"_tf);
			ui::push()->feature_toggle(ui, "player_off_radar"_tf);
			ui::push()->feature_toggle(ui, "player_no_idle_kick"_tf);
			ui->push(button("Claim Bounty")
				.set_action([=] {
					network::claim_bounty();
					}));
			ui->push(info("Requests"));
			ui->push(button("Request Bullshark Testosterone")
				.add_function([=] {
					scripted_globals::request_bullshark_testosterone();
					}));

			ui->push(button("Request Ballistic Armor")
				.add_function([=] {
					scripted_globals::request_ballistic_armor();
					}));

			ui->push(button("Request Ammo Drop")
				.add_function([=] {
					scripted_globals::request_ammo_drop();
					}));

			ui->push(button("Request Boat Pickup")
				.add_function([=] {
					scripted_globals::request_boat_pickup();
					}));

			ui->push(button("Request Helicopter Pickup")
				.add_function([=] {
					scripted_globals::request_helicopter_pickup();
					}));

			ui->push(button("Request Backup Helicopter")
				.add_function([=] {
					scripted_globals::request_backup_helicopter();
					}));

			ui->push(button("Request Airstrike")
				.add_function([=] {
					scripted_globals::request_airstrike();
					}));

			ui->push(button("Request Avenger")
				.add_function([=] {
					scripted_globals::request_avenger();
					}));

			ui->push(button("Request Kosatka")
				.add_function([=] {
					scripted_globals::request_kosatka();
					}));

			ui->push(button("Request Mobile Operations")
				.add_function([=] {
					scripted_globals::request_mobile_operations_center();
					}));

			ui->push(button("Request Terrorbyte")
				.add_function([=] {
					scripted_globals::request_terrorbyte();
					}));

			ui->push(button("Request Acidlab")
				.add_function([=] {
					scripted_globals::request_acidlab();
					}));

			ui->push(button("Request Acidlab Bike")
				.add_function([=] {
					scripted_globals::request_acidlab_bike();
					}));

			ui->push(button("Request Taxi")
				.add_function([=] {
					scripted_globals::request_taxi();
					}));

			ui->push(button("Request Rcbandito")
				.add_function([=] {
					scripted_globals::request_rcbandito();
					}));
			ui->push(button("Request Minitank")
				.add_function([=] {
					scripted_globals::request_minitank();
					}));
			});

		render::push<sub>("Social", "Network_Social"_joaat, [](sub* ui) {
			ui->push(keyboard("Name").add_right_text(m_name_to_join_holder).add_input(&m_name_to_join_holder));
			ui->push(keyboard("Scid").add_right_text(m_rid_to_join_holder_string).add_input(&m_rid_to_join_holder_string).set_action([] {
				m_rid_to_join_holder = std::stoull(m_rid_to_join_holder_string);
				}));
			ui->push(array<std::string, int>("Join Player").add_array(&m_join_rid_array).add_position(&holder_1).add_function([] {
				if (!m_name_to_join_holder.empty()) {
					if (holder_1 == 0) {
						std::thread([&] {
							m_rid_to_join_holder = tasks::name_to_rid(m_name_to_join_holder);
							}).detach();

							if (m_rid_to_join_holder) {
								tasks::join_rid(m_rid_to_join_holder);
							}
					}
					else {
						if (m_rid_to_join_holder) {
							tasks::join_rid(m_rid_to_join_holder);
						}
					}
				}
				else { notify::send("Join Player","Please Enter RID or Name Before"); }
				}));
			ui->push(info("Tools"));
			ui->push(button("Is Player Online By Name").set_action([] {
				if (!m_name_to_join_holder.empty()) {
					std::thread([] {
						auto scid = tasks::name_to_rid(m_name_to_join_holder);
						m_rid_to_join_holder = scid;
						m_rid_to_join_holder_string = std::to_string(scid);
						if (tasks::is_rid_online(scid)) {
							notify::send("Social", std::format("{} is online", m_name_to_join_holder));
						}
						else {
							notify::send("Social", std::format("{} is not online", m_name_to_join_holder));
						}

						}).detach();
				}
				else { notify::send("Join Player", "Please Enter RID or Name Before"); }
				}));
			ui->push(button("Is Player Online By Rid").set_action([] {
				if (!m_name_to_join_holder.empty()) {
					std::thread([] {
						m_rid_to_join_holder = std::stoull(m_rid_to_join_holder_string);
						if (tasks::is_rid_online(m_rid_to_join_holder)) {
							notify::send("Social", std::format("{} is online", m_name_to_join_holder));
						}
						else {
							notify::send("Social", std::format("{} is not online", m_name_to_join_holder));
						}
						}).detach();
				}
				else { notify::send("Join Player", "Please Enter RID or Name Before"); }

				}));
			ui->push(button("Copy Scid From Name").set_action([] {
				std::thread([] {
					auto scid = tasks::name_to_rid(m_name_to_join_holder);
					m_rid_to_join_holder = scid;
					m_rid_to_join_holder_string = std::to_string(scid);
					copy_to_clipboard(std::to_string(scid));
					}).detach();
				}));
			ui->push(button("Copy Name From Rid").set_action([] {
				std::thread([] {
					m_rid_to_join_holder = std::stoull(m_rid_to_join_holder_string);
					auto name = tasks::rid_to_name(m_rid_to_join_holder);
					copy_to_clipboard(name);
					}).detach();
				}));
			});
		render::push<sub>("Indicators", "Network_Lobby_Logging"_joaat, [](sub* ui) {
			ui::push()->array_feature_toggle(ui, "network_get_join_n_leave_players"_tif, Lobby_Logger, 3);
			ui::push()->feature_toggle(ui, "network_get_join_n_leave_players_notifications"_tf);
			if ("network_get_join_n_leave_players"_tif->m_number_value.integer == 0 || "network_get_join_n_leave_players"_tif->m_number_value.integer == 2)
				ui::push()->feature_toggle(ui, "network_get_join_n_leave_players_consolelog"_tf);
			});
		render::push<sub>("Tunables", "Network_Tunables"_joaat, [](sub* ui) {
			display_tunables(tunables_main, ui);
			ui->push(submenu("Vehicles").add_target("Network_Tunables_Vehicles"_joaat));
			});
		render::push<sub>("Tunables", "Network_Tunables_Vehicles"_joaat, [](sub* ui) {
			display_tunables(tunables_vehicles, ui);
			});
	}
}