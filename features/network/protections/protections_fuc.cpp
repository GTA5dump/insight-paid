#include "cheat/features/tasks.hpp"
#include "cheat/features/globals.hpp"
#include "cheat/features/features.hpp"
#include "util/gta_util.hpp"
#include <network/Network.hpp>
#include "util/caller.hpp"

namespace insight {

	void network::protection_kick(toggle_int_feature* feature,bool& value, int& value2) {
		detour::protections::g_kick_toggle = value;
		detour::protections::g_kick_integer = value2;
	}	
	void network::protection_crash(toggle_int_feature* feature,bool& value, int& value2) {
		detour::protections::g_crash_toggle = value;
		detour::protections::g_crash_integer = value2;
	}	
	void network::protection_freeze(toggle_int_feature* feature,bool& value, int& value2) {
		detour::protections::g_freeze_toggle = value;
		detour::protections::g_freeze_integer = value2;
	}	
	void network::protection_ragdoll(toggle_int_feature* feature,bool& value, int& value2) {
		detour::protections::g_ragdoll_toggle = value;
		detour::protections::g_ragdoll_integer = value2;
	}	
	void network::protection_request_control(toggle_int_feature* feature,bool& value, int& value2) {
		detour::protections::g_requestcontrol_toggle = value;
		detour::protections::g_requestcontrol_integer = value2;
	}	
	void network::protection_report(toggle_int_feature* feature,bool& value, int& value2) {
		detour::protections::g_report_toggle = value;
		detour::protections::g_report_integer = value2;
	}	

	void network::protection_bounty(toggle_int_feature* feature,bool& value, int& value2) {
		detour::protections::g_bounty_toggle = value;
		detour::protections::g_bounty_integer = value2;
	}
	void network::protection_remove_weapons(toggle_int_feature* feature, bool& value, int& value2) {
		detour::protections::g_report_toggle = value;
		detour::protections::g_report_integer = value2;
	}
	void network::protection_sound_spam(toggle_int_feature* feature, bool& value, int& value2) {
		detour::protections::g_sound_spam_toggle = value;
		detour::protections::g_sound_spam_integer = value2;
	}
	void network::protection_ceo_money(toggle_int_feature* feature, bool& value, int& value2) {
		detour::protections::g_ceo_money_toggle = value;
		detour::protections::g_ceo_money_integer = value2;
	}
	void network::protection_clear_wanted(toggle_int_feature* feature, bool& value, int& value2) {
		detour::protections::g_clear_wanted_toggle = value;
		detour::protections::g_clear_wanted_integer = value2;
	}
	void network::protection_fake_depost(toggle_int_feature* feature, bool& value, int& value2) {
		detour::protections::g_fake_deposit_toggle = value;
		detour::protections::g_fake_deposit_integer = value2;
	}
	void network::protection_force_mission(toggle_int_feature* feature, bool& value, int& value2) {
		detour::protections::g_force_mission_toggle = value;
		detour::protections::g_force_mission_integer = value2;
	}	
	void network::protection_collectibles(toggle_int_feature* feature, bool& value, int& value2) {
		detour::protections::g_collectibles_toggle = value;
		detour::protections::g_collectibles_integer = value2;
	}
	void network::protection_banner(toggle_int_feature* feature, bool& value, int& value2) {
		detour::protections::g_banner_toggle = value;
		detour::protections::g_banner_integer = value2;
	}	
	void network::protection_teleport(toggle_int_feature* feature, bool& value, int& value2) {
		detour::protections::g_teleport_toggle = value;
		detour::protections::g_teleport_integer = value2;
	}	
	void network::protection_vehicle_damage(toggle_int_feature* feature, bool& value, int& value2) {
		detour::protections::g_vehicle_damage_toggle = value;
		detour::protections::g_vehicle_damage_integer = value2;
	}	
	void network::protection_off_radar(toggle_int_feature* feature, bool& value, int& value2) {
		detour::protections::g_off_radar_toggle = value;
		detour::protections::g_off_radar_integer = value2;
	}	
	void network::protection_camera(toggle_int_feature* feature, bool& value, int& value2) {
		detour::protections::g_camera_toggle = value;
		detour::protections::g_camera_integer = value2;
	}	
	void network::protection_vehicle_kick(toggle_int_feature* feature, bool& value, int& value2) {
		detour::protections::g_vehicle_kick_toggle = value;
		detour::protections::g_vehicle_kick_integer = value2;
	}	
	void network::protection_activity(toggle_int_feature* feature, bool& value, int& value2) {
		detour::protections::g_activity_toggle = value;
		detour::protections::g_activity_integer = value2;
	}
	void network::protection_inf_loadings(toggle_int_feature* feature, bool& value, int& value2) {
		detour::protections::g_inf_loading_toggle = value;
		detour::protections::g_inf_loading_integer = value2;
	}	

