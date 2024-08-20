
#include "cheat/features/features.hpp"

#include "cheat/features/tasks.hpp"



namespace insight {
	static timer one_million_loop_time(std::chrono::seconds(1));
	void miscellaneous::one_million_loop(toggle_feature* feature, bool& value) {
		if (!value) {
			return;
		}
		if (one_million_loop_time.update())
			tasks::send_transaction(rage::joaat("CATEGORY_SERVICE_WITH_THRESHOLD"), 1633116913, rage::joaat("NET_SHOP_ACTION_EARN"), 1000000, 4);
	}
}