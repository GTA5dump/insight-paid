#include "cheat/features/features.hpp"
#include "util/script/script_global.hpp"

namespace insight {
	
	void network::no_idle_kick(toggle_feature* feature, bool& value) {
		if (!value)
			return;

		*script_global(1654054).at(1155).as<int*>() = 0;//idle kick
		*script_global(262145).at(87).as<int*>() = 120000;//idle kick
		*script_global(262145).at(88).as<int*>() = 300000;//idle kick
		*script_global(262145).at(89).as<int*>() = 600000;//idle kick
		*script_global(262145).at(90).as<int*>() = 900000;//idle kick

		*script_global(1654054).at(1171).as<int*>() = 0;//idle kick
		*script_global(262145).at(8420).as<int*>() = 30000;//idle kick
		*script_global(262145).at(8421).as<int*>() = 60000;//idle kick
		*script_global(262145).at(8422).as<int*>() = 90000;//idle kick
		*script_global(262145).at(8423).as<int*>() = 120000;//idle kick
	}
}