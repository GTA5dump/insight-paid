#pragma once
#include "cheat/features/globals.hpp"
#include "cheat/features/scripted_globals.hpp"
#include "util/script/script_global.hpp"

namespace insight {
    //				return Global_1853988[bParam0 /*867*/].f_205.f_5;
    void scripted_globals::set_player_stat(int id, int value) {
        *script_global(1853988).at(globals::player_id, 867).at(205).at(id).as<int*>() = value;
    }
    int get_player_info(int id, int value) {    
       return *script_global(1853988).at(id, 867).at(205).at(value).as<int*>();
    }
    char* get_player_info_c(int id, int value) {    
       return script_global(1853988).at(id, 867).at(205).at(value).as<char*>();
    }
};
