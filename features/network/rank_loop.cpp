#include "cheat/features/globals.hpp"
#include "cheat/features/features.hpp"

namespace insight {
	static timer rank_loop_timer(std::chrono::milliseconds(1000));
	bool was_rank_loop_on = false;
	void network::rank_loop(toggle_int_feature* feature, bool& value, int& value2) {
		if (!value) {
			if (was_rank_loop_on) {
				player_options::get()->remote_rp_value[globals::player_id] = false;
				was_rank_loop_on = false;
			}
			return;
		}
		if (!was_rank_loop_on) {

			was_rank_loop_on = true;
		}
		rank_loop_timer.setdelay(std::chrono::milliseconds(value2 * 100));
		if (rank_loop_timer.update()) {
			player_options::get()->remote_rp_value[globals::player_id] = true;
		}	

	}
}