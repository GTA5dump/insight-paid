#pragma once
#include <string>
#include "game/gta/enums.hpp"
#include "cheat/render/render.hpp"
namespace insight {
	enum ScaleformButtons { ARROW_UP, ARROW_DOWN, ARROW_LEFT, ARROW_RIGHT, BUTTON_DPAD_UP, BUTTON_DPAD_DOWN, BUTTON_DPAD_RIGHT, BUTTON_DPAD_LEFT, BUTTON_DPAD_BLANK, BUTTON_DPAD_ALL, BUTTON_DPAD_UP_DOWN, BUTTON_DPAD_LEFT_RIGHT, BUTTON_LSTICK_UP, BUTTON_LSTICK_DOWN, BUTTON_LSTICK_LEFT, BUTTON_LSTICK_RIGHT, BUTTON_LSTICK, BUTTON_LSTICK_ALL, BUTTON_LSTICK_UP_DOWN, BUTTON_LSTICK_LEFT_RIGHT, BUTTON_LSTICK_ROTATE, BUTTON_RSTICK_UP, BUTTON_RSTICK_DOWN, BUTTON_RSTICK_LEFT, BUTTON_RSTICK_RIGHT, BUTTON_RSTICK, BUTTON_RSTICK_ALL, BUTTON_RSTICK_UP_DOWN, BUTTON_RSTICK_LEFT_RIGHT, BUTTON_RSTICK_ROTATE, BUTTON_A, BUTTON_B, BUTTON_X, BUTTON_Y, BUTTON_LB, BUTTON_LT, BUTTON_RB, BUTTON_RT, BUTTON_START, BUTTON_BACK, RED_BOX, RED_BOX_1, RED_BOX_2, RED_BOX_3, LOADING_HALF_CIRCLE_LEFT, ARROW_UP_DOWN, ARROW_LEFT_RIGHT, ARROW_ALL, LOADING_HALF_CIRCLE_LEFT_2, SAVE_HALF_CIRCLE_LEFT, LOADING_HALF_CIRCLE_RIGHT, };

}
namespace insight {
    class instructionals {
    public:
        void setup();
        void add_instructional(std::string text, ControllerInputs control);
        void add_instructional(std::string text, ScaleformButtons button_option);
        void add_instructional(std::string text, int vk);
        void close();
        void main_menu() {
            setup();
            if (render::get()->m_opened) {
                add_instructional("Close", ControllerInputs::INPUT_VEH_FLY_ATTACK_CAMERA);
                add_instructional("Up", ControllerInputs::INPUT_CELLPHONE_UP);
                add_instructional("Down", ControllerInputs::INPUT_CELLPHONE_DOWN);
                add_instructional("Left", ControllerInputs::INPUT_CELLPHONE_LEFT);
                add_instructional("Right", ControllerInputs::INPUT_CELLPHONE_RIGHT);
                add_instructional("Mouse", ControllerInputs::INPUT_CELLPHONE_CAMERA_EXPRESSION);
                add_instructional("Hotkey", ControllerInputs::INPUT_SELECT_CHARACTER_MULTIPLAYER);
            }
            else {
                add_instructional("Open", ControllerInputs::INPUT_VEH_FLY_ATTACK_CAMERA);
            }
            close();
        }     
        void objects_instructional() {
            setup();
            add_instructional("Add To Favorite", ControllerInputs::INPUT_SCRIPT_RLEFT);
            add_instructional("Search", ControllerInputs::INPUT_REPLAY_PREVIEW);
            add_instructional("Clear Search", ControllerInputs::INPUT_REPLAY_TIMELINE_PLACE_CLIP);
            close();
        }

    public:
        static instructionals* get() {
            static instructionals i;
            return &i;
        }
    };
}