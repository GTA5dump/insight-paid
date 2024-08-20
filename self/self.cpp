#include "self.hpp"
#include "natives.hpp"
#include "../globals.hpp"
#include "util/script/script.hpp"
#include "../tasks.hpp"
#include "util/notify/notify.hpp"
#include "util/math/math.hpp"
#include "util/input/input.hpp"
#include "../scripted_globals.hpp"
#include "util/ptfx_bullet/ptfx_bullet.hpp"
namespace insight {
	bool was_wet_mode_on = false;
	void self::wet_mode(toggle_float_feature* feature, bool& value, float& value2) {
		if (!value) {
			if (was_wet_mode_on) {
				PED::SET_PED_WETNESS_ENABLED_THIS_FRAME(false);
				PED::SET_PED_WETNESS_HEIGHT(globals::h_local_ped(), 0.f);
				PED::CLEAR_PED_WETNESS(globals::h_local_ped());
				was_wet_mode_on = false;
			}
			return;
		}
		PED::SET_PED_WETNESS_ENABLED_THIS_FRAME(true);
		PED::SET_PED_WETNESS_HEIGHT(globals::h_local_ped(), value2);
		was_wet_mode_on = true;
	}
}
namespace insight {

	bool was_walk_under_water_on = false;
	void reset_flags_walk_under_water()
	{
		globals::c_local_ped()->m_health = 0; // the only way to reset
		script::get_current()->yield(100ms);
		PED::RESURRECT_PED(globals::h_local_ped());
		ENTITY::SET_ENTITY_COORDS_NO_OFFSET(globals::h_local_ped(), globals::h_local_ped_pos(), 0, 0, 0);
		TASK::CLEAR_PED_TASKS_IMMEDIATELY(globals::h_local_ped());
		MISC::FORCE_GAME_STATE_PLAYING();

	}

	void self::walk_under_water(toggle_feature* feature, bool& value) {

		if (!value) {
			if (was_walk_under_water_on) {
				reset_flags_walk_under_water();
				was_walk_under_water_on = false;
			}
			return;
		}
		if (value) {
			Ped playerPed = PLAYER::PLAYER_PED_ID();
			if (ENTITY::IS_ENTITY_IN_WATER(playerPed))
			{
				was_walk_under_water_on = true;
				PED::SET_PED_CONFIG_FLAG(playerPed, 65, false);
				PED::SET_PED_CONFIG_FLAG(playerPed, 66, false);
				PED::SET_PED_CONFIG_FLAG(playerPed, 168, false);

				Vector3 PlayerPos = ENTITY::GET_ENTITY_COORDS(playerPed, 0);
				if (PED::IS_PED_JUMPING(playerPed))
				{
					ENTITY::APPLY_FORCE_TO_ENTITY(playerPed, true, { 0, 0, 0.7f }, { 0, 0, 0 }, true, true, true, true, false, true);
				}

				if (ENTITY::GET_ENTITY_HEIGHT_ABOVE_GROUND(playerPed) > 1.2f)
				{
					PED::SET_PED_CONFIG_FLAG(playerPed, 60, false);
					PED::SET_PED_CONFIG_FLAG(playerPed, 61, false);
					PED::SET_PED_CONFIG_FLAG(playerPed, 104, false);
					PED::SET_PED_CONFIG_FLAG(playerPed, 276, false);
					PED::SET_PED_CONFIG_FLAG(playerPed, 76, true);
					ENTITY::APPLY_FORCE_TO_ENTITY(playerPed, true, { 0, 0, -0.7f }, { 0, 0, 0 }, true, true, true, true, false, true);
				}

				if (TASK::GET_IS_TASK_ACTIVE(playerPed, 281) || PED::IS_PED_SWIMMING_UNDER_WATER(playerPed))
				{
					TASK::CLEAR_PED_TASKS_IMMEDIATELY(playerPed);
				}
			}
		}
	}
}
namespace insight {
	void self::walk_thru(toggle_int_feature* feature, bool& value, int& value2) {
		if (!value) {
			return;
		}
		if (value2 == 0)
		{
			for (auto entity : tasks::get_world_entities(true, false, false))
			{
				ENTITY::SET_ENTITY_NO_COLLISION_ENTITY(entity, globals::h_local_ped(), true);
			}
		}
		else
			if (value2 == 1)
			{
				for (auto entity : tasks::get_world_entities(false, true, false))
				{
					ENTITY::SET_ENTITY_NO_COLLISION_ENTITY(entity, globals::h_local_ped(), true);
				}
			}
			else
				if (value2 == 2)
				{
					for (auto entity : tasks::get_world_entities(false, false, true))
					{
						ENTITY::SET_ENTITY_NO_COLLISION_ENTITY(entity, globals::h_local_ped(), true);
					}
				}
				else
					if (value2 == 3)
					{
						for (auto entity : tasks::get_world_entities(true, true, true))
						{
							ENTITY::SET_ENTITY_NO_COLLISION_ENTITY(entity, globals::h_local_ped(), true);
						}
					}

	}
}
namespace insight {

	bool was_walk_on_air_on_gravity = false;
	bool was_walk_on_air_on_carpet = false;
	Entity magic_carpet;
	float walk_on_air_z_f = 0.0f;
	bool was_walk_on_air_on = false;
	void self::walk_on_air(toggle_int_feature* feature, bool& value, int& value2) {
		if (!value) {
			was_walk_on_air_on = false;
			if (was_walk_on_air_on_carpet) {
				if (ENTITY::DOES_ENTITY_EXIST(magic_carpet))
				{
					OBJECT::DELETE_OBJECT(&magic_carpet);
				}

				was_walk_on_air_on_carpet = false;
			}
			if (was_walk_on_air_on_gravity) {
				ENTITY::SET_ENTITY_HAS_GRAVITY(globals::h_local_ped(), true);
				ENTITY::SET_ENTITY_VELOCITY(globals::h_local_ped(), Vector3(0.0f, 0.0f, 1.0f));
				was_walk_on_air_on_gravity = false;
			}
			return;
		}
		if (value2 == 0)
		{
			if (was_walk_on_air_on_carpet) {
				if (ENTITY::DOES_ENTITY_EXIST(magic_carpet)) {
					OBJECT::DELETE_OBJECT(&magic_carpet);
				}
				notify::send("player_vehicle_flymode"_tif->m_name,
					globals::is_using_controller() ?
					"To go up and down, use RB and LB."
					:
					"To go up and down, use numpad +  and numpad -.");

				was_walk_on_air_on_carpet = false;
			}
			if (!was_walk_on_air_on) {
				notify::send("player_vehicle_flymode"_tif->m_name,
					globals::is_using_controller() ?
					"To go up and down, use RB and LB."
					:
					"To go up and down, use numpad +  and numpad -.");

				was_walk_on_air_on = true;
			}
			if (was_walk_on_air_on_gravity == false) {
				Vector3 currentPosition = ENTITY::GET_ENTITY_COORDS(globals::h_local_ped(), true);
				float targetHeight = currentPosition.z + 10.f;
				ENTITY::SET_ENTITY_COORDS(globals::h_local_ped(), Vector3(currentPosition.x, currentPosition.y, targetHeight), true, true, true, false);
			}
			PAD::DISABLE_CONTROL_ACTION(0, (int)ControllerInputs::INPUT_RADIO_WHEEL_UD, true);
			bool is_shift_pressed = PAD::IS_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_REPLAY_FOVINCREASE);
			bool is_control_pressed = PAD::IS_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_REPLAY_FOVDECREASE);

			if (is_shift_pressed) {
				Vector3 currentPosition = ENTITY::GET_ENTITY_COORDS(globals::h_local_ped(), true);
				float targetHeight = currentPosition.z + 5.f;
				ENTITY::SET_ENTITY_COORDS(globals::h_local_ped(), Vector3(currentPosition.x, currentPosition.y, targetHeight), true, true, true, false);
			}
			else if (is_control_pressed) {
				Vector3 currentPosition = ENTITY::GET_ENTITY_COORDS(globals::h_local_ped(), true);
				float targetHeight = currentPosition.z - 5.f;
				ENTITY::SET_ENTITY_COORDS(globals::h_local_ped(), Vector3(currentPosition.x, currentPosition.y, targetHeight), true, true, true, false);
			}