	void network::protection_desync(toggle_int_feature* feature, bool& value, int& value2) {
		detour::protections::g_desync_toggle = value;
		detour::protections::g_desync_integer = value2;
		if (STREAMING::IS_PLAYER_SWITCH_IN_PROGRESS()) {
			detour::protections::g_was_force_host_used = false;
		}
		if (!value)
			return;
		memset(&gta_util::get_network()->m_game_complaint_mgr.m_host_tokens_complained, 0, 64 * sizeof(uint64_t));

		if (!globals::get()->m_net_complaint_kicked
			|| !globals::get()->m_net_complaint_kicked->get_net_data())
			gta_util::get_network()->m_game_complaint_mgr.m_num_tokens_complained = 0;
		else
		{
			gta_util::get_network()->m_game_complaint_mgr.m_num_tokens_complained = 1;
			if (gta_util::get_network()->m_game_complaint_mgr.m_host_tokens_complained != nullptr)
				if (globals::get()->m_net_complaint_kicked->get_net_data() != nullptr)
			gta_util::get_network()->m_game_complaint_mgr.m_host_tokens_complained[0] = globals::get()->m_net_complaint_kicked->get_net_data()->m_host_token;
		}
	}


	void network::protection_spammers(toggle_int_feature* feature, bool& value, int& value2) {
		detour::protections::g_spammers_toggle = value;
		detour::protections::g_spammers_integer = value2;
	}	
	void network::protection_cage_protection(toggle_int_feature* feature, bool& value, int& value2) {
		detour::protections::g_cage_toggle = value;
		detour::protections::g_cage_integer = value2;
	}	
	void network::protection_kick_spammers(toggle_feature* feature, bool& value) {
		detour::protections::g_kick_spammers_toggle = value;
	}
	void network::protection_entities_spam(toggle_int_feature* feature, bool& value, int& value2) {
		detour::protections::g_entities_spam_toggle = value;
		detour::protections::g_entities_spam_integer = value2;
	}
	void network::protection_explosion(toggle_int_feature* feature, bool& value, int& value2) {
		detour::protections::g_creating_explosion_toggle = value;
		detour::protections::g_creating_explosion_int = value;
	}
	void network::protection_ptfx(toggle_feature* feature, bool& value) {
		detour::protections::g_creating_ptfx = value;
	}
	void network::protection_label_sms(toggle_feature* feature, bool& value) {
		detour::protections::g_label_sms_toggle = value;
	}
	void network::protection_money_drops(toggle_feature* feature, bool& value) {
		detour::protections::g_detect_drops_toggle = value;
	}

