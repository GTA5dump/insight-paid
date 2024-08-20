#pragma once
#include "cheat/features/globals.hpp"
#include "cheat/features/scripted_globals.hpp"
#include "cheat/features/scripted_globals/scr_globals.hpp"
#include <script/globals/GPBD_FM_3.hpp>
#include <script/globals/GlobalPlayerBD.hpp>
#include "util/script/script_global.hpp"
namespace insight
{

    bool scripted_globals::get_player_otr(Player player) {
   //     int offradar = *script_global(2657704).at(1 + (player * 463)).at(213).as<int*>();
      //  return *script_global(2657704).at(player, 463).at(210).as<int*>();
        return  scr_globals::globalplayer_bd.as<GlobalPlayerBD*>()->Entries[player].OffRadarActive;
    }

    void scripted_globals::local_set_player_otr_flag(bool toggle) {  
      //  *script_global(2657704).at(globals::player_id, 463).at(210).as<int*>() = 1;
        scr_globals::globalplayer_bd.as<GlobalPlayerBD*>()->Entries[globals::player_id].OffRadarActive = toggle;

    }

    void scripted_globals::local_set_player_otr_time() {
         *scr_globals::offradar_time.at(57).as<int*>() = NETWORK::GET_NETWORK_TIME() + 757000;
    }   
    int scripted_globals::get_character() {
        return *script_global(1574918).as<int*>();
    }
    std::string scripted_globals::get_character_stats() {
        if (get_character() == 0) {
            return "MP0_";
        }
        else {
            return "MP1_";
        }
        return "MP0_";      
    }
    int64_t* scripted_globals::fuc_321(Player player) {
      //  Global_1895156[plParam0 /*609*/].f_511;
        return script_global(1895156).at(1 + (player * 609)).at(511).as<int64_t*>();
      //  return (int64_t*)scr_globals::gpbd_fm_3.as<GPBD_FM_3*>()->Entries[player].ScriptEventReplayProtectionCounter;
    }

    int64_t* scripted_globals::u_param0() {
      //  *uParam0 = Global_1924276.f_9;
        return script_global(1924276).at(9).as<int64_t*>();
        //return (int64_t*)scr_globals::gsbd_fm_events.at(9).as<int*>();
    }   
    int64_t* scripted_globals::u_param1() {
      //  *uParam0 = Global_1924276.f_9;
        return script_global(1924276).at(10).as<int64_t*>();
       // return (int64_t*)scr_globals::gsbd_fm_events.at(10).as<int*>();
       
    }
    int scripted_globals::is_local_player_pointing(int value) {
        if (value == -1)
            return *script_global(4521801).at(930).as<int*>();
        else
        {
            *script_global(4521801).at(935).as<int*>() = value;
        } return 0;
    }
    void scripted_globals::claim_bounty() {
        *script_global(2359296).at(0, 5568).at(5150).at(13).as<int*>() = 2880000;
    }

    void scripted_globals::func_7329(bool toggle) {
        *script_global(2794162).at(5999).as<int*>() = toggle;

    }
    void scripted_globals::veh_spawn_bypass(bool toggle) {
        *script_global(4540731).as<bool*>() = true;

    }
};
