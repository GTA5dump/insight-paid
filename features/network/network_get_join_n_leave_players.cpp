#include "cheat/features/features.hpp"
#include "cheat/features/scripted_globals.hpp"

namespace insight {
	void network::network_get_join_n_leave_players(toggle_int_feature* feature, bool& value, int& value2) {
		detour::g_network_indicators_leave_join_toggle = value;
		detour::g_network_indicators_leave_join_int = value2;
	}
	void network::indicators_log(toggle_feature* feature, bool& value) {
		detour::g_network_indicators_leave_join_notifcations = value;
	}
	void network::indicators_notify(toggle_feature* feature, bool& value) {
		detour::g_network_indicators_leave_join_console_log = value;
	}
}
