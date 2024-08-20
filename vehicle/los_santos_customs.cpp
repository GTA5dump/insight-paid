#include "cheat/script/script.hpp"
#include "cheat/menu/helper/ui.hpp"
#include "util/panels/panels.hpp"
#include "util/config/config.hpp"
#include "cheat/features/globals.hpp"
#include "util/math/math.hpp"
#include "cheat/features/features/features_utility.hpp"
#include "cheat/script/script_utility.hpp"
#include "game/gta/enums.hpp"
namespace insight {
	struct Struct_Lebel_Data
	{
		const char* lebel;
		const char* def;
	};


	std::vector<Struct_Lebel_Data> VehicleModTypes_Armor_Lebel{
		{"CMOD_ARM_0", "None"},
		{"CMOD_ARM_1", "Armor Upgrade 20%"},
		{"CMOD_ARM_2", "Armor Upgrade 40%"},
		{"CMOD_ARM_3", "Armor Upgrade 60%"},
		{"CMOD_ARM_4", "Armor Upgrade 80%"},
		{"CMOD_ARM_5", "Armor Upgrade 100%"}
	};

	std::vector<Struct_Lebel_Data> VehicleModTypes_Brakes_Lebel{
		{"CMOD_BRA_1", "Street Brakes"},
		{"CMOD_BRA_2", "Sport Brakes"},
		{"CMOD_BRA_3", "Race Brakes"},
		{"CMOD_BRA_4", "Super Brakes"},
		{"CMOD_BRA_5", "HSW Brakes"},
		{"CMOD_BRA_6", "Unknown"},
		{"CMOD_BRA_7", "Unknown"},
		{"CMOD_BRA_8", "Unknown"},
		{"CMOD_BRA_9", "Unknown"}
	};

	std::vector<Struct_Lebel_Data> VehicleModTypes_Transmission_Lebel{
		{"UNK", "Stock Transmission"},
		{"CMOD_GBX_1", "Street Transmission"},
		{"CMOD_GBX_3", "Sports Transmission"},
		{"CMOD_GBX_4", "Race Transmission"},
		{"CMOD_GBX_5", "HSW Transmission"},
		{"CMOD_GBX_6", "Unknown"},
		{"CMOD_GBX_7", "Unknown"},
		{"CMOD_GBX_8", "Unknown"},
		{"CMOD_GBX_9", "Unknown"}
	};

	std::vector<Struct_Lebel_Data> VehicleModTypes_Horn_Lebel{
		{"HORN_STOCK", "Stock Horn"},
		{"HORN_TRUCK", "Truck Horn"},
		{"HORN_POLICE", "Cop Horn"},
		{"HORN_CLOWN", "Clown Horn"},
		{"HORN_MUSICAL1", "Musical Horn 1"},
		{"HORN_MUSICAL2", "Musical Horn 2"},
		{"HORN_MUSICAL3", "Musical Horn 3"},
		{"HORN_MUSICAL4", "Musical Horn 4"},
		{"HORN_MUSICAL5", "Musical Horn 5"},
		{"HORN_SADTROMBONE", "Sad Trombone"},
		{"HORN_CALSSICAL1", "Classical Horn 1"},
		{"HORN_CALSSICAL2", "Classical Horn 2"},
		{"HORN_CALSSICAL3", "Classical Horn 3"},
		{"HORN_CALSSICAL4", "Classical Horn 4"},
		{"HORN_CALSSICAL5", "Classical Horn 5"},
		{"HORN_CALSSICAL6", "Classical Horn 6"},
		{"HORN_CALSSICAL7", "Classical Horn 7"},
		{"HORN_SCALEDO", "Scale - Do"},
		{"HORN_SCALERE", "Scale - Re"},
		{"HORN_SCALEMI", "Scale - Mi"},
		{"HORN_SCALEFA", "Scale - Fa"},
		{"HORN_SCALESOL", "Scale - Sol"},
		{"HORN_SCALELA", "Scale - La"},
		{"HORN_SCALETI", "Scale - Ti"},
		{"HORN_SCALEDO_HIG", "Scale - Do (high)"},
		{"HORN_JAZZ1", "Jazz Horn 1"},
		{"HORN_JAZZ2", "Jazz Horn 2"},
		{"HORN_JAZZ3", "Jazz Horn 3"},
		{"HORN_JAZZLOOP", "Jazz Horn Loop"},
		{"HORN_STARSPANGBA1", "Star Spangled Banner 1"},
		{"HORN_STARSPANGBA2", "Star Spangled Banner 2"},
		{"HORN_STARSPANGBA3", "Star Spangled Banner 3"},
		{"HORN_STARSPANGBA4", "Star Spangled Banner 4"},
		{"HORN_CLASSICALLO1", "Classical Horn Loop 1"},
		{"HORN_CLASSICAL8", "Classical Horn 8"},
		{"HORN_CLASSICALLO2", "Classical Horn Loop 2"},
		{"HORN_CLASSICALLO3", "Unknown Classical 1"},
		{"HORN_CLASSICALLO4", "Unknown Classical 2"},
		{"HORN_CLASSICALLO5", "Unknown Classical 3"},
		{"HORN_CLASSICALLO6", "Halloween 1"},
		{"HORN_CLASSICALLO7", "Halloween 2"},
		{"HORN_CLASSICALLO8", "Halloween 3"},
		{"HORN_CLASSICALLO9", "Halloween 4"},
		{"HORN_CLASSICALLO10", "San Andreas Loop"},
		{"HORN_CLASSICALLO11", "Liberty City Loop 1"},
		{"HORN_CLASSICALLO12", "Liberty City Loop 2"},
		{"HORN_CLASSICALLO13", "Liberty City Loop 3"},
		{"HORN_CLASSICALLO14", "Jingle Bells"},
		{"HORN_CLASSICALLO15", "Sleigh Bells"},
		{"HORN_CLASSICALLO16", "Deck the Halls"},
		{"HORN_CLASSICALLO17", "Sleigh Bells Loop"},
		{"HORN_CLASSICALLO18", "Organ Song"},
		{"HORN_CLASSICALLO19", "Sleigh Bells Loop 2"},
		{"HORN_CLASSICALLO20", "Air Horn 1"},
		{"HORN_CLASSICALLO21", "Air Horn 2"},
		{"HORN_CLASSICALLO22", "Air Horn 3"},
		{"HORN_CLASSICALLO23", "Air Horn 4"},
		{"HORN_CLASSICALLO24", "Air Horn 5"},
		{"HORN_CLASSICALLO25", "Air Horn 6"},
		{"HORN_CLASSICALLO26", "Unknown"}
	};

