#pragma once
#include "cheat/render/render.hpp"
#include "cheat/pointers/pointers.hpp"
struct hotkey {
	int m_key;
	bool* m_pointer;
	std::string m_name;
};
namespace insight {
	class input {
	public:
		input();
	public:
		bool is_input_aim_pressed();
	public:
		static LRESULT APIENTRY window_process_callback(HWND hwnd, UINT msg, WPARAM param, LPARAM lparam);

		static void tick();
		static bool is_just_released(bool keyboard, int key, bool override_input = false);
		static bool is_just_pressed(bool keyboard, int key, bool override_input = false);
		static bool is_pressed(bool keyboard, int key, bool override_input = false,bool held = false);

		static bool is_open_bind_pressed(bool override_input = false);
		static bool is_option_pressed(bool override_input = false);
		static bool is_enter_pressed(bool override_input = false);
		static bool is_left_just_pressed(bool override_input = false);
		static bool is_right_just_pressed(bool override_input = false);
		static bool is_left_pressed(bool override_input = false);
		static bool is_right_pressed(bool override_input = false);

		static void set_last_key(int key) { input::get()->m_last_key = key; }

		static WNDPROC get_windows_process() { return input::get()->m_windows_process; }
		static int get_last_key() { return input::get()->m_last_key; }

		static void update_hotkeys();

		static void save_hotkeys();
		static void load_hotkeys();

		std::unordered_map<const char*, hotkey> m_hotkeys;

		static bool is_press_sync(const int key) {
			if (GetForegroundWindow() == insight::pointers::get()->g_hwnd) {
				if (GetAsyncKeyState(key) & 0x8000) {
					return true;
				}
			}
			return false;
		}

		bool m_hotkey_pressed;
	public:
		struct LiveKeysState {
			int key;
			const char* text;
		};
		struct KeyboardState {
			uint32_t m_time;
			bool m_is_with_alt;
			bool m_was_down_before;
			bool m_is_up_now;
			bool m_just_up;
			bool m_just_down;
		};

