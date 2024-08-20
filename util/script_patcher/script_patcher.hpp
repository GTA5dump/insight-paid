#pragma once
#include "script_patch.hpp"

namespace insight {
	class script_patcher {
	public:
		void add_patch(script_patch&& patch);
		void on_script_load(rage::scrProgram* program);
		std::uint8_t** get_script_byte_code(uint32_t script);
		void update();
	public:
		void register_patches();
	private:
		script_data* get_data_for_script(uint32_t script);
		bool does_script_have_patches(uint32_t script);
		void create_data_for_script(rage::scrProgram* program);
		void update_all_patches_for_script(uint32_t script);
	private:
		std::vector<script_patch> m_script_patches;
		std::unordered_map<uint32_t, std::unique_ptr<script_data>> m_script_data;
	};
	
	inline script_patcher g_script_patcher;
}