			was_walk_on_air_on_gravity = true;
			ENTITY::SET_ENTITY_HAS_GRAVITY(globals::h_local_ped(), false);
		}
		if (value2 == 1)
		{
			if (was_walk_on_air_on_gravity) {
				ENTITY::SET_ENTITY_HAS_GRAVITY(globals::h_local_ped(), true);
				ENTITY::SET_ENTITY_VELOCITY(globals::h_local_ped(), Vector3(0.0f, 0.0f, 1.0f)); //disable other array
				was_walk_on_air_on_gravity = false;
			}
			was_walk_on_air_on_carpet = true;
			Vector3 get_local_ped_coordinates = ENTITY::GET_ENTITY_COORDS(globals::h_local_ped(), true);
			{
				if (PED::IS_PED_IN_ANY_VEHICLE(globals::h_local_ped(), true)) {
					if (ENTITY::DOES_ENTITY_EXIST(magic_carpet)) {
						OBJECT::DELETE_OBJECT(&magic_carpet);
					}

				}
				else {
					if (!ENTITY::DOES_ENTITY_EXIST(magic_carpet)) {
						tasks::request_model(rage::joaat("p_yoga_mat_01_s"));
						magic_carpet = OBJECT::CREATE_OBJECT(rage::joaat("p_yoga_mat_01_s"), get_local_ped_coordinates, globals::in_multiplayer(), 0, 0);
						ENTITY::FREEZE_ENTITY_POSITION(magic_carpet, true);
					}
					else {
						if (tasks::request_control(magic_carpet))
							ENTITY::SET_ENTITY_COORDS(magic_carpet, Vector3(get_local_ped_coordinates.x - 0.85f, get_local_ped_coordinates.y, get_local_ped_coordinates.z + walk_on_air_z_f - 1.02), 1, 0, 0, 0);
						if (PAD::IS_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_REPLAY_FOVINCREASE)) {
							if (walk_on_air_z_f < 0.400000) {
								walk_on_air_z_f = walk_on_air_z_f + 0.004;
							}
						}
						else if (PAD::IS_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_REPLAY_FOVDECREASE)) {
							if (walk_on_air_z_f > -0.400000) {
								walk_on_air_z_f = walk_on_air_z_f - 0.004;
							}

						}
					}

				}
			}
		}
	}
}
namespace insight {
	void fuc_unlimited_parachuting(int entity, float speed) {
		if (ENTITY::IS_ENTITY_ATTACHED_TO_ENTITY(entity, globals::h_local_ped())) {
			Hash has = ENTITY::GET_ENTITY_MODEL(entity);
			if (has == 218548447 || has == 1336576410 || has == 1931904776) {
				ENTITY::APPLY_FORCE_TO_ENTITY(entity, 1, Vector3(0.0f, 0.1 * speed, 0), Vector3(0.0f, 0.0f, 0.0f), 0, 1, 1, 1, 0, 1);
			}
		}
	}
	Object obj_ultimate_parachuting;
	void self::ultimate_parachuting(toggle_float_feature* feature, bool& value, float& value2) {
		if (!value) {
			return;
		}
		if (value2 != 0) {
			Object obj = OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(globals::h_local_ped_pos(), 10.f, 218548447, 0, 0, 0);
			if (obj) {
				obj_ultimate_parachuting = obj;
			}
			Object obj2 = OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(globals::h_local_ped_pos(), 10.f, 1336576410, 0, 0, 0);
			if (obj2) {
				obj_ultimate_parachuting = obj2;
			}
			Object obj3 = OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(globals::h_local_ped_pos(), 10.f, 1931904776, 0, 0, 0);
			if (obj3) {
				obj_ultimate_parachuting = obj3;
			}
			fuc_unlimited_parachuting(obj_ultimate_parachuting, value2);

		}
	}
}
namespace insight {
	bool was_tiny_ped_on = false;
	void self::tiny_ped(toggle_feature* feature, bool& value) {
		if (!value) {
			if (was_tiny_ped_on)
			{
				PED::SET_PED_CONFIG_FLAG(globals::h_local_ped(), ePedConfigFlags::PED_FLAG_SHRINK, false);
				was_tiny_ped_on = false;
			}
			return;
		}
		was_tiny_ped_on = true;
		PED::SET_PED_CONFIG_FLAG(globals::h_local_ped(), ePedConfigFlags::PED_FLAG_SHRINK, true);
	}
}
namespace insight {
	bool was_tiny_legs_on = false;
	static timer was_tiny_legs_on_timer(std::chrono::milliseconds(60ms));
	void self::tiny_legs(toggle_feature* feature, bool& value) {
		if (!value) {
			if (was_tiny_legs_on) {
				PED::SET_PED_RESET_FLAG(globals::h_local_ped(), ePedConfigFlags::CPED_CONFIG_FLAG_IsStanding, true);
				was_tiny_legs_on = false;
			}
			return;
		}
		was_tiny_legs_on = true;
		PED::SET_PED_CONFIG_FLAG(globals::h_local_ped(), ePedConfigFlags::CPED_CONFIG_FLAG_IsStanding, true);
		PED::SET_PED_CONFIG_FLAG(globals::h_local_ped(), ePedConfigFlags::CPED_CONFIG_FLAG_IsStanding, false);
	}
}
namespace insight {
	bool was_swim_modifier_on = false;
	void self::swim_modifier(toggle_float_feature* feature, bool& value, float& value2) {
		if (!value) {
			if (was_swim_modifier_on)
			{
				globals::c_local_ped()->m_player_info->m_swim_speed = 1.0f;
				was_swim_modifier_on = false;
			}
			return;
		}
		was_swim_modifier_on = true;
		globals::c_local_ped()->m_player_info->m_swim_speed = value2;
	}
}
namespace insight {
	bool was_swim_everywhere_on = false;
	void swim_everywhere_reset_flags()
	{
		globals::c_local_ped()->m_health = 0; // the only way to reset
		script::get_current()->yield(100ms);
		PED::RESURRECT_PED(globals::h_local_ped());
		ENTITY::SET_ENTITY_COORDS_NO_OFFSET(globals::h_local_ped(), globals::h_local_ped_pos(), 0, 0, 0);
		TASK::CLEAR_PED_TASKS_IMMEDIATELY(globals::h_local_ped());
		MISC::FORCE_GAME_STATE_PLAYING();
	}
	void self::swim_everywhere(toggle_feature* feature, bool& value) {

		if (!value) {
			if (was_swim_everywhere_on)
			{
				swim_everywhere_reset_flags();
				was_swim_everywhere_on = false;
			}
			return;
		}
		was_swim_everywhere_on = true;

		if ("player_walk_under_water"_tif->m_toggle_value.toggle)
		{
			notify::send("player_walk_under_water"_tif->m_name, "Walk Under Water Disabled");
			"player_walk_under_water"_tif->m_toggle_value.toggle = false;
		}
		PED::SET_PED_CONFIG_FLAG(globals::h_local_ped(), ePedConfigFlags::CPED_CONFIG_FLAG_IsSwimming, true);
	}
}
namespace insight {
	void self::super_swim(toggle_float_feature* feature, bool& value, float& value2) {
		if (!value) {
			return;
		}
		if (!PED::IS_PED_JUMPING(globals::h_local_ped()) && !PED::IS_PED_FALLING(globals::h_local_ped())) {
			if (PED::IS_PED_SWIMMING(globals::h_local_ped())) {
				bool fastswiming = PAD::IS_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_SPRINT);
				ENTITY::APPLY_FORCE_TO_ENTITY(globals::h_local_ped(), 1, Vector3(0.0f, fastswiming ? value2 * 1.2 : value2, 0), Vector3(0.0f, 0.0f, 0.0f), 0, 1, 1, 1, 0, 1);

			}
		}
	}
}
namespace insight {
	void super_run_fuc(float speed, int direction) {
		if (direction == 0) {
			if (!PED::IS_PED_JUMPING(globals::h_local_ped()) && !PED::IS_PED_FALLING(globals::h_local_ped()) && ENTITY::GET_ENTITY_HEIGHT_ABOVE_GROUND(globals::h_local_ped()) < 5.0f && !PED::IS_PED_SWIMMING(globals::h_local_ped())) {
				if (TASK::IS_PED_RUNNING(globals::h_local_ped())) {
					ENTITY::APPLY_FORCE_TO_ENTITY(globals::h_local_ped(), 1, Vector3(0.0f, speed, 0), Vector3(0.0f, 0.0f, 0.0f), 0, 1, 1, 1, 0, 1);
				}
				else if (TASK::IS_PED_SPRINTING(globals::h_local_ped())) {
					ENTITY::APPLY_FORCE_TO_ENTITY(globals::h_local_ped(), 1, Vector3(0.0f, speed * 1.2, 0), Vector3(0.0f, 0.0f, 0.0f), 0, 1, 1, 1, 0, 1);
				}
			}
		}
		else {
			if (!PED::IS_PED_JUMPING(globals::h_local_ped()) && !PED::IS_PED_FALLING(globals::h_local_ped()) && ENTITY::GET_ENTITY_HEIGHT_ABOVE_GROUND(globals::h_local_ped()) < 5.0f && !PED::IS_PED_SWIMMING(globals::h_local_ped())) {
				if (TASK::IS_PED_RUNNING(globals::h_local_ped())) {
					ENTITY::APPLY_FORCE_TO_ENTITY(globals::h_local_ped(), 1, Vector3(0.0f, -speed, 0), Vector3(0.0f, 0.0f, 0.0f), 0, 1, 1, 1, 0, 1);
				}
				else if (TASK::IS_PED_SPRINTING(globals::h_local_ped())) {
					ENTITY::APPLY_FORCE_TO_ENTITY(globals::h_local_ped(), 1, Vector3(0.0f, speed * -1.2, 0), Vector3(0.0f, 0.0f, 0.0f), 0, 1, 1, 1, 0, 1);
				}
			}

		}
	}
	void self::super_run(toggle_float_feature* feature, bool& value, float& value2) {
		if (!value) {
			return;
		}
		super_run_fuc(value2, "player_super_run_type"_if->m_value.integer);
	}
}
namespace insight {
	timer self_ptfx_stomach_timer(std::chrono::milliseconds(100));
	void self::self_ptfx_stomach(toggle_int_feature* feature, bool& value, int& value2) {
		if (!value) {
			return;
		}
		self_ptfx_stomach_timer.setdelay(std::chrono::milliseconds((int)"playe_ptfx_stomach_scale_d"_FF->m_value.floating_point * 100));
		if (self_ptfx_stomach_timer.update()) {
			if (globals::h_local_ped())
				tasks::get()->play_ptfx_on_ped_bone(globals::h_local_ped(), xorstr_("SKEL_ROOT"), value2, "playe_ptfx_stomach_scale"_FF->m_value.floating_point);
		}
	}
	timer self_ptfx_head_timer(std::chrono::milliseconds(100));
	void self::self_ptfx_head(toggle_int_feature* feature, bool& value, int& value2) {
		if (!value) {
			return;
		}
		self_ptfx_head_timer.setdelay(std::chrono::milliseconds((int)"playe_ptfx_head_scale_d"_FF->m_value.floating_point * 100));
		if (self_ptfx_head_timer.update()) {
			if (globals::h_local_ped())
				tasks::get()->play_ptfx_on_ped_bone(globals::h_local_ped(), xorstr_("IK_Head"), value2, "playe_ptfx_head_scale"_FF->m_value.floating_point);
		}
	}
	timer self_ptfx_left_hand_timer(std::chrono::milliseconds(100));
	void self::self_ptfx_left_hand(toggle_int_feature* feature, bool& value, int& value2) {
		if (!value) {
			return;
		}
		self_ptfx_left_hand_timer.setdelay(std::chrono::milliseconds((int)"playe_ptfx_l_hand_scale_d"_FF->m_value.floating_point * 100));
		if (self_ptfx_left_hand_timer.update()) {
			if (globals::h_local_ped())
				tasks::get()->play_ptfx_on_ped_bone(globals::h_local_ped(), xorstr_("IK_L_Hand"), value2, "playe_ptfx_l_hand_scale"_FF->m_value.floating_point);
		}
	}
	timer self_ptfx_right_hand_timer(std::chrono::milliseconds(100));
	void self::self_ptfx_right_hand(toggle_int_feature* feature, bool& value, int& value2) {
		if (!value) {
			return;
		}
		self_ptfx_right_hand_timer.setdelay(std::chrono::milliseconds((int)"playe_ptfx_r_hand_scale_d"_FF->m_value.floating_point * 100));
		if (self_ptfx_right_hand_timer.update()) {
			if (globals::h_local_ped())
				tasks::get()->play_ptfx_on_ped_bone(globals::h_local_ped(), xorstr_("IK_R_Hand"), value2, "playe_ptfx_r_hand_scale"_FF->m_value.floating_point);
		}
	}
	timer self_ptfx_left_foot_timer(std::chrono::milliseconds(100));
	void self::self_ptfx_left_foot(toggle_int_feature* feature, bool& value, int& value2) {
		if (!value) {
			return;
		}
		self_ptfx_left_foot_timer.setdelay(std::chrono::milliseconds((int)"playe_ptfx_l_foot_scale_d"_FF->m_value.floating_point * 100));
		if (self_ptfx_left_foot_timer.update()) {
			if (globals::h_local_ped())
				tasks::get()->play_ptfx_on_ped_bone(globals::h_local_ped(), xorstr_("IK_L_Foot"), value2, "playe_ptfx_l_foot_scale"_FF->m_value.floating_point);
		}
	}
	timer self_ptfx_right_foot_timer(std::chrono::milliseconds(100));
	void self::self_ptfx_right_foot(toggle_int_feature* feature, bool& value, int& value2) {
		if (!value) {
			return;
		}
		self_ptfx_right_foot_timer.setdelay(std::chrono::milliseconds((int)"playe_ptfx_r_foot_scale_d"_FF->m_value.floating_point * 100));
		if (self_ptfx_right_foot_timer.update()) {
			if (globals::h_local_ped())
				tasks::get()->play_ptfx_on_ped_bone(globals::h_local_ped(), xorstr_("IK_R_Foot"), value2, "playe_ptfx_r_foot_scale"_FF->m_value.floating_point);
		}
	}
}
namespace insight {
	bool was_self_ped_alphha_on = false;
	void self::self_ped_alphha(toggle_int_feature* feature, bool& value, int& value2) {
		if (!value) {
			if (was_self_ped_alphha_on) {
				ENTITY::SET_ENTITY_ALPHA(globals::h_local_ped(), 255, 0);
				was_self_ped_alphha_on = false;
			}
			return;
		}
		was_self_ped_alphha_on = true;
		ENTITY::SET_ENTITY_ALPHA(globals::h_local_ped(), 51 * value2, 0);
	}
}
namespace insight {
	bool does_player_had_parachute_gadget = false;
	void parachute_check()
	{
		Hash gadget_parachute = rage::joaat("GADGET_PARACHUTE");
		bool does_player_have_parachute = WEAPON::HAS_PED_GOT_WEAPON(globals::h_local_ped(), gadget_parachute, false);
		if (does_player_have_parachute) {
			does_player_had_parachute_gadget = true;
			if (PED::IS_PED_JUMPING(globals::h_local_ped())) {
				WEAPON::REMOVE_WEAPON_FROM_PED(globals::h_local_ped(), gadget_parachute);
			}

		}
		else {
			if (does_player_had_parachute_gadget) {
				WEAPON::GIVE_DELAYED_WEAPON_TO_PED(globals::h_local_ped(), gadget_parachute, 1, 0);
				does_player_had_parachute_gadget = false;
			}
		}
	}
	static float ninja_spin_rotation = 10.0f;
	void super_jumping_animation_ninja(bool use_cam, float speed) {
		if (PED::IS_PED_JUMPING(globals::h_local_ped())) {
			if (ENTITY::IS_ENTITY_IN_AIR(globals::h_local_ped())) {
				ninja_spin_rotation = ninja_spin_rotation + speed;
				ENTITY::SET_ENTITY_ROTATION(globals::h_local_ped(), ninja_spin_rotation, 0, use_cam ? 0 : CAM::GET_GAMEPLAY_CAM_ROT(2).z, 0, 0);
			}
		}
	}
	static float threesixte_spin_rotation = 10.0f;
	void super_jumping_animation_threesixte(float speed) {
		if (PED::IS_PED_JUMPING(globals::h_local_ped())) {
			if (ENTITY::IS_ENTITY_IN_AIR(globals::h_local_ped())) {
				threesixte_spin_rotation = threesixte_spin_rotation + speed;
				ENTITY::SET_ENTITY_ROTATION(globals::h_local_ped(), 0, 0, threesixte_spin_rotation, 0, 0);
			}
		}
	}
	bool super_jump_get = false;
	void self::super_jump(toggle_int_feature* feature, bool& value, int& value2) {
		detour::g_super_jump_mode = value2;
		detour::g_is_super_jump_enabled = value;
		if (!value) {
			return;
		}
		parachute_check();
		if ("player_super_jump_ninja"_tff->m_toggle_value.toggle)
			super_jumping_animation_ninja("player_super_jump_360"_tff->m_toggle_value.toggle, "player_super_jump_ninja"_tff->m_number_value.floating_point);
		if ("player_super_jump_360"_tff->m_toggle_value.toggle)
			super_jumping_animation_threesixte("player_super_jump_360"_tff->m_number_value.floating_point);
		if (PED::IS_PED_JUMPING(globals::h_local_ped())) {
			if (!super_jump_get) {
				Vector3 force_ = { 0,0,0 };
				if ("player_super_jump_directional_force"_tif->m_toggle_value.toggle && "player_super_jump_directional_force"_tif->m_number_value.integer == 0) { // forward
					Vector3 front_f = vectors::get()->get_front_camera_coordinates_local("player_super_jump_directional_force_rate"_FF->m_value.floating_point) - globals::h_local_ped_pos();
					force_ = Vector3(front_f.x + "player_super_jump_x"_FF->m_value.floating_point,
						front_f.y + "player_super_jump_y"_FF->m_value.floating_point, front_f.z + "player_super_jump_z"_FF->m_value.floating_point);
					ENTITY::SET_ENTITY_VELOCITY(globals::h_local_ped(), force_);
				}
				else  if ("player_super_jump_directional_force"_tif->m_toggle_value.toggle && "player_super_jump_directional_force"_tif->m_number_value.integer == 1) { // backward
					Vector3 front_f = vectors::get()->get_front_camera_coordinates_local(-"player_super_jump_directional_force_rate"_FF->m_value.floating_point) - globals::h_local_ped_pos();
					force_ = Vector3(front_f.x + "player_super_jump_x"_FF->m_value.floating_point,
						front_f.y + "player_super_jump_y"_FF->m_value.floating_point, front_f.z + "player_super_jump_z"_FF->m_value.floating_point);
					ENTITY::SET_ENTITY_VELOCITY(globals::h_local_ped(), force_);
				}
				else {
					force_ = Vector3("player_super_jump_x"_FF->m_value.floating_point,
						"player_super_jump_y"_FF->m_value.floating_point, "player_super_jump_z"_FF->m_value.floating_point);
					ENTITY::SET_ENTITY_VELOCITY(globals::h_local_ped(), force_);
				}
				super_jump_get = true;
			}
		}
		else {
			super_jump_get = false;
		}
	}
	void self::graceful_landing(toggle_feature* feature, bool& value) {
		detour::g_graceful_landing = value;
	}
	void self::double_jumping(toggle_feature* feature, bool& value) {
		if (!value) {
			return;
		}
		if (PAD::IS_CONTROL_JUST_PRESSED(0, (int)ControllerInputs::INPUT_JUMP)) {
			if ("player_super_jump"_tif->m_toggle_value.toggle) {
				TASK::TASK_JUMP(globals::h_local_ped(), 0, 0, 0);
			}
		}
	}
}
namespace insight {
	bool was_super_man_flying_on = false;
	void self::super_man_flying(toggle_float_feature* feature, bool& value, float& value2) {
		if (!value) {
			if (was_super_man_flying_on) {
				was_super_man_flying_on = false;
			}
			return;
		}
		if (!was_super_man_flying_on) {
			notify::send("Superman Flying",
				globals::is_using_controller() ?
				"Usage : Press Sprint Key (LShift) For Boost And Jump (Space) Key To Fly & Go Up."
				:
				"Usage : Press Sprint (X) Key For Boost And Jump (Box) Key To Fly & Go Up.");
			was_super_man_flying_on = true;
		}
		if (ENTITY::IS_ENTITY_IN_AIR(globals::h_local_ped())) {
			PAD::DISABLE_CONTROL_ACTION(0, (int)ControllerInputs::INPUT_SPRINT, true);
			if (PED::IS_PED_IN_PARACHUTE_FREE_FALL(globals::h_local_ped())) {
				ENTITY::APPLY_FORCE_TO_ENTITY(globals::h_local_ped(), 1, Vector3(0.0f, 2.0 * value2, 0.5f * value2), Vector3(0.0f, 0.0f, 0.0f), 0, 1, 1, 1, 0, 1);
				if (PAD::IS_DISABLED_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_SPRINT)) {
					ENTITY::APPLY_FORCE_TO_ENTITY(globals::h_local_ped(), 1, Vector3(0.0f, 3.0 * value2, 0.0f), Vector3(0.0f, 0.0f, 0.0f), 0, 1, 1, 1, 0, 1);
				}
			}
		}
		if (PAD::IS_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_JUMP)) {
			ENTITY::APPLY_FORCE_TO_ENTITY(globals::h_local_ped(), 1, Vector3(0.0f, 0.0, 2.0f * value2), Vector3(0.0f, 0.0f, 0.0f), 0, 1, 1, 1, 0, 1);
			if (!PED::IS_PED_IN_PARACHUTE_FREE_FALL(globals::h_local_ped())) {
				TASK::TASK_PARACHUTE(globals::h_local_ped(), 1, 1);
			}
		}

	}
}
namespace insight {
	bool is_key_jumping_pressed = false;
	bool check_one_passed = false;
	float last_hulk_distance = 0;
	bool was_hulking_jumping_on = false;
	void self::hulking_jumping(toggle_feature* feature, bool& value) {
		if (!value) {
			was_hulking_jumping_on = false;
			return;
		}
		if (!was_hulking_jumping_on) {
			notify::send("Hulk Jumping",
				globals::is_using_controller() ?
				"Usage : Press E Key (LShift) to aim & jump."
				:
				"Usage : Press DPAD RIGHT to aim & jump.");
			was_hulking_jumping_on = true;
		}
		if (PAD::IS_DISABLED_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_TALK))
		{
			last_hulk_distance = 10000.f;
			while (!STREAMING::HAS_ANIM_DICT_LOADED(("amb@world_human_gardener_plant@female@idle_a")))
			{
				STREAMING::REQUEST_ANIM_DICT("amb@world_human_gardener_plant@female@idle_a");
				script::get_current()->yield();
			}
			tasks::get()->play_animation_tick(globals::h_local_ped(), "amb@world_human_gardener_plant@female@idle_a", "idle_a_female", 0);
			is_key_jumping_pressed = true;
			check_one_passed = true;
			Vector3 laser = tasks::get_laser_ending_coordinates();
			Vector3 head = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(globals::h_local_ped(), Vector3(0, 0, 1.2));
			tasks::draw_marker(eMarkerType::MarkerTypeDebugSphere, head, 0.1, 0, 120, 200, 200, true);
			tasks::draw_marker(eMarkerType::MarkerTypeHorizontalCircleFat, laser, 1, 0, 120, 200, 200, true);
			float height = 25.0f;
			tasks::draw_marker(eMarkerType::MarkerTypeDebugSphere, Vector3(laser.x, laser.y, laser.z + height), 2, 0, 120, 200, 200);
			GRAPHICS::DRAW_LINE(Vector3(laser.x, laser.y, laser.z + height), laser, 0, 120, 200, 255);
			GRAPHICS::DRAW_LINE(Vector3(laser.x, laser.y, laser.z + height), Vector3(laser.x, laser.y + 2.0f, laser.z + height), 0, 120, 200, 255);
			GRAPHICS::DRAW_LINE(Vector3(laser.x, laser.y, laser.z + height), Vector3(laser.x, laser.y - 2, laser.z + height), 0, 120, 200, 255);
			float distanceInFeet = SYSTEM::VDIST(laser, globals::h_local_ped_pos()) * 3.28084f;
			float roundedDistance = std::roundf(distanceInFeet * 100) / 100;
			std::ostringstream oss;
			oss << std::fixed << std::setprecision(2) << roundedDistance;
			std::string formattedDistance = oss.str();
			render::get()->draw_text_coordinates(std::string(formattedDistance + " ft").c_str(), laser, 0, 120, 200, 200);
		}
		else
		{
			if (is_key_jumping_pressed)
			{
				//	detour::g_disable_parachute = true;
				PED::SET_PED_CONFIG_FLAG(globals::h_local_ped(), 362, FALSE);
				PED::SET_PED_CONFIG_FLAG(globals::h_local_ped(), 363, FALSE);
				ENTITY::SET_ENTITY_COLLISION(globals::h_local_ped(), 0, 0);
				Hash gadget_parachute = rage::joaat("GADGET_PARACHUTE");
				WEAPON::REMOVE_WEAPON_FROM_PED(globals::h_local_ped(), gadget_parachute);
				Hash gadget_parachute2 = -72657034;
				WEAPON::REMOVE_WEAPON_FROM_PED(globals::h_local_ped(), gadget_parachute2);

				Vector3 laser = tasks::get_laser_ending_coordinates();
				TASK::TASK_JUMP(globals::h_local_ped(), 1, 0, 0);
				script::get_current()->yield(100ms);
				Vector3 top_coords = { laser.x,laser.y,laser.z + "player_hulk_jumping_height"_FF->m_value.floating_point };
			LABEL_ONE:
				ENTITY::SET_ENTITY_VELOCITY(globals::h_local_ped(), top_coords - globals::h_local_ped_pos());
				float distance = tasks::get()->get_distance_between(globals::h_local_ped_pos(), top_coords);
				if (value && distance > 10.f) {
					script::get_current()->yield();
					if (distance <= last_hulk_distance) {
						last_hulk_distance = distance;
					}
					if (distance > last_hulk_distance) {
						goto SKIPPER;
					}
					goto LABEL_ONE;

				}
				else {
				SKIPPER:
					//	Vector3 velo = ENTITY::GET_ENTITY_VELOCITY(globals::h_local_ped());
					for (size_t i = 0; i < 20; i++)
					{
						ENTITY::SET_ENTITY_VELOCITY(globals::h_local_ped(), { 0,0,0 });
					}
					ENTITY::SET_ENTITY_COLLISION(globals::h_local_ped(), 1, 1);

					//detour::g_disable_parachute = false;
					is_key_jumping_pressed = false;
				}
			}
		}
	}
}
namespace insight {
	bool was_run_modifier_on = false;
	void self::run_modifier(toggle_float_feature* feature, bool& value, float& value2) {
		if (!value) {

			if (was_run_modifier_on)
			{
				globals::c_local_ped()->m_player_info->m_run_speed = 1.0f;
				was_run_modifier_on = false;
			}
			return;
		}
		was_run_modifier_on = true;
		globals::c_local_ped()->m_player_info->m_run_speed = value2;
	}
}
namespace insight {
	void self::matrix_lean(toggle_float_feature* feature, bool& value, float& value2) {
		if (!value) {
			return;
		}
		if (auto ped_factory = *reinterpret_cast<std::add_pointer_t<std::uint64_t>>(insight::pointers::get()->g_ped_factory)) {
			if (auto player_ped = *reinterpret_cast<std::add_pointer_t<std::uint64_t>>(ped_factory + 0x8)) {
				*reinterpret_cast<std::add_pointer_t<std::float_t>>(player_ped + 0x80) = value2;
			}
		}
	}

