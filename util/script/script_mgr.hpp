#pragma once
#include "common.hpp"
#include "script.hpp"

namespace insight
{
	class script_mgr
	{
	public:
		explicit script_mgr() = default;
		~script_mgr() = default;

		void add_script(const char* scriptName, std::unique_ptr<script> script);
		void add_script(std::unique_ptr<script> script);
		void remove_all_scripts();
		void remove_script(script* scriptToRemove);
		void remove_script(const char* scriptName);
		void tick();
	private:
		void tick_internal();
	private:
		std::recursive_mutex m_mutex;
	public:
		std::vector<std::pair<const char*, std::unique_ptr<script>>> m_scripts;
	};

	inline script_mgr g_script_mgr;
}
