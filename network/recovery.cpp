#include "cheat/script/script.hpp"
#include "cheat/menu/helper/ui.hpp"
#include "util/panels/panels.hpp"
#include "util/config/config.hpp"
#include "cheat/features/scripted_globals.hpp"
#include "util/script/script_global.hpp"
#include "util/timer.hpp"

namespace insight {
	int m_recovery_casino_heist_approch_;
	std::string m_recovery_casino_heist_approch[] = {
		"Stealth","Trickery","Loud"
	};	
	int m_recovery_casino_heist_target_;
	std::string m_recovery_casino_heist_target[] = {
		"Money","Gold","Art","Diamonds"
	};
	void Casio_Heist_Editor(int step, int typeofheist, int whattosteal, int confirmheist)
	{
		if (step == 1) {
			STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("H3OPT_APPROACH ")), typeofheist, TRUE);
			STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("H3OPT_TARGET")), whattosteal, TRUE);

		}
		else if (step == 2) {
			STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("H3OPT_BITSET1")), confirmheist, TRUE);

		}
		else if (step == 3) {
			STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("H3OPT_DISRUPTSHIP")), 3, TRUE);
			STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("H3OPT_KEYLEVELS")), 2, TRUE);
			STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("H3OPT_CREWWEAP")), 5, TRUE);
			STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("H3OPT_CREWDRIVER")), 5, TRUE);
			STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("H3OPT_CREWHACKER")), 5, TRUE);
			STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("H3OPT_VEHS")), 4, TRUE);
			STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("H3OPT_WEAPS")), 1, TRUE);

		}
		else if (step == 4) {
			STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("H3OPT_BITSET0")), confirmheist, TRUE);

		}
	}
	int m_recovery_cayo_heist_difficulty_;
	std::string m_recovery_cayo_heist_difficulty[] = {
	"Normal","Hard"
	};
	int m_recovery_cayo_heist_target_;
	std::string m_recovery_cayo_heist_target[] = {
	"Tequila ~g~(N900K)~y~(H990k)"," Ruby Necklace ~g~(N1M)~y~(H1.1M)","Bearer Bonds ~g~(N1.1M)~y~(H1.21M)","Pink Diamond ~g~(N1.3M)~y~(H1.43M)","Madrazo Files ~g~(N 1.1M)~y~(Hunk)","Sapphire Panther ~g~(N1.9M)~y~(H2.09M)"
	};
	int m_recovery_cayo_heist_weapon_variations_;
	std::string m_recovery_cayo_heist_weapon_variations[] = {
	"Aggressor","Conspirator","Crackshot","Saboteur","Marksman"
	};
	int m_recovery_cayo_heist_supply_truck_;
	std::string m_recovery_cayo_heist_supply_truck[] = {
	"Airport","N0rth Dock","Main Dock - East","Main Dock - West","Inside Compound"
	};
	int m_recovery_cayo_heist_cash_value = 1000;
	int m_recovery_cayo_heist_weed_value = 2000;
	int m_recovery_cayo_heist_coke_value = 3000;
	int m_recovery_cayo_heist_gold_value = 100000;
	int m_recovery_cayo_heist_painting_value = 100000;
	struct add_int_stat_dat
	{
		std::string option_name;
		const char* stat;
		int val = 0;
	};
	std::vector<add_int_stat_dat> add_int_stat_data{
		{"Races Won", "MPPLY_TOTAL_RACES_WON"},
		{"Races Lost", "MPPLY_TOTAL_RACES_LOST"},
		{"Basejump Won", "MPPLY_BJ_WINS"},
		{"Basejump Lost", "MPPLY_BJ_LOST"},
		{"Deathmatch Won", "MPPLY_TOTAL_DEATHMATCH_WON"},
		{"Deathmatch Lost", "MPPLY_TOTAL_DEATHMATCH_LOST"},
		{"Team Deathmatch Won", "MPPLY_TOTAL_TDEATHMATCH_WON"},
		{"Team Deathmatch Lost", "MPPLY_TOTAL_TDEATHMATCH_LOST"},
		{"Darts Total Won", "MPPLY_DARTS_TOTAL_WINS"},
		{"Darts Total Matches", "MPPLY_DARTS_TOTAL_MATCHES"},
		{"Arm Wrestling Won", "MPPLY_ARMWRESTLING_TOTAL_WINS"},
		{"Arm Wrestling Matches", "MPPLY_ARMWRESTLING_TOTAL_MATCH"},
		{"Tennis Matches Won", "MPPLY_TENNIS_MATCHES_WON"},
		{"Tennis Matches Lost", "MPPLY_TENNIS_MATCHES_LOST"},
		{"Golf Won", "MPPLY_GOLF_WINS"},
		{"Golf Lost", "MPPLY_GOLF_LOSSES"},
		{"Shooting Range Won", "MPPLY_SHOOTINGRANGE_WINS"},
		{"Shooting Range Lost", "MPPLY_SHOOTINGRANGE_LOSSES"}
	};
	void add_int_stat(sub* ui, add_int_stat_dat& d) {
		timer delayed_update(std::chrono::milliseconds(5000));
		if (delayed_update.update())
			STATS::STAT_GET_INT(rage::joaat(d.stat), &d.val, -1);
		ui->push(number<int>(d.option_name).add_number(&d.val).add_min(0).add_max(99999).add_precision(1).add_step(1).set_action([=] {
			STATS::STAT_SET_INT(rage::joaat(d.stat), d.val, TRUE);
			LOG(INFO) << d.stat << " d " << d.val;
			}));

	}
	struct add_float_stat_dat
	{
		std::string option_name;
		const char* stat;
		float val = 0.f;
	};
	std::vector<add_float_stat_dat> add_float_stat_data{
		{"KD", "MPPLY_KILL_DEATH_RATIO"}
	};

	void add_float_stat(sub* ui, add_float_stat_dat& d) {
		timer delayed_update(std::chrono::milliseconds(5000));
		if (delayed_update.update()) {
			STATS::STAT_GET_FLOAT(rage::joaat(d.stat), &d.val, -1);
			LOG(INFO) << d.stat << " d " << d.val;
		}
		ui->push(number<float>(d.option_name).add_number(&d.val).add_min(0).add_max(99999).add_precision(2).add_step(0.01).set_action([=] {
			STATS::STAT_SET_FLOAT(rage::joaat(d.stat), d.val, TRUE);
			}));

	}
}
namespace insight {
	void script_ui::network_recovery() {
		render::push<sub>("Recovery", "Network_Recovery"_joaat, [](sub* ui) {
			ui->push(submenu("Money").add_target("Network_Recovery_Money"_joaat)); 
			ui->push(submenu("Ranks").add_target("Network_Recovery_Rank"_joaat));
			ui->push(submenu("Inventory").add_target("Network_Recovery_Inventory"_joaat));
			ui->push(submenu("Heists").add_target("Network_Recovery_Heist"_joaat));
			ui->push(submenu("Unlocks").add_target("Network_Recovery_Unlock"_joaat));
			ui->push(submenu("Modify").add_target("Network_Recovery_Modify"_joaat));
			ui->push(info("Clear"));
			ui->push(button(xorstr_("Badsports")).set_action([] {
				DWORD date[12];
				STATS::STAT_SET_BOOL(rage::joaat(xorstr_("MPPLY_CHAR_IS_BADSPORT")), 0, 1);
				STATS::STAT_SET_INT(rage::joaat(xorstr_("MP0_BAD_SPORT_BITSET")), 0, 1);
				STATS::STAT_SET_INT(rage::joaat(xorstr_("MP1_BAD_SPORT_BITSET")), 0, 1);
				STATS::STAT_SET_DATE(rage::joaat(xorstr_("MPPLY_BECAME_BADSPORT_DT")), (Any*)&date[0], 7, 1);
				}));
			ui->push(button(xorstr_("Reset Mental State")).set_action([] {
				STATS::STAT_SET_FLOAT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("PLAYER_MENTAL_STATE")), 0.0, true);
				}));
			ui->push(button(xorstr_("Skip Tutorial")).set_action([] {
				STATS::STAT_SET_BOOL(rage::joaat(scripted_globals::get_character_stats() + xorstr_("NO_MORE_TUTORIALS")), 1, 1);
				}));
			ui->push(info("Others"));

			ui->push(button(xorstr_("Unlock Permanent Fast Run")).set_action([] {
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CHAR_ABILITY_1_UNLCK")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CHAR_ABILITY_2_UNLCK")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CHAR_ABILITY_3_UNLCK")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CHAR_FM_ABILITY_1_UNLCK")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CHAR_FM_ABILITY_2_UNLCK")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CHAR_FM_ABILITY_3_UNLCK")), -1, 1);
				notify::send("Permanent Fast Run", "Sprint at lightning speed always. Join new lobby to apply.");
				}));	
			ui->push(button(xorstr_("Redesign Character")).set_action([] {
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("FM_CHANGECHAR_ASKED")), 0, 1);
				notify::send("Redesign Character", "Join new lobby to apply.And You Will Get Popup.");
				}));
			ui->push(button(xorstr_("Max Skills")).set_action([] {
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("SCRIPT_INCREASE_STAM")), 100, 0);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("SCRIPT_INCREASE_STRN")), 100, 0);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("SCRIPT_INCREASE_LUNG")), 100, 0);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("SCRIPT_INCREASE_DRIV")), 100, 0);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("SCRIPT_INCREASE_FLY")), 100, 0);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("SCRIPT_INCREASE_SHO")), 100, 0);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("SCRIPT_INCREASE_STL")), 100, 0);			
				}));

		});
		render::push<sub>("Inventory", "Network_Recovery_Inventory"_joaat, [](sub* ui) {
			ui->push(button(xorstr_("Fill Snacks")).set_action([] {
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("NO_BOUGHT_YUM_SNACKS")), 30, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("NO_BOUGHT_HEALTH_SNACKS")), 15, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("NO_BOUGHT_EPIC_SNACKS")), 5, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("NUMBER_OF_CHAMP_BOUGHT")), 5, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("NUMBER_OF_ORANGE_BOUGHT")), 11, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CIGARETTES_BOUGHT")), 20, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("NUMBER_OF_BOURGE_BOUGHT")), 10, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("NUMBER_OF_SPRUNK_BOUGHT")), 5, 1);
				
				}));
			ui->push(button(xorstr_("Fill Armors")).set_action([] {
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("MP_CHAR_ARMOUR_1_COUNT")), 5, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("MP_CHAR_ARMOUR_2_COUNT")), 5, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("MP_CHAR_ARMOUR_3_COUNT")), 5, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("MP_CHAR_ARMOUR_4_COUNT")), 5, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("MP_CHAR_ARMOUR_5_COUNT")), 5, 1);
				}));
			ui->push(button(xorstr_("Fill Rebreathers")).set_action([] {
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("BREATHING_APPAR_BOUGHT")), 20, 1);
				}));

			});
		render::push<sub>("Heists", "Network_Recovery_Heist"_joaat, [](sub* ui) {
			ui->push(submenu("Apartment").add_target("Network_Recovery_Heist_Apartment"_joaat));
			ui->push(submenu("Casino").add_target("Network_Recovery_Heist_Casino"_joaat));
			ui->push(submenu("Cayo").add_target("Network_Recovery_Heist_Cayo"_joaat));

			});
		render::push<sub>("Apartment", "Network_Recovery_Heist_Apartment"_joaat, [](sub* ui) {


			//Global_1938365.f_3008[1+iVar0*1]
			ui->push(info("Cuts"));
			for (int i = 0; i < 4; ++i) {
				int& cut = *script_global(1938365 + 3008+ (1 + i * 1)).as<int*>();
				ui->push(number<int>("Player " + std::to_string(i)).add_number(&cut).add_min(0).add_max(100).add_precision(1).add_step(1).set_action([] {}));
			}
			});
		render::push<sub>("Casino", "Network_Recovery_Heist_Casino"_joaat, [](sub* ui) {
			ui->push(array<std::string, int>("Preps Approch").add_array(&m_recovery_casino_heist_approch).add_position(&m_recovery_casino_heist_approch_));
			ui->push(array<std::string, int>("Preps Target").add_array(&m_recovery_casino_heist_target).add_position(&m_recovery_casino_heist_target_));
			ui->push(button(xorstr_("Skip & Confirm Heist Preps")).set_action([] {
				Casio_Heist_Editor(1, m_recovery_casino_heist_approch_, m_recovery_casino_heist_target_, 0);
				Casio_Heist_Editor(2, m_recovery_casino_heist_approch_, m_recovery_casino_heist_target_, -1);
				Casio_Heist_Editor(3, m_recovery_casino_heist_approch_, m_recovery_casino_heist_target_, 0);
				Casio_Heist_Editor(4, m_recovery_casino_heist_approch_, m_recovery_casino_heist_target_, -1);
				}));

			//Global_1971696.f_1497.f_736.f_92[1+iVar0*1] gotta test
			ui->push(info("Cuts"));
			for (int i = 0; i < 4; ++i) {
				int& cut = *script_global(1971696 + 1497 + 736 + 92 + (1 + i * 1)).as<int*>();
				ui->push(number<int>("Player " + std::to_string(i)).add_number(&cut).add_min(0).add_max(100).add_precision(1).add_step(1).set_action([] {}));
			}
			});
		render::push<sub>("Cayo", "Network_Recovery_Heist_Cayo"_joaat, [](sub* ui) {
			ui->push(array<std::string, int>("Difficulty").add_array(&m_recovery_cayo_heist_difficulty).add_position(&m_recovery_cayo_heist_difficulty_));
			ui->push(array<std::string, int>("Target").add_array(&m_recovery_cayo_heist_target).add_position(&m_recovery_cayo_heist_target_));
			ui->push(array<std::string, int>("Weapon Variations").add_array(&m_recovery_cayo_heist_weapon_variations).add_position(&m_recovery_cayo_heist_weapon_variations_));
			ui->push(array<std::string, int>("Supply Truck Location").add_array(&m_recovery_cayo_heist_supply_truck).add_position(&m_recovery_cayo_heist_supply_truck_));
			ui->push(number<int>("Cash Value").add_number(&m_recovery_cayo_heist_cash_value).add_min(-2147483).add_max(2147483).add_precision(1).add_step(1).set_action([] {}));
			ui->push(number<int>("Weed Value").add_number(&m_recovery_cayo_heist_weed_value).add_min(-2147483).add_max(2147483).add_precision(1).add_step(1).set_action([] {}));
			ui->push(number<int>("Coke Value").add_number(&m_recovery_cayo_heist_coke_value).add_min(-2147483).add_max(2147483).add_precision(1).add_step(1).set_action([] {}));
			ui->push(number<int>("Gold Value").add_number(&m_recovery_cayo_heist_gold_value).add_min(-2147483).add_max(2147483).add_precision(1).add_step(1).set_action([] {}));
			ui->push(number<int>("Painting Value").add_number(&m_recovery_cayo_heist_painting_value).add_min(-2147483).add_max(2147483).add_precision(1).add_step(1).set_action([] {}));

			ui->push(button(xorstr_("Skip & Confirm Heist Preps")).set_action([] {
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("H4CNF_BS_GEN")), 131071, TRUE);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("H4CNF_BS_ENTR")), 63, TRUE);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("H4CNF_BS_ABIL")), 63, TRUE);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("H4CNF_WEAPONS")), m_recovery_cayo_heist_weapon_variations_ + 1, TRUE);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("H4CNF_WEP_DISRP")), 3, TRUE);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("H4CNF_ARM_DISRP")), 3, TRUE);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("H4CNF_HEL_DISRP")), 3, TRUE);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("H4CNF_TARGET")), m_recovery_cayo_heist_target_, TRUE);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("H4CNF_TROJAN")), m_recovery_cayo_heist_supply_truck_ + 1, TRUE);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("H4CNF_APPROACH")), -1, TRUE);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("H4LOOT_CASH_I")), 0, TRUE);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("H4LOOT_CASH_C")), -1, TRUE);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("H4LOOT_CASH_V")), m_recovery_cayo_heist_cash_value, TRUE);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("H4LOOT_WEED_I")), 0, TRUE);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("H4LOOT_WEED_C")), -1, TRUE);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("H4LOOT_WEED_V")), m_recovery_cayo_heist_weed_value, TRUE);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("H4LOOT_COKE_I")), 0, TRUE);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("H4LOOT_COKE_C")), -1, TRUE);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("H4LOOT_COKE_V")), m_recovery_cayo_heist_coke_value, TRUE);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("H4LOOT_GOLD_I")), 0, TRUE);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("H4LOOT_GOLD_C")), -1, TRUE);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("H4LOOT_GOLD_V")), m_recovery_cayo_heist_gold_value, TRUE);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("H4LOOT_PAINT")), -1, TRUE);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("H4LOOT_PAINT_V")), m_recovery_cayo_heist_painting_value, TRUE); //with 100000 1 player 150k

				if (m_recovery_cayo_heist_difficulty_ == 0)				
					STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("H4_PROGRESS")), 126823, TRUE);
				else 
					STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("H4_PROGRESS")), 131055, TRUE);

				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("H4LOOT_CASH_I_SCOPED")), -1, TRUE);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("H4LOOT_CASH_C_SCOPED")), -1, TRUE);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("H4LOOT_WEED_I_SCOPED")), -1, TRUE);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("H4LOOT_WEED_C_SCOPED")), -1, TRUE);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("H4LOOT_COKE_I_SCOPED")), -1, TRUE);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("H4LOOT_COKE_C_SCOPED")), -1, TRUE);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("H4LOOT_GOLD_I_SCOPED")), -1, TRUE);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("H4LOOT_GOLD_C_SCOPED")), -1, TRUE);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("H4LOOT_PAINT_SCOPED")), -1, TRUE);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("H4_MISSIONS")), 65535, TRUE);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("H4_PLAYTHROUGH_STATUS")), 10, TRUE);

				}));
			ui->push(info("Cooldowns"));
			ui->push(button(xorstr_("Reset Preps")).set_action([] {
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("H3OPT_BITSET1")), 0, TRUE);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("H4_MISSIONS")), 0, TRUE);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("H4_PROGRESS")), 0, TRUE);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("H4_PLAYTHROUGH_STATUS")), 0, TRUE);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("H4CNF_APPROACH")), 0, TRUE);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("H4CNF_BS_ENTR")), 0, TRUE);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("H4CNF_BS_GEN")), 0, TRUE);
				}));

			//Global_1978495.f_825.f_56[1+iVar0*1]
			ui->push(info("Cuts"));
			for (int i = 0; i < 4; ++i) {
				int& cut = *script_global(1978495 + 1497 + 825 + 56 + (1 + i * 1)).as<int*>();
				ui->push(number<int>("Player " + std::to_string(i)).add_number(&cut).add_min(0).add_max(100).add_precision(1).add_step(1).set_action([] {}));
			}
			});
		render::push<sub>("Unlock", "Network_Recovery_Unlock"_joaat, [](sub* ui) {
			ui->push(button(xorstr_("Heist Vehicles")).set_action([] {
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CHAR_KIT_FM_PURCHAS E")), -1, 0);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CHAR_KIT_FM_PURCHAS E2")), -1, 0);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CHAR_KIT_FM_PURCHAS E3")), -1, 0);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CHAR_KIT_FM_PURCHAS E4")), -1, 0);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CHAR_KIT_FM_PURCHAS E5")), -1, 0);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CHAR_KIT_FM_PURCHAS E6")), -1, 0);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CHAR_KIT_FM_PURCHAS E7")), -1, 0);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CHAR_KIT_FM_PURCHAS E8")), -1, 0);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CHAR_KIT_FM_PURCHAS E9")), -1, 0);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CHAR_KIT_FM_PURCHAS E10")), -1, 0);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CHAR_KIT_FM_PURCHAS E11")), -1, 0);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CHAR_KIT_FM_PURCHAS E12")), -1, 0);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CHAR_KIT_1_FM_UNLCK")), -1, 0);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CHAR_KIT_2_FM_UNLCK")), -1, 0);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CHAR_KIT_3_FM_UNLCK")), -1, 0);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CHAR_KIT_4_FM_UNLCK")), -1, 0);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CHAR_KIT_5_FM_UNLCK")), -1, 0);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CHAR_KIT_6_FM_UNLCK")), -1, 0);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CHAR_KIT_7_FM_UNLCK")), -1, 0);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CHAR_KIT_8_FM_UNLCK")), -1, 0);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CHAR_KIT_9_FM_UNLCK")), -1, 0);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CHAR_KIT_10_FM_UNLCK")), -1, 0);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CHAR_KIT_11_FM_UNLCK")), -1, 0);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CHAR_KIT_12_FM_UNLCK")), -1, 0);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("races_won")), 100, 0);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("number_turbo_starts_in_race")), 100, 0);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("usjs_found")), 50, 0);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("usjs_completed")), 50, 0);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("awd_fmwinairrace")), 50, 0);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("awd_fmwinsearace")), 50, 0);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("awd_fmrallywonnav")), 50, 0);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("awd_fmrallywondrive ")), 500, 0);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("awd_fm_races_fastest_lap")), 500, 0);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("char_fm_carmod_0_unlck")), -1, 0);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("char_fm_carmod_1_unlck")), -1, 0);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("char_fm_carmod_2_unlck")), -1, 0);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("char_fm_carmod_3_unlck")), -1, 0);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("char_fm_carmod_4_unlck")), -1, 0);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("char_fm_carmod_5_unlck")), -1, 0);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("char_fm_carmod_6_unlck")), -1, 0);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("char_fm_carmod_7_unlck")), -1, 0);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CHAR_FM_VEHICLE_1_UNLCK")), -1, 0);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CHAR_FM_VEHICLE_2_UNLCK")), -1, 0);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CHAR_FM_ABILITY_1_UNLCK")), -1, 0);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CHAR_FM_ABILITY_2_UNLCK")), -1, 0);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CHAR_FM_ABILITY_3_UNLCK")), -1, 0);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CHAR_FM_PACKAGE_1_COLLECT")), -1, 0);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CHAR_FM_PACKAGE_2_COLLECT")), -1, 0);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CHAR_FM_PACKAGE_3_COLLECT")), -1, 0);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CHAR_FM_PACKAGE_4_COLLECT")), -1, 0);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CHAR_FM_PACKAGE_5_COLLECT")), -1, 0);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CHAR_FM_PACKAGE_6_COLLECT")), -1, 0);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CHAR_FM_PACKAGE_7_COLLECT")), -1, 0);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CHAR_FM_PACKAGE_8_COLLECT")), -1, 0);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CHAR_FM_PACKAGE_9_COLLECT")), -1, 0);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CHAR_FM_HEALTH_1_UNLCK")), -1, 0);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CHAR_FM_HEALTH_2_UNLCK")), -1, 0);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("HOLDUPS_BITSET")), -1, 0);
				}));
			ui->push(button(xorstr_("Tattoo's")).set_action([] {
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("AWD_FM_DM_WINS")), 50, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("AWD_FM_TDM_MVP")), 50, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("AWD_FM_DM_TOTALKILLS")), 500, 1);
				STATS::STAT_SET_BOOL(rage::joaat(scripted_globals::get_character_stats() + xorstr_("AWD_FMATTGANGHQ")), 1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("AWD_FMBBETWIN")), 50000, 1);
				STATS::STAT_SET_BOOL(rage::joaat(scripted_globals::get_character_stats() + xorstr_("AWD_FMWINEVERYGAMEMODE")), 1, 1);
				STATS::STAT_SET_BOOL(rage::joaat(scripted_globals::get_character_stats() + xorstr_("AWD_FMRACEWORLDRECHOLDER")), 1, 1);
				STATS::STAT_SET_BOOL(rage::joaat(scripted_globals::get_character_stats() + xorstr_("AWD_FMFULLYMODDEDCAR")), 1, 1);
				STATS::STAT_SET_BOOL(rage::joaat(scripted_globals::get_character_stats() + xorstr_("AWD_FMMOSTKILLSSURVIVE")), 1, 1);
				STATS::STAT_SET_BOOL(rage::joaat(scripted_globals::get_character_stats() + xorstr_("AWD_FMKILL3ANDWINGTARACE")), 1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("AWD_FMKILLBOUNTY")), 25, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("AWD_FMREVENGEKILLSDM")), 50, 1);
				STATS::STAT_SET_BOOL(rage::joaat(scripted_globals::get_character_stats() + xorstr_("AWD_FMKILLSTREAKSDM")), 1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("AWD_HOLD_UP_SHOPS")), 20, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("AWD_LAPDANCES")), 25, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("AWD_SECURITY_CARS_ROBBED")), 25, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("AWD_RACES_WON")), 50, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("AWD_CAR_BOMBS_ENEMY_KILLS")), 25, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("PLAYER_HEADSHOTS")), 500, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("DB_PLAYER_KILLS")), 1000, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("tattoo_fm_unlocks_1")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("tattoo_fm_unlocks_2")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("tattoo_fm_unlocks_3")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("tattoo_fm_unlocks_4")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("tattoo_fm_unlocks_5")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("tattoo_fm_unlocks_6")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("tattoo_fm_unlocks_7")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("tattoo_fm_unlocks_8")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("tattoo_fm_unlocks_9")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("tattoo_fm_unlocks_10")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("tattoo_fm_unlocks_11")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("tattoo_fm_unlocks_12")), -1, 1);
		
				}));
			ui->push(button(xorstr_("Clothing")).set_action([] {
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CLTHS_AVAILABLE_FEET_1")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CLTHS_AVAILABLE_HAIR")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CLTHS_AVAILABLE_HAIR_1")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CLTHS_AVAILABLE_HAIR_2")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CLTHS_AVAILABLE_HAIR_3")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CLTHS_AVAILABLE_HAIR_4")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CLTHS_AVAILABLE_HAIR_5")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CLTHS_AVAILABLE_HAIR_6")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CLTHS_AVAILABLE_HAIR_7")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CLTHS_AVAILABLE_JBIB")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CLTHS_AVAILABLE_JBIB_1")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CLTHS_AVAILABLE_JBIB_2")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CLTHS_AVAILABLE_JBIB_3")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CLTHS_AVAILABLE_JBIB_4")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CLTHS_AVAILABLE_JBIB_5")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CLTHS_AVAILABLE_JBIB_6")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CLTHS_AVAILABLE_JBIB_7")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CLTHS_AVAILABLE_LEGS")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CLTHS_AVAILABLE_LEGS_1")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CLTHS_AVAILABLE_LEGS_2")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CLTHS_AVAILABLE_LEGS_3")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CLTHS_AVAILABLE_LEGS_4")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CLTHS_AVAILABLE_LEGS_5")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CLTHS_AVAILABLE_LEGS_6")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CLTHS_AVAILABLE_LEGS_7")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CLTHS_AVAILABLE_FEET")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CLTHS_AVAILABLE_FEET_1")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CLTHS_AVAILABLE_FEET_2")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CLTHS_AVAILABLE_FEET_3")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CLTHS_AVAILABLE_FEET_4")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CLTHS_AVAILABLE_FEET_5")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CLTHS_AVAILABLE_FEET_6")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CLTHS_AVAILABLE_FEET_7")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CLTHS_AVAILABLE_BERD")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CLTHS_AVAILABLE_BERD_1")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CLTHS_AVAILABLE_BERD_2")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CLTHS_AVAILABLE_BERD_3")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CLTHS_AVAILABLE_BERD_4")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CLTHS_AVAILABLE_BERD_5")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CLTHS_AVAILABLE_BERD_6")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CLTHS_AVAILABLE_BERD_7")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CLTHS_AVAILABLE_PROPS")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CLTHS_AVAILABLE_PROPS_1")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CLTHS_AVAILABLE_PROPS_2")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CLTHS_AVAILABLE_PROPS_3")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CLTHS_AVAILABLE_PROPS_4")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CLTHS_AVAILABLE_PROPS_5")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CLTHS_AVAILABLE_PROPS_6")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CLTHS_AVAILABLE_PROPS_7")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CLTHS_AVAILABLE_PROPS_8")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CLTHS_AVAILABLE_PROPS_9")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CLTHS_AVAILABLE_PROPS_10")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CLTHS_AVAILABLE_OUTFIT")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CLTHS_ACQUIRED_HAIR")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CLTHS_ACQUIRED_HAIR_1")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CLTHS_ACQUIRED_HAIR_2")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CLTHS_ACQUIRED_HAIR_3")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CLTHS_ACQUIRED_HAIR_4")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CLTHS_ACQUIRED_HAIR_5")), -1, 1);;
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CLTHS_ACQUIRED_HAIR_6")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CLTHS_ACQUIRED_HAIR_7")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CLTHS_ACQUIRED_JBIB")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CLTHS_ACQUIRED_JBIB_1")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CLTHS_ACQUIRED_JBIB_2")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CLTHS_ACQUIRED_JBIB_3")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CLTHS_ACQUIRED_JBIB_4")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CLTHS_ACQUIRED_JBIB_5")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CLTHS_ACQUIRED_JBIB_6")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CLTHS_ACQUIRED_JBIB_7")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CLTHS_ACQUIRED_LEGS")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CLTHS_ACQUIRED_LEGS_1")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CLTHS_ACQUIRED_LEGS_2")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CLTHS_ACQUIRED_LEGS_3")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CLTHS_ACQUIRED_LEGS_4")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CLTHS_ACQUIRED_LEGS_5")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CLTHS_ACQUIRED_LEGS_6")), -1, 1);;
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CLTHS_ACQUIRED_LEGS_7")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CLTHS_ACQUIRED_FEET")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CLTHS_ACQUIRED_FEET_1")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CLTHS_ACQUIRED_FEET_2")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CLTHS_ACQUIRED_FEET_3")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CLTHS_ACQUIRED_FEET_4")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CLTHS_ACQUIRED_FEET_5")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CLTHS_ACQUIRED_FEET_6")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CLTHS_ACQUIRED_FEET_7")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CLTHS_ACQUIRED_BERD")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CLTHS_ACQUIRED_BERD_1")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CLTHS_ACQUIRED_BERD_2")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CLTHS_ACQUIRED_BERD_3")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CLTHS_ACQUIRED_BERD_4")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CLTHS_ACQUIRED_BERD_5")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CLTHS_ACQUIRED_BERD_6")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CLTHS_ACQUIRED_BERD_7")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CLTHS_ACQUIRED_PROPS")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CLTHS_ACQUIRED_PROPS_1")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CLTHS_ACQUIRED_PROPS_2")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CLTHS_ACQUIRED_PROPS_3")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CLTHS_ACQUIRED_PROPS_4")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CLTHS_ACQUIRED_PROPS_5")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CLTHS_ACQUIRED_PROPS_6")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CLTHS_ACQUIRED_PROPS_7")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CLTHS_ACQUIRED_PROPS_8")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CLTHS_ACQUIRED_PROPS_9")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CLTHS_ACQUIRED_PROPS_10")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CLTHS_ACQUIRED_OUTFIT")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CLTHS_AVAILABLE_TORSO")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CLTHS_AVAILABLE_SPECIAL")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CLTHS_AVAILABLE_SPECIAL_1")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CLTHS_AVAILABLE_SPECIAL_2")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CLTHS_AVAILABLE_SPECIAL_3")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CLTHS_AVAILABLE_SPECIAL_4")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CLTHS_AVAILABLE_SPECIAL_5")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CLTHS_AVAILABLE_SPECIAL_6")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CLTHS_AVAILABLE_SPECIAL_7")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CLTHS_AVAILABLE_SPECIAL2")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CLTHS_AVAILABLE_SPECIAL2_1")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CLTHS_AVAILABLE_DECL")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CLTHS_AVAILABLE_TEETH")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CLTHS_AVAILABLE_TEETH_1")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CLTHS_AVAILABLE_TEETH_2")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CLTHS_ACQUIRED_TORSO")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CLTHS_ACQUIRED_SPECIAL")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CLTHS_ACQUIRED_SPECIAL_1")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CLTHS_ACQUIRED_SPECIAL_2")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CLTHS_ACQUIRED_SPECIAL_3")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CLTHS_ACQUIRED_SPECIAL_4")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CLTHS_ACQUIRED_SPECIAL_5")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CLTHS_ACQUIRED_SPECIAL_6")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CLTHS_ACQUIRED_SPECIAL_7")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CLTHS_ACQUIRED_SPECIAL2")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CLTHS_ACQUIRED_SPECIAL2_1")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CLTHS_ACQUIRED_DECL")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CLTHS_ACQUIRED_TEETH")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CLTHS_ACQUIRED_TEETH_1")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CLTHS_ACQUIRED_TEETH_2")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("DLC_APPAREL_ACQUIRED_0")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("DLC_APPAREL_ACQUIRED_1")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("DLC_APPAREL_ACQUIRED_2")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("DLC_APPAREL_ACQUIRED_3")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("DLC_APPAREL_ACQUIRED_4")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("DLC_APPAREL_ACQUIRED_5")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("DLC_APPAREL_ACQUIRED_6")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("DLC_APPAREL_ACQUIRED_7")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("DLC_APPAREL_ACQUIRED_8")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("DLC_APPAREL_ACQUIRED_9")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("DLC_APPAREL_ACQUIRED_10")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("DLC_APPAREL_ACQUIRED_11")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("DLC_APPAREL_ACQUIRED_12")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("DLC_APPAREL_ACQUIRED_13")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("DLC_APPAREL_ACQUIRED_14")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("DLC_APPAREL_ACQUIRED_15")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("DLC_APPAREL_ACQUIRED_16")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("DLC_APPAREL_ACQUIRED_17")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("DLC_APPAREL_ACQUIRED_18")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("DLC_APPAREL_ACQUIRED_19")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("DLC_APPAREL_ACQUIRED_21")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("DLC_APPAREL_ACQUIRED_22")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("DLC_APPAREL_ACQUIRED_23")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("DLC_APPAREL_ACQUIRED_24")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("DLC_APPAREL_ACQUIRED_24")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("DLC_APPAREL_ACQUIRED_25")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("DLC_APPAREL_ACQUIRED_26")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("DLC_APPAREL_ACQUIRED_27")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("DLC_APPAREL_ACQUIRED_28")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("DLC_APPAREL_ACQUIRED_29")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("DLC_APPAREL_ACQUIRED_30")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("DLC_APPAREL_ACQUIRED_31")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("DLC_APPAREL_ACQUIRED_32")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("DLC_APPAREL_ACQUIRED_33")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("DLC_APPAREL_ACQUIRED_34")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("DLC_APPAREL_ACQUIRED_35")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("DLC_APPAREL_ACQUIRED_36")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("DLC_APPAREL_ACQUIRED_37")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("DLC_APPAREL_ACQUIRED_38")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("DLC_APPAREL_ACQUIRED_39")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("DLC_APPAREL_ACQUIRED_40")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("ADMIN_CLOTHES_GV_BS_1")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("ADMIN_CLOTHES_GV_BS_2")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("ADMIN_CLOTHES_GV_BS_3")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("ADMIN_CLOTHES_GV_BS_4")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("ADMIN_CLOTHES_GV_BS_5")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("ADMIN_CLOTHES_GV_BS_6")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("ADMIN_CLOTHES_GV_BS_7")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("ADMIN_CLOTHES_GV_BS_8")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("ADMIN_CLOTHES_GV_BS_9")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("ADMIN_CLOTHES_GV_BS_10")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("ADMIN_CLOTHES_GV_BS_11")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("ADMIN_CLOTHES_GV_BS_12")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("ADMIN_CLOTHES_GV_BS_13")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("ADMIN_CLOTHES_GV_BS_1")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("ADMIN_CLOTHES_GV_BS_10")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("ADMIN_CLOTHES_GV_BS_11")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("ADMIN_CLOTHES_GV_BS_12")), -1, 1);	
			}));
			ui->push(button(xorstr_("Weapon Skins")).set_action([] {
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CLTHS_AVAILABLE_FEET_1")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("MOLOTOV _ENEMY_KILLS")), 600, 0);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CMBTPISTOL_ENEMY_KILLS")), 600, 0);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("PISTOL50_ENEMY_KILLS")), 600, 0);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("APPISTOL_ENEMY_KILLS")), 600, 0);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("MICROSMG_ENEMY_KILLS")), 600, 0);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("SMG_ENEMY_KILLS")), 600, 0);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("ASLTSMG_ENEMY_KILLS")), 600, 0);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("ASLTRIFLE_ENEMY_KILLS")), 600, 0);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CRBNRIFLE_ENEMY_KILLS")), 600, 0);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("ADVRIFLE_ENEMY_KILLS")), 600, 0);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("MG_ENEMY_KILLS")), 600, 0);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CMBTMG_ENEMY_KILLS")), 600, 0);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("ASLTMG_ENEMY_KILLS")), 600, 0);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("PUMP_ENEMY_KILLS")), 600, 0);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("SAWNOFF_ENEMY_KILLS")), 600, 0);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("BULLPUP_ENEMY_KILLS")), 600, 0);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("ASLTSHTGN_ENEMY_KILLS")), 600, 0);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("SNIPERRFL_ENEMY_KILLS")), 600, 0);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("HVYSNIPER_ENEMY_KILLS")), 600, 0);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("GRNLAUNCH_ENEMY_KILLS")), 600, 0);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("RPG_ENEMY_KILLS")), 600, 0);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("MINIGUNS_ENEMY_KILLS")), 600, 0);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("GRENADE_ENEMY_KILLS")), 600, 0);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("SMKGRENADE_ENEMY_KILLS")), 600, 0);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("STKYBMB_ENEMY_KILLS")), 600, 0);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("MOLOTOV_ENEMY_KILLS")), 600, 0);
				}));
			ui->push(button(xorstr_("Weapon")).set_action([] {
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("ADMIN_WEAPON_GV_BS_1")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("ADMIN_WEAPON_GV_BS_2")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("ADMIN_WEAPON_GV_BS_3")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("BOTTLE_IN_POSSESSION")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CHAR_FM_WEAP_UNLOCKED")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CHAR_FM_WEAP_UNLOCKED2")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CHAR_WEAP_FM_PURCHASE")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CHAR_WEAP_FM_PURCHASE2")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CHAR_FM_WEAP_ADDON_1_UNLCK")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CHAR_FM_WEAP_ADDON_2_UNLCK")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CHAR_FM_WEAP_ADDON_3_UNLCK")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CHAR_FM_WEAP_ADDON_4_UNLCK")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CHAR_FM_WEAP_ADDON_5_UNLCK")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("WEAP_FM_ADDON_PURCH")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("WEAP_FM_ADDON_PURCH2")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("WEAP_FM_ADDON_PURCH3")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("WEAP_FM_ADDON_PURCH4")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("WEAP_FM_ADDON_PURCH5")), -1, 1);
				}));
			ui->push(button(xorstr_("LSC Mods")).set_action([] {
				STATS::STAT_SET_BOOL(rage::joaat(scripted_globals::get_character_stats() + xorstr_("AWD_FMRACEWORLDRECHOLDER")), 1, true);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("AWD_ENEMYDRIVEBYKILLS")), 600, true);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("USJS_COMPLETED")), 50, true);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("USJS_FOUND")), 50, true);
				STATS::STAT_SET_BOOL(rage::joaat(scripted_globals::get_character_stats() + xorstr_("AWD_FMWINALLRACEMODES")), 1, true);
				STATS::STAT_SET_BOOL(rage::joaat(scripted_globals::get_character_stats() + xorstr_("AWD_FMWINEVERYGAMEMODE")), 1, true);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("DB_PLAYER_KILLS")), 1000, true);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("KILLS_PLAYERS")), 1000, true);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("AWD_FMHORDWAVESSURVIVE")), 21, true);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("AWD_CAR_BOMBS_ENEMY_KILLS")), 25, true);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("AWD_FM_TDM_MVP")), 60, true);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("AWD_HOLD_UP_SHOPS")), 20, true);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("AWD_RACES_WON")), 101, true);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("AWD_NO_ARMWRESTLING_WINS")), 21, true);
				STATS::STAT_SET_BOOL(rage::joaat(scripted_globals::get_character_stats() + xorstr_("AWD_FMATTGANGHQ")), 1, true);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("AWD_FMBBETWIN")), 50000, true);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("AWD_FM_DM_WINS")), 51, true);
				STATS::STAT_SET_BOOL(rage::joaat(scripted_globals::get_character_stats() + xorstr_("AWD_FMFULLYMODDEDCAR")), 1, true);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("AWD_FM_DM_TOTALKILLS")), 500, true);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("MPPLY_DM_TOTAL_DEATHS")), 412, true);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("MPPLY_TIMES_FINISH_DM_TOP_3")), 36, true);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("PLAYER_HEADSHOTS")), 623, true);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("AWD_FM_DM_WINS")), 63, true);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("AWD_FM_TDM_WINS")), 13, true);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("AWD_FM_GTA_RACES_WON")), 12, true);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("AWD_FM_GOLF_WON")), 2, true);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("AWD_FM_SHOOTRANG_TG_WON")), 2, true);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("AWD_FM_SHOOTRANG_RT_WON")), 2, true);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("AWD_FM_SHOOTRANG_CT_WON")), 2, true);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("AWD_FM_SHOOTRANG_GRAN_WON")), 2, true);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("AWD_FM_TENNIS_WON")), 2, true);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("MPPLY_TENNIS_MATCHES_WON")), 2, true);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("MPPLY_TOTAL_TDEATHMATCH_WON")), 63, true);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("MPPLY_TOTAL_RACES_WON")), 101, true);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("MPPLY_TOTAL_DEATHMATCH_LOST")), 23, true);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("MPPLY_TOTAL_RACES_LOST")), 36, true);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("AWD_25_KILLS_STICKYBOMBS")), 50, true);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("AWD_50_KILLS_GRENADES")), 50, true);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("GRENADE_ENEMY_KILLS ")), 50, true);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("AWD_20_KILLS_MELEE")), 50, true);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("AWD_WIN_CAPTURES")), 250, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("AWD_DROPOFF_CAP_PACKAGES")), 1000, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("AWD_KILL_CARRIER_CAPTURE")), 1000, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("AWD_FINISH_HEISTS")), 500, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("AWD_FINISH_HEIST_SETUP_JOB")), 500, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("AWD_NIGHTVISION_KILLS, 100")), 1000, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("AWD_WIN_LAST_TEAM_STANDINGS")), 500, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("AWD_ONLY_PLAYER_ALIVE_LTS")), 500, 1);
				}));
			ui->push(button(xorstr_("Hair Styles")).set_action([] {
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CLTHS_AVAILABLE_HAIR")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CLTHS_AVAILABLE_HAIR_1")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CLTHS_AVAILABLE_HAIR_2")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CLTHS_AVAILABLE_HAIR_3")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CLTHS_AVAILABLE_HAIR_4")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CLTHS_AVAILABLE_HAIR_5")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CLTHS_AVAILABLE_HAIR_6")), -1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CLTHS_AVAILABLE_HAIR_7")), -1, 1);
				}));
			ui->push(button(xorstr_("Achievment's")).set_action([] {
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("PLAYER_HEADSHOTS")), 500, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("PISTOL_ENEMY_KILLS")), 500, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("SAWNOFF_ENEMY_KILLS")), 500, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("MICROSMG_ENEMY_KILLS")), 500, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("SNIPERRFL_ENEMY_KILLS")), 100, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("UNARMED_ENEMY_KILLS")), 50, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("STKYBMB_ENEMY_KILLS")), 50, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("GRENADE_ENEMY_KILLS")), 50, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("RPG_ENEMY_KILLS")), 50, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CARS_EXPLODED")), 500, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("AWD_5STAR_WANTED_AVOIDANCE")), 50, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("AWD_CAR_BOMBS_ENEMY_KILLS")), 25, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("AWD_CARS_EXPORTED")), 50, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("PASS_DB_PLAYER_KILLS")), 100, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("AWD_FM_DM_WINS")), 50, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("AWD_FM_GOLF_WON")), 25, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("AWD_FM_GTA_RACES_WON")), 50, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("AWD_FM_SHOOTRANG_CT_WON")), 25, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("AWD_FM_SHOOTRANG_RT_WON")), 25, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("AWD_FM_SHOOTRANG_TG_WON")), 25, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("AWD_FM_TDM_WINS")), 50, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("AWD_FM_TENNIS_WON")), 25, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("MOST_SPINS_IN_ONE_JUMP")), 5, 1);
				STATS::STAT_SET_INT(rage::joaat(xorstr_("MPPLY_AWD_FM_CR_DM_MADE")), 25, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("AWD_FMHORDWAVESSURVIVE")), 10, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("AWD_HOLD_UP_SHOPS")), 20, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("ASLTRIFLE_ENEMY_KILLS")), 500, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("MG_ENEMY_KILLS")), 500, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("AWD_LAPDANCES")), 25, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("MOST_ARM_WRESTLING_WINS")), 25, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("AWD_NO_HAIRCUTS")), 25, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("AWD_RACES_WON")), 50, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("AWD_SECURITY_CARS_ROBBED")), 25, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("AWD_VEHICLES_JACKEDR")), 500, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("MOST_FLIPS_IN_ONE_JUMP")), 5, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("AWD_WIN_AT_DARTS")), 25, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("AWD_PASSENGERTIME")), 4, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("AWD_TIME_IN_HELICOPTER")), 4, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("AWD_FM_DM_3KILLSAMEGUY")), 50, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("AWD_FM_DM_KILLSTREAK")), 100, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("AWD_FM_DM_STOLENKILL")), 50, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("AWD_FM_DM_TOTALKILLS")), 500, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("AWD_FM_GOLF_BIRDIES")), 25, 1);
				STATS::STAT_SET_BOOL(rage::joaat(scripted_globals::get_character_stats() + xorstr_("AWD_FM_GOLF_HOLE_IN_1")), 1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("AWD_FM_RACE_LAST_FIRST")), 25, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("AWD_FM_RACES_FASTEST_LAP")), 25, 1);
				STATS::STAT_SET_BOOL(rage::joaat(scripted_globals::get_character_stats() + xorstr_("AWD_FM_SHOOTRANG_GRAN_WON")), 1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("AWD_FM_TDM_MVP")), 50, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("AWD_FM_TENNIS_ACE")), 25, 1);
				STATS::STAT_SET_BOOL(rage::joaat(scripted_globals::get_character_stats() + xorstr_("AWD_FM_TENNIS_STASETWIN")), 1, 1);
				STATS::STAT_SET_BOOL(rage::joaat(scripted_globals::get_character_stats() + xorstr_("AWD_FM6DARTCHKOUT")), 1, 1);
				STATS::STAT_SET_BOOL(rage::joaat(scripted_globals::get_character_stats() + xorstr_("AWD_FMATTGANGHQ")), 1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("AWD_PARACHUTE_JUMPS_20M")), 25, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("AWD_PARACHUTE_JUMPS_50M")), 25, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("AIR_LAUNCHES_OVER_40M")), 25, 1);
				STATS::STAT_SET_BOOL(rage::joaat(scripted_globals::get_character_stats() + xorstr_("AWD_BUY_EVERY_GUN")), 1, 1);
				STATS::STAT_SET_BOOL(rage::joaat(scripted_globals::get_character_stats() + xorstr_("AWD_FMWINEVERYGAMEMODE")), 1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("AWD_FMDRIVEWITHOUTCRASH")), 255, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("AWD_FMCRATEDROPS")), 25, 1);
				STATS::STAT_SET_BOOL(rage::joaat(scripted_globals::get_character_stats() + xorstr_("AWD_FM25DIFFERENTDM")), 1, 1);
				STATS::STAT_SET_BOOL(rage::joaat(scripted_globals::get_character_stats() + xorstr_("AWD_FM_TENNIS_5_SET_WINS")), 1, 1);
				STATS::STAT_SET_INT(rage::joaat(xorstr_("MPPLY_AWD_FM_CR_PLAYED_BY_PEEP")), 100, 1);
				STATS::STAT_SET_INT(rage::joaat(xorstr_("MPPLY_AWD_FM_CR_RACES_MADE")), 25, 1);
				STATS::STAT_SET_BOOL(rage::joaat(scripted_globals::get_character_stats() + xorstr_("AWD_FM25DIFFERENTRACES")), 1, 1);
				STATS::STAT_SET_BOOL(rage::joaat(scripted_globals::get_character_stats() + xorstr_("AWD_FM25DIFITEMSCLOTHES")), 1, 1);
				STATS::STAT_SET_BOOL(rage::joaat(scripted_globals::get_character_stats() + xorstr_("AWD_FMFULLYMODDEDCAR")), 1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("AWD_FMKILLBOUNTY")), 25, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("KILLS_PLAYERS")), 1000, 1);
				STATS::STAT_SET_BOOL(rage::joaat(scripted_globals::get_character_stats() + xorstr_("AWD_FMPICKUPDLCCRATE1ST")), 1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("AWD_FMSHOOTDOWNCOPHELI")), 25, 1);
				STATS::STAT_SET_BOOL(rage::joaat(scripted_globals::get_character_stats() + xorstr_("AWD_FMKILL3ANDWINGTARACE")), 1, 1);
				STATS::STAT_SET_BOOL(rage::joaat(scripted_globals::get_character_stats() + xorstr_("AWD_FMKILLSTREAKSDM")), 1, 1);
				STATS::STAT_SET_BOOL(rage::joaat(scripted_globals::get_character_stats() + xorstr_("AWD_FMMOSTKILLSGANGHIDE")), 1, 1);
				STATS::STAT_SET_BOOL(rage::joaat(scripted_globals::get_character_stats() + xorstr_("AWD_FMMOSTKILLSSURVIVE")), 1, 1);
				STATS::STAT_SET_BOOL(rage::joaat(scripted_globals::get_character_stats() + xorstr_("AWD_FMRACEWORLDRECHOLDER")), 1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("AWD_FMRALLYWONDRIVE")), 25, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("AWD_FMRALLYWONNAV")), 25, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("AWD_FMREVENGEKILLSDM")), 50, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("AWD_FMWINAIRRACE")), 25, 1);
				STATS::STAT_SET_BOOL(rage::joaat(scripted_globals::get_character_stats() + xorstr_("AWD_FMWINCUSTOMRACE")), 1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("AWD_FMWINRACETOPOINTS")), 25, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("AWD_FMWINSEARACE")), 25, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("AWD_FMBASEJMP")), 25, 1);
				STATS::STAT_SET_BOOL(rage::joaat(scripted_globals::get_character_stats() + xorstr_("MP0_AWD_FMWINALLRACEMODES")), 1, 1);
				STATS::STAT_SET_BOOL(rage::joaat(scripted_globals::get_character_stats() + xorstr_("AWD_FMTATTOOALLBODYPARTS")), 1, 1);
				STATS::STAT_SET_INT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("CHAR_WANTED_LEVEL_TIME5STAR")), 2147483647, 1);
				STATS::STAT_SET_FLOAT(rage::joaat(scripted_globals::get_character_stats() + xorstr_("LONGEST_WHEELIE_DIST")), 1000, 1);
				}));


			});
		render::push<sub>("Modify", "Network_Recovery_Modify"_joaat, [](sub* ui) {
			for (int i = 0; i < add_int_stat_data.size(); i++)
			{
				add_int_stat(ui, add_int_stat_data[i]);
			}
			for (int i = 0; i < add_float_stat_data.size(); i++)
			{
				add_float_stat(ui, add_float_stat_data[i]);
			}
			});
	}

}