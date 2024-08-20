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
	void script_ui::network_social_options() {
		render::push<sub>("Social", "Network_Players_Selected_Social"_joaat, [](sub* ui) {
			tasks::draw_player_info(globals::get_selected_id());
			ui::feature_toggle_player(ui, "network_block_radio_requests"_tf, &player_options::get()->block_radio_requests[globals::get_selected_id()]);
			ui::feature_toggle_player(ui, "network_remote_rp"_tf, &player_options::get()->kill_player_chat_command[globals::get_selected_id()]);

			ui->push(button(xorstr_("Show Profile"))
				.set_action([=] {
					int handle[13];
					NETWORK::NETWORK_HANDLE_FROM_PLAYER(globals::get_selected_id(), (Any*)handle, 13);
					NETWORK::NETWORK_SHOW_PROFILE_UI((Any*)handle);
					}));
			ui->push(button(xorstr_("Send Friend Request"))
				.set_action([=] {
					int handle[13];
					NETWORK::NETWORK_HANDLE_FROM_PLAYER(globals::get_selected_id(),(Any*)handle, 13);
					NETWORK::NETWORK_ADD_FRIEND((Any*)handle, xorstr_("I would like to be your friend."));
					}));
			});
		render::push<sub>("Chat Command", "Network_Players_Selected_Chat_Commands"_joaat, [](sub* ui) {
			tasks::draw_player_info(globals::get_selected_id());
			ui::feature_toggle_player(ui, "network_command_ped_spawning"_tf, &player_options::get()->ped_spawning_chat_command[globals::get_selected_id()]);
			ui::feature_toggle_player(ui, "network_command_vehicle_spawning"_tf, &player_options::get()->vehicle_spawning_chat_command[globals::get_selected_id()]);
			ui::feature_toggle_player(ui, "network_command_object_spawning"_tf, &player_options::get()->object_spawning_chat_command[globals::get_selected_id()]);
			ui::feature_toggle_player(ui, "network_command_kill_player"_tf, &player_options::get()->kill_player_chat_command[globals::get_selected_id()]);
			ui::feature_toggle_player(ui, "network_command_explode_player"_tf, &player_options::get()->explode_player_chat_command[globals::get_selected_id()]);
			ui::feature_toggle_player(ui, "network_command_kill_my_self"_tf, &player_options::get()->kill_my_self_command[globals::get_selected_id()]);
			ui::feature_toggle_player(ui, "network_command_money_rp"_tf, &player_options::get()->money_n_rp_command[globals::get_selected_id()]);
			ui::feature_toggle_player(ui, "network_command_fix"_tf, &player_options::get()->upgrade_command[globals::get_selected_id()]);
			ui::feature_toggle_player(ui, "network_command_upgrade"_tf, &player_options::get()->fix_command[globals::get_selected_id()]);
			});

	}
}