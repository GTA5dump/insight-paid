#include "cheat/features/tasks.hpp"
#include "util/input/input.hpp"
#include "natives.hpp"
#include "util/script/script.hpp"
#include "cheat/render/renderer.hpp"
std::string get_clipboard_text() {
	std::string text;
	if (OpenClipboard(nullptr)) {
		HANDLE clipboardHandle = GetClipboardData(CF_TEXT);
		if (clipboardHandle != nullptr) {
			char* clipboardData = static_cast<char*>(GlobalLock(clipboardHandle));
			if (clipboardData != nullptr) {
				text = clipboardData;
				GlobalUnlock(clipboardHandle);
			}
		}
		CloseClipboard();
	}

	return text;
}

namespace insight {
	//YEA SORRY IM DEAD HEAD (VERY CLEAN YEAH) :(
	bool get_keyboard_input_first_use = false;
	bool is_ready_for_use = false;
	std::string get_keyboard_input_text = "";
	static timer get_keyboard_input_timer(std::chrono::milliseconds(140));
	static timer get_keyboard_input_reset_timer(std::chrono::milliseconds(150));
	std::string tasks::get_keyboard_input(std::string title, std::string default_input, int max_input) {
		if (input::is_press_sync(VK_LCONTROL) && input::is_press_sync(0x4B)) {
			return get_clipboard_text().substr(0, 20);
		}
		while (get_keyboard_input_first_use == false) {
			if (input::get()->is_press_sync(input::get()->m_live_state_key.key) && get_keyboard_input_timer.update()) {
				for (int i = 0; i < 73; i++) {
					if (input::get()->m_live_state_key.text == "ENTER") {
						if (is_ready_for_use) {
							get_keyboard_input_first_use = true;
						}
						is_ready_for_use = true;
						break;
					}
					if (input::get()->m_live_state_key.text == "BACKSPACE") {
						if (!get_keyboard_input_text.empty()) {
							get_keyboard_input_text = get_keyboard_input_text.substr(0, get_keyboard_input_text.size() - 1);
						}
						break;
					}
					if (input::get()->m_live_state_key.text == input::get()->g_keyboard_input_names[i]) {
						get_keyboard_input_text = get_keyboard_input_text + input::get()->m_live_state_key.text;
						break;
					}

				}
			}
			get_keyboard_input_reset_timer.restart();
			g_renderer->draw_text(get_keyboard_input_text.empty() ? "Input" : get_keyboard_input_text.c_str(), font_justify::center, {0.5f, 0.5f}, 0.7f, 0, {0.f, 0.f});
			PAD::DISABLE_ALL_CONTROL_ACTIONS(0);
			script::get_current()->yield();
		}
		if (get_keyboard_input_text.empty()) { return "0"; }		
		return get_keyboard_input_text;
	}
	void tasks::get_keyboard_input_tick() {
		if (get_keyboard_input_reset_timer.update()) {
			get_keyboard_input_text = "";
			get_keyboard_input_first_use = false;
			is_ready_for_use = false;
		}
	}
}