		KeyboardState m_key_states[255];
		LiveKeysState m_live_state_key;
		WNDPROC m_windows_process;
		int m_last_key;
	public:
		const char* g_key_names[254] = {
		"",
		"F10",
		"F10",
		"SCROLL LOCK",
		"SCROLL LOCK",
		"SCROLL LOCK",
		"SCROLL LOCK",
		"SCROLL LOCK",
		"BACKSPACE",
		"TAB",
		"TAB",
		"TAB",
		"NUM 5",
		"ENTER",
		"ENTER",
		"ENTER",
		"SHIFT",
		"CTRL",
		"ALT",
		"ALT",
		"CAPSLOCK",
		"CAPSLOCK",
		"CAPSLOCK",
		"CAPSLOCK",
		"CAPSLOCK",
		"CAPSLOCK",
		"CAPSLOCK",
		"ESC",
		"ESC",
		"ESC",
		"ESC",
		"ESC",
		"SPACE",
		"NUM 9",
		"NUM 3",
		"NUM 1",
		"NUM 7",
		"LEFT",
		"UP",
		"RIGHT",
		"DOWN",
		"NUM 2",
		"NUM 2",
		"NUM 2",
		"NUM 2",
		"NUM 0",
		"DELETE",
		"NUM DECIMAL",
		"0",
		"1",
		"2",
		"3",
		"4",
		"5",
		"6",
		"7",
		"8",
		"9",
		"9",
		"9",
		"9",
		"9",
		"9",
		"9",
		"9",
		"A",
		"B",
		"C",
		"D",
		"E",
		"F",
		"G",
		"H",
		"I",
		"J",
		"K",
		"L",
		"M",
		"N",
		"O",
		"P",
		"Q",
		"R",
		"S",
		"T",
		"U",
		"V",
		"W",
		"X",
		"Y",
		"Z",
		"Z",
		"Z",
		"Z",
		"Z",
		"Z",
		"NUM 0",
		"NUM 1",
		"NUM 2",
		"NUM 3",
		"NUM 4",
		"NUM 5",
		"NUM 6",
		"NUM 7",
		"NUM 8",
		"NUM 9",
		"*",
		"NUM PLUS",
		"NUM PLUS",
		"NUM SUB",
		"NUM DECIMAL",
		"/",
		"F1",
		"F2",
		"F3",
		"F4",
		"F5",
		"F6",
		"F7",
		"F8",
		"F9",
		"F10",
		"F11",
		"F12",
		"F12",
		"F12",
		"F12",
		"F12",
		"F12",
		"F12",
		"F12",
		"F12",
		"F12",
		"F12",
		"F12",
		"F12",
		"F12",
		"F12",
		"F12",
		"F12",
		"F12",
		"F12",
		"F12",
		"F12",
		"Pause",
		"SCROLL LOCK",
		"SCROLL LOCK",
		"SCROLL LOCK",
		"SCROLL LOCK",
		"SCROLL LOCK",
		"SCROLL LOCK",
		"SCROLL LOCK",
		"SCROLL LOCK",
		"SCROLL LOCK",
		"SCROLL LOCK",
		"SCROLL LOCK",
		"SCROLL LOCK",
		"SCROLL LOCK",
		"SCROLL LOCK",
		"SCROLL LOCK",
		"SHIFT",
		"RIGHT SHIFT",
		"CTRL",
		"CTRL",
		"ALT",
		"ALT",
		"ALT",
		"ALT",
		"ALT",
		"ALT",
		"ALT",
		"ALT",
		"M",
		"D",
		"C",
		"B",
		"P",
		"Q",
		"J",
		"G",
		"G",
		"G",
		"G",
		"F",
		"F",
		"F",
		";",
		"=",
		",",
		"-",
		".",
		"/",
		"GRAVE",
		"GRAVE",
		"GRAVE",
		"GRAVE",
		"GRAVE",
		"GRAVE",
		"GRAVE",
		"GRAVE",
		"GRAVE",
		"A",
		"B",
		"X",
		"Y",
		"Left Button",
		"Right Button",
		"Left Trigger",
		"Right Trigger",
		"Left Stick",
		"Right Stick",
		"GRAVE",
		"GRAVE",
		"GRAVE",
		"GRAVE",
		"GRAVE",
		"GRAVE",
		"GRAVE",
		"GRAVE",
		"[",
		"null",
		"]",
		"ACUTE/CEDILLA",
		"ACUTE/CEDILLA",
		"ACUTE/CEDILLA",
		"ACUTE/CEDILLA",
		"null",
		"null",
		"null",
		"null",
		"null",
		"null",
		"null",
		"null",
		"null",
		"null",
		"null",
		"null",
		"null",
		"null",
		"null",
		"null",
		"null",
		"null",
		"null",
		"null",
		"null",
		"null",
		"null",
		"null",
		"null",
		"null",
		"null",
		"null"
		};
		const char* g_keyboard_input_names[73] = {
		"0",
		"1",
		"2",
		"3",
		"4",
		"5",
		"6",
		"7",
		"8",
		"9",
		"9",
		"9",
		"9",
		"9",
		"9",
		"9",
		"9",
		"A",
		"B",
		"C",
		"D",
		"E",
		"F",
		"G",
		"H",
		"I",
		"J",
		"K",
		"L",
		"M",
		"N",
		"O",
		"P",
		"Q",
		"R",
		"S",
		"T",
		"U",
		"V",
		"W",
		"X",
		"Y",
		"Z",
		"Z",
		"Z",
		"Z",
		"Z",
		"Z",
		"*",
		"M",
		"D",
		"C",
		"B",
		"P",
		"Q",
		"J",
		"G",
		"G",
		"G",
		"G",
		"F",
		"F",
		"F",
		";",
		"=",
		",",
		"-",
		".",
		"/",
		"A",
		"B",
		"X",
		"Y"
		};
	public:
		static void destroy();
		static input* get() {
			static input i{};
			return &i;
		}
	public:
		static void initialize() {
			get();
		}
	};
}