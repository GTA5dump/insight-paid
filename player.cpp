
#include "cheat/script/script.hpp"
#include "cheat/features/globals.hpp"
#include "natives.hpp"
#include "cheat/menu/xml/xml.hpp"
#include "util/script/script.hpp"
#include "cheat/script/script_utility.hpp"
#include <util/panels/panels.hpp>
#include "cheat/features/features.hpp"
namespace insight {
	std::string m_no_ragdoll_type[] = {
		"Normal",
		"Smart"
	};
	std::string m_invisible_type[] = {
		"Normal",
		"Visible Locally"
	};
	std::string m_super_run_type[] = {
		"Slow",
		"Medium",
		"Fast"
	};
	std::string m_super_jump_type[] = {
		"Settings Only",
		"Super",
		"Beast"
	};	
	std::string m_alpha_set[] = {
		"0%",
		"25%",
		"50%",
		"75%",
		"100%"
	};
	std::string m_walk_thru_type[] = {
		"Vehicles",
		"Peds",
		"Objects",
		"All"
	};

	std::string m_no_clip_type[] = {
		"Normal",
		"Walking"
	};

	std::string m_freecam_type[] = {
		"Normal",
		"Teleport"
	};
	std::string m_player_fast_respawn_type[] = {
		"Normal",
		"Instantly"
	};
	std::string m_player_karama_type[] = {
		"All",
		"Players Only"
	};
	std::string m_player_drunk_mode_type[] = {
		"Light",
		"Medium",
		"High",
		"Very High"
	};
	std::string m_player_bab_yoga_type[] = {
		"Attract Entities + Rockets",
		"Rockets Only"
	};
	std::string m_player_wetness_type[] = {
		"Water"
	};
	std::string m_player_tinylegs_type[] = {
		"Tiny",
		"Springy Legs"
	};
	std::string m_auto_heal_n_armor_type[] = {
		"Looped",
		"While In Cover",
		"While Shooting",
		"While Running"
	};

	int Player_Visions_Selected = 0;
	struct vision_display { const char* display_name; const char* real_name; };
	inline std::vector<vision_display> visions{
		{ "None", "" },
		{ "Sunglasses", "sunglasses" },
		{ "Camera BW", "CAMERA_BW" },
		{ "Hint Cam", "Hint_cam" },
		{ "UFO", "ufo" },
		{ "UFO Deathray", "ufo_deathray" },
		{ "Dying", "dying" },
		{ "Underwater", "underwater" },
		{ "Spectator", "spectator1" },
		{ "Cops Splash", "CopsSPLASH" },
		{ "Crane Cam", "crane_cam" },
		{ "Secret Camera", "secret_camera" },
		{ "Graveyard Shootout", "graveyard_shootout" },
		{ "Cops", "cops" },
		{ "Damage", "damage" },
		{ "Bikers Splash", "BikersSPLASH" },
		{ "Bikers", "Bikers" },
		{ "Prologue Shootout", "prologue_shootout" },
		{ "Vagos", "vagos" },
		{ "Sniper", "sniper" }
	};
	struct animations_data
	{

