#include "input.hpp"
#include "natives.hpp"
#include "cheat/render/render.hpp"
#include "util/notify/notify.hpp"
#include "util/script/script.hpp"
#include "cheat/features/manager/manager.h"
#include <WinUser.h>
#include "util/timer.hpp"
#include "game/gta/enums.hpp"
#include "util/translation/translation.hpp"
#include "util/script/fiber_pool.hpp"
#include "cheat/render/renderer.hpp"
#include <timeapi.h>
using jsonf = nlohmann::json;
jsonf loader;
namespace insight {
	LRESULT APIENTRY input::window_process_callback(HWND hwnd, UINT msg, WPARAM param, LPARAM lparam) {
		switch (msg) {
		case WM_KEYDOWN:
		case WM_KEYUP:
		case WM_SYSKEYDOWN:
		case WM_SYSKEYUP: {
			if (param < 255) {
				input::get()->m_live_state_key.key = (int)param;
				input::get()->m_live_state_key.text = input::get()->g_key_names[(int)param];
				input::get()->m_key_states[param].m_time = GetTickCount64();
				input::get()->m_key_states[param].m_is_with_alt = (msg == WM_SYSKEYDOWN || msg == WM_SYSKEYUP);
				input::get()->m_key_states[param].m_was_down_before = (lparam >> 30) & 1;
				input::get()->m_key_states[param].m_is_up_now = (msg == WM_SYSKEYUP || msg == WM_KEYUP);
				if (!input::get()->m_key_states[param].m_was_down_before) input::get()->m_key_states[param].m_just_down = !(msg == WM_SYSKEYUP || msg == WM_KEYUP);

				if (input::get()->m_key_states[param].m_is_up_now) {
					if (param != VK_RETURN && param != VK_F8) {
						input::get()->set_last_key((int)param);
					}
				}
			}
			break;
		}
		}
		g_renderer->wnd_proc(hwnd, msg, param, lparam);
		return CallWindowProcA(input::get()->m_windows_process, hwnd, msg, param, lparam);
	}

	input::input() {
		m_windows_process = (WNDPROC)SetWindowLongPtrA(insight::pointers::get()->g_hwnd, GWLP_WNDPROC, (LONG_PTR)window_process_callback);
	}
	bool input::is_input_aim_pressed() {
		if (PED::GET_PED_CONFIG_FLAG(PLAYER::PLAYER_PED_ID(), 78, 0)) {
			return true;
		}
		return false;
	}
	struct smooth_scrolling_plus_ {
		timer pressing = (timer)std::chrono::milliseconds(150);
		int pressing_int = 0;
		int delay = 250;
		smooth_scrolling_plus_(int delay) : pressing(std::chrono::milliseconds(150)), delay(delay) {}
	};
	void smooth_scrolling_plus(smooth_scrolling_plus_ &i) {
		i.pressing_int++;
		if (i.pressing_int > 150 && i.pressing_int < i.delay) {
			i.pressing.setdelay(std::chrono::milliseconds(100));
		}
		else if (i.pressing_int > 300 && i.pressing_int < i.delay) {
			i.pressing.setdelay(std::chrono::milliseconds(50));			
		}
		else if (i.pressing_int > i.delay) {
			i.pressing.setdelay(std::chrono::milliseconds(0));			
		}
		else {
			i.pressing.setdelay(std::chrono::milliseconds(i.delay));
		}
	}
	void smooth_scrolling_plus_reset(smooth_scrolling_plus_& i) {
		i.pressing_int = 0;
		i.pressing.setdelay(std::chrono::milliseconds(i.delay));
	}

