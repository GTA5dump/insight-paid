#pragma once
namespace insight {
	class translation {
	public:
		static void enable();
		static void disbale();
		static void reload(std::string string);
	public:
		static std::string get(std::string string);
		static void push(std::string string);
	public:
		static translation* get() {
			static translation i{}; 
			return &i;
		}
	public:
		std::unordered_map<u32, std::string> m_translation_table;
		std::vector<std::string> m_files{};
		bool m_translate = false;
	};

	inline int m_text_case;
	extern std::string trans(std::string string); 
	extern std::string get_case_state(std::string string);
	extern void remove_last_segment(std::string* str);
	extern std::string to_lower_case(std::string str);
	extern std::string to_upper_case(std::string str);
	extern std::string to_title_case(std::string str);
}