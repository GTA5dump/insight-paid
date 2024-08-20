#include "../manager/manager.h"

namespace insight {
	extern void null_feature_toggle(toggle_feature* feature, bool& value);
	extern void null_feature_float(float_feature* feature, float& value);
	extern void null_feature_int_toggle(toggle_int_feature* feature, bool& value, int& value2);
	extern  void null_feature_float_toggle(toggle_float_feature* feature, bool& value, float& value2);

	extern void null_feature_u64(u64_feature* feature, u64& value);
	extern void null_feature_int(int_feature* feature, int& value);

	class weapon {
		static void aimbot(toggle_int_feature* feature, bool& value, int& value2);
		static void explosion_impact(toggle_int_feature* feature, bool& value, int& value2);
		static void particle_impact(toggle_int_feature* feature, bool& value, int& value2);
		static void money_gun(toggle_int_feature* feature, bool& value, int& value2);
		static void airstrike_gun(toggle_int_feature* feature, bool& value, int& value2);
		static void drive_it_gun(toggle_feature* feature, bool& value);
		static void delete_gun(toggle_feature* feature, bool& value);
		static void rope_gun(toggle_feature* feature, bool& value);
		static void paint_gun(toggle_float_feature* feature, bool& value, float& value2);
		static void force_gun(toggle_float_feature* feature, bool& value, float& value2);
		static void gravity_gun(toggle_int_feature* feature, bool& value, int& value2);
		static void nuke_gun(toggle_int_feature* feature, bool& value, int& value2);
		static void rapidfire(toggle_feature* feature, bool& value);
		static void halloween_special_ball(toggle_feature* feature, bool& value);
		static void missle_launcher(toggle_feature* feature, bool& value);
		static void infammo(toggle_feature* feature, bool& value);
		static void noreload(toggle_int_feature* feature, bool& value, int& value2);
		static void triggerbot(toggle_feature* feature, bool& value);
		static void superpunch(toggle_feature* feature, bool& value);
		static void teleport_gun(toggle_int_feature* feature, bool& value, int& value2);
		static void projectile_gun(toggle_int_feature* feature, bool& value, int& value2);
		static void aimed_explosive(toggle_feature* feature, bool& value);
		static void dead_eye(toggle_feature* feature, bool& value);
		static void shotgun_mode(toggle_feature* feature, bool& value);
		static void flame_thrower(toggle_feature* feature, bool& value);
		static void destroy_ped(toggle_feature* feature, bool& value);
		static void shrink_ray(toggle_feature* feature, bool& value);
		static void revive_gun(toggle_feature* feature, bool& value);
		//static void missle_gun(toggle_feature* feature, bool& value);
		static void dubstep_gun(toggle_feature* feature, bool& value);
		static void flaming_ammo(toggle_feature* feature, bool& value);
		static void instrumentofdeath(toggle_int_feature* feature, bool& value, int& value2);
		static void laser_sight(toggle_feature* feature, bool& value);
		static void no_recoil(toggle_feature* feature, bool& value);
		static void inf_range(toggle_feature* feature, bool& value);
		static void wep_damage(toggle_float_feature* feature, bool& value, float& value2);
		static void explosive_fist(toggle_feature* feature, bool& value);
		static void explosive_ammo(toggle_feature* feature, bool& value);
		static void fire_ammo(toggle_feature* feature, bool& value);

		static void blackhole_gun(toggle_int_feature* feature, bool& value, int& value2);
		static void tornado_gun(toggle_int_feature* feature, bool& value, int& value2);

		static void projectile_grenade(toggle_int_feature* feature, bool& value, int& value2);
		static void projectile_molotov(toggle_int_feature* feature, bool& value, int& value2);

