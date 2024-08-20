#pragma once
#include "instructionals buttons.hpp"
#include "natives.hpp"
#include "game/gta/enums.hpp"

namespace insight {
	static const char* instructional_keys[254] = {
xorstr_("F10"),
xorstr_("F10"),
xorstr_("F10"),
xorstr_("SCROLL LOCK"),
xorstr_("SCROLL LOCK"),
xorstr_("SCROLL LOCK"),
xorstr_("SCROLL LOCK"),
xorstr_("SCROLL LOCK"),
xorstr_("BACKSPACE"),
xorstr_("TAB"),
xorstr_("TAB"),
xorstr_("TAB"),
xorstr_("NUM 5"),
xorstr_("ENTER"),
xorstr_("ENTER"),
xorstr_("ENTER"),
xorstr_("SHIFT"),
xorstr_("CTRL"),
xorstr_("ALT"),
xorstr_("ALT"),
xorstr_("CAPSLOCK"),
xorstr_("CAPSLOCK"),
xorstr_("CAPSLOCK"),
xorstr_("CAPSLOCK"),
xorstr_("CAPSLOCK"),
xorstr_("CAPSLOCK"),
xorstr_("CAPSLOCK"),
xorstr_("ESC"),
xorstr_("ESC"),
xorstr_("ESC"),
xorstr_("ESC"),
xorstr_("ESC"),
xorstr_("SPACE"),
xorstr_("NUM 9"),
xorstr_("NUM 3"),
xorstr_("NUM 1"),
xorstr_("NUM 7"),
xorstr_("LEFT"),
xorstr_("UP"),
xorstr_("RIGHT"),
xorstr_("DOWN"),
xorstr_("NUM 2"),
xorstr_("NUM 2"),
xorstr_("NUM 2"),
xorstr_("NUM 2"),
xorstr_("NUM 0"),
xorstr_("DELETE"),
xorstr_("NUM DECIMAL"),
xorstr_("0"),
xorstr_("1"),
xorstr_("2"),
xorstr_("3"),
xorstr_("4"),
xorstr_("5"),
xorstr_("6"),
xorstr_("7"),
xorstr_("8"),
xorstr_("9"),
xorstr_("9"),
xorstr_("9"),
xorstr_("9"),
xorstr_("9"),
xorstr_("9"),
xorstr_("9"),
xorstr_("9"),
xorstr_("A"),
xorstr_("B"),
xorstr_("C"),
xorstr_("D"),
xorstr_("E"),
xorstr_("F"),
xorstr_("G"),
xorstr_("H"),
xorstr_("I"),
xorstr_("J"),
xorstr_("K"),
xorstr_("L"),
xorstr_("M"),
xorstr_("N"),
xorstr_("O"),
xorstr_("P"),
xorstr_("Q"),
xorstr_("R"),
xorstr_("S"),
xorstr_("T"),
xorstr_("U"),
xorstr_("V"),
xorstr_("W"),
xorstr_("X"),
xorstr_("Y"),
xorstr_("Z"),
xorstr_("Z"),
xorstr_("Z"),
xorstr_("Z"),
xorstr_("Z"),
xorstr_("Z"),
xorstr_("N0"),
xorstr_("N1"),
xorstr_("N2"),
xorstr_("N3"),
xorstr_("N4"),
xorstr_("N5"),
xorstr_("N6"),
xorstr_("N7"),
xorstr_("N8"),
xorstr_("N9"),
xorstr_("*"),
xorstr_("NUM PLUS"),
xorstr_("NUM PLUS"),
xorstr_("NUM SUB"),
xorstr_("NUM DECIMAL"),
xorstr_("/"),
xorstr_("F1"),
xorstr_("F2"),
xorstr_("F3"),
xorstr_("F4"),
xorstr_("F5"),
xorstr_("F6"),
xorstr_("F7"),
xorstr_("F8"),
xorstr_("F9"),
xorstr_("F10"),
xorstr_("F11"),
xorstr_("F12"),
xorstr_("F12"),
xorstr_("F12"),
xorstr_("F12"),
xorstr_("F12"),
xorstr_("F12"),
xorstr_("F12"),
xorstr_("F12"),
xorstr_("F12"),
xorstr_("F12"),
xorstr_("F12"),
xorstr_("F12"),
xorstr_("F12"),
xorstr_("F12"),
xorstr_("F12"),
xorstr_("F12"),
xorstr_("F12"),
xorstr_("F12"),
xorstr_("F12"),
xorstr_("F12"),
xorstr_("F12"),
xorstr_("Pause"),
xorstr_("SCROLL LOCK"),
xorstr_("SCROLL LOCK"),
xorstr_("SCROLL LOCK"),
xorstr_("SCROLL LOCK"),
xorstr_("SCROLL LOCK"),
xorstr_("SCROLL LOCK"),
xorstr_("SCROLL LOCK"),
xorstr_("SCROLL LOCK"),
xorstr_("SCROLL LOCK"),
xorstr_("SCROLL LOCK"),
xorstr_("SCROLL LOCK"),
xorstr_("SCROLL LOCK"),
xorstr_("SCROLL LOCK"),
xorstr_("SCROLL LOCK"),
xorstr_("SCROLL LOCK"),
xorstr_("SHIFT"),
xorstr_("RIGHT SHIFT"),
xorstr_("CTRL"),
xorstr_("CTRL"),
xorstr_("ALT"),
xorstr_("ALT"),
xorstr_("ALT"),
xorstr_("ALT"),
xorstr_("ALT"),
xorstr_("ALT"),
xorstr_("ALT"),
xorstr_("ALT"),
xorstr_("M"),
xorstr_("D"),
xorstr_("C"),
xorstr_("B"),
xorstr_("P"),
xorstr_("Q"),
xorstr_("J"),
xorstr_("G"),
xorstr_("G"),
xorstr_("G"),
xorstr_("G"),
xorstr_("F"),
xorstr_("F"),
xorstr_("F"),
xorstr_(";"),
xorstr_("="),
xorstr_(","),
xorstr_("-"),
xorstr_("."),
xorstr_("/"),
xorstr_("GRAVE"),
xorstr_("GRAVE"),
xorstr_("GRAVE"),
xorstr_("GRAVE"),
xorstr_("GRAVE"),
xorstr_("GRAVE"),
xorstr_("GRAVE"),
xorstr_("GRAVE"),
xorstr_("GRAVE"),
xorstr_("GRAVE"),
xorstr_("GRAVE"),
xorstr_("GRAVE"),
xorstr_("GRAVE"),
xorstr_("GRAVE"),
xorstr_("GRAVE"),
xorstr_("GRAVE"),
xorstr_("GRAVE"),
xorstr_("GRAVE"),
xorstr_("GRAVE"),
xorstr_("GRAVE"),
xorstr_("GRAVE"),
xorstr_("GRAVE"),
xorstr_("GRAVE"),
xorstr_("GRAVE"),
xorstr_("GRAVE"),
xorstr_("GRAVE"),
xorstr_("GRAVE"),
xorstr_("["),
xorstr_("null"),
xorstr_("]"),
xorstr_("ACUTE/CEDILLA"),
xorstr_("ACUTE/CEDILLA"),
xorstr_("ACUTE/CEDILLA"),
xorstr_("ACUTE/CEDILLA"),
xorstr_("null"),
xorstr_("null"),
xorstr_("null"),
xorstr_("null"),
xorstr_("null"),
xorstr_("null"),
xorstr_("null"),
xorstr_("null"),
xorstr_("null"),
xorstr_("null"),
xorstr_("null"),
xorstr_("null"),
xorstr_("null"),
xorstr_("null"),
xorstr_("null"),
xorstr_("null"),
xorstr_("null"),
xorstr_("null"),
xorstr_("null"),
xorstr_("null"),
xorstr_("null"),
xorstr_("null"),
xorstr_("null"),
xorstr_("null"),
xorstr_("null"),
xorstr_("null"),
xorstr_("null"),
xorstr_("null"),
	};           
	int m_count = 0;
	int m_handle = 0;
	void instructionals::setup() {

		if (!GRAPHICS::HAS_SCALEFORM_MOVIE_LOADED(m_handle)) {
			m_handle = GRAPHICS::REQUEST_SCALEFORM_MOVIE(xorstr_("instructional_buttons"));
			return;
		}

		GRAPHICS::BEGIN_SCALEFORM_MOVIE_METHOD(m_handle, xorstr_("CLEAR_ALL"));
		GRAPHICS::END_SCALEFORM_MOVIE_METHOD();

		GRAPHICS::BEGIN_SCALEFORM_MOVIE_METHOD(m_handle, xorstr_("TOGGLE_MOUSE_BUTTONS"));
		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_BOOL(1);
		GRAPHICS::END_SCALEFORM_MOVIE_METHOD();

		GRAPHICS::BEGIN_SCALEFORM_MOVIE_METHOD(m_handle, xorstr_("SET_MAX_WIDTH"));
		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_FLOAT(1.f);
		GRAPHICS::END_SCALEFORM_MOVIE_METHOD();
	}

