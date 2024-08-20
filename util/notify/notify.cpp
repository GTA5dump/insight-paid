#include "notify.hpp"
#include "natives.hpp"
#include "cheat/render/renderer.hpp"
#include "util/translation/translation.hpp"
#include "util/timer.hpp"
namespace insight::notify {
	enum eJustify {
		JUSTIFY_LEFT,
		JUSTIFY_RIGHT,
		JUSTIFY_CENTER,
	};
	int m_notify_font = 0;
	float calculate_string_width(std::string string, int font, float scale) {
		HUD::BEGIN_TEXT_COMMAND_GET_SCREEN_WIDTH_OF_DISPLAY_TEXT("STRING");
		HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(string.c_str());
		HUD::SET_TEXT_SCALE(0.f, scale);
		return HUD::END_TEXT_COMMAND_GET_SCREEN_WIDTH_OF_DISPLAY_TEXT(font);
	}
	float get_normalized_font_scale(int font, float scale) {
		switch (font) {
		case 0: return (scale * 1.0f);
		case 1: return (scale * 1.3f);
		case 2: return (scale * 1.11f);
		case 4: return (scale * 1.11f);
		case 7: return (scale * 1.29f);
		}
		return scale;
	}
	float lerp(float toEase, float easeFrom, float percent) {
		return (toEase + percent * (easeFrom - toEase));
	}
	void draw_rect(Vector2 position, Vector2 scale, color color) {
		GRAPHICS::DRAW_RECT({ position.x + (scale.x * 0.5f), position.y + (scale.y * 0.5f) }, scale.x, scale.y, color.r, color.g, color.b, color.a, 0);
	}
	void draw_text(std::string text, Vector2 position, float scale, int font, color color, eJustify justification, Vector2 wrap = { 0.f, 5.f }) {
		if (font >= 8) {
			font = custom_fonts[font];
		}

		HUD::SET_TEXT_WRAP(wrap.x, wrap.y);

		if (justification != JUSTIFY_LEFT) {
			HUD::SET_TEXT_JUSTIFICATION(justification == JUSTIFY_CENTER ? 0 : 2);
		}

		HUD::SET_TEXT_CENTRE(justification == JUSTIFY_CENTER);
		HUD::SET_TEXT_SCALE(0.f, scale);
		HUD::SET_TEXT_COLOUR(color.r, color.g, color.b, color.a);
		HUD::SET_TEXT_FONT(font);


		HUD::BEGIN_TEXT_COMMAND_DISPLAY_TEXT("STRING");
		HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(text.c_str());
		HUD::END_TEXT_COMMAND_DISPLAY_TEXT({ position.x, position.y }, 0);
	}

