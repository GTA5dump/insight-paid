#include "common.hpp"
#include "features.hpp"
#include "util/script/fiber_pool.hpp"
#include "util/logger.hpp"
#include "game/hooking/hooking.hpp"
#include "cheat/pointers/pointers.hpp"
#include "cheat/render/renderer.hpp"
#include "util/script/script_mgr.hpp"
#include "g3log/crashhandler.hpp"
#include "util/textures/textures.hpp"
#include <Psapi.h>
#include "game/invoker/invoker.hpp"
#include "util/discord/Discord_Integration.hpp"
#include <dbghelp.h>
#include "cheat/menu/helper/ui.hpp"
#include "util/input/input.hpp"
#include "cheat/features/features.hpp"
#include "dll/entry.hpp"
#include <util/threads/threads.hpp>
#include "util/exceptions/handler.hpp"
#pragma comment(lib, "dbghelp.lib")

void notifty44(std::string notify) {
}

BOOL APIENTRY DllMain(HMODULE hmod, DWORD reason, PVOID) {
	using namespace insight;
	if (reason == DLL_PROCESS_ATTACH) {
		g_hmodule = hmod;
		insight::threads::add_job(dll::entry_point, hmod);
	}

	return true;
}