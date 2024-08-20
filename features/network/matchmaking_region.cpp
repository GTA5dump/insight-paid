#include "cheat/features/features.hpp"

int regions_corrected[] = {
	5, 3, 4, 7, 1, 0, 0, 6
};
namespace insight {
	void network::matchmaking_region(toggle_int_feature* feature, bool& value, int& value2) {
		if (!value)
			return;
		static int timer;
		if ((timeGetTime() - timer) > 100000) {
			*insight::pointers::get()->g_matchmaking_region = (u32)regions_corrected[value2];
		}
	}
}