	void self::matrix_width(toggle_float_feature* feature, bool& value, float& value2) {
		if (!value) {
			return;
		}
		if (auto ped_factory = *reinterpret_cast<std::add_pointer_t<std::uint64_t>>(insight::pointers::get()->g_ped_factory)) {
			if (auto player_ped = *reinterpret_cast<std::add_pointer_t<std::uint64_t>>(ped_factory + 0x8)) {
				*reinterpret_cast<std::add_pointer_t<std::float_t>>(player_ped + 0x60) = value2;
			}
		}
	}

	void self::matrix_height(toggle_float_feature* feature, bool& value, float& value2) {
		if (!value) {
			return;
		}
		if (auto ped_factory = *reinterpret_cast<std::add_pointer_t<std::uint64_t>>(insight::pointers::get()->g_ped_factory)) {
			if (auto player_ped = *reinterpret_cast<std::add_pointer_t<std::uint64_t>>(ped_factory + 0x8)) {
				*reinterpret_cast<std::add_pointer_t<std::float_t>>(player_ped + 0x88) = value2;
			}
		}
	}
}
namespace insight {
	bool was_no_ragdoll_on = false;
	void self::no_ragdoll(toggle_int_feature* feature, bool& value, int& value2) {
		if (!value) {
			if (was_no_ragdoll_on) {
				PED::SET_PED_CAN_RAGDOLL(globals::h_local_ped(), true);
				was_no_ragdoll_on = false;
			}
			return;
		}
		if (value2 == 0) {
			was_no_ragdoll_on = true;
			PED::SET_PED_CAN_RAGDOLL(globals::h_local_ped(), false);
		}
		else if (value2 == 1) {
			was_no_ragdoll_on = true;
			Vector3 my_coords = ENTITY::GET_ENTITY_COORDS(globals::h_local_ped(), TRUE);
			float tmp_z = my_coords.z;
			MISC::GET_GROUND_Z_FOR_3D_COORD(my_coords, &tmp_z, false, false);
			Vector3 ground_coords = { my_coords.x, my_coords.y, tmp_z };
			float distance = MISC::GET_DISTANCE_BETWEEN_COORDS(my_coords, ground_coords, true);
			if ((!PED::IS_PED_VAULTING(globals::h_local_ped())) && (distance > 1 && distance < 1.4) && (ENTITY::GET_ENTITY_VELOCITY(PLAYER::PLAYER_PED_ID()).z < -4.5 || PED::IS_PED_IN_PARACHUTE_FREE_FALL(PLAYER::PLAYER_PED_ID()))) {
				TASK::CLEAR_PED_TASKS(globals::h_local_ped());
				TASK::CLEAR_PED_TASKS_IMMEDIATELY(globals::h_local_ped());
				ENTITY::SET_ENTITY_COORDS_NO_OFFSET(globals::h_local_ped(), { ground_coords.x, ground_coords.y, ground_coords.z + 1.34f }, true, true, true);
				ENTITY::SET_ENTITY_VELOCITY(globals::h_local_ped(), ground_coords * 0);
			}
			if (PED::IS_PED_FALLING(globals::h_local_ped()) && ENTITY::GET_ENTITY_HEIGHT_ABOVE_GROUND(globals::h_local_ped()) < 1.0f) {
				TASK::CLEAR_PED_TASKS(globals::h_local_ped());
				TASK::CLEAR_PED_TASKS_IMMEDIATELY(globals::h_local_ped());

			}
		}
	}
}
namespace insight {
	void self::never_wanted(toggle_feature* feature, bool& value) {
		if (value) {
			globals::c_local_ped()->m_player_info->m_wanted_level = 0;
		}
	}
}
namespace insight {

	void self::no_clip_speed(float_feature* feature, float& value) {
		return;
	}
	int no_clip_t_pos_rot = 0.f;
	void no_clip_t_pos(float speed_, bool rotating, float rotation_speed, float vertical_move_speed, float lateral_move_speed) {

		Entity target = !PED::IS_PED_IN_ANY_VEHICLE(globals::h_local_ped(), false) ? globals::h_local_ped() : globals::h_local_vehicle();
		ENTITY::SET_ENTITY_ROTATION(target, 0, 0, rotating ? no_clip_t_pos_rot : 0, 0, 0);
		Vector3 camera_direction = vectors::get()->get_direction();
		float speed = speed_;
		if (rotating) {
			no_clip_t_pos_rot += rotation_speed;
			ENTITY::SET_ENTITY_COORDS_NO_OFFSET(target, ENTITY::GET_ENTITY_COORDS(target, true), false, false, false);
		}
		bool sprint_pressed = PAD::IS_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_SPRINT);
		speed *= sprint_pressed ? lateral_move_speed * 2 : lateral_move_speed;

		Vector3 position = ENTITY::GET_ENTITY_COORDS(target, false);

		if (input::is_pressed(true, VK_SPACE)) {
			ENTITY::SET_ENTITY_COORDS_NO_OFFSET(target, { position.x, position.y, position.z + vertical_move_speed }, false, false, false);
		}

		if (input::is_pressed(true, VK_CONTROL)) {
			ENTITY::SET_ENTITY_COORDS_NO_OFFSET(target, { position.x, position.y, position.z - vertical_move_speed }, false, false, false);
		}

		if (ENTITY::IS_ENTITY_A_PED(target))
			CAM::SET_FOLLOW_PED_CAM_VIEW_MODE(2);
		else
			CAM::SET_FOLLOW_VEHICLE_CAM_ZOOM_LEVEL(2);

		ENTITY::SET_ENTITY_COLLISION(target, false, false);
		ENTITY::FREEZE_ENTITY_POSITION(target, true);

