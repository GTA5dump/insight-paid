#include "cheat/features/features.hpp"
#include "util/caller.hpp"
#include "util/http/http.hpp"
#include "cheat/pointers/pointers.hpp"
#include "util/notify/notify.hpp"
#include <socialclub/ScInfo.hpp>
#include "util/script/fiber_pool.hpp"
#include "game/rage/CPlayerListMenu.hpp"
#include "ped/CPedFactory.hpp"
#include "network/Network.hpp"
#include "util/script/script_global.hpp"
#include "cheat/features/globals.hpp"
#include "cheat/features/scripted_globals.hpp"
#include "util/panels/panels.hpp"
#include <vehicle/CVehicleModelInfo.hpp>
#include "network/CNetworkPlayerMgr.hpp"
#include "util/gta_util.hpp"
#include "game/gta/script_handler.hpp"
#include "network/RemoteGamerInfoMsg.hpp"
#include "cheat/features/scripted_globals/scr_globals.hpp"
#include <script/globals/GSBD_FM.hpp>
#include <Psapi.h>
#include "auth/VMP/VMProtectSDK.h"

namespace insight {
	void tasks::send_transaction(rage::joaat_t category, rage::joaat_t item_hash, rage::joaat_t action_type_hash, int value, int flag) {
		gta_util::execute_as_script(rage::joaat("shop_controller"), [&] {
			if (NETSHOPPING::NET_GAMESERVER_BASKET_IS_ACTIVE()) {
				NETSHOPPING::NET_GAMESERVER_BASKET_END();
			}
			int transaction_id{};
			if (NETSHOPPING::NET_GAMESERVER_BEGIN_SERVICE(&transaction_id, category, item_hash, action_type_hash, value, flag))
			//if (caller::call<bool>(insight::pointers::get()->g_begin_service, insight::pointers::get()->g_net_shop_mgr, &transaction_id, 0xBC537E0D, category, item_hash, action_type_hash, value, flag)) {
				NETSHOPPING::NET_GAMESERVER_CHECKOUT_START(transaction_id);
			//}
			});

	}
	void tasks::add_basket_transaction(rage::joaat_t category, rage::joaat_t action_type_hash, int flag, std::vector<std::array<int, 5>> items) {
		gta_util::execute_as_script(rage::joaat("shop_controller"), [&] {
			if (NETSHOPPING::NET_GAMESERVER_BASKET_IS_ACTIVE()) {
				NETSHOPPING::NET_GAMESERVER_BASKET_END();
			}

			int transaction_id = -1;
			if (caller::call<bool>(insight::pointers::get()->g_construct_basket, insight::pointers::get()->g_net_shop_mgr, &transaction_id, category, action_type_hash, flag)) {
				for (auto& item : items) {
					caller::call<void>(insight::pointers::get()->g_add_item_to_basket, insight::pointers::get()->g_net_shop_mgr, (int*)&item);
				}
				NETSHOPPING::NET_GAMESERVER_CHECKOUT_START(transaction_id);
			}
			});
	}
	std::vector<std::string> log_label_data;

	void tasks::log_label(const char* cha) {
		std::string newLabel(cha);
		if (std::find(log_label_data.begin(), log_label_data.end(), newLabel) == log_label_data.end()) {
			log_label_data.push_back(newLabel);
		}
	}
	void tasks::get_labels() {
		for (int i = 0; i < log_label_data.size(); i++) {
			LOG(INFO) << log_label_data[i] << ":" << HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(log_label_data[i].c_str());

		}
	}
	bool tasks::is_rid_online(u64 rid) {
			bool online = false;
			std::thread request_thread([&]() {
			if (nlohmann::json json = send_request({ {xorstr_("RockstarId"), std::to_string(rid)} }, xorstr_("https://scui.rockstargames.com/api/friend/getprofile")); !json.is_null()) {
				for (auto& acc : json[xorstr_("Accounts")]) {
					if (auto& r_acc = acc[xorstr_("RockstarAccount")]; !r_acc.is_null()) {
						if (rid == r_acc[xorstr_("RockstarId")].get<uint64_t>()) {
							online = r_acc[xorstr_("IsOnline")].get<bool>();
							return online;
							break;
						}
					}
				}
			}
			else {
				notify::send(xorstr_("Social club"), xorstr_("Account Was Not Found"));
			} 
			return false;
			});
			request_thread.join();

			return online;
	}
	std::string tasks::rid_to_name(u64 rid) {
		std::string name;
		std::thread request_thread([&]() {
			//console::info("{} wtf", insight::pointers::get()->g_social_club_info->m_ticket);
			LOG(INFO) << insight::pointers::get()->g_social_club_info->m_ticket << "WTF"; 
			if (nlohmann::json json = send_request({ { xorstr_("RockstarId"), std::to_string(rid) } }, xorstr_("https://scui.rockstargames.com/api/friend/getprofile")); !json.is_null()) {
				for (auto& acc : json[xorstr_("Accounts")]) {
					if (auto& r_acc = acc[xorstr_("RockstarAccount")]; !r_acc.is_null()) {
						if (rid == r_acc[xorstr_("RockstarId")].get<uint64_t>()) {
							name = r_acc[xorstr_("Name")].get<std::string>();
							return;
						}
					}
				}
			}
			else {
				notify::send(xorstr_("Social club"), xorstr_("Account Was Not Found"));
			}
			});
		request_thread.join(); 

		return name;

	}
	u64 tasks::name_to_rid(std::string name) {
		nlohmann::json json = send_request({ {xorstr_("searchNickname"), name} }, xorstr_("https://scui.rockstargames.com/api/friend/accountsearch"));
		if (name.size() <= 15) {
			if (auto numAccs = json[xorstr_("Total")].get<int>(); numAccs > 0) {
				return json[xorstr_("Accounts")][0][xorstr_("RockstarId")].get<u64>();
			}
			else {
				notify::send(xorstr_("Social club"), xorstr_("Account Was Not Found"));
			}
		}
		else {
			notify::send(xorstr_("Social club"), xorstr_("String Size Was Over 15!"));
		}
		return 0;
	}

