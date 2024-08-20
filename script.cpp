#pragma once
#include "script.hpp"
#include "cheat/menu/xml/xml.hpp"
#include "util/script/script.hpp"
#include "util/script/fiber_pool.hpp"
#include "cheat/render/render.hpp"
#include "auth/instance.hpp"

inline bool script_toggles[64];
inline int scriptt_count;
namespace insight {
	timer fuc_sub_menu_title_timer(std::chrono::seconds(1));
	void fuc_sub_menu_title_reset() {
		if (fuc_sub_menu_title_timer.update()) {
			render::get()->m_title.m_title = trans("Root/");
		}
	}
}
using namespace insight;
void push_large_message(std::string title, std::string message, int color, int duration) {
	g_fiber_pool->queue_job([duration, title, message, color] {
		if (render::get()->m_opened) {
			return;
		}
		script::get_current()->yield(500ms);
		float startPos = 0.0f;
		for (int i = 0; i < duration; i++) {
			int m_scaleForm = GRAPHICS::REQUEST_SCALEFORM_MOVIE("MP_BIG_MESSAGE_FREEMODE");
			if (GRAPHICS::HAS_SCALEFORM_MOVIE_LOADED(m_scaleForm)) {
				GRAPHICS::BEGIN_SCALEFORM_MOVIE_METHOD(m_scaleForm, "OVERRIDE_Y_POSITION");
				GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_FLOAT(startPos - 0.75f);
				GRAPHICS::END_SCALEFORM_MOVIE_METHOD();
				if (startPos < 0.5f)startPos += (0.5f - startPos) / 100.0f;
				if (i > duration - 150)startPos -= startPos / 50.0f;
				GRAPHICS::BEGIN_SCALEFORM_MOVIE_METHOD(m_scaleForm, "SHOW_CENTERED_MP_MESSAGE_LARGE");
				GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_TEXTURE_NAME_STRING(title.c_str());
				HUD::SET_COLOUR_OF_NEXT_TEXT_COMPONENT(color);
				GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_TEXTURE_NAME_STRING(message.c_str());
				GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT(100);
				GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_BOOL(1);
				GRAPHICS::END_SCALEFORM_MOVIE_METHOD();
				GRAPHICS::DRAW_SCALEFORM_MOVIE_FULLSCREEN_MASKED(m_scaleForm, 255, 255, 255, 0, 0);
			}
			script::get_current()->yield(1ms);
		}
		});
}
namespace insight {
	void script_ui::initialize() {
		render::push<sub>("Insight", "insight"_joaat, [](sub* ui) {
			fuc_sub_menu_title_reset();
			ui->push(submenu("Player").add_target("Player"_joaat));
			ui->push(submenu("Vehicle").add_target("Vehicle"_joaat));
			ui->push(submenu("Weapons").add_target("Weapons"_joaat));
			ui->push(submenu("Spawner").add_target("Spawner"_joaat));
			ui->push(submenu("Network").add_target("Network"_joaat));
			ui->push(submenu("World").add_target("World"_joaat));
			ui->push(submenu("Teleports").add_target("Teleports"_joaat).set_action([=] {
				xml::get()->load_teleport_data();
				}));
			ui->push(submenu("Protections").add_target("Network_Protections"_joaat));
			ui->push(submenu("Miscellaneous").add_target("Miscellaneous"_joaat));
			ui->push(submenu("Settings").add_target("Settings"_joaat));
		});
		script_ui::settings();
		script_ui::player();
		script_ui::vehicle();
		script_ui::vehiclelsc();
		script_ui::teleports();
		script_ui::weapon();
		script_ui::spawner();
		script_ui::network();
		script_ui::network_all_players_options();
		script_ui::network_player_options();
		script_ui::network_vehicle_options();
		script_ui::network_weapon_options();
		script_ui::network_social_options();
		script_ui::network_teleport_options();
		script_ui::network_removal_options();
		script_ui::weapon_projectile_manager();
		script_ui::network_recovery();
		script_ui::network_recovery_money();
		script_ui::network_recovery_rank();	
		script_ui::network_recovery_stats();
		script_ui::network_spoofing();
		script_ui::network_spoofing_host_token();
		script_ui::network_spoofing_stats();
		script_ui::network_spoofing_rotation();
		script_ui::world();
		script_ui::world_subs();
		script_ui::miscellaneous();
		ui::push_color_sub();
		/*std::stringstream message;
		message << xorstr_("Welcome ") << auth::g_auth_instance.m_data.m_username << xorstr_(", Press Insert To Open");
		push_large_message(xorstr_("Insight"), message.str(), 12, 600);*/
		notify::send("Insight", "Intilization Finished Press Insert");
	}

	script_ui::~script_ui() {
	}
}