		static void bullet_tracers(toggle_feature* feature, bool& value);
		static void round_force_gun(toggle_feature* feature, bool& value);
		static void weapon_axe(toggle_float_feature* feature, bool& value, float& value2);
		static void weapon_width(toggle_float_feature* feature, bool& value, float& value2);
		static void weapon_height(toggle_float_feature* feature, bool& value, float& value2);
		static void weapon_height_width(toggle_float_feature* feature, bool& value, float& value2);
		static void upgrade_weapons_on_session_join(toggle_feature* feature, bool& value);
		static void give_weapons_on_session_join(toggle_feature* feature, bool& value);
	public:
		static weapon* get() {
			static weapon i{};
			return &i;
		}
	public:
		static void set_values() {
			"weapon_aimbot_fov"_FF->m_value.floating_point = 20.f;
			"weapon_aimbot_distance"_FF->m_value.floating_point = 1000.f;
			"weapon_aimbot_shoot_delay"_if->m_value.integer = 100;
			"weapon_impact_airstrike_speed"_FF->m_value.floating_point = 1000.f;
			"weapon_impact_paint"_tif->m_number_value.integer = 1030;
			"weapon_impact_paint"_tif->m_number_value.floating_point = 2.0f;
			"weapon_laxe"_tif->m_number_value.floating_point = 1.0f;

			"weapon_gravity_gun_fx"_tf->m_value.toggle = true;
			"weapon_gravity_gun_distance"_FF->m_value.floating_point = 14.f;
			"weapon_gravity_gun_throwforce"_FF->m_value.floating_point = 1.9f;
			"weapon_gravity_gun_pickforce"_FF->m_value.floating_point = 1.9f;



			"weapon_impact_force"_tif->m_number_value.floating_point = 1.0f;

			"weapon_impact_particle_size"_FF->m_value.floating_point = 1.f;

			"weapon_money_gun"_tif->m_number_value.integer = 1999;

			"weapon_bullet_tracers_limiter"_tif->m_toggle_value.toggle = true;
			"weapon_bullet_tracers_limiter"_tif->m_number_value.integer = 10;

			"weapon_impact_explosion_dmgscale"_FF->m_value.floating_point = 100.f;
			"weapon_impact_explosion_audio"_tf->m_value.toggle = true;
			"weapon_impact_explosion_invisible"_tf->m_value.toggle = false;
			"weapon_impact_explosion_cam_shake"_FF->m_value.floating_point = 0.f;
			"weapon_impact_explosion_damage"_tf->m_value.toggle = true;

			"weapon_missle_launcher_shake"_tif->m_toggle_value.toggle = false;
			"weapon_missle_launcher_shake"_tif->m_number_value.floating_point = 1.0f;
			"weapon_missle_launcher_ptfx"_tif->m_toggle_value.toggle = true;
			"weapon_missle_launcher_ptfx"_tif->m_number_value.floating_point = 1.0f;
			"weapon_missle_launcher_speed"_FF->m_value.floating_point = 1.0f;
			"weapon_missle_launcher_audio"_tf->m_value.toggle = true;

			"weapon_width"_tff->m_number_value.floating_point = 1.f;
			"weapon_height"_tff->m_number_value.floating_point = 1.f;
			"weapon_height_width"_tff->m_number_value.floating_point = 1.f;
			"weapon_laser_sight_fx_distance"_FF->m_value.floating_point = 8.0f;
			"weapon_laser_sight_fx_Brightness"_FF->m_value.floating_point = 5.0f;
			"weapon_laser_sight_fx_Hardness"_FF->m_value.floating_point = 10.0f;
			"weapon_laser_sight_fx_Radius"_FF->m_value.floating_point = 5.f;
			"weapon_laser_sight_fx_Fall_Off"_FF->m_value.floating_point = 5.f;

			"weapon_missle_launcher_esp"_tf->m_value.toggle = true;
		}

