#include "../manager/manager.h"


namespace insight {
	extern void null_feature_toggle(toggle_feature* feature, bool& value);
	extern void null_feature_float(float_feature* feature, float& value);
	extern void null_feature_int_toggle(toggle_int_feature* feature, bool& value, int& value2);
	extern  void null_feature_float_toggle(toggle_float_feature* feature, bool& value, float& value2);
	extern void null_feature_u64(u64_feature* feature, u64& value);
	extern void null_feature_int(int_feature* feature, int& value);

	class self {
	public: // self 
		static void god_mode(toggle_feature* feature, bool& value);
		static void fast_respawn(toggle_int_feature* feature, bool& value, int& value2);
		static void no_ragdoll(toggle_int_feature* feature, bool& value, int& value2);
		static void never_wanted(toggle_feature* feature, bool& value);
		static void lock_wanted_level(toggle_int_feature* feature, bool& value, int& value2);
		static void invisible(toggle_int_feature* feature, bool& value, int& value2);
		static void wall_runner(toggle_feature* feature, bool& value);
		static void karama(toggle_int_feature* feature, bool& value, int& value2);
		static void super_run(toggle_float_feature* feature, bool& value, float& value2);
		static void flash_sprint(toggle_feature* feature, bool& value);
		static void super_swim(toggle_float_feature* feature, bool& value, float& value2);
		static void run_modifier(toggle_float_feature* feature, bool& value, float& value2);
		static void swim_modifier(toggle_float_feature* feature, bool& value, float& value2);
		static void super_jump(toggle_int_feature* feature, bool& value, int& value2);
		static void no_clip(toggle_int_feature* feature, bool& value, int& value2);
		static void no_clip_speed(float_feature* feature, float& value);
		static void free_cam(toggle_int_feature* feature, bool& value, int& value2);
		static void force_field(toggle_float_feature* feature, bool& value, float& value2);
		static void drunk_mode(toggle_int_feature* feature, bool& value, int& value2);
		static void baba_yoga(toggle_int_feature* feature, bool& value, int& value2);
		static void walk_under_water(toggle_feature* feature, bool& value);
		static void swim_everywhere(toggle_feature* feature, bool& value);
		static void tiny_ped(toggle_feature* feature, bool& value);
		static void wet_mode(toggle_float_feature* feature, bool& value, float& value2);
		static void ingored_by_peds(toggle_feature* feature, bool& value);
		static void injured(toggle_feature* feature, bool& value);
		static void ebony_maw(toggle_feature* feature, bool& value);
		static void infamous_mode(toggle_feature* feature, bool& value);
		static void flappy_bird(toggle_feature* feature, bool& value);
		static void auto_heal(toggle_int_feature* feature, bool& value, int& value2);
		static void auto_armor(toggle_int_feature* feature, bool& value, int& value2);
		static void mobile_radio(toggle_feature* feature, bool& value);
		static void walk_on_air(toggle_int_feature* feature, bool& value, int& value2);
		static void auto_clean(toggle_feature* feature, bool& value);
		static void walk_thru(toggle_int_feature* feature, bool& value, int& value2);
		static void burning_man(toggle_feature* feature, bool& value);
		static void alladin_carpet(toggle_feature* feature, bool& value);
		static void fov_modifier(toggle_float_feature* feature, bool& value, float& value2);
		static void matrix_lean(toggle_float_feature* feature, bool& value, float& value2);
		static void matrix_width(toggle_float_feature* feature, bool& value, float& value2);
		static void matrix_height(toggle_float_feature* feature, bool& value, float& value2);
		static void tiny_legs(toggle_feature* feature, bool& value);
		static void ultimate_parachuting(toggle_float_feature* feature, bool& value, float& value2);
		static void god_finger(toggle_float_feature* feature, bool& value, float& value2);
		static void graceful_landing(toggle_feature* feature, bool& value);
		static void super_man_flying(toggle_float_feature* feature, bool& value, float& value2);
		static void double_jumping(toggle_feature* feature, bool& value);
		static void hulking_jumping(toggle_feature* feature, bool& value);
		static void laser_eyes(toggle_feature* feature, bool& value);

