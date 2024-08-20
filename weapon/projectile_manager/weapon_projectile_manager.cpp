#pragma once

#include "cheat/features/features/features_utility.hpp"
#include "cheat/script/script.hpp"
#include "cheat/menu/helper/ui.hpp"
#include "util/panels/panels.hpp"
#include "util/config/config.hpp"
#include "cheat/features/globals.hpp"
#include "util/math/math.hpp"

#include "cheat/features/features/features_utility.hpp"
//fuck its gonna be slaves work. :(((((((((((((((
namespace insight {
	std::string m_explosionTags[] = {
	"Grenade",
	"Grenade Launcher",
	"Sticky Bomb",
	"Molotov",
	"Rocket",
	"Tank Shell",
	"Hi Octane",
	"Car",
	"Plane",
	"Petrol Pump",
	"Bike",
	"Steam",
	"Flame",
	"Water Hydrant",
	"Gas Canister",
	"Boat",
	"Ship Destroy",
	"Truck",
	"Bullet",
	"Smoke Grenade Launcher",
	"Smoke Grenade",
	"BZ Gas",
	"Flare",
	"Gas Canister",
	"Extinguisher",
	"0x988620B8",
	"Train",
	"Barrel",
	"Propane",
	"Blimp",
	"Dir Flame Explode",
	"Tanker",
	"Plane Rocket",
	"Vehicle Bullet",
	"Gas Tank",
	"Bird Crap",
	"Railgun",
	"Blimp2",
	"Firework",
	"Snowball",
	"Prox Mine",
	"Valkyrie Cannon",
	"Air Defence",
	"Pipe Bomb",
	"Vehicle Mine",
	"Explosive Ammo",
	"APC Shell",
	"Bomb Cluster",
	"Bomb Gas",
	"Bomb Incendiary",
	"Bomb Standard",
	"Torpedo",
	"Torpedo Underwater",
	"Bombushka Cannon",
	"Bomb Cluster Secondary",
	"Hunter Barrage",
	"Hunter Cannon",
	"Rogue Cannon",
	"Mine Underwater",
	"Orbital Cannon",
	"Bomb Standard Wide",
	"Explosive Ammo Shotgun",
	"Oppressor2 Cannon",
	"Mortar Kinetic",
	"Vehicle Mine Kinetic",
	"Vehicle Mine EMP",
	"Vehicle Mine Spike",
	"Vehicle Mine Slick",
	"Vehicle Mine Tar",
	"Script Drone",
	"Raygun",
	"Buried Mine",
	"Script Missile",
	"RCTank Rocket",
	"Bomb Water",
	"Bomb Water Secondary",
	"0xF728C4A9",
	"0xBAEC056F",
	"Flash Grenade",
	"Stun Grenade",
	"0x763D3B3B",
	"Script Missile Large",
	"Submarine Big"
	};

	int Weapons_Mods_Projectile_Manager_Sub = 0;
};
namespace insight {
	void script_ui::weapon_projectile_manager() {
		render::push<sub>("Special", "Weapons_Mods_Projectile_Manager"_joaat, [](sub* ui) {
			ui::push()->array_feature_toggle(ui, "weapon_projectile_grenade"_tif, m_explosionTags, 83);
			ui::push()->array_feature_toggle(ui, "weapon_projectile_molotov"_tif, m_explosionTags, 83);
			ui::push()->feature_toggle(ui, "weapon_halloween_special_bomb"_tf);

			});


	}
}