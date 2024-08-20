#pragma once
#include "cheat/render/render.hpp"
namespace insight::notify {
	struct notify_context {
		std::vector<std::string> m_text = {};
		std::string m_rendering_text = "";
		std::string m_title = "";
		int m_lines = 1;
		color m_color = {};
		float m_max_width = 0.20f;
		float x = 0.009f;
		float m_y = 0.0f;
		uint32_t m_start_time = 0;
		uint32_t m_time_limit = 5000;
		bool m_has_calculated = false;
		bool m_has_init = false;
		uint32_t m_alpha_start = 0;
		int m_alpha = 255;
		float m_title_width = 0.f;
	};

	class notify {
	public:
		void update();
		void stacked(std::string title, std::string text, color color = { 0, 0, 0, 255 }, uint32_t timeout = 6000);
		void stacked_lines(std::string title, std::vector<std::string> text, color color = { 0, 0, 0, 255 });
		void protection(std::string sender, std::string event, bool redirected, bool blocked);
		void subtitle(const char* msg,int timer);
		int tool_tip_value;
		std::string tooltipy;
		std::vector<notify_context>& get_contexts() { return m_context; }
	public:
		void tick_anti_spam_msg();
		void spamsend(std::string Title, std::string Content, int duration = 6000, color color = { 0, 0, 0, 255 });
	private:
		std::vector<notify_context> m_context;

		std::unordered_map<uint32_t, uint32_t> m_protection_spam;
	};
	inline void notify::subtitle(const char* msg, int timer) {
		HUD::BEGIN_TEXT_COMMAND_PRINT("STRING");
		HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(msg);
		HUD::END_TEXT_COMMAND_PRINT(timer, true);
	}
	inline notify* get_notify() {
		static notify instance;
		return &instance;
	}
	inline void update() {
		get_notify()->update();
	}

	inline void subtitle(const char* msg, int timer = 3000) {
		get_notify()->subtitle(msg, timer);
	}

	inline void send(std::string title, std::string text, color color = { 0, 0, 0, 255 }, uint32_t timeout = 6000) {
		get_notify()->stacked(title, text, color, timeout);
	}
	inline void send_anti_spam(std::string title, std::string text, color color = { 0, 0, 0, 255 }, uint32_t timeout = 6000) {
		get_notify()->spamsend(title, text, timeout, color);
		
	}
	inline void send_lined(std::string title, std::vector<std::string> text, color color = { 0, 0, 0, 255 }) {
		get_notify()->stacked_lines(title, text, color);
	}
}