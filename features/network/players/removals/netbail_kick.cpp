	

#include "cheat/features/tasks.hpp"
#include "cheat/features/globals.hpp"
#include "cheat/features/features.hpp"

#include <network/CNetworkPlayerMgr.hpp>
#include "cheat/features/scripted_globals.hpp"
#include "util/notify/notify.hpp"
#include "util/security/xorstr.hpp"
#include "cheat/features/scripted_globals/scr_globals.hpp"
#include <script/globals/GPBD_FM_3.hpp>
#include "util/gta_util.hpp"
#include <game/gta/net_game_event.hpp>
#include <network/Network.hpp>
#include <network/netConnection.hpp>
#include <network/RemoteGamerInfoMsg.hpp>
#include <game/gta/net_game_event.hpp>
#include "game/rage/packet.hpp"
namespace insight {

	void network::netbail_kick(int i) {
		if (NETWORK::NETWORK_IS_PLAYER_CONNECTED(i)) {
			const size_t arg_count = 3;
			int64_t args[arg_count] = {
			static_cast<int64_t>(eRemoteEvent::NetworkBail),
			globals::player_id,
			(int64_t)scr_globals::gpbd_fm_3.as<GPBD_FM_3*>()->Entries[i].ScriptEventReplayProtectionCounter
			};
			pointers::get()->g_trigger_script_event(1, args, arg_count, 1 << i);
		}
	}
	void network::tse_crash2(int i) {
		if (NETWORK::NETWORK_IS_PLAYER_CONNECTED(i)) {
				const size_t arg_count = 3;
				int64_t args[arg_count] = {
				static_cast<int64_t>(eRemoteEvent::Crash2),
				(int64_t)globals::player_id,
				99999999999999999
				};
				pointers::get()->g_trigger_script_event(1, args, arg_count, 1 << i);
		}
	}
	void network::desync_kick(int i) {
		gta_util::execute_as_script(rage::joaat("main_persistent"), [&] {
			if (auto netplayer = insight::pointers::get()->g_netplayer(i)) {
				if (auto& netmgr = *insight::pointers::get()->g_network_player_mgr) {
					netmgr->RemovePlayer(netplayer);
					tasks::upgrade_player_current_weapon(globals::player_id);
					WEAPON::GIVE_WEAPON_TO_PED(globals::h_local_ped(), 0xFBAB5776, -1, true, true);
					netmgr->UpdatePlayerListsForPlayer(insight::pointers::get()->g_netplayer(globals::player_id));
				}
			}
			});
	}


	void network::breakup_kick(int i, int type)
	{
		if (NETWORK::NETWORK_IS_PLAYER_CONNECTED(globals::player_id) && NETWORK::NETWORK_IS_PLAYER_CONNECTED(i))
		{
			if (tasks::is_player_host(globals::player_id)) {
				if (CNetGamePlayer* player = pointers::get()->g_netplayer(i)) {
					rage::snMsgRemoveGamersFromSessionCmd cmd{};
					cmd.m_session_id = gta_util::get_network()->m_game_session_ptr->m_rline_session.m_session_id;
					cmd.m_num_peers = 1;
					cmd.m_handles[0] = player->get_net_data()->m_gamer_handle;

					if (type == 1)
						cmd.m_unk = 19;

					auto session_player = tasks::get()->get_session_player(player);
					globals::get()->m_net_complaint_kicked = player;
					pointers::get()->g_handle_remove_gamer_cmd(gta_util::get_network()->m_game_session_ptr, session_player, &cmd);
				}
			}
		}
	}


	void packet::send(uint32_t msg_id)
	{
		pointers::get()->g_queue_packet(gta_util::get_network()->m_game_session_ptr->m_net_connection_mgr, msg_id, m_data, (m_buffer.m_curBit + 7) >> 3, 1, nullptr);
	}

	void packet::send_player(int player, int connection_id)
	{
		send_peer(globals::get_network()->m_game_session_ptr->m_players[player]->m_player_data.m_peer_id_2, connection_id);
	}

	void packet::send_peer(int peer_id, int connection_id)
	{
		auto mgr = globals::get_network()->m_game_session_ptr->m_net_connection_mgr;
		auto peer = pointers::get()->g_get_connection_peer(mgr, peer_id);
		pointers::get()->g_send_packet(mgr, &peer->m_peer_address, connection_id, m_data, (m_buffer.m_curBit + 7) >> 3, 0x1000000);
	}

	void network::packet_kick(int i) {
		if (auto net_player = pointers::get()->g_netplayer(i)) {
			packet msg{};

			msg.write_message(rage::eNetMessage::MsgRadioStationSyncRequest);

			auto msg_id = tasks::get()->get_session_player(net_player)->m_msg_id;

			for (int j = 0; j < 2000; j++)
			{
				msg.send(msg_id);
			}
		}
	}


}
