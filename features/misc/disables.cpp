#include "cheat/features/features.hpp"

namespace insight {
	void miscellaneous::disable_hud(toggle_feature* feature, bool& value) {
		if (!value)
			return;
		HUD::HIDE_HUD_AND_RADAR_THIS_FRAME();
	}
	bool was_disable_minimap_on = false;
	void miscellaneous::disable_minimap(toggle_feature* feature, bool& value) {
		if (!value) {
			if (was_disable_minimap_on) {
				HUD::DISPLAY_RADAR(true);
				was_disable_minimap_on = false;
			}
			return;
		}
		was_disable_minimap_on = true;
		HUD::DISPLAY_RADAR(false);
	}

	void miscellaneous::disable_notifications(toggle_feature* feature, bool& value) {
		if (!value)
			return;
		HUD::THEFEED_HIDE_THIS_FRAME();//
	}

	void miscellaneous::disable_game_recording(toggle_feature* feature, bool& value) {
		if (!value)
			return;
		if (RECORDING::IS_REPLAY_RECORDING()) {
			RECORDING::CANCEL_REPLAY_RECORDING();
		}
	}

	void miscellaneous::disable_phone(toggle_feature* feature, bool& value) {
		if (!value)
			return;
		tasks::disable_phone();
	}

	void miscellaneous::disable_stunt_jump(toggle_feature* feature, bool& value) {
		if (!value)
			return;
		if (MISC::IS_STUNT_JUMP_IN_PROGRESS()) {
			MISC::CANCEL_STUNT_JUMP();
		}
	}

	void miscellaneous::disable_cinematic(toggle_feature* feature, bool& value) {
		if (!value)
			return;
		CAM::SET_CINEMATIC_MODE_ACTIVE(0);
		CAM::STOP_GAMEPLAY_HINT(true);
		AUDIO::STOP_AUDIO_SCENE("HINT_CAM_SCENE");
		GRAPHICS::ANIMPOSTFX_STOP("FocusIn");
		GRAPHICS::ANIMPOSTFX_STOP("FocusOut");
	}

	void miscellaneous::disable_cutscenes(toggle_feature* feature, bool& value) {
		if (!value)
			return;
		if (CUTSCENE::IS_CUTSCENE_ACTIVE()) {
			CUTSCENE::STOP_CUTSCENE_IMMEDIATELY();
		}
	}
}