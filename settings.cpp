
#include "util/textures/theme.hpp"
#include "cheat/script/script.hpp"
#include "cheat/menu/helper/ui.hpp"
#include "util/panels/panels.hpp"
#include "util/config/config.hpp"

std::string text_case[]{
	"None",
	"lower case",
	"UPPER CASE",
	"Title Case"
};
std::string m_selected_config;

namespace insight {
	void script_ui::settings() {
		render::push<sub>("Settings", "Settings"_joaat, [](sub* ui) {
			ui->push(submenu("Menu").add_target("Settings_Menu"_joaat));
			ui->push(submenu("Panels").add_target("Panels"_joaat));
			ui->push(submenu("Hotkeys").add_target("Hotkeys"_joaat));
			ui->push(submenu("Config").add_target("Config"_joaat).set_action([] {
				config::get()->load_config_files();
			}));
			ui->push(submenu("Theme").add_target("UIF"_joaat));

			ui->push(submenu("Translations").add_target("Translation"_joaat));
			ui->push(info("Misc"));
			ui->push(array<std::string, int>("Text Case Type").add_array(&text_case).add_position(&m_text_case));
			ui->push(toggle("Log Script Events").add_toggle(&detour::protections::g_log_script_events));
			ui->push(toggle("Log Can Apply Data").add_toggle(&detour::protections::g_log_cad));
			ui->push(icon("Unload").add_icon("Refresh").set_action([] {
				g_running = false;
			}));
			panel settings(0.2f, 0.f, 0.022f);
			settings.start_panel("Settings");
			settings.push("Build", "Developer");
			settings.push("Loaded Config", "Default");
			settings.push("Hotkeys Amount", std::to_string(input::get()->m_hotkeys.size()));
			settings.end_panel();
		});

		render::push<sub>("Panels", "Panels"_joaat, [](sub* ui) {
			ui->push(number<float>("Panel Spacing X").add_min(0.f).add_max(1.f).add_number(&panels::get()->m_panel_spacing).add_precision(2).add_step(0.01f));
			ui->push(number<float>("Panel Spacing Y").add_min(0.f).add_max(1.f).add_number(&panels::get()->m_panel_spacing_under).add_precision(2).add_step(0.01f));
		});

		render::push<sub>("Config", "Config"_joaat, [](sub* ui) {
			ui->push(icon("Load Configs").add_icon("Refresh").set_action([] {
				config::get()->load_config_files();
				}));
			ui->push(icon("Save Config").add_icon("Save").set_action([] {
				config::get()->save_config(tasks::get_keyboard_input());
				}));
			ui->push(icon("Clear Configs").add_icon("Bin").set_action([] {
				config::get()->m_configs.clear();
				}));
			ui->push(info("Configs"));
			for (auto config : config::get()->m_configs) {
				ui->push(submenu(config).add_target("selected_config"_joaat).add_function([config] {
					m_selected_config = config;
				}));
			}
		});
		render::push<sub>("Config", "UIF"_joaat, [](sub* ui) {
			ui->push(icon("Save Preferences").add_icon("Save").set_action([] {
				theme::get()->save();
				}));
			ui->push(icon("Reload Preferences").add_icon("Refresh").set_action([] {
				theme::get()->load();
				}));
		});

		render::push<sub>(m_selected_config, "selected_config"_joaat, [](sub* ui) {
			ui->push(icon("Reload").add_icon("Refresh").set_action([] {
				config::get()->load_config(m_selected_config);
				}));
			ui->push(icon("Save").add_icon("Save").set_action([] {
				config::get()->save_config(m_selected_config);
				}));
			ui->push(icon("Clear Configs").add_icon("Bin").set_action([] {
				auto config_path = std::filesystem::path(std::getenv(xorstr_("appdata"))).append(xorstr_("insight")).append(xorstr_("configs")).append(m_selected_config + ".cfg");

				std::remove(config_path.string().c_str());
			}));
	    });
		render::push<sub>("Translation", "Translation"_joaat, [](sub* ui) {
			ui->push(icon("Reload Table").add_icon("Refresh").add_description("Download Table From Discord Server").set_action([] {
				translation::get()->enable();
			}));
		});
		render::push<sub>("Hotkeys", "Hotkeys"_joaat, [](sub* ui) {
			ui->push(icon("Reload Hotkeys").add_icon("Refresh").set_action([] {
				input::get()->load_hotkeys();
			}));
			ui->push(icon("Save Hotkeys").add_icon("Save").set_action([] {
				input::get()->save_hotkeys();
			}));
			ui->push(icon("Clear Hotkeys").add_icon("Bin").set_action([] {
				input::get()->m_hotkeys.clear();
			}));
			ui->push(info("Hotkeys"));
			for (auto hotkey : input::get()->m_hotkeys) {
				ui->push(icon(std::format("{} : ~c~{}",hotkey.second.m_name, input::get()->g_key_names[hotkey.second.m_key])).add_icon("Bin").add_function([=] {
					input::get()->m_hotkeys.erase(hotkey.first);
				}));
			}
		});
		render::push<sub>("Menu", "Settings_Menu"_joaat, [](sub* ui) {
			ui->push(submenu("Header").add_target("Settings_Header"_joaat));
			ui->push(submenu("Options").add_target("Settings_Options"_joaat));
			ui->push(submenu("Title").add_target("Settings_Title"_joaat));
			ui->push(submenu("Footer").add_target("Settings_Footer"_joaat));
			ui->push(submenu("Scrollbar").add_target("Settings_Scrollbar"_joaat));
			ui->push(submenu("Description").add_target("Settings_Description"_joaat));
			ui->push(submenu("Animations").add_target("Settings_Animations"_joaat));
			ui->push(number<float>("Width").add_min(0.f).add_max(1.f).add_number(&render::get()->m_width).add_step(0.001f).add_precision(3));
		});		

		render::push<sub>("Animations", "Settings_Animations"_joaat, [](sub* ui) {
			ui->push(number<float>("Scroller").add_description("Set To Max Speed To Disable Animations").add_min(0.f).add_max(2.f).add_number(&render::get()->m_speed).add_step(0.001f).add_precision(3));
			ui->push(number<float>("Background").add_description("Set To Max Speed To Disable Animations").add_min(0.f).add_max(2.f).add_number(&render::get()->m_bg_speed).add_step(0.001f).add_precision(3));
			ui->push(number<float>("Scroll Bar").add_description("Set To Max Speed To Disable Animations").add_min(0.f).add_max(2.f).add_number(&render::get()->m_scroll_speed).add_step(0.001f).add_precision(3));
		});


		render::push<sub>("Header", "Settings_Description"_joaat, [](sub* ui) {
			ui::push()->color_option(ui, "Background", &render::get()->m_description.m_color);
			ui->push(info("Text"));
			ui::push()->color_option(ui, "Text Color", &render::get()->m_description.m_text_color);
			ui->push(number<float>("Scale").add_min(0.f).add_max(1.f).add_number(&render::get()->m_description.m_font_scale).add_step(0.01f).add_precision(2));
			ui->push(number<int>("Font").add_min(0).add_max(font_limit).add_number(&render::get()->m_description.m_font).add_step(1).add_precision(0));
			ui->push(info("Rect"));
			ui->push(number<float>("Height").add_min(0.f).add_max(1.f).add_number(&render::get()->m_description.m_height).add_step(0.001f).add_precision(3));
			});

		render::push<sub>("Header", "Settings_Header"_joaat, [](sub* ui) {
			ui::push()->color_option(ui, "Background", &render::get()->m_header.m_color);
			ui->push(info("Text"));
			ui->push(keyboard("Text").add_input(&render::get()->m_header.m_text));
			if (!render::get()->m_header.m_text.empty()) {
				ui::push()->color_option(ui, "Text Color", &render::get()->m_header.m_text_color);

				ui->push(number<float>("Scale").add_min(0.f).add_max(1.f).add_number(&render::get()->m_header.m_font_scale).add_step(0.01f).add_precision(2));
				ui->push(number<int>("Font").add_min(0).add_max(font_limit).add_number(&render::get()->m_header.m_font).add_step(1).add_precision(0));
			}
			ui->push(info("Rect"));
			ui->push(number<float>("Height").add_min(0.f).add_max(1.f).add_number(&render::get()->m_header.m_height).add_step(0.001f).add_precision(3));
		});

		render::push<sub>("Options", "Settings_Options"_joaat, [=](sub* ui) {
			ui->push(toggle("Custom").add_toggle(&render::get()->m_option.custom_texture));
			ui::push()->color_option(ui, "Background", &render::get()->m_option.m_color);
			ui::push()->color_option(ui, "Text", &render::get()->m_option.m_text_color);
			ui::push()->color_option(ui, "Selected Text", &render::get()->m_option.m_selected_text_color);
			ui->push(info("Text"));
			ui->push(number<float>("Scale").add_min(0.f).add_max(1.f).add_number(&render::get()->m_option.m_font_scale).add_step(0.001f).add_precision(3));
			ui->push(number<int>("Font").add_min(0).add_max(font_limit).add_number(&render::get()->m_option.m_font).add_step(1).add_precision(0));
			ui->push(info("Rect"));
			ui->push(number<float>("Height").add_min(0.f).add_max(1.f).add_number(&render::get()->m_option.m_height).add_step(0.001f).add_precision(3));
		});

		render::push<sub>("Title", "Settings_Title"_joaat, [=](sub* ui) {
			ui::push()->color_option(ui, "Background", &render::get()->m_title.m_color);
			ui::push()->color_option(ui, "Text", &render::get()->m_title.m_text_color);
			ui->push(info("Text"));
			ui->push(number<float>("Scale").add_min(0.f).add_max(1.f).add_number(&render::get()->m_title.m_font_scale).add_step(0.001f).add_precision(3));
			ui->push(number<int>("Font").add_min(0).add_max(font_limit).add_number(&render::get()->m_title.m_font).add_step(1).add_precision(0));
			ui->push(info("Rect"));
			ui->push(number<float>("Height").add_min(0.f).add_max(1.f).add_number(&render::get()->m_title.m_height).add_step(0.001f).add_precision(3));
		});

		render::push<sub>("Scrollbar", "Settings_Scrollbar"_joaat, [=](sub* ui) {
			ui::push()->color_option(ui, "Scrollbar", &render::get()->m_scrollbar.m_color);
			ui::push()->color_option(ui, "Scroller", &render::get()->m_scroller_color);
			ui->push(info("Sizes"));
			ui->push(number<float>("Width").add_min(0.f).add_max(1.f).add_number(&render::get()->m_scrollbar.m_width).add_step(0.001f).add_precision(3));
			ui->push(number<float>("In Width").add_min(0.f).add_max(1.f).add_number(&render::get()->m_scrollbar.m_in_width).add_step(0.001f).add_precision(3));
			ui->push(info("Sprites"));
			ui->push(number<float>("Width").add_min(0.f).add_max(1.f).add_number(&render::get()->m_scrollbar.m_ends.x).add_step(0.001f).add_precision(3));
			ui->push(number<float>("Height").add_min(0.f).add_max(1.f).add_number(&render::get()->m_scrollbar.m_ends.y).add_step(0.001f).add_precision(3));
		});


		render::push<sub>("Footer", "Settings_Footer"_joaat, [=](sub* ui) {
			ui::push()->color_option(ui, "Background", &render::get()->m_footer.m_color);
			ui::push()->color_option(ui, "Text", &render::get()->m_footer.m_text_color);
			ui->push(info("Text"));
			ui->push(number<float>("Scale").add_min(0.f).add_max(1.f).add_number(&render::get()->m_footer.m_font_scale).add_step(0.001f).add_precision(3));
			ui->push(number<int>("Font").add_min(0).add_max(font_limit).add_number(&render::get()->m_footer.m_font).add_step(1).add_precision(0));
			ui->push(info("Rect"));
			ui->push(number<float>("Height").add_min(0.f).add_max(1.f).add_number(&render::get()->m_footer.m_height).add_step(0.001f).add_precision(3));
			ui->push(info("Sprite"));
			ui->push(number<float>("Width").add_min(0.f).add_max(1.f).add_number(&render::get()->m_footer.m_icon_size.x).add_step(0.001f).add_precision(3));
			ui->push(number<float>("Height").add_min(0.f).add_max(1.f).add_number(&render::get()->m_footer.m_icon_size.y).add_step(0.001f).add_precision(3));
		});
	}
}