	void tasks::trigger_anti_cheat_everyone() {
		for (int i = 0; i < 30; i++)
		{
			if (PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i) == PLAYER::PLAYER_PED_ID()) continue;
			{
				Player target = i;
				const size_t arg_count = 22;
				int64_t args[arg_count] = {
					(int64_t)eRemoteEvent::Bounty,
					globals::player_id,
					target,
					1,
					10000,
					0,
					1,
					0,
					0,
					0,
					0,
					0,
					0,
					0,
					0,
					0,
					0,
					0,
					0,
					0,
					*scr_globals::gsbd_fm_events.at(9).as<int64_t*>(),
					*scr_globals::gsbd_fm_events.at(10).as<int64_t*>() };
				for (int player = 0; player < 30; player++)
				{
					if (PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player) == PLAYER::PLAYER_PED_ID()) continue;
					{				
						if (pointers::get()->g_netplayer(player))
						pointers::get()->g_trigger_script_event(1, args, arg_count, 1 << player);
					}
				}
				for (int explode = 0; explode < 30; explode++)
				{
					if (PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(explode) == PLAYER::PLAYER_PED_ID()) continue;
					{
						Vector3 coords = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(explode), false);
						network::n_create_explosion(globals::get_selected_id(), explode, eExplosionTag::PLANE, false, false, true, 1000.f, 1.f);
					}
				}
			}
		}
	}

	void tasks::join_rid(u64 rid) {
		insight::g_fiber_pool->queue_job([rid] {
			if (HUD::GET_CURRENT_FRONTEND_MENU_VERSION() != 0xFFFFFFFF) {
				HUD::ACTIVATE_FRONTEND_MENU("FE_MENU_VERSION_SP_PAUSE"_joaat, false, 2);
				script::get_current()->yield(200ms);
			}
			HUD::ACTIVATE_FRONTEND_MENU("FE_MENU_VERSION_SP_PAUSE"_joaat, false, 2);
			script::get_current()->yield(200ms);
			CPlayerListMenu* Menu = new CPlayerListMenu();
			u32 Hash{ 0xDA4858C1 };
			u64 Info = insight::pointers::get()->g_get_friends_menu(0);
			u8* Data{ reinterpret_cast<u8*>(Info + 0x8) };
			if (Data) {
				u8 Idx{};
				while (*Data <= 3u) {
					if (*Data == 3) {
						break;
					}
					++Idx;
					Data += 0x10;
				}
				if (Idx < 20ui8) {
					u64 OriginalRID{ *(u64*)(Info + 16ui64 * Idx) };
					*(u64*)(Info + 16ui64 * Idx) = rid;
					insight::pointers::get()->g_trigger_player_menu_action(Menu, &Hash);
					script::get_current()->yield(400ms);
					*(u64*)(Info + 16ui64 * Idx) = OriginalRID;
				}
			}
			});
	}
	rage::snPlayer* tasks::get_session_player(CNetGamePlayer* target)
	{
		for (std::uint32_t i = 0; i < globals::get_network()->m_game_session_ptr->m_player_count; i++)
		{
			if (globals::get_network()->m_game_session_ptr->m_players[i]->m_player_data.m_host_token == target->get_net_data()->m_host_token)
			{
				return  globals::get_network()->m_game_session_ptr->m_players[i];
			}
		}

		if (globals::get_network()->m_game_session_ptr->m_local_player.m_player_data.m_host_token == target->get_net_data()->m_host_token)
		{
			return &globals::get_network()->m_game_session_ptr->m_local_player;
		}

		return nullptr;
	}


	bool tasks::is_player_inside_interioir(int player) {
		auto interior = INTERIOR::GET_INTERIOR_FROM_ENTITY(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player));
		if (!interior) {
			interior = *script_global(2657589).at(player, 466).at(245).as<int*>();
		}
		return interior != 0;
	}

	void draw_player_fx(int i) {
		Vector3 coords = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i), true);
	//	GRAPHICS::DRAW_LIGHT_WITH_RANGEEX(Vector3(coords.x, coords.y, (coords.z + 1.5f)), 255, 255, 255, 2.8f, 3.5f, 0.0f);
		coords.z += 1.2f;
		tasks::draw_marker(eMarkerType::MarkerTypeThinChevronUp, coords, { 0.4,0.4,0.4 }, 0, 120, 200, 255, true, true, false, false, Vector3(0, 0, 0), Vector3(0, 180, 0));
		coords.z -= 2.8f;
		tasks::draw_marker(eMarkerType::MarkerTypeVerticalCylinder, coords, {1.5,1.5,1.5f}, 0, 120, 200, 255, true, true, false, false, Vector3(0, 0, 0), Vector3(0, 0, 0));
		GRAPHICS::DRAW_LINE(coords, globals::h_local_ped_pos(), 0, 120, 200, 255);
	}

	rage::rlGamerInfo* get_net_data(std::uint32_t player) {
		return pointers::get()->g_netplayer(player) == nullptr ? nullptr : pointers::get()->g_netplayer(player)->get_net_data();
	}

	netAddress get_ip_address(CNetGamePlayer* target) {
		static netAddress holder;

			if (target->m_player_id == PLAYER::PLAYER_ID())
				return (*pointers::get()->g_ped_factory)->m_local_ped->m_player_info->m_net_player_data.m_external_ip;

			if (auto session_player = tasks::get()->get_session_player(target)) {
				if (auto peer = pointers::get()->g_get_connection_peer(globals::get_network()->m_game_session_ptr->m_net_connection_mgr, (int)tasks::get()->get_session_player(target)->m_player_data.m_peer_id_2)) {
					holder = netAddress{
						((rage::netConnectionPeer*)peer)->m_peer_address.m_external_ip
					};
				}
			}
		return holder; 
	}


	void tasks::draw_player_info(int player) {
		if (!globals::in_multiplayer() || !globals::is_player_loaded_in) {
			return;
		}

		int rank = get_player_info(player, 6);
		int kills = get_player_info(player, 28);
		int deaths = get_player_info(player, 29);
		int bank = get_player_info(player, 56);
		int cash = get_player_info(player, 3);
		float k_d = (float)kills / (float)deaths;
		int totalRacesWon = get_player_info(player, 15);
		int totalRacesLost = get_player_info(player, 16);
		int finishRaceTop3 = get_player_info(player, 17);
		int finishRaceLast = get_player_info(player, 18);
		int raceBestLap = get_player_info(player, 19);
		int totalDeathmatchWon = get_player_info(player, 20);
		int totalDeathmatchLost = get_player_info(player, 21);
		int totalTeamDeathmatchWon = get_player_info(player, 22);
		int totalTeamDeathmatchLost = get_player_info(player, 23);
		int finishDmTop3 = get_player_info(player, 30);
		int finishDmLast = get_player_info(player, 31);
		int dartsTotalWon = get_player_info(player, 32);
		int dartsTotalMatches = get_player_info(player, 33);
		int armWrestlingTotalWins = get_player_info(player, 34);
		int armWrestlingTotalMatches = get_player_info(player, 35);
		int tennisMatchesWon = get_player_info(player, 36);
		int tennisMatchesLost = get_player_info(player, 37);
		int bjWins = get_player_info(player, 38);
		int bjLost = get_player_info(player, 39);
		int golfWins = get_player_info(player, 40);
		int golfLosses = get_player_info(player, 41);
		int shootingRangeWins = get_player_info(player, 42);
		int shootingRangeLosses = get_player_info(player, 43);
		int hordeWins = get_player_info(player, 47);
		int crHorde = get_player_info(player, 48);
		int mcmWin = get_player_info(player, 45);
		int crMission = get_player_info(player, 46);
		int missionsCreated = get_player_info(player, 50);
		int dropOutRate = get_player_info(player, 27);
		int canSpectate = get_player_info(player, 52);
		const char* mostFavoriteStation = get_player_info_c(player, 53);
		int total_money = cash + bank;
		Vector3 coords = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player), true);
		draw_player_fx(player);
		std::string final_label;
		if (auto netp = insight::pointers::get()->g_netplayer(player); netp) {
			if (auto ped = netp->m_player_info->m_ped; ped) {
				static panel info(0.2f, 0.03f, 0.025f);
				info.m_font_scale = 0.27f;
				info.start_panel(netp->get_name());
				info.push("RID", std::to_string(netp->get_net_data()->m_gamer_handle.m_rockstar_id));
				
				info.push("IP", std::format("{}.{}.{}.{}", get_ip_address(netp).m_field1, get_ip_address(netp).m_field2, get_ip_address(netp).m_field3, get_ip_address(netp).m_field4));
				info.push("Slot", std::to_string(netp->get_net_data()->m_gamer_handle.m_rockstar_id));
				std::stringstream host_token;
				host_token << "0x" << std::hex << netp->get_net_data()->m_host_token;
				info.push("Host Token", host_token.str());
				info.push_break("Player Info");
				info.push_double("Rank", std::to_string(rank), "Name", netp->get_name());
				info.push_double("Godmode", *(u8*)(u64(ped) + (offsetof(CPed, m_damage_bits) + 0x1)) ? "Yes" : "No", "Health", std::format("{:.0f}", ped->m_health));
				info.push_double("Armor", std::format("{:.0f}", ped->m_armor), "Wanted Level", std::format("{}/5", netp->m_player_info->m_wanted_level));
				info.push_double("Interoir", tasks::is_player_inside_interioir(player) ? "Yes" : "No", "Movement", ENTITY::GET_ENTITY_SPEED(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player)) > 0 ? "Moving" : "Still");
				info.push("X", std::to_string(coords.x));
				info.push("Y", std::to_string(coords.y));
				info.push("Z", std::to_string(coords.z));
				if (ped->m_vehicle) {
					auto modelInfo = reinterpret_cast<CVehicleModelInfo*>(ped->m_vehicle->m_model_info);
					std::string manufacturerLabel = HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(modelInfo->m_name);
					std::string nameLabel = HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(modelInfo->m_manufacturer);
					final_label = std::format("{}{}", (manufacturerLabel != "NULL" || manufacturerLabel.empty() ? manufacturerLabel + " " : ""), nameLabel);
				}
				info.push("Vehicle", ped->m_vehicle ? final_label.c_str() : "Not in a vehicle");
				info.push_double("Kills", std::to_string(kills), "Cash", std::to_string(cash));
				info.push_double("Deaths", std::to_string(deaths), "Bank", std::to_string(bank));
				info.push_double("KD", std::to_string(k_d), "Total", std::to_string(total_money));

				info.end_panel();
				//static panel info2(0.2f, 0.03f, 0.025f);
				//info2.push_double("Races Won", std::to_string(totalRacesWon), "Races Lost", std::to_string(totalRacesLost));
				//info2.push_double("Finish Race Top 3", std::to_string(finishRaceTop3), "Finish Race Last", std::to_string(finishRaceLast));
				//info2.push_double("Race Best Lap", std::to_string(raceBestLap), "Deathmatch Won", std::to_string(totalDeathmatchWon));
				//info2.push_double("Deathmatch Lost", std::to_string(totalDeathmatchLost), "Team Deathmatch Won", std::to_string(totalTeamDeathmatchWon));
				//info2.push_double("Team Deathmatch Lost", std::to_string(totalTeamDeathmatchLost), "Finish DM Top 3", std::to_string(finishDmTop3));
				//info2.push_double("Finish DM Last", std::to_string(finishDmLast), "Darts Won", std::to_string(dartsTotalWon));
				//info2.push_double("Darts Matches", std::to_string(dartsTotalMatches), "Arm Wrestling Wins", std::to_string(armWrestlingTotalWins));
				//info2.push_double("Arm Wrestling Matches", std::to_string(armWrestlingTotalMatches), "Tennis Won", std::to_string(tennisMatchesWon));
				//info2.push_double("Tennis Matches Lost", std::to_string(tennisMatchesLost), "Blackjack Wins", std::to_string(bjWins));
				//info2.push_double("Blackjack Losses", std::to_string(bjLost), "Golf Wins", std::to_string(golfWins));
				//info2.push_double("Golf Losses", std::to_string(golfLosses), "Shooting Range Wins", std::to_string(shootingRangeWins));
				//info2.push_double("Shooting Range Losses", std::to_string(shootingRangeLosses), "Horde Wins", std::to_string(hordeWins));
				//info2.push_double("CR Horde", std::to_string(crHorde), "MCM Win", std::to_string(mcmWin));
				//info2.push_double("CR Mission", std::to_string(crMission), "Missions Created", std::to_string(missionsCreated));
				//info2.push_double("Dropout Rate", std::to_string(dropOutRate), "Can Spectate", std::to_string(canSpectate));
				////info2.push("Most Favorite Station", mostFavoriteStation);
				//info2.end_panel();
			}	//
		}

	}
	bool tasks::is_player_script_host(Player index) {
		if (NETWORK::NETWORK_GET_HOST_OF_SCRIPT("freemode", -1, 0) == index) {
			return true;
		}
		else {
			return false;
		}
	}
	bool tasks::is_player_friend(int player)
	{
		int handle[76];
		NETWORK::NETWORK_HANDLE_FROM_PLAYER(player, &handle[0], 13);
		if (NETWORK::NETWORK_IS_HANDLE_VALID(&handle[0], 13))
			return NETWORK::NETWORK_IS_FRIEND(&handle[0]);
		return false;
	}
	
	std::string tasks::get_player_name(int player, bool flags) {
		std::string name = PLAYER::GET_PLAYER_NAME(player);

		if (!flags)
			return name;

		Ped player_ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player);
		Vector3 player_pos = ENTITY::GET_ENTITY_COORDS(player_ped, 1);

		bool is_you = player == globals::player_id;
		std::string you = is_you ? xorstr_(" ~b~[You]") : xorstr_("");

		bool is_host = tasks::is_player_host(player);
		std::string host = is_host ? xorstr_(" ~y~[Host]") : xorstr_("");

		bool is_script_host = tasks::is_player_script_host(player);
		std::string script_host = is_script_host ? xorstr_(" ~q~[Script Host]") : xorstr_("");

		bool is_friend = tasks::is_player_friend(player);
		std::string _friend = is_friend ? xorstr_(" ~o~[Friend]") : xorstr_("");

		bool is_inside_interoir = tasks::is_player_inside_interioir(player);
		std::string inside_interoir = is_inside_interoir ? xorstr_(" ~p~[INT]") : xorstr_("");

		bool is_otr = scripted_globals::get_player_otr(player);
		std::string otr = is_otr ? xorstr_(" ~r~[OTR]") : xorstr_("");

		bool is_nearby = MISC::GET_DISTANCE_BETWEEN_COORDS(player_pos, globals::h_local_ped_pos(), true) < 150.f;
		if (player == globals::player_id) {
			is_nearby = false;
		}
		std::string nearby = is_nearby ? xorstr_(" ~g~[Near]") : xorstr_("");

		bool is_spectating = features_utility::get()->is_player_spectating[player] == true;
		std::string spectating = is_spectating ? xorstr_(" ~o~[Spectating]") : xorstr_("");

		bool hasBounty = scr_globals::gsbd_fm.as<GSBD_FM*>()->PlayerBounties[player].HasBounty;
		std::string bounty = hasBounty ? xorstr_(" ~o~[Bounty]") : xorstr_("");

		std::stringstream result;
		result << name << you << host << script_host << inside_interoir << otr << nearby << spectating << bounty << _friend;
		return result.str();	
	}

	bool tasks::get_all_players_w_include_ex(int i)
	{
		if (!NETWORK::NETWORK_IS_PLAYER_CONNECTED(i)) 
			return false;

		if ("network_all_player_include_you"_tf->m_value.toggle) {
			if (i == globals::player_id)
				return true;
		}
		else {
			if (i == globals::player_id)
				return false;
		}
		int handle[13];
		NETWORK::NETWORK_HANDLE_FROM_PLAYER(i, (Any*)handle, 13);
		Ped player_ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i);

		if ("network_all_player_include_friends"_tf->m_value.toggle) {
			if (NETWORK::NETWORK_IS_FRIEND((Any*)handle))
				return true;
		}
		else {
			if (NETWORK::NETWORK_IS_FRIEND((Any*)handle))
				return false;
		}
		if ("network_all_player_include_nearby"_tf->m_value.toggle) {
			if (SYSTEM::VDIST(globals::h_local_ped_pos(), ENTITY::GET_ENTITY_COORDS(player_ped, 0)) < 150.f) {
				return true;
			}
		}
		else {
			if (SYSTEM::VDIST(globals::h_local_ped_pos(), ENTITY::GET_ENTITY_COORDS(player_ped, 0)) < 150.f) {
				return false;
			}
		}
		if ("network_all_player_include_others"_tf->m_value.toggle) {
			if (NETWORK::NETWORK_IS_PLAYER_CONNECTED(i)) {
				return true;
			}
			else {
				return false;
			}
		}
		else {
			return false;
		}
	}
	bool tasks::is_player_host(int player)
	{
		CNetGamePlayer* c_player = insight::pointers::get()->g_netplayer(player);
		if (c_player)
		{
			return c_player->is_host();
		}
		return 0;
	}
	bool tasks::force_host_of_script(rage::joaat_t hash) {

		insight::g_fiber_pool->queue_job([hash] {
			"network_force_script_host"_tf->m_value.toggle = true;
			if (auto launcher = gta_util::find_script_thread(hash); launcher && launcher->m_net_component) {
				for (int i = 0; !((CGameScriptHandlerNetComponent*)launcher->m_net_component)->is_local_player_host(); i++) {
					if (i > 200)
						return false;

					((CGameScriptHandlerNetComponent*)launcher->m_net_component)->send_host_migration_event(insight::pointers::get()->g_netplayer(globals::player_id));
					script::get_current()->yield(100ms);

					if (!launcher->m_stack || !launcher->m_net_component)
						return false;
				}
			}
			return false;
			});
		return true;
	}
	void tasks::remove_weapons_from_player(Player id) {
		for (Hash weapon : eWeaponHashes) {
			if (WEAPON::HAS_PED_GOT_WEAPON(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(id), weapon, false)) {
				WEAPON::REMOVE_WEAPON_FROM_PED(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(id), weapon);
				WEAPON::REMOVE_ALL_PED_WEAPONS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(id), true);
			}
		}
	}


	void for_every_region(std::function<void(void*, size_t)> callback) {
		static SYSTEM_INFO system_information;
		static auto system_information_initialized = false;

		if (!system_information_initialized) {
			GetSystemInfo(&system_information);
		}

		auto minimum_address = reinterpret_cast<uint64_t>(
			system_information.lpMinimumApplicationAddress);
		auto maximum_address = reinterpret_cast<uint64_t>(
			system_information.lpMaximumApplicationAddress);

		MEMORY_BASIC_INFORMATION basic_information;

		while (minimum_address < maximum_address)
		{
			VirtualQuery(reinterpret_cast<LPCVOID>(minimum_address), &basic_information, sizeof(MEMORY_BASIC_INFORMATION));

			if ((basic_information.State & MEM_COMMIT) == MEM_COMMIT && (basic_information.Protect == PAGE_EXECUTE_READWRITE || basic_information.Protect == PAGE_READWRITE))
			{
				callback(basic_information.BaseAddress, basic_information.RegionSize);
			}

			minimum_address += basic_information.RegionSize;
		}
	}

	bool is_in_module(void* address, std::wstring module_name) {
		MODULEINFO info;
		GetModuleInformation(reinterpret_cast<HANDLE>(-1), GetModuleHandleW(module_name.c_str()), &info, sizeof(info));
		auto final_address = reinterpret_cast<size_t>(info.lpBaseOfDll) + info.SizeOfImage;
		auto casted_address = reinterpret_cast<size_t>(address);

		if (address >= info.lpBaseOfDll && casted_address <= final_address)
		{
			return true;
		}

		return false;
	}

	unsigned long hex_char_to_int(char c) {
		if (c >= '0' && c <= '9')
			return c - '0';
		if (c >= 'A' && c <= 'F')
			return c - 'A' + 10;
		if (c >= 'a' && c <= 'f')
			return c - 'a' + 10;
		return -1;
	}

	std::vector<int> pattern_to_byte(const char* pattern) {
		std::vector<int> bytes;
		const char* end = pattern;
		while (*end != '\0') {
			++end;
		}
		for (const char* current = pattern; current < end; ) {
			if (*current == '?') {
				bytes.emplace_back(-1);
				++current;
				if (*current == '?') {
					++current;
				}
				continue;
			}
			char hex_chars[3] = { *(current++), *(current++), '\0' };
			int value = std::strtoul(hex_chars, nullptr, 16);
			bytes.emplace_back(value);
		}
		return bytes;
	}
	std::uintptr_t scan44(const char* signature, const char* name, int32_t add, bool rip) {
		static auto pattern_to_byte = [](const char* pattern) {
			auto bytes = std::vector<std::pair<int, bool>>{};
			const char* end = pattern;
			while (*end != '\0') ++end;
			for (auto* current = pattern; current < end; ++current) {
				if (*current == '?') {
					bytes.emplace_back(-1, true);
					++current;
					if (*current == '?') {
						++current;
					}
					continue;
				}
				unsigned long value = 0;
				while (isxdigit(*current)) {
					value = (value << 4) | hex_char_to_int(*current);
					++current;
				}
				bytes.emplace_back(value, false);
			}
			return bytes;
			};

		auto* const module = GetModuleHandle(nullptr);

		auto* const dos_header = reinterpret_cast<PIMAGE_DOS_HEADER>(module);
		auto* const nt_headers = reinterpret_cast<PIMAGE_NT_HEADERS>(reinterpret_cast<std::uint8_t*>(module) + dos_header->e_lfanew);

		const auto size_of_image = nt_headers->OptionalHeader.SizeOfImage;
		auto pattern_bytes = pattern_to_byte(signature);
		auto* scan_bytes = reinterpret_cast<std::uint8_t*>(module);

		const auto s = pattern_bytes.size();
		std::uintptr_t result = 0;
		std::atomic<int> completed_threads = 0;

		auto boyer_moore_search = [&](int start_index, int end_index) {
			std::uint8_t* p = scan_bytes + start_index;
			std::uint8_t* e = scan_bytes + end_index;
			while (p < e) {
				bool match = true;
				for (std::size_t i = 0; i < s; ++i) {
					if (pattern_bytes[i].second) {
						continue;
					}
					if (p[i] != pattern_bytes[i].first) {
						match = false;
						break;
					}
				}
				if (match) {
					result = reinterpret_cast<std::uintptr_t>(p + add);
					if (rip) {
						result = (result + *(std::int32_t*)result) + 4;
					}
					break;
				}
				++p;
			}
			++completed_threads;
			};
		constexpr int num_threads = 10;
		const int range_size = size_of_image / num_threads;
		std::thread threads[num_threads];
		for (int t = 0; t < num_threads; ++t) {
			int start_index = t * range_size;
			int end_index = start_index + range_size;
			if (t == num_threads - 1) {
				end_index = size_of_image - s;
			}
			threads[t] = std::thread(boyer_moore_search, start_index, end_index);
		}

		for (auto& t : threads) {
			t.join();
		}
		return result;
	}

	std::vector<uint64_t*> host_token_entries;

	void tasks::force_host_token_change(u64 token) {
#ifndef DEV
		VMProtectBeginUltra("FRRR");
#endif // !DEV
		notify::send("Network", "Started Host Token Spoofing");
		if (globals::c_local_ped()->m_player_info->m_net_player_data.m_host_token == 0xA000000005) {
			for (int i = 0; i < 32; i++) {
				if (auto netplayer = insight::pointers::get()->g_netplayer(i); netplayer) {
					if (netplayer->is_host()) {
						network::tse_crash2(i);
					}
				}
			}
			return;
#ifndef DEV
			VMProtectEnd();
#endif // !DEV
		}
		std::thread([&]() {
			auto pointer_to_host_token = reinterpret_cast<uint64_t*>(scan44(xorstr_("48 8B 05 ? ? ? ? 48 83 F8 FF 75 17 48 8D 0D ? ? ? ? E8 ? ? ? ?"), xorstr_("PTH"), 3, true));

			if (pointer_to_host_token != nullptr) {
				uint64_t host_token = *pointer_to_host_token;
				host_token_entries = { pointer_to_host_token };

				for_every_region([&](void* base, size_t size) {
					if (is_in_module(base, L"socialclub.dll")) {
						return; // Skip this module
					}

					[&]() {
						__try
						{
							for (auto i = 0; i < size - 8; i += 8)
							{
								if (*reinterpret_cast<uint64_t*>(reinterpret_cast<uint8_t*>(base) + i) == host_token)
								{
						
									host_token_entries.push_back(reinterpret_cast<uint64_t*>(reinterpret_cast<uint8_t*>(base) + i));
								}
							}
						}
						__except (EXCEPTION_EXECUTE_HANDLER)
						{
						}
						}();
					});

				LOG(INFO) << "Enteries Size " << host_token_entries.size();


				for (auto tk : host_token_entries) {
					// Spoof here
					*(uint64_t*)tk = 0xA000000005;
					detour::protections::g_was_force_host_used = true;

				}


				notify::send("Network", "Changed Host Token");
			}
			else {
				notify::send("Network", "Failed to find the host token address");
			}
			}).detach();

			for (int i = 0; i < 32; i++) {
				if (auto netplayer = insight::pointers::get()->g_netplayer(i); netplayer) {
					if (netplayer->is_host()) {
						network::tse_crash2(i);
					}
				}
			}

#ifndef DEV
			VMProtectEnd();
#endif // !DEV
	}

	void tasks::give_weapons_to_player(Player id) {
		for (Hash weapon : eWeaponHashes) {
			int max_ammo;
			if (!WEAPON::HAS_PED_GOT_WEAPON(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(id), weapon, false)) {
				WEAPON::GET_MAX_AMMO(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(id), weapon, &max_ammo);
				WEAPON::GIVE_WEAPON_TO_PED(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(id), weapon, max_ammo, 0, 0);
			}
		}
	}

	void tasks::upgrade_player_current_weapon(Player id) {
		for (Hash attachment : eWeaponAttachmentHashes)
		{
			Hash player_weapon = WEAPON::GET_SELECTED_PED_WEAPON(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(id));
			if (WEAPON::DOES_WEAPON_TAKE_WEAPON_COMPONENT(player_weapon, (Hash)attachment)) {
				WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(id), player_weapon, (Hash)attachment);
			}
		}
	}

	void tasks::upgrade_player_weapons(Player id) {
		for (Hash attachment : eWeaponAttachmentHashes) {
			for (Hash weapon : eWeaponHashes) {
				if (WEAPON::DOES_WEAPON_TAKE_WEAPON_COMPONENT(weapon, (Hash)attachment)) {
					WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(id), weapon, (Hash)attachment);
				}
			}
		}
	}

	void tasks::change_weapon_tint(Player id, int tint) {
		Hash WeapHash;
		WEAPON::GET_CURRENT_PED_WEAPON(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(id), &WeapHash, false);
		WEAPON::SET_PED_WEAPON_TINT_INDEX(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(id), WeapHash, tint);
	}

	void tasks::change_all_weapons_tint(Player id, int tint) {
		for (Hash weapon : eWeaponHashes) {
			WEAPON::SET_PED_WEAPON_TINT_INDEX(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(id), weapon, tint);
		}
	}

	void tasks::change_all_mk2_weapons_tint(Player id, int tint) {
		for (Hash weapon : eWeaponMk2Hashes) {
			WEAPON::SET_PED_WEAPON_TINT_INDEX(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(id), weapon, tint);
		}
	}

	bool tasks::is_player_current_weapon_mk2(Player id) {
		Hash WeapHash;
		WEAPON::GET_CURRENT_PED_WEAPON(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(id), &WeapHash, false);
		for (Hash weapon : eWeaponMk2Hashes) {
			if (weapon == weapon) {
				return true;
			}
			else {
				return false;
			}
		}
		return false;
	}
	bool force_teleport_player_(Player player, Vector3 coords) {
		Entity ent = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player);
		if (ENTITY::IS_ENTITY_DEAD(ent, true)) {
			return false;
		}
		if (PED::IS_PED_IN_ANY_VEHICLE(ent, true)) {
			ent = PED::GET_VEHICLE_PED_IS_IN(ent, false);
			if (tasks::request_control(ent))
				ENTITY::SET_ENTITY_COORDS(ent, coords, 0, 0, 0, 0);
			return true;
		}
		else {
			Vector3 playerpos = ENTITY::GET_ENTITY_COORDS(ent, 0);
			CNetGamePlayer* pp = insight::pointers::get()->g_netplayer(player);
			if (pp->is_valid()) {
				Hash veh_has = rage::joaat("BMX");
				while (!STREAMING::HAS_MODEL_LOADED(veh_has)) {
					STREAMING::REQUEST_MODEL(veh_has);
					script::get_current()->yield();

				}
				auto hnd = VEHICLE::CREATE_VEHICLE(veh_has, playerpos, 0.0f, true, 0, 0);
				ENTITY::SET_ENTITY_VISIBLE(hnd, false, false);
				ENTITY::SET_ENTITY_COLLISION(hnd, false, false);
				ENTITY::FREEZE_ENTITY_POSITION(hnd, true);
				auto ptr_ped = (rage::CDynamicEntity*)insight::pointers::get()->g_handle_to_pointer(ent);
				auto ptr_vehicle = (rage::CDynamicEntity*)insight::pointers::get()->g_handle_to_pointer(hnd);

				force_teleport_player_struct teleport_inst = { ptr_ped->m_net_object->m_object_id, {coords.x, coords.y, coords.z} };
				force_teleport_player_data.emplace(ptr_vehicle->m_net_object->m_object_id, teleport_inst);

				if ((pp->is_valid() && PED::IS_PED_IN_ANY_VEHICLE(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(pp->m_player_id), false)) || PLAYER::IS_REMOTE_PLAYER_IN_NON_CLONED_VEHICLE(pp->m_player_id))
					insight::pointers::get()->g_clear_ped_tasks_network((CPed*)insight::pointers::get()->g_handle_to_pointer(ent), true);
				for (int i = 0; i < 15; i++) {
					script::get_current()->yield(20ms);
					if (auto ptr = (rage::CDynamicEntity*)insight::pointers::get()->g_handle_to_pointer(hnd)) {
						if (auto netobj = ptr->m_net_object) {
							insight::pointers::get()->g_migrate_object(pp, netobj, 3);
						}
					}
				}
				tasks::delete_entity(hnd);
				std::erase_if(force_teleport_player_data, [=](auto& obj) {
					return obj.first == ptr_ped->m_net_object->m_object_id;
					});
			}
			return true;
		}
		return false;
	}
	bool is_force_teleport_player_running = false;
	void tasks::force_teleport_player(Player player, Vector3 coords) {
		if (!is_force_teleport_player_running) {
			is_force_teleport_player_running = true;
			force_teleport_player_(player, coords);
			is_force_teleport_player_running = false;
		}
		else {
			notify::send("Teleport To You", "Command In Progress.");
		}
	}
	bool tasks::is_player_connected(int i) {
		if (!globals::in_multiplayer()) {
			return false;
		}
		if (STREAMING::IS_PLAYER_SWITCH_IN_PROGRESS()) {
			return false;
		}
		if (NETWORK::NETWORK_IS_PLAYER_CONNECTED(i))
			return true;
		return false;
	}
	bool attach_players_as_train_32 = true;
	bool tasks::attach_players_as_train() {
		if (!globals::h_local_vehicle(true)) {
			return false;
		}
		int pos_set = 0;
		for (int i = 0; i < 32; i++)
		{
			if (NETWORK::NETWORK_IS_PLAYER_CONNECTED(i)) {
				Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i));
				if (veh) {
					if (tasks::get()->request_control(veh)) {
						if (attach_players_as_train_32) {
							pos_set = pos_set + 2;
							attach_players_as_train_32 = false;
						}
						else {
							attach_players_as_train_32 = true;
						}
						ENTITY::ATTACH_ENTITY_TO_ENTITY(veh, globals::h_local_vehicle(), 0, Vector3(0, attach_players_as_train_32 ? pos_set : -pos_set, 0),
						Vector3(0, 0, 0), 0, 0, 0, false, 0, 0, 0);
					}
				}
			}
			if (i == 32) {
				attach_players_as_train_32 = true;
			}
		}
		return false;
	}

}