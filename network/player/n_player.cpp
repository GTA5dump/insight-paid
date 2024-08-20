#include "cheat/script/script.hpp"
#include "cheat/menu/helper/ui.hpp"
#include "util/panels/panels.hpp"
#include "util/config/config.hpp"
#include "cheat/menu/xml/xml.hpp"
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
#include "cheat/menu/helper/ui.hpp"
namespace insight {
	std::string m_player_auto_heal[] = {
	"Health",
	"Armor",
	"Both"
	};	
	int m_cages_illusion_selected = 0;
	std::string m_cages_illusion[] = {
		"White",
		"Blue Space",
		"Rainbow Space",
		"Bright Rainbow Space",
		"Box Space",
		"Yellow"
	};
	int m_kidnap_player_selected = 0;
	std::string m_kidnap_player[] = {
		"By An NPC",
		"By You"
	};
	int m_plane_attackers_player_selected = 0;
	std::string m_plane_attackers_player[] = {
	"microlight",
	"hydra",
	"lazer",
	"strikeforce"
	};
	std::string m_plane_attackers_player_display[] = {
	"Microlight",
	"Hydra",
	"Lazer",
	"StrikeForce"

	};	
	int m_meteor_player_selected = 0;
	std::string m_meteor_player[] = {
	"Tiny",
	"Standard",
	"Huge"
	};	

	int m_rammingcars_player_selected = 0;
	static const std::vector<std::pair<const char*, const char*>> m_rammingcars_player_vec = {
		{"rcbandito","a_f_y_hipster_02"},
		{"minitank","a_f_y_hipster_02"},
		{"caddy3","a_m_y_acult_02"},
		{"blazer4","a_f_y_topless_01"},
		{"dune5","a_f_y_hipster_02"},
		{"faggio2","a_f_y_beach_01"},
		{"bmx","a_m_m_acult_01"},
		{"panto","a_f_y_hipster_02"},
		{"airtug","a_f_m_fatcult_01"},
		{"tractor","a_f_m_eastsa_01"}
	};
	std::string m_rammingcars_player_display[] = {
	"RC Bandito",
	"Mini Tank",
	"Canddy",
	"Blazer",
	"Ramp Buggy",
	"Faggio",
	"BMX",
	"Panto",
	"Airtug",
	"Tractor",
	};
	std::string m_player_rockets_speed_tys[] = {
		"Slow",
		"Medium",
		"Fast"
	};

	std::string m_player_karama_speed_tys[] = {
		"All",
		"Players Only",
	};
	
