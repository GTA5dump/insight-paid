#include "cheat/features/tasks.hpp"
#include "cheat/features/globals.hpp"
#include "cheat/features/features.hpp"
#include "cheat/features/scripted_globals.hpp"
#include "util/notify/notify.hpp"
#include "util/security/xorstr.hpp"



namespace insight {
	void network::n_esp_box(int target)
	{
		if (NETWORK::NETWORK_IS_PLAYER_CONNECTED(target))
		{
			Ped ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(target);
			tasks::draw_esp_box(ped, 255, 255, 255, 255, target);
		}
		else
		{
			player_options::get()->n_esp_box_value[target] = false;
		}
	}
	void network::n_esp_line(int target)
	{
		if (NETWORK::NETWORK_IS_PLAYER_CONNECTED(target))
		{
			Ped ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(target);
			tasks::draw_esp_line(ped, 255, 255, 255, 255);
		}
		else
		{
			player_options::get()->n_esp_line_value[target] = false;
		}
	}
	void network::n_esp_name(int target)
	{
		if (NETWORK::NETWORK_IS_PLAYER_CONNECTED(target))
		{
			Ped ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(target);
			tasks::draw_esp_name(ped, 255, 255, 255, 255,PLAYER::GET_PLAYER_NAME(target));
		}
		else
		{
			player_options::get()->n_esp_line_value[target] = false;
		}
	}
	void network::n_money_drop(int target)
	{
		if (NETWORK::NETWORK_IS_PLAYER_CONNECTED(target))
		{
			Ped ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(target);
			tasks::spawn_money(1999,ENTITY::GET_ENTITY_COORDS(ped,0));
		}
		else
		{
			player_options::get()->n_money_drop_value[target] = false;
		}
	}
	void network::n_money_rain_value(int target)
	{
		if (NETWORK::NETWORK_IS_PLAYER_CONNECTED(target))
		{
			Ped ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(target);
			Vector3 coords = ENTITY::GET_ENTITY_COORDS(ped, 0);
			coords.x += MISC::GET_RANDOM_FLOAT_IN_RANGE(-4, 4);
			coords.y += MISC::GET_RANDOM_FLOAT_IN_RANGE(-4, 4);
			coords.z += MISC::GET_RANDOM_FLOAT_IN_RANGE(8,10);
			tasks::spawn_money(1999, coords);
		}
		else
		{
			player_options::get()->n_money_rain_value[target] = false;
		}
	}
}