	std::vector<Struct_Lebel_Data> VehicleModTypes_Suspension_Lebel{
		{"CMOD_SUS_0", "Stock Suspension"},
		{"CMOD_SUS_1", "Lowered Suspension"},
		{"CMOD_SUS_2", "Street Suspension"},
		{"CMOD_SUS_3", "Sport Suspension"},
		{"CMOD_SUS_4", "Race Suspension"},
		{"CMOD_SUS_5", "Unknown"},
		{"CMOD_SUS_6", "Unknown"},
		{"CMOD_SUS_7", "Unknown"},
		{"CMOD_SUS_8", "Unknown"}
	};

	std::vector<Struct_Lebel_Data> VehicleModTypes_Windows_Lebel{
		{"CMOD_WIN_0", "Unknown"},
		{"CMOD_WIN_1", "None"},
		{"CMOD_WIN_2", "Limousine"},
		{"CMOD_WIN_3", "Dark Smoke Glass"},
		{"CMOD_WIN_4", "Light Smoke Glass"},
		{"CMOD_WIN_5", "Unknown"},
		{"CMOD_WIN_6", "Unknown"},
		{"CMOD_WIN_7", "Unknown"},
		{"CMOD_WIN_8", "Unknown"},
		{"CMOD_WIN_9", "Unknown"}
	};

	struct PaintColour_struct {
		const char* Paintname;
		int Paintvalue;
		int Pearlescentvalue;
	};

	std::vector<PaintColour_struct> PAINTS_CAR_NORMAL_MATTELIC{
		{"Black", 0, 0},
		{"Carbon Black", 147, 0},
		{"Graphite Black", 1, 0},
		{"Anthracite Black", 11, 0},
		{"Black Steel", 2, 0},
		{"Dark Steel", 3, 2},
		{"Silver", 4, 4},
		{"Bluish Silver", 5, 5},
		{"Rolled Steel", 6, 0},
		{"Shadow Silver", 7, 0},
		{"Stone Silver", 8, 0},
		{"Midnight Silver", 9, 0},
		{"Cast Iron Silver", 10, 0},
		{"Red", 27, 0},
		{"Torino Red", 28, 0},
		{"Formula Red", 29, 0},
		{"Lava Red", 150, 0},
		{"Blaze Red", 30, 0},
		{"Grace Red", 31, 0},
		{"Garnet Red", 32, 0},
		{"Sunset Red", 33, 0},
		{"Cabernet Red", 34, 0},
		{"Wine Red", 143, 0},
		{"Candy Red", 35, 0},
		{"Hot Pink", 135, 0},
		{"Pfister Pink", 137, 0},
		{"Salmon Pink", 136, 0},
		{"Sunrise Orange", 36, 0},
		{"Orange", 38, 0},
		{"Bright Orange", 138, 0},
		{"Gold", 99, 99},
		{"Bronze", 90, 102},
		{"Yellow", 88, 0},
		{"Race Yellow", 89, 0},
		{"Dew Yellow", 91, 0},
		{"Dark Green", 49, 0},
		{"Racing Green", 50, 0},
		{"Sea Green", 51, 0},
		{"Olive Green", 52, 0},
		{"Bright Green", 53, 0},
		{"Gasoline Green", 54, 0},
		{"Lime Green", 92, 0},
		{"Midnight Blue", 141, 0},
		{"Galaxy Blue", 61, 0},
		{"Dark Blue", 62, 0},
		{"Saxon Blue", 63, 0},
		{"Blue", 64, 0},
		{"Mariner Blue", 65, 0},
		{"Harbor Blue", 66, 0},
		{"Diamond Blue", 67, 0},
		{"Surf Blue", 68, 0},
		{"Nautical Blue", 69, 0},
		{"Racing Blue", 73, 0},
		{"Ultra Blue", 70, 0},
		{"Light Blue", 74, 0},
		{"Chocolate Brown", 96, 0},
		{"Bison Brown", 101, 0},
		{"Creek Brown", 95, 0},
		{"Feltzer Brown", 94, 0},
		{"Maple Brown", 97, 0},
		{"Beechwood Brown", 103, 0},
		{"Sienna Brown", 104, 0},
		{"Saddle Brown", 98, 0},
		{"Moss Brown", 100, 0},
		{"Woodbeech Brown", 102, 0},
		{"Straw Brown", 99, 0},
		{"Sandy Brown", 105, 0},
		{"Bleached Brown", 106, 0},
		{"Schafter Purple", 71, 0},
		{"Spinnaker Purple", 72, 0},
		{"Midnight Purple", 142, 0},
		{"Bright Purple", 145, 0},
		{"Cream", 107, 0},
		{"Ice White", 111, 0},
		{"Frost White", 112, 0}
	};
	std::vector<PaintColour_struct> PAINTS_CAR_MATTE{
		{"Black", 12, 0},
		{"Gray", 13, 0},
		{"Light Gray", 14, 0},
		{"Ice White", 131, 0},
		{"Blue", 83, 0},
		{"Dark Blue", 82, 0},
		{"Midnight Blue", 84, 0},
		{"Midnight Purple", 149, 0},
		{"Schafter Purple", 148, 0},
		{"Red", 39, 0},
		{"Dark Red", 40, 0},
		{"Orange", 41, 0},
		{"Yellow", 42, 0},
		{"Lime Green", 55, 0},
		{"Green", 128, 0},
		{"Forest Green", 151, 0},
		{"Foliage Green", 155, 0},
		{"Olive Drab", 152, 0},
		{"Dark Earth", 153, 0},
		{"Desert Tan", 154, 0}
	};
	std::vector<PaintColour_struct> PAINTS_CAR_METAL{
		{"Brushed Steel", 117, 18},
		{"Brushed Black Steel", 118, 3},
		{"Brushed Aluminum", 119, 5},
		{"Pure Gold", 158, 160},
		{"Brushed Gold", 159, 160}
	};
	std::vector<PaintColour_struct> PAINTS_CAR_PEARLESCENT{
		{"Black", -1, 0},
		{"Carbon Black", -1, 147},
		{"Graphite Black", -1, 1},
		{"Anthracite Black", -1, 11},
		{"Black Steel", -1, 2},
		{"Dark Steel", -1, 3},
		{"Silver", -1, 4},
		{"Bluish Silver", -1, 5},
		{"Rolled Steel", -1, 6},
		{"Shadow Silver", -1, 7},
		{"Stone Silver", -1, 8},
		{"Midnight Silver", -1, 9},
		{"Cast Iron Silver", -1, 10},
		{"Red", -1, 27},
		{"Torino Red", -1, 28},
		{"Formula Red", -1, 29},
		{"Lava Red", -1, 150},
		{"Blaze Red", -1, 30},
		{"Grace Red", -1, 31},
		{"Garnet Red", -1, 32},
		{"Sunset Red", -1, 33},
		{"Cabernet Red", -1, 34},
		{"Wine Red", -1, 143},
		{"Candy Red", -1, 35},
		{"Hot Pink", -1, 135},
		{"Pfister Pink", -1, 137},
		{"Salmon Pink", -1, 136},
		{"Sunrise Orange", -1, 36},
		{"Orange", -1, 38},
		{"Bright Orange", -1, 138},
		{"Gold", -1, 37},
		{"Bronze", -1, 90},
		{"Yellow", -1, 88},
		{"Race Yellow", -1, 89},
		{"Dew Yellow", -1, 91},
		{"Dark Green", -1, 49},
		{"Racing Green", -1, 50},
		{"Sea Green", -1, 51},
		{"Olive Green", -1, 52},
		{"Bright Green", -1, 53},
		{"Gasoline Green", -1, 54},
		{"Lime Green", -1, 92},
		{"Midnight Blue", -1, 141},
		{"Galaxy Blue", -1, 61},
		{"Dark Blue", -1, 62},
		{"Saxon Blue", -1, 63},
		{"Blue", -1, 64},
		{"Mariner Blue", -1, 65},
		{"Harbor Blue", -1, 66},
		{"Diamond Blue", -1, 67},
		{"Surf Blue", -1, 68},
		{"Nautical Blue", -1, 69},
		{"Racing Blue", -1, 73},
		{"Ultra Blue", -1, 70},
		{"Light Blue", -1, 74},
		{"Chocolate Brown", -1, 96},
		{"Bison Brown", -1, 101},
		{"Creek Brown", -1, 95},
		{"Feltzer Brown", -1, 94},
		{"Maple Brown", -1, 97},
		{"Beechwood Brown", -1, 103},
		{"Sienna Brown", -1, 104},
		{"Saddle Brown", -1, 98},
		{"Moss Brown", -1, 100},
		{"Woodbeech Brown", -1, 102},
		{"Straw Brown", -1, 99},
		{"Sandy Brown", -1, 105},
		{"Bleached Brown", -1, 106},
		{"Schafter Purple", -1, 71},
		{"Spinnaker Purple", -1, 72},
		{"Midnight Purple", -1, 146},
		{"Bright Purple", -1, 145},
		{"Cream", -1, 107},
		{"Ice White", -1, 111},
		{"Frost White", -1, 112},
		{"Secret Gold", -1, 160}
	};