	inline void draw_text2(std::string text, Vector2 position, float scale, int font, color color, eJustify justification = JUSTIFY_LEFT, Vector2 wrap = { 0.f, 5.f }) {
		draw_text(text, position, scale, font, color, justification, wrap);
	}
	void notify::update() {
		static u32 frame_cache;
		static u32 this_frame;
		static u32 last_frame;
		if (frame_cache < *pointers::get()->g_frame_count) {
			frame_cache = *pointers::get()->g_frame_count;
			this_frame = GetTickCount64();
			g_delta = (float)(this_frame - last_frame) / 1000;
			last_frame = this_frame;
		}
		float current = 0.f;
		for (auto context = m_context.begin(); context != m_context.end(); context++) {
			float wrap = 0.1362f;
			float x_offset = 0.006f;
			float text_height = 0.2f;

			if (context->m_has_init) {
				continue;
			}

			context->m_has_init = true;

			if (context->m_text.size() == 1) {
				HUD::SET_TEXT_FONT(0);
				HUD::SET_TEXT_SCALE(0.f, text_height);
				HUD::SET_TEXT_WRAP(context->x + x_offset, wrap);
				HUD::BEGIN_TEXT_COMMAND_GET_NUMBER_OF_LINES_FOR_STRING("STRING");
				HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(context->m_text[0].c_str());
				context->m_lines = HUD::END_TEXT_COMMAND_GET_NUMBER_OF_LINES_FOR_STRING({ context->x + x_offset, 0.015f });
				current += (context->m_lines * HUD::GET_RENDERED_CHARACTER_HEIGHT(text_height, 0)) + (context->m_lines * x_offset) + (x_offset * 3.f);
			}
			else {
				context->m_max_width = calculate_string_width(context->m_text[0], 0, text_height) + (x_offset * 2.f);

				for (std::size_t i = 0; i < context->m_text.size(); i++) {
					std::string str = context->m_text[i];

					float width = calculate_string_width(str, 0, text_height) + (x_offset * 2.f);
					if (context->m_max_width < width) {
						context->m_max_width = width;
					}
				}

				context->m_lines = (int)context->m_text.size();
				current += (context->m_lines * HUD::GET_RENDERED_CHARACTER_HEIGHT(text_height, 0)) + (context->m_lines * x_offset) + (x_offset * 3.f);
			}

			current += 0.004f;
			context->m_y = -current;
		}

		float y = 0.01f;
		for (auto context = m_context.rbegin(); context != m_context.rend(); context++) {
			float x_offset = 0.006f;
			float wrap = context->m_max_width + x_offset;
			float text_height = 0.2f;
			float height = (text_height / 10.f) + ((text_height * 1.1f) / 10.f);
			bool death = false;

			float scaled_body_height = get_normalized_font_scale(0, text_height);
			float scaled_title_height = get_normalized_font_scale(0, text_height * 1.1f);

			// nearing death, slide out
			uint32_t end_time = context->m_start_time + context->m_time_limit;
			if (end_time < GetTickCount() || end_time - GetTickCount() < 1000) {
				death = true;
				context->m_y = lerp(context->m_y, 1.2f, 5.f * g_delta);

				if (context->m_alpha_start == 0) context->m_alpha_start = GetTickCount();
				context->m_alpha = 255 - (((GetTickCount() - context->m_alpha_start) * 255) / 1000);
			}
			else {
				if (context->m_title_width > context->m_max_width) {
					wrap = context->m_title_width + x_offset;
				}
			}

			if (context->m_title_width == 0.f) {
				context->m_title_width = calculate_string_width("~bold~" + context->m_title, 0, scaled_title_height) + (0.004f * 2.f);
			}

			// if it has one bit of text, calculate the lines
			if (context->m_text.size() == 1) {
				HUD::SET_TEXT_FONT(0);
				HUD::SET_TEXT_SCALE(scaled_body_height, scaled_body_height);
				HUD::SET_TEXT_WRAP(context->x, wrap - x_offset);
				HUD::BEGIN_TEXT_COMMAND_GET_NUMBER_OF_LINES_FOR_STRING("STRING");
				HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(context->m_text[0].c_str());

				context->m_lines = HUD::END_TEXT_COMMAND_GET_NUMBER_OF_LINES_FOR_STRING({ context->x, y + 0.005f });
				context->m_rendering_text = context->m_text[0];

				if (context->m_lines > 1) {
					height = (context->m_lines * HUD::GET_RENDERED_CHARACTER_HEIGHT(scaled_body_height, 0)) + 0.034f;
				}
				else {
					context->m_max_width = calculate_string_width(context->m_text[0], 0, scaled_body_height) + (x_offset * 2.f);
				}
			}
			else {
				// its a list of lines, calculate the longest line and use that as the width
				std::string full_line = "";
				context->m_max_width = calculate_string_width(context->m_text[0], 0, scaled_body_height) + (x_offset * 2.f);

				for (std::size_t i = 0; i < context->m_text.size(); i++) {
					std::string str = context->m_text[i];

					float width = calculate_string_width(str, 0, scaled_body_height) + (x_offset * 2.f);
					if (context->m_max_width < width) {
						context->m_max_width = width;
					}

					full_line += str;

					if (i != (context->m_text.size() - 1)) {
						full_line += '\n';
					}
				}

				context->m_lines = (int)context->m_text.size();
				context->m_rendering_text = full_line;
				height = (context->m_lines * HUD::GET_RENDERED_CHARACTER_HEIGHT(scaled_body_height, 0)) + 0.034f;
			}

			if (context->m_text.size() == 4) {
				height += 0.002f;
			}

			// lerp the Y position to account for new notifies
			if (!death) {
				context->m_y = lerp(context->m_y, y, 5.f * g_delta);
			}

			if (context->m_y + height > 0.7f) {
				context->m_time_limit = 0;
			}

			if (context->m_y <= 1.f) {
				HUD::CLEAR_HELP(true);
				HUD::CLEAR_ALL_HELP_MESSAGES();

				int rect_alpha = context->m_alpha >= 35 ? context->m_alpha - 35 : 0;
				g_renderer->draw_rect({ context->x, context->m_y }, { context->m_max_width, height }, { 20, 20, 20, (uint8_t)rect_alpha }, true);
				draw_rect({ context->x, context->m_y }, { 0.0009f, height }, { 255, 255, 255, (uint8_t)rect_alpha });
				Vector2 text_wrap;
				if (context->m_text.size() > 1) {
					text_wrap = Vector2{ 0.f, 1.f };
				}
				else {
					text_wrap = Vector2{ context->x, wrap };
				}
				draw_text(context->m_rendering_text, {context->x + (x_offset / 2.f), context->m_y + 0.02f + 0.001f}, scaled_body_height, (int)eFontType::custom1, {255, 255, 255, (uint8_t)context->m_alpha}, JUSTIFY_LEFT, text_wrap);
				draw_text2(context->m_title, {context->x + (x_offset / 2.f), context->m_y + 0.003f + 0.001f}, scaled_title_height, (int)eFontType::custom1, {255, 255, 255, (uint8_t)context->m_alpha}, JUSTIFY_LEFT);
				y += height + 0.004f;
			}
		}

		for (auto context = m_context.begin(); context != m_context.end();) {
			if (context->m_start_time + context->m_time_limit < GetTickCount()) {
				context = m_context.erase(context);
				continue;
			}

			context++;
		}
	}
	void notify::stacked(std::string title, std::string text, color color, uint32_t timeout) {
		notify_context context;
		context.m_text.push_back(get_case_state(text));
		context.m_title = get_case_state(title);
		context.m_color = color;
		context.m_start_time = GetTickCount();
		context.m_time_limit = timeout;

		m_context.push_back(context);
	}

