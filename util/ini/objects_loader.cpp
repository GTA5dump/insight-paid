#include <iostream>
#include "ini_util.hpp"
namespace insight {

	void ini::load_objects_ini()
	{
		auto path_str = std::filesystem::path(std::getenv(xorstr_("appdata"))).append(xorstr_("insight")).append(xorstr_("ini")).append(xorstr_("objects.ini"));
		all_objects.clear();
		std::ifstream path(path_str.generic_string());
		if (path.is_open())
		{
			LOG(INFO) << xorstr_("Phrasing objects.ini");
			std::string name;
			while (getline(path, name))
			{
				all_objects.push_back(name);
			}

		}
		else { LOG(WARNING) << xorstr_("Failed Phrasing objects.ini");
		}
	}

	void ini::load_favorite_objects_ini()
	{
		auto path_str = std::filesystem::path(std::getenv(xorstr_("appdata"))).append(xorstr_("insight")).append(xorstr_("ini")).append(xorstr_("favorite_objects.ini"));
		favorite_objects_name.clear();
		favorite_objects_hash.clear();
		std::ifstream path(path_str.generic_string());
		if (path.is_open())
		{
			//console::info(xorstr_("Phrasing favorite_objects.ini"));
			std::string allline;
			while (getline(path, allline))
			{
				std::size_t textbefore = allline.find(",");
				std::string hash = allline.substr(0, textbefore);
				std::string real_name = allline.substr(allline.find(",") + 1);
				favorite_objects_name.push_back(real_name);
				favorite_objects_hash.push_back(hash);
			}

		}
		else { LOG(WARNING) << xorstr_("Failed Phrasing favorite_objects.ini"); }
	}
	bool does_line_exist(const std::string& file_path, const std::string& line)
	{
		std::ifstream file(file_path);
		if (file.is_open())
		{
			std::string file_line;
			while (getline(file, file_line))
			{
				if (file_line == line)
				{
					file.close();
					return true;
				}
			}
			file.close();
		}
		return false;
	}
	void ini::add_favorite_object(const std::string hash, const std::string real_name)
	{
		auto path_str = std::filesystem::path(std::getenv(xorstr_("appdata")))
			.append(xorstr_("insight"))
			.append(xorstr_("ini"))
			.append(xorstr_("favorite_objects.ini"));
		std::string new_line = hash + "," + real_name;
		if (!does_line_exist(path_str.generic_string(), new_line))
		{
			std::ofstream file(path_str.generic_string(), std::ios_base::app);
			if (file.is_open()) {
				file << new_line << std::endl;
				file.close();
			}
			else {
				LOG(WARNING) << xorstr_("Failed to open favorite_objects.ini for writing");
			}
		}
	}
}