		static void initialize() {
			feature_manager::get()->add(toggle_int_feature("weapon_aimbot", "Aimbot", "Do I Have To Explain Really ?.", weapon::aimbot), "weapon");
			feature_manager::get()->add(toggle_feature("weapon_aimbot_silent", "Silent", "No Sound & Quick Kills", null_feature_toggle), "weapon");
			feature_manager::get()->add(int_feature("weapon_aimbot_target", "Target", "Which Entities You Wanna Shoot.", null_feature_int), "weapon");
			feature_manager::get()->add(int_feature("weapon_aimbot_shoot_delay", "Shoot Delay", "Delay Between Each Shot.", null_feature_int), "weapon");
			feature_manager::get()->add(float_feature("weapon_aimbot_fov", "Fov", "The Fov View Of Your Aimbot.", null_feature_float), "weapon");
			feature_manager::get()->add(float_feature("weapon_aimbot_distance", "Distance", "The Aimbot Distance.", null_feature_float), "weapon");
			feature_manager::get()->add(toggle_feature("give_weapons_on_session_join", "Give Weapons", "Gives Player Weapons On Session Join", weapon::give_weapons_on_session_join), "weapon");
			feature_manager::get()->add(toggle_feature("upgrade_weapons_on_session_join", "Upgrade Weapons", "Gives Player Weapons On Session Join", weapon::upgrade_weapons_on_session_join), "weapon");
			feature_manager::get()->add(toggle_int_feature("weapon_impact_explosion", "Enable", "Creates A Custom Explosion At Impact Coord", weapon::explosion_impact), "weapon");
			feature_manager::get()->add(float_feature("weapon_impact_explosion_dmgscale", "Damage Scale", "As Name Suggests.", null_feature_float), "weapon");
			feature_manager::get()->add(float_feature("weapon_impact_explosion_cam_shake", "Cam Shake", "As Name Suggests.", null_feature_float), "weapon");
			feature_manager::get()->add(toggle_feature("weapon_impact_explosion_audio", "Audio", "As Name Suggests.", null_feature_toggle), "weapon");
			feature_manager::get()->add(toggle_feature("weapon_impact_explosion_invisible", "Invisible", "As Name Suggests.", null_feature_toggle), "weapon");
			feature_manager::get()->add(toggle_feature("weapon_impact_explosion_damage", "Damage", "As Name Suggests.", null_feature_toggle), "weapon");

			feature_manager::get()->add(toggle_int_feature("weapon_impact_particle", "Enable", "Creates A Custom Particle At Impact Coord", weapon::particle_impact), "weapon");
			feature_manager::get()->add(float_feature("weapon_impact_particle_size", "Size", "As Name Suggests.", null_feature_float), "weapon");
			feature_manager::get()->add(toggle_feature("weapon_impact_particle_muzzle", "Muzzle Position", "Position Of Ptfx Is Changed To Gun.", null_feature_toggle), "weapon");

			feature_manager::get()->add(toggle_int_feature("weapon_impact_nuke", "Nuke Gun", "Creates A Nuke At Impact Coord", weapon::nuke_gun), "weapon");
			feature_manager::get()->add(toggle_int_feature("weapon_impact_airstrike", "Airstrike", "Shoots An Airstrike From Above", weapon::airstrike_gun), "weapon");
			feature_manager::get()->add(toggle_feature("weapon_impact_drive_it", "Drive It", "Puts You In The Vehilce You Shot", weapon::drive_it_gun), "weapon");
			feature_manager::get()->add(toggle_feature("weapon_impact_delete", "Delete", "Deletes The Entity You Shot At", weapon::delete_gun), "weapon");
			feature_manager::get()->add(toggle_feature("weapon_impact_rope", "Rope", "Basically Spider Man Webs But Limited", weapon::rope_gun), "weapon");
			feature_manager::get()->add(toggle_float_feature("weapon_impact_paint", "Paint", "Paints The Grounds And Change Size.", weapon::paint_gun), "weapon");
			feature_manager::get()->add(toggle_feature("weapon_impact_paint_rainbow", "Rainbow", "Make Fx Colors To Rainbow.", null_feature_toggle), "weapon");
			feature_manager::get()->add(toggle_float_feature("weapon_impact_force", "Force", "Applies Force To Entities", weapon::force_gun), "weapon");
			feature_manager::get()->add(float_feature("weapon_impact_airstrike_speed", "Projectile Speed", "Sets Projectile Speed", null_feature_float), "weapon");
			feature_manager::get()->add(toggle_feature("weapon_rapidfire", "Rapid Fire", "Your Gun Fires Likes RRRRRRR.", weapon::rapidfire), "weapon");
			feature_manager::get()->add(toggle_feature("weapon_infammo", "Unlimited Ammo", "Endless Ammo.", weapon::infammo), "weapon");
			feature_manager::get()->add(toggle_int_feature("weapon_noreload", "Reload", "As The Name Suggests.", weapon::noreload), "weapon");
			feature_manager::get()->add(toggle_feature("weapon_triggerbot", "Triggerbot", "As The Name Suggests.", weapon::triggerbot), "weapon");
			feature_manager::get()->add(toggle_feature("weapon_superpunch", "Super Punch", "As The Name Suggests.", weapon::superpunch), "weapon");
			feature_manager::get()->add(toggle_int_feature("weapon_teleport_gun", "Teleport", "As The Name Suggests.", weapon::teleport_gun), "weapon");
			feature_manager::get()->add(toggle_int_feature("weapon_projectiles", "Projectiles", "Shoots Projectiles.", weapon::projectile_gun), "weapon");
			feature_manager::get()->add(toggle_feature("weapon_dead_eye", "Dead Eye", "Slows Time When You Are Aiming.", weapon::dead_eye), "weapon");
			feature_manager::get()->add(toggle_feature("weapon_shotgun_mode", "Shotgun Mode", "Makes Any Weapon Work As Shotgun.", weapon::shotgun_mode), "weapon");
			feature_manager::get()->add(toggle_feature("weapon_flame_thrower", "Flame Thrower", "Throws Flames Use Fire Extinguisher.", weapon::flame_thrower), "weapon");
			feature_manager::get()->add(toggle_feature("weapon_destroy_ped", "Destroy Gun", "Kills Any Ped Or Vehicle No Matter Health.", weapon::destroy_ped), "weapon");
			feature_manager::get()->add(toggle_feature("weapon_revive_gun", "Revive Gun", "Revives Any Ped Shot At.", weapon::revive_gun), "weapon");
			feature_manager::get()->add(toggle_feature("weapon_shrink_ray", "Shrink Ray", "Shrinks Any Ped Shot At.", weapon::shrink_ray), "weapon");
			feature_manager::get()->add(toggle_feature("weapon_dubstep_gun", "Dubstep Gun", "Makes Peds And Vehicles Dance.Use Railgun", weapon::dubstep_gun), "weapon");
			feature_manager::get()->add(toggle_feature("weapon_flaming_ammo", "Flaming Ammo", "Sets Ped Or Vehicles In Fire.", weapon::flaming_ammo), "weapon");
			feature_manager::get()->add(toggle_float_feature("weapon_width", "Weapon Width", "Change Your Weapon Size", weapon::weapon_width), "weapon");
			feature_manager::get()->add(toggle_float_feature("weapon_height", "Weapon Height", "Change Your Weapon Size", weapon::weapon_height), "weapon");
			feature_manager::get()->add(toggle_float_feature("weapon_height_width", "Weapon Height & Width", "Change Your Weapon Size", weapon::weapon_height_width), "weapon");

			feature_manager::get()->add(toggle_feature("weapon_missle_launcher", "Rocket Launcher", "Spaws Controllable A New Clear Rocket.", weapon::missle_launcher), "weapon");
			feature_manager::get()->add(int_feature("weapon_missle_launcher_type", "Rocket Type", "Choose Rocket", null_feature_int), "weapon");
			feature_manager::get()->add(toggle_feature("weapon_missle_launcher_audio", "Sound", "The Bomming Sound.", null_feature_toggle), "weapon");
			feature_manager::get()->add(toggle_float_feature("weapon_missle_launcher_shake", "Cam Shake", "Shaking Set", null_feature_float_toggle), "weapon");
			feature_manager::get()->add(toggle_float_feature("weapon_missle_launcher_ptfx", "Particle Effects", "PTFX Size Multiplier", null_feature_float_toggle), "weapon");
			feature_manager::get()->add(float_feature("weapon_missle_launcher_speed", "Speed Multiplier", "As The Name Suggests.", null_feature_float), "weapon");
			feature_manager::get()->add(toggle_feature("weapon_missle_launcher_esp", "ESP", "Draw name and line on nearby players.", null_feature_toggle), "weapon");

			feature_manager::get()->add(toggle_int_feature("weapon_blackhole", "Blackhole Gun", "Creates A Black Hole Where You Shoot.", weapon::blackhole_gun), "weapon");
			feature_manager::get()->add(toggle_int_feature("weapon_instrumentofdeath", "Instrument Of Death", "Like A Fortnite Gun.", weapon::instrumentofdeath), "weapon");
			feature_manager::get()->add(toggle_int_feature("weapon_projectile_grenade", "Grenade", "Change Grenade Effect To Choosen One.", weapon::projectile_grenade), "weapon");
			feature_manager::get()->add(toggle_int_feature("weapon_projectile_molotov", "Molotov", "Change Molotov Effect To Choosen One.", weapon::projectile_molotov), "weapon");
			feature_manager::get()->add(toggle_feature("weapon_halloween_special_bomb", "Massacre Bomb ~o~ Halloween Special", "Turn this on and throw grenade.", weapon::halloween_special_ball), "weapon");
			feature_manager::get()->add(toggle_int_feature("weapon_tornado_gun", "Tornado Gun", "Create's Tornado Where You Aim At.", weapon::tornado_gun), "weapon");
			feature_manager::get()->add(toggle_feature("weapon_bullet_tracers", "Bullet Tracers", "Trace Bullet Shoot Coords.", weapon::bullet_tracers), "weapon");
			feature_manager::get()->add(toggle_int_feature("weapon_bullet_tracers_limiter", "Limiter", "Limits Amount Of Traces Drawn.", null_feature_int_toggle), "weapon");

			feature_manager::get()->add(toggle_feature("weapon_round_force_gun", "Spiral Gun", "Creates Circling Entities In The Air And Shoots Rockets.", weapon::round_force_gun), "weapon");
			feature_manager::get()->add(toggle_float_feature("weapon_laxe", "Leviathan Axe", "It A Axe. Set Speed Of Axe", weapon::weapon_axe), "weapon");
			feature_manager::get()->add(toggle_int_feature("weapon_gravity_gun", "Gravity Gun", "Pick Entites.", weapon::gravity_gun), "weapon");
			feature_manager::get()->add(float_feature("weapon_gravity_gun_throwforce", "Throw Force", "As The Name Suggests.", null_feature_float), "weapon");
			feature_manager::get()->add(float_feature("weapon_gravity_gun_pickforce", "Pick Force", "As The Name Suggests.", null_feature_float), "weapon");
			feature_manager::get()->add(float_feature("weapon_gravity_gun_distance", "Distance", "As The Name Suggests.", null_feature_float), "weapon");
			feature_manager::get()->add(toggle_feature("weapon_gravity_gun_fx", "FX", "Turns Ray Effect Off/On", null_feature_toggle), "weapon");
			feature_manager::get()->add(toggle_feature("weapon_laser_sight_fx", "Laser Sight", "Turns Laser Effect On Gun", weapon::laser_sight), "weapon");
			feature_manager::get()->add(toggle_feature("weapon_no_recoil", "No Recoil", "Aim Does Not Move When Shot", weapon::no_recoil), "weapon");
			feature_manager::get()->add(toggle_feature("weapon_inf_range", "Infinite Range", "Does Exactly What It Says.", weapon::inf_range), "weapon");
			feature_manager::get()->add(toggle_feature("weapon_explosive_ammo", "Explosive Ammo", "Gives You Explosive Ammo By Game.", weapon::explosive_ammo), "weapon");
			feature_manager::get()->add(toggle_feature("weapon_fire_ammo", "Fire Ammo", "Gives You Explosive Fire By Game.", weapon::fire_ammo), "weapon");
			feature_manager::get()->add(toggle_feature("weapon_explosive_fist", "Explosive Fist", "Gives You Explosive Fist By Game.", weapon::explosive_fist), "weapon");
			feature_manager::get()->add(toggle_float_feature("weapon_damage", "Damage Modifier", "Changes Weapon Damage", weapon::wep_damage), "weapon");
			feature_manager::get()->add(float_feature("weapon_laser_sight_fx_distance", "Light Distance", "As The Name Suggests.", null_feature_float), "weapon");
			feature_manager::get()->add(float_feature("weapon_laser_sight_fx_Brightness", "Brightness", "As The Name Suggests.", null_feature_float), "weapon");
			feature_manager::get()->add(float_feature("weapon_laser_sight_fx_Hardness", "Hardness", "As The Name Suggests.", null_feature_float), "weapon");
			feature_manager::get()->add(float_feature("weapon_laser_sight_fx_Radius", "Radius", "As The Name Suggests.", null_feature_float), "weapon");
			feature_manager::get()->add(float_feature("weapon_laser_sight_fx_Fall_Off", "Fall Off", "As The Name Suggests.", null_feature_float), "weapon");

			feature_manager::get()->add(toggle_int_feature("weapon_money_gun", "Money Gun", "Spawns Money At Place You Shoot At.", weapon::money_gun), "weapon");
			set_values();
		}
	};
}