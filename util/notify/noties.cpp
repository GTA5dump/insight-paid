#pragma once
#include <network/CNetGamePlayer.hpp>
#include "util/timer.hpp"
#include "cheat/features/globals.hpp"
#include "cheat/features/features.hpp"
#include "noties.hpp"
namespace insight {
	void set_player_fishy(int i) {
		player_options::get()->is_fishy[i] = true;
		tick_fishy_timer[i].time.restart();
	}
	void tick_fishy() {
		for (int i = 0; i < 32; i++)
		{
			if (player_options::get()->is_fishy[i]) {
				if (tick_fishy_timer[i].time.update()) {
					player_options::get()->is_fishy[i] = false;
				}
			}
		}
	}
	 void noties_add(reactions_noties& rec, CNetGamePlayer* sender) {
		if (rec.player.empty()) {
			rec.player = sender->get_name();
		}
		else if (rec.player == sender->get_name()) {
			rec.time.restart();
		}
	}
	 void protections_noties() {
		if (globals::in_multiplayer()) {
			noties_ticker(g_invalid_vehiclemodel);
			noties_ticker(g_invalid_doormodel);
			noties_ticker(g_invalid_pickupmodel);
			noties_ticker(g_invalid_pedmodel);
			noties_ticker(g_invalid_propmodel);
			noties_ticker(g_inf_attachments);
			noties_ticker(g_invalid_object);
			noties_ticker(g_invalid_playermodel);
			noties_ticker(g_invalid_sectorpos);
			noties_ticker(g_invalid_sectorpos2);
			noties_ticker(g_invalid_train_track);
			noties_ticker(g_invalid_sub_control_crash);
			noties_ticker(g_flag_crash_crash);
			noties_ticker(g_invalid_gadget_crash);
			noties_ticker(g_caging_protection);
			noties_ticker(g_explosion_protection);
		}
	}
	 void noties_ticker(reactions_noties& rec) {
		 if (rec.time.update()) {
			 rec.player.clear();
		 }
	 }
}