		if (PAD::IS_DISABLED_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_MOVE_UP_ONLY))
		{
			ENTITY::SET_ENTITY_COORDS_NO_OFFSET(target, position + (camera_direction * speed), false, false, false);
		}
		else if (PAD::IS_DISABLED_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_MOVE_DOWN_ONLY))
		{
			ENTITY::SET_ENTITY_COORDS_NO_OFFSET(target, position - (camera_direction * speed), false, false, false);
		}
		if (PAD::IS_DISABLED_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_MOVE_LEFT_ONLY)) {
			ENTITY::SET_ENTITY_COORDS_NO_OFFSET(target, position - (vectors::get()->get_right_vector() * speed), true, true, true);
		}
		else if (PAD::IS_DISABLED_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_MOVE_RIGHT_ONLY)) {
			ENTITY::SET_ENTITY_COORDS_NO_OFFSET(target, position + (vectors::get()->get_right_vector() * speed), true, true, true);
		}
	}
	void no_clip_walking(float speed_, float vertical_move_speed, float lateral_move_speed) {
		ENTITY::SET_ENTITY_ROTATION(globals::h_local_ped(), CAM::GET_GAMEPLAY_CAM_ROT(0).x, CAM::GET_GAMEPLAY_CAM_ROT(0).y, CAM::GET_GAMEPLAY_CAM_ROT(0).z, 2, true);
		Vector3 camera_direction = vectors::get()->get_direction();

		float speed = speed_;

		bool sprint_pressed = PAD::IS_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_SPRINT);
		speed *= sprint_pressed ? lateral_move_speed * 2 : lateral_move_speed;

		Entity target = !PED::IS_PED_IN_ANY_VEHICLE(globals::h_local_ped(), false) ? globals::h_local_ped() : globals::h_local_vehicle();
		Vector3 position = ENTITY::GET_ENTITY_COORDS(target, false);


		if (input::is_pressed(true, VK_SPACE)) {
			ENTITY::SET_ENTITY_COORDS_NO_OFFSET(target, { position.x, position.y, position.z + vertical_move_speed }, false, false, false);
		}

		if (input::is_pressed(true, VK_CONTROL)) {
			ENTITY::SET_ENTITY_COORDS_NO_OFFSET(target, { position.x, position.y, position.z - vertical_move_speed }, false, false, false);
		}

		if (ENTITY::IS_ENTITY_A_PED(target))
			CAM::SET_FOLLOW_PED_CAM_VIEW_MODE(2);
		else
			CAM::SET_FOLLOW_VEHICLE_CAM_ZOOM_LEVEL(2);

		ENTITY::SET_ENTITY_COLLISION(target, false, false);
		ENTITY::FREEZE_ENTITY_POSITION(target, true);

		Vector3 rotation = CAM::GET_GAMEPLAY_CAM_ROT(0);
		ENTITY::SET_ENTITY_ROTATION(target, rotation.x, rotation.y, rotation.z, 2, true);

		if (PAD::IS_DISABLED_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_MOVE_UP_ONLY))
		{
			ENTITY::SET_ENTITY_COORDS_NO_OFFSET(target, position + (camera_direction * speed), true, true, true);
		}
		else if (PAD::IS_DISABLED_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_MOVE_DOWN_ONLY))
		{
			ENTITY::SET_ENTITY_COORDS_NO_OFFSET(target, position - (camera_direction * speed), true, true, true);
		}

		if (PAD::IS_DISABLED_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_MOVE_LEFT_ONLY)) {
			ENTITY::SET_ENTITY_COORDS_NO_OFFSET(target, position - (vectors::get()->get_right_vector() * speed), true, true, true);
		}
		else if (PAD::IS_DISABLED_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_MOVE_RIGHT_ONLY)) {
			ENTITY::SET_ENTITY_COORDS_NO_OFFSET(target, position + (vectors::get()->get_right_vector() * speed), true, true, true);
		}
	}

	bool was_no_clip_on;
	void self::no_clip(toggle_int_feature* feature, bool& value, int& value2) {
		if (!value) {
			if (was_no_clip_on) {
				Entity target = !PED::IS_PED_IN_ANY_VEHICLE(globals::h_local_ped(), false) ? globals::h_local_ped() : globals::h_local_vehicle();

				ENTITY::SET_ENTITY_COLLISION(target, true, true);
				ENTITY::FREEZE_ENTITY_POSITION(target, false);
				was_no_clip_on = false;
			}
			return;
		}
		if (value2 == 0) {
			no_clip_t_pos("player_no_clip_speed"_FF->m_value.floating_point, "player_no_clip_rotation"_tff->m_toggle_value.toggle, "player_no_clip_rotation"_tff->m_number_value.floating_point, "player_no_clip_speed_ver"_FF->m_value.floating_point, "player_no_clip_speed_lat"_FF->m_value.floating_point);
		}
		if (value2 == 1) {
			no_clip_walking("player_no_clip_speed"_FF->m_value.floating_point, "player_no_clip_speed_ver2"_FF->m_value.floating_point, "player_no_clip_speed_lat2"_FF->m_value.floating_point);
		}
		was_no_clip_on = true;
	}
}
namespace insight {
	bool was_feature_on = false;

	void self::mobile_radio(toggle_feature* feature, bool& value) {
		AUDIO::SET_MOBILE_RADIO_ENABLED_DURING_GAMEPLAY(value);
		AUDIO::SET_MOBILE_PHONE_RADIO_STATE(value);
	}
}
namespace insight {
	int last_lock_wanted_level = 0;
	void self::lock_wanted_level(toggle_int_feature* feature, bool& value, int& value2) {
		if (!value) {
			if (last_lock_wanted_level != value2) {
				if (value2 > 5) {
					value2 = 5;
				}
				globals::c_local_ped()->m_player_info->m_wanted_level = value2;
				last_lock_wanted_level = value2;
			}
			if (globals::c_local_ped()->m_player_info->m_wanted_level != last_lock_wanted_level) {
				value2 = globals::c_local_ped()->m_player_info->m_wanted_level;
				last_lock_wanted_level = globals::c_local_ped()->m_player_info->m_wanted_level;
			}

			return;
		}
		if (value) {
			globals::c_local_ped()->m_player_info->m_wanted_level = value2;
		}
	}
}
namespace insight {
	int bone = 0;
	void self::laser_eyes(toggle_feature* feature, bool& value) {
		if (!value) {
			return;
		}
		for (int i = 0 + bone; i < 10 + bone; i++)
		{
			render::get()->draw_text_coordinates(std::to_string(i).c_str(), ENTITY::GET_ENTITY_BONE_POSTION(globals::h_local_ped(), i), 255, 255, 255, 255);
		}
		if (PAD::IS_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_VEH_CINEMATIC_DOWN_ONLY))
			bone += 1;
		if (PAD::IS_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_VEH_CINEMATIC_UP_ONLY))
			bone -= 1;
		tasks::play_ptfx_bone_woffsets_tick(globals::h_local_ped(), 0, particles[76].dict, particles[76].dict,
			particles[76].texture, 2.0f,
			Vector3(0, 0, 0), Vector3(vectors::get()->get_direction()));

		tasks::play_ptfx_bone_woffsets_tick(globals::h_local_ped(), 0, particles[76].dict, particles[76].dict,
			particles[76].texture, 2.0f,
			Vector3(0, 0, 0), Vector3(vectors::get()->get_direction()));
	}
}
namespace insight {
	void self::karama(toggle_int_feature* feature, bool& value, int& value2) {
		if (!value)
			return;

		Entity killer = PED::GET_PED_SOURCE_OF_DEATH(globals::h_local_ped());
		bool is_player = PED::IS_PED_A_PLAYER(killer);
		if (value2 == 1 ? (is_player && killer != 0) : killer) {
			{
				if (!ENTITY::IS_ENTITY_DEAD(killer, 1) && ENTITY::IS_ENTITY_DEAD(globals::h_local_ped(), 1)) {
					Vector3 coords = ENTITY::GET_ENTITY_COORDS(killer, true);
					FIRE::ADD_EXPLOSION(coords, 1, 100.f, true, false, 0.f, false);
				}
			}
		}
	}
}
namespace insight {
	bool was_invisible_on = false;
	void self::invisible(toggle_int_feature* feature, bool& value, int& value2) {
		if (!value) {
			if (was_invisible_on) {
				ENTITY::SET_ENTITY_VISIBLE(globals::h_local_ped(), true, 0);
				NETWORK::SET_ENTITY_LOCALLY_VISIBLE(globals::h_local_ped());
				was_invisible_on = false;
			}
			return;
		}
		was_invisible_on = true;
		if (value2 == 0) {
			ENTITY::SET_ENTITY_VISIBLE(globals::h_local_ped(), !value, 0);
		}
		else if (value2 == 1) {
			ENTITY::SET_ENTITY_VISIBLE(globals::h_local_ped(), !value, 0);
			if (globals::in_multiplayer()) {
				NETWORK::SET_ENTITY_LOCALLY_VISIBLE(globals::h_local_ped());
			}
		}
	}


	void wall_run_on_key_down() {
		PAD::DISABLE_CONTROL_ACTION(2, 44, true);
		//if (!PAD::IS_CONTROL_PRESSED(2, 44))
		//	return;
		Vector3 ong = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(globals::h_local_ped(), Vector3(0, 0, 0));
		Vector3 ong1 = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(globals::h_local_ped(), Vector3(0, 5, 0));

		auto cast = tasks::get()->point_to_point_cast(ong, ong1);
		if (cast) {
			if (PAD::IS_CONTROL_JUST_PRESSED(2, 44)) {
				TASK::CLEAR_PED_TASKS_IMMEDIATELY(globals::h_local_ped());
				STREAMING::REQUEST_ANIM_DICT("move_m@gangster@generic");
				TASK::TASK_PLAY_ANIM(globals::h_local_ped(), "move_m@gangster@generic", "sprint", 8.f, 1.f, -1, 1, 0.0, false, false, false);
				if (ENTITY::IS_ENTITY_PLAYING_ANIM(globals::h_local_ped(), "move_m@gangster@generic", "move", 1)) {
					PED::SET_PED_GRAVITY(globals::h_local_ped(), false);
					auto rotation = ENTITY::GET_ENTITY_ROTATION_VELOCITY(globals::h_local_ped());
					ENTITY::SET_ENTITY_ROTATION(globals::h_local_ped(), 92.F, rotation.y, rotation.z, 0, 0);
					ENTITY::APPLY_FORCE_TO_ENTITY(globals::h_local_ped(), 1, Vector3(0.0f, 0.0f, 0.2f), Vector3(0.0f, 0.0f, 0.0f), 0, 1, 1, 1, 0, 1);
				}
			}
			notify::subtitle("sfdf");
		}
		if (ENTITY::IS_ENTITY_PLAYING_ANIM(globals::h_local_ped(), "move_m@gangster@generic", "move", 1) && !cast) {
			TASK::CLEAR_PED_TASKS_IMMEDIATELY(globals::h_local_ped());
			TASK::TASK_CLIMB(globals::h_local_ped(), false);
			notify::subtitle("dfg");
		}
	}

	void wall_run_on_key_up() {
		if (ENTITY::IS_ENTITY_PLAYING_ANIM(globals::h_local_ped(), "move_m@gangster@generic", "move", 1) && !PAD::IS_CONTROL_JUST_PRESSED(2, 44)) {
			return;
		}
		//TASK::CLEAR_PED_TASKS_IMMEDIATELY(globals::h_local_ped());
		PED::SET_PED_GRAVITY(globals::h_local_ped(), true);
	}

	void self::wall_runner(toggle_feature* feature, bool& value) {
		if (!value) {
			return;
		}
		wall_run_on_key_down();
		//	wall_run_on_key_up();
	}
}
namespace insight {
	bool g_injured_flag_reset = false;

	void self::injured(toggle_feature* feature, bool& value) {
		if (value)
			PED::SET_PED_MOVEMENT_CLIPSET(PLAYER::PLAYER_PED_ID(), "move_injured_generic", 1.f);
		else if (value != g_injured_flag_reset)
		{
			PED::RESET_PED_MOVEMENT_CLIPSET(PLAYER::PLAYER_PED_ID(), 1.f);
		}

		g_injured_flag_reset = value;
	}
}
namespace insight {
	void self::ingored_by_peds(toggle_feature* feature, bool& value) {
		if (!value)
			return;

		for (Ped ped : tasks::get_world_entities(false, true, false)) {
			PED::SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(ped, true);
			PED::SET_PED_FLEE_ATTRIBUTES(ped, 0, false);
			PED::SET_PED_COMBAT_ATTRIBUTES(ped, 17, false);
		}
	}
}
namespace insight {

	bool was_god_mode_on = false;
	void self::god_mode(toggle_feature* feature, bool& value) {
		if (!value) {
			if (was_god_mode_on) {
				tasks::set_entity_damage_bits(globals::c_local_ped(), false);
				if (auto ped_factory = *reinterpret_cast<std::add_pointer_t<u64>>(insight::pointers::get()->g_ped_factory)) {
					if (auto player_ped = *reinterpret_cast<std::add_pointer_t<u64>>(ped_factory + 0x8)) {
						*reinterpret_cast<std::add_pointer_t<bool>>(player_ped + 0x189) = false;
					}
				}
				was_god_mode_on = false;
			}
			return;
		}
		if (ENTITY::IS_ENTITY_DEAD(globals::h_local_ped(), 0)) {
			was_god_mode_on = false;
			return;
		}
		if (STREAMING::IS_PLAYER_SWITCH_IN_PROGRESS()) {
			was_god_mode_on = false;
			return;
		}
		uint32_t damage_bits = globals::c_local_ped()->m_damage_bits;
		bool is_god_on = (damage_bits & static_cast<uint32_t>(eEntityProofs::GOD)) != 0;
		if (!is_god_on) {
			was_god_mode_on = false;
		}
		if (!was_god_mode_on) {
			if (globals::h_local_ped()) {
				tasks::set_entity_damage_bits(globals::c_local_ped(), true);
				if (auto ped_factory = *reinterpret_cast<std::add_pointer_t<u64>>(insight::pointers::get()->g_ped_factory)) {
					if (auto player_ped = *reinterpret_cast<std::add_pointer_t<u64>>(ped_factory + 0x8)) {
						*reinterpret_cast<std::add_pointer_t<bool>>(player_ped + 0x189) = true;
					}
				}
				was_god_mode_on = true;
			}
		}

	}
}

namespace insight {
	Vector3 god_finger_force_vec = { 0,0,0 };
	void god_finger_force(int i, float speed)
	{
		if (SYSTEM::VDIST(globals::h_local_ped_pos(), ENTITY::GET_ENTITY_COORDS(i, 0)) < 100) {
			Vector3 sub_vec = god_finger_force_vec - ENTITY::GET_ENTITY_COORDS(i, 0);
			if (tasks::get()->get_control_of_entity_tick(i)) {
				tasks::apply_force_to_position(i, sub_vec, ENTITY::GET_ENTITY_VELOCITY(i), speed, 0.3);
			}
		}
	}

	Entity god_finger_entity;
	int god_finger_mode = 0;
	int god_finger_distance = 15;

