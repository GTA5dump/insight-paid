#include "cheat/features/features.hpp"
namespace insight {
	bool camera_enabled;
	void miscellaneous::camera_zoom(toggle_float_feature* feature, bool& value, float& value2) {
		if (!value) {
			if (camera_enabled) {
				camera_enabled = false;
				CAM::SET_THIRD_PERSON_CAM_ORBIT_DISTANCE_LIMITS_THIS_UPDATE(1.0f, 5);
			}
			return;
		}
		CAM::SET_THIRD_PERSON_CAM_ORBIT_DISTANCE_LIMITS_THIS_UPDATE(1.0f, value2);
		camera_enabled = true;
	}
}