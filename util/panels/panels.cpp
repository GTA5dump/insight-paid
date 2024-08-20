#include "panels.hpp"

namespace insight {

    void panel::start_panel(std::string title) {
        auto menu = render::get();

        panels::get()->m_panel_base_2 = panels::get()->m_panel_pos.y;

        if (!m_next_to) {
            if (menu->m_position.x > 0.5f) {
                panels::get()->m_panel_pos.x = menu->m_position.x - (menu->m_width / 2.f) - (m_width / 2.f) - panels::get()->m_panel_spacing;
            }
            else {
                panels::get()->m_panel_pos.x = menu->m_position.x + (menu->m_width / 2.f) + (m_width / 2.f) + panels::get()->m_panel_spacing;
            }
        }
        else {
            if (menu->m_position.x > 0.5f) {
                panels::get()->m_panel_pos.x = menu->m_position.x - (menu->m_width / 2.f) - (m_width / 2.f) - panels::get()->m_panel_spacing;
            }
            else {
                panels::get()->m_panel_pos.x = menu->m_position.x + (menu->m_width / 2.f) + (m_width / 2.f) + panels::get()->m_panel_spacing;
            }

            panels::get()->m_panel_base = panels::get()->m_panel_pos.y;
        }

        panels::get()->m_panel_pos.y = menu->m_position.y;

        panels::get()->m_panel_base = panels::get()->m_panel_pos.y;

        insight::g_renderer->draw_rect({ panels::get()->m_panel_pos.x, insight::g_renderer->get_rect_base(0.004f, panels::get()->m_panel_base) }, { m_width, 0.004f }, menu->m_header.m_color);
        panels::get()->m_panel_base += 0.004f;

        if (m_title_height != 0.f) {
            insight::g_renderer->draw_rect({ panels::get()->m_panel_pos.x, insight::g_renderer->get_rect_base(m_title_height, panels::get()->m_panel_base) }, { m_width, m_title_height }, m_back_ground);
            insight::g_renderer->draw_text(title, font_justify::center, { panels::get()->m_panel_pos.x, insight::g_renderer->get_rect_base(m_title_height, panels::get()->m_panel_base) }, m_title_font_scale, (int)m_title_font, m_padding);
        }

        panels::get()->m_panel_base += m_title_height;
    }

    eFontType panel::m_item_font = eFontType::custom1;

    void panel::start_panel_under(std::string title) {
        auto menu = render::get();

        panels::get()->m_panel_base_2 = panels::get()->m_panel_pos.y;

        if (!m_next_to) {
            if (menu->m_position.x > 0.5f) {
                panels::get()->m_panel_pos.x = menu->m_position.x - (menu->m_width / 2.f) - (m_width / 2.f) - panels::get()->m_panel_spacing;
            }
            else {
                panels::get()->m_panel_pos.x = menu->m_position.x + (menu->m_width / 2.f) + (m_width / 2.f) + panels::get()->m_panel_spacing;
            }
        }
        else {
            if (menu->m_position.x > 0.5f) {
                panels::get()->m_panel_pos.x = menu->m_position.x - (menu->m_width / 2.f) - (m_width / 2.f) - panels::get()->m_panel_spacing;
            }
            else {
                panels::get()->m_panel_pos.x = menu->m_position.x + (menu->m_width / 2.f) + (m_width / 2.f) + panels::get()->m_panel_spacing;
            }

            panels::get()->m_panel_base = panels::get()->m_panel_pos.y;
        }

        insight::g_renderer->draw_rect({ panels::get()->m_panel_pos.x, insight::g_renderer->get_rect_base(0.004f, panels::get()->m_panel_base) }, { m_width, 0.004f }, menu->m_header.m_color);
        panels::get()->m_panel_base += 0.004f;

        insight::g_renderer->draw_rect({ panels::get()->m_panel_pos.x, insight::g_renderer->get_rect_base(m_title_height, panels::get()->m_panel_base) }, { m_width, m_title_height }, m_back_ground);
        insight::g_renderer->draw_text(title.c_str(), font_justify::center, { panels::get()->m_panel_pos.x, insight::g_renderer->get_rect_base(m_title_height, panels::get()->m_panel_base) }, m_title_font_scale, (int)m_title_font, m_padding, m_text_color, m_width);

        panels::get()->m_panel_base += m_title_height;
    }

