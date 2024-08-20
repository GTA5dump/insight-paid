#pragma once
#include "script_patch.hpp"
#include "script_patcher.hpp"
#include "cheat/features/features.hpp"
#include <game/gta/script_program.hpp>
namespace insight {
	script_data* script_patcher::get_data_for_script(uint32_t script) {
		for (auto& p : m_script_data) {
			if (p.first == script) {
				return p.second.get();
			}
		}

		return nullptr;
	}

	bool script_patcher::does_script_have_patches(uint32_t script) {
		for (auto& p : m_script_patches) {
			if (p.get_script() == script)
				return true;
		}

		return false;
	}

	void script_patcher::create_data_for_script(rage::scrProgram* program) {
		auto pages = new uint8_t * [program->get_num_code_pages()];

		for (auto i = 0u; i < program->get_num_code_pages(); i++) {
			pages[i] = new uint8_t[program->get_code_page_size(i)];
			std::memcpy(pages[i], program->get_code_page(i), program->get_code_page_size(i));
		}

		m_script_data.emplace(program->m_name_hash, std::make_unique<script_data>(program->m_code_size, pages, program->get_num_code_pages()));
	}

	void script_patcher::update_all_patches_for_script(uint32_t script) {
		auto data = get_data_for_script(script);

		for (auto& p : m_script_patches)
			if (p.get_script() == script)
				p.update(data);
	}

	void script_patcher::add_patch(script_patch&& patch) {
		m_script_patches.push_back(std::move(patch));
	}

	void script_patcher::on_script_load(rage::scrProgram* program) {
		if (get_data_for_script(program->m_name_hash) == nullptr && does_script_have_patches(program->m_name_hash)) {
			create_data_for_script(program);
			update_all_patches_for_script(program->m_name_hash);
		}
	}

	std::uint8_t** script_patcher::get_script_byte_code(uint32_t script) {
		if (auto data = get_data_for_script(script))
			return data->m_byte_code;

		return nullptr;
	}

	void script_patcher::update() {
		for (auto& p : m_script_patches) {
			auto data = get_data_for_script(p.get_script());
			if (data) {
				p.update(data);
			}
		}
	}

	void script_patcher::register_patches() {
		// Script host kick allowance - because this AC is simply the best
		add_patch({ "freemode"_joaat, "2D 01 04 00 ? 2C ? ? ? 5D ? ? ? 71 57 ? ? 2C", 5, { 0x2E, 0x01, 0x00 }, nullptr });
		// End session kick protection - because Rockstar can't
		add_patch({ "freemode"_joaat, "5D ? ? ? 76 57 ? ? 5D ? ? ? 76", 0, { 0x2E, 0x00, 0x00 }, nullptr });
		// Out of bounds death bypass - allows you to go under the map and (illegally) spectate players without dying at random
		add_patch({ "freemode"_joaat, "2D 01 09 00 00 5D ? ? ? 56 ? ? 2E", 5, { 0x2E, 0x01, 0x00 }, nullptr });
		// load island even if stranded animal IPL choice is not set
		add_patch({ "freemode"_joaat, "71 2E ? ? 55 ? ? 61 ? ? ? 47 ? ? 63", 0, { 0x72 }, nullptr });
		// disable population load balancing
		add_patch({ "freemode"_joaat, "2D 00 07 00 00 7B", 5, { 0x2E, 0x00, 0x00 }, nullptr });

		// Vehicle despawn bypass - stops newer vehicles despawning/kicking out player in Story Mode
		add_patch({ "shop_controller"_joaat, "2D 01 04 00 00 2C ? ? ? 56 ? ? 71", 5, { 0x71, 0x2E, 0x01, 0x01 }, nullptr });
		// Godmode/Invisibility detection bypass - not that Arxan would detect if you have them on, but other menus can
		add_patch({ "shop_controller"_joaat, "38 00 5D ? ? ? 38 00 5D ? ? ? 38 00 41", 0, std::vector<uint8_t>(12, 0x0), nullptr });

		add_patch({ "maintransition"_joaat, "2D 00 02 00 00 2C ? ? ? 56 ? ? 2C ? ? ? 74 58 ? ? 2C ? ? ? 73", 5, {0x72, 0x2E, 0x00, 0x01}, &"seemless_transition"_tf->m_value.toggle });
		add_patch({ "freemode"_joaat, "2D 09 53 00 00", 5, {0x2E, 0x09, 0x00}, &"seemless_transition"_tf->m_value.toggle });

		for (auto& entry : *insight::pointers::get()->g_script_program_table) {
			if (entry.m_program)
				on_script_load(entry.m_program);
		}
	}
}