	struct Struct_Vehicle_Mod_Wheels
	{
		int index;
		const char* name;
		uint32_t sub;
	};

	const std::vector<Struct_Vehicle_Mod_Wheels> VehicleModTypes_Wheels {
		{0 , "Sport", "Player_Vehicle_LosSantosCustom_MOD_WHEELS_SPORT"_joaat},
		{1 , "Muscle", "Player_Vehicle_LosSantosCustom_MOD_WHEELS_MUSCLE"_joaat},
		{2 , "Lowrider", "Player_Vehicle_LosSantosCustom_MOD_WHEELS_LOWRIDER"_joaat},
		{3 , "SUV", "Player_Vehicle_LosSantosCustom_MOD_WHEELS_SUV"_joaat},
		{4 , "Offroad", "Player_Vehicle_LosSantosCustom_MOD_WHEELS_OFFROAD"_joaat},
		{5 , "Tuner", "Player_Vehicle_LosSantosCustom_MOD_WHEELS_TUNER"_joaat},
		{6 , "Bike Wheels", "Player_Vehicle_LosSantosCustom_MOD_WHEELS_BIKE"_joaat},
		{7 , "High End", "Player_Vehicle_LosSantosCustom_MOD_WHEELS_HIGHEND"_joaat},
		{8 , "Benny's Wheels", "Player_Vehicle_LosSantosCustom_MOD_WHEELS_BENNY"_joaat},
		{9 , "Bespoke Wheels", "Player_Vehicle_LosSantosCustom_MOD_WHEELS_BESPOKE"_joaat},
		{10 , "Street Wheels", "Player_Vehicle_LosSantosCustom_MOD_WHEELS_STREET"_joaat},
		{11 , "Track Wheels", "Player_Vehicle_LosSantosCustom_MOD_WHEELS_TRACK"_joaat}
	};

