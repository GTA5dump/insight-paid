#include "rage/Joaat.hpp"
#include "cheat/render/render.hpp"
#include "theme.hpp"
using json = nlohmann::json;

namespace insight {
	void theme::save() {
        json header_json = {
    {"m_height", render::get()->m_header.m_height},
    {"m_font_scale", render::get()->m_header.m_font_scale},
    {"m_font", render::get()->m_header.m_font},
    {"m_color", {
        {"r", render::get()->m_header.m_color.r},
        {"g", render::get()->m_header.m_color.g},
        {"b", render::get()->m_header.m_color.b},
        {"a", render::get()->m_header.m_color.a}
    }},
    {"m_text_color", {
        {"r", render::get()->m_header.m_text_color.r},
        {"g", render::get()->m_header.m_text_color.g},
        {"b", render::get()->m_header.m_text_color.b},
        {"a", render::get()->m_header.m_text_color.a}
    }},
    {"m_texture", render::get()->m_header.m_texture},
    {"m_text", render::get()->m_header.m_text}
        };


        json title_json = {
            {"m_height", render::get()->m_title.m_height},
            {"m_font_scale", render::get()->m_title.m_font_scale},
            {"m_font", render::get()->m_title.m_font},
            {"m_padding", {
                {"x", render::get()->m_title.m_padding.x},
                {"y", render::get()->m_title.m_padding.y}
            }},
            {"m_color", {
                {"r", render::get()->m_title.m_color.r},
                {"g", render::get()->m_title.m_color.g},
                {"b", render::get()->m_title.m_color.b},
                {"a", render::get()->m_title.m_color.a}
            }},
            {"m_text_color", {
                {"r", render::get()->m_title.m_text_color.r},
                {"g", render::get()->m_title.m_text_color.g},
                {"b", render::get()->m_title.m_text_color.b},
                {"a", render::get()->m_title.m_text_color.a}
            }},
            {"m_texture", render::get()->m_title.m_texture}
        };

        json option_json = {
            {"m_height", render::get()->m_option.m_height},
            {"m_font_scale", render::get()->m_option.m_font_scale},
            {"m_font", render::get()->m_option.m_font},
            {"m_padding", {
                {"x", render::get()->m_option.m_padding.x},
                {"y", render::get()->m_option.m_padding.y}
            }},
            {"m_color", {
                {"r", render::get()->m_option.m_color.r},
                {"g", render::get()->m_option.m_color.g},
                {"b", render::get()->m_option.m_color.b},
                {"a", render::get()->m_option.m_color.a}
            }},
            {"m_text_color", {
                {"r", render::get()->m_option.m_text_color.r},
                {"g", render::get()->m_option.m_text_color.g},
                {"b", render::get()->m_option.m_text_color.b},
                {"a", render::get()->m_option.m_text_color.a}
            }},
            {"m_selected_text_color", {
                {"r", render::get()->m_option.m_selected_text_color.r},
                {"g", render::get()->m_option.m_selected_text_color.g},
                {"b", render::get()->m_option.m_selected_text_color.b},
                {"a", render::get()->m_option.m_selected_text_color.a}
            }},
            {"m_arrow_size", {
                {"x", render::get()->m_option.m_arrow_size.x},
                {"y", render::get()->m_option.m_arrow_size.y}
            }},
            {"m_icon_size", {
                {"x", render::get()->m_option.m_icon_size.x},
                {"y", render::get()->m_option.m_icon_size.y}
            }},
            {"m_toggle_size", {
                {"x", render::get()->m_option.m_toggle_size.x},
                {"y", render::get()->m_option.m_toggle_size.y}
            }},
            {"m_right_spacing", render::get()->m_option.m_right_spacing},
            {"m_spacing_extras", render::get()->m_option.m_spacing_extras},
            {"m_texture", render::get()->m_option.m_texture},
            {"custom_texture", render::get()->m_option.custom_texture}
        };

        json scrollbar_json = {
            {"m_color", {
                {"r", render::get()->m_scrollbar.m_color.r},
                {"g", render::get()->m_scrollbar.m_color.g},
                {"b", render::get()->m_scrollbar.m_color.b},
                {"a", render::get()->m_scrollbar.m_color.a}
            }},
            {"m_width", render::get()->m_scrollbar.m_width},
            {"m_in_width", render::get()->m_scrollbar.m_in_width},
            {"m_spacing", render::get()->m_scrollbar.m_spacing},
            {"m_ends", {
                {"x", render::get()->m_scrollbar.m_ends.x},
                {"y", render::get()->m_scrollbar.m_ends.y}
            }}
        };


        json footer_json = {
    {"m_height", render::get()->m_footer.m_height},
    {"m_font_scale", render::get()->m_footer.m_font_scale},
    {"m_font", render::get()->m_footer.m_font},
    {"m_padding", {
        {"x", render::get()->m_footer.m_padding.x},
        {"y", render::get()->m_footer.m_padding.y}
    }},
    {"m_color", {
        {"r", render::get()->m_footer.m_color.r},
        {"g", render::get()->m_footer.m_color.g},
        {"b", render::get()->m_footer.m_color.b},
        {"a", render::get()->m_footer.m_color.a}
    }},
    {"m_text_color", {
        {"r", render::get()->m_footer.m_text_color.r},
        {"g", render::get()->m_footer.m_text_color.g},
        {"b", render::get()->m_footer.m_text_color.b},
        {"a", render::get()->m_footer.m_text_color.a}
    }},
    {"m_icon_size", {
        {"x", render::get()->m_footer.m_icon_size.x},
        {"y", render::get()->m_footer.m_icon_size.y}
    }}
        };


        json description_json = {
    {"m_height", render::get()->m_description.m_height},
    {"m_font_scale", render::get()->m_description.m_font_scale},
    {"m_font", render::get()->m_description.m_font},
    {"m_padding", {
        {"x", render::get()->m_description.m_padding.x},
        {"y", render::get()->m_description.m_padding.y}
    }},
    {"m_color", {
        {"r", render::get()->m_description.m_color.r},
        {"g", render::get()->m_description.m_color.g},
        {"b", render::get()->m_description.m_color.b},
        {"a", render::get()->m_description.m_color.a}
    }},
    {"m_text_color", {
        {"r", render::get()->m_description.m_text_color.r},
        {"g", render::get()->m_description.m_text_color.g},
        {"b", render::get()->m_description.m_text_color.b},
        {"a", render::get()->m_description.m_text_color.a}
    }},
    {"m_text", render::get()->m_description.m_text},
    {"m_line_height", render::get()->m_description.m_line_height}
        };
        json config = {
            {"header", header_json},
            {"title", title_json},
            {"option", option_json},
            {"scrollbar", scrollbar_json},
            {"footer", footer_json},
            {"description", description_json}
        };
        auto path_str = std::filesystem::path(std::getenv(xorstr_("appdata"))).append(xorstr_("insight")).append(xorstr_("configs")).append(xorstr_("theme_config.json"));

        std::ofstream outfile(path_str.generic_string());
        outfile << std::setw(4) << config << std::endl;
        outfile.close();

        return;
	}
	void theme::load() {
        auto path_str = std::filesystem::path(std::getenv(xorstr_("appdata"))).append(xorstr_("insight")).append(xorstr_("configs")).append(xorstr_("theme_config.json"));

        std::ifstream infile(path_str.generic_string());
        if (!infile.is_open()) {
           LOG(INFO) << "theme_config.json does not exist. Creating a new one.";
           save();
           return;  
        }
        LOG(INFO) << "theme_config.json loaded.";


        json loaded_config;
        infile >> loaded_config;
        infile.close();
        try {
            header m_header;
            m_header.m_height = loaded_config["header"]["m_height"];
            m_header.m_font_scale = loaded_config["header"]["m_font_scale"];
            m_header.m_font = loaded_config["header"]["m_font"];
            m_header.m_texture = loaded_config["header"]["m_texture"];
            m_header.m_text = loaded_config["header"]["m_text"];
            m_header.m_color.r = loaded_config["header"]["m_color"]["r"];
            m_header.m_color.g = loaded_config["header"]["m_color"]["g"];
            m_header.m_color.b = loaded_config["header"]["m_color"]["b"];
            m_header.m_color.a = loaded_config["header"]["m_color"]["a"];
            m_header.m_text_color.r = loaded_config["header"]["m_text_color"]["r"];
            m_header.m_text_color.g = loaded_config["header"]["m_text_color"]["g"];
            m_header.m_text_color.b = loaded_config["header"]["m_text_color"]["b"];
            m_header.m_text_color.a = loaded_config["header"]["m_text_color"]["a"];
            render::get()->m_header = m_header;

            title m_title;
            m_title.m_height = loaded_config["title"]["m_height"];
            m_title.m_font_scale = loaded_config["title"]["m_font_scale"];
            m_title.m_font = loaded_config["title"]["m_font"];
            m_title.m_texture = loaded_config["title"]["m_texture"];
            m_title.m_padding.x = loaded_config["title"]["m_padding"]["x"];
            m_title.m_padding.y = loaded_config["title"]["m_padding"]["y"];
            m_title.m_color.r = loaded_config["title"]["m_color"]["r"];
            m_title.m_color.g = loaded_config["title"]["m_color"]["g"];
            m_title.m_color.b = loaded_config["title"]["m_color"]["b"];
            m_title.m_color.a = loaded_config["title"]["m_color"]["a"];
            m_title.m_text_color.r = loaded_config["title"]["m_text_color"]["r"];
            m_title.m_text_color.g = loaded_config["title"]["m_text_color"]["g"];
            m_title.m_text_color.b = loaded_config["title"]["m_text_color"]["b"];
            m_title.m_text_color.a = loaded_config["title"]["m_text_color"]["a"];
            render::get()->m_title = m_title;

            option m_option;
            m_option.m_height = loaded_config["option"]["m_height"];
            m_option.m_font_scale = loaded_config["option"]["m_font_scale"];
            m_option.m_font = loaded_config["option"]["m_font"];
            m_option.m_texture = loaded_config["option"]["m_texture"];
            m_option.custom_texture = loaded_config["option"]["custom_texture"];
            m_option.m_padding.x = loaded_config["option"]["m_padding"]["x"];
            m_option.m_padding.y = loaded_config["option"]["m_padding"]["y"];
            m_option.m_color.r = loaded_config["option"]["m_color"]["r"];
            m_option.m_color.g = loaded_config["option"]["m_color"]["g"];
            m_option.m_color.b = loaded_config["option"]["m_color"]["b"];
            m_option.m_color.a = loaded_config["option"]["m_color"]["a"];
            m_option.m_text_color.r = loaded_config["option"]["m_text_color"]["r"];
            m_option.m_text_color.g = loaded_config["option"]["m_text_color"]["g"];
            m_option.m_text_color.b = loaded_config["option"]["m_text_color"]["b"];
            m_option.m_text_color.a = loaded_config["option"]["m_text_color"]["a"];
            m_option.m_selected_text_color.r = loaded_config["option"]["m_selected_text_color"]["r"];
            m_option.m_selected_text_color.g = loaded_config["option"]["m_selected_text_color"]["g"];
            m_option.m_selected_text_color.b = loaded_config["option"]["m_selected_text_color"]["b"];
            m_option.m_selected_text_color.a = loaded_config["option"]["m_selected_text_color"]["a"];
            m_option.m_arrow_size.x = loaded_config["option"]["m_arrow_size"]["x"];
            m_option.m_arrow_size.y = loaded_config["option"]["m_arrow_size"]["y"];
            m_option.m_icon_size.x = loaded_config["option"]["m_icon_size"]["x"];
            m_option.m_icon_size.y = loaded_config["option"]["m_icon_size"]["y"];
            m_option.m_toggle_size.x = loaded_config["option"]["m_toggle_size"]["x"];
            m_option.m_toggle_size.y = loaded_config["option"]["m_toggle_size"]["y"];
            m_option.m_right_spacing = loaded_config["option"]["m_right_spacing"];
            m_option.m_spacing_extras = loaded_config["option"]["m_spacing_extras"];
            render::get()->m_option = m_option;

            scrollbar m_scrollbar;
            m_scrollbar.m_color.r = loaded_config["scrollbar"]["m_color"]["r"];
            m_scrollbar.m_color.g = loaded_config["scrollbar"]["m_color"]["g"];
            m_scrollbar.m_color.b = loaded_config["scrollbar"]["m_color"]["b"];
            m_scrollbar.m_color.a = loaded_config["scrollbar"]["m_color"]["a"];
            m_scrollbar.m_width = loaded_config["scrollbar"]["m_width"];
            m_scrollbar.m_in_width = loaded_config["scrollbar"]["m_in_width"];
            m_scrollbar.m_spacing = loaded_config["scrollbar"]["m_spacing"];
            m_scrollbar.m_ends.x = loaded_config["scrollbar"]["m_ends"]["x"];
            m_scrollbar.m_ends.y = loaded_config["scrollbar"]["m_ends"]["y"];
            render::get()->m_scrollbar = m_scrollbar;

            footer m_footer;
            m_footer.m_height = loaded_config["footer"]["m_height"];
            m_footer.m_font_scale = loaded_config["footer"]["m_font_scale"];
            m_footer.m_font = loaded_config["footer"]["m_font"];
            m_footer.m_padding.x = loaded_config["footer"]["m_padding"]["x"];
            m_footer.m_padding.y = loaded_config["footer"]["m_padding"]["y"];
            m_footer.m_color.r = loaded_config["footer"]["m_color"]["r"];
            m_footer.m_color.g = loaded_config["footer"]["m_color"]["g"];
            m_footer.m_color.b = loaded_config["footer"]["m_color"]["b"];
            m_footer.m_color.a = loaded_config["footer"]["m_color"]["a"];
            m_footer.m_text_color.r = loaded_config["footer"]["m_text_color"]["r"];
            m_footer.m_text_color.g = loaded_config["footer"]["m_text_color"]["g"];
            m_footer.m_text_color.b = loaded_config["footer"]["m_text_color"]["b"];
            m_footer.m_text_color.a = loaded_config["footer"]["m_text_color"]["a"];
            m_footer.m_icon_size.x = loaded_config["footer"]["m_icon_size"]["x"];
            m_footer.m_icon_size.y = loaded_config["footer"]["m_icon_size"]["y"];
            render::get()->m_footer = m_footer;

            description m_description;
            m_description.m_height = loaded_config["description"]["m_height"];
            m_description.m_font_scale = loaded_config["description"]["m_font_scale"];
            m_description.m_font = loaded_config["description"]["m_font"];
            m_description.m_text = loaded_config["description"]["m_text"];
            m_description.m_line_height = loaded_config["description"]["m_line_height"];
            m_description.m_padding.x = loaded_config["description"]["m_padding"]["x"];
            m_description.m_padding.y = loaded_config["description"]["m_padding"]["y"];
            m_description.m_color.r = loaded_config["description"]["m_color"]["r"];
            m_description.m_color.g = loaded_config["description"]["m_color"]["g"];
            m_description.m_color.b = loaded_config["description"]["m_color"]["b"];
            m_description.m_color.a = loaded_config["description"]["m_color"]["a"];
            m_description.m_text_color.r = loaded_config["description"]["m_text_color"]["r"];
            m_description.m_text_color.g = loaded_config["description"]["m_text_color"]["g"];
            m_description.m_text_color.b = loaded_config["description"]["m_text_color"]["b"];
            m_description.m_text_color.a = loaded_config["description"]["m_text_color"]["a"];
            render::get()->m_description = m_description;
            }
            catch(std::exception info) {
                LOG(INFO) << "Issue Loading Theme(Update It / Remake It)" << info.what();
            }
        return;
	}

}