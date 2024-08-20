#include "cheat/script/script.hpp"
#include "cheat/menu/helper/ui.hpp"
#include "util/panels/panels.hpp"
#include "util/config/config.hpp"
#include "cheat/features/globals.hpp"
#include "cheat/features/features/features_utility.hpp"
#include "cheat/features/scripted_globals.hpp"
#include "util/script/script_global.hpp"
#include <network/Network.hpp>
#include "cheat/pointers/pointers.hpp"
#include"cheat/features/features.hpp"
#include "util/script/fiber_pool.hpp"
#include "cheat/features/features/features_utility.hpp"
#include "cheat/script/script_utility.hpp"
#include "game/gta/enums.hpp"
#include <base/CObject.hpp>
namespace insight {
	void script_ui::network_removal_options() {
		render::push<sub>(xorstr_("Removal"), "Network_Players_Selected_Removal"_joaat, [](sub* ui) {
			tasks::draw_player_info(globals::get_selected_id());
			ui->push(button(xorstr_("Host Kick ~p~{HOST}"))
				.set_action([=] {
					network::host_kick(globals::get_selected_id());
					}));
			if (!detour::protections::g_was_force_host_used) {
				ui->push(button(xorstr_("Cheater Kick ~p~{HOST}"))
					.set_action([=] {
						network::breakup_kick(globals::get_selected_id(), 1);
						}));
				ui->push(button(xorstr_("Breakup Kick ~p~{HOST}"))
					.set_action([=] {
						network::breakup_kick(globals::get_selected_id(), 0);
						}));
			}

			//ui->push(button(xorstr_("Desync Kick"))
			//	.set_action([=] {
			//		network::desync_kick(globals::get_selected_id());
			//		})); desync self

			ui->push(button(xorstr_("Packet Kick"))
				.set_action([=] {
					network::packet_kick(globals::get_selected_id());
					}));

			ui->push(button(xorstr_("Null Kick"))
				.set_action([=] {
					network::null_kick(globals::get_selected_id());
					}));
			ui->push(info("Crash"));
			ui->push(button(xorstr_("Cock Crash")).set_action([] {
				network::tse_crash2(globals::get_selected_id());
				}));	

			ui->push(button(xorstr_("On God Crash"))
				.set_action([=] {
					if (!features_utility::get()->ong_crash) {
						insight::g_fiber_pool->queue_job([&] {
							network::on_god_crash(globals::get_selected_id());
							});
					}
					else {
						notify::send(xorstr_("On God Crash"), xorstr_("Crash is alreay in progress."));
					}
					}));
			ui->push(button(xorstr_("Jew Crash"))
				.set_action([=] {
					if (!features_utility::get()->jew_crash)
					{
						insight::g_fiber_pool->queue_job([&] {
							features_utility::get()->jew_crash = true;
							tasks::request_model("a_m_m_hasjew_01"_joaat);
							Ped crash_ped = PED::CREATE_PED(26, "a_m_m_hasjew_01"_joaat, ENTITY::GET_ENTITY_COORDS(globals::get()->get_selected_ped(), 0), 0, true, 0);
							ENTITY::SET_ENTITY_AS_NO_LONGER_NEEDED(&crash_ped);
							tasks::delete_entity(crash_ped);
							});
					}
					else
					{
						notify::send(xorstr_("Jew Crash"), xorstr_("Crash is alreay in progress."));
					}
					}));
			//ui->push(button(xorstr_("Nitro Crash"))
			//	.set_action([=] {
			//		if (!features_utility::get()->nitro_crash)
			//		{
			//			insight::g_fiber_pool->queue_job([&] {
			//				features_utility::get()->nitro_crash = true;
			//				tasks::request_model("a_m_m_hasjew_01"_joaat);
			//				Ped crash_ped = PED::CREATE_PED(26, "a_m_m_hasjew_01"_joaat, ENTITY::GET_ENTITY_COORDS(globals::get()->get_selected_ped(), 0), 0, true, 0);
			//				ENTITY::SET_ENTITY_AS_NO_LONGER_NEEDED(&crash_ped);
			//				});
			//		}
			//		else
			//		{
			//			notify::send(xorstr_("Nitro"), xorstr_("Crash is alreay in progress."));
			//		}
			//		}));

			ui->push(button(xorstr_("Parachute Crash"))
				.set_action([=] {
					if (!features_utility::get()->parachute_crash2)
					{
						insight::g_fiber_pool->queue_job([&] {
							features_utility::get()->parachute_crash2 = true;
							network::get()->parachute_crash2(globals::get_selected_id());
							features_utility::get()->parachute_crash2 = false;

							});
					}
					else
					{
						notify::send(xorstr_("Parachute 2 Crash"), xorstr_("Crash is alreay in progress."));
					}
					}));
			ui->push(button(xorstr_("Mods Crash")).add_description(xorstr_("Cool Instant Crash."))
				.set_action([=] {
					if (!features_utility::get()->mods_crash)
					{
						insight::g_fiber_pool->queue_job([&] {
							features_utility::get()->mods_crash = true;
							network::get()->mods_crash(globals::get_selected_id());
							features_utility::get()->mods_crash = false;
							});
					}
					else
					{
						notify::send(xorstr_("Mods Crash"), xorstr_("Crash is alreay in progress."));
					}
					}));
			ui->push(button(xorstr_("Vehicle Crash")).add_description(xorstr_("Cool Instant Crash 2."))
				.set_action([=] {
					if (!features_utility::get()->vehicle_crash)
					{
						insight::g_fiber_pool->queue_job([&] {
							features_utility::get()->vehicle_crash = true;
							if (globals::get_selected_vehicle())
								network::get()->vehicle_temp_crash(globals::get_selected_id());
							else
								notify::send("Vehicle Crash", "Player Must Be in A Car.");
							features_utility::get()->vehicle_crash = false;
							});
					}
					else
					{
						notify::send(xorstr_("Vehicle Crash"), xorstr_("Crash is alreay in progress."));
					}
					}));
			ui->push(button(xorstr_("Fragment Crash")).add_description(xorstr_("Cool Instant Crash 3."))
				.set_action([=] {
					if (!features_utility::get()->fragment_crash)
					{
						insight::g_fiber_pool->queue_job([&] {
							features_utility::get()->fragment_crash = true;
								network::get()->fragment_crash(globals::get_selected_id());
							features_utility::get()->fragment_crash = false;
							});
					}
					else
					{
						notify::send(xorstr_("Fragment Crash"), xorstr_("Crash is alreay in progress."));
					}
					}));
			ui->push(button(xorstr_("Beggy Crash")).add_description(xorstr_("Basic Object Crash."))
				.set_action([=] {
					if (!features_utility::get()->objects_crash)
					{
						insight::g_fiber_pool->queue_job([&] {
							features_utility::get()->objects_crash = true;
								network::get()->object_crash(globals::get_selected_id());
							features_utility::get()->objects_crash = false;
							});
					}
					else
					{
						notify::send(xorstr_("Beggy Crash"), xorstr_("Crash is alreay in progress."));
					}
					}));
			

			});

	}
}