	std::string m_headlights_color[] = {
		"Stock",
		"White",
		"Blue",
		"ElectricBlue",
		"MintGreen",
		"LimeGreen",
		"Yellow",
		"GoldenShower",
		"Orange",
		"Red",
		"PonyPink",
		"HotPink",
		"Purple",
		"Blacklight"
	};
};
namespace insight {
	int paint_type_set = 0;
	int wheel_type_set = 0;
	Vehicle lsc_entity;
	Vehicle last_lsc_entity;
	bool _turbo = false;
	bool _xeon = false;
	int m_headlights_color_selected = 0;
	void get_all_info() {
		if (lsc_entity != globals::h_local_vehicle()) {
			_turbo = VEHICLE::IS_TOGGLE_MOD_ON(lsc_entity, _turbo);
			_xeon = VEHICLE::IS_TOGGLE_MOD_ON(lsc_entity, MOD_XENONLIGHTS);
			if (_xeon) {
				m_headlights_color_selected = VEHICLE::GET_VEHICLE_XENON_LIGHT_COLOR_INDEX(lsc_entity);
			}
			lsc_entity = globals::h_local_vehicle();
		}
	}
	void script_ui::vehiclelsc() {

		render::push<sub>("Customs", "Player_Vehicle_LosSantosCustom"_joaat, [](sub* ui) {
			if (script_utility::get()->lsc_sub == 0) {
				lsc_entity = globals::h_local_vehicle();
			}
			else {
				lsc_entity = globals::get_selected_vehicle();
			}
			if (lsc_entity) {
				NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(lsc_entity);
				VEHICLE::SET_VEHICLE_MOD_KIT(lsc_entity, 0);
				get_all_info();
				ui->push(submenu("Paint").add_target("Player_Vehicle_LosSantosCustom_MOD_PAINT"_joaat));
				ui->push(submenu("Wheels").add_target("Player_Vehicle_LosSantosCustom_MOD_WHEELS"_joaat));
				if (VEHICLE::GET_NUM_VEHICLE_MODS(lsc_entity, MOD_ARMOR) != 0) {
					ui->push(submenu("Armor").add_target("Player_Vehicle_LosSantosCustom_MOD_ARMOR"_joaat));
				}
				if (VEHICLE::GET_NUM_VEHICLE_MODS(lsc_entity, MOD_BRAKES) != 0) {
					ui->push(submenu("Breaks").add_target("Player_Vehicle_LosSantosCustom_MOD_BRAKES"_joaat));
				}
				if (VEHICLE::GET_NUM_VEHICLE_MODS(lsc_entity, MOD_TRANSMISSION) != 0) {
					ui->push(submenu("Trasmission").add_target("Player_Vehicle_LosSantosCustom_MOD_TRANSMISSION"_joaat));
				}
				if (VEHICLE::GET_NUM_VEHICLE_MODS(lsc_entity, MOD_SUSPENSION) != 0) {
					ui->push(submenu("Suspension").add_target("Player_Vehicle_LosSantosCustom_MOD_SUSPENSION"_joaat));
				}
				ui->push(toggle("Turbo").add_toggle(&_turbo).set_action([=] {
					VEHICLE::TOGGLE_VEHICLE_MOD(lsc_entity, MOD_TURBO, _turbo);
					}));
				ui->push(toggle("Xenon").add_toggle(&_xeon).set_action([=] {
					if (_xeon) {
						VEHICLE::SET_VEHICLE_XENON_LIGHT_COLOR_INDEX(lsc_entity, HeadlightColors::Hlc_Stock);
					}
					VEHICLE::TOGGLE_VEHICLE_MOD(lsc_entity, MOD_XENONLIGHTS, _xeon);
					}));
				if (_xeon) {
					ui->push(array<std::string, int>("Headlights Color").add_array(&m_headlights_color).
						add_position(&m_headlights_color_selected).set_use_enter_only(true).set_action([=] {
							VEHICLE::SET_VEHICLE_XENON_LIGHT_COLOR_INDEX(lsc_entity, m_headlights_color_selected);
							}));
				}

				if (VEHICLE::GET_NUM_VEHICLE_MODS(lsc_entity, MOD_HORNS) != 0) {
					ui->push(submenu("Horn").add_target("Player_Vehicle_LosSantosCustom_MOD_HORNS"_joaat));
				}
				ui->push(submenu("Windows").add_target("Player_Vehicle_LosSantosCustom_Windows"_joaat));
				if (VEHICLE::GET_NUM_VEHICLE_MODS(lsc_entity, MOD_SPOILER) != 0) {
					ui->push(submenu("Spoiler").add_target("Player_Vehicle_LosSantosCustom_MOD_SPOILER"_joaat));
				}		
				if (VEHICLE::GET_NUM_VEHICLE_MODS(lsc_entity, MOD_FRONTBUMPER) != 0) {
					ui->push(submenu("Front Bumper").add_target("Player_Vehicle_LosSantosCustom_MOD_FRONTBUMPER"_joaat));
				}			
				if (VEHICLE::GET_NUM_VEHICLE_MODS(lsc_entity, MOD_REARBUMPER) != 0) {
					ui->push(submenu("Rear Bumper").add_target("Player_Vehicle_LosSantosCustom_MOD_REARBUMPER"_joaat));
				}			
				if (VEHICLE::GET_NUM_VEHICLE_MODS(lsc_entity, MOD_SIDESKIRT) != 0) {
					ui->push(submenu("Side Skirts").add_target("Player_Vehicle_LosSantosCustom_MOD_REARBUMPER"_joaat));
				}			
				if (VEHICLE::GET_NUM_VEHICLE_MODS(lsc_entity, MOD_EXHAUST) != 0) {
					ui->push(submenu("Exhaust").add_target("Player_Vehicle_LosSantosCustom_MOD_EXHAUST"_joaat));
				}			
				if (VEHICLE::GET_NUM_VEHICLE_MODS(lsc_entity, MOD_GRILLE) != 0) {
					ui->push(submenu("Grille").add_target("Player_Vehicle_LosSantosCustom_MOD_GRILLE"_joaat));
				}		
				if (VEHICLE::GET_NUM_VEHICLE_MODS(lsc_entity, MOD_CHASSIS) != 0) {
					ui->push(submenu("Roll Cage").add_target("Player_Vehicle_LosSantosCustom_MOD_CHASSIS"_joaat));
				}			
				if (VEHICLE::GET_NUM_VEHICLE_MODS(lsc_entity, MOD_HOOD) != 0) {
					ui->push(submenu("Hood").add_target("Player_Vehicle_LosSantosCustom_MOD_HOOD"_joaat));
				}
				if (VEHICLE::GET_NUM_VEHICLE_MODS(lsc_entity, MOD_FENDER) != 0) {
					ui->push(submenu("Fender").add_target("Player_Vehicle_LosSantosCustom_MOD_FENDER"_joaat));
				}			
				if (VEHICLE::GET_NUM_VEHICLE_MODS(lsc_entity, MOD_RIGHTFENDER) != 0) {
					ui->push(submenu("Right Fender").add_target("Player_Vehicle_LosSantosCustom_MOD_RIGHTFENDER"_joaat));
				}		
				if (VEHICLE::GET_NUM_VEHICLE_MODS(lsc_entity, MOD_ROOF) != 0) {
					ui->push(submenu("Roof").add_target("Player_Vehicle_LosSantosCustom_MOD_ROOF"_joaat));
				}				
				if (VEHICLE::GET_NUM_VEHICLE_MODS(lsc_entity, MOD_LIVERY) != 0) {
					ui->push(submenu("Livery").add_target("Player_Vehicle_LosSantosCustom_MOD_LIVERY"_joaat));
				}
				ui->push(submenu("Doors").add_target("Player_Vehicle_Doors"_joaat).set_action([=] {
					script_utility::get()->Player_Vehicle_Doors_Entity = lsc_entity;
					script_utility::get()->doors_locked = VEHICLE::GET_VEHICLE_DOORS_LOCKED_FOR_PLAYER(script_utility::get()->Player_Vehicle_Doors_Entity, globals::player_id);
					}));
				ui->push(number<float>("lsc_vehicle_top_speed"_FF->m_name).add_number(&"lsc_vehicle_top_speed"_FF->m_value.floating_point).
					add_min(-5000).add_max(5000).add_precision(1).add_step(10.f).add_description("lsc_vehicle_top_speed"_FF->m_description).
					set_action([=] {
						if (tasks::request_control(lsc_entity)) {
							VEHICLE::MODIFY_VEHICLE_TOP_SPEED(lsc_entity, "lsc_vehicle_top_speed"_FF->m_value.floating_point);
						}}));		
				
				ui->push(number<float>("lsc_vehicle_max_speed"_FF->m_name).add_number(&"lsc_vehicle_max_speed"_FF->m_value.floating_point).
					add_min(-5000).add_max(5000).add_precision(1).add_step(10.f).add_description("lsc_vehicle_max_speed"_FF->m_description).
					set_action([=] {
						if (tasks::request_control(lsc_entity)) {
							ENTITY::SET_ENTITY_MAX_SPEED(lsc_entity, "lsc_vehicle_max_speed"_FF->m_value.floating_point);
						}}));
			}
			});
		render::push<sub>("Paint", "Player_Vehicle_LosSantosCustom_MOD_PAINT"_joaat, [](sub* ui) {
			ui->push(submenu("Primary").add_target("Player_Vehicle_LosSantosCustom_MOD_PAINT_Type"_joaat).set_action([=] {
				paint_type_set = 0;
				}));
			ui->push(submenu("Secondary").add_target("Player_Vehicle_LosSantosCustom_MOD_PAINT_Type"_joaat).set_action([=] {
				paint_type_set = 1;
				}));

			});		
		render::push<sub>(paint_type_set == 0 ? "Primary" : "Secondary", "Player_Vehicle_LosSantosCustom_MOD_PAINT_Type"_joaat, [](sub* ui) {

			ui->push(button("Chrome")
				.set_action([=] {
					int Primary_Paint, Sec_Paint;
					VEHICLE::GET_VEHICLE_COLOURS(lsc_entity, &Primary_Paint, &Sec_Paint);
					if (paint_type_set == 0)
					{
						if (tasks::request_control(lsc_entity))
						VEHICLE::SET_VEHICLE_COLOURS(lsc_entity, 120, Sec_Paint);

					}
					else if (paint_type_set == 1)
					{
						if (tasks::request_control(lsc_entity))
						VEHICLE::SET_VEHICLE_COLOURS(lsc_entity, Primary_Paint, 120);
					}				
					}));
			ui->push(submenu("Metallic").add_target("Player_Vehicle_LosSantosCustom_MOD_PAINT_Type_Mettalic"_joaat));
			ui->push(submenu("Matte").add_target("Player_Vehicle_LosSantosCustom_MOD_PAINT_Type_Matte"_joaat));
			ui->push(submenu("Metals").add_target("Player_Vehicle_LosSantosCustom_MOD_PAINT_Type_Metals"_joaat));
			ui->push(submenu("Pearlescent").add_target("Player_Vehicle_LosSantosCustom_MOD_PAINT_Type_Pearlescents"_joaat));
			});
		render::push<sub>("Metallic", "Player_Vehicle_LosSantosCustom_MOD_PAINT_Type_Mettalic"_joaat, [](sub* ui) {
			for (std::uint32_t i = 0; i < PAINTS_CAR_NORMAL_MATTELIC.size(); ++i)
			{
				ui->push(button(PAINTS_CAR_NORMAL_MATTELIC[i].Paintname)
					.set_action([=] {
						int Primary_Paint, Sec_Paint;
						VEHICLE::GET_VEHICLE_COLOURS(lsc_entity, &Primary_Paint, &Sec_Paint);

						if (paint_type_set == 0)
						{
							if (tasks::request_control(lsc_entity))
							VEHICLE::SET_VEHICLE_COLOURS(lsc_entity, PAINTS_CAR_NORMAL_MATTELIC[i].Paintvalue, Sec_Paint);
							//	VEHICLE::GET_VEHICLE_CUSTOM_SECONDARY_COLOUR(lsc_entity, &VEHICLE_CUSTOM_C_R, &VEHICLE_CUSTOM_C_G, &VEHICLE_CUSTOM_C_B);
						}
						else if (paint_type_set == 1)
						{
							if (tasks::request_control(lsc_entity))
							VEHICLE::SET_VEHICLE_COLOURS(lsc_entity, Primary_Paint, PAINTS_CAR_NORMAL_MATTELIC[i].Paintvalue);
							//	VEHICLE::GET_VEHICLE_CUSTOM_PRIMARY_COLOUR(lsc_entity, &VEHICLE_CUSTOM_C_R, &VEHICLE_CUSTOM_C_G, &VEHICLE_CUSTOM_C_B);
						}
						}));
			}
			});	
		render::push<sub>("Matte", "Player_Vehicle_LosSantosCustom_MOD_PAINT_Type_Matte"_joaat, [](sub* ui) {
			for (std::uint32_t i = 0; i < PAINTS_CAR_MATTE.size(); ++i)
			{
				ui->push(button(PAINTS_CAR_MATTE[i].Paintname)
					.set_action([=] {
						int Primary_Paint, Sec_Paint;
						VEHICLE::GET_VEHICLE_COLOURS(lsc_entity, &Primary_Paint, &Sec_Paint);

						if (paint_type_set == 0)
						{

							VEHICLE::SET_VEHICLE_COLOURS(lsc_entity, PAINTS_CAR_MATTE[i].Paintvalue, Sec_Paint);
							//	VEHICLE::GET_VEHICLE_CUSTOM_SECONDARY_COLOUR(lsc_entity, &VEHICLE_CUSTOM_C_R, &VEHICLE_CUSTOM_C_G, &VEHICLE_CUSTOM_C_B);
						}
						else if (paint_type_set == 1)
						{
							VEHICLE::SET_VEHICLE_COLOURS(lsc_entity, Primary_Paint, PAINTS_CAR_MATTE[i].Paintvalue);
							//	VEHICLE::GET_VEHICLE_CUSTOM_PRIMARY_COLOUR(lsc_entity, &VEHICLE_CUSTOM_C_R, &VEHICLE_CUSTOM_C_G, &VEHICLE_CUSTOM_C_B);
						}
						}));
			}
			});
		render::push<sub>("Metal", "Player_Vehicle_LosSantosCustom_MOD_PAINT_Type_Metals"_joaat, [](sub* ui) {
			for (std::uint32_t i = 0; i < PAINTS_CAR_METAL.size(); ++i)
			{
				ui->push(button(PAINTS_CAR_METAL[i].Paintname)
					.set_action([=] {
						int Primary_Paint, Sec_Paint;
						VEHICLE::GET_VEHICLE_COLOURS(lsc_entity, &Primary_Paint, &Sec_Paint);

						if (paint_type_set == 0)
						{

							VEHICLE::SET_VEHICLE_COLOURS(lsc_entity, PAINTS_CAR_METAL[i].Paintvalue, Sec_Paint);
							//	VEHICLE::GET_VEHICLE_CUSTOM_SECONDARY_COLOUR(lsc_entity, &VEHICLE_CUSTOM_C_R, &VEHICLE_CUSTOM_C_G, &VEHICLE_CUSTOM_C_B);
						}
						else if (paint_type_set == 1)
						{
							VEHICLE::SET_VEHICLE_COLOURS(lsc_entity, Primary_Paint, PAINTS_CAR_METAL[i].Paintvalue);
							//	VEHICLE::GET_VEHICLE_CUSTOM_PRIMARY_COLOUR(lsc_entity, &VEHICLE_CUSTOM_C_R, &VEHICLE_CUSTOM_C_G, &VEHICLE_CUSTOM_C_B);
						}
						}));
			}
			});
		render::push<sub>("Pearlecent", "Player_Vehicle_LosSantosCustom_MOD_PAINT_Type_Pearlescents"_joaat, [](sub* ui) {
			for (std::uint32_t i = 0; i < PAINTS_CAR_PEARLESCENT.size(); ++i)
			{
				ui->push(button(PAINTS_CAR_PEARLESCENT[i].Paintname)
					.set_action([=] {
						int Primary_Paint, Sec_Paint;
						VEHICLE::GET_VEHICLE_COLOURS(lsc_entity, &Primary_Paint, &Sec_Paint);
						int Pearlescent_Color, Pearlescent_Wheel;
						VEHICLE::GET_VEHICLE_EXTRA_COLOURS(lsc_entity, &Pearlescent_Color, &Pearlescent_Wheel);

						if (paint_type_set == 0 || paint_type_set == 2)
						{
							if (tasks::request_control(lsc_entity))
							VEHICLE::SET_VEHICLE_EXTRA_COLOURS(lsc_entity, PAINTS_CAR_PEARLESCENT[i].Pearlescentvalue, Pearlescent_Wheel); //sameshit for sec
						}
						}));
			}
			});
		render::push<sub>("Wheels", "Player_Vehicle_LosSantosCustom_MOD_WHEELS"_joaat, [](sub* ui) {
			for (int i = 0; i < VehicleModTypes_Wheels.size(); ++i)
			{
				ui->push(submenu(VehicleModTypes_Wheels[i].name).add_target(VehicleModTypes_Wheels[i].sub).set_action([=] {
					wheel_type_set = i;
					if (tasks::request_control(lsc_entity))
					VEHICLE::SET_VEHICLE_WHEEL_TYPE(lsc_entity, i);
					}));
			}

			});
		for (int i = 0; i < VehicleModTypes_Wheels.size(); ++i)
		{
			render::push<sub>(VehicleModTypes_Wheels[i].name, VehicleModTypes_Wheels[i].sub, [](sub* ui) {
				for (int i = 0; i < VEHICLE::GET_NUM_VEHICLE_MODS(lsc_entity, MOD_FRONTWHEELS) + 1; ++i)
				{
					int THIS_CAR_HAS = VEHICLE::GET_VEHICLE_MOD(lsc_entity, MOD_FRONTWHEELS) + 1;
					bool has_this_mod = i == THIS_CAR_HAS;
					ui->push(button(has_this_mod ? std::string(std::string("~r~") + HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(VEHICLE::GET_MOD_TEXT_LABEL(lsc_entity, MOD_FRONTWHEELS, i - 1))) :
						std::string(HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(VEHICLE::GET_MOD_TEXT_LABEL(lsc_entity, MOD_FRONTWHEELS, i - 1))))
						.set_action([=] {
							if (tasks::request_control(lsc_entity))
							VEHICLE::SET_VEHICLE_MOD(lsc_entity, MOD_FRONTWHEELS, i - 1, false);
							}));
				}
				});
		}	
		render::push<sub>("Armor", "Player_Vehicle_LosSantosCustom_MOD_ARMOR"_joaat, [](sub* ui) {
			for (int i = 0; i < VEHICLE::GET_NUM_VEHICLE_MODS(lsc_entity, MOD_ARMOR) + 1; ++i)
			{
				int THIS_CAR_HAS = VEHICLE::GET_VEHICLE_MOD(lsc_entity, MOD_ARMOR) + 1;
				bool has_this_mod = i == THIS_CAR_HAS;
				ui->push(button(has_this_mod ? std::string(std::string("~r~") + HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(VehicleModTypes_Armor_Lebel[i].lebel)) :
					HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(VehicleModTypes_Armor_Lebel[i].lebel))
					.set_action([=] {
						VEHICLE::SET_VEHICLE_MOD(lsc_entity, MOD_ARMOR, i - 1, false);
						}));

			}
			});
		render::push<sub>("Breaks", "Player_Vehicle_LosSantosCustom_MOD_BRAKES"_joaat, [](sub* ui) {
			for (int i = 0; i < VEHICLE::GET_NUM_VEHICLE_MODS(lsc_entity, MOD_BRAKES) + 1; ++i)
			{
				int THIS_CAR_HAS = VEHICLE::GET_VEHICLE_MOD(lsc_entity, MOD_BRAKES) + 1;
				bool has_this_mod = i == THIS_CAR_HAS;
				ui->push(button(has_this_mod ? std::string(std::string("~r~") + HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(VehicleModTypes_Brakes_Lebel[i].lebel) ) :
					HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(VehicleModTypes_Brakes_Lebel[i].lebel))
					.set_action([=] {
						if (tasks::request_control(lsc_entity))
						VEHICLE::SET_VEHICLE_MOD(lsc_entity, MOD_BRAKES, i - 1, false);
						}));

			}
			});
		render::push<sub>("Trasmission", "Player_Vehicle_LosSantosCustom_MOD_TRANSMISSION"_joaat, [](sub* ui) {
			for (int i = 0; i < VEHICLE::GET_NUM_VEHICLE_MODS(lsc_entity, MOD_TRANSMISSION) + 1; ++i)
			{
				int THIS_CAR_HAS = VEHICLE::GET_VEHICLE_MOD(lsc_entity, MOD_TRANSMISSION) + 1;
				bool has_this_mod = i == THIS_CAR_HAS;
				ui->push(button(has_this_mod ? std::string(std::string("~r~") + HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(VehicleModTypes_Transmission_Lebel[i].lebel) ) :
					HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(VehicleModTypes_Transmission_Lebel[i].lebel))
					.set_action([=] {
						if (tasks::request_control(lsc_entity))
						VEHICLE::SET_VEHICLE_MOD(lsc_entity, MOD_TRANSMISSION, i - 1, false);
						}));
			}
			});
		render::push<sub>("Suspension", "Player_Vehicle_LosSantosCustom_MOD_SUSPENSION"_joaat, [](sub* ui) {
			for (int i = 0; i < VEHICLE::GET_NUM_VEHICLE_MODS(lsc_entity, MOD_SUSPENSION) + 1; ++i)
			{
				int THIS_CAR_HAS = VEHICLE::GET_VEHICLE_MOD(lsc_entity, MOD_SUSPENSION) + 1;
				bool has_this_mod = i == THIS_CAR_HAS;
				ui->push(button(has_this_mod ? std::string(std::string("~r~") + HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(VehicleModTypes_Transmission_Lebel[i].lebel) ) :
					HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(VehicleModTypes_Transmission_Lebel[i].lebel))
					.set_action([=] {
						if (tasks::request_control(lsc_entity))
						VEHICLE::SET_VEHICLE_MOD(lsc_entity, MOD_SUSPENSION, i - 1, false);
						}));
			}
			});

		render::push<sub>("Horn", "Player_Vehicle_LosSantosCustom_MOD_HORNS"_joaat, [](sub* ui) {
			for (int i = 0; i < VEHICLE::GET_NUM_VEHICLE_MODS(lsc_entity, MOD_HORNS) + 1; ++i)
			{
				int THIS_CAR_HAS = VEHICLE::GET_VEHICLE_MOD(lsc_entity, MOD_HORNS) + 1;
				bool has_this_mod = i == THIS_CAR_HAS;
				ui->push(button(has_this_mod ? std::string(std::string("~r~") + VehicleModTypes_Horn_Lebel[i].def ) :
					VehicleModTypes_Horn_Lebel[i].def)
					.set_action([=] {
						if (tasks::request_control(lsc_entity))
						VEHICLE::SET_VEHICLE_MOD(lsc_entity, MOD_HORNS, i - 1, false);
						}));
			}
			});
		render::push<sub>("Windows", "Player_Vehicle_LosSantosCustom_Windows"_joaat, [](sub* ui) {
			for (int i = 0; i < VEHICLE::GET_NUM_VEHICLE_WINDOW_TINTS() + 1; ++i)
			{
				int THIS_CAR_HAS = VEHICLE::GET_VEHICLE_WINDOW_TINT(lsc_entity) + 1;
				bool has_this_mod = i == THIS_CAR_HAS;
				ui->push(button(has_this_mod ? std::string(std::string("~r~") + VehicleModTypes_Windows_Lebel[i].def ) :
					VehicleModTypes_Windows_Lebel[i].def)
					.set_action([=] {
						if (tasks::request_control(lsc_entity))
						VEHICLE::SET_VEHICLE_WINDOW_TINT(lsc_entity, i - 1);
						}));
			}
			});
		render::push<sub>("Spoiler", "Player_Vehicle_LosSantosCustom_MOD_SPOILER"_joaat, [](sub* ui) {
			for (int i = 0; i < VEHICLE::GET_NUM_VEHICLE_MODS(lsc_entity, MOD_SPOILER) + 1; ++i)
			{
				int THIS_CAR_HAS = VEHICLE::GET_VEHICLE_MOD(lsc_entity, MOD_SPOILER) + 1;
				bool has_this_mod = i == THIS_CAR_HAS;
				ui->push(button(has_this_mod ? std::string(std::string("~r~") + HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(VEHICLE::GET_MOD_TEXT_LABEL(lsc_entity, MOD_SPOILER, i - 1)) ) :
					std::string(HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(VEHICLE::GET_MOD_TEXT_LABEL(lsc_entity, MOD_SPOILER, i - 1))))
					.set_action([=] {
						if (tasks::request_control(lsc_entity))
						VEHICLE::SET_VEHICLE_MOD(lsc_entity, MOD_SPOILER, i - 1, false);
						}));
			}
			});
		render::push<sub>("Front Bumper", "Player_Vehicle_LosSantosCustom_MOD_FRONTBUMPER"_joaat, [](sub* ui) {
			for (int i = 0; i < VEHICLE::GET_NUM_VEHICLE_MODS(lsc_entity, MOD_FRONTBUMPER) + 1; ++i)
			{
				int THIS_CAR_HAS = VEHICLE::GET_VEHICLE_MOD(lsc_entity, MOD_FRONTBUMPER) + 1;
				bool has_this_mod = i == THIS_CAR_HAS;
				ui->push(button(has_this_mod ? std::string(std::string("~r~") + HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(VEHICLE::GET_MOD_TEXT_LABEL(lsc_entity, MOD_FRONTBUMPER, i - 1)) ) :
					std::string(HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(VEHICLE::GET_MOD_TEXT_LABEL(lsc_entity, MOD_FRONTBUMPER, i - 1))))
					.set_action([=] {
						if (tasks::request_control(lsc_entity))
						VEHICLE::SET_VEHICLE_MOD(lsc_entity, MOD_FRONTBUMPER, i - 1, false);
						}));
			}
			});
		render::push<sub>("Rear Bumper", "Player_Vehicle_LosSantosCustom_MOD_REARBUMPER"_joaat, [](sub* ui) {
			for (int i = 0; i < VEHICLE::GET_NUM_VEHICLE_MODS(lsc_entity, MOD_REARBUMPER) + 1; ++i)
			{
				int THIS_CAR_HAS = VEHICLE::GET_VEHICLE_MOD(lsc_entity, MOD_REARBUMPER) + 1;
				bool has_this_mod = i == THIS_CAR_HAS;
				ui->push(button(has_this_mod ? std::string(std::string("~r~") + HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(VEHICLE::GET_MOD_TEXT_LABEL(lsc_entity, MOD_REARBUMPER, i - 1)) ) :
					std::string(HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(VEHICLE::GET_MOD_TEXT_LABEL(lsc_entity, MOD_REARBUMPER, i - 1))))
					.set_action([=] {
						if (tasks::request_control(lsc_entity))
						VEHICLE::SET_VEHICLE_MOD(lsc_entity, MOD_REARBUMPER, i - 1, false);
						}));
			}
			});	
		render::push<sub>("Side Skirts", "Player_Vehicle_LosSantosCustom_MOD_SIDESKIRT"_joaat, [](sub* ui) {
			for (int i = 0; i < VEHICLE::GET_NUM_VEHICLE_MODS(lsc_entity, MOD_SIDESKIRT) + 1; ++i)
			{
				int THIS_CAR_HAS = VEHICLE::GET_VEHICLE_MOD(lsc_entity, MOD_SIDESKIRT) + 1;
				bool has_this_mod = i == THIS_CAR_HAS;
				ui->push(button(has_this_mod ? std::string(std::string("~r~") + HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(VEHICLE::GET_MOD_TEXT_LABEL(lsc_entity, MOD_SIDESKIRT, i - 1)) ) :
					std::string(HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(VEHICLE::GET_MOD_TEXT_LABEL(lsc_entity, MOD_SIDESKIRT, i - 1))))
					.set_action([=] {
						if (tasks::request_control(lsc_entity))
						VEHICLE::SET_VEHICLE_MOD(lsc_entity, MOD_SIDESKIRT, i - 1, false);
						}));
			}
			});
		render::push<sub>("Exhausts", "Player_Vehicle_LosSantosCustom_MOD_EXHAUST"_joaat, [](sub* ui) {
			for (int i = 0; i < VEHICLE::GET_NUM_VEHICLE_MODS(lsc_entity, MOD_EXHAUST) + 1; ++i)
			{
				int THIS_CAR_HAS = VEHICLE::GET_VEHICLE_MOD(lsc_entity, MOD_EXHAUST) + 1;
				bool has_this_mod = i == THIS_CAR_HAS;
				ui->push(button(has_this_mod ? std::string(std::string("~r~") + HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(VEHICLE::GET_MOD_TEXT_LABEL(lsc_entity, MOD_EXHAUST, i - 1)) ) :
					std::string(HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(VEHICLE::GET_MOD_TEXT_LABEL(lsc_entity, MOD_EXHAUST, i - 1))))
					.set_action([=] {
						if (tasks::request_control(lsc_entity))
						VEHICLE::SET_VEHICLE_MOD(lsc_entity, MOD_EXHAUST, i - 1, false);
						}));
			}
			});
		render::push<sub>("Grille", "Player_Vehicle_LosSantosCustom_MOD_GRILLE"_joaat, [](sub* ui) {
			for (int i = 0; i < VEHICLE::GET_NUM_VEHICLE_MODS(lsc_entity, MOD_GRILLE) + 1; ++i)
			{
				int THIS_CAR_HAS = VEHICLE::GET_VEHICLE_MOD(lsc_entity, MOD_GRILLE) + 1;
				bool has_this_mod = i == THIS_CAR_HAS;
				ui->push(button(has_this_mod ? std::string(std::string("~r~") + HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(VEHICLE::GET_MOD_TEXT_LABEL(lsc_entity, MOD_GRILLE, i - 1)) ) :
					std::string(HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(VEHICLE::GET_MOD_TEXT_LABEL(lsc_entity, MOD_GRILLE, i - 1))))
					.set_action([=] {
						if (tasks::request_control(lsc_entity))
						VEHICLE::SET_VEHICLE_MOD(lsc_entity, MOD_GRILLE, i - 1, false);
						}));
			}
			});
		render::push<sub>("Roll Cage", "Player_Vehicle_LosSantosCustom_MOD_CHASSIS"_joaat, [](sub* ui) {
			for (int i = 0; i < VEHICLE::GET_NUM_VEHICLE_MODS(lsc_entity, MOD_CHASSIS) + 1; ++i)
			{
				int THIS_CAR_HAS = VEHICLE::GET_VEHICLE_MOD(lsc_entity, MOD_CHASSIS) + 1;
				bool has_this_mod = i == THIS_CAR_HAS;
				ui->push(button(has_this_mod ? std::string(std::string("~r~") + HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(VEHICLE::GET_MOD_TEXT_LABEL(lsc_entity, MOD_CHASSIS, i - 1)) ) :
					std::string(HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(VEHICLE::GET_MOD_TEXT_LABEL(lsc_entity, MOD_CHASSIS, i - 1))))
					.set_action([=] {
						if (tasks::request_control(lsc_entity))
						VEHICLE::SET_VEHICLE_MOD(lsc_entity, MOD_CHASSIS, i - 1, false);
						}));
			}
			});
		render::push<sub>("Hood", "Player_Vehicle_LosSantosCustom_MOD_HOOD"_joaat, [](sub* ui) {
			for (int i = 0; i < VEHICLE::GET_NUM_VEHICLE_MODS(lsc_entity, MOD_HOOD) + 1; ++i)
			{
				int THIS_CAR_HAS = VEHICLE::GET_VEHICLE_MOD(lsc_entity, MOD_HOOD) + 1;
				bool has_this_mod = i == THIS_CAR_HAS;
				ui->push(button(has_this_mod ? std::string(std::string("~r~") + HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(VEHICLE::GET_MOD_TEXT_LABEL(lsc_entity, MOD_HOOD, i - 1)) ) :
					std::string(HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(VEHICLE::GET_MOD_TEXT_LABEL(lsc_entity, MOD_HOOD, i - 1))))
					.set_action([=] {
						if (tasks::request_control(lsc_entity))
						VEHICLE::SET_VEHICLE_MOD(lsc_entity, MOD_HOOD, i - 1, false);
						}));
			}
			});
		render::push<sub>("Fender", "Player_Vehicle_LosSantosCustom_MOD_FENDER"_joaat, [](sub* ui) {
			for (int i = 0; i < VEHICLE::GET_NUM_VEHICLE_MODS(lsc_entity, MOD_FENDER) + 1; ++i)
			{
				int THIS_CAR_HAS = VEHICLE::GET_VEHICLE_MOD(lsc_entity, MOD_FENDER) + 1;
				bool has_this_mod = i == THIS_CAR_HAS;
				ui->push(button(has_this_mod ? std::string(std::string("~r~") + HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(VEHICLE::GET_MOD_TEXT_LABEL(lsc_entity, MOD_FENDER, i - 1)) ) :
					std::string(HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(VEHICLE::GET_MOD_TEXT_LABEL(lsc_entity, MOD_FENDER, i - 1))))
					.set_action([=] {
						if (tasks::request_control(lsc_entity))
						VEHICLE::SET_VEHICLE_MOD(lsc_entity, MOD_FENDER, i - 1, false);
						}));
			}
			});
		render::push<sub>("R Fender", "Player_Vehicle_LosSantosCustom_MOD_RIGHTFENDER"_joaat, [](sub* ui) {
			for (int i = 0; i < VEHICLE::GET_NUM_VEHICLE_MODS(lsc_entity, MOD_RIGHTFENDER) + 1; ++i)
			{
				int THIS_CAR_HAS = VEHICLE::GET_VEHICLE_MOD(lsc_entity, MOD_RIGHTFENDER) + 1;
				bool has_this_mod = i == THIS_CAR_HAS;
				ui->push(button(has_this_mod ? std::string(std::string("~r~") + HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(VEHICLE::GET_MOD_TEXT_LABEL(lsc_entity, MOD_RIGHTFENDER, i - 1)) ) :
					std::string(HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(VEHICLE::GET_MOD_TEXT_LABEL(lsc_entity, MOD_RIGHTFENDER, i - 1))))
					.set_action([=] {
						if (tasks::request_control(lsc_entity))
						VEHICLE::SET_VEHICLE_MOD(lsc_entity, MOD_RIGHTFENDER, i - 1, false);
						}));
			}
			});
		render::push<sub>("Roof", "Player_Vehicle_LosSantosCustom_MOD_ROOF"_joaat, [](sub* ui) {
			for (int i = 0; i < VEHICLE::GET_NUM_VEHICLE_MODS(lsc_entity, MOD_ROOF) + 1; ++i)
			{
				int THIS_CAR_HAS = VEHICLE::GET_VEHICLE_MOD(lsc_entity, MOD_ROOF) + 1;
				bool has_this_mod = i == THIS_CAR_HAS;
				ui->push(button(has_this_mod ? std::string(std::string("~r~") + HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(VEHICLE::GET_MOD_TEXT_LABEL(lsc_entity, MOD_ROOF, i - 1)) ) :
					std::string(HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(VEHICLE::GET_MOD_TEXT_LABEL(lsc_entity, MOD_ROOF, i - 1))))
					.set_action([=] {
						if (tasks::request_control(lsc_entity))
						VEHICLE::SET_VEHICLE_MOD(lsc_entity, MOD_ROOF, i - 1, false);
						}));
			}
			});
		render::push<sub>("Livery", "Player_Vehicle_LosSantosCustom_MOD_LIVERY"_joaat, [](sub* ui) {
			for (int i = 0; i < VEHICLE::GET_NUM_VEHICLE_MODS(lsc_entity, MOD_LIVERY) + 1; ++i)
			{
				int THIS_CAR_HAS = VEHICLE::GET_VEHICLE_MOD(lsc_entity, MOD_LIVERY) + 1;
				bool has_this_mod = i == THIS_CAR_HAS;
				ui->push(button(has_this_mod ? std::string(std::string("~r~") + HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(VEHICLE::GET_MOD_TEXT_LABEL(lsc_entity, MOD_LIVERY, i - 1)) ) :
					std::string(HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(VEHICLE::GET_MOD_TEXT_LABEL(lsc_entity, MOD_LIVERY, i - 1))))
					.set_action([=] {
						if (tasks::request_control(lsc_entity))
						VEHICLE::SET_VEHICLE_MOD(lsc_entity, MOD_LIVERY, i - 1, false);
						}));
			}
			});

	}
}