#include "shv.hpp"
#include "cheat/features/globals.hpp"
#include "util/notify/notify.hpp"
#include "util/script/script_mgr.hpp"
#include "cheat/pointers/pointers.hpp"
#include "game/gta/replay.hpp"
#include "game/gta/enums.hpp"
#include "game/invoker/invoker.hpp"
#include <set>
namespace insight {
	rage::scrNativeCallContext shv_script_hook::native_context;

	u64 shv_script_hook::native_hash;

	std::unordered_map<std::string, asi_module> shv_script_hook::m_modules;

	HMODULE shv_script_hook::m_instance;

	HMODULE m_invalid_mods_instance;
	void shv_script_hook::create() {
		std::thread([] {
			auto file_path = std::filesystem::path(std::getenv("appdata")).append("insight").append("Patcher.dll");

			if (!GetModuleHandleA("Patcher.dll")) {
				m_instance = LoadLibraryA(file_path.string().c_str());
				LOG(INFO) << "Created Patcher Instance";
			}
			}).detach();
	}

	void shv_script_hook::load_modules_from_path() {
		m_modules.clear();
		auto path = std::filesystem::path(std::getenv(xorstr_("appdata"))).append(xorstr_("insight")).append(xorstr_("scripts"));
		if (std::filesystem::exists(path)) {
			std::filesystem::directory_iterator it{ path };
			for (auto&& entry : it) {
				if (entry.is_regular_file()) {
					auto path{ entry.path() };
					if (path.has_filename() && path.extension() == xorstr_(".asi")) {
						asi_module holder{ false, LoadLibraryA("null") };
						m_modules.insert({ path.stem().string(), holder });
					}
				}
			}
		}
	}

	void shv_script_hook::destroy() {
		FreeLibrary(m_instance);

		for (auto& module : shv_script_hook::m_modules) {
			HMODULE lib = module.second.m_module;
			g_script_mgr.remove_script(std::to_string((u64)lib).c_str());
			FreeLibrary(lib);
			shv_script_hook::m_modules.erase(module.first);
		}
		LOG(INFO) << xorstr_("Removed Script Hook V Instance");
	}
	

	void shv_script_hook::script_register(HMODULE module, void(*LP_SCRIPT_MAIN)())
	{
		g_script_mgr.add_script(std::format("0x{:X}:0x{:X}", (uint64_t)module, (uint64_t)LP_SCRIPT_MAIN).c_str(), std::make_unique<script>(LP_SCRIPT_MAIN));
	}

	void shv_script_hook::script_register_another_thread(HMODULE module, void(*LP_SCRIPT_MAIN)())
	{
		g_script_mgr.add_script(std::format("0x{:X}:0x{:X}", (uint64_t)module, (uint64_t)LP_SCRIPT_MAIN).c_str(), std::make_unique<script>(LP_SCRIPT_MAIN));
	}

	void shv_script_hook::script_unregister(HMODULE module)
	{
		g_script_mgr.remove_script(std::format("0x{:X}", (uint64_t)module).c_str());
		for (const auto& script : g_script_mgr.m_scripts) {
			if (strstr(script.first, std::format("0x{:X}", (uint64_t)module).c_str())) {
				try {
					script.second.get()->~script();
					FreeLibrary(module);
				}
				catch (std::exception e) {
					LOG(INFO) << "Issue Deleting Fiber" << e.what();
				}
			}
		}
	}

	void shv_script_hook::script_unregister_depricated(void(*LP_SCRIPT_MAIN)())
	{
		g_script_mgr.remove_script(std::format("0x{:X}", (uint64_t)LP_SCRIPT_MAIN).c_str());
	}
	void shv_script_hook::native_call_begin(uint64_t hash) {
		insight::g_native_invoker.end_call(hash);
	}

	void shv_script_hook::native_push(uint64_t val) {
		insight::g_native_invoker.push_arg(std::forward<uint64_t>(val));
	}

	uint64_t* shv_script_hook::native_call_end() {
		insight::g_native_invoker.end_call(native_hash);	
		return  (uint64_t*)insight::g_native_invoker.get_return_value<u64>();
	}