	void instructionals::add_instructional(std::string text, ControllerInputs control) {
		GRAPHICS::BEGIN_SCALEFORM_MOVIE_METHOD(m_handle, xorstr_("SET_DATA_SLOT"));
		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT(m_count++);

		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_PLAYER_NAME_STRING(PAD::GET_CONTROL_INSTRUCTIONAL_BUTTONS_STRING(0, (int)control, true)); // problem!

		GRAPHICS::BEGIN_TEXT_COMMAND_SCALEFORM_STRING(xorstr_("STRING"));
			HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(text.c_str());
		GRAPHICS::END_TEXT_COMMAND_SCALEFORM_STRING();

		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_BOOL(true);
		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT((int)control);

		GRAPHICS::END_SCALEFORM_MOVIE_METHOD();
	}

	void instructionals::add_instructional(std::string text, ScaleformButtons button_option) {
		GRAPHICS::BEGIN_SCALEFORM_MOVIE_METHOD(m_handle, xorstr_("SET_DATA_SLOT"));
		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT(m_count++);

		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT(button_option);

		GRAPHICS::BEGIN_TEXT_COMMAND_SCALEFORM_STRING(xorstr_("STRING"));
		HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(text.c_str());
		GRAPHICS::END_TEXT_COMMAND_SCALEFORM_STRING();

		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_BOOL(true);
		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT(button_option);

		GRAPHICS::END_SCALEFORM_MOVIE_METHOD();
	}

