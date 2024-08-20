#include "cheat/features/features.hpp"
#include "util/notify/notify.hpp"

namespace insight {
	
	void network::host_kick(int i) {
		if (tasks::is_player_host(globals::player_id)) {
			NETWORK::NETWORK_SESSION_KICK_PLAYER(i);
		}
		else {
			notify::send(xorstr_("Host Kick"), xorstr_("Failed Your Not Host."));
		}
	}
}