	uint64_t* shv_script_hook::get_global(int index) {
		return (uint64_t*)&insight::pointers::get()->g_script_globals[index >> 18 & 0x3F][index & 0x3FFFF];
	}

	int shv_script_hook::create_texture(const char* fileName) {
		return 0;
	}

	void shv_script_hook::draw_texture(int id, int index, int level, int time, float sizeX, float sizeY, float centerX, float centerY, float posX, float posY, float rotation, float screenHeightScaleFactor, float r, float g, float b, float a) {
	}

	void shv_script_hook::script_wait(unsigned long waitTime) {
		script::get_current()->yield(std::chrono::milliseconds(waitTime));
	}

	static std::set<keyboard_handler> g_keyboard_functions;
	void shv_script_hook::keyboard_register(keyboard_handler function) {
		g_keyboard_functions.insert(function);
	}

	void shv_script_hook::keyboard_unregister(keyboard_handler function) {
		g_keyboard_functions.erase(function);
	}

	void shv_script_hook::wnd_proc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
		DWORD key{ DWORD(wParam) };
		WORD repeats{ WORD(lParam & 0xFFFF) };
		BYTE scanCode{ BYTE((lParam >> 16) & 0xFF) };
		BOOL isExt{ (lParam >> 24) & 1 }, isAlt{ uMsg == WM_SYSKEYDOWN || uMsg == WM_SYSKEYUP },
			wasDown{ (lParam >> 30) & 1 }, isUp{ uMsg == WM_SYSKEYUP || uMsg == WM_KEYUP };
		for (auto& fn : g_keyboard_functions) {
			fn(key, repeats, scanCode, isExt, isAlt, wasDown, isUp);
		}
	}

	int shv_script_hook::get_game_verison() {
		return GetModuleHandleA("steam_api64.dll") ? VER_1_0_1493_1_STEAM : VER_1_0_1493_1_NOSTEAM;
	}

	BYTE* shv_script_hook::get_script_handle_base_address(int handle) {
		return (BYTE*)insight::pointers::get()->g_handle_to_pointer(handle);
	}

	void shv_script_hook::present_call_back_register(present_callback cb) {
	}

	void shv_script_hook::present_call_back_unregister(present_callback cb) {
	}

	Entity get_entity_from_handle(rage::CEntity* handle) {
		if (handle)
			return insight::pointers::get()->g_pointer_to_handle(handle);
		return NULL;
	}

	template <typename t>
	int get_pool_objects(int type, int* arr, int arrSize) {
		std::vector<u64> objects{};
		if (auto replay_interface{ *insight::pointers::get()->g_replay_interface }) {
			t* inf;
			switch (type) {
			case 0: {
				inf = (t*)replay_interface->m_vehicle_interface;
			} break;
			case 1: {
				inf = (t*)replay_interface->m_ped_interface;
			} break;
			case 2: {
				inf = (t*)replay_interface->m_object_interface;
			} break;
			case 3: {
				inf = (t*)replay_interface->m_pickup_interface;
			} break;
			}
		}
		for (int32_t i{}; i != objects.size(); ++i) {
			arr[i] = get_entity_from_handle((rage::CEntity*)objects[i]);
		}
		return objects.size();
	}

	int shv_script_hook::world_get_all_vehicles(int* arr, int arrSize) {
		return get_pool_objects<rage::CVehicleInterface>(0, arr, arrSize);
	}

	int shv_script_hook::world_get_all_peds(int* arr, int arrSize) {
		return get_pool_objects<rage::CPedInterface>(1, arr, arrSize);
	}

	int shv_script_hook::world_get_all_objects(int* arr, int arrSize) {
		return get_pool_objects<rage::CObjectInterface>(2, arr, arrSize);
	}
	int shv_script_hook::world_get_all_pickups(int* arr, int arrSize) {
		return get_pool_objects<rage::CPickupInterface>(3, arr, arrSize);
	}

	int shv_script_hook::register_raw_streaming_file(const std::string& fileName, const std::string& registerAs) {
		int32_t id{ -1 };
		insight::pointers::get()->g_register_streaming_texture(&id, fileName.c_str(), true, registerAs.c_str(), false);
		return id;
	}
}