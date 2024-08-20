#include "cheat/features/features.hpp"

namespace insight {
	void network::show_invisible_players(toggle_feature* feature, bool& value) {
		if (!value) {		
			return;
		}
		for (int i = 0; i < 32; ++i)
		{
			if (NETWORK::NETWORK_IS_PLAYER_CONNECTED(i))
			{
				Player b = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i);
				if (!ENTITY::IS_ENTITY_VISIBLE(b))
				{
					NETWORK::SET_ENTITY_LOCALLY_VISIBLE(b);
				}

			}

		}
	}
}