		static void self_ptfx_stomach(toggle_int_feature* feature, bool& value, int& value2);
		static void self_ptfx_head(toggle_int_feature* feature, bool& value, int& value2);
		static void self_ptfx_left_hand(toggle_int_feature* feature, bool& value, int& value2);
		static void self_ptfx_right_hand(toggle_int_feature* feature, bool& value, int& value2);
		static void self_ptfx_left_foot(toggle_int_feature* feature, bool& value, int& value2);
		static void self_ptfx_right_foot(toggle_int_feature* feature, bool& value, int& value2);
		static void flash_mode(toggle_float_feature* feature, bool& value, float& value2);
		static void self_ped_alphha(toggle_int_feature* feature, bool& value, int& value2);

	public:
		static self* get() {
			static self i{};
			return &i;
		}
	public:
		static void set_values() {
			"player_no_clip_speed"_FF->m_value.floating_point = 1.f;
			"player_run_modifier"_tif->m_number_value.floating_point = 1.f;
			"player_swim_modifier"_tif->m_number_value.floating_point = 1.f;
			"player_super_run"_tif->m_number_value.floating_point = 1.f;
			"player_super_swim"_tif->m_number_value.floating_point = 1.f;

			"player_animation_settings_blendin"_FF->m_value.floating_point = 8.0f;
			"player_animation_settings_blendout"_FF->m_value.floating_point = 8.0f;

			"player_fov_modifier"_tif->m_number_value.floating_point = 55.f;
			"player_matrix_height"_tif->m_number_value.floating_point = 0.f;
			"player_super_swim"_tif->m_number_value.floating_point = 1.f;

			"god_finger"_tif->m_number_value.floating_point = 1.5f;
			"god_finger_distance"_FF->m_value.floating_point = 15.f;

			"playe_ptfx_stomach_scale"_FF->m_value.floating_point = 1.0f;
			"playe_ptfx_head_scale"_FF->m_value.floating_point = 1.0f;
			"playe_ptfx_l_hand_scale"_FF->m_value.floating_point = 1.0f;
			"playe_ptfx_r_hand_scale"_FF->m_value.floating_point = 1.0f;
			"playe_ptfx_l_foot_scale"_FF->m_value.floating_point = 1.0f;
			"playe_ptfx_r_foot_scale"_FF->m_value.floating_point = 1.0f;

			"playe_ptfx_stomach_scale_d"_FF->m_value.floating_point = 1.0f;
			"playe_ptfx_head_scale_d"_FF->m_value.floating_point = 1.0f;
			"playe_ptfx_l_hand_scale_d"_FF->m_value.floating_point = 1.0f;
			"playe_ptfx_r_hand_scale_d"_FF->m_value.floating_point = 1.0f;
			"playe_ptfx_l_foot_scale_d"_FF->m_value.floating_point = 1.0f;
			"playe_ptfx_r_foot_scale_d"_FF->m_value.floating_point = 1.0f;

			"player_ultimate_parachuting"_tff->m_number_value.floating_point = 1.0f;

			"player_wet_mode"_tff->m_number_value.floating_point = 100.f;
			"player_super_man_flying"_tff->m_number_value.floating_point = 1.f;

			"player_auto_heal_rate"_if->m_value.integer = 50;
			"player_auto_armor_rate"_if->m_value.integer = 50;
			"player_super_jump_directional_force_rate"_FF->m_value.floating_point = 20.f;

			"player_super_jump_ninja"_tff->m_number_value.floating_point = 5.0f;
			"player_super_jump_360"_tff->m_number_value.floating_point = 5.0f;
			"player_no_clip_speed_ver"_FF->m_value.floating_point = 1.0f;
			"player_no_clip_speed_lat"_FF->m_value.floating_point = 1.0f;
			"player_no_clip_speed_ver2"_FF->m_value.floating_point = 1.0f;
			"player_no_clip_speed_lat2"_FF->m_value.floating_point = 1.0f;
			"player_no_clip_rotation"_tff->m_toggle_value.toggle = true;
			"player_no_clip_rotation"_tff->m_number_value.floating_point = 5.f;
			"flash_mode_color_1"_if->m_value.integer = 255;


			"player_ebony_maw_idle_speed"_FF->m_value.floating_point = 2.9f;
			"player_ebony_maw_idle_frq"_FF->m_value.floating_point = 0.1f;
			"player_ebony_maw_throw_speed"_FF->m_value.floating_point = 5.0f;
			"player_ebony_maw_throw_frq"_FF->m_value.floating_point = 0.2f;
			"player_abilities_baba_yoga_rotation_speed"_FF->m_value.floating_point = 5.0f;
			"player_abilities_baba_yoga_speed_multiplier"_FF->m_value.floating_point = 1.0f;
			"player_abilities_baba_yoga_zspeed_multiplier"_FF->m_value.floating_point = 1.0f;

			"flappy_bird_vertical_force"_FF->m_value.floating_point = 20.0f;
			"flappy_bird_horizontal_force"_FF->m_value.floating_point = 20.0f;
			"flappy_bird_up_force"_FF->m_value.floating_point = 20.0f;
			"flappy_bird_up_speed"_FF->m_value.floating_point = 0.6f;

			"player_infamous_mode_shotting_force"_FF->m_value.floating_point = 1.0f;
			"player_infamous_mode_flying_multiplier"_FF->m_value.floating_point = 1.0f;

			"player_flash_sprint_speed"_FF->m_value.floating_point = 5.0f;
			"player_flash_sprint_fov"_FF->m_value.floating_point = 1.0f;
			"player_aladdin_magic_carpet_speed"_FF->m_value.floating_point = 1.5f;
			"flash_mode_trails"_tf->m_value.toggle = true;
			"player_infamous_mode_exp_sound"_tf->m_value.toggle = true;
			"player_infamous_mode_exp_visible"_tf->m_value.toggle = true;

			"player_hulk_jumping_height"_FF->m_value.floating_point = 50.f;
		}