	smooth_scrolling_plus_ up_pressing{ 170 };
	smooth_scrolling_plus_ down_pressing{ 170 };
	smooth_scrolling_plus_ left_pressing{ 170 };
	smooth_scrolling_plus_ right_pressing{ 170 };
	smooth_scrolling_plus_ open_n_backing_pressing{ 300 };
	void input::tick()  {
		if (insight::g_input_disabled) return;
		update_hotkeys();


		if (input::get()->m_hotkey_pressed) {
			PAD::DISABLE_ALL_CONTROL_ACTIONS(0);
		}

		if (is_open_bind_pressed() || is_pressed(true, 0x58) || is_pressed(true, VK_F8) && render::get()->m_opened) {
			if (open_n_backing_pressing.pressing.update()) {
				AUDIO::PLAY_SOUND_FRONTEND(-1, "Back", "HUD_FRONTEND_DEFAULT_SOUNDSET", false);
				if (is_open_bind_pressed()) {
					render::get()->m_opened ^= true;
				}
				if (is_pressed(true, 0x58)) {
					mouse::g_is_mouse_enabled ^= true;
				}
				if (is_pressed(true, VK_F8)) {
					if (render::get()->m_opened) {
						input::get()->m_hotkey_pressed = true;
					}
				}
			}
		}
		else {
			if (render::get()->m_opened) { 
				auto sub = render::get()->m_submenu_stack.top();
				if (is_pressed(true, VK_UP) || is_pressed(false, (int)ControllerInputs::INPUT_FRONTEND_UP, false, true)) {
					if (up_pressing.pressing.update()) {
						sub->scroll_backward();
						AUDIO::PLAY_SOUND_FRONTEND(-1, "NAV_UP_DOWN", "HUD_FRONTEND_DEFAULT_SOUNDSET", FALSE);
					} smooth_scrolling_plus(up_pressing);
				}
				else {
					smooth_scrolling_plus_reset(up_pressing);
				}
				if (is_pressed(true, VK_DOWN) || is_pressed(false, (int)ControllerInputs::INPUT_FRONTEND_DOWN, false, true)) {
					if (down_pressing.pressing.update()) {
						sub->scroll_forward();
						AUDIO::PLAY_SOUND_FRONTEND(-1, "NAV_UP_DOWN", "HUD_FRONTEND_DEFAULT_SOUNDSET", FALSE);
					} smooth_scrolling_plus(down_pressing);
				}
				else {
					smooth_scrolling_plus_reset(down_pressing);
				}
				if (is_pressed(true, VK_LEFT) || is_pressed(false, (int)ControllerInputs::INPUT_FRONTEND_LEFT, false, true)) {
					if (left_pressing.pressing.update()) {
						sub->get_option(sub->get_selected_option())->handle_action(eOptionAction::left_click);
						AUDIO::PLAY_SOUND_FRONTEND(-1, "NAV_LEFT_RIGHT", "HUD_FRONTEND_DEFAULT_SOUNDSET", FALSE);
					}smooth_scrolling_plus(left_pressing);
				}
				else {
					smooth_scrolling_plus_reset(left_pressing);
				}
				if (is_pressed(true, VK_RIGHT) || is_pressed(false, (int)ControllerInputs::INPUT_FRONTEND_RIGHT, false, true)) {
					if (right_pressing.pressing.update()) {
						sub->get_option(sub->get_selected_option())->handle_action(eOptionAction::right_click);
						AUDIO::PLAY_SOUND_FRONTEND(-1, "NAV_LEFT_RIGHT", "HUD_FRONTEND_DEFAULT_SOUNDSET", FALSE);
					}smooth_scrolling_plus(right_pressing);
				}
				else {
					smooth_scrolling_plus_reset(right_pressing);
				}
				if (is_pressed(true, VK_RETURN) || is_pressed(false, (int)ControllerInputs::INPUT_FRONTEND_ACCEPT, false, true)) {
					if (open_n_backing_pressing.pressing.update()) {
						sub->get_option(sub->get_selected_option())->handle_action(eOptionAction::click);
						AUDIO::PLAY_SOUND_FRONTEND(-1, "SELECT", "HUD_FRONTEND_DEFAULT_SOUNDSET", false);
					}
				}
				if (is_just_pressed(true, VK_NUMPAD0) || is_pressed(false, (int)ControllerInputs::INPUT_FRONTEND_CANCEL, false, true)) {
					if (open_n_backing_pressing.pressing.update()) {
						if (render::get()->m_submenu_stack.size() > 1) {
							remove_last_segment(&render::get()->m_title.m_title);
							render::get()->m_submenu_stack.pop();
							AUDIO::PLAY_SOUND_FRONTEND(-1, "BACK", "HUD_FRONTEND_DEFAULT_SOUNDSET", false);

						}
						else {
							render::get()->m_opened = false;
						}
					}
				}
				if (GetAsyncKeyState(VK_RBUTTON) && mouse::g_is_mouse_enabled) {
					if (open_n_backing_pressing.pressing.update()) {
						if (render::get()->m_submenu_stack.size() > 1) {
							remove_last_segment(&render::get()->m_title.m_title);
							render::get()->m_submenu_stack.pop();
						}
						else {
							render::get()->m_opened = false;
						}
						AUDIO::PLAY_SOUND_FRONTEND(-1, "BACK", "HUD_FRONTEND_DEFAULT_SOUNDSET", false);
					}
				}
			}
		}
	}
	bool input::is_just_released(bool keyboard, int key, bool override_input) {
		if (insight::g_input_disabled && !override_input) return false;

		if (keyboard) {
			bool result = GetTickCount64() < (input::get()->m_key_states[key].m_time + 100) && input::get()->m_key_states[key].m_is_up_now;
			memset(&input::get()->m_key_states[key], 0, sizeof(input::get()->m_key_states[0]));
			return result;
		}

		return PAD::IS_DISABLED_CONTROL_JUST_PRESSED(0, key);
	}

