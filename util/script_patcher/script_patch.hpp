#pragma once
#include "rage/Joaat.hpp"
#include "util/memory/pattern.hpp"
namespace insight {
	
	class script_data {
	public:
		script_data(std::uint32_t codeSize, std::uint8_t** bytecode, std::uint32_t numPages) : m_code_size(codeSize), m_byte_code(bytecode), m_num_pages(numPages) {}
		script_data(const script_data&) = delete;
		script_data& operator=(const script_data&) = delete;

		~script_data() {
			for (uint32_t i = 0u; i < m_num_pages; i++) {
				delete[] m_byte_code[i];
			}

			delete[] m_byte_code;
			m_byte_code = nullptr;
		}
	public:
		uint32_t m_code_size;
		uint8_t** m_byte_code;
	private:
		uint32_t m_num_pages;
	};
	class script_patch
	{
	public:
		script_patch(rage::joaat_t script, const memory::pattern pattern, int32_t offset, std::vector<uint8_t> patch, bool* enable_bool);
	public:
		static std::uint8_t* get_code_address(script_data* data, std::uint32_t index);
		static const std::optional<uint32_t> get_code_location_by_pattern(script_data* data, const memory::pattern& pattern);
		void enable(script_data* data);
		void disable(script_data* data);
	public:
		rage::joaat_t m_script;
		const memory::pattern m_pattern;
		int32_t m_offset;
		std::vector<uint8_t> m_patch;
		std::vector<uint8_t> m_original;
		bool* m_bool;
		int32_t m_index;
	public:
		inline rage::joaat_t get_script() {
			return m_script;
		}
		void update(script_data* data);
	};
}