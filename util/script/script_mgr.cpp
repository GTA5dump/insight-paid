#include "common.hpp"
#include <script/scrThread.hpp>
#include "util/gta_util.hpp"
#include "game/invoker/invoker.hpp"
#include "cheat/pointers/pointers.hpp"
#include "util/script/script_mgr.hpp"
#include <random>
#include <string>
namespace insight {
	std::string generate_random_name()
	{
		static const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
		const size_t charsetSize = sizeof(charset) - 1;

		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<size_t> dist(0, charsetSize - 1);

		const size_t nameLength = 10; 
		std::string randomName(nameLength, ' ');

		for (size_t i = 0; i < nameLength; ++i)
		{
			randomName[i] = charset[dist(gen)];
		}

		return randomName;
	}
}
namespace insight
{
	void script_mgr::add_script(const char* scriptName, std::unique_ptr<script> script)
	{
		std::lock_guard lock(m_mutex);
		m_scripts.emplace_back(scriptName, std::move(script));
	}
	void script_mgr::add_script(std::unique_ptr<script> script)
	{
		std::lock_guard lock(m_mutex);
		const char* scriptName = generate_random_name().c_str(); 
		m_scripts.emplace_back(scriptName, std::move(script));
	}

	void script_mgr::remove_all_scripts()
	{
		std::lock_guard lock(m_mutex);
		m_scripts.clear();
	}
	void script_mgr::remove_script(const char* scriptName)
	{
		std::lock_guard lock(m_mutex);

		m_scripts.erase(std::remove_if(m_scripts.begin(), m_scripts.end(),
			[scriptName](const std::pair<const char*, std::unique_ptr<script>>& entry) {
				return entry.first != nullptr && strcmp(entry.first, scriptName) == 0;
			}), m_scripts.end());
	}

	void script_mgr::remove_script(script* scriptToRemove)
	{
		std::lock_guard lock(m_mutex);

		auto it = std::remove_if(m_scripts.begin(), m_scripts.end(),
			[scriptToRemove](const std::pair<const char*, std::unique_ptr<script>>& entry) {
				return entry.second.get() == scriptToRemove;
			});

		if (it != m_scripts.end())
		{
			m_scripts.erase(it, m_scripts.end());
		}
	}
	void script_mgr::tick() {
	//	insight::gta_util::execute_as_script("main_persistent"_joaat, std::mem_fn(&script_mgr::tick_internal), this);
		script_mgr::tick_internal();
	}

	void script_mgr::tick_internal()
	{
		static bool ensure_main_fiber = (ConvertThreadToFiber(nullptr), true);
		static bool ensure_native_handlers = (insight::g_native_invoker.cache_handlers(), true);

		std::lock_guard lock(m_mutex);
		for (auto const &script : m_scripts)
		{
			script.second.get()->tick();
		}
	}
}