    void panel::push(std::string left, std::string right) {
        insight::g_renderer->draw_rect({ panels::get()->m_panel_pos.x, insight::g_renderer->get_rect_base(m_item_height, panels::get()->m_panel_base) }, { m_width, m_item_height }, m_back_ground);
        insight::g_renderer->draw_text(left, font_justify::left, { panels::get()->m_panel_pos.x, insight::g_renderer->get_rect_base(m_item_height, panels::get()->m_panel_base) }, m_font_scale, (int)m_item_font, m_padding, m_text_color, m_width);
        insight::g_renderer->draw_text(right, font_justify::right, { panels::get()->m_panel_pos.x, insight::g_renderer->get_rect_base(m_item_height, panels::get()->m_panel_base) }, m_font_scale, (int)m_item_font, m_padding, m_text_color, m_width);

        panels::get()->m_panel_base += m_item_height;
    }

    void panel::push_break(std::string text) {
        insight::g_renderer->draw_rect({ panels::get()->m_panel_pos.x, insight::g_renderer->get_rect_base(m_item_height, panels::get()->m_panel_base) }, { m_width, m_item_height }, m_back_ground);
        insight::g_renderer->draw_text(text, font_justify::center, { panels::get()->m_panel_pos.x, insight::g_renderer->get_rect_base(m_item_height, panels::get()->m_panel_base) }, m_font_scale, (int)m_item_font, m_padding, m_text_color, m_width);
 
        panels::get()->m_panel_base += m_item_height;
    }
    
    void panel::push_rect(color color, float height) {
        insight::g_renderer->draw_rect({ panels::get()->m_panel_pos.x, insight::g_renderer->get_rect_base(height, panels::get()->m_panel_base) }, { m_width, height }, color);

        panels::get()->m_panel_base += height;
    }

    void panel::push_sprite(std::pair<std::string, std::string> texture, Vector2 size) {
        insight::g_renderer->draw_sprite(texture, { panels::get()->m_panel_pos.x, insight::g_renderer->get_rect_base(size.y, panels::get()->m_panel_base) }, size, { 255, 255, 255, 255 });

        panels::get()->m_panel_base += size.y;
    }

    void panel::push_double(std::string left_left, std::string left_right, std::string right_left, std::string right_right) {
        insight::g_renderer->draw_rect({ panels::get()->m_panel_pos.x, insight::g_renderer->get_rect_base(m_item_height, panels::get()->m_panel_base) }, { m_width, m_item_height}, m_back_ground);
        insight::g_renderer->draw_text(left_left, font_justify::left, { (panels::get()->m_panel_pos.x), insight::g_renderer->get_rect_base(m_item_height, panels::get()->m_panel_base ) }, m_font_scale, (int)m_item_font, m_padding, m_text_color, m_width);
        insight::g_renderer->draw_text(left_right, font_justify::right, { (panels::get()->m_panel_pos.x - (m_width / 2.f)), insight::g_renderer->get_rect_base(m_item_height, panels::get()->m_panel_base) }, m_font_scale, (int)m_item_font, m_padding, m_text_color, m_width);
        insight::g_renderer->draw_text(right_left, font_justify::left, { (panels::get()->m_panel_pos.x + (m_width / 2.f)), insight::g_renderer->get_rect_base(m_item_height, panels::get()->m_panel_base) }, m_font_scale, (int)m_item_font, m_padding, m_text_color, m_width);
        insight::g_renderer->draw_text(right_right, font_justify::right, { (panels::get()->m_panel_pos.x), insight::g_renderer->get_rect_base(m_item_height, panels::get()->m_panel_base) }, m_font_scale, (int)m_item_font, m_padding, m_text_color, m_width);
        insight::g_renderer->draw_text("~c~|", font_justify::center, {(panels::get()->m_panel_pos.x), insight::g_renderer->get_rect_base(m_item_height, panels::get()->m_panel_base)}, m_font_scale * 1.7f, (int)m_item_font, m_padding, m_text_color, m_width);
        panels::get()->m_panel_base += m_item_height;
    }

    void panel::end_panel() {
        insight::g_renderer->draw_rect({ panels::get()->m_panel_pos.x, insight::g_renderer->get_rect_base((m_item_height / 4.f), panels::get()->m_panel_base) }, { m_width, (m_item_height / 4.f)}, m_back_ground);
        panels::get()->m_panel_base += panels::get()->m_panel_spacing_under;
    }

    void panel::set_next() {
        m_next_to = true;
    }

}