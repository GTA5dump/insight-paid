

#include "cheat/features/tasks.hpp"
#include "cheat/features/globals.hpp"
#include "cheat/features/features.hpp"


#include "cheat/features/scripted_globals.hpp"
#include "util/notify/notify.hpp"
#include "util/security/xorstr.hpp"

namespace insight {

	void network::null_kick(int i) {
		if (NETWORK::NETWORK_IS_PLAYER_CONNECTED(i)) {
			send_to_interior(i, -1);
		}
	}
}