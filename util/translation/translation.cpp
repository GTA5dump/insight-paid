#include "translation.hpp"
#include "rage/Joaat.hpp"
#include "cheat/render/render.hpp"

using jsonf = nlohmann::json;
jsonf g_loader44;

namespace insight {
	void translation::enable() {
		translation::get()->m_translate = true;

		auto config_path = std::filesystem::path(std::getenv(xorstr_("appdata"))).append(xorstr_("insight")).append("cheat.translation");
		std::ifstream file(config_path);

		if (file.good()) {
			file >> g_loader44;
		}
		else {
			translation::get()->m_translate = false;
			return;
		}

		try {
			LOG(INFO) << xorstr_("Found ") << g_loader44.size() << xorstr_("Strings In Translation Table");
			for (auto& item : g_loader44.items()) {
				try {
					const std::string& original_string = item.key();
					std::string replacment = g_loader44[original_string][xorstr_("Replacement")];
					translation::get()->m_translation_table.insert({ rage::joaat(original_string),replacment });
				}
				catch (std::exception w) {

				}
 			}
		}
		catch (std::exception w) {

		}
		render::get()->m_option.m_font = 0;
		render::get()->m_header.m_font = 0;
		render::get()->m_description.m_font = 0;
		render::get()->m_footer.m_font = 0; 
		render::get()->m_title.m_font = 0;
	}

	void translation::disbale() {
		translation::get()->m_translate = false;
	}

	void translation::push(std::string string) {
		static bool saved_once;
		using jsonf = nlohmann::json;
		static jsonf save;
		std::filesystem::path cheat_path;
		cheat_path.append(std::getenv("appdata"));
		cheat_path.append("Insight");
		cheat_path.append("cheat.translation");
		std::ofstream file(cheat_path, std::ios::out | std::ios::trunc);

		save[string.c_str()]["Replacement"] = string.c_str();
		save["Fonts"]["Option"] = render::get()->m_option.m_font;
		save["Fonts"]["Subtitle"] = render::get()->m_title.m_font;
		save["Fonts"]["Header"] = render::get()->m_header.m_font;
		save["Fonts"]["Description"] = render::get()->m_description.m_font;
		std::ofstream json_file(cheat_path);
		json_file << std::setw(4) << save << std::endl;
		json_file.close();
	}

	std::string translation::get(std::string string) {
		if (!translation::get()->m_translate) {
			return string;
		}
		if (auto it = translation::get()->m_translation_table.find(rage::joaat(string));  it != translation::get()->m_translation_table.end()) {
			return &(it->second)[0];
		}
		else {
			return string;
		}
	}

	std::string trans(std::string string) {
		return translation::get(string);
	}


	std::string to_upper_case(std::string str) {
		std::transform(str.begin(), str.end(), str.begin(),
			[](unsigned char c) { return std::toupper(c); });
		return str;
	}

	std::string to_lower_case(std::string str) {
		std::transform(str.begin(), str.end(), str.begin(),
			[](unsigned char c) { return std::tolower(c); });
		return str;
	}

	std::string to_title_case(std::string str) {
		bool newWord = true;
		std::transform(str.begin(), str.end(), str.begin(),
			[&newWord](char c) {
				if (std::isspace(static_cast<unsigned char>(c))) {
					newWord = true;
					return c;
				}
				else if (newWord) {
					newWord = false;
					return static_cast<char>(std::toupper(static_cast<unsigned char>(c)));
				}
				else {
					return static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
				}
			});
		return str;
	}


	void remove_last_segment(std::string* string_ptr) {
		std::string& str = *string_ptr;

		if (!str.empty() && str[str.size() - 1] == '/') {
			str = str.substr(0, str.size() - 1);
		}

		size_t found = str.find_last_of("/");

		if (found != std::string::npos) {
			str = str.substr(0, found + 1);  
		}
	}

	std::string get_case_state(std::string string) {
		if (m_text_case == 1) {
			return to_lower_case(string);
		}
		if (m_text_case == 2) {
			return to_upper_case(string);
		}
		if (m_text_case == 3) {
			return to_title_case(string);
		}
		return string;
	}
}