	bool n_player_trap_invisible = true;
}
namespace insight {
	void script_ui::network_player_options() {
		render::push<sub>(xorstr_("Player"), "Network_Players_Selected_Player"_joaat, [](sub* ui) {
			tasks::draw_player_info(globals::get_selected_id());
			ui->push(submenu(xorstr_("Health")).add_target("Network_Players_Selected_Health"_joaat));
			ui->push(submenu(xorstr_("Bounty")).add_target("Network_Players_Selected_Bounty"_joaat));
			ui->push(submenu(xorstr_("Explosion")).add_target("Network_Players_Selected_Explosion"_joaat));
			ui->push(submenu(xorstr_("Airstrike")).add_target("Network_Players_Selected_Airstrike"_joaat));
			ui->push(submenu(xorstr_("Trap")).add_target("Network_Players_Selected_Cage"_joaat));
			ui->push(submenu(xorstr_("Persistent Actions")).add_target("Network_Players_Selected_Actions"_joaat));
			ui->push(submenu(xorstr_("Actions Denying")).add_target("Network_Players_Actions_Denying"_joaat));
			ui->push(submenu(xorstr_("Sounds")).add_target("Network_Players_Selected_Sounds"_joaat));
			ui->push(submenu(xorstr_("Attackers")).add_target("Network_Players_Selected_Attackers"_joaat));
			ui->push(submenu(xorstr_("ESP")).add_target("Network_Players_Selected_ESP"_joaat));
			ui->push(array_toggle<std::string, int>("network_karama"_tf->m_name)
				.add_toggle(&player_options::get()->n_karama_value[globals::get_selected_id()])
				.add_position(&player_options::get()->n_karama_selection[globals::get_selected_id()])
				.add_description("network_karama"_tf->m_description)
				.add_array2(m_player_karama_speed_tys, 2));

			ui::feature_toggle_player(ui, "network_remoteotr_loop"_tf, &player_options::get()->n_remote_otr_value[globals::get_selected_id()]);

			ui::feature_toggle_player(ui, "network_remotewanted_loop"_tf, &player_options::get()->n_remote_wanted_loop_value[globals::get_selected_id()]);
			ui::feature_toggle_player(ui, "network_drop_money"_tf, &player_options::get()->n_money_drop_value[globals::get_selected_id()]);
			ui::feature_toggle_player(ui, "network_rain_money"_tf, &player_options::get()->n_money_rain_value[globals::get_selected_id()]);

			ui->push(array<std::string, int>(xorstr_("Take hostage"))
				.add_position(&m_kidnap_player_selected)
				.add_array2(m_kidnap_player,2).set_use_enter_only(true).set_action([=] {
					insight::g_fiber_pool->queue_job([&] {
							network::kidnap_player(globals::get_selected_id(), xorstr_("mule2"), xorstr_("s_m_y_clown_01"), 1.5, m_kidnap_player_selected);
						});
					}));		
			ui->push(array<std::string, int>(xorstr_("Meteor Strike"))
				.add_position(&m_meteor_player_selected)
				.add_array2(m_meteor_player,3).set_use_enter_only(true).set_action([=] {
					insight::g_fiber_pool->queue_job([=] {
							tasks::strike_meteor(globals::get_selected_id(), m_meteor_player_selected);
						});
					}));
			ui->push(button(xorstr_("Inf Loading Screen"))
				.set_action([=] {
					network::send_to_interior(globals::get_selected_id(), 81);
					}));
			ui->push(button(xorstr_("Jumpscare"))
				.set_action([=] {
					network::jump_scare_player(globals::get_selected_id());
					}));

			ui->push(button(xorstr_("Copy Appearance"))
				.set_action([=] {
					if (ENTITY::GET_ENTITY_MODEL(globals::get_selected_ped()) != ENTITY::GET_ENTITY_MODEL(globals::get_selected_ped())) {
						tasks::change_model(ENTITY::GET_ENTITY_MODEL(globals::get_selected_ped()));
					}
					PED::CLONE_PED_TO_TARGET(globals::get_selected_ped(), globals::h_local_ped());
					}));
			});	
		render::push<sub>("Health", "Network_Players_Selected_Health"_joaat, [](sub* ui) {
			tasks::draw_player_info(globals::get_selected_id());
			ui->push(button(xorstr_("Give Heal"))
				.set_action([=] {
					insight::pointers::get()->g_give_pickup_rewards(1 << globals::get_selected_id(), "REWARD_HEALTH"_joaat);
					}));		
			ui->push(button(xorstr_("Give Armor"))
				.set_action([=] {
					insight::pointers::get()->g_give_pickup_rewards(1 << globals::get_selected_id(), "REWARD_ARMOUR"_joaat);
					}));			
			ui->push(array_toggle<std::string, int>("network_auto_heal"_tif->m_name)
				.add_toggle(&player_options::get()->n_auto_heal_value[globals::get_selected_id()])
				.add_position(&player_options::get()->n_auto_heal_selection[globals::get_selected_id()])
				.add_description("network_auto_heal"_tif->m_description)
				.add_array2(m_player_auto_heal, 3));

			ui->push(button(xorstr_("Neutralize Godmode")).add_description(xorstr_("Kill Godmode Player By Spawning Tanks On Him."))
				.set_action([=] {
					insight::g_fiber_pool->queue_job([&] {
						network::n_kill_godmode(globals::get_selected_id());
						});
					}));
			});
		render::push<sub>("Bounty", "Network_Players_Selected_Bounty"_joaat, [](sub* ui) {
			tasks::draw_player_info(globals::get_selected_id());
			ui->push(number<int>(xorstr_("Value")).add_number(&player_options::get()->n_bounty_selection[globals::get_selected_id()]).
				add_min(1).add_max(10000).add_precision(0).add_step(50));

			ui::feature_toggle_player(ui, "network_bounty_unknow"_tf, &player_options::get()->n_bounty_unknow[globals::get_selected_id()]);

			ui->push(button(xorstr_("Apply Bounty"))
				.set_action([=] {
					network::n_setbounty(globals::get_selected_id(), player_options::get()->n_bounty_selection[globals::get_selected_id()],
					player_options::get()->n_bounty_unknow[globals::get_selected_id()]);
					}));

			ui::feature_toggle_player(ui, "network_bounty_loop"_tf, &player_options::get()->n_bounty_loop[globals::get_selected_id()]);
			});
		render::push<sub>("Explosion", "Network_Players_Selected_Explosion"_joaat, [](sub* ui) {
			tasks::draw_player_info(globals::get_selected_id());
			ui->push(submenu(xorstr_("Accuser - (Get Kill)")).add_target("Network_Players_Selected_Explosion_Blamer"_joaat));
			ui->push(submenu(xorstr_("Blame - (Make Kill)")).add_target("Network_Players_Selected_Explosion_Blame"_joaat));
			ui::feature_toggle_player(ui, "network_explosion_audio"_tf, &player_options::get()->n_explosionaudio[globals::get_selected_id()]);
			ui::feature_toggle_player(ui, "network_explosion_visible"_tf, &player_options::get()->n_explosionvisible[globals::get_selected_id()]);
			ui::feature_toggle_player(ui, "network_explosion_damage"_tf, &player_options::get()->n_explosiondamage[globals::get_selected_id()]);

				ui->push(array<std::string, int>(xorstr_("Explosion"))
				.add_position(&player_options::get()->n_explosion[globals::get_selected_id()])
				.add_array2(eExplosionsType, 73));

				ui->push(number<float>(xorstr_("Camera Shake")).add_number(&player_options::get()->n_explosion_shakeness[globals::get_selected_id()]).
					add_min(0).add_max(10).add_precision(1).add_step(1));

			ui->push(button(xorstr_("Apply Explosion"))
				.set_action([=] {
					network::n_create_explosion_tick(globals::get_selected_id());
					}));
			ui::feature_toggle_player(ui, "network_explosion_loop"_tf, &player_options::get()->n_explosion_value[globals::get_selected_id()]);
			});
		render::push<sub>("Accuser", "Network_Players_Selected_Explosion_Blamer"_joaat, [](sub* ui) {
			tasks::draw_player_info(globals::get_selected_id());
			if (globals::in_multiplayer()) {
				for (int id = 0; id < 32; id++) {
					if (auto netplayer = insight::pointers::get()->g_netplayer(id); netplayer) {
						bool selected = player_options::get()->n_explosion_blamer[globals::get_selected_id()] == id;
						ui->push(button(selected ? "~r~" + (std::string)netplayer->get_name() : netplayer->get_name())
							.set_action([=] {
								player_options::get()->n_explosion_blam[globals::get_selected_id()] = -2;
								player_options::get()->n_explosion_blamer[globals::get_selected_id()] = selected ? -1 : id;
								}));

					}
				}
			}
			});
		render::push<sub>("Blame", "Network_Players_Selected_Explosion_Blame"_joaat, [](sub* ui) {
			tasks::draw_player_info(globals::get_selected_id());
			if (globals::in_multiplayer()) {
				for (int id = 0; id < 32; id++) {
					if (auto netplayer = insight::pointers::get()->g_netplayer(id); netplayer) {
						bool selected = player_options::get()->n_explosion_blam[globals::get_selected_id()] == id;
						ui->push(button(selected ? "~r~" + (std::string)netplayer->get_name() : netplayer->get_name())
							.set_action([=] {
								player_options::get()->n_explosion_blamer[globals::get_selected_id()] = -2;
								player_options::get()->n_explosion_blam[globals::get_selected_id()] = selected ? -1 : id;
								}));

					}
				}
			}
			});
		render::push<sub>("Airstrike", "Network_Players_Selected_Airstrike"_joaat, [](sub* ui) {
			tasks::draw_player_info(globals::get_selected_id());
			ui->push(submenu("Projectile").add_target("Player_Vehicle_Weapons_Selct"_joaat).set_action([=] {
				script_utility::get()->weapon_projectile_select = 2;
				}));
			ui->push(array<std::string, int>(xorstr_("Speed"))
				.add_position(&player_options::get()->n_create_airstrike_speed[globals::get_selected_id()])
				.add_array2(m_player_rockets_speed_tys,3));

			ui::feature_toggle_player(ui, "network_airstrike_owned"_tf, &player_options::get()->n_create_airstrike_owned[globals::get_selected_id()]);

			ui->push(button(xorstr_("Create Strike"))
				.set_action([=] {
					int target = globals::get_selected_id();
					Vector3 shootpos;
					shootpos = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(target), 0);
					shootpos.x = shootpos.x + MISC::GET_RANDOM_FLOAT_IN_RANGE(-5, 5);
					shootpos.y = shootpos.y + MISC::GET_RANDOM_FLOAT_IN_RANGE(-5, 5);
					shootpos.z = shootpos.z + MISC::GET_RANDOM_FLOAT_IN_RANGE(50, 60);
					int speed;
					if (player_options::get()->n_create_airstrike_speed[target] == 0)
						speed = 100;
					else   if (player_options::get()->n_create_airstrike_speed[target] == 1)
						speed = 500;
					else   if (player_options::get()->n_create_airstrike_speed[target] == 2)
						speed = 1000;
					network::get()->n_create_airstrike(target, shootpos,
						player_options::get()->n_create_airstrike_exp[target], player_options::get()->n_create_airstrike_owned[target],
						speed);
					}));

			ui->push(info(xorstr_("Loop & Settings")));
			ui::feature_toggle_player(ui, "network_explosion_loop"_tf, &player_options::get()->n_create_airstrike_value[globals::get_selected_id()]);
			ui::feature_toggle_player(ui, "network_airstrike_360"_tf, &player_options::get()->n_create_airstrike_360[globals::get_selected_id()]);

			});
		render::push<sub>("Trap", "Network_Players_Selected_Cage"_joaat, [](sub* ui) {
			tasks::draw_player_info(globals::get_selected_id());
			ui->push(button(xorstr_("Alien UFO (Spinning)"))
				.set_action([=] {
					insight::g_fiber_pool->queue_job([&] {
						network::n_spinning_alien_cage(ENTITY::GET_ENTITY_COORDS(globals::get_selected_ped(), 0),
						n_player_trap_invisible);
						});
					}));
			
			ui->push(button(xorstr_("Long Tube"))
				.set_action([=] {	insight::g_fiber_pool->queue_job([&] {
					network::n_fun_cages(globals::get_selected_ped(), ENTITY::GET_ENTITY_COORDS(globals::get_selected_ped(), 0),
					n_player_trap_invisible, 3);
					});
					}));		
			ui->push(button(xorstr_("Dog Kennel"))
				.set_action([=] {	insight::g_fiber_pool->queue_job([&] {
					network::n_fun_cages(globals::get_selected_ped(), ENTITY::GET_ENTITY_COORDS(globals::get_selected_ped(), 0),
					n_player_trap_invisible, 4);
					});
					}));


			ui->push(array<std::string, int>(xorstr_("Illusion Tubes"))
				.add_position(&m_cages_illusion_selected)
				.add_array2(m_cages_illusion, 6).set_action([=] {
					if (input::get()->is_enter_pressed())
					{
						insight::g_fiber_pool->queue_job([&] {
							network::n_illusion_cages(ENTITY::GET_ENTITY_COORDS(globals::get_selected_ped(), 0),
							n_player_trap_invisible, m_cages_illusion_selected);
							});
					}
					}));


			ui->push(info(xorstr_("Settings")));

			ui::feature_toggle_player(ui, "network_explosion_visible"_tf, &player_options::get()->n_create_airstrike_360[globals::get_selected_id()]);

			});
		render::push<sub>("Actions", "Network_Players_Selected_Actions"_joaat, [](sub* ui) {
			tasks::draw_player_info(globals::get_selected_id());
			ui::feature_toggle_player(ui, "network_always_ragdoll"_tf, &player_options::get()->n_always_ragdoll_value[globals::get_selected_id()]);
			ui::feature_toggle_player(ui, "network_always_fire"_tf, &player_options::get()->n_always_on_fire_value[globals::get_selected_id()]);
			ui::feature_toggle_player(ui, "network_action_moaning_world"_tf, &player_options::get()->n_action_spawn_moanners_value[globals::get_selected_id()]);
			ui::feature_toggle_player(ui, "network_slamming_veh"_tf, &player_options::get()->n_slamming_veh_value[globals::get_selected_id()]);

			ui->push(button("Trigger Transaction Error").add_description("Triggers transaction errors for selected player").set_action([] {
				tasks::trigger_anti_cheat_everyone();
				}));
			});
		render::push<sub>("Actions Denying", "Network_Players_Actions_Denying"_joaat, [](sub* ui) {
			tasks::draw_player_info(globals::get_selected_id());
			ui::feature_toggle_player(ui, "network_action_denying_bicycle"_tf, &player_options::get()->n_action_denying_bicycle_value[globals::get_selected_id()]);
			ui::feature_toggle_player(ui, "network_action_denying_bike"_tf, &player_options::get()->n_action_denying_bike_value[globals::get_selected_id()]);
			ui::feature_toggle_player(ui, "network_action_denying_boat"_tf, &player_options::get()->n_action_denying_boat_value[globals::get_selected_id()]);
			ui::feature_toggle_player(ui, "network_action_denying_car"_tf, &player_options::get()->n_action_denying_car_value[globals::get_selected_id()]);
			ui::feature_toggle_player(ui, "network_action_denying_heli"_tf, &player_options::get()->n_action_denying_heli_value[globals::get_selected_id()]);
			ui::feature_toggle_player(ui, "network_action_denying_jetski"_tf, &player_options::get()->n_action_denying_jetski_value[globals::get_selected_id()]);
			ui::feature_toggle_player(ui, "network_action_denying_plane"_tf, &player_options::get()->n_action_denying_plane_value[globals::get_selected_id()]);
			ui::feature_toggle_player(ui, "network_action_denying_quadbike"_tf, &player_options::get()->n_action_denying_quadbike_value[globals::get_selected_id()]);
			ui::feature_toggle_player(ui, "network_action_denying_jumping"_tf, &player_options::get()->n_action_denying_jumping_value[globals::get_selected_id()]);
			ui::feature_toggle_player(ui, "network_action_denying_aiming"_tf, &player_options::get()->n_action_denying_aiming_value[globals::get_selected_id()]);
			ui::feature_toggle_player(ui, "network_action_denying_holding_gun"_tf, &player_options::get()->n_action_denying_holding_gun_value[globals::get_selected_id()]);
			ui::feature_toggle_player(ui, "network_action_denying_running"_tf, &player_options::get()->n_action_denying_running_value[globals::get_selected_id()]);
			ui::feature_toggle_player(ui, "network_action_denying_sprinting"_tf, &player_options::get()->n_action_denying_sprinting_value[globals::get_selected_id()]);
			ui::feature_toggle_player(ui, "network_action_denying_walking"_tf, &player_options::get()->n_action_denying_walking_value[globals::get_selected_id()]);				
			});
		render::push<sub>("Sounds", "Network_Players_Selected_Sounds"_joaat, [](sub* ui) {
			tasks::draw_player_info(globals::get_selected_id());
			ui->push(button(xorstr_("Wasted Earrape"))
				.set_action([=] {	insight::g_fiber_pool->queue_job([&] {
					network::ear_rape(globals::get_selected_ped(), 0);
					});
					}));		
			ui->push(button(xorstr_("Atomic Earrape"))
				.set_action([=] {	insight::g_fiber_pool->queue_job([&] {
					network::ear_rape(globals::get_selected_ped(), 1);
					});
					}));		
			ui->push(button(xorstr_("Lester Laugh"))
				.set_action([=] {	insight::g_fiber_pool->queue_job([&] {
					network::ear_rape(globals::get_selected_ped(), 2);
					});
					}));
			});
		render::push<sub>("Attackers", "Network_Players_Selected_Attackers"_joaat, [](sub* ui) {
			tasks::draw_player_info(globals::get_selected_id());
			ui->push(array<std::string, int>(xorstr_("Send Plane Attacker"))
				.add_position(&m_plane_attackers_player_selected)
				.add_array2(m_plane_attackers_player_display,4).set_use_enter_only(true).set_action([=] {
					insight::g_fiber_pool->queue_job([&] {
						tasks::get()->plane_attacker(m_plane_attackers_player->c_str(), globals::get_selected_ped(), globals::get_selected_vehicle());
						});
					}));
			ui->push(array<std::string, int>(xorstr_("Troll/Ramming Cars"))
				.add_position(&m_rammingcars_player_selected)
				.add_array2(m_rammingcars_player_display,10).set_use_enter_only(true).set_action([=] {
					insight::g_fiber_pool->queue_job([&] {
						tasks::get()->spawn_formation_vehicle(globals::get_selected_ped(), m_rammingcars_player_vec[m_rammingcars_player_selected].first
							, m_rammingcars_player_vec[m_rammingcars_player_selected].second, 1);
						});
					}));
			ui->push(button(xorstr_("Pig"))
				.set_action([=] {	insight::g_fiber_pool->queue_job([&] {
					tasks::spawn_custom_attacker(globals::get_selected_ped(), "a_c_pig"_joaat, "weapon_bat"_joaat, 2000);
					});
					}));
			ui->push(info(xorstr_("Custom Ped W Weapon")));
			ui->push(array<std::string, int>(xorstr_("Weapon"))
				.add_position(&script_utility::get()->n_attacker_weapon_hash_selected)
				.add_array2(weaponNames_Cleaned,98));
			ui->push(submenu(xorstr_("Spawn")).add_target("Player_Models"_joaat).set_action([=]
				{				
					xml::get()->load_ped_models();
					script_utility::get()->ped_spawner_sub = 2;
				}));
			});

		render::push<sub>("ESP", "Network_Players_Selected_ESP"_joaat, [](sub* ui) {
			tasks::draw_player_info(globals::get_selected_id());
			ui::feature_toggle_player(ui, "network_esp_box"_tf, &player_options::get()->n_esp_box_value[globals::get_selected_id()]);
			ui::feature_toggle_player(ui, "network_esp_line"_tf, &player_options::get()->n_esp_line_value[globals::get_selected_id()]);
			ui::feature_toggle_player(ui, "network_esp_name"_tf, &player_options::get()->n_esp_name_value[globals::get_selected_id()]);
			});
	}
}