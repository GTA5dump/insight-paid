#include "cheat/features/features.hpp"
#include "cheat/features/scripted_globals.hpp"
Blip reveal_off_the_radar_blips[32];
bool was_reveal_off_the_radar_in[32] = { false };
namespace insight {
	void network::reveal_off_the_radar_map(toggle_feature* feature, bool& value) {
		if (!value)
		{
			for (int i = 0; i < 32; ++i) {
				if (was_reveal_off_the_radar_in[i])
				{
					if (HUD::DOES_BLIP_EXIST(reveal_off_the_radar_blips[i]))
					{
						HUD::REMOVE_BLIP(&reveal_off_the_radar_blips[i]);
					}
				}
			}
			return;
		}
		for (int i = 0; i < 32; ++i) {
			was_reveal_off_the_radar_in[i] = true;
			
			
			bool is_player_otr = scripted_globals::get_player_otr(i);;
			if (NETWORK::NETWORK_IS_PLAYER_CONNECTED(i) && is_player_otr)

			{
				Player p = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i);
				Vector3 vec = ENTITY::GET_ENTITY_COORDS(p, true);
				if (!HUD::DOES_BLIP_EXIST(reveal_off_the_radar_blips[i]))
					reveal_off_the_radar_blips[i] = tasks::add_blip_entity(373, 28, p);
				HUD::SET_BLIP_NAME_TO_PLAYER_NAME(reveal_off_the_radar_blips[i], p); // set_player_name
			}

			else if (HUD::DOES_BLIP_EXIST(reveal_off_the_radar_blips[i]))
			{
				HUD::REMOVE_BLIP(&reveal_off_the_radar_blips[i]);
			}
		}
	}
}