	static timer god_finger_mode_switch_timer(std::chrono::milliseconds(120ms));
	void god_finger_mode_switch() {
		PAD::DISABLE_CONTROL_ACTION(0, (int)ControllerInputs::INPUT_CELLPHONE_CAMERA_FOCUS_LOCK, true);
		if (god_finger_mode_switch_timer.update()) {
			if (PAD::IS_DISABLED_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_CELLPHONE_CAMERA_FOCUS_LOCK)) {
				if (god_finger_mode == 0) {
					notify::subtitle(xorstr_("God Finger: All Entites"));
					god_finger_mode = 1;
				}
				else if (god_finger_mode == 1) {
					notify::subtitle(xorstr_("God Finger: Single"));
					god_finger_mode = 0;
				}
			}
		}
	}
	void god_finger_draw_markers()
	{
		tasks::draw_marker(eMarkerType::MarkerTypeDebugSphere, vectors::get()->get_front_camera_coordinates_local(god_finger_distance), 0.5, 0, 120, 200, 100);
		Vector3 ent_cor = ENTITY::GET_ENTITY_COORDS(god_finger_entity, 0);
		ent_cor.z = ent_cor.z + 1.0;
		tasks::draw_marker(eMarkerType::MarkerTypeUpsideDownCone, ent_cor, 0.5, 0, 120, 200, 100);
	}
	bool was_god_finger = false;
	void self::god_finger(toggle_float_feature* feature, bool& value, float& value2) {
		if (!value) {
			if (was_god_finger)
				was_god_finger = false;
			return;
		}
		god_finger_distance = "god_finger_distance"_FF->m_value.floating_point;
		if (!was_god_finger) {
			notify::send("god_finger"_tif->m_name,
				globals::is_using_controller() ?
				"To increase/decrease distance use D-Pad Right/Finger Aim Key. To Change Mode Use RT."
				:
				"To increase/decrease distance use B/Finger Aim Key. To Change Mode Use L Key.");

			was_god_finger = true;
		}
		if (god_finger_mode == 0) {
			if (scripted_globals::is_local_player_pointing() == 3) {
				scripted_globals::is_local_player_pointing(NETWORK::GET_NETWORK_TIME());
				god_finger_mode_switch();
				god_finger_draw_markers();
				if (!god_finger_entity) {
					god_finger_entity = tasks::get_closest_screen_entity();
				}
				else {
					Vector3 Sub_Vect = vectors::get()->get_front_camera_coordinates_local(god_finger_distance) - ENTITY::GET_ENTITY_COORDS(god_finger_entity, 0);
					if (tasks::get_control_of_entity_tick(god_finger_entity)) {
						tasks::apply_force_to_position(god_finger_entity, Sub_Vect, ENTITY::GET_ENTITY_VELOCITY(god_finger_entity), value2, 0.3);
					}
				}
			}
			else {
				god_finger_entity = 0;
			}
		}
		if (god_finger_mode == 1) {
			if (scripted_globals::is_local_player_pointing() == 3) {
				scripted_globals::is_local_player_pointing(NETWORK::GET_NETWORK_TIME());
				god_finger_mode_switch();
				god_finger_draw_markers();
				god_finger_force_vec = vectors::get()->get_front_camera_coordinates_local(god_finger_distance);
				for (auto i : tasks::get_world_entities(true, true, false)) {
					if (!ENTITY::IS_ENTITY_STATIC(i))
						god_finger_force(i, value2);
				}
			}
			else {
				god_finger_entity = 0;
			}
		}
	}
}
namespace insight {
	bool was_free_cam_on = false;
	void self::free_cam(toggle_int_feature* feature, bool& value, int& value2) {
		if (!value) {
			if (was_free_cam_on)
			{

				if (CAM::DOES_CAM_EXIST(globals::m_freecam_handle)) {
					if (value2 == 1)
					{
						Vector3 teleport_pos = CAM::GET_CAM_COORD(globals::m_freecam_handle);
						PED::SET_PED_COORDS_KEEP_VEHICLE(globals::h_local_ped(), teleport_pos);
						Vector3 cam_rotation = CAM::GET_CAM_ROT(globals::m_freecam_handle, 0);
						ENTITY::SET_ENTITY_ROTATION(globals::h_local_vehicle() ? globals::h_local_vehicle() : globals::h_local_ped(), cam_rotation.x, cam_rotation.y, cam_rotation.z, 0, 0);

					}
					CAM::SET_CAM_ACTIVE(globals::m_freecam_handle, false);
					CAM::RENDER_SCRIPT_CAMS(false, true, 1000, true, false, 1);
					CAM::DESTROY_CAM(globals::m_freecam_handle, false);
					STREAMING::SET_FOCUS_ENTITY(globals::h_local_ped());
				}
				was_free_cam_on = false;
			}
			return;
		}
		was_free_cam_on = true;
		if (!CAM::DOES_CAM_EXIST(globals::m_freecam_handle)) {
			Vector3 coords = ENTITY::GET_ENTITY_COORDS(globals::h_local_ped(), 1);
			globals::m_freecam_handle = CAM::CREATE_CAM("DEFAULT_SCRIPTED_CAMERA", 0);
			CAM::SET_CAM_ACTIVE(globals::m_freecam_handle, true);
			CAM::RENDER_SCRIPT_CAMS(true, true, 1000, true, false, 1);
			CAM::SET_CAM_COORD(globals::m_freecam_handle, { coords.x, coords.y, coords.z + 5.0f });
		}
		else {
			Vector3 cam_coords = CAM::GET_CAM_COORD(globals::m_freecam_handle);
			Vector3 gameplay_cam_rot = CAM::GET_GAMEPLAY_CAM_ROT(0);
			CAM::SET_CAM_ROT(globals::m_freecam_handle, { gameplay_cam_rot.x, gameplay_cam_rot.y, gameplay_cam_rot.z }, 2);

			if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), false)) {
				VEHICLE::SET_VEHICLE_FORWARD_SPEED(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false), 0.0f);
			}
			else {
				TASK::TASK_STAND_STILL(PLAYER::PLAYER_PED_ID(), 10);
			}

			Vector3 infront = vectors::get()->get_direction();

			int left_right = PAD::GET_CONTROL_VALUE(2, 188);
			int up_down = PAD::GET_CONTROL_VALUE(2, 189);

			auto w_down = GetKeyState('W') & 0x8000 || up_down == 0;
			auto s_down = GetKeyState('S') & 0x8000 || up_down == 254;
			auto d_down = GetKeyState('D') & 0x8000 || left_right == 254;
			auto a_down = GetKeyState('A') & 0x8000 || left_right == 0;

			if (w_down) {
				CAM::SET_CAM_COORD(globals::m_freecam_handle, cam_coords + infront * 2.f);
			}
			else if (s_down) {
				CAM::SET_CAM_COORD(globals::m_freecam_handle, cam_coords - infront * 2.f);
			}

			if (a_down) {
				Vector3 gameplay_cam_rot_new = gameplay_cam_rot;

				gameplay_cam_rot_new.x = 0.f;
				gameplay_cam_rot_new.y = 0.f;
				gameplay_cam_rot_new.z += 90.f;

				Vector3 new_coords = cam_coords + (vectors::get()->get_cam_direction(gameplay_cam_rot_new) * 2.f);
				CAM::SET_CAM_COORD(globals::m_freecam_handle, new_coords);
			}

			if (d_down) {
				Vector3 gameplay_cam_rot_new = gameplay_cam_rot;

				gameplay_cam_rot_new.x = 0.f;
				gameplay_cam_rot_new.y = 0.f;
				gameplay_cam_rot_new.z -= 90.f;

				Vector3 new_coords = cam_coords + (vectors::get()->get_cam_direction(gameplay_cam_rot_new) * 2.f);
				CAM::SET_CAM_COORD(globals::m_freecam_handle, new_coords);
			}


			STREAMING::SET_FOCUS_POS_AND_VEL({ cam_coords.x, cam_coords.y, cam_coords.z }, { 0, 0, 0 });
		}
	}
}
namespace insight {
	void set_other_fov(float val) {
		if (auto ped_factory = *reinterpret_cast<std::add_pointer_t<std::uint64_t>>(insight::pointers::get()->g_ped_factory)) {
			if (auto player_ped = *reinterpret_cast<std::add_pointer_t<std::uint64_t>>(ped_factory + 0x8)) {
				if (auto wep_mgr = *reinterpret_cast<std::add_pointer_t<std::uint64_t>>(player_ped + 0x10B8)) {
					if (auto wep_info = *reinterpret_cast<std::add_pointer_t<std::uint64_t>>(wep_mgr + 0x0020)) {
						*reinterpret_cast<std::add_pointer_t<std::float_t>>(wep_info + 0x02FC) = val;
						*reinterpret_cast<std::add_pointer_t<std::float_t>>(wep_info + 0x0308) = val;
						*reinterpret_cast<std::add_pointer_t<std::float_t>>(wep_info + 0x030C) = val;
					}
				}
			}
		}
	}
	bool was_fov_modifier_on = false;
	float default_cam_value = 55.0f;
	float default_cam_aim_value = 55.0f;
	void self::fov_modifier(toggle_float_feature* feature, bool& value, float& value2) {
		if (!value) {
			if (was_fov_modifier_on)
			{
				globals::c_local_cam()->m_cam_data->m_fov = default_cam_value;
				set_other_fov(default_cam_value);
				was_fov_modifier_on = false;
			}
			return;
		}
		globals::c_local_cam()->m_cam_data->m_fov = value2;
		set_other_fov(value2);
		was_fov_modifier_on = true;
	}
}
namespace insight {

	static timer create_drawing_sphere(std::chrono::seconds(2));
	float previews_value2 = 0.0f;
	bool has_range_changed = false;
	void self::force_field(toggle_float_feature* feature, bool& value, float& value2) {
		if (!value) {
			return;
		}
		if (value2 != previews_value2) {
			create_drawing_sphere.restart();
			has_range_changed = true;
			previews_value2 = value2;
		}
		Vector3 pedPos = ENTITY::GET_ENTITY_COORDS(globals::h_local_ped(), true);
		if (has_range_changed)
		{
			tasks::draw_marker(eMarkerType::MarkerTypeDebugSphere, pedPos, value2, 255, 0, 0, 60);
			if (create_drawing_sphere.update())
			{
				has_range_changed = false;
			}
		}
		if (value2 != 0) {
			std::vector<Entity> nearbyEntities = tasks::get_world_entities(true, true, false);

			for (const auto& entity : nearbyEntities) {
				if (ENTITY::DOES_ENTITY_EXIST(entity)) {
					Vector3 entityPos = ENTITY::GET_ENTITY_COORDS(entity, true);

					if (ENTITY::IS_ENTITY_A_PED(entity) && PED::IS_PED_A_PLAYER(entity))
					{
						FIRE::ADD_EXPLOSION(entityPos, 60, 5.f, false, true, 0.0f, true);
						return;
					}
					Vector3 direction = entityPos - pedPos;
					float distance = MISC::GET_DISTANCE_BETWEEN_COORDS(pedPos, entityPos, 1);

					if (distance < value2) {
						float force = 1.f;
						if (tasks::get_control_of_entity_tick(entity))
							ENTITY::APPLY_FORCE_TO_ENTITY(entity, 1, direction * force, Vector3(0.0f, 0.0f, 0.0f), 0, 0, 1, 1, 0, 1);
					}
				}
			}
		}
	}
}
namespace insight {
	struct heavyplayer_data {
		timer timer;
		Vector3 force;
		Vector3 hit;
	};
	std::unordered_map<Entity, heavyplayer_data> heavy_player_data;

	void heavy_player_effect(int i) {
		if (ENTITY::IS_ENTITY_TOUCHING_ENTITY(globals::h_local_ped(), i)) {

			Vector3 force = vectors::get()->get_front_camera_coordinates_local(20) - vectors::get()->get_front_camera_coordinates_local(0);
			Vector3 hit = ENTITY::GET_COLLISION_NORMAL_OF_LAST_HIT_FOR_ENTITY(i);

			if (heavy_player_data.find(i) == heavy_player_data.end())
				heavy_player_data.emplace(i, heavyplayer_data(timer(1s), force, hit));
		}
	}

	timer flash_sprint_timer(std::chrono::milliseconds(20));
	bool was_flash_sprint_on = false;
	float flash_sprint_speed = 0;
	void flash_sprint_reset() {
		if (was_flash_sprint_on) {
			globals::c_local_cam()->m_cam_data->m_fov = 55.f;
			ENTITY::SET_ENTITY_COLLISION(globals::h_local_ped(), 1, 1);
			was_flash_sprint_on = false;
			flash_sprint_speed = 0.f;
		}
	}
	void fast_sprint_fuc() {
		bool is_ped_sprinting = !PED::IS_PED_FALLING(globals::h_local_ped()) && !PED::IS_PED_JUMPING(globals::h_local_ped()) &&
			PAD::IS_DISABLED_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_SPRINT);