		static void initialize() {
			feature_manager::get()->add(toggle_feature("player_god_mode", "God Mode", "Player Never Dies", self::god_mode), "self");
			feature_manager::get()->add(toggle_int_feature("player_fast_respawn", "Fast Respawn", "Player Spawns Instantly On Death", self::fast_respawn), "self");
			feature_manager::get()->add(toggle_int_feature("player_no_ragdoll", "No Ragdoll", "Disables Player Ragdoll", self::no_ragdoll), "self");
			feature_manager::get()->add(toggle_feature("player_never_wanted", "Never Wanted", "As The Name Suggests", self::never_wanted), "self");
			feature_manager::get()->add(toggle_int_feature("player_lock_wanted", "Lock Wanted Level", "Freezes The Player Wanted Level", self::lock_wanted_level), "self");
			feature_manager::get()->add(toggle_int_feature("player_invisible", "Invisible", "Makes Your Player Invisible.", self::invisible), "self");
			feature_manager::get()->add(toggle_int_feature("player_karama", "Karama", "Kills What Ever Kill You.", self::karama), "self");
			feature_manager::get()->add(toggle_float_feature("player_super_run", "Super Run", "Wind Push Your Player To Make You Run Faster.", self::super_run), "self");
			feature_manager::get()->add(int_feature("player_super_run_type", "Super Run Direction", "As The Name Suggests", null_feature_int), "self");
			feature_manager::get()->add(toggle_feature("player_wall_runner", "Wall Runner", "Being Able To Run On Wallsh.", self::wall_runner), "self");
			feature_manager::get()->add(int_feature("flash_mode_color_1", "Red", null_feature_int), "self");
			feature_manager::get()->add(int_feature("flash_mode_color_2", "Green", null_feature_int), "self");
			feature_manager::get()->add(int_feature("flash_mode_color_3", "Blue", null_feature_int), "self");
			feature_manager::get()->add(toggle_feature("flash_mode_trails", "Trails", null_feature_toggle), "self");
			feature_manager::get()->add(toggle_float_feature("player_flash_mode", "Flash Mode", "Run Like The Flash On The Ground,Sea,Air.", self::flash_mode), "self");

			feature_manager::get()->add(toggle_feature("player_flash_sprint_air", "Air Mode", "Allows You On Run On Air.", null_feature_toggle), "self");
			feature_manager::get()->add(toggle_feature("player_flash_sprint", "Quicksilver Sprint", "Run in a quckicky way.", self::flash_sprint), "self");
			feature_manager::get()->add(float_feature("player_flash_sprint_speed", "Quicksilver Speed Multiplier", "Increase The Speed.", null_feature_float), "self");
			feature_manager::get()->add(float_feature("player_flash_sprint_fov", "Fov Multiplier", "Sets Camera Fov.", null_feature_float), "self");

			feature_manager::get()->add(toggle_float_feature("player_super_swim", "Super Swim", "Wind Push Your Player To Make You Swim Faster.", self::super_swim), "self");
			feature_manager::get()->add(toggle_float_feature("player_swim_modifier", "Swim Speed", "Changes The Player Swim Speed Directly.", self::swim_modifier), "self");
			feature_manager::get()->add(toggle_float_feature("player_run_modifier", "Run Speed", "Changes The Player Run Speed Directly.", self::run_modifier), "self");
			feature_manager::get()->add(toggle_float_feature("player_force_field", "Forcefield", "Pushes Peds And Vehicles Away.", self::force_field), "self");
			feature_manager::get()->add(toggle_float_feature("player_super_jump_ninja", "Ninja Animation", "Ninjaing.", null_feature_float_toggle), "self");
			feature_manager::get()->add(toggle_float_feature("player_super_jump_360", "360 Animation", "360ing.", null_feature_float_toggle), "self");
			feature_manager::get()->add(toggle_int_feature("player_super_jump_directional_force", "Direction", "As The Name Suggests.", null_feature_int_toggle), "self");

			feature_manager::get()->add(float_feature("player_super_jump_directional_force_rate", "Direction Rate", "Set The Amount Of Force.", null_feature_float), "self");
			feature_manager::get()->add(float_feature("player_super_jump_x", "X", "Set Custom X Force.", null_feature_float), "self");
			feature_manager::get()->add(float_feature("player_super_jump_y", "Y", "Set Custom Y Force.", null_feature_float), "self");
			feature_manager::get()->add(float_feature("player_super_jump_z", "Z", "Set Custom Z Force.", null_feature_float), "self");


			feature_manager::get()->add(toggle_int_feature("player_no_clip", "No Clip", "Absence Of Physics, While Changing Position.", self::no_clip), "self");
			feature_manager::get()->add(float_feature("player_no_clip_speed", "No Clip Speed ", "As The Speed Of No Clipping.", null_feature_float), "self");
			feature_manager::get()->add(toggle_float_feature("player_no_clip_rotation", "Rotation", "Creates 360 Rotation", null_feature_float_toggle), "self");
			feature_manager::get()->add(float_feature("player_no_clip_speed_ver", "Vertical Move Speed ", "Sets Vertical Speed.", null_feature_float), "self");
			feature_manager::get()->add(float_feature("player_no_clip_speed_lat", "Lateral Move Speed ", "Sets Lateral Speed.", null_feature_float), "self");
			feature_manager::get()->add(float_feature("player_no_clip_speed_ver2", "Vertical Move Speed ", "Sets Vertical Speed.", null_feature_float), "self");
			feature_manager::get()->add(float_feature("player_no_clip_speed_lat2", "Lateral Move Speed ", "Sets Lateral Speed.", null_feature_float), "self");
			feature_manager::get()->add(toggle_int_feature("player_free_cam", "Free Cam", "Move Where Ever You Want Without Limits.", self::free_cam), "self");
			feature_manager::get()->add(toggle_int_feature("player_drunk_mode", "Drunk", "Makes Your Ped Drunk.", self::drunk_mode), "self");
			feature_manager::get()->add(toggle_int_feature("player_abilities_baba_yoga", "Baba Yoga", "Become A God Now You Decide Who Lives", self::baba_yoga), "self");
			feature_manager::get()->add(float_feature("player_abilities_baba_yoga_rotation_speed", "Rotation Speed ", "Sets Rotation Speed.", null_feature_float), "self");
			feature_manager::get()->add(float_feature("player_abilities_baba_yoga_speed_multiplier", "Speed Multiplier", "Multiplies Speed.", null_feature_float), "self");
			feature_manager::get()->add(float_feature("player_abilities_baba_yoga_zspeed_multiplier", "Height Speed Multiplier", "Multiplies Speed.", null_feature_float), "self");


			feature_manager::get()->add(toggle_feature("player_walk_under_water", "Walk Underwater", "As The Name Suggests", self::walk_under_water), "self");
			feature_manager::get()->add(toggle_feature("player_swim_everywhere", "Swim Everywhere", "As The Name Suggests", self::swim_everywhere), "self");
			feature_manager::get()->add(toggle_feature("player_graceful_landing", "Gracefull Landing", "Land Gracefully Fr", self::graceful_landing/*:(*/), "self");
			feature_manager::get()->add(toggle_float_feature("player_super_man_flying", "Superman Flying", "Adjust Speed & Fly", self::super_man_flying), "self");
			feature_manager::get()->add(toggle_feature("player_double_jumping", "JumpStack", "Leap to New Heights with Multiple Jumps!", self::double_jumping/*:(*/), "self");
			feature_manager::get()->add(toggle_feature("player_hulk_jumping", "Hulk Jumping", "Make far & greater jumps", self::hulking_jumping), "self");
			feature_manager::get()->add(float_feature("player_hulk_jumping_height", "Height Boost", "Multiplies the height.", null_feature_float), "self");

			feature_manager::get()->add(toggle_feature("player_tiny_ped", "Tiny Player", "Makes Your Ped Smaller", self::tiny_ped), "self");
			feature_manager::get()->add(toggle_float_feature("player_wet_mode", "Wetness", "Get Your Ped Wet", self::wet_mode), "self");
			feature_manager::get()->add(toggle_feature("player_ignored_by_peds", "Ignored By Peds", "You Don't Exist For Peds Do You", self::ingored_by_peds), "self");


			feature_manager::get()->add(toggle_feature("player_infamous_mode", "Infamous Mode", "Enable Infamous Mode?", self::infamous_mode), "self");
			feature_manager::get()->add(float_feature("player_infamous_mode_shotting_force", "Throw Frequency", "Default: 1.0", null_feature_float), "self");
			feature_manager::get()->add(toggle_feature("player_infamous_mode_owned_damage", "Owned Damage", "Damges as you kill them.", null_feature_toggle), "self");
			feature_manager::get()->add(toggle_feature("player_infamous_mode_exp_sound", "Explosion Sound", "Set Explosion Sound..", null_feature_toggle), "self");
			feature_manager::get()->add(toggle_feature("player_infamous_mode_exp_visible", "Explosion Visible", "Change Explosion Visibility.", null_feature_toggle), "self");
			feature_manager::get()->add(float_feature("player_infamous_mode_flying_multiplier", "Flying Multiplier", "Default: 1.0", null_feature_float), "self");

			feature_manager::get()->add(toggle_feature("player_ebony_maw", "Ebony Maw", "Become One Of Thanos's Childen.", self::ebony_maw), "self");
			feature_manager::get()->add(float_feature("player_ebony_maw_idle_speed", "Idle Speed", "Default Speed Is 5.0", null_feature_float), "self");
			feature_manager::get()->add(float_feature("player_ebony_maw_idle_frq", "Idle Frequency", "Default Frequency Is 0.2", null_feature_float), "self");
			feature_manager::get()->add(float_feature("player_ebony_maw_throw_speed", "Throw Speed", "Default Speed Is 5.0", null_feature_float), "self");
			feature_manager::get()->add(float_feature("player_ebony_maw_throw_frq", "Throw Frequency", "Default Speed Is 0.2", null_feature_float), "self");


			feature_manager::get()->add(toggle_feature("flappy_bird", "Enable Flappy Bird Mode", "Leg sensation.", self::flappy_bird), "self");
			feature_manager::get()->add(float_feature("flappy_bird_vertical_force", "Vertical Force", "Adjust vertical force.", null_feature_float), "self");
			feature_manager::get()->add(float_feature("flappy_bird_horizontal_force", "Horizontal Force", "Adjust horizontal force.", null_feature_float), "self");
			feature_manager::get()->add(float_feature("flappy_bird_up_force", "Upward Force", "Adjust upward force.", null_feature_float), "self");
			feature_manager::get()->add(float_feature("flappy_bird_up_speed", "Force Speed", "Modify force speed. Default: 0.6", null_feature_float), "self");

			feature_manager::get()->add(toggle_feature("player_injured", "Injured", "You Broke Your Leg Right !?", self::injured), "self");
			feature_manager::get()->add(toggle_int_feature("player_auto_heal", "Auto Heal", "Heal Your Ped Gradually", self::auto_heal), "self");
			feature_manager::get()->add(int_feature("player_auto_heal_rate", "Healing Rate", "Speed Of Health Regeneration.", null_feature_int), "self");

			feature_manager::get()->add(toggle_int_feature("player_auto_armor", "Auto Armor", "Add Armor To Your Ped", self::auto_armor), "self");
			feature_manager::get()->add(int_feature("player_auto_armor_rate", "Armor Rate", "Speed Of Armor Regeneration.", null_feature_int), "self");

			feature_manager::get()->add(toggle_int_feature("player_walk_on_air", "Walk On Air", "Its Like a Magic Carpet Innit !?", self::walk_on_air), "self");
			feature_manager::get()->add(toggle_feature("player_auto_clean", "Auto Clean", "Straight Out Of A Shower", self::auto_clean), "self");
			feature_manager::get()->add(toggle_feature("player_mobile_radio", "Mobile Radio", "Have A Radio On Your Phone", self::mobile_radio), "self");
			feature_manager::get()->add(float_feature("player_animation_settings_blendin", "Blend In Speed", "Normal Speed Is 8.0", null_feature_float), "self");
			feature_manager::get()->add(float_feature("player_animation_settings_blendout", "Blend Out Speed", "Normal Speed Is 8.0", null_feature_float), "self");
			feature_manager::get()->add(toggle_int_feature("player_walk_thru", "Walk Thru", "As The Name Suggests.", walk_thru), "self");

			feature_manager::get()->add(toggle_feature("player_burning_man", "Burning Man", "Sets Fire On Your Ped", self::burning_man), "self");
			feature_manager::get()->add(toggle_feature("player_aladdin_magic_carpet", "Aladdin Magic Ride", "Jump To Use It.", self::alladin_carpet), "self");
			feature_manager::get()->add(float_feature("player_aladdin_magic_carpet_speed", "Speed Mutliplier", "Increase The Speed", null_feature_float), "self");

			feature_manager::get()->add(toggle_float_feature("player_fov_modifier", "Change Fov", "Changes Your Gameplay Cam's Fov.", self::fov_modifier), "self");
			feature_manager::get()->add(toggle_float_feature("player_matrix_height", "Height", "Changes Your Gameplay Cam's Fov.", self::matrix_height), "self");
			feature_manager::get()->add(toggle_float_feature("player_matrix_lean", "Lean", "Changes Your Gameplay Cam's Fov.", self::matrix_lean), "self");
			feature_manager::get()->add(toggle_float_feature("player_matrix_width", "Width", "Changes Your Gameplay Cam's Fov.", self::matrix_width), "self");
			feature_manager::get()->add(toggle_feature("player_tiny_legs", "Tiny Legs", "Legs Are Smaller.", self::tiny_legs), "self");
			feature_manager::get()->add(toggle_float_feature("player_ultimate_parachuting", "Ultimate Parachuting", "Parachute As Long As You Want.", self::ultimate_parachuting), "self");
			feature_manager::get()->add(toggle_float_feature("god_finger", "God Finger", "Point At Something TO Pick It Up.Adjust Speed Here.", self::god_finger), "self");
			feature_manager::get()->add(float_feature("god_finger_distance", "Distance", "Set How Far Entity Should Be When Picked.", null_feature_float), "self");

			feature_manager::get()->add(toggle_feature("player_laser_eyes", "Laser Eyes", "Like SuperMan.", self::laser_eyes), "self");

			feature_manager::get()->add(toggle_int_feature("playe_ptfx_stomach", "Enable", "As The Name Suggests.", self::self_ptfx_stomach), "self");
			feature_manager::get()->add(float_feature("playe_ptfx_stomach_scale", "Scale", "As The Name Suggests.", null_feature_float), "self");
			feature_manager::get()->add(float_feature("playe_ptfx_stomach_scale_d", "Delay", "As The Name Suggests.", null_feature_float), "self");

			feature_manager::get()->add(toggle_int_feature("playe_ptfx_head", "Enable", "As The Name Suggests.", self::self_ptfx_head), "self");
			feature_manager::get()->add(float_feature("playe_ptfx_head_scale", "Scale", "As The Name Suggests.", null_feature_float), "self");
			feature_manager::get()->add(float_feature("playe_ptfx_head_scale_d", "Delay", "As The Name Suggests.", null_feature_float), "self");

			feature_manager::get()->add(toggle_int_feature("playe_ptfx_l_hand", "Enable", "As The Name Suggests.", self::self_ptfx_left_hand), "self");
			feature_manager::get()->add(float_feature("playe_ptfx_l_hand_scale", "Scale", "As The Name Suggests.", null_feature_float), "self");
			feature_manager::get()->add(float_feature("playe_ptfx_l_hand_scale_d", "Delay", "As The Name Suggests.", null_feature_float), "self");

			feature_manager::get()->add(toggle_int_feature("playe_ptfx_r_hand", "Enable", "As The Name Suggests.", self::self_ptfx_right_hand), "self");
			feature_manager::get()->add(float_feature("playe_ptfx_r_hand_scale", "Scale", "As The Name Suggests.", null_feature_float), "self");
			feature_manager::get()->add(float_feature("playe_ptfx_r_hand_scale_d", "Delay", "As The Name Suggests.", null_feature_float), "self");

			feature_manager::get()->add(toggle_int_feature("playe_ptfx_l_foot", "Enable", "As The Name Suggests.", self::self_ptfx_left_foot), "self");
			feature_manager::get()->add(float_feature("playe_ptfx_l_foot_scale", "Scale", "As The Name Suggests.", null_feature_float), "self");
			feature_manager::get()->add(float_feature("playe_ptfx_l_foot_scale_d", "Delay", "As The Name Suggests.", null_feature_float), "self");

			feature_manager::get()->add(toggle_int_feature("playe_ptfx_r_foot", "Enable", "As The Name Suggests.", self::self_ptfx_right_foot), "self");
			feature_manager::get()->add(float_feature("playe_ptfx_r_foot_scale", "Scale", "As The Name Suggests.", null_feature_float), "self");
			feature_manager::get()->add(float_feature("playe_ptfx_r_foot_scale_d", "Delay", "As The Name Suggests.", null_feature_float), "self");

			set_values();
			feature_manager::get()->add(toggle_int_feature("player_super_jump", "Enable", "As The Name Suggests.", self::super_jump), "self");
			feature_manager::get()->add(toggle_int_feature("player_set_alpha", "Change Alpha", "As The Name Suggests.", self::self_ped_alphha), "self");
		}
	};
}