	void network::network_log_chat(toggle_feature* feature, bool& value) {
		detour::protections::g_log_chat_toggle = value;
	}
	void network::network_force_script_host(toggle_feature* feature, bool& value) {
		detour::protections::g_force_script_host_toggle = value;
	}
	void network::protection_block_radio(toggle_feature* feature, bool& value) {
		detour::protections::g_block_radio_requests_toggle = value;
	}
	void network::player_network_magnet(toggle_int_feature* feature, bool& value, int& value2) {
		detour::g_player_magnet_int = value2;
		detour::g_player_magnet_toggle = value;
	}
	void network::network_player_pos_pos(toggle_int_feature* feature, bool& value, int& value2) {
		detour::g_spoof_pos_pos = value;
		detour::g_spoof_pos_pos_int = value2;
	}	
	void network::network_spoof_camera_pos(toggle_feature* feature, bool& value) {
		detour::g_spoof_camera_pos = value;
	}	
	void network::network_spoof_camera_freecam(toggle_int_feature* feature, bool& value, int& value2) {
		detour::g_spoof_freecam = value;
		detour::g_spoof_freecam_int = value2;
	}
	void network::network_spoof_max_health(toggle_int_feature* feature, bool& value, int& value2) {
		detour::g_spoof_max_health = value;
		detour::g_spoof_max_health_int = value2;
	}	
	void network::network_spoof_max_armor(toggle_int_feature* feature, bool& value, int& value2) {
		detour::g_spoof_max_armor = value;
		detour::g_spoof_max_armor_int = value2;
	}
	void network::network_spoof_default_health_armor(toggle_int_feature* feature, bool& value, int& value2) {
		detour::g_spoof_health_armor_default = value;
		detour::g_spoof_health_armor_default_int = value2;
	}	
	void network::network_spoof_collision(toggle_int_feature* feature, bool& value, int& value2) {
		detour::g_spoof_collision = value;
		detour::g_spoof_collision_int = value2;
	}	
	void network::network_spoof_super_jump(toggle_int_feature* feature, bool& value, int& value2) {
		detour::g_spoof_super_jump_int = value;
		detour::g_spoof_super_jump_int = value2;
	}
	void network::network_spoof_spectating(toggle_int_feature* feature, bool& value, int& value2) {
		detour::g_spoof_spectating = value;
		detour::g_spoof_spectating_int = value2;
	}
	void network::network_spoof_god_mode(toggle_int_feature* feature, bool& value, int& value2) {
		detour::g_spoof_god_mode = value;
		detour::g_spoof_god_mode_int = value2;
	}	
	void network::network_spoof_ped_relative(toggle_feature* feature, bool& value) {
		detour::g_spoof_ped_relative = value;
	}	
	void network::network_spoof_player_rotation(toggle_feature* feature, bool& value) {
		detour::g_spoof_player_rotation = value;
	}
	void network::network_spoof_ped_face_direction(toggle_int_feature* feature, bool& value, int& value2) {
		detour::g_spoof_player_face_direction = value;
		detour::g_spoof_player_face_direction_int = value2;
	}
	void network::network_spoof_ped_jitter(toggle_feature* feature, bool& value) {
		detour::g_spoof_spoof_ped_jitter = value;
		if (detour::g_disable_parachute) {
			for (int i = 0; i < 26; i++)
			{
				PED::SET_RAGDOLL_BLOCKING_FLAGS(globals::h_local_ped(), i);
			}

			PED::SET_PED_CAN_RAGDOLL(globals::h_local_ped(), FALSE);
			PED::SET_PED_CAN_RAGDOLL_FROM_PLAYER_IMPACT(globals::h_local_ped(), FALSE);
			PED::SET_PED_CONFIG_FLAG(globals::h_local_ped(), 287, TRUE);

			// If by any chance you are still ragdolled, just get the fuck up?

			// This speeds up the weird falling animation where you're injured
			PED::SET_PED_CONFIG_FLAG(globals::h_local_ped(), 166, FALSE);
			PED::DISABLE_PED_INJURED_ON_GROUND_BEHAVIOUR(globals::h_local_ped());

			// Stop Injured clipset
			PED::RESET_PED_STRAFE_CLIPSET(globals::h_local_ped());
		}
	}
	static bool network_force_host_last = false;
	void network::network_force_host(toggle_feature* feature, bool& value) {
		if (value) {
			if (STREAMING::IS_PLAYER_SWITCH_IN_PROGRESS()) {
				network_force_host_last = false;
				value = false;
				return;
			}
		}
		if (network_force_host_last != value && gta_util::get_network()->m_game_session_state == 0) {
			uint64_t host_token;
			//	caller::call<uint64_t>(insight::pointers::get()->g_generate_uuid(&host_token));
			pointers::get()->g_generate_uuid(&host_token);

			host_token = value ? (rand() % 10000) : host_token;

			*pointers::get()->g_host_token = host_token;

			if (gta_util::get_network()->m_game_session_ptr)
				gta_util::get_network()->m_game_session_ptr->m_local_player.m_player_data.m_host_token = host_token;

			pointers::get()->g_profile_gamer_info->m_host_token = host_token;
			pointers::get()->g_player_info_gamer_info->m_host_token = host_token;
			(*pointers::get()->g_communications)->m_voice.m_connections[0]->m_gamer_info.m_host_token = host_token;

			if (globals::c_local_ped() && globals::c_local_ped()->m_player_info)
				globals::c_local_ped()->m_player_info->m_net_player_data.m_host_token = host_token;
			network_force_host_last = value;
			if (auto netplayer = insight::pointers::get()->g_netplayer(globals::player_id)) {
				if (!netplayer->is_host()) {
					for (int i = 0; i < 32; i++) {
						if (i != globals::player_id) {
							if (auto netplayer = insight::pointers::get()->g_netplayer(i)) {
								if (netplayer->is_host()) {
									network::netbail_kick(i);
									network::null_kick(i);
									network::tse_crash2(i);
								}
							}
						}
					}
				}
			}

		}
	}
}