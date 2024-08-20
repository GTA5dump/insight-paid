#include "cheat/script/script.hpp"
#include "cheat/menu/helper/ui.hpp"
#include "util/panels/panels.hpp"
#include "util/config/config.hpp"
#include "cheat/features/globals.hpp"
#include "util/script/script_global.hpp"
#include <network/Network.hpp>
#include "cheat/pointers/pointers.hpp"
#include"cheat/features/features.hpp"
#include "util/script/fiber_pool.hpp"
#include "cheat/features/features/features_utility.hpp"
namespace insight {
	bool teleport_all_froce_running = false;
	std::string m_playerall_auto_heal[] = {
	"Health",
	"Armor",
	"Both"
	};	
	std::string m_playerall_hornboost_[] = {
	"Forwards",
	"Backwards"
	};
	bool train_moment_running = false;
}
namespace insight {
	void script_ui::network_all_players_options() {
		render::push<sub>("All Players", "Network_All_Players"_joaat, [](sub* ui) {

			ui->push(submenu(xorstr_("Include")).add_target("Network_All_Players_Include"_joaat));
			if (globals::in_multiplayer()) {
				ui->push(submenu(xorstr_("Health")).add_target("Network_All_Players_Health"_joaat));
				ui->push(submenu(xorstr_("Bounty")).add_target("Network_All_Players_Bounty"_joaat));
				ui->push(submenu(xorstr_("Sounds")).add_target("Network_All_Players_Sounds"_joaat));
				ui::push()->feature_toggle(ui, "network_all_player_otr"_tf);
				ui::push()->feature_toggle(ui, "network_all_player_karama"_tf);
				ui::push()->feature_toggle(ui, "network_all_player_wanted"_tf);
				ui::push()->feature_toggle(ui, "network_all_player_remote_rp"_tf);
				ui->push(button(xorstr_("Train Moment")).add_description(xorstr_("Makes Train With Players Vehicles"))
					.set_action([=] { insight::g_fiber_pool->queue_job([&] {
						if (!train_moment_running){
							train_moment_running = true;
							for (int i = 0; i < 32; i++) {
								if (i != globals::player_id)
									if (tasks::get_all_players_w_include_ex(i)) {
										network::train_moment(i);
									}
							}
							network::train_moment(-1);
							train_moment_running = false;
						}
						});
						}));
				ui->push(button(xorstr_("Jumpscare Lobby ~r~Unstoppable"))
					.set_action([=] {	insight::g_fiber_pool->queue_job([&] {
						network::jump_scare_lobby();

						});
						}));

				ui->push(button(xorstr_("Kill All")).add_description(xorstr_("Kills Everyone."))
					.set_action([=] { insight::g_fiber_pool->queue_job([&] {
						for (int i = 0; i < 32; i++) {
							if (i != globals::player_id)
								if (tasks::get_all_players_w_include_ex(i)) {
									FIRE::ADD_EXPLOSION(ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i), 0), 49, 999, 1, 0, 0, 0);
								}
						}
						});
						}));
				ui->push(submenu(xorstr_("Movments")).add_target("Network_All_Players_Actions"_joaat));
				ui->push(submenu(xorstr_("Action Denying")).add_target("Network_All_Players_ActionsDeny"_joaat));
				ui->push(submenu(xorstr_("Chat Commands")).add_target("Network_All_Players_ChatCommands"_joaat));
				ui->push(submenu(xorstr_("Vehicle")).add_target("Network_All_Players_Vehicle"_joaat));
				ui->push(submenu(xorstr_("Weapons")).add_target("Network_All_Players_Weapons"_joaat));
				ui->push(submenu(xorstr_("Teleport")).add_target("Network_All_Players_Teleport"_joaat));
			}
			});

		render::push<sub>("Include", "Network_All_Players_Include"_joaat, [](sub* ui) {
			ui::push()->feature_toggle(ui, "network_all_player_include_you"_tf);
			ui::push()->feature_toggle(ui, "network_all_player_include_friends"_tf);
			ui::push()->feature_toggle(ui, "network_all_player_include_nearby"_tf);
			ui::push()->feature_toggle(ui, "network_all_player_include_others"_tf);
			});		
		render::push<sub>("Actions", "Network_All_Players_Actions"_joaat, [](sub* ui) {
			ui::push()->feature_toggle(ui, "network_all_player_ragdoll"_tf);
			ui::push()->feature_toggle(ui, "network_all_player_fire"_tf);

			});	
		render::push<sub>("Actions Denying", "Network_All_Players_ActionsDeny"_joaat, [](sub* ui) {
			ui::push()->feature_toggle(ui, "network_action_denying_bicycle"_tf);
			ui::push()->feature_toggle(ui, "network_action_denying_bike"_tf);
			ui::push()->feature_toggle(ui, "network_action_denying_boat"_tf);
			ui::push()->feature_toggle(ui, "network_action_denying_car"_tf);
			ui::push()->feature_toggle(ui, "network_action_denying_heli"_tf);
			ui::push()->feature_toggle(ui, "network_action_denying_jetski"_tf);
			ui::push()->feature_toggle(ui, "network_action_denying_plane"_tf);
			ui::push()->feature_toggle(ui, "network_action_denying_quadbike"_tf);
			ui::push()->feature_toggle(ui, "network_action_denying_jumping"_tf);
			ui::push()->feature_toggle(ui, "network_action_denying_aiming"_tf);
			ui::push()->feature_toggle(ui, "network_action_denying_holding_gun"_tf);
			ui::push()->feature_toggle(ui, "network_action_denying_running"_tf);
			ui::push()->feature_toggle(ui, "network_action_denying_sprinting"_tf);
			ui::push()->feature_toggle(ui, "network_action_denying_walking"_tf);
			});
		render::push<sub>("Chat Commands", "Network_All_Players_ChatCommands"_joaat, [](sub* ui) {
			ui::push()->feature_toggle(ui, "network_command_ped_spawning"_tf);
			ui::push()->feature_toggle(ui, "network_command_vehicle_spawning"_tf);
			ui::push()->feature_toggle(ui, "network_command_object_spawning"_tf);
			ui::push()->feature_toggle(ui, "network_command_kill_player"_tf);
			ui::push()->feature_toggle(ui, "network_command_explode_player"_tf);
			ui::push()->feature_toggle(ui, "network_command_kill_my_self"_tf);
			ui::push()->feature_toggle(ui, "network_command_money_rp"_tf);		
			ui::push()->feature_toggle(ui, "network_command_fix"_tf);		
			ui::push()->feature_toggle(ui, "network_command_upgrade"_tf);		
			});

		render::push<sub>("Health", "Network_All_Players_Health"_joaat, [](sub* ui) {
			ui->push(button(xorstr_("Give Heal"))
				.set_action([=] {
					for (int i = 0; i < 32; i++) {
						if (tasks::get_all_players_w_include_ex(i)) {
							insight::pointers::get()->g_give_pickup_rewards(1 << i, "REWARD_HEALTH"_joaat);
						}
					}
					}));	
			ui->push(button(xorstr_("Give Armor"))
				.set_action([=] {
					for (int i = 0; i < 32; i++) {
						if (tasks::get_all_players_w_include_ex(i)) {
							insight::pointers::get()->g_give_pickup_rewards(1 << i, "REWARD_ARMOUR"_joaat);
						}
					}
					}));
			ui::push()->array_feature_toggle(ui, "network_all_player_auto_heal"_tif, m_playerall_auto_heal, 3);

			});
		render::push<sub>("Bounty", "Network_All_Players_Bounty"_joaat, [](sub* ui) {

			ui->push(number<int>(xorstr_("Value")).add_number(&player_options::get()->n_bounty_selection[globals::player_id]).
				add_min(1).add_max(10000).add_precision(0).add_step(50));

			ui->push(toggle("network_bounty_unknow"_tf->m_name)
				.add_toggle(&player_options::get()->n_bounty_unknow[globals::player_id])
				.add_description("network_bounty_unknow"_tf->m_description));

			ui->push(button(xorstr_("Apply Bounty"))
				.set_action([=] {
					for (int i = 0; i < 32; i++) {
						if (tasks::get_all_players_w_include_ex(i)) {
							network::n_setbounty(i, player_options::get()->n_bounty_selection[globals::player_id],
								player_options::get()->n_bounty_unknow[globals::player_id]);
						}
					}
					}));

			ui::push()->feature_toggle(ui, "network_all_player_bounty_loop"_tf);

			});
		render::push<sub>("Sounds", "Network_All_Players_Sounds"_joaat, [](sub* ui) {

			ui->push(button(xorstr_("Wasted Earrape"))
				.set_action([=] { insight::g_fiber_pool->queue_job([&] {
					for (int i = 0; i < 32; i++) {
						if (tasks::get_all_players_w_include_ex(i)) {
							network::ear_rape(i, 0);
						}
					}
					});
					}));
			ui->push(button(xorstr_("Atomic Earrape"))
				.set_action([=] {	insight::g_fiber_pool->queue_job([&] {
					for (int i = 0; i < 32; i++) {
						if (tasks::get_all_players_w_include_ex(i)) {
							network::ear_rape(i, 1);
						}
					}
					});
					}));
			ui->push(button(xorstr_("Lester Laugh"))
				.set_action([=] {	insight::g_fiber_pool->queue_job([&] {
					for (int i = 0; i < 32; i++) {
						if (tasks::get_all_players_w_include_ex(i)) {
							network::ear_rape(i, 2);
						}
					}
					});
					}));

			});
		render::push<sub>("Vehicle", "Network_All_Players_Vehicle"_joaat, [](sub* ui) {
			ui::push()->feature_toggle(ui, "network_all_player_autofix"_tf);
			ui::push()->feature_toggle(ui, "network_all_player_slipery"_tf);
			ui::push()->array_feature_toggle(ui, "network_all_player_hornboost"_tif, m_playerall_hornboost_, 2);

			});
		render::push<sub>("Weapons", "Network_All_Players_Weapons"_joaat, [](sub* ui) {
			ui::push()->feature_toggle(ui, "network_all_player_delete_Gun"_tf);
			ui::push()->feature_toggle(ui, "network_all_player_flaming_Gun"_tf);
			ui::push()->feature_toggle(ui, "network_all_player_magnet_Gun"_tf);
			ui::push()->feature_toggle(ui, "network_all_player_tryhard_Gun"_tf);
			ui::push()->array_feature_toggle(ui, "network_all_player_projectile_gun"_tif, eVehicleWeapons_Names, 28);
			ui::push()->array_feature_toggle(ui, "network_all_player_exp_ammo"_tif, eExplosionsType, 73);
			ui::push()->array_feature_toggle(ui, "network_all_player_particle_gun"_tif, particle_effects, std::size(particle_effects));
			});
		render::push<sub>("Teleport", "Network_All_Players_Teleport"_joaat, [](sub* ui) {
			ui->push(button(xorstr_("Teleport To You")).set_action([=] {
				insight::g_fiber_pool->queue_job([&] {
					if (!teleport_all_froce_running) {
						teleport_all_froce_running = true;
						for (int i = 0; i < 32; i++) {
							if (i != globals::player_id) {
								if (tasks::get_all_players_w_include_ex(i)) {
									tasks::force_teleport_player(i, globals::h_local_ped_pos());
								}
								script::get_current()->yield(100ms);
							}
						}
						teleport_all_froce_running = false;
					}});
				}));
			ui->push(submenu("To Apartments").add_target("Network_All_Players_Teleport_Apartments"_joaat));
			ui->push(button(xorstr_("To Casino"))
				.set_action([=] {
					for (int i = 0; i < 32; i++) {
						if (tasks::get_all_players_w_include_ex(i)) {
							network::send_to_interior(i, 123);
						}
					}
					}));

			});
		render::push<sub>("Apartments", "Network_All_Players_Teleport_Apartments"_joaat, [](sub* ui) {
			for (size_t i = 0; i < eApartementsLocations.size(); i++)
			{
				ui->push(button(eApartementsLocations[i].first)
					.set_action([=] {
						for (int i = 0; i < 32; i++) {
							if (tasks::get_all_players_w_include_ex(i)) {
								network::send_to_apartments(i, eApartementsLocations[i].second);
							}
						}
						}));
			}
			});

	}
}