		std::string name;
		const char* animation;
		const char* animationid;
	};
	int animations_flags_selected;
	const std::vector<animations_data> animations{
		{"Pole Dance", "mini@strip_club@pole_dance@pole_dance3", "pd_dance_03"},
		{ "Hood Dance","missfbi3_sniping","dance_m_default" },
		{ "Burning","ragdoll@human","on_fire" },
		{ "Getting Stunned","ragdoll@human","electrocute" },
		{ "Private Dance","mini@strip_club@private_dance@part1","priv_dance_p1" },
		{ "The Abundance","rcmpaparazzo_2","shag_loop_poppy" },
		{ "Invisible Man","rcmpaparazzo_2","shag_loop_a" },
		{ "Push ups","amb@world_human_push_ups@male@base","base" },
		{ "Sit ups","amb@world_human_sit_ups@male@base","base" },
		{ "Wave Arms","random@car_thief@victimpoints_ig_3","arms_waving" },
		{ "Give BJ to Driver","mini@prostitutes@sexnorm_veh","bj_loop_prostitute" },
		{ "Pleasure Driver","mini@prostitutes@sexnorm_veh","sex_loop_prostitute" },
		{ "Mime","special_ped@mime@monologue_8@monologue_8a","08_ig_1_wall_ba_0" },
		{ "Mime 2","special_ped@mime@monologue_7@monologue_7a","11_ig_1_run_aw_0" },
		{ "Throw","switch@franklin@throw_cup","throw_cup_loop" },
		{ "Smoke Coughing","timetable@gardener@smoking_joint","idle_cough" },
		{ "Chilling","friends@laf@ig_1@base","base" },
		{ "Crazy Dance","misschinese1crazydance","crazy_dance_1" },
		{ "Crazy Dance 1","misschinese1crazydance","crazy_dance_2" },
		{ "Crazy Dance 2","misschinese1crazydance","crazy_dance_3" },
		{ "Think We Dumb","timetable@ron@they_think_were_stupid","they_think_were_stupid" },
		{ "Come ici","gestures@m@standing@fat","gesture_come_here_hard" },
		{ "No Way","gestures@m@standing@fat","gesture_no_way" },
		{ "Kill Me","random@bicycle_thief@ask_help","my_dads_going_to_kill_me" },
		{ "Help Me","random@bicycle_thief@ask_help","please_man_you_gotta_help_me" },
		{ "Sleep","savecouch@","t_sleep_loop_couch" },
		{ "Sleep 2","savem_default@","m_sleep_r_loop" },
		{ "Sleep 3","timetable@tracy@sleep@","idle_c" },
		{ "Meditate","rcmcollect_paperleadinout@","meditiate_idle" },
		{ "Yeah Yeah","special_ped@jessie@michael_1@michael_1b","jessie_ig_2_yeahyeahyeah_1" },
		{ "Idle On Laptop","switch@franklin@on_laptop","001927_01_fras_v2_4_on_laptop_idle" },
		{ "Idle - Conceal Weapon 1", "anim@miss@low@fin@vagos@", "idle_ped01" },
		{ "Idle - Conceal Weapon 2", "anim@miss@low@fin@vagos@", "idle_ped02" },
		{ "Idle - Conceal Weapon 3", "anim@miss@low@fin@vagos@", "idle_ped03" },
		{ "Idle - Conceal Weapon 4", "anim@miss@low@fin@vagos@", "idle_ped04" },
		{ "Idle - Conceal Weapon 5", "anim@miss@low@fin@vagos@", "idle_ped05" },
		{ "Idle - Conceal Weapon 6", "anim@miss@low@fin@vagos@", "idle_ped06" },
		{ "Idle - Conceal Weapon 7", "anim@miss@low@fin@vagos@", "idle_ped07" },
		{ "Idle - Conceal Weapon 8", "anim@miss@low@fin@vagos@", "idle_ped08" },
		{ "Surrender", "random@arrests@busted", "idle_a" },
		{ "Police - Use Radio", "random@arrests", "generic_radio_chatter" },
		{ "Sniper Crouch", "missfbi2", "franklin_sniper_crouch" },
		{ "Crouch Walking", "move_weapon@rifle@generic", "walk_crouch" },
		{ "Hip Hop Dance", "missfbi3_sniping", "dance_m_default" },
		{ "Private Dance", "mini@strip_club@private_dance@part1", "priv_dance_p1" },
		{ "Move to the Beat 1", "amb@world_human_strip_watch_stand@male_a@base", "base" },
		{ "Move to the Beat 2", "amb@world_human_strip_watch_stand@male_b@base", "base" },
		{ "Move to the Beat 3", "amb@world_human_strip_watch_stand@male_c@base", "base" },
		{ "Move to the Beat 4", "amb@world_human_strip_watch_stand@male_c@idle_a", "idle_a" },
		{ "Move to the Beat 5", "amb@world_human_partying@female@partying_beer@base", "base" },
		{ "Mountain Dance", "special_ped@mountain_dancer@monologue_1@monologue_1a", "mtn_dnc_if_you_want_to_get_to_heaven" },
		{ "Bump and Grind", "mini@strip_club@private_dance@idle", "priv_dance_idle" },
		{ "Corny Dancing", "anim@mp_player_intincardancebodhi@rds@", "idle_a" },
		{ "Dirty Dancing", "oddjobs@assassinate@multi@yachttarget@lapdance", "yacht_ld_f" },
		{ "Crazy Dancing", "misschinese2_crystalmazemcs1_ig", "dance_loop_tao" },
		{ "Shake Your Butt", "switch@trevor@mocks_lapdance", "001443_01_trvs_28_idle_stripper" },
		{ "Jerking Off", "switch@trevor@jerking_off", "trev_jerking_off_loop" },
		{ "Butt Scratch", "mp_player_int_upperarse_pick", "mp_player_int_arse_pick" },
		{ "Peeing", "misscarsteal2peeing", "peeing_loop" },
		{ "Pooping", "missfbi3ig_0", "shit_loop_trev" },
		{ "Pick Nose", "anim@mp_player_intincarnose_pickstd@rps@", "idle_a" },
		{ "Wash Hands", "missheist_agency3aig_23", "urinal_sink_loop" },
		{ "Look at Fingernails", "missfbi3_camcrew", "base_gal" },
		{ "Brush Shoulders Off", "missfbi3_camcrew", "base_gal" },
		{ "Drunk", "move_m@drunk@verydrunk_idles@", "fidget_01" },
		{ "Twitchy", "oddjobs@bailbond_hobotwitchy", "idle_a" },
		{ "Ow, My Head", "misscarsteal4@actor", "dazed_idle" },
		{ "So Depressed", "oddjobs@bailbond_hobodepressed", "idle_a" },
		{ "Kick Rocks", "timetable@ron@ig_1", "ig_1_idle_a" },
		{ "Looking for Something", "missmic_4premierejimwaitbef_prem", "wait_idle_a" },
		{ "Bend Over to Look", "switch@franklin@admire_motorcycle", "base_franklin" },
		{ "Examining", "missfbi5ig_15", "look_into_microscope_c_scientistb" },
		{ "It's a Bird, It's a Plane", "oddjobs@basejump@", "ped_a_loop" },
		{ "Flip the Bird", "anim@mp_player_intincarfingerbodhi@ds@", "idle_a" },
		{ "Yelling at Someone", "misscarsteal4@actor", "actor_berating_loop" },
		{ "Getting Yelled At", "misscarsteal4", "assistant_loop" },
		{ "Arguing Girl", "missfbi3_camcrew", "first_action_gal" },
		{ "Arguing Guy", "missfbi3_camcrew", "first_action_guy" },
		{ "Kicking Guy on Ground 1", "missheistdockssetup1ig_13@kick_idle", "guard_beatup_kickidle_guard1" },
		{ "Kicking Guy on Ground 2", "missheistdockssetup1ig_13@kick_idle", "guard_beatup_kickidle_guard2" },
		{ "Getting Kicked", "missheistdockssetup1ig_13@kick_idle", "guard_beatup_kickidle_dockworker" },
		{ "Tough Guy - Arms Crossed", "missdocksshowoffcar@idle_a", "idle_b_5" },
		{ "Stand at Rail", "anim@amb@yacht@rail@standing@male@variant_01@", "base" },
		{ "Out of Breath", "re@construction", "out_of_breath" },
		{ "Base Jump Prep", "oddjobs@bailbond_mountain", "base_jump_idle" },
		{ "Jazzercise 1", "timetable@tracy@ig_5@idle_a", "idle_c" },
		{ "Jazzercise 2", "timetable@tracy@ig_5@idle_b", "idle_e" },
		{ "Warmup Stretching 1", "mini@triathlon", "idle_a" },
		{ "Warmup Stretching 2", "mini@triathlon", "ig_2_gen_warmup_01" },
		{ "Jog in Place", "amb@world_human_jog_standing@male@fitbase", "base" },
		{ "Cat - Scratch Ear", "creatures@cat@player_action@", "action_a" },
		{ "Dog - Sit", "creatures@dog@move", "sit_loop" },
		{ "Dog - Walk in Circles", "creatures@dog@move", "idle_turn_l" },
		{ "Rabbit - Scratch Ear", "creatures@rabbit@player_action@", "action_a" },
		{ "Monkey - Idle 1", "missfbi5ig_30monkeys", "monkey_a_idle" },
		{ "Monkey - Idle 2", "missfbi5ig_30monkeys", "monkey_b_idle" },
		{ "Monkey - Idle 3", "missfbi5ig_30monkeys", "monkey_c_idle" },
		{ "Monkey - Freakout 1", "missfbi5ig_30monkeys", "monkey_a_freakout_loop" },
		{ "Monkey - Freakout 2", "missfbi5ig_30monkeys", "monkey_b_freakout_loop" },
		{ "Monkey - Freakout 3", "missfbi5ig_30monkeys", "monkey_c_freakout_loop" }
	};
	struct animations_data_flags
	{
		std::string name;
		int Value;
	};
	const std::vector<animations_data_flags> animations_flags{
		{"Normal", 0},
		{ "Repeat",1 },
		{ "Stop on last frame",2 },
		{ "Upper Body Normal",16 },
		{ "Upper Body Loop",17 },
		{ "Upper Body Last Frame",18 },
		{ "Secondary Task Normal",32 },
		{ "Secondary Task Loop",33 },
		{ "Secondary Task Last Frame",34 },
		{ "UpperBody + ST Normal",48 },
		{ "UpperBody + ST Loop",49 },
		{ "UpperBody + ST Last Frame",50 }
	};
	std::string m_walk_on_air[] = {
	"Gravity Style",
	"Magic Carpet Style"
	};
	std::string m_outfit_editor_types[] = {
	"Head", "Beard", "Hair", "Torso", "Legs", "Hands", "Feet", "Chest", "Accessories", "Accessories 2", "Decals/masks", "Auxiliary parts"
	};
	ped_outfit_data outfit_editor_data[sizeof(m_outfit_editor_types) / sizeof(m_outfit_editor_types[0])];

