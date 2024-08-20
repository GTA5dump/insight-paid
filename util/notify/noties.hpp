#pragma once
#include <network/CNetGamePlayer.hpp>
#include "util/timer.hpp"
#include "cheat/features/globals.hpp"
namespace insight {
	struct reactions_noties {
		timer time = timer(std::chrono::seconds(5));
		std::string player;
	};
	inline reactions_noties g_invalid_vehiclemodel;
	inline reactions_noties g_invalid_doormodel;
	inline reactions_noties g_invalid_pickupmodel;
	inline reactions_noties g_invalid_pedmodel;
	inline reactions_noties g_invalid_propmodel;
	inline reactions_noties g_inf_attachments;
	inline reactions_noties g_invalid_object;
	inline reactions_noties g_invalid_playermodel;
	inline reactions_noties g_invalid_sectorpos;
	inline reactions_noties g_invalid_sectorpos2;
	inline reactions_noties g_invalid_train_track;
	inline reactions_noties g_invalid_sub_control_crash;
	inline reactions_noties g_flag_crash_crash;
	inline reactions_noties g_invalid_gadget_crash;
	inline reactions_noties g_caging_protection;
	inline reactions_noties g_explosion_protection;
	void noties_ticker(reactions_noties& rec);
	void noties_add(reactions_noties& rec, CNetGamePlayer* sender);
	void protections_noties();
	struct reactions_fishy {
		timer time = timer(std::chrono::seconds(20));
	};
	inline reactions_fishy tick_fishy_timer[32];
	void set_player_fishy(int i);
	void tick_fishy();
}