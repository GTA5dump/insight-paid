
#include "cheat/features/features/features_utility.hpp"
#include "cheat/script/script.hpp"
#include "cheat/menu/helper/ui.hpp"
#include "util/panels/panels.hpp"
#include "util/config/config.hpp"
#include "cheat/features/globals.hpp"
#include "util/math/math.hpp"
#include "cheat/script/script_utility.hpp"
#include "cheat/menu/sub/option_flag.h"	
std::string aimbot_type[] = {
	"Snap", "Advance (Beta)"
};

std::string target_names[] = {
	"Players", "Peds", "All"
};

std::string  nuke_effects[] = {
	"Realistic",
	"Normal",
	"X Pattern"
};
std::string m_airstrike_gun[] = {
	"None", "Owned"
};
struct aimbot_name_and_bone
{
	std::string name;
	std::uint32_t bone;
};
const std::vector<aimbot_name_and_bone> aimbot_names_and_bones{
{"Stomach",0x0},
{"Head",0x796E},
{"Left Hand",0x8CBD},
{"Right Hand",0x188E},
{"Left Foot",0xFEDD},
{"Right Foot",0x8AAE}
};

inline std::string regular_tints[] = { "Default/Black", "Green", "Gold", "Pink", "Army", "LSPD", "Orange", "Platinum" };
inline std::string mk2_tints[] = { "Classic Black", "Classic Gray", "Classic Two-Tone", "Classic White", "Classic Beige", "Classic Green", "Classic Blue", "Classic Earth", "Classic Brown & Black", "Red Contrast", "Blue Contrast", "Yellow Contrast", "Orange Contrast", "Bold Pink", "Bold Purple & Yellow", "Bold Orange", "Bold Green & Purple", "Bold Red Features", "Bold Green Features", "Bold Cyan Features", "Bold Yellow Features", "Bold Red & White", "Bold Blue & White", "Metallic Gold", "Metallic Platinum", "Metallic Gray & Lilac", "Metallic Purple & Lime", "Metallic Red", "Metallic Green", "Metallic Blue", "Metallic White & Aqua", "Metallic Orange & Yellow", "Metallic Red and Yellow" };

inline int weapon_tints;
inline int all_weapon_tints;
inline int all_mk_weapon_tints;

