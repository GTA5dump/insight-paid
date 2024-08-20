#include "commands.hpp"
#include "natives.hpp"
#include "cheat/features/tasks.hpp"
#include "util/script/fiber_pool.hpp"
#include <algorithm>
namespace insight {
	struct PaintColour_struct_ {
		const char* Paintname;
		int Paintvalue;
		int Pearlescentvalue;
	};
	PaintColour_struct_ founded_paint;
	PaintColour_struct_ pearl_paint;
	std::vector<PaintColour_struct_> vehicle_paint_mattelic{
		{"Black", 0, 0},
		{ "Carbon Black", 147, 0 },
		{ "Graphite Black", 1, 0 },
		{ "Anthracite Black", 11, 0 },
		{ "Black Steel", 2, 0 },
		{ "Dark Steel", 3, 2 },
		{ "Silver", 4, 4 },
		{ "Bluish Silver", 5, 5 },
		{ "Rolled Steel", 6, 0 },
		{ "Shadow Silver", 7, 0 },
		{ "Stone Silver", 8, 0 },
		{ "Midnight Silver", 9, 0 },
		{ "Cast Iron Silver", 10, 0 },
		{ "Red", 27, 0 },
		{ "Torino Red", 28, 0 },
		{ "Formula Red", 29, 0 },
		{ "Lava Red", 150, 0 },
		{ "Blaze Red", 30, 0 },
		{ "Grace Red", 31, 0 },
		{ "Garnet Red", 32, 0 },
		{ "Sunset Red", 33, 0 },
		{ "Cabernet Red", 34, 0 },
		{ "Wine Red", 143, 0 },
		{ "Candy Red", 35, 0 },
		{ "Hot Pink", 135, 0 },
		{ "Pfister Pink", 137, 0 },
		{ "Salmon Pink", 136, 0 },
		{ "Sunrise Orange", 36, 0 },
		{ "Orange", 38, 0 },
		{ "Bright Orange", 138, 0 },
		{ "Gold", 99, 99 },
		{ "Bronze", 90, 102 },
		{ "Yellow", 88, 0 },
		{ "Race Yellow", 89, 0 },
		{ "Dew Yellow", 91, 0 },
		{ "Dark Green", 49, 0 },
		{ "Racing Green", 50, 0 },
		{ "Sea Green", 51, 0 },
		{ "Olive Green", 52, 0 },
		{ "Bright Green", 53, 0 },
		{ "Gasoline Green", 54, 0 },
		{ "Lime Green", 92, 0 },
		{ "Midnight Blue", 141, 0 },
		{ "Galaxy Blue", 61, 0 },
		{ "Dark Blue", 62, 0 },
		{ "Saxon Blue", 63, 0 },
		{ "Blue", 64, 0 },
		{ "Mariner Blue", 65, 0 },
		{ "Harbor Blue", 66, 0 },
		{ "Diamond Blue", 67, 0 },
		{ "Surf Blue", 68, 0 },
		{ "Nautical Blue", 69, 0 },
		{ "Racing Blue", 73, 0 },
		{ "Ultra Blue", 70, 0 },
		{ "Light Blue", 74, 0 },
		{ "Chocolate Brown", 96, 0 },
		{ "Bison Brown", 101, 0 },
		{ "Creek Brown", 95, 0 },
		{ "Feltzer Brown", 94, 0 },
		{ "Maple Brown", 97, 0 },
		{ "Beechwood Brown", 103, 0 },
		{ "Sienna Brown", 104, 0 },
		{ "Saddle Brown", 98, 0 },
		{ "Moss Brown", 100, 0 },
		{ "Woodbeech Brown", 102, 0 },
		{ "Straw Brown", 99, 0 },
		{ "Sandy Brown", 105, 0 },
		{ "Bleached Brown", 106, 0 },
		{ "Schafter Purple", 71, 0 },
		{ "Spinnaker Purple", 72, 0 },
		{ "Midnight Purple", 142, 0 },
		{ "Bright Purple", 145, 0 },
		{ "Cream", 107, 0 },
		{ "Ice White", 111, 0 },
		{ "Frost White", 112, 0 }
	};
	std::vector<PaintColour_struct_> vehicle_paint_matte{
		{ "Black", 12, 0},
		{ "Gray", 13, 0 },
		{ "Light Gray", 14, 0 },
		{ "Ice White", 131, 0 },
		{ "Blue", 83, 0 },
		{ "Dark Blue", 82, 0 },
		{ "Midnight Blue", 84, 0 },
		{ "Midnight Purple", 149, 0 },
		{ "Schafter Purple", 148, 0 },
		{ "Red", 39, 0 },
		{ "Dark Red", 40, 0 },
		{ "Orange", 41, 0 },
		{ "Yellow", 42, 0 },
		{ "Lime Green", 55, 0 },
		{ "Green", 128, 0 },
		{ "Forest Green", 151, 0 },
		{ "Foliage Green", 155, 0 },
		{ "Olive Drab", 152, 0 },
		{ "Dark Earth", 153, 0 },
		{ "Desert Tan", 154, 0 }
	};
	std::vector<PaintColour_struct_> vehicle_paint_metal{
		{"Brushed Steel", 117, 18},
		{ "Brushed Black Steel", 118, 3 },
		{ "Brushed Aluminum", 119, 5 },
		{ "Pure Gold", 158, 160 },
		{ "Brushed Gold", 159, 160 }
	};
	std::vector<PaintColour_struct_> vehicle_paint_pearlescent{
		{"Black", -1, 0},
		{ "Carbon Black", -1, 147 },
		{ "Graphite Black", -1, 1 },
		{ "Anthracite Black", -1, 11 },
		{ "Black Steel", -1, 2 },
		{ "Dark Steel", -1, 3 },
		{ "Silver", -1, 4 },
		{ "Bluish Silver", -1, 5 },
		{ "Rolled Steel", -1, 6 },
		{ "Shadow Silver", -1, 7 },
		{ "Stone Silver", -1, 8 },
		{ "Midnight Silver", -1, 9 },
		{ "Cast Iron Silver", -1, 10 },
		{ "Red", -1, 27 },
		{ "Torino Red", -1, 28 },
		{ "Formula Red", -1, 29 },
		{ "Lava Red", -1, 150 },
		{ "Blaze Red", -1, 30 },
		{ "Grace Red", -1, 31 },
		{ "Garnet Red", -1, 32 },
		{ "Sunset Red", -1, 33 },
		{ "Cabernet Red", -1, 34 },
		{ "Wine Red", -1, 143 },
		{ "Candy Red", -1, 35 },
		{ "Hot Pink", -1, 135 },
		{ "Pfister Pink", -1, 137 },
		{ "Salmon Pink", -1, 136 },
		{ "Sunrise Orange", -1, 36 },
		{ "Orange", -1, 38 },
		{ "Bright Orange", -1, 138 },
		{ "Gold", -1, 37 },
		{ "Bronze", -1, 90 },
		{ "Yellow", -1, 88 },
		{ "Race Yellow", -1, 89 },
		{ "Dew Yellow", -1, 91 },
		{ "Dark Green", -1, 49 },
		{ "Racing Green", -1, 50 },
		{ "Sea Green", -1, 51 },
		{ "Olive Green", -1, 52 },
		{ "Bright Green", -1, 53 },
		{ "Gasoline Green", -1, 54 },
		{ "Lime Green", -1, 92 },
		{ "Midnight Blue", -1, 141 },
		{ "Galaxy Blue", -1, 61 },
		{ "Dark Blue", -1, 62 },
		{ "Saxon Blue", -1, 63 },
		{ "Blue", -1, 64 },
		{ "Mariner Blue", -1, 65 },
		{ "Harbor Blue", -1, 66 },
		{ "Diamond Blue", -1, 67 },
		{ "Surf Blue", -1, 68 },
		{ "Nautical Blue", -1, 69 },
		{ "Racing Blue", -1, 73 },
		{ "Ultra Blue", -1, 70 },
		{ "Light Blue", -1, 74 },
		{ "Chocolate Brown", -1, 96 },
		{ "Bison Brown", -1, 101 },
		{ "Creek Brown", -1, 95 },
		{ "Feltzer Brown", -1, 94 },
		{ "Maple Brown", -1, 97 },
		{ "Beechwood Brown", -1, 103 },
		{ "Sienna Brown", -1, 104 },
		{ "Saddle Brown", -1, 98 },
		{ "Moss Brown", -1, 100 },
		{ "Woodbeech Brown", -1, 102 },
		{ "Straw Brown", -1, 99 },
		{ "Sandy Brown", -1, 105 },
		{ "Bleached Brown", -1, 106 },
		{ "Schafter Purple", -1, 71 },
		{ "Spinnaker Purple", -1, 72 },
		{ "Midnight Purple", -1, 146 },
		{ "Bright Purple", -1, 145 },
		{ "Cream", -1, 107 },
		{ "Ice White", -1, 111 },
		{ "Frost White", -1, 112 },
		{ "Secret Gold", -1, 160 }
	};
	std::vector<std::string> stored_msgs;
	bool contains_color(const std::string chat_msg, std::vector<PaintColour_struct_> b) {
		std::string lowercaseText = chat_msg;
		std::transform(lowercaseText.begin(), lowercaseText.end(), lowercaseText.begin(), ::tolower);
		for (const auto& color_info : b) {
			std::string lowercaseColorName = color_info.Paintname;
			std::transform(lowercaseColorName.begin(), lowercaseColorName.end(), lowercaseColorName.begin(), ::tolower);
			if (lowercaseText.find(lowercaseColorName) != std::string::npos) {
				founded_paint = color_info;
				if (chat_msg == "pearlescent") {
					pearl_paint = color_info;
				}
				return true;
			}
		}
		return false;
	}