		if (is_ped_sprinting) {
			was_flash_sprint_on = true;
			if (flash_sprint_speed < 40.f)
				flash_sprint_speed += 0.1;
			else
				flash_sprint_speed += 0.01;
			PED::FORCE_PED_AI_AND_ANIMATION_UPDATE(globals::h_local_ped(), 1, 0);
			if ("player_flash_sprint_air"_tf->m_value.toggle) {

				if (ENTITY::GET_ENTITY_HEIGHT_ABOVE_GROUND(globals::h_local_ped()) > 5.f) {
					ENTITY::SET_ENTITY_COLLISION(globals::h_local_ped(), 0, 0);
				}
				else {
					ENTITY::SET_ENTITY_COLLISION(globals::h_local_ped(), 1, 1);
				}
				Vector3 pos_force = vectors::get()->get_front_camera_coordinates_local(20 * "player_flash_sprint_speed"_FF->m_value.floating_point) - globals::h_local_ped_pos();
				pos_force.z += 2.0f;
				ENTITY::SET_ENTITY_VELOCITY(globals::h_local_ped(), { pos_force.x,pos_force.y,pos_force.z });

			}
			else {
				Vector3 front = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(globals::h_local_ped(), { 0,(10 + flash_sprint_speed) * "player_flash_sprint_speed"_FF->m_value.floating_point,0 });
				Vector3 pos_force = vectors::get()->get_ground_coordinates({ front.x,front.y }) - globals::h_local_ped_pos();
				pos_force.z += 2.0f;
				ENTITY::SET_ENTITY_VELOCITY(globals::h_local_ped(), { pos_force.x,pos_force.y,pos_force.z * 2.f });
			}
			globals::c_local_cam()->m_cam_data->m_fov = (55.f + flash_sprint_speed) * "player_flash_sprint_fov"_FF->m_value.floating_point;

			if (flash_sprint_timer.update()) {
				tasks::get()->play_ptfx_on_ped_bone(globals::h_local_ped(), xorstr_("IK_R_Hand"), 71, 0.2);
				tasks::get()->play_ptfx_on_ped_bone(globals::h_local_ped(), xorstr_("IK_L_Hand"), 71, 0.2);
			}
		}
		else {
			flash_sprint_reset();
		}
	}
	void self::flash_sprint(toggle_feature* feature, bool& value) {
		if (!value) {
			flash_sprint_reset();
			return;
		}
		fast_sprint_fuc();
	}

	float entity_to_aim(float aimX, float entityX) {
		static float entity_velo;

		if (aimX > 0 && entityX > 0) entity_velo = aimX - (entityX);

		if (aimX < 0 && entityX < 0) entity_velo = aimX - (entityX);

		if (aimX > 0 && entityX < 0) entity_velo = aimX + (entityX);

		if (aimX < 0 && entityX > 0) entity_velo = aimX + (entityX);

		return entity_velo;
	}

	bool flash_mode_was_on;
	void self::flash_mode(toggle_float_feature* feature, bool& value, float& value2) {
		if (!value) {
			if (flash_mode_was_on) {
				globals::c_local_ped()->m_player_info->m_run_speed = "player_run_modifier"_tif->m_number_value.floating_point;
				"player_super_jump"_tif->m_toggle_value.toggle = false;
				flash_mode_was_on = false;
			}
			return;
		}

		bool is_ped_sprinting = TASK::IS_PED_RUNNING(globals::h_local_ped()) ||
			TASK::IS_PED_SPRINTING(globals::h_local_ped()) &&
			!PED::IS_PED_FALLING(globals::h_local_ped()) &&
			!PED::IS_PED_JUMPING(globals::h_local_ped()) &&
			PAD::IS_DISABLED_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_SPRINT);

		globals::c_local_ped()->m_player_info->m_run_speed = 2.f;

		Vector3 position = ENTITY::GET_ENTITY_COORDS(globals::h_local_ped(), false);

		if (is_ped_sprinting) {
			Vector3 self_cam_coord = vectors::get()->get_front_camera_coordinates_local(10 * value2);
			float ground_height;
			MISC::GET_GROUND_Z_FOR_3D_COORD(self_cam_coord, &ground_height, false, 0);
			self_cam_coord.z = ground_height;
			PED::SET_PED_CAN_RAGDOLL(globals::h_local_ped(), false);
			Vector3 pos_to_force = self_cam_coord - position;

			ENTITY::SET_ENTITY_VELOCITY(globals::h_local_ped(), pos_to_force);
			ENTITY::SET_ENTITY_ROTATION(globals::h_local_ped(), CAM::GET_GAMEPLAY_CAM_ROT(2).x, CAM::GET_GAMEPLAY_CAM_ROT(2).y, CAM::GET_GAMEPLAY_CAM_ROT(2).z, 2, 0);
			if ("flash_mode_trails"_tf->m_value.toggle) {
				tasks::play_ptfx_on_ped_bone(globals::h_local_ped(), "SKEL_R_UpperArm", 8, 0.55f, true, "flash_mode_color_1"_if->m_value.integer, "flash_mode_color_2"_if->m_value.integer, "flash_mode_color_3"_if->m_value.integer);
				tasks::play_ptfx_on_ped_bone(globals::h_local_ped(), "SKEL_L_UpperArm", 8, 0.55f, true, "flash_mode_color_1"_if->m_value.integer, "flash_mode_color_2"_if->m_value.integer, "flash_mode_color_3"_if->m_value.integer);
				tasks::play_ptfx_on_ped_bone(globals::h_local_ped(), "IK_L_Foot", 8, 0.55f, true, "flash_mode_color_1"_if->m_value.integer, "flash_mode_color_2"_if->m_value.integer, "flash_mode_color_3"_if->m_value.integer);
				tasks::play_ptfx_on_ped_bone(globals::h_local_ped(), "IK_R_Foot", 8, 0.55f, true, "flash_mode_color_1"_if->m_value.integer, "flash_mode_color_2"_if->m_value.integer, "flash_mode_color_3"_if->m_value.integer);
			}
			for (auto entity : tasks::get_world_entities(true, true, false))
			{
				heavy_player_effect(entity);
			}
			for (auto& [entity, data] : heavy_player_data)
			{
				if (data.timer.update())
				{
					heavy_player_data.erase(entity);
				}
				else {
					if (tasks::get_control_of_entity_tick(globals::h_local_ped()))
					{
						ENTITY::APPLY_FORCE_TO_ENTITY(entity, 1, data.force, data.hit, 0, 0, 0, 1, 0, 1);
						ENTITY::SET_ENTITY_NO_COLLISION_ENTITY(entity, globals::h_local_ped(), true);
					}
				}

			}
		}
		else if (PED::IS_PED_JUMPING(globals::h_local_ped())) {
			int SHoulderL = PED::GET_PED_BONE_INDEX(globals::h_local_ped(), 0xFCD9);
			int SHoulderR = PED::GET_PED_BONE_INDEX(globals::h_local_ped(), 0x29D2);
			tasks::play_ptfx_on_ped_bone(globals::h_local_ped(), SHoulderL, 8, 0.55f, true, "flash_mode_color_1"_if->m_value.integer, "flash_mode_color_2"_if->m_value.integer, "flash_mode_color_3"_if->m_value.integer);
			tasks::play_ptfx_on_ped_bone(globals::h_local_ped(), SHoulderR, 8, 0.55f, true, "flash_mode_color_1"_if->m_value.integer, "flash_mode_color_2"_if->m_value.integer, "flash_mode_color_3"_if->m_value.integer);
			tasks::play_ptfx_on_ped_bone(globals::h_local_ped(), "IK_L_Foot", 8, 0.55f, true, "flash_mode_color_1"_if->m_value.integer, "flash_mode_color_2"_if->m_value.integer, "flash_mode_color_3"_if->m_value.integer);
			tasks::play_ptfx_on_ped_bone(globals::h_local_ped(), "IK_R_Foot", 8, 0.55f, true, "flash_mode_color_1"_if->m_value.integer, "flash_mode_color_2"_if->m_value.integer, "flash_mode_color_3"_if->m_value.integer);
		}
		else {
			GRAPHICS::POP_TIMECYCLE_MODIFIER();
		}

		globals::c_local_ped()->m_player_info->m_stamina = 100.f;

		WEAPON::REMOVE_WEAPON_FROM_PED(globals::h_local_ped(), 0xFBAB5776); // remove parachute 

		if (PAD::IS_DISABLED_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_JUMP) && !PED::IS_PED_LANDING(globals::h_local_ped())) {
			TASK::TASK_JUMP(globals::h_local_ped(), true, true, true);
			ENTITY::APPLY_FORCE_TO_ENTITY(globals::h_local_ped(), 1, { 0.f, 14.f, 0.f }, { 0.f, 0.f, 0.f }, 1, true, true, true, false, true);
			ENTITY::APPLY_FORCE_TO_ENTITY(globals::h_local_ped(), 1, { 0.f, 0.0f, 10.f }, { 0.f, 0.f, 0.f }, 1, true, true, true, false, true);
		}

		flash_mode_was_on = true;
	}
}
namespace insight {
	static timer yield(std::chrono::seconds(3));
	void self::fast_respawn(toggle_int_feature* feature, bool& value, int& value2) {
		if (!value) {
			return;
		}

		if (PED::IS_PED_DEAD_OR_DYING(globals::h_local_ped(), true)) {
			if (value2 == 0)
				script::get_current()->yield(4s);

			Vector3 get_pos_coordinates = ENTITY::GET_ENTITY_COORDS(globals::h_local_ped(), 0);
			float spawn_range = 200.f;
			Vector3 set_final_coordinates = Vector3(get_pos_coordinates.x + MISC::GET_RANDOM_FLOAT_IN_RANGE(-spawn_range, spawn_range), get_pos_coordinates.y + MISC::GET_RANDOM_FLOAT_IN_RANGE(-spawn_range, spawn_range), 0);
			PED::RESURRECT_PED(globals::h_local_ped());
			ENTITY::SET_ENTITY_COORDS_NO_OFFSET(globals::h_local_ped(), vectors::get()->get_ground_coordinates(Vector2(set_final_coordinates.x, set_final_coordinates.y)), 0, 0, 0);
			TASK::CLEAR_PED_TASKS_IMMEDIATELY(globals::h_local_ped());
			MISC::FORCE_GAME_STATE_PLAYING();
			if (globals::in_multiplayer())
			{
				NETWORK::NETWORK_FADE_IN_ENTITY(globals::h_local_ped(), true, true);
			}
			PED::SET_PED_USING_ACTION_MODE(globals::h_local_ped(), false, -1, "DEFAULT_ACTION");
			WEAPON::SET_CURRENT_PED_WEAPON(globals::h_local_ped(), rage::joaat("weapon_unarmed"), true);
			tasks::disable_kill_screen();
			if (globals::get()->in_multiplayer())
				MISC::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("respawn_controller");
		}
	}
}
namespace insight {
	int pos_updater = 0;
	bool was_ebony_maw_on = false;
	struct box_data {
		Object obj;
		timer time_ptfx;
		bool attacking;
	};
	double convertTo360(double rotation) {
		rotation += 180.0;
		rotation = fmod(rotation, 360.0);
		return rotation;
	}
	std::vector<box_data> o;
	bool was_attak_mode_pressed = false;
	bool attak_mode_locked = false;
	int targeted_entity = 0;
	int num_attacks_entity = 0;
	void self::ebony_maw(toggle_feature* feature, bool& value) {
		if (!value) {
			if (was_ebony_maw_on) {
				for (int i = 0; i < o.size(); i++) {
					tasks::delete_entity(o[i].obj);
				}o.clear();
				attak_mode_locked = false;
				was_ebony_maw_on = false;
			}
			return;
		}
		if (!was_ebony_maw_on) {
			notify::send("player_ebony_maw"_tf->m_name,
				globals::is_using_controller() ?
				"Press D-Pad Down To Set Target."
				:
				"Press Z Key To Set Target.");

			was_ebony_maw_on = true;
		}
		if (o.size() < 7) {
			auto hash = "prop_cs_cardbox_01"_joaat;
			while (!STREAMING::HAS_MODEL_LOADED(hash)) {
				STREAMING::REQUEST_MODEL(hash);
				script::get_current()->yield();
			}
			Vector3 pos = globals::h_local_ped_pos();
			pos.z += 40.f;
			Object box = OBJECT::CREATE_OBJECT(hash, pos, globals::in_multiplayer(), false, false);
			o.push_back(box_data(box, (timer)std::chrono::milliseconds(1000ms), false));
		}
		bool is_aiming = PAD::IS_DISABLED_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_HUD_SPECIAL);
		for (int i = 0; i < o.size(); i++) {
			if (!o[i].attacking) {

				Vector3 pos = vectors::get()->get_custom_angle_vec_around_coord(globals::h_local_ped_pos(), is_aiming ? 3.f : 5.f, 0, 20, pos_updater + (i * 50));
				//	render::get()->draw_text_coordinates(std::to_string(pos_updater + (i * 20)).c_str(), pos, 255, 255, 255, 255, 0.30);

				Vector3 force = pos - ENTITY::GET_ENTITY_COORDS(o[i].obj, 0);
				if (tasks::get_control_of_entity_tick(o[i].obj))
					tasks::apply_force_to_position(o[i].obj, force, ENTITY::GET_ENTITY_VELOCITY(o[i].obj), "player_ebony_maw_idle_speed"_FF->m_value.floating_point,
						"player_ebony_maw_idle_frq"_FF->m_value.floating_point);
				if (o[i].time_ptfx.update())
					tasks::play_ptfx_bone_tick(o[i].obj, 0, "scr_rcbarry2", "scr_rcbarry2", "scr_clown_death", 0.1f);
				if (!attak_mode_locked) {
					PAD::DISABLE_CONTROL_ACTION(0, (int)ControllerInputs::INPUT_HUD_SPECIAL, TRUE);
					if (PAD::IS_DISABLED_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_HUD_SPECIAL)) {
						int ent = tasks::get_closest_screen_entity();
						Vector3 coords = ENTITY::GET_ENTITY_COORDS(ent, 0);
						coords.z += 2;
						tasks::draw_marker(eMarkerType::MarkerTypeUpsideDownCone, coords, 4, 255, 192, 203, 255, TRUE);
						targeted_entity = ent, 0;
						was_attak_mode_pressed = true;
					}
					else {
						if (was_attak_mode_pressed) {
							attak_mode_locked = true;
							was_attak_mode_pressed = false;
						}
					}
				}
				else {
					if (pos_updater + (i * 2) > 10 && pos_updater + (i * 2) < 15) {
						o[i].attacking = true;
					}
				}
			}
			else {
				Vector3 force = ENTITY::GET_ENTITY_COORDS(targeted_entity, 0) - ENTITY::GET_ENTITY_COORDS(o[i].obj, 0);
				if (tasks::get_control_of_entity_tick(o[i].obj))
					tasks::apply_force_to_position(o[i].obj, force, ENTITY::GET_ENTITY_VELOCITY(o[i].obj), "player_ebony_maw_throw_speed"_FF->m_value.floating_point,
						"player_ebony_maw_throw_frq"_FF->m_value.floating_point);
				if (o[i].time_ptfx.update())
					tasks::play_ptfx_bone_tick(o[i].obj, 0, "scr_rcbarry2", "scr_rcbarry2", "scr_clown_death", 0.1f);
				if (ENTITY::IS_ENTITY_TOUCHING_ENTITY(o[i].obj, targeted_entity)) {
					if (tasks::get_control_of_entity_tick(o[i].obj))
						tasks::delete_entity(o[i].obj);
					if (num_attacks_entity > 6) {
						num_attacks_entity = 0;
						attak_mode_locked = false;
					}
					num_attacks_entity++;
					FIRE::ADD_EXPLOSION(ENTITY::GET_ENTITY_COORDS(targeted_entity, 0), 18, 999.f, true, false, 1.f, 0);
					o.erase(o.begin() + i);
				}
			}
		}
		pos_updater++;
		if (pos_updater == 360) {
			pos_updater = 0;
		}
	}

	bool was_infamous_mode_on = false;
	static timer infamous_mode_fx_timer(100ms);
	static timer infamous_mode_v_timer(2000ms);
	bool infamous_mode_v_timer_updated = false;
	bool is_infamous_mode_flying_mode = false;
	void self::infamous_mode(toggle_feature* feature, bool& value) {
		if (!value) {
			was_infamous_mode_on = false;
			return;
		}
		if (!was_infamous_mode_on) {
			notify::send("Infamous Mod",
				globals::is_using_controller() ?
				"Usage : Press Jump To Fly And Attack Button To Shoot Electric Balls."
				:
				"Usage : Press Jump To Fly And Attack Button To Shoot Electric Balls.");

			was_infamous_mode_on = true;
		}

		if (PAD::IS_DISABLED_CONTROL_PRESSED(0, int(ControllerInputs::INPUT_JUMP))) {
			is_infamous_mode_flying_mode = true;
			const char* anin = "mini@racing@bike@";
			tasks::play_animation_with_settings(globals::h_local_ped(), anin, "celebrate_a", 999.F, 8.0F, 9999999, 0, -1, 0, 0, 0);
			if (ENTITY::IS_ENTITY_PLAYING_ANIM(globals::h_local_ped(), anin, "celebrate_a", 3)) {
				if (infamous_mode_fx_timer.update()) {
					tasks::get()->play_ptfx_on_ped_bone(globals::h_local_ped(), xorstr_("IK_R_Hand"), 26, 0.3);
					tasks::get()->play_ptfx_on_ped_bone(globals::h_local_ped(), xorstr_("IK_L_Hand"), 26, 0.3);
				}
				Vector3 rot = CAM::GET_GAMEPLAY_CAM_ROT(0);
				if (PAD::IS_DISABLED_CONTROL_PRESSED(0, int(ControllerInputs::INPUT_MOVE_LEFT_ONLY))) {
					ENTITY::SET_ENTITY_ROTATION(globals::h_local_ped(), rot.x, rot.y - 20, rot.z, 0, 0);
				}
				else if (PAD::IS_DISABLED_CONTROL_PRESSED(0, int(ControllerInputs::INPUT_MOVE_RIGHT_ONLY))) {
					ENTITY::SET_ENTITY_ROTATION(globals::h_local_ped(), rot.x, rot.y + 20, rot.z, 0, 0);
				}
				else {
					ENTITY::SET_ENTITY_ROTATION(globals::h_local_ped(), rot.x, rot.y, rot.z, 0, 0);
				}
				Vector3 force = vectors::get()->get_front_camera_coordinates_local(30 * "player_infamous_mode_flying_multiplier"_FF->m_value.floating_point) - globals::h_local_ped_pos();

				if (!infamous_mode_v_timer_updated) { force.z = 6; }
				else { force.z = -1; }

				if (infamous_mode_v_timer.update()) { infamous_mode_v_timer_updated = true; }
				ENTITY::SET_ENTITY_VELOCITY(globals::h_local_ped(), force);
			}
			if (ENTITY::GET_ENTITY_HEIGHT_ABOVE_GROUND(globals::h_local_ped()) > 4.0f) {
				ENTITY::SET_ENTITY_COLLISION(globals::h_local_ped(), 0, 0);
			}
			else {
				is_infamous_mode_flying_mode = false;
				ENTITY::SET_ENTITY_COLLISION(globals::h_local_ped(), 1, 1);
			}
		}
		else {
			infamous_mode_v_timer.restart();
			infamous_mode_v_timer_updated = false;
			TASK::CLEAR_PED_TASKS(globals::h_local_ped());
			ENTITY::SET_ENTITY_COLLISION(globals::h_local_ped(), 1, 1);
			is_infamous_mode_flying_mode = false;
		}
		PLAYER::DISABLE_PLAYER_FIRING(globals::player_id, 1);
		if (PAD::IS_DISABLED_CONTROL_PRESSED(0, int(ControllerInputs::INPUT_ATTACK))) {
			if (!is_infamous_mode_flying_mode) {
				Vector3 rot = ENTITY::GET_ENTITY_ROTATION(globals::h_local_ped(), 0);
				ENTITY::SET_ENTITY_ROTATION(globals::h_local_ped(), rot.x, rot.y, rot.z + 50, 0, 1);
			}
			Vector3 from = ENTITY::GET_ENTITY_BONE_POSTION(globals::h_local_ped(),
				ENTITY::GET_ENTITY_BONE_INDEX_BY_NAME(globals::h_local_ped(), "IK_R_Hand"));
			from.y += 1.f;
			bullet_ptfx::get()->shoot_ptfx_bullet(from, vectors::get()->get_front_camera_coordinates_local(999), 0,
				"player_infamous_mode_shotting_force"_FF->m_value.floating_point, 5000,
				ptfx_stuff_dat("weap_ch_vehicle_weapons", "muz_ch_tank_laser", 2.0f, 0, 0,
					"player_infamous_mode_owned_damage"_tf->m_value.toggle, globals::h_local_ped()),
				ptfx_bullet_impact_dat(true, 18, "player_infamous_mode_exp_sound"_tf->m_value.toggle,
					"player_infamous_mode_exp_visible"_tf->m_value.toggle, 0, 0, 0));
		}
	}
	void flappy_bird_fuc(float verticalForce, float horizontalForce, float upForce, float speed) {
		float frq = 0.3f;
		float ragdollDuration = 1000;
		if (PAD::IS_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_MOVE_UP_ONLY)) {
			Vector3 force = globals::h_local_ped_pos();
			force.y += verticalForce;
			tasks::apply_force_to_position(globals::h_local_ped(), force - globals::h_local_ped_pos(), ENTITY::GET_ENTITY_VELOCITY(globals::h_local_ped()), speed, frq);
			PED::SET_PED_TO_RAGDOLL(globals::h_local_ped(), ragdollDuration, ragdollDuration, 0, false, false, false);
		}

		if (PAD::IS_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_MOVE_DOWN_ONLY)) {
			Vector3 force = globals::h_local_ped_pos();
			force.y -= verticalForce;
			tasks::apply_force_to_position(globals::h_local_ped(), force - globals::h_local_ped_pos(), ENTITY::GET_ENTITY_VELOCITY(globals::h_local_ped()), speed, frq);
			PED::SET_PED_TO_RAGDOLL(globals::h_local_ped(), ragdollDuration, ragdollDuration, 0, false, false, false);
		}

		if (PAD::IS_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_MOVE_LEFT_ONLY)) {
			Vector3 force = globals::h_local_ped_pos();
			force.x -= horizontalForce;
			tasks::apply_force_to_position(globals::h_local_ped(), force - globals::h_local_ped_pos(), ENTITY::GET_ENTITY_VELOCITY(globals::h_local_ped()), speed, frq);
			PED::SET_PED_TO_RAGDOLL(globals::h_local_ped(), ragdollDuration, ragdollDuration, 0, false, false, false);
		}

		if (PAD::IS_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_MOVE_RIGHT_ONLY)) {
			Vector3 force = globals::h_local_ped_pos();
			force.x += horizontalForce;
			tasks::apply_force_to_position(globals::h_local_ped(), force - globals::h_local_ped_pos(), ENTITY::GET_ENTITY_VELOCITY(globals::h_local_ped()), speed, frq);
			PED::SET_PED_TO_RAGDOLL(globals::h_local_ped(), ragdollDuration, ragdollDuration, 0, false, false, false);
		}

		if (PAD::IS_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_JUMP)) {
			Vector3 force = globals::h_local_ped_pos();
			force.z += upForce;
			tasks::apply_force_to_position(globals::h_local_ped(), force - globals::h_local_ped_pos(), ENTITY::GET_ENTITY_VELOCITY(globals::h_local_ped()), speed, frq);
			PED::SET_PED_TO_RAGDOLL(globals::h_local_ped(), ragdollDuration, ragdollDuration, 0, false, false, false);
		}
	}
	bool was_flappy_bird_on = false;
	void self::flappy_bird(toggle_feature* feature, bool& value) {
		if (!value) {
			was_flappy_bird_on = false;
			return;
		}
		if (!was_flappy_bird_on) {
			notify::send("flappy_bird"_tf->m_name,
				globals::is_using_controller() ?
				"Controls WSAD & Jump Key."
				:
				"Controls Left Joystick & Jump Key.");
			was_flappy_bird_on = true;
		}
		flappy_bird_fuc("flappy_bird_vertical_force"_FF->m_value.floating_point, "flappy_bird_horizontal_force"_FF->m_value.floating_point,
			"flappy_bird_up_force"_FF->m_value.floating_point, "flappy_bird_up_speed"_FF->m_value.floating_point);
	}
}
namespace insight {
	bool was_drunk_mode_on = false;
	const char* drunk_effect = "DrugsDrivingIn";
	const char* drunkClipset;

