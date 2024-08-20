#include "config.hpp"

#include "util/notify/notify.hpp"
#include "cheat/render/render.hpp"
#include "cheat/features/manager/manager.h"
#include "util/security/xorstr.hpp"

float* convert_to_float(i64* pointer) {
	return reinterpret_cast<float*>(pointer);
}

int* convert_to_int(i64* pointer) {
	return reinterpret_cast<int*>(pointer);
}

using jsonf = nlohmann::json;
jsonf g_loader;

namespace insight {
	void config::load_config_files() {
		m_configs.clear();
		auto path = std::filesystem::path(std::getenv(xorstr_("appdata"))).append(xorstr_("insight")).append(xorstr_("configs"));
		if (std::filesystem::exists(path)) {
			std::filesystem::directory_iterator it{ path };
			for (auto&& entry : it) {
				if (entry.is_regular_file()) {
					auto path{ entry.path() };
					if (path.has_filename() && path.extension() == xorstr_(".cfg")) {
						m_configs.push_back({ path.stem().string() });
					}
				}
			}
		}
	}

	void config::save_config(std::string name) {
		static nlohmann::json save;

		auto config_path = std::filesystem::path(std::getenv(xorstr_("appdata"))).append(xorstr_("insight")).append(xorstr_("configs")).append(name + xorstr_(".cfg"));

		std::ofstream file(config_path, std::ios::out | std::ios::trunc);

		for (const auto& feature : feature_manager::get()->m_features) {
			if (auto ptr_feature = feature_manager::get()->get_feature<float_feature>(feature->m_id.c_str())) {
				if (feature->get_type() == feature_type::float_feature) {
					save[feature->m_id][xorstr_("Float Value")] = ptr_feature->m_value.floating_point;
				}
			}

			if (auto ptr_feature = feature_manager::get()->get_feature<int_feature>(feature->m_id.c_str())) {
				if (feature->get_type() == feature_type::int_feature) {
					save[feature->m_id][xorstr_("Int Value")] = ptr_feature->m_value.floating_point;
				}
			}

			if (auto ptr_feature = feature_manager::get()->get_feature<toggle_feature>(feature->m_id.c_str())) {
				if (feature->get_type() == feature_type::toggle_feature) {
					save[feature->m_id][xorstr_("Boolean Value")] = ptr_feature->m_value.toggle;
				}
			}

			if (auto ptr_feature = feature_manager::get()->get_feature<toggle_int_feature>(feature->m_id.c_str())) {
				if (feature->get_type() == feature_type::toggle_int_feature) {
					save[feature->m_id][xorstr_("Int Value")] = ptr_feature->m_number_value.integer;
					save[feature->m_id][xorstr_("Boolean Value")] = ptr_feature->m_toggle_value.toggle;
				}
			}

			if (auto ptr_feature = feature_manager::get()->get_feature<toggle_float_feature>(feature->m_id.c_str())) {
				if (feature->get_type() == feature_type::toggle_float_feature) {
					save[feature->m_id][xorstr_("Float Value")] = ptr_feature->m_number_value.floating_point;
					save[feature->m_id][xorstr_("Boolean Value")] = ptr_feature->m_toggle_value.toggle;
				}
			}

		}

		std::ofstream json_file(config_path);
		json_file << std::setw(4) << save << std::endl;
		notify::send(xorstr_("Config Manager"), std::format("Saved Config {}", name));
		m_configs.push_back({ name });
	}

	void config::load_config(std::string name) {

		auto config_path = std::filesystem::path(std::getenv(xorstr_("appdata"))).append(xorstr_("insight")).append(xorstr_("configs")).append(name + xorstr_(".cfg"));
		LOG(INFO) << xorstr_("Configuration from '") << config_path.stem().string() << xorstr_("' has been loaded.");
		std::ifstream file(config_path);

		if (file.good()) {
			file >> g_loader;
		}
		else {
			LOG(WARNING) << xorstr_("File Not Found");
			return;
		}
		
		try {
			LOG(INFO) << xorstr_("Found ") << g_loader.size() << xorstr_(" Saved Options");

			for (auto& item : g_loader.items()) {
				try {
					const std::string& key = item.key();					
					if (g_loader[key].contains(xorstr_("Float Value")) && !g_loader[key].contains(xorstr_("Boolean Value"))) {
						float value = g_loader[key][xorstr_("Float Value")];
						if (auto feature = feature_manager::get()->get_feature<toggle_int_feature>(rage::joaat(key))) {
							feature_manager::get()->get_feature<float_feature>(key.c_str())->m_value.floating_point = value;
						}
					}

					if (g_loader[key].contains(xorstr_("Int Value")) && !g_loader[key].contains(xorstr_("Boolean Value"))) {
						int value = g_loader[key][xorstr_("Int Value")];
						if (auto feature = feature_manager::get()->get_feature<int_feature>(rage::joaat(key))) {
							feature->m_value.integer = value;
						}
					}

					if (g_loader[key].contains(xorstr_("Int Value")) && g_loader[key].contains(xorstr_("Boolean Value"))) {
						int intValue = g_loader[key][xorstr_("Int Value")];
						bool boolValue = g_loader[key][xorstr_("Boolean Value")];

						if (auto feature = feature_manager::get()->get_feature<toggle_int_feature>(rage::joaat(key))) {
							feature->m_number_value.integer = intValue;
							feature->m_toggle_value.toggle = boolValue;
						}
					}

					if (g_loader[key].contains(xorstr_("Boolean Value")) && !g_loader[key].contains(xorstr_("Int Value"))) {
						bool value = g_loader[key][xorstr_("Boolean Value")];
						if (auto toggle = feature_manager::get()->get_feature<toggle_feature>(rage::joaat(key))) {
							feature_manager::get()->get_feature<toggle_feature>(key.c_str())->m_value.toggle = value;
						}
					}

					if (g_loader[key].contains(xorstr_("Float Value")) && g_loader[key].contains(xorstr_("Boolean Value"))) {
						float intValue = g_loader[key][xorstr_("Float Value")];
						bool boolValue = g_loader[key][xorstr_("Boolean Value")];

						if (auto feature = feature_manager::get()->get_feature<toggle_float_feature>(rage::joaat(key))) {
							feature->m_number_value.floating_point = intValue;
							feature->m_toggle_value.toggle = boolValue;
						}
					}
				}
				catch (const std::exception& e) { 
					LOG(FATAL) << e.what();
				}
			}
		}
		catch (const std::exception& e) { 
			LOG(FATAL) << e.what();
			LOG(INFO) << xorstr_("Outdated Config, Delete {} from configs folder"), name;

		}
		notify::send(xorstr_("Config Manager"), std::format("Loaded Config {}", name));
	}

	config::config() {
	}

	auto config::load_default() -> void {
		auto config_path = std::filesystem::path(std::getenv(xorstr_("appdata"))).append(xorstr_("insight")).append(xorstr_("configs")).append(xorstr_("Default.cfg"));

		std::ifstream file(config_path);

		if (file.good()) {
			get()->load_config(xorstr_("Default"));
		}
		else {
			get()->save_config(xorstr_("Default"));
			LOG(INFO) << xorstr_("Created Default Config File");
			notify::send("Config", "Created Default Config");
		}
	}
}