struct paint_gun_fx
{
	std::string name;
	DecalTypes fx;
};
const std::vector<paint_gun_fx> paint_gun_fx_list{
{"Splatters Blood", DecalTypes::splatters_blood},
{"Splatters Blood Dir", DecalTypes::splatters_blood_dir},
{"Splatters Blood Mist", DecalTypes::splatters_blood_mist},
{"Splatters Mud", DecalTypes::splatters_mud},
{"Splatters Paint", DecalTypes::splatters_paint},
{"Splatters Water", DecalTypes::splatters_water},
{"Splatters Water Hydrant", DecalTypes::splatters_water_hydrant},
{"Splatters Blood 2", DecalTypes::splatters_blood2},
{"Weap Impact Metal", DecalTypes::weapImpact_metal},
{"Weap Impact Concrete", DecalTypes::weapImpact_concrete},
{"Weap Impact Mattress", DecalTypes::weapImpact_mattress},
{"Weap Impact Mud", DecalTypes::weapImpact_mud},
{"Weap Impact Wood", DecalTypes::weapImpact_wood},
{"Weap Impact Sand", DecalTypes::weapImpact_sand},
{"Weap Impact Cardboard", DecalTypes::weapImpact_cardboard},
{"Weap Impact Melee Glass", DecalTypes::weapImpact_melee_glass},
{"Weap Impact Glass Blood", DecalTypes::weapImpact_glass_blood},
{"Weap Impact Glass Blood 2", DecalTypes::weapImpact_glass_blood2},
{"Weap Impact Shotgun Paper", DecalTypes::weapImpact_shotgun_paper},
{"Weap Impact Shotgun Mattress", DecalTypes::weapImpact_shotgun_mattress},
{"Weap Impact Shotgun Metal", DecalTypes::weapImpact_shotgun_metal},
{"Weap Impact Shotgun Wood", DecalTypes::weapImpact_shotgun_wood},
{"Weap Impact Shotgun Dirt", DecalTypes::weapImpact_shotgun_dirt},
{"Weap Impact Shotgun TV Screen", DecalTypes::weapImpact_shotgun_tvscreen},
{"Weap Impact Shotgun TV Screen 2", DecalTypes::weapImpact_shotgun_tvscreen2},
{"Weap Impact Shotgun TV Screen 3", DecalTypes::weapImpact_shotgun_tvscreen3},
{"Weap Impact Melee Concrete", DecalTypes::weapImpact_melee_concrete},
{"Weap Impact Melee Wood", DecalTypes::weapImpact_melee_wood},
{"Weap Impact Melee Metal", DecalTypes::weapImpact_melee_metal},
{"Burn 1", DecalTypes::burn1},
{"Burn 2", DecalTypes::burn2},
{"Burn 3", DecalTypes::burn3},
{"Burn 4", DecalTypes::burn4},
{"Burn 5", DecalTypes::burn5},
{"Bang Concrete Bang", DecalTypes::bang_concrete_bang},
{"Bang Concrete Bang 2", DecalTypes::bang_concrete_bang2},
{"Bang Bullet Bang", DecalTypes::bang_bullet_bang},
{"Bang Bullet Bang 2", DecalTypes::bang_bullet_bang2},
{"Bang Glass", DecalTypes::bang_glass},
{"Bang Glass 2", DecalTypes::bang_glass2},
{"SolidPool Water", DecalTypes::solidPool_water},
{"SolidPool Blood", DecalTypes::solidPool_blood},
{"SolidPool Oil", DecalTypes::solidPool_oil},
{"SolidPool Petrol", DecalTypes::solidPool_petrol},
{"SolidPool Mud", DecalTypes::solidPool_mud},
{"PorousPool Water", DecalTypes::porousPool_water},
{"PorousPool Blood", DecalTypes::porousPool_blood},
{"PorousPool Oil", DecalTypes::porousPool_oil},
{"PorousPool Petrol", DecalTypes::porousPool_petrol},
{"PorousPool Mud", DecalTypes::porousPool_mud},
{"PorousPool Water Ped Drip", DecalTypes::porousPool_water_ped_drip},
{"LiquidTrail Water", DecalTypes::liquidTrail_water}
};
std::string m_teleport_gun[] = {
	 "Smooth","Instant"
};
std::string m_blackhole_gun[] = {
	 "Force","Force & Delete"
};
std::string m_instrument_of_death_gun[] = {
	 "Cursor Following","Motor Mode"
};
std::string m_tornado_gun[] = {
	 "Super","Smooth"
};
std::string m_gravity_gun_gun[] = {
	 "Smooth","Instant"
};
std::string m_reload_gun[] = {
	 "Never","Fast"
};
std::string m_rockets_mis[] = {
	"Giant Rocket",
	"RPG Rocket",
	"Homing Rocket",
	"Firework Rocket"
};
namespace insight {
	void script_ui::weapon() {
		render::push<sub>("Weapons", "Weapons"_joaat, [](sub* ui) {
			ui->push(submenu("Aimbot").add_target("Weapons_Aimbot"_joaat));
			ui->push(submenu("Triggerbot").add_target("Weapons_Triggerbot"_joaat));
			ui->push(submenu("Locker").add_target("Weapons_Locker"_joaat));
			ui->push(submenu("Impact").add_target("Weapons_Impact"_joaat));
			ui->push(submenu("Mods").add_target("Weapons_Mods"_joaat));
			ui->push(submenu("Rocket Missile").add_target("Weapons_Rocket_Missle"_joaat));
			ui->push(submenu("Matrix").add_target("Weapons_Matrix"_joaat));
			ui->push(submenu("Laser Sight").add_target("Weapons_Laser_Sight"_joaat));
			ui::push()->feature_toggle(ui, "weapon_infammo"_tf);
			ui::push()->array_feature_toggle(ui, "weapon_noreload"_tif, m_reload_gun, 2);
			ui::push()->feature_toggle(ui, "weapon_rapidfire"_tf);
			ui->push(info("Modifiers"));

			ui::push()->feature_toggle(ui, "weapon_no_recoil"_tf);
			ui::push()->feature_toggle_float(ui, "weapon_damage"_tff, 0.0f, 100.f, 0.1f, 1);
			ui::push()->feature_toggle(ui, "weapon_inf_range"_tf);
			ui->push(info("Flags"));

			ui::push()->feature_toggle(ui, "weapon_explosive_ammo"_tf);
			ui::push()->feature_toggle(ui, "weapon_fire_ammo"_tf);
			ui::push()->feature_toggle(ui, "weapon_explosive_fist"_tf);


		});

		render::push<sub>("Lazer Sight", "Weapons_Laser_Sight"_joaat, [](sub* ui) {
			ui::push()->feature_toggle(ui, "weapon_laser_sight_fx"_tf);
			ui::push()->feature_float(ui, "weapon_laser_sight_fx_distance"_FF, 0, 100.0, 0.1f);
			ui::push()->feature_float(ui, "weapon_laser_sight_fx_Brightness"_FF, 0, 100.0, 0.1f);
			ui::push()->feature_float(ui, "weapon_laser_sight_fx_Hardness"_FF, 0, 100.0, 0.1f);
			ui::push()->feature_float(ui, "weapon_laser_sight_fx_Radius"_FF, 0, 100.0, 0.1f);
			ui::push()->feature_float(ui, "weapon_laser_sight_fx_Fall_Off"_FF, 0, 100.0, 0.1f);
			ui::push()->color_option(ui, "Color", &features_utility::get()->n_laser_sight_color);

		});
		render::push<sub>("Mods", "Weapons_Mods"_joaat, [](sub* ui) {
			ui->push(submenu("Special").add_target("Weapons_Mods_Projectile_Manager"_joaat));
			ui->push(submenu("Gravity Gun").add_target("Weapons_Mods_GravityGun"_joaat));

			ui::push()->array_feature_toggle(ui, "weapon_projectiles"_tif, eVehicleWeapons_Names, std::size(eVehicleWeapons_Names));
			ui::push()->array_feature_toggle(ui, "weapon_blackhole"_tif, m_blackhole_gun, 2);
			ui::push()->array_feature_toggle(ui, "weapon_tornado_gun"_tif, m_tornado_gun, 2);
			ui::push()->array_feature_toggle(ui, "weapon_instrumentofdeath"_tif, m_instrument_of_death_gun, 2);
			ui::push()->feature_toggle_float(ui, "weapon_laxe"_tff, 0.5f, 3.f, 0.1f, 1);
			ui::push()->feature_toggle(ui, "weapon_superpunch"_tf);
			ui::push()->feature_toggle(ui, "weapon_dead_eye"_tf);
			ui::push()->feature_toggle(ui, "weapon_shotgun_mode"_tf);
			ui::push()->feature_toggle(ui, "weapon_flame_thrower"_tf);
			ui::push()->feature_toggle(ui, "weapon_destroy_ped"_tf);
			ui::push()->feature_toggle(ui, "weapon_revive_gun"_tf);
			ui::push()->feature_toggle(ui, "weapon_shrink_ray"_tf);
			ui::push()->feature_toggle(ui, "weapon_dubstep_gun"_tf);
			ui::push()->feature_toggle(ui, "weapon_flaming_ammo"_tf);
			ui::push()->feature_toggle(ui, "weapon_round_force_gun"_tf);

		});
		render::push<sub>("Missle", "Weapons_Rocket_Missle"_joaat, [](sub* ui) {
			ui::push()->feature_toggle(ui, "weapon_missle_launcher"_tf);
			//ui::push()->array_feature(ui, "weapon_missle_launcher_type"_if, m_rockets_mis, std::size(m_rockets_mis)); other don't rotate. game issue
			ui::push()->feature_toggle(ui, "weapon_missle_launcher_esp"_tf);
			ui::push()->feature_toggle(ui, "weapon_missle_launcher_audio"_tf);
			ui::push()->feature_toggle_float(ui, "weapon_missle_launcher_shake"_tff, 0.001f, 100.f, 0.01f, 3);
			ui::push()->feature_toggle_float(ui, "weapon_missle_launcher_ptfx"_tff, 0.001f, 100.f, 0.01f, 3);
			ui::push()->feature_float(ui, "weapon_missle_launcher_speed"_FF, 0, 10.0, 0.1f);

		});
		render::push<sub>("Mods", "Weapons_Matrix"_joaat, [](sub* ui) {
			ui::push()->feature_toggle_float(ui, "weapon_width"_tff, 0.f, 10.f, 0.01f, 2);
			ui::push()->feature_toggle_float(ui, "weapon_height"_tff, 0.f, 10.f, 0.01f, 2);
			ui::push()->feature_toggle_float(ui, "weapon_height_width"_tff, 0.f, 10.f, 0.01f, 2);
			});
		render::push<sub>("Gravity Gun", "Weapons_Mods_GravityGun"_joaat, [](sub* ui) {
			ui::push()->array_feature_toggle(ui, "weapon_gravity_gun"_tif, m_gravity_gun_gun, 2);
			if ("weapon_gravity_gun"_tif->m_number_value.integer == 0)
			ui::push()->feature_float(ui, "weapon_gravity_gun_pickforce"_FF, 0, 3.0, 0.1f);
			ui::push()->feature_float(ui, "weapon_gravity_gun_throwforce"_FF, 0, 3.0, 0.1f);
			ui::push()->feature_float(ui, "weapon_gravity_gun_distance"_FF, 0, 100.0, 0.1f);
			ui::push()->feature_toggle(ui, "weapon_gravity_gun_fx"_tf);


		});
		render::push<sub>("Impact", "Weapons_Impact"_joaat, [](sub* ui) {
			ui->push(submenu("Airstrike").add_target("Weapons_Impact_Airstrike"_joaat));
			ui->push(submenu("Paint").add_target("Weapons_Impact_Paint"_joaat));
			ui->push(submenu("Explosion").add_target("Weapons_Impact_Explosion"_joaat));
			ui->push(submenu("Particle").add_target("Weapons_Impact_Particle"_joaat));
			ui->push(submenu("Bullet Tracers").add_target("Weapons_Impact_Tracers"_joaat));
			ui::push()->array_feature_toggle(ui, "weapon_impact_nuke"_tif, nuke_effects, 3);
			ui::push()->array_feature_toggle(ui, "weapon_teleport_gun"_tif, m_teleport_gun, 2);
			if ("weapon_teleport_gun"_tif->m_toggle_value.toggle) {
				if ("weapon_teleport_gun"_tif->m_number_value.integer == 0) {
					ui::push()->feature_float(ui, "teleport_settings_animation_ease_out"_FF, 0.f, 5000.f, 100.f);
				}
			}			
			ui::push()->feature_toggle_int(ui, "weapon_money_gun"_tif, 1, 1999, 1, 0);
			ui::push()->feature_toggle(ui, "weapon_impact_drive_it"_tf);
			ui::push()->feature_toggle(ui, "weapon_impact_delete"_tf);
			ui::push()->feature_toggle(ui, "weapon_impact_rope"_tf);
			ui::push()->feature_toggle_float(ui, "weapon_impact_force"_tff, 1.0f, 10.f, 0.1f, 1);

		});
		render::push<sub>("Explosion", "Weapons_Impact_Explosion"_joaat, [](sub* ui) {
			ui::push()->array_feature_toggle(ui, "weapon_impact_explosion"_tif, eExplosionsType, 73);
			ui::push()->feature_toggle(ui, "weapon_impact_explosion_audio"_tf);
			ui::push()->feature_toggle(ui, "weapon_impact_explosion_invisible"_tf);
			ui::push()->feature_toggle(ui, "weapon_impact_explosion_damage"_tf);
			ui::push()->feature_float(ui, "weapon_impact_explosion_dmgscale"_FF, 0, 100.f, 1.0f);
			ui::push()->feature_float(ui, "weapon_impact_explosion_cam_shake"_FF, 0, 10.0, 0.1f);

			});
		render::push<sub>("Particle", "Weapons_Impact_Particle"_joaat, [](sub* ui) {
			ui::push()->array_feature_toggle(ui, "weapon_impact_particle"_tif, particle_effects, std::size(particle_effects));
			ui::push()->feature_float(ui, "weapon_impact_particle_size"_FF, 0, 10.0, 0.1f);
			ui::push()->feature_toggle(ui, "weapon_impact_particle_muzzle"_tf);
			});
		render::push<sub>("Bullet Tracers", "Weapons_Impact_Tracers"_joaat, [](sub* ui) {
			ui::push()->feature_toggle(ui, "weapon_bullet_tracers"_tf);
			ui::push()->feature_toggle_int(ui, "weapon_bullet_tracers_limiter"_tif, 1, 100, 1, 0);
			ui::push()->color_option(ui, "Color", &features_utility::get()->n_bullet_tracer_color);
			});
		render::push<sub>("Airstrike", "Weapons_Impact_Airstrike"_joaat, [](sub* ui) {
			ui::push()->array_feature_toggle(ui, "weapon_impact_airstrike"_tif, m_airstrike_gun, 2);

			ui->push(number<float>("weapon_impact_airstrike_speed"_FF->m_name).add_number(&"weapon_impact_airstrike_speed"_FF->m_value.floating_point).
				add_min(100).add_max(1000).add_precision(1).add_step(100).add_description("weapon_impact_airstrike_speed"_FF->m_description));

				ui->push(submenu("Projectile").add_target("Player_Vehicle_Weapons_Selct"_joaat).add_function([] {
					script_utility::get()->weapon_projectile_select = 1;
					}));

			});
		render::push<sub>("Paint", "Weapons_Impact_Paint"_joaat, [](sub* ui) {

			ui::push()->feature_toggle_float(ui, "weapon_impact_paint"_tff, 0.f, 100.f, 1.f, 0);

			ui->push(submenu("Fx").add_target("Weapons_Impact_PaintFX"_joaat));
			ui::push()->feature_toggle(ui, "weapon_impact_paint_rainbow"_tf);
			if (!"weapon_impact_paint_rainbow"_tf->m_value.toggle)
			{
				ui->push(info("Colors"));

				ui->push(number<float>("Red").add_number(&features_utility::get()->Paint_Gun_Colors.x).add_min(0).
					add_max(255).add_precision(1).add_step(1));
				ui->push(number<float>("Green").add_number(&features_utility::get()->Paint_Gun_Colors.y).add_min(0).
					add_max(255).add_precision(1).add_step(1));
				ui->push(number<float>("Blue").add_number(&features_utility::get()->Paint_Gun_Colors.z).add_min(0).
					add_max(255).add_precision(1).add_step(1));

			}
			});	
		render::push<sub>("Fx", "Weapons_Impact_PaintFX"_joaat, [](sub* ui) {

			for (int i = 0; i < paint_gun_fx_list.size(); i++)
			{
				bool selected = paint_gun_fx_list[i].fx == features_utility::get()->decal_paintgun;
				ui->push(button(selected ? "~o~" + paint_gun_fx_list[i].name : paint_gun_fx_list[i].name).set_action([=] {
					features_utility::get()->decal_paintgun = paint_gun_fx_list[i].fx;
					}));
			}
			

			});
		render::push<sub>("Triggerbot", "Weapons_Triggerbot"_joaat, [](sub* ui) {
			ui->push(submenu("Targeted Bones").add_target("Weapons_Aimbot_Bones"_joaat));
			ui::push()->feature_toggle(ui, "weapon_triggerbot"_tf);
			});
		render::push<sub>("Aimbot", "Weapons_Aimbot"_joaat, [](sub* ui) {
			ui->push(submenu("Targeted Bones").add_target("Weapons_Aimbot_Bones"_joaat));
			ui::push()->array_feature_toggle(ui, "weapon_aimbot"_tif, aimbot_type, 2);
			if ("weapon_aimbot"_tif->m_number_value.integer != 1) {
				ui::push()->array_feature(ui, "weapon_aimbot_target"_if, target_names, 3);
				if ("weapon_aimbot"_tif->m_number_value.integer == 1) {
					ui::push()->feature_int(ui, "weapon_aimbot_shoot_delay"_if, 0, 1000, 10);
				}
				ui::push()->feature_toggle(ui, "weapon_aimbot_silent"_tf);
				ui::push()->feature_float(ui, "weapon_aimbot_distance"_FF, 0, 10000.f, 10.f);
			}
			ui::push()->feature_float(ui, "weapon_aimbot_fov"_FF, 0, 10000.f, 10.f);

		});
		render::push<sub>("Bones", "Weapons_Aimbot_Bones"_joaat, [](sub* ui) {
			for (std::uint32_t r = 0; r < aimbot_names_and_bones.size(); ++r)
			{
				bool found = false;
				for (int i = 0; i < features_utility::get()->aimbot_selected_bones.size(); i++) {
					if (features_utility::get()->aimbot_selected_bones[i] == aimbot_names_and_bones[r].bone) {
						found = true;
						break;
					} 
				}
				ui->push(button(found ? "~o~" + aimbot_names_and_bones[r].name :  aimbot_names_and_bones[r].name).add_function([=] {
					bool found = false;
					for (int f = 0; f < features_utility::get()->aimbot_selected_bones.size(); f++) {
						if (features_utility::get()->aimbot_selected_bones[f] == aimbot_names_and_bones[r].bone) {
							found = true;
							features_utility::get()->aimbot_selected_bones.erase(features_utility::get()->aimbot_selected_bones.begin() + f);
							break;
						}
					}
					if (!found) {
						features_utility::get()->aimbot_selected_bones.push_back(aimbot_names_and_bones[r].bone);
					}
					}));
			}

		});

		render::push<sub>("Locker", "Weapons_Locker"_joaat, [](sub* ui) {
			ui->push(button("Give All Weapons").add_function([] {
				tasks::give_weapons_to_player(globals::player_id);
			}));
			ui->push(button("Remove All Weapons").add_function([] {
				tasks::remove_weapons_from_player(globals::player_id);
			}));
			ui->push(info("Upgrades"));
			ui->push(button("Upgrade Current Weapon").add_function([] {
				tasks::upgrade_player_current_weapon(globals::player_id);
			}));
			ui->push(button("Upgrade All Weapons").add_function([] {
				tasks::upgrade_player_weapons(globals::player_id);
			}));
			ui->push(info("Tints"));
			if (tasks::is_player_current_weapon_mk2(globals::player_id)) {
				ui->push(array<std::string, int>("Current Weapon Tint").add_array(&mk2_tints).add_position(&weapon_tints).set_action([] {
					tasks::change_weapon_tint(globals::player_id, weapon_tints);
				}));
			}
			else {
				ui->push(array<std::string, int>("Current Weapon Tint").add_array(&regular_tints).add_position(&weapon_tints).set_action([] {
					tasks::change_weapon_tint(globals::player_id, weapon_tints);
				}));
			}
			ui->push(array<std::string, int>("All Weapons Tints").add_array(&regular_tints).add_position(&all_weapon_tints).set_action([] {
				tasks::change_all_weapons_tint(globals::player_id, all_weapon_tints);
			}));
			ui->push(array<std::string, int>("All Mk2 Weapons Tints").add_array(&mk2_tints).add_position(&all_mk_weapon_tints).set_action([] {
				tasks::change_all_mk2_weapons_tint(globals::player_id, all_mk_weapon_tints);
			}));
			ui->push(info("On Session Join"));
			ui::push()->feature_toggle(ui, "give_weapons_on_session_join"_tf);
			ui::push()->feature_toggle(ui, "upgrade_weapons_on_session_join"_tf);
		});
	}
}