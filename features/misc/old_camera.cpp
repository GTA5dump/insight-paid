#include "cheat/features/features.hpp"

namespace insight {
	Cam cam_handle;
	bool cam_was_enabled;
	void miscellaneous::gta_1_camera(toggle_float_feature* feature, bool& value, float& value2) {
		if (!value) {
			if (cam_was_enabled) {
				if (CAM::DOES_CAM_EXIST(cam_handle)) {
					CAM::SET_CAM_ACTIVE(cam_handle, false);
					CAM::RENDER_SCRIPT_CAMS(false, true, 1000, true, false, 1);
					CAM::DESTROY_CAM(cam_handle, false);
					STREAMING::SET_FOCUS_ENTITY(globals::h_local_ped());
				}
				cam_was_enabled = false;
			}
			return;
		}

		if (!CAM::DOES_CAM_EXIST(cam_handle)) {
			cam_handle = CAM::CREATE_CAM("DEFAULT_SCRIPTED_CAMERA", 0);
			CAM::SET_CAM_ACTIVE(cam_handle, 1);
			CAM::RENDER_SCRIPT_CAMS(1, 1, 1000, 1, 0, 0);
		}
		else {
			CAM::ATTACH_CAM_TO_PED_BONE(cam_handle, globals::h_local_ped(), 31086, { 0, 0, value2 }, 1);
			Vector3 Rotation = CAM::GET_GAMEPLAY_CAM_ROT(2);
			CAM::SET_CAM_ROT(cam_handle, { -88, Rotation.y, Rotation.z }, 2);
		}
		cam_was_enabled = true;
	}
}
