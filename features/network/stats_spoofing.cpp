#include "cheat/features/globals.hpp"
#include "cheat/features/features.hpp"
#include "cheat/features/scripted_globals.hpp"
#include "util/script/script_global.hpp"



namespace insight {
	void network::spoof_kills(toggle_int_feature* feature, bool& value, int& value2) {
		if (!value)
			return;
		scripted_globals::set_player_stat(28, value2);
	}

	void network::spoof_rank(toggle_int_feature* feature, bool& value, int& value2) {
		if (!value)
			return;
		scripted_globals::set_player_stat(6, value2);
	}

	void network::spoof_cash(toggle_int_feature* feature, bool& value, int& value2) {
		if (!value)
			return;
		scripted_globals::set_player_stat(3, value2);
	}

	void network::spoof_bank(toggle_int_feature* feature, bool& value, int& value2) {
		if (!value)
			return;
		scripted_globals::set_player_stat(56, value2);
	}

	void network::spoof_input(toggle_int_feature* feature, bool& value, int& value2) {
		if (!value)
			return;
		*script_global(1853988).at(globals::player_id, 862).at(96).at(29).as<int*>() = value2 + 1;
	}
}