	void instructionals::add_instructional(std::string text, int vk) {
		GRAPHICS::BEGIN_SCALEFORM_MOVIE_METHOD(m_handle, xorstr_("SET_DATA_SLOT"));
		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT(m_count++);

		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_PLAYER_NAME_STRING(("t_" + (std::string)instructional_keys[vk]).c_str());
		GRAPHICS::BEGIN_SCALEFORM_MOVIE_METHOD_ON_FRONTEND(text.c_str());
		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_BOOL(true);
		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT(vk);

		GRAPHICS::END_SCALEFORM_MOVIE_METHOD();
	}

	void instructionals::close() {
		GRAPHICS::BEGIN_SCALEFORM_MOVIE_METHOD(m_handle, xorstr_("SET_BACKGROUND_COLOUR"));
		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT(0);
		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT(0);
		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT(0);
		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT(80);
		GRAPHICS::END_SCALEFORM_MOVIE_METHOD();

		GRAPHICS::BEGIN_SCALEFORM_MOVIE_METHOD(m_handle, xorstr_("DRAW_INSTRUCTIONAL_BUTTONS"));
		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT(0);
		GRAPHICS::END_SCALEFORM_MOVIE_METHOD();

		GRAPHICS::DRAW_SCALEFORM_MOVIE_FULLSCREEN(m_handle, 255, 255, 255, 255, 0);
		m_count = 0;
	}	
}