	void play_drunk_screen_effect(bool play)
	{
		if (play)
		{
			if (!GRAPHICS::ANIMPOSTFX_IS_RUNNING(drunk_effect))
				GRAPHICS::ANIMPOSTFX_PLAY(drunk_effect, -1, true);
		}
		else
		{
			if (GRAPHICS::ANIMPOSTFX_IS_RUNNING(drunk_effect))
				GRAPHICS::ANIMPOSTFX_STOP(drunk_effect);
		}
	}

	void self::drunk_mode(toggle_int_feature* feature, bool& value, int& value2) {
		if (!value) {
			if (was_drunk_mode_on)
			{
				play_drunk_screen_effect(false);
				AUDIO::SET_PED_IS_DRUNK(globals::h_local_ped(), false);
				PED::RESET_PED_MOVEMENT_CLIPSET(globals::h_local_ped(), 1.0);
				was_drunk_mode_on = false;
			}
			return;
		}
		was_drunk_mode_on = true;
		if (value2 == 0)
		{
			drunkClipset = "MOVE_M@DRUNK@MODERATEDRUNK";
			play_drunk_screen_effect(false);
		}
		else if (value2 == 1)
		{
			drunkClipset = "MOVE_M@DRUNK@MODERATEDRUNK_HEAD_UP";
			play_drunk_screen_effect(false);
		}
		else if (value2 == 2)
		{
			drunkClipset = "move_m@drunk@verydrunk";
			play_drunk_screen_effect(false);

		}
		else if (value2 == 3)
		{
			drunkClipset = "move_m@drunk@verydrunk";
			play_drunk_screen_effect(true);

		}
		AUDIO::SET_PED_IS_DRUNK(globals::h_local_ped(), true);
		while (!STREAMING::HAS_CLIP_SET_LOADED(drunkClipset))
		{
			STREAMING::REQUEST_CLIP_SET(drunkClipset);
			script::get_current()->yield();
		}
		PED::SET_PED_MOVEMENT_CLIPSET(globals::h_local_ped(), drunkClipset, 1.0f);
	}
}
namespace insight {

	bool was_burning_man_on = false;
	bool was_burning_man_godmodecheck_on = false;
	void self::burning_man(toggle_feature* feature, bool& value) {
		if (!value) {
			was_burning_man_godmodecheck_on = false;
			if (was_burning_man_on) {
				FIRE::STOP_ENTITY_FIRE(globals::h_local_ped());
				was_burning_man_on = false;
			}
			return;
		}
		if (!FIRE::IS_ENTITY_ON_FIRE(globals::h_local_ped()))
		{
			if ("player_god_mode"_tf->m_value.toggle)
			{
				if (!was_burning_man_godmodecheck_on)
				{
					globals::c_local_ped()->m_damage_bits = 0;
					was_burning_man_godmodecheck_on = true;
				}
				else
				{
					// god mode problem hmm
				}
			}
			else { was_burning_man_godmodecheck_on = false; }

			FIRE::START_ENTITY_FIRE(globals::h_local_ped());
			was_burning_man_on = true;

		}
	}
}
namespace insight {

	void baba_yoyoyo_mode(int i)
	{
		Vector3 entites_coord = ENTITY::GET_ENTITY_COORDS(i, 0);
		Vector3 local_ped_coordinates = ENTITY::GET_ENTITY_COORDS(globals::h_local_ped(), 0);
		if (MISC::GET_DISTANCE_BETWEEN_COORDS(entites_coord, local_ped_coordinates, true) < 60.f)
		{
			Vector3 set_coord = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(globals::h_local_ped(), Vector3(0, 45, 0));
			Vector3 subed_vectors = set_coord - entites_coord;
			ENTITY::SET_ENTITY_NO_COLLISION_ENTITY(globals::h_local_ped(), i, true);
			if (tasks::get_control_of_entity_tick(i))
				ENTITY::APPLY_FORCE_TO_ENTITY(i, 1, subed_vectors * 0.06f, Vector3(0.0f, 0.0f, 0.0f), 0, 0, 1, 1, 0, 1);
		}
	}