	bool input::is_just_pressed(bool keyboard, int key, bool override_input) {
		if (insight::g_input_disabled && !override_input) return false;

		if (keyboard) {
			bool result = GetTickCount64() - 100 < input::get()->m_key_states[key].m_time && !input::get()->m_key_states[key].m_is_up_now && input::get()->m_key_states[key].m_just_down;
			if (result) input::get()->m_key_states[key].m_just_down = false;
			return result;
		}
		return PAD::IS_DISABLED_CONTROL_JUST_PRESSED(0, key);
	}

	bool input::is_pressed(bool keyboard, int key, bool override_input, bool held) {
		if (insight::g_input_disabled && !override_input) return false;

		if (keyboard) {
			return timeGetTime() < (input::get()->m_key_states[key].m_time + 300000) && !input::get()->m_key_states[key].m_is_up_now;
		}
		if (held)
			return PAD::IS_DISABLED_CONTROL_PRESSED(0, key);
		else
			return PAD::IS_DISABLED_CONTROL_JUST_PRESSED(0, key);
	}

	bool input::is_open_bind_pressed(bool override_input) {
		bool is_pressed_controller = is_pressed(false, (int)ControllerInputs::INPUT_FRONTEND_RB, false,true) && is_pressed(false, (int)ControllerInputs::INPUT_FRONTEND_RIGHT, false, true);
		return is_pressed_controller || is_pressed(true, VK_INSERT, override_input);
	}

