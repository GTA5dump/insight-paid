#pragma once
#include "game/gta/enums.hpp"
#include "common.hpp"

typedef void(*keyboard_handler)(DWORD, WORD, BYTE, BOOL, BOOL, BOOL, BOOL);
typedef void(*present_callback)(void*);

namespace insight {
	struct asi_module {
		bool m_running = false;
		HMODULE m_module = nullptr;
	};
	class shv_script_hook {
	public:
		static void create();
		static void destroy();
	public:
		static shv_script_hook* get() {
			static shv_script_hook i;
			return &i;
		}
	public:
		static rage::scrNativeCallContext native_context;
		static u64 native_hash;

		static void script_register(HMODULE module, void(*LP_SCRIPT_MAIN)());
		static void script_register_another_thread(HMODULE module, void(*LP_SCRIPT_MAIN)());
		static void script_unregister(HMODULE module);
		static void script_unregister_depricated(void(*LP_SCRIPT_MAIN)());

		static BYTE* get_script_handle_base_address(int handle);
		static void present_call_back_register(present_callback cb);
		static void present_call_back_unregister(present_callback cb);

		static void native_call_begin(uint64_t hash);
		static void native_push(uint64_t val);
		static u64* native_call_end();
		static void load_modules_from_path();

		static u64* get_global(int index);

		static int create_texture(const char* fileName);
		static void draw_texture(int id, int index, int level, int time, float sizeX, float sizeY, float centerX, float centerY, float posX, float posY, float rotation, float screenHeightScaleFactor, float r, float g, float b, float a);

		static void keyboard_register(keyboard_handler function);
		static void keyboard_unregister(keyboard_handler function);

		static void script_wait(unsigned long waitTime);
		static void wnd_proc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

		static int world_get_all_vehicles(int* arr, int arrSize);
		static int world_get_all_peds(int* arr, int arrSize);
		static int world_get_all_objects(int* arr, int arrSize);
		static int world_get_all_pickups(int* arr, int arrSize);

		static int get_game_verison();

		static int register_raw_streaming_file(const std::string& fileName, const std::string& registerAs);
		static std::unordered_map<std::string, asi_module> m_modules;
		static HMODULE m_instance;
	};
}