	bool was_baba_yoga_on = false;
	static timer rpg_shoot_delay(std::chrono::milliseconds(50));
	void self::baba_yoga(toggle_int_feature* feature, bool& value, int& value2) {
		if (!value) {
			if (was_baba_yoga_on) {
				TASK::CLEAR_PED_TASKS_IMMEDIATELY(globals::h_local_ped());
				PED::SET_PED_CAN_RAGDOLL(globals::h_local_ped(), true);
				//	ENTITY::SET_ENTITY_COLLISION(globals::h_local_ped(), true, true);
				ENTITY::FREEZE_ENTITY_POSITION(globals::h_local_ped(), false);

				was_baba_yoga_on = false;
			}
			return;
		}
		if (!was_baba_yoga_on) {
			notify::send("player_ebony_maw"_tif->m_name,
				globals::is_using_controller() ?
				"To move forward, use the joystick. Press the sprint button for speed boost,aim to go up and press shoot button to shoot rockets."
				:
				"To move forward, press W, use left mouse button to shoot rockets,use shift for speed boost and right click to go up.");

			//	ENTITY::SET_ENTITY_COLLISION(globals::h_local_ped(), false, false);
			was_baba_yoga_on = true;
		}
		PED::SET_PED_CAN_RAGDOLL(globals::h_local_ped(), false);
		CAM::STOP_GAMEPLAY_CAM_SHAKING(TRUE);
		const char* anim = "rcmcollect_paperleadinout@";
		const char* animid = "meditiate_idle";

		tasks::play_animation_tick(globals::h_local_ped(), anim, animid, 1);

		Vector3 local_ped_coorinates = ENTITY::GET_ENTITY_COORDS(globals::h_local_ped(), true);

		Vector3 local_ped_rotation = ENTITY::GET_ENTITY_ROTATION(globals::h_local_ped(), 2);
		ENTITY::SET_ENTITY_ROTATION(globals::h_local_ped(), local_ped_rotation.x, local_ped_rotation.y, local_ped_rotation.z + "player_abilities_baba_yoga_rotation_speed"_FF->m_value.floating_point, 2, 0);

		if (PAD::IS_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_MOVE_UP_ONLY)) {
			Vector3 camera_direction = vectors::get()->get_direction();
			bool sprint_pressed = PAD::IS_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_SPRINT);
			float speed = sprint_pressed ? 1.0f * "player_abilities_baba_yoga_speed_multiplier"_FF->m_value.floating_point :
				0.5f * "player_abilities_baba_yoga_speed_multiplier"_FF->m_value.floating_point;
			if (PAD::IS_CONTROL_PRESSED(1, (int)ControllerInputs::INPUT_AIM)) {
				camera_direction.z = camera_direction.z + (0.4f * "player_abilities_baba_yoga_zspeed_multiplier"_FF->m_value.floating_point);
			}
			Vector3 coordinates = local_ped_coorinates + (camera_direction * speed);
			ENTITY::SET_ENTITY_COORDS_NO_OFFSET(globals::h_local_ped(), coordinates, true, true, true);

		}
		ENTITY::FREEZE_ENTITY_POSITION(globals::h_local_ped(), true);

		const char* particle_asset = "scr_rcbarry2";
		const char* particle_name = "scr_clown_bul";
		tasks::play_ptfx_bone_tick(globals::h_local_ped(), ENTITY::GET_ENTITY_BONE_INDEX_BY_NAME(globals::h_local_ped(), "IK_L_Hand"), particle_asset, particle_asset, particle_name, 0.08f);
		tasks::play_ptfx_bone_tick(globals::h_local_ped(), ENTITY::GET_ENTITY_BONE_INDEX_BY_NAME(globals::h_local_ped(), "IK_R_Hand"), particle_asset, particle_asset, particle_name, 0.08f);
		if (value2 == 0) {
			std::vector<Entity> nearbyEntities = tasks::get_world_entities(true, true, false);
			for (const auto& entity : nearbyEntities) {
				bool is_player = ENTITY::IS_ENTITY_A_PED(entity) && PED::IS_PED_A_PLAYER(entity);
				if (!is_player) {
					baba_yoyoyo_mode(entity);
				}
			}
		}
		if (PAD::IS_CONTROL_PRESSED(1, (int)ControllerInputs::INPUT_ATTACK)) {
			if (rpg_shoot_delay.update()) {
				Vector3 shoot_pos = vectors::get()->get_front_camera_coordinates_local(50);
				Vector3 shoot_from = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(globals::h_local_ped(), Vector3(MISC::GET_RANDOM_FLOAT_IN_RANGE(-2, 2), 4, MISC::GET_RANDOM_FLOAT_IN_RANGE(-2, 2)));
				MISC::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(shoot_from, shoot_pos, 999, false, 0xB1CA77B1, NULL, 1, 1, 1000);
			}
			if (!WEAPON::HAS_PED_GOT_WEAPON(globals::h_local_ped(), 0xB1CA77B1, 0)) {
				WEAPON::GIVE_DELAYED_WEAPON_TO_PED(globals::h_local_ped(), 0xB1CA77B1, 1, 0);
			}
		}
	}
}
namespace insight {
	void gain_health()
	{
		Ped self = globals::h_local_ped();
		float fHealth = ENTITY::GET_ENTITY_HEALTH(self);
		float fHealthMax = PED::GET_PED_MAX_HEALTH(self);
		float value = 1.0f;
		{
			{
				value += fHealth;
				if (fHealth < fHealthMax) {
					fHealth = value;
					ENTITY::SET_ENTITY_HEALTH(self, (int)value, 0);
				}
				if (fHealth == fHealthMax) {
					fHealth = fHealthMax;
				}

			}
		}
	}
	void self::auto_heal(toggle_int_feature* feature, bool& value, int& value2) {
		if (!value)
			return;
		static timer delay(0ms);
		delay.setdelay((std::chrono::milliseconds)"player_auto_armor_rate"_if->m_value.integer);
		if (delay.update()) {
			if (value2 == 0)
			{
				gain_health();
			}
			else if (value2 == 1)
			{
				if (PED::IS_PED_IN_COVER(globals::h_local_ped(), 0))
				{
					gain_health();
				}
			}
			else if (value2 == 2)
			{
				if (tasks::is_ped_shooting(globals::h_local_ped())) {
					gain_health();
				}
			}
			else if (value2 == 3)
			{
				if (TASK::IS_PED_RUNNING(globals::h_local_ped()) || TASK::IS_PED_SPRINTING(globals::h_local_ped())) {
					gain_health();
				}
			}

		}

	}
}
namespace insight {
	void self::auto_clean(toggle_feature* feature, bool& value) {
		if (!value) {
			return;
		}
		tasks::clean_ped(globals::h_local_ped());
	}
}
namespace insight {
	void gain_armor()
	{
		if (PED::GET_PED_ARMOUR(globals::h_local_ped()) < PLAYER::GET_PLAYER_MAX_ARMOUR(globals::player_id)) {
			PED::ADD_ARMOUR_TO_PED(globals::h_local_ped(), 1);
		}
	}
	void tick_armor(int mode) {
		static timer delay(0ms);
		delay.setdelay((std::chrono::milliseconds)"player_auto_heal_rate"_if->m_value.integer);
		if (delay.update()) {
			if (mode == 0)
			{
				gain_armor();
			}
			else if (mode == 1)
			{
				if (PED::IS_PED_IN_COVER(globals::h_local_ped(), 0)) {
					gain_armor();
				}
			}
			else if (mode == 2)
			{
				if (tasks::is_ped_shooting(globals::h_local_ped())) {
					gain_armor();
				}
			}
			else if (mode == 3)
			{
				if (TASK::IS_PED_RUNNING(globals::h_local_ped()) || TASK::IS_PED_SPRINTING(globals::h_local_ped())) {
					gain_armor();
				}
			}
		}
	}
	void self::auto_armor(toggle_int_feature* feature, bool& value, int& value2) {
		if (!value)
			return;
		tick_armor(value2);
	}
}
namespace insight {
	Entity alladin_ride;
	float alladin_ride_speed;
	Entity alladin_weapon;
	Vector3 alladin_weapon_shoot_coord;
	int alladin_weapon_timer = 0;

	int alladin_force_charg = 0;
	Vector3 alladin_force_pos;
	void alladin_force(int i)
	{
		if (MISC::GET_DISTANCE_BETWEEN_COORDS(ENTITY::GET_ENTITY_COORDS(alladin_ride, 0), ENTITY::GET_ENTITY_COORDS(i, 0), 1) < 100)
		{
			Vector3 sub_vec = alladin_force_pos - ENTITY::GET_ENTITY_COORDS(i, 0);
			if (tasks::get_control_of_entity_tick(i))
				ENTITY::APPLY_FORCE_TO_ENTITY(i, 3, sub_vec, Vector3(0.0f, 0.f, 0.f), 0, 0, 1, 1, 0, 1);
		}
	}
	bool was_alladin_carpet_on = false;
	void self::alladin_carpet(toggle_feature* feature, bool& value) {
		if (!value) {
			if (was_alladin_carpet_on)
			{
				if (ENTITY::DOES_ENTITY_EXIST(alladin_ride))
				{
					ENTITY::DETACH_ENTITY(globals::h_local_ped(), 1, 1);
					ENTITY::DELETE_ENTITY(&alladin_ride);
				}
				script::get_current()->yield(2s);
				TASK::CLEAR_PED_TASKS_IMMEDIATELY(globals::h_local_ped());
				was_alladin_carpet_on = false;
			}
			return;
		}
		Hash carpet = rage::joaat("p_yoga_mat_03_s"); // carpet hash
		Hash weapon = rage::joaat("prop_golf_ball"); // weapon hash
		bool is_ped_jumping = PAD::IS_CONTROL_JUST_PRESSED(0, (int)ControllerInputs::INPUT_JUMP);
		bool is_ped_aim = PAD::IS_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_AIM);
		bool is_ped_attacking = PAD::IS_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_ATTACK);
		bool is_ped_attac_released = PAD::IS_CONTROL_JUST_RELEASED(0, (int)ControllerInputs::INPUT_ATTACK);
		bool does_ride_exist = ENTITY::DOES_ENTITY_EXIST(alladin_ride);
		bool does_weapon_exist = ENTITY::DOES_ENTITY_EXIST(alladin_weapon);

		//weapon have a bug sometimes here is fix alladin_weapon
		if (does_weapon_exist)
		{
			if (alladin_weapon_timer > 300) // est  2~4 secs
			{
				ENTITY::SET_ENTITY_AS_NO_LONGER_NEEDED(&alladin_weapon);
				ENTITY::DELETE_ENTITY(&alladin_weapon); //end weapon

			}
			alladin_weapon_timer++;
		}
		while (!STREAMING::HAS_MODEL_LOADED(carpet) && !STREAMING::HAS_MODEL_LOADED(weapon)) // here we have model loaded always so we don't have to wait to spawn it.again and again.
		{
			STREAMING::REQUEST_MODEL(carpet);
			STREAMING::REQUEST_MODEL(weapon);
			script::get_current()->yield();

		}
		if (is_ped_jumping)
		{
			if (!does_ride_exist)
				alladin_ride = OBJECT::CREATE_OBJECT(carpet, globals::h_local_ped_pos(), globals::in_multiplayer(), 0, 1); // creating ride when jumping
			else
			{
				ENTITY::DETACH_ENTITY(globals::h_local_ped(), 1, 1);
				TASK::CLEAR_PED_TASKS_IMMEDIATELY(globals::h_local_ped());
				ENTITY::DELETE_ENTITY(&alladin_ride);
			}
		}
		if (does_ride_exist)
		{
			was_alladin_carpet_on = true;
			Vector3 self_cam_coord = vectors::get()->get_front_camera_coordinates_local(PAD::IS_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_MOVE_UP_ONLY) ? (20 + (int)ENTITY::GET_ENTITY_SPEED(alladin_ride)) * "player_aladdin_magic_carpet_speed"_FF->m_value.floating_point : 20);
			if (!ENTITY::IS_ENTITY_ATTACHED_TO_ENTITY(globals::h_local_ped(), alladin_ride))
				ENTITY::ATTACH_ENTITY_TO_ENTITY(globals::h_local_ped(), alladin_ride, 0, Vector3(1.f, 0.f, 1.2f), Vector3(0, 0, 90), 1, 1, 0, 1, 2, 1, 0); // attachments

			tasks::play_animation_tick(globals::h_local_ped(), (char*)"missfbi5ig_30monkeys", (char*)"monkey_c_idle", 1); // amimation with loop flag
			//	AUDIO::PLAY_SOUND_FROM_ENTITY(56/*just so its different*/, "WIND", alladin_ride, "CONSTRUCTION_ACCIDENT_1_SOUNDS", g_local::online, 0); // wind sound fx broken :(
			if (is_ped_aim) // shoot stuff
			{
				//alladin_ride_speed = -30.f;
				GRAPHICS::DRAW_SPRITE("crosstheline", "timer_largecross_32", Vector2(0.5f, 0.5f), 0.005f, 0.005f, 0, 255, 255, 255, 200, 0, 0);

				tasks::play_animation_tick(globals::h_local_ped(), (char*)"rcmcollect_paperleadinout@", (char*)"meditiate_idle", 48); // amimation with upper body flag
				if (ENTITY::IS_ENTITY_PLAYING_ANIM(globals::h_local_ped(), "rcmcollect_paperleadinout@", "meditiate_idle", 3))
				{

					if (!does_weapon_exist)
					{
						alladin_weapon = OBJECT::CREATE_OBJECT(weapon, globals::h_local_ped_pos(), globals::in_multiplayer(), 0, 1); // creating weapon 
						alladin_weapon_shoot_coord = vectors::get()->get_front_camera_coordinates_local(1000);
						ENTITY::SET_ENTITY_VISIBLE(alladin_weapon, 0, 0);
						alladin_weapon_timer = 0;
					}
				}
			}
			if (is_ped_attacking) // force
			{
				alladin_force_pos = vectors::get()->get_front_camera_coordinates_local(40 * "player_aladdin_magic_carpet_speed"_FF->m_value.floating_point);
				std::vector<Entity> nearbyEntities = tasks::get_world_entities(true, true, false);
				for (const auto& entity : nearbyEntities) {
					alladin_force(entity);
				}
				//GRAPHICS::DRAW_MARKER_SPHERE(alladin_force_pos, 1, 255, 0, 0, 50);
				alladin_force_charg++;
			}
			else if (is_ped_attac_released)
			{
				alladin_force_pos = vectors::get()->get_front_camera_coordinates_local((40 + alladin_force_charg) * "player_aladdin_magic_carpet_speed"_FF->m_value.floating_point);
				std::vector<Entity> nearbyEntities = tasks::get_world_entities(true, true, false);
				for (const auto& entity : nearbyEntities) {
					alladin_force(entity);
				}


			}
			else { alladin_force_charg = 0; }
			//create_notification_bottom
			// force to carpet
			Vector3 pos_to_force = self_cam_coord - ENTITY::GET_ENTITY_COORDS(alladin_ride, 0); // use can just - if using latest  c++ lang
			ENTITY::SET_ENTITY_VELOCITY(alladin_ride, pos_to_force);
			ENTITY::SET_ENTITY_ROTATION(alladin_ride, CAM::GET_GAMEPLAY_CAM_ROT(2).x, CAM::GET_GAMEPLAY_CAM_ROT(2).y, CAM::GET_GAMEPLAY_CAM_ROT(2).z - 90.f, 2, 0);
			tasks::play_ptfx_bone_tick(globals::h_local_ped(), ENTITY::GET_ENTITY_BONE_INDEX_BY_NAME(globals::h_local_ped(), "IK_L_Foot"), (char*)"scr_rcbarry2", (char*)"scr_rcbarry2", (char*)"scr_exp_clown_trails", 0.1, 1, 255, 255, 255);
			tasks::play_ptfx_bone_tick(globals::h_local_ped(), ENTITY::GET_ENTITY_BONE_INDEX_BY_NAME(globals::h_local_ped(), "IK_R_Foot"), (char*)"scr_rcbarry2", (char*)"scr_rcbarry2", (char*)"scr_exp_clown_trails", 0.1, 1, 255, 255, 255);

			//force to weapon
			if (does_weapon_exist)
			{
				Vector3 live_alladin_weapon_coord = ENTITY::GET_ENTITY_COORDS(alladin_weapon, 0); // added here becuse we need it in multiple things

				Vector3 pos_to_force_weapon = alladin_weapon_shoot_coord - live_alladin_weapon_coord; // use can just - if using latest c++ lang
				ENTITY::SET_ENTITY_VELOCITY(alladin_weapon, Vector3(pos_to_force_weapon.x, pos_to_force_weapon.y, pos_to_force_weapon.z + 5));
				tasks::play_ptfx_bone_tick(alladin_weapon, 0, (char*)"core", (char*)"core", (char*)"sp_foundry_sparks", 4, 0, 0, 0, 0); // weapon fx and has sound with it

				//rotation so the fx looks cool
				Vector3 rotation = ENTITY::GET_ENTITY_ROTATION(alladin_weapon, 2);
				ENTITY::SET_ENTITY_ROTATION(alladin_weapon, MISC::GET_RANDOM_INT_IN_RANGE(-180, 180), MISC::GET_RANDOM_INT_IN_RANGE(-180, 180), MISC::GET_RANDOM_INT_IN_RANGE(-180, 180), 2, 1);

				FIRE::ADD_EXPLOSION(live_alladin_weapon_coord, 29, 99, false, true, 0, false); // power to weapon or use can use force and make it better

				if (ENTITY::GET_ENTITY_HEIGHT_ABOVE_GROUND(alladin_weapon) < 1.f)
				{
					ENTITY::SET_ENTITY_AS_NO_LONGER_NEEDED(&alladin_weapon);
					ENTITY::DELETE_ENTITY(&alladin_weapon); //end weapon
				}
			}

		}
	}
}
