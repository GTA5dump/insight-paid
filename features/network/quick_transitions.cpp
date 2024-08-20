#include "cheat/features/features.hpp"
#include "util/script/script_global.hpp"

namespace insight {
	void network::quick_transitions(int session) {
		*script_global(2695915).as<bool*>() = session == 13;
		*script_global(session == -1 ? 1574591 : 1575020).as<int*>() = session;
		*script_global(1574589).as<bool*>() = true;		
		script::get_current()->yield(200ms);
		*script_global(1574589).as<bool*>() = false;
	}
}