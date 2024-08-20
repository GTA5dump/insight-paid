#pragma once
namespace insight {
	struct config_context {
		std::string m_name;
		std::filesystem::path m_path;
	};

	class config {
		config();
	public:
		void load_config_files();
		void load_config(std::string name);
		void save_config(std::string name);
		static void load_default();
	public:
		static config* get() {
			static config i{};
			return &i;
		}
		std::vector<std::string> m_configs;
	};
}