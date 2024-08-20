#include "common.hpp"
#include "common.hpp"
#include "features.hpp"
#include "util/logger.hpp"
#include "util/script/script.hpp"
#include "common.hpp"
#include "natives.hpp"
#include "util/timer.hpp"
#include "util/gta_util.hpp"
#include "cheat/render/render.hpp"
#include "util/textures/textures.hpp"
#include "util/input/input.hpp"
#include "util/notify/notify.hpp"
#include "util/config/config.hpp"
#include "cheat/script/script.hpp"
#include "cheat/features/features.hpp"
#include "util/script/fiber_pool.hpp"
#include "util/discord/Discord_Integration.hpp"
#include <util/script_patcher/script_patcher.hpp>
#include "util/notify/noties.hpp"
#include "util/instructionals _buttons/instructionals buttons.hpp"
#include "util/ptfx_bullet/ptfx_bullet.hpp"
#include "cheat/features/self/self.hpp"
#include "cheat/features/vehicle/vehicle.hpp"
#include "cheat/features/weapons/weapons.hpp"
namespace insight
{
	void features::discord_rpc() {
		while (true) {
			DiscordIntegration::Utility::tick();
			insight::script::get_current()->yield();
		}
	}
	void features::textures() {
		insight::textures::initialize();
		while (true) {
			insight::textures::tick();
			insight::script::get_current()->yield();
		}
	}
	void features::gui() {
		insight::fonts::initialize();
		insight::script_ui::initialize();
		while (true) {
				insight::render::tick();
				insight::fonts::tick();
				insight::input::tick();
				insight::notify::get_notify()->tick_anti_spam_msg();
				instructionals::get()->main_menu();
				insight::script::get_current()->yield();
		}
	}
	void features::self() {
		self::initialize();
		while (true) {
			feature_manager::get()->tick(xorstr_("self"));
			script::get_current()->yield();
		}
	}
	void features::vehicle() {
		vehicle::initialize();
		while (true) {
			feature_manager::get()->tick(xorstr_("vehicle"));
			script::get_current()->yield();
		}
	}	
	void features::network() {
		insight::network::initialize();
		while (true) {
			feature_manager::get()->tick(xorstr_("network"));
			insight::script::get_current()->yield();
		}
	}
	void features::players() {
       	insight:player_options::get()->initialize();
		while (true) {
			player_options::get()->tick_players_features();
			insight::script::get_current()->yield();
		}
	}

	void features::weapons() {
		weapon::initialize();
		while (true) {
			feature_manager::get()->tick(xorstr_("weapon"));
			script::get_current()->yield();
		}
	}
	void features::teleport() {
		insight::teleport::initialize();
		while (true) {
			feature_manager::get()->tick(xorstr_("teleport"));
			insight::script::get_current()->yield();
		}
	}
	void features::spawner() {
		insight::spawner::initialize();
		while (true) {
			feature_manager::get()->tick(xorstr_("spawner"));
			insight::script::get_current()->yield();
		}
	}
	void features::world() {
		insight::world::initialize();
		while (true) {
			feature_manager::get()->tick(xorstr_("world"));
			insight::script::get_current()->yield();
		}
	}
	void features::miscellaneous() {
		insight::miscellaneous::initialize();
		while (true) {
			feature_manager::get()->tick(xorstr_("miscellaneous"));
			insight::script::get_current()->yield();
		}
	}
	void features::protections() {
		while (true) {
			g_local::h_local_ped_heading = ENTITY::GET_ENTITY_HEADING(globals::h_local_ped());
			globals::player_id = PLAYER::PLAYER_ID();
			globals::is_player_loaded_in = !STREAMING::IS_PLAYER_SWITCH_IN_PROGRESS();
			bullet_ptfx::get()->tick();
			tasks::get_keyboard_input_tick();
			protections_noties();
			tick_fishy();
			insight::script::get_current()->yield();
		}
	}
	void features::script_patcher() {
		g_script_patcher.register_patches();
		while (true) {
			if (!STREAMING::IS_PLAYER_SWITCH_IN_PROGRESS()) 
			g_script_patcher.update();
			insight::script::get_current()->yield();
		}
	}
	void features::body_guards() {
		while (true) {
			if (!STREAMING::IS_PLAYER_SWITCH_IN_PROGRESS())
				tasks::tick_bodyguards();
			insight::script::get_current()->yield();
		}
	}
}