	bool input::is_option_pressed(bool override_input) {
		if (insight::g_input_disabled && !override_input) return false;

		if (is_pressed(false, (int)ControllerInputs::INPUT_FRONTEND_ACCEPT, false, true) || is_just_pressed(true, VK_NUMPAD5, override_input)) {
			AUDIO::PLAY_SOUND_FRONTEND(-1, "SELECT", "HUD_FRONTEND_DEFAULT_SOUNDSET", FALSE);
			return true;
		}

		return false;
	}
	bool input::is_enter_pressed(bool override_input) {
		if (insight::g_input_disabled && !override_input) return false;
		if (PAD::IS_DISABLED_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_FRONTEND_ACCEPT) || input::get()->is_just_pressed(true, VK_NUMPAD5, false))
		{
			return true;
		}
		return false;
	}

	bool input::is_left_just_pressed(bool override_input) {
		if (insight::g_input_disabled && !override_input) return false;
		return is_pressed(false, (int)ControllerInputs::INPUT_FRONTEND_LEFT, false, true) || is_just_pressed(true, VK_NUMPAD4, override_input);
	}

	bool input::is_right_just_pressed(bool override_input) {
		if (insight::g_input_disabled && !override_input) return false;
		return is_pressed(false, (int)ControllerInputs::INPUT_FRONTEND_RIGHT, false, true) || is_just_pressed(true, VK_NUMPAD6, override_input);
	}

	bool input::is_left_pressed(bool override_input) {
		if (insight::g_input_disabled && !override_input) return false;
		return is_pressed(false, (int)ControllerInputs::INPUT_FRONTEND_LEFT, false, true) || is_pressed(true, VK_NUMPAD4, override_input);
	}

	bool input::is_right_pressed(bool override_input) {
		if (insight::g_input_disabled && !override_input) return false;
		return is_pressed(false, (int)ControllerInputs::INPUT_FRONTEND_RIGHT, false, true) || is_pressed(true, VK_NUMPAD6, override_input);
	}

	void input::destroy() {
		SetWindowLongPtrA(insight::pointers::get()->g_hwnd, GWLP_WNDPROC, (LONG_PTR)input::get()->m_windows_process);
	}

	void input::update_hotkeys() {
		if (input::get()->m_hotkeys.empty()) {
			return;
		}
		static int delay_tick;
		for (auto pair : input::get()->m_hotkeys) {
			if (timeGetTime() - delay_tick > 500) {
				if (is_press_sync(pair.second.m_key)) {
					*pair.second.m_pointer = !*pair.second.m_pointer;

					AUDIO::PLAY_SOUND_FRONTEND(-1, "SELECT", "HUD_FRONTEND_DEFAULT_SOUNDSET", FALSE);

					if (*pair.second.m_pointer) {
						notify::send("Hotkey Manager", std::format("Pressed {}, Enabled {},", input::get()->g_key_names[pair.second.m_key], pair.second.m_name));
					}
					else {
						notify::send("Hotkey Manager", std::format("Pressed {}, Disabled {},", input::get()->g_key_names[pair.second.m_key], pair.second.m_name));
					}

					delay_tick = timeGetTime();
				}
			}
		}
	}

	int hotkey_load_count;
	void input::load_hotkeys() {
		
		insight::g_fiber_pool->queue_job([=] {
			try {
				hotkey_load_count = 0;
				std::filesystem::path cheat_path;
				cheat_path.append(std::getenv("appdata"));
				cheat_path.append("Insight");
				cheat_path.append("cheat.hotkeys");
				std::ifstream file(cheat_path);
				if (!file.good()) {
					return;
				}
				file >> loader;
				LOG(INFO) << "Found " << loader.size() << " Hotkeys";
				input::get()->m_hotkeys;
				for (auto& item : loader.items()) {
					hotkey_load_count++;
					const std::string& key = item.key();
					const char* id = key.c_str();
					int hotkey = item.value()["Hotkey"].get<int>();
					std::string name = item.value()["Name"].get<std::string>();
					if (auto feature = feature_manager::get()->get_feature<toggle_feature>(id); feature) {
						if (auto boolPtr = &feature->m_value.toggle; boolPtr) {
							script::get_current()->yield(std::chrono::milliseconds(50));
							bool holder;
							input::get()->m_hotkeys.insert({ id, {hotkey, boolPtr ? boolPtr : &holder, name}});
						}
						else {
							LOG(INFO) << "Failed to get bool pointer for feature " << id;
						}
					}
					else {
						LOG(INFO) << "Failed to get feature for" << id;
					}
				}
			}
			catch (const std::exception& e) { 
				LOG(FATAL) << e.what();
			}
		});
	}

	void input::save_hotkeys() {
		using jsonf = nlohmann::json;
		static jsonf save;
		for (auto hotkey : input::get()->m_hotkeys) {
			std::filesystem::path cheat_path;
			cheat_path.append(std::getenv("appdata"));
			cheat_path.append("Insight");
			cheat_path.append("cheat.hotkeys");
			std::ofstream file(cheat_path, std::ios::out | std::ios::trunc);
			save[hotkey.first]["Hotkey"] = hotkey.second.m_key;
			save[hotkey.first]["Name"] = hotkey.second.m_name;
			std::ofstream json_file(cheat_path);
			json_file << std::setw(4) << save << std::endl;
			json_file.close();
		}
	}
}