	void notify::stacked_lines(std::string title, std::vector<std::string> text, color color) {
		notify_context context;
		for (std::string str : text) context.m_text.push_back(get_case_state(str));

		context.m_title = get_case_state(title);
		context.m_color = color;
		context.m_start_time = GetTickCount();
		context.m_time_limit = 6000;

		m_context.push_back(context);
	}
	// i mean it works;
	std::vector<timer> create_notification_protex_result(50, timer(std::chrono::milliseconds(0)));
	std::vector<timer> create_notification_protex_timer(50, timer(std::chrono::milliseconds(0)));
	std::vector<std::string> create_notification_protex_last(50, "");
	bool create_notification_protex_exist = false;
	int create_notification_protex_index = 0;

	void create_notification_protex_reset(int index, int i)
	{
		create_notification_protex_result[index].setdelay(std::chrono::milliseconds(i));
		create_notification_protex_timer[index].restart();
	}

	void notify::tick_anti_spam_msg()
	{
		for (int i = 0; i < 50; i++)
		{
			if (create_notification_protex_result[i].update())
			{
				create_notification_protex_last[i] = "";
			}
			else if (create_notification_protex_timer[i].update())
			{
				create_notification_protex_timer[i].restart();
			}
			else {
				create_notification_protex_timer[i].setdelay(std::chrono::milliseconds(5)); //doesnt really matter 
			}
		}
	}
	void notify::spamsend(std::string Title, std::string Content, int duration, color color)
	{
		for (int i = 0; i < 50; i++)
		{
			if (create_notification_protex_last[i] == Content)
			{
				create_notification_protex_exist = true;
				create_notification_protex_index = i;
			}
			if (i == 49)
			{
				if (!create_notification_protex_exist)
				{
					int rand_num = rand() % 48 + 1;

					send(Title, Content, color, duration);
					LOG(INFO)  << Content;
					create_notification_protex_last[rand_num] = Content;
					create_notification_protex_reset(rand_num, duration);
				}
				create_notification_protex_exist = false;
			}
		}
	}
	
}