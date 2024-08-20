#pragma once
#include "cheat/menu/options/array.h"
#include "cheat/menu/options/button.h"
#include "cheat/menu/options/number.h"
#include "cheat/menu/options/toggle.h"
#include "cheat/menu/options/combo.h"
#include "cheat/menu/options/sub.h"
#include "cheat/menu/options/vehicle.h"
#include "cheat/menu/options/array.h"
#include "cheat/menu/options/icon.h"
#include "cheat/menu/options/keyboard.h"
#include "cheat/menu/options/number_toggle.h"
#include "cheat/menu/options/array_toggle.h"
#include "cheat/menu/options/player_sub.h"
#include "cheat/menu/options/info.h"
#include "cheat/menu/sub/sub.h"
#include "cheat/render/render.hpp"
#include "util/notify/notify.hpp"
#include "util/input/input.hpp"
#include "cheat/menu/helper/ui.hpp"

namespace insight {
	class script_ui final {
    private:
        script_ui();
    public:
        ~script_ui();
      
        script_ui(const script_ui&) = delete;
        script_ui(script_ui&&) noexcept = delete;
        script_ui& operator=(const script_ui&) = delete;
        script_ui& operator=(script_ui&&) noexcept = delete;
    private:
        static script_ui& get()
        {
            static script_ui i{};

            return i;
        }
    public:
        static void initialize();
    public:
        static void settings(); 
        static void player();
        static void vehicle();
        static void teleports();
        static void vehiclelsc();
        static void network();
        static void network_player_options();
        static void network_vehicle_options();
        static void network_weapon_options();
        static void network_removal_options();
        static void network_social_options();
        static void network_teleport_options();
        static void network_all_players_options();
        static void weapon();
        static void weapon_projectile_manager();
        static void network_recovery();
        static void network_recovery_money();
        static void network_recovery_rank();
        static void network_recovery_stats();
        static void network_recovery_unlocks();

        static void network_spoofing();
        static void network_spoofing_stats();
        static void network_spoofing_host_token();
        static void network_spoofing_rotation();

        static void spawner();

        static void world();
        static void world_subs();
        static void miscellaneous();
	};
}