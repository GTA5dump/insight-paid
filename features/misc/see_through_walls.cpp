#include "cheat/features/features.hpp"
namespace insight {
	void miscellaneous::see_through_walls(toggle_feature* feature, bool& value) {
		if (!value)
			return;

		CAM::SET_THIRD_PERSON_AIM_CAM_NEAR_CLIP_THIS_UPDATE(418.490f);
	}
}