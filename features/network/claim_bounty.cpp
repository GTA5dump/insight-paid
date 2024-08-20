#include "cheat/features/features.hpp"
#include "cheat/features/scripted_globals.hpp"



namespace insight {
	void network::claim_bounty() {
		scripted_globals::claim_bounty();
	}
}