	void chat_cds::create_model(int player, std::string chat_msg, bool _ped, bool _vehicle, bool _object) {
		if (!_ped && !_vehicle && !_object)
			return;
		g_fiber_pool->queue_job([=] {
			bool upgraded = false;
			bool mattelic = false;
			bool matte = false;
			bool metal = false;
			bool pearlescent = false;
			bool colored = false;
			stored_msgs.clear();
			if (chat_msg.empty())
				return;
			if (chat_msg.find(".spawn") != std::string::npos || chat_msg.find(".create") != std::string::npos) {
				std::istringstream iss(chat_msg);
				std::string word;
				while (iss >> word) {
					if (word != ".spawn" && word != ".create") {
						stored_msgs.push_back(word);
						if (_object) {
							if (word == "upgraded" || word == "upgrade" || word == "mods") {
								upgraded = true;
							}
							if (word == "mattelic")
								if (contains_color(word, vehicle_paint_mattelic)) {
									colored = true;
									mattelic = true;
								}
							if (word == "matte")
								if (contains_color(word, vehicle_paint_matte)) {
									colored = true;
									matte = true;

								}
							if (word == "metal")
								if (contains_color(word, vehicle_paint_metal)) {
									colored = true;
									metal = true;
								}
							if (word == "pearlescent")
								if (contains_color(word, vehicle_paint_pearlescent)) {
									colored = true;
									pearlescent = true;
								}
						}
					}
				}
			}
			else return;
			for (int i = 0; i < stored_msgs.size(); i++) {
				Hash spawn_model = rage::joaat(stored_msgs[i]);
				if (STREAMING::IS_MODEL_VALID(spawn_model)) {
					Ped player_ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player);
					Vector3 spawn_pos = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(player_ped, Vector3(0, 2.f, 0));
					float heading = ENTITY::GET_ENTITY_HEADING(player_ped);
					if (STREAMING::IS_MODEL_A_VEHICLE(spawn_model)) {
						if (_vehicle) {
							tasks::request_model(spawn_model);
							Vehicle veh = VEHICLE::CREATE_VEHICLE(spawn_model, spawn_pos, heading, true, 0, 0);
							if (upgraded) {
								tasks::upgrade_vehicle(veh);
							}
							if (colored)
								VEHICLE::SET_VEHICLE_COLOURS(veh, founded_paint.Paintvalue, founded_paint.Paintvalue);

							if (mattelic) {
								VEHICLE::SET_VEHICLE_COLOURS(veh, founded_paint.Paintvalue, founded_paint.Paintvalue);
							}
							if (matte) {
								VEHICLE::SET_VEHICLE_COLOURS(veh, founded_paint.Paintvalue, founded_paint.Paintvalue);
							}
							if (metal) {
								VEHICLE::SET_VEHICLE_COLOURS(veh, founded_paint.Paintvalue, founded_paint.Paintvalue);
							}
							if (pearlescent) {
								VEHICLE::SET_VEHICLE_COLOURS(veh, founded_paint.Paintvalue, founded_paint.Paintvalue);
							}
						}
					}
					else
						if (STREAMING::IS_MODEL_A_PED(spawn_model)) {
							if (_ped) {
								tasks::request_model(spawn_model);
								Ped ped = PED::CREATE_PED(26, spawn_model, spawn_pos, heading, true, 0);
								PED::SET_PED_DEFAULT_COMPONENT_VARIATION(ped);
							}
						}
						else {
							if (_object) {
								tasks::request_model(spawn_model);
								OBJECT::CREATE_OBJECT(spawn_model, spawn_pos, true, 0, 0);
							}
						}
				}
			}
			});
	}

	void chat_cds::kill_player(bool toggle, int player, std::string chat_msg) {
		if (!toggle)
			return;
		if (chat_msg.empty())
			return;
		g_fiber_pool->queue_job([=] {
			int target_player = -1;
			if (chat_msg.find(".kill") != std::string::npos) {
				std::istringstream iss(chat_msg);
				std::string word;
				while (iss >> word) {
					if (word != ".kill") {
						for (int i = 0; i < 32; i++) {
							if (NETWORK::NETWORK_IS_PLAYER_CONNECTED(i)) {
								const char* name = PLAYER::GET_PLAYER_NAME(i);
								std::string lowercaseWord = _strlwr(_strdup(word.c_str()));
								std::string lowercaseName = _strlwr(_strdup(name));
								if (word == name) {
									target_player = i;
									break;
								}
								else
									if (lowercaseName.find(lowercaseWord) != std::string::npos) {
										target_player = i;
										break;
									}
							}
						}
					}
				}
			}
			else return;
			if (target_player == -1) return;
			else
				FIRE::ADD_OWNED_EXPLOSION(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player),
					ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(target_player), 0),
					18, 999.F, FALSE, TRUE, 0);
			});
	}
	void chat_cds::explode_player(bool toggle, int player, std::string chat_msg) {
		if (!toggle)
			return;
		if (chat_msg.empty())
			return;
		g_fiber_pool->queue_job([=] {
			int target_player = -1;
			if (chat_msg.find(".explode") != std::string::npos) {
				std::istringstream iss(chat_msg);
				std::string word;
				while (iss >> word) {
					if (word != ".explode") {
						for (int i = 0; i < 32; i++) {
							if (NETWORK::NETWORK_IS_PLAYER_CONNECTED(i)) {
								const char* name = PLAYER::GET_PLAYER_NAME(i);
								std::string lowercaseWord = _strlwr(_strdup(word.c_str()));
								std::string lowercaseName = _strlwr(_strdup(name));
								if (word == name) {
									target_player = i;
									break;
								}
								else
									if (lowercaseName.find(lowercaseWord) != std::string::npos) {
										target_player = i;
										break;
									}
							}
						}
					}
				}
			}
			else return;
			if (target_player == -1) return;
			else
				FIRE::ADD_EXPLOSION(ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(target_player), 0),
					18, 999.F, TRUE, FALSE, 0, FALSE);
			});
	}
	void chat_cds::kms(bool toggle, int player, std::string chat_msg) {
		if (!toggle)
			return;
		if (chat_msg.empty())
			return;
		g_fiber_pool->queue_job([=] {
			int target_player = -1;
			if (chat_msg.find(".kms") != std::string::npos || chat_msg.find(".kill my self") != std::string::npos) {
				std::istringstream iss(chat_msg);
				std::string word;
				while (iss >> word) {
					if (word != ".kms" && word != ".kill my self") {
						FIRE::ADD_OWNED_EXPLOSION(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player),
							ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player), 0),
							18, 999.F, FALSE, TRUE, 0);

					}
				}
			}
			});
	}
	bool chat_cds::money_rp(bool toggle, int player, std::string chat_msg) {
		if (!toggle)
			return false;
		if (chat_msg.empty())
			return false;
		int target_player = -1;
		if (chat_msg.find(".money") != std::string::npos || chat_msg.find(".rp") != std::string::npos) {
			std::istringstream iss(chat_msg);
			std::string word;
			while (iss >> word) {
				if (word != ".money" && word != ".rp") {
					return true;
				}
			}
		}
		return false;
	}
	void chat_cds::fix_veh(bool toggle, int player, std::string chat_msg) {
		if (!toggle)
			return;
		if (chat_msg.empty())
			return;
		g_fiber_pool->queue_job([=] {
			if (chat_msg.find(".fix") != std::string::npos || chat_msg.find(".repair") != std::string::npos) {
				if (auto veh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player))) {
					if (tasks::request_control(veh))
					tasks::fix_vehicle(veh);
				}
			}
			});
	}	
	void chat_cds::upgrade_veh(bool toggle, int player, std::string chat_msg) {
		if (!toggle)
			return;
		if (chat_msg.empty())
			return;
		g_fiber_pool->queue_job([=] {
			if (chat_msg.find(".upgrade") != std::string::npos || chat_msg.find(".pimp") != std::string::npos) {
				if (auto veh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player))) {
					if (tasks::request_control(veh))
					tasks::upgrade_vehicle(veh);
				}
			}
			});
	}
}