	std::string m_outfit_editor_prop_types[] = {
	"Masks", "Glasses", "Ear accessories","Watches"
	};
	std::string m_super_run_types[] = {
	"Forwards", "Backwards",
	};
	std::string m_jump_force_offset[] = {
	"Forward", "Backward"
	};
	ped_outfit_data outfit_editor_prop_data[sizeof(m_outfit_editor_prop_types) / sizeof(m_outfit_editor_prop_types[0])];
	void start_particle(const char* dict, const char* texture, int id) {
		if (!STREAMING::HAS_NAMED_PTFX_ASSET_LOADED(dict)) {
			while (!STREAMING::HAS_NAMED_PTFX_ASSET_LOADED(dict)) {
				STREAMING::REQUEST_NAMED_PTFX_ASSET(dict);
				script::get_current()->yield();
			}

		}
		GRAPHICS::USE_PARTICLE_FX_ASSET(dict);
		GRAPHICS::START_NETWORKED_PARTICLE_FX_NON_LOOPED_ON_ENTITY(texture, globals::h_local_ped(), { 0, 0, 0 }, { 0, 0, 0 }, 0.5f, 0, 0, 0);

	}
}
namespace insight {	
	void script_ui::player() {
		render::push<sub>("Player", "Player"_joaat, [](sub* ui) {
			ui->push(submenu("Modifiers").add_target("Player_Modifiers"_joaat));
			ui->push(submenu("Movement").add_target("Player_Movement"_joaat));
			ui->push(submenu("Animations").add_target("Player_Animations"_joaat));	
			ui->push(submenu("Visuals").add_target("Player_Visuals"_joaat));
			ui->push(submenu("Abilities").add_target("Player_Abilities"_joaat));
			ui->push(info("General"));
			ui::push()->feature_toggle(ui, "player_never_wanted"_tf);
			ui::push()->feature_toggle_int(ui, "player_lock_wanted"_tif, 0, 5, 1, 0);
			ui::push()->array_feature_toggle(ui, "player_fast_respawn"_tif, m_player_fast_respawn_type, 2);
			ui::push()->array_feature_toggle(ui, "player_karama"_tif, m_player_karama_type, 2);
			ui->push(button("Sky Drive")
				.set_action([=] {
					tasks::get()->teleport_local_ped_to_pos(4, globals::h_local_ped(), globals::h_local_ped_pos(), 0);
					}));		
			ui->push(button("Kill Your Self")
				.set_action([=] {
					globals::c_local_ped()->m_health = 0;
					}));

		});

		render::push<sub>("Modifiers", "Player_Modifiers"_joaat, [](sub* ui) {
			ui::push()->feature_toggle(ui, "player_god_mode"_tf);
			ui::push()->array_feature_toggle(ui, "player_auto_heal"_tif, m_auto_heal_n_armor_type,4);
			if ("player_auto_heal"_tif->m_toggle_value.toggle)
			ui::push()->feature_int(ui, "player_auto_heal_rate"_if, 0, 2000, 50, 1);
			ui::push()->array_feature_toggle(ui, "player_auto_armor"_tif, m_auto_heal_n_armor_type,4);
			if ("player_auto_armor"_tif->m_toggle_value.toggle)
			ui::push()->feature_int(ui, "player_auto_armor_rate"_if, 0, 2000, 50, 1);
			ui::push()->array_feature_toggle(ui, "player_walk_on_air"_tif, m_walk_on_air, 2);

			ui->push(info("Flags")); 
			ui::push()->feature_toggle(ui, "player_walk_under_water"_tf);
			ui::push()->feature_toggle(ui, "player_swim_everywhere"_tf);
			ui::push()->feature_toggle(ui, "player_ignored_by_peds"_tf);
		});

		render::push<sub>("Player", "Player_Movement"_joaat, [](sub* ui) {
			ui->push(submenu("No Clip").add_target("Player_Noclip"_joaat));
			ui->push(submenu("Jumping").add_target("Player_Jumping"_joaat));
			ui::push()->feature_toggle_float(ui, "player_super_run"_tff, 0.1f, 100.f, 0.1f, 1);
			if ("player_super_run"_tff->m_toggle_value.toggle)
			ui->push(array<std::string, int>("player_super_run_type"_if->m_name).add_array(&m_super_run_types).
			add_position(&"player_super_run_type"_if->m_value.integer));
			ui::push()->feature_toggle_float(ui, "player_super_swim"_tff, 0.1f, 100.f, 0.1f, 1);
			ui::push()->feature_toggle_float(ui, "player_swim_modifier"_tff, 0.1f, 100.f, 0.1f, 1);
			ui::push()->feature_toggle_float(ui, "player_run_modifier"_tff, 0.1f, 100.f, 0.1f, 1);
			ui::push()->feature_toggle_float(ui, "player_super_man_flying"_tff, 0.1f, 10.f, 0.1f, 1);
			ui::push()->feature_toggle(ui, "player_graceful_landing"_tf);
			ui::push()->array_feature_toggle(ui, "player_no_ragdoll"_tif, m_no_ragdoll_type, 2);
			ui->push(info("Unphysical"));
			ui::push()->array_feature_toggle(ui, "player_free_cam"_tif, m_freecam_type, 2);
			});
		render::push<sub>("No Clip", "Player_Noclip"_joaat, [](sub* ui) {
			ui::push()->array_feature_toggle(ui, "player_no_clip"_tif, m_no_clip_type, 2);
			ui::push()->feature_float(ui, "player_no_clip_speed"_FF, 0.f, 100.f);
			if ("player_no_clip"_tif->m_number_value.integer == 0) {
				ui::push()->feature_toggle_float(ui, "player_no_clip_rotation"_tff, 0.f, 100.f, 1.f, 1);
				ui::push()->feature_float(ui, "player_no_clip_speed_ver"_FF, 0.f, 100.f);
				ui::push()->feature_float(ui, "player_no_clip_speed_lat"_FF, 0.f, 100.f);

			}else
			if ("player_no_clip"_tif->m_number_value.integer == 1) {
				ui::push()->feature_float(ui, "player_no_clip_speed_ver2"_FF, 0.f, 100.f);
				ui::push()->feature_float(ui, "player_no_clip_speed_lat2"_FF, 0.f, 100.f);
			}
			});
		render::push<sub>("Jumping", "Player_Jumping"_joaat, [](sub* ui) {
			ui::push()->array_feature_toggle(ui, "player_super_jump"_tif, m_super_jump_type, 3);
			ui::push()->feature_toggle(ui, "player_double_jumping"_tf);
			if (!"player_super_jump_360"_tff->m_toggle_value.toggle)
			ui::push()->feature_toggle_float(ui, "player_super_jump_ninja"_tff, -100.f, 100.f, 1.f, 1);
			if (!"player_super_jump_ninja"_tff->m_toggle_value.toggle)
			ui::push()->feature_toggle_float(ui, "player_super_jump_360"_tff, -100.f, 100.f, 1.f, 1);
			ui->push(info("Direction"));
			ui::push()->array_feature_toggle(ui, "player_super_jump_directional_force"_tif, m_jump_force_offset, 2);
			if ("player_super_jump_directional_force"_tif->m_toggle_value.toggle)
			ui::push()->feature_float(ui, "player_super_jump_directional_force_rate"_FF, 10.f, 100.f, 1.f);
			ui->push(info("Offsets"));
			ui::push()->feature_float(ui, "player_super_jump_x"_FF, -100.f, 100.f, 1.f);
			ui::push()->feature_float(ui, "player_super_jump_y"_FF, -100.f, 100.f, 1.f);
			ui::push()->feature_float(ui, "player_super_jump_z"_FF, -100.f, 100.f,1.f);

			});

		render::push<sub>("Animations", "Player_Animations"_joaat, [](sub* ui) {
			ui->push(submenu("Settings").add_target("Player_Animations_Settings"_joaat));
			ui->push(button("Stop")
				.set_action([=] {
					TASK::CLEAR_PED_TASKS(globals::h_local_ped());
					}));
			for (int i = 0; i < animations.size(); i++)
			{
				bool is_playing_anim = ENTITY::IS_ENTITY_PLAYING_ANIM(globals::h_local_ped(), animations[i].animation, animations[i].animationid,3);

				ui->push(button(is_playing_anim ? ("~r~" + animations[i].name) :animations[i].name)
					.set_action([=] {
						tasks::play_animation_with_settings(globals::h_local_ped(), animations[i].animation, animations[i].animationid,
						"player_animation_settings_blendin"_FF->m_value.floating_point, "player_animation_settings_blendout"_FF->m_value.floating_point, -1,
						animations_flags_selected, 0.0, false, false, false);
						}));
			}
			});		
		render::push<sub>("Animations Settings", "Player_Animations_Settings"_joaat, [](sub* ui) {
			ui::push()->feature_float(ui, "player_animation_settings_blendin"_FF, -8.0f, 8.0f);
			ui::push()->feature_float(ui, "player_animation_settings_blendout"_FF, -8.0f, 8.0f);
			ui->push(info("Flags"));
			for (int i = 0; i < animations_flags.size(); i++)
			{
				bool selected = animations_flags_selected == animations_flags[i].Value;
				ui->push(button(selected ? "~r~" + animations_flags[i].name:  animations_flags[i].name)
					.set_action([=] {
						animations_flags_selected = animations_flags[i].Value;
						}));
			}
			});

		render::push<sub>("Visuals", "Player_Visuals"_joaat, [](sub* ui) {
			ui->push(submenu("Wardrobe").add_target("Wardrobe"_joaat).set_action([=] {
				}));

			ui->push(submenu("Model").add_target("Player_Models"_joaat).set_action([=] {
				xml::get()->load_ped_models();
				script_utility::get()->ped_spawner_sub = 1;
				}));
			ui->push(submenu("Matrix").add_target("Player_Matrix"_joaat));
			ui->push(submenu("Visions").add_target("Player_Visions"_joaat));
			ui->push(submenu("Particles").add_target("Player_Particles"_joaat)); 
			ui->push(info("Misc"));
			ui::push()->array_feature_toggle(ui, "player_set_alpha"_tif, m_alpha_set, std::size(m_alpha_set));
			ui::push()->array_feature_toggle(ui, "player_drunk_mode"_tif, m_player_drunk_mode_type, 4);
			ui::push()->feature_toggle_float(ui, "player_wet_mode"_tff, 1.f, 300.f, 1.f, 1);
			ui::push()->feature_toggle_float(ui, "player_fov_modifier"_tff, 1.f, 300.f, 1.f, 1);
			ui::push()->feature_toggle(ui, "player_tiny_legs"_tf);
			ui::push()->feature_toggle(ui, "player_burning_man"_tf);
			ui::push()->feature_toggle(ui, "player_injured"_tf);
			ui::push()->feature_toggle(ui, "player_tiny_ped"_tf);
			ui::push()->feature_toggle(ui, "player_auto_clean"_tf);
			ui->push(button(xorstr_("Clean Ped"))
				.set_action([=] {		
					tasks::clean_ped(globals::h_local_ped());
				}));
			});
		render::push<sub>("Matrix", "Player_Matrix"_joaat, [](sub* ui) {
			ui::push()->feature_toggle_float(ui, "player_matrix_height"_tff, -10.f, 10.f, 0.1f, 3);
			ui::push()->feature_toggle_float(ui, "player_matrix_lean"_tff, -10.f, 10.f, 0.1f, 3);
			ui::push()->feature_toggle_float(ui, "player_matrix_width"_tff, -10.f, 10.f, 0.1f, 3);

			});
		render::push<sub>("Visions", "Player_Visions"_joaat, [](sub* ui) {
			for (int i = 0; i < visions.size(); i++) {
				bool is_vision_selected = Player_Visions_Selected == i;

				ui->push(button(is_vision_selected ? std::string("~r~" + std::string(visions[i].display_name)).c_str() : visions[i].display_name)
					.add_function([=] {
						Player_Visions_Selected = i;
						if (i == 0) { GRAPHICS::POP_TIMECYCLE_MODIFIER(); }
						else { GRAPHICS::SET_TIMECYCLE_MODIFIER(visions[i].real_name); }
						}));
			}
			});

		render::push<sub>("Particles", "Player_Particles"_joaat, [](sub* ui) {
			ui->push(submenu("Play Once").add_target("Player_Particles_Play_Once"_joaat));
			ui->push(info("Loop"));
			ui->push(submenu("Stomach").add_target("Player_Particles_Stomach"_joaat));
			ui->push(submenu("Head").add_target("Player_Particles_Head"_joaat));
			ui->push(submenu("Left Hand").add_target("Player_Particles_Lhand"_joaat));
			ui->push(submenu("Right Hand").add_target("Player_Particles_Rhand"_joaat));
			ui->push(submenu("Left Foot").add_target("Player_Particles_Lfoot"_joaat));
			ui->push(submenu("Right Foot").add_target("Player_Particles_Rfoot"_joaat));
			});		
		render::push<sub>("Stomach", "Player_Particles_Stomach"_joaat, [](sub* ui) {
			ui::push()->array_feature_toggle(ui, "playe_ptfx_stomach"_tif, particle_effects, std::size(particle_effects));
			ui::push()->feature_float(ui, "playe_ptfx_stomach_scale"_FF, 0.0f, 5.f, 0.1f, 1);
			ui::push()->feature_float(ui, "playe_ptfx_stomach_scale_d"_FF, 0.0f, 10.f, 0.1f, 1);			
			});	
		render::push<sub>("Head", "Player_Particles_Head"_joaat, [](sub* ui) {
			ui::push()->array_feature_toggle(ui, "playe_ptfx_head"_tif, particle_effects, std::size(particle_effects));
			ui::push()->feature_float(ui, "playe_ptfx_head_scale"_FF, 0.0f, 5.f, 0.1f, 1);
			ui::push()->feature_float(ui, "playe_ptfx_head_scale_d"_FF, 0.0f, 10.f, 0.1f, 1);		
			});
		render::push<sub>("Left Hand", "Player_Particles_Lhand"_joaat, [](sub* ui) {
			ui::push()->array_feature_toggle(ui, "playe_ptfx_l_hand"_tif, particle_effects, std::size(particle_effects));
			ui::push()->feature_float(ui, "playe_ptfx_l_hand_scale"_FF, 0.0f, 5.f, 0.1f, 1);
			ui::push()->feature_float(ui, "playe_ptfx_l_hand_scale_d"_FF, 0.0f, 10.f, 0.1f, 1);
			});
		render::push<sub>("Right Hand", "Player_Particles_Rhand"_joaat, [](sub* ui) {
			ui::push()->array_feature_toggle(ui, "playe_ptfx_r_hand"_tif, particle_effects, std::size(particle_effects));
			ui::push()->feature_float(ui, "playe_ptfx_r_hand_scale"_FF, 0.0f, 5.f, 0.1f, 1);
			ui::push()->feature_float(ui, "playe_ptfx_r_hand_scale_d"_FF, 0.0f, 10.f, 0.1f, 1);
			});		
		render::push<sub>("Left Foot", "Player_Particles_Lfoot"_joaat, [](sub* ui) {
			ui::push()->array_feature_toggle(ui, "playe_ptfx_l_foot"_tif, particle_effects, std::size(particle_effects));
			ui::push()->feature_float(ui, "playe_ptfx_l_foot_scale"_FF, 0.0f, 5.f, 0.1f, 1);
			ui::push()->feature_float(ui, "playe_ptfx_l_foot_scale_d"_FF, 0.0f, 10.f, 0.1f, 1);
			});
		render::push<sub>("Right Foot", "Player_Particles_Rfoot"_joaat, [](sub* ui) {
			ui::push()->array_feature_toggle(ui, "playe_ptfx_r_foot"_tif, particle_effects, std::size(particle_effects));
			ui::push()->feature_float(ui, "playe_ptfx_r_foot_scale"_FF, 0.0f, 5.f, 0.1f, 1);
			ui::push()->feature_float(ui, "playe_ptfx_r_foot_scale_d"_FF, 0.0f, 10.f, 0.1f, 1);			
			});

		render::push<sub>("Particles", "Player_Particles_Play_Once"_joaat, [](sub* ui) {

			for (int i = 0; i < particles.size(); i++) {
				ui->push(button(particles[i].name)
					.set_action([=] {
						start_particle(particles[i].dict, particles[i].texture, i);
					}));
			}
			});

		render::push<sub>("Abilities", "Player_Abilities"_joaat, [](sub* ui) {
			ui->push(submenu("Flash Mod").add_target("Flash_Mod"_joaat));
			ui->push(submenu("Ebouny Maw").add_target("Ebouny_Maw"_joaat));
			ui->push(submenu("Baba Yoga").add_target("Baba_Yoga"_joaat));
			ui->push(submenu("Hulk Jumping").add_target("HULK_JUMP"_joaat));
			ui->push(submenu("Flappy Bird").add_target("Flappy_Bird"_joaat));
			ui->push(submenu("Infamous Mod").add_target("Infamous_Mod"_joaat));
			ui->push(submenu("Quicksilver").add_target("Quick_silver"_joaat));
			ui->push(submenu("Aladdin Carpet").add_target("Aladdin_Magic"_joaat));
			ui->push(submenu("God Finger").add_target("God_Finger"_joaat));
			ui::push()->array_feature_toggle(ui, "player_invisible"_tif, m_invisible_type, 2);
			ui::push()->feature_toggle_float(ui, "player_force_field"_tff, 1.f, 100.f, 1.f, 0);
			ui::push()->feature_toggle_float(ui, "player_ultimate_parachuting"_tff, 1.f, 10.f, 0.5f, 1);
			ui::push()->array_feature_toggle(ui, "player_walk_thru"_tif, m_walk_thru_type, 4);	
		});		

		render::push<sub>("Hulk Jumping", "HULK_JUMP"_joaat, [](sub* ui) {
			ui::push()->feature_toggle(ui, "player_hulk_jumping"_tf);
			ui::push()->feature_float(ui, "player_hulk_jumping_height"_FF, 0.0f, 100.f, 0.1f, 1);

		});
		render::push<sub>("Flash Mode", "Flash_Mod"_joaat, [](sub* ui) {
			ui::push()->feature_toggle_float(ui, "player_flash_mode"_tff, 0.f, 100.f, 0.1f, 1);
			ui::push()->feature_toggle(ui, "flash_mode_trails"_tf);
			ui->push(info("Trail Color"));
			ui::push()->feature_int(ui, "flash_mode_color_1"_if, 0, 255, 1);
			ui::push()->feature_int(ui, "flash_mode_color_2"_if, 0, 255, 1);
			ui::push()->feature_int(ui, "flash_mode_color_3"_if, 0, 255, 1);
			panel color_preview(0.075f, 0.f, 0.022f);
			color_preview.start_panel("Trail Color");
			color_preview.push_rect(color("flash_mode_color_1"_if->m_value.integer, "flash_mode_color_2"_if->m_value.integer, "flash_mode_color_3"_if->m_value.integer), 0.05f);
			color_preview.end_panel();
		});
		render::push<sub>("Ebouny Maw", "Ebouny_Maw"_joaat, [](sub* ui) {
			ui::push()->feature_toggle(ui, "player_ebony_maw"_tf);
			ui::push()->feature_float(ui, "player_ebony_maw_idle_speed"_FF, 0.0f, 10.f, 0.1f, 1);
			ui::push()->feature_float(ui, "player_ebony_maw_idle_frq"_FF, 0.0f, 10.f, 0.1f, 1);
			ui::push()->feature_float(ui, "player_ebony_maw_throw_speed"_FF, 0.0f, 10.f, 0.1f, 1);
			ui::push()->feature_float(ui, "player_ebony_maw_throw_frq"_FF, 0.0f, 10.f, 0.1f, 1);
		});		
		render::push<sub>("Baba Yoga", "Baba_Yoga"_joaat, [](sub* ui) {
			ui::push()->array_feature_toggle(ui, "player_abilities_baba_yoga"_tif, m_player_bab_yoga_type, 2);
			ui::push()->feature_float(ui, "player_abilities_baba_yoga_rotation_speed"_FF, 0.0f, 10.f, 0.1f, 1);
			ui::push()->feature_float(ui, "player_abilities_baba_yoga_speed_multiplier"_FF, 0.0f, 10.f, 0.1f, 1);
			ui::push()->feature_float(ui, "player_abilities_baba_yoga_zspeed_multiplier"_FF, 0.0f, 10.f, 0.1f, 1);
			});		

		render::push<sub>("Flappy Bird", "Flappy_Bird"_joaat, [](sub* ui) {
			ui::push()->feature_toggle(ui, "flappy_bird"_tf);
			ui::push()->feature_float(ui, "flappy_bird_vertical_force"_FF, 0.0f, 100.f, 1.f, 1);
			ui::push()->feature_float(ui, "flappy_bird_horizontal_force"_FF, 0.0f, 100.f, 1.f, 1);
			ui::push()->feature_float(ui, "flappy_bird_up_force"_FF, 0.0f, 100.f, 1.f, 1);
			ui::push()->feature_float(ui, "flappy_bird_up_speed"_FF, 0.0f, 10.f, 0.1f, 1);
			});
		render::push<sub>("Infamous Mod", "Infamous_Mod"_joaat, [](sub* ui) {
			ui::push()->feature_toggle(ui, "player_infamous_mode"_tf);
			ui::push()->feature_toggle(ui, "player_infamous_mode_owned_damage"_tf);
			ui::push()->feature_toggle(ui, "player_infamous_mode_exp_sound"_tf);
			ui::push()->feature_toggle(ui, "player_infamous_mode_exp_visible"_tf);
			ui::push()->feature_float(ui, "player_infamous_mode_shotting_force"_FF, 0.0f, 100.f, 0.1f, 1);
			ui::push()->feature_float(ui, "player_infamous_mode_flying_multiplier"_FF, 0.0f, 100.f, 0.1f, 1);

			});
		render::push<sub>("Quicksilver", "Quick_silver"_joaat, [](sub* ui) {
			ui::push()->feature_toggle(ui, "player_flash_sprint"_tf);
			ui::push()->feature_toggle(ui, "player_flash_sprint_air"_tf);
			ui::push()->feature_float(ui, "player_flash_sprint_speed"_FF, 0.0f, 100.f, 0.1f, 1);
			ui::push()->feature_float(ui, "player_flash_sprint_fov"_FF, 0.0f, 100.f, 0.1f, 1);		
			});
		render::push<sub>("Aladdin Carpet", "Aladdin_Magic"_joaat, [](sub* ui) {
			ui::push()->feature_toggle(ui, "player_aladdin_magic_carpet"_tf);
			ui::push()->feature_float(ui, "player_aladdin_magic_carpet_speed"_FF, 0.0f, 100.f, 0.1f, 1);

			});
		render::push<sub>("God Finger", "God_Finger"_joaat, [](sub* ui) {
			ui::push()->feature_toggle_float(ui, "god_finger"_tff, 0.f, 10.f, 0.5f, 1);
			ui::push()->feature_float(ui, "god_finger_distance"_FF, 0.0f, 50.f, 1.f, 1);
			});
	
		render::push<sub>("Wardrobe", "Wardrobe"_joaat, [](sub* ui) {
			ui->push(submenu("Editor").add_target("Wardrobe_Editor"_joaat)); 
			ui->push(info("Saved"));

			auto path = std::filesystem::path(std::getenv("appdata")).append("insight").append("xml").append("outfits");
			if (std::filesystem::exists(path)) {
				std::filesystem::directory_iterator it{ path };
				for (auto&& entry : it) {
					if (entry.is_regular_file()) {
						auto path{ entry.path() };
						if (path.has_filename() && path.extension() == ".xml") {
							ui->push(button(path.stem().string())
								.set_action([=] {
									xml::get()->wardrobe_load(path.generic_string());
									}));

						}
					}
				}
			}
			});
		render::push<sub>("Wardrobe", "Wardrobe_Editor"_joaat, [](sub* ui) {

			ui->push(submenu("Clothes").add_target("Wardrobe_Editor_Components"_joaat));
			ui->push(submenu("Props").add_target("Wardrobe_Editor_Props"_joaat));

	

			ui->push(button("Save")
				.set_action([=] {
					xml::get()->wardrobe_save(tasks::get_keyboard_input().c_str());
					}));

			});
		render::push<sub>("Components", "Wardrobe_Editor_Components"_joaat, [](sub* ui) {

			for (int i = 0; i < sizeof(m_outfit_editor_types) / sizeof(m_outfit_editor_types[0]); i++)
			{
				outfit_editor_data[i] = tasks::get_ped_outfit_data(globals::h_local_ped(), i);
				ui->push(number<int>(m_outfit_editor_types[i]).add_number(&outfit_editor_data[i].texture_id).add_min(0).add_max(outfit_editor_data[i].number_of_textures).add_precision(1).add_step(1).set_action([=] {
					PED::SET_PED_COMPONENT_VARIATION(globals::h_local_ped(), i, outfit_editor_data[i].texture_id, outfit_editor_data[i].variation, 0);
					outfit_editor_data[i].variation = 0; // it needs to be reset cuz; it has to :(
					}));
				ui->push(number<int>(std::string(m_outfit_editor_types[i] + " Variation").c_str()).add_number(&outfit_editor_data[i].variation).add_min(0).add_max(outfit_editor_data[i].number_of_variations).add_precision(1).add_step(1).set_action([=] {
					PED::SET_PED_COMPONENT_VARIATION(globals::h_local_ped(), i, outfit_editor_data[i].texture_id, outfit_editor_data[i].variation, 0);
					}));

			}
			});
		render::push<sub>("Props", "Wardrobe_Editor_Props"_joaat, [](sub* ui) {

			for (int i = 0; i < sizeof(m_outfit_editor_prop_types) / sizeof(m_outfit_editor_prop_types[0]); i++)
			{
				outfit_editor_prop_data[i] = tasks::get_ped_outfit_prop_data(globals::h_local_ped(), i);
				ui->push(number<int>(m_outfit_editor_prop_types[i]).add_number(&outfit_editor_prop_data[i].texture_id).add_min(0).add_max(outfit_editor_prop_data[i].number_of_textures).add_precision(1).add_step(1).set_action([=] {
					PED::SET_PED_PROP_INDEX(globals::h_local_ped(), i, outfit_editor_prop_data[i].texture_id, outfit_editor_prop_data[i].variation, 0);
					outfit_editor_prop_data[i].variation = 0;
					}));
				ui->push(number<int>(std::string(m_outfit_editor_prop_types[i] + " Variation").c_str()).add_number(&outfit_editor_prop_data[i].variation).add_min(0).add_max(outfit_editor_prop_data[i].number_of_variations).add_precision(1).add_step(1).set_action([=] {
					PED::SET_PED_PROP_INDEX(globals::h_local_ped(), i, outfit_editor_prop_data[i].texture_id, outfit_editor_prop_data[i].variation, 0);
					}));

			}
			});
	}
}