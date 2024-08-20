#ifndef COMMON_INC
#define COMMON_INC

#define _WIN32_WINNT _WIN32_WINNT_WIN7
#define STB_IMAGE_IMPLEMENTATION
#define CURL_STATICLIB
#include <sdkddkver.h>
#include <winsock2.h>
#include <windows.h>
#include <wrl/client.h>
#include <d3d11.h>

#include <cinttypes>
#include <cstddef>
#include <cstdint>
#include <timeapi.h>

#include <chrono>
#include <ctime>

#include <filesystem>
#include <fstream>
#include <iostream>
#include <iomanip>

#include <atomic>
#include <mutex>
#include <thread>

#include <memory>
#include <new>

#include <sstream>
#include <string>
#include <string_view>

#include <algorithm>
#include <functional>
#include <utility>

#include <stack>
#include <vector>

#include <typeinfo>
#include <type_traits>

#include <exception>
#include <stdexcept>

#include <any>
#include <optional>
#include <variant>

#include <format>
#include <nlohmann/json.hpp>
#include "util/logger.hpp"

#include "game/gta/natives.hpp"
#include "ped/CPed.hpp"
#include <rage/joaat.hpp>
#pragma comment(lib, "Winmm.lib")
#include "util/security/xorstr.hpp"
#include "util/timer.hpp" //why include it at all places : idk 
#define DEV
using namespace std::chrono_literals;
namespace insight
{
	using namespace std::chrono_literals;

	template <typename T>
	using comptr = Microsoft::WRL::ComPtr<T>;

	inline HMODULE g_hmodule{};
	inline HANDLE g_main_thread{};
	inline DWORD g_main_thread_id{};
	inline std::atomic_bool g_running{ false };
	inline bool g_input_disabled{};
	inline float g_delta{};
	inline int g_frame_count{};
}
using u64 = uint64_t;
using i64 = int64_t;
using u32 = uint32_t;
using i32 = int32_t;
using u16 = uint16_t;
using i16 = int16_t;
using u8 = uint8_t;
using i8 = int8_t;
using cc = const char;
using ccp = cc*;
using fp = float_t;
using db = double_t;
inline consteval uint32_t operator ""_joaat(const char* str, size_t) { return rage::joaat(str); }
template<size_t N>
struct template_str
{
	constexpr template_str(const char(&str)[N])
	{
		std::copy_n(str, N, value);
	}

	char value[N];
};
template <typename a, typename v>
inline void put(a addr, v value) {
	memcpy(reinterpret_cast<void*>(addr), &value, sizeof(value));
}
template<typename a>
inline void nop(a addr, i32 size) {
	mset<a>(addr, 0x90, size);
}
template <typename a, typename t>
inline void call(a addr, t func) {
	put<a, u8>(addr, 0xE8);
	put<u64, i32>(reinterpret_cast<u64>(addr) + 1, reinterpret_cast<u64>(func) - reinterpret_cast<u64>(addr) - 5);
}
template <typename t>
	requires std::is_function_v<t>
using fnptr = std::add_pointer_t<t>;

#endif
