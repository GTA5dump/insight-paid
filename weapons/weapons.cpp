#include "weapons.hpp"
#include "natives.hpp"
#include "../globals.hpp"
#include "util/script/script.hpp"
#include "../tasks.hpp"
#include "util/notify/notify.hpp"
#include "util/math/math.hpp"
#include "util/input/input.hpp"
#include "../scripted_globals.hpp"
#include <windows.h>
#include <mmsystem.h>
#include "cheat/menu/sub/option_flag.h"
#include "projectile_manager.hpp"
namespace insight
{
	void play_axe_sound_catch()
	{
		auto path = std::filesystem::path(std::getenv("appdata")).append("insight").append("sounds").append("axe").append("catch.wav");
		std::string soundPath = path.generic_string();
		if (!soundPath.empty()) {
			if (!PlaySoundA(soundPath.c_str(), NULL, SND_FILENAME | SND_ASYNC)) {
				std::cout << xorstr_("Failed to play sound: ") << GetLastError() << std::endl;
			}
		}
	}
	void play_axe_sound_throw()
	{
		auto path = std::filesystem::path(std::getenv("appdata")).append("insight").append("sounds").append("axe").append("throw.wav");
		std::string soundPath = path.generic_string();
		if (!soundPath.empty()) {
			if (!PlaySoundA(soundPath.c_str(), NULL, SND_FILENAME | SND_ASYNC)) {
				std::cout << xorstr_("Failed to play sound: ") << GetLastError() << std::endl;
			}
		}
	}
	void play_axe_sound_stomp()
	{
		auto path = std::filesystem::path(std::getenv("appdata")).append("insight").append("sounds").append("axe").append("stomp.wav");
		std::string soundPath = path.generic_string();
		if (!soundPath.empty()) {
			if (!PlaySoundA(soundPath.c_str(), NULL, SND_FILENAME | SND_ASYNC)) {
				std::cout << xorstr_("Failed to play sound: ") << GetLastError() << std::endl;
			}
		}
	}

	Entity Local_Flying_Axe;

	void Local_Misc_Flying_Axe_Fuc(int ent)
	{
		if (ent != globals::h_local_vehicle())
		{
			float K_SPPED = ENTITY::GET_ENTITY_SPEED(Local_Flying_Axe);
			if (K_SPPED < 0.5f)
				return;
			float PUSH_FORCE = K_SPPED * 3.5;

			if (ENTITY::IS_ENTITY_TOUCHING_ENTITY(Local_Flying_Axe, ent))
			{
				if (tasks::get_control_of_entity_tick(ent))
				{
					tasks::play_ptfx_bone_tick(ent, 0, xorstr_("scr_paletoscore"), xorstr_("scr_paletoscore"), xorstr_("scr_paleto_box_sparks"), 5);
					Vector3 CLisson_f = ENTITY::GET_COLLISION_NORMAL_OF_LAST_HIT_FOR_ENTITY(Local_Flying_Axe);
					Vector3 fent = Vector3(CLisson_f.x * PUSH_FORCE, CLisson_f.y * PUSH_FORCE, CLisson_f.z * PUSH_FORCE);
					ENTITY::APPLY_FORCE_TO_ENTITY(ent, 3, fent, Vector3(0.0f, 0.f, 0.f), 0, 0, 1, 1, 0, 1);
					if (ENTITY::IS_ENTITY_A_PED(ent)) PED::APPLY_DAMAGE_TO_PED(ent, 9999, 0, 0);
				}
			}
		}
	}
	Vector3 Local_Flying_Axe_Cor;
	Vector3 New_Local_Flying_Axe_Cor;
	Entity New_Local_Flying_Axe_Cor_TARGET;
	static timer Local_Flying_Axe_Delay(200ms);
	static timer Local_Flying_Axe_Delay_LOC(200ms);
	bool Local_Flying_Axe_Idle = false;
	bool Local_Flying_Axe_Attack = false;
	bool Local_Flying_Axe_Animation = true;

	void fuc_start_levitation_axe_auto(int i)
	{

		if (SYSTEM::VDIST(ENTITY::GET_ENTITY_COORDS(i, 0), ENTITY::GET_ENTITY_COORDS(globals::h_local_ped(), 0)) < 15) {
			if (!ENTITY::IS_ENTITY_DEAD(i, 0))
			{
				New_Local_Flying_Axe_Cor = ENTITY::GET_ENTITY_COORDS(i, 0);
				New_Local_Flying_Axe_Cor_TARGET = i;
			}
		}
	}

	int New_Local_Flying_Axe_Cor_Pos;
	int weapon_axe_was_flying_mode_on_rotadd = 0;
	int weapon_axe_was_flying_mode_on_speed = 0;
	bool weapon_axe_jumping = false;
	bool weapon_axe_jumping_and_in_sky = false;
	bool weapon_axe_stomp = false;
	bool weapon_axe_was_flying_mode_on = false;
	static timer weapon_axe_jump(500ms);
	bool was_weapon_axe_on = false;
	void weapon::weapon_axe(toggle_float_feature* feature, bool& value, float& value2)
	{
		detour::g_weapon_laxe = value;
		if (!value) {
			if (was_weapon_axe_on) {
				if (ENTITY::DOES_ENTITY_EXIST(Local_Flying_Axe)) {
					tasks::delete_entity(Local_Flying_Axe);
				}
				was_weapon_axe_on = false;
			}
			return;
		}
		//disable
		if (!was_weapon_axe_on) {
			notify::send("weapon_laxe"_tif->m_name,
				globals::is_using_controller() ?
				"To move fly hold attack button and joystick to forword when in air, To stomp jump and then hold jump button.To throw axe hold aim and hold attack button.To recall axe hold aim."
				:
				"To move fly hold attack button and w when in air, To stomp jump and then hold space.To throw axe hold aim and hold attack button.To recall axe hold aim.");
			was_weapon_axe_on = true;
		}
		if (!globals::h_local_vehicle(true)) {
			if (PED::IS_PED_JUMPING(globals::h_local_ped())) {
				if (weapon_axe_jumping) {
					Vector3 forcepos = vectors::get()->get_front_camera_coordinates_local(30) - vectors::get()->get_front_camera_coordinates_local(0);
					forcepos.z = forcepos.z + 10.0f * 5;
					ENTITY::SET_ENTITY_VELOCITY(globals::h_local_ped(), forcepos);
					weapon_axe_jumping = false;
					weapon_axe_jumping_and_in_sky = false;
					weapon_axe_jump.restart();
				}
				else {//weapon_axe_jump
					if (weapon_axe_jump.update()) {
						weapon_axe_jumping_and_in_sky = true;
					}
					if (weapon_axe_jumping_and_in_sky == true) {
						//weapon_axe_stomp = true;
						if (PAD::IS_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_JUMP)) {
							Vector3 forcepos = Vector3(0, 0, -500);
							ENTITY::SET_ENTITY_VELOCITY(globals::h_local_ped(), forcepos);
							const char* particle_asset = "scr_rcbarry2";
							const char* particle_name = "scr_clown_bul";
							tasks::play_ptfx_bone_tick(globals::h_local_ped(), ENTITY::GET_ENTITY_BONE_INDEX_BY_NAME(globals::h_local_ped(), "IK_L_Hand"), particle_asset, particle_asset, particle_name, 0.08f);
							tasks::play_ptfx_bone_tick(globals::h_local_ped(), ENTITY::GET_ENTITY_BONE_INDEX_BY_NAME(globals::h_local_ped(), "IK_R_Hand"), particle_asset, particle_asset, particle_name, 0.08f);


						}

					}
				}
			}
			else {
				weapon_axe_jumping = true;
				weapon_axe_jumping_and_in_sky = false;
			}
			if (weapon_axe_stomp) {
				if (ENTITY::GET_ENTITY_HEIGHT_ABOVE_GROUND(globals::h_local_ped()) < 2.f) {
					tasks::clear_tasks(globals::h_local_ped());
					const char* KROX_ANIMA = "amb@code_human_cower@male@exit";
					const char* KROX_ANIMAID = "exit";
					tasks::play_animation_with_settings(globals::h_local_ped(), KROX_ANIMA, KROX_ANIMAID, 99, 99, 500, 0, 0, 0, 0, 0);
					FIRE::ADD_EXPLOSION(globals::h_local_ped_pos(), (int)eExplosionTag::EXP_TAG_BOMB_INCENDIARY, 9999.f, TRUE, FALSE, 0.f, FALSE);
					play_axe_sound_stomp();
					weapon_axe_stomp = false;
				}
			}
			PAD::DISABLE_CONTROL_ACTION(0, (int)ControllerInputs::INPUT_ATTACK, true);
			if (ENTITY::GET_ENTITY_HEIGHT_ABOVE_GROUND(globals::h_local_ped()) < 8.f) {
				if (weapon_axe_was_flying_mode_on_rotadd > 0) {
					weapon_axe_was_flying_mode_on_rotadd--;
				}
				weapon_axe_was_flying_mode_on_speed = 30;
			}
			else if (ENTITY::GET_ENTITY_HEIGHT_ABOVE_GROUND(globals::h_local_ped()) > 8.f) {
				weapon_axe_stomp = true;
				if (weapon_axe_was_flying_mode_on_rotadd < 90) {
					weapon_axe_was_flying_mode_on_rotadd++;

				}
				weapon_axe_was_flying_mode_on_speed = 50;

			}
			if (PAD::IS_DISABLED_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_ATTACK) && !PAD::IS_DISABLED_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_AIM)) {
				weapon_axe_was_flying_mode_on = true;
				const char* KROX_ANIMA = "amb@code_human_cross_road@female@idle_enter";
				const char* KROX_ANIMAID = "idle_intro";
				tasks::play_animation_tick(globals::h_local_ped(), KROX_ANIMA, KROX_ANIMAID, 48);
				PED::FORCE_PED_MOTION_STATE(globals::h_local_ped(), -1871534317, 1, 1, 1);
				Vector3 local_ped_rotation = CAM::GET_GAMEPLAY_CAM_ROT(2);
				ENTITY::SET_ENTITY_ROTATION(globals::h_local_ped(), local_ped_rotation.x + -weapon_axe_was_flying_mode_on_rotadd, local_ped_rotation.y, local_ped_rotation.z, 2, 0);
				PED::SET_PED_CAN_RAGDOLL(globals::h_local_ped(), false);
				ENTITY::SET_ENTITY_COLLISION(globals::h_local_ped(), false, false);
				const char* particle_asset = "scr_trevor1";
				const char* particle_name = "scr_trev1_trailer_boosh";
				tasks::play_ptfx_bone_tick(globals::h_local_ped(), ENTITY::GET_ENTITY_BONE_INDEX_BY_NAME(globals::h_local_ped(), "IK_L_Hand"), particle_asset, particle_asset, particle_name, 0.08f);
				tasks::play_ptfx_bone_tick(globals::h_local_ped(), ENTITY::GET_ENTITY_BONE_INDEX_BY_NAME(globals::h_local_ped(), "IK_R_Hand"), particle_asset, particle_asset, particle_name, 0.08f);

				if (ENTITY::GET_ENTITY_HEIGHT_ABOVE_GROUND(globals::h_local_ped()) < 5.f) {
					Vector3 forcepos = Vector3(0, 0, 2);
					ENTITY::SET_ENTITY_VELOCITY(globals::h_local_ped(), forcepos);
				}
				else {
					if (PAD::IS_DISABLED_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_MOVE_UP_ONLY)) {

						Vector3 forcepos = vectors::get()->get_front_camera_coordinates_local(weapon_axe_was_flying_mode_on_speed) - vectors::get()->get_front_camera_coordinates_local(0);
						ENTITY::SET_ENTITY_VELOCITY(globals::h_local_ped(), forcepos);
					}
				}

			}
			else {
				if (weapon_axe_was_flying_mode_on) {
					weapon_axe_was_flying_mode_on_rotadd = 0;
					TASK::CLEAR_PED_TASKS(globals::h_local_ped());
					PED::SET_PED_CAN_RAGDOLL(globals::h_local_ped(), true);
					ENTITY::SET_ENTITY_COLLISION(globals::h_local_ped(), true, true);
					weapon_axe_was_flying_mode_on = false;
				}
			}
		}
		if (!ENTITY::DOES_ENTITY_EXIST(Local_Flying_Axe)) {
			Local_Flying_Axe_Delay.setdelay(200ms);
			if (Local_Flying_Axe_Delay.update()) {

				Vector3 COORDSPWA2 = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(globals::h_local_ped(), Vector3(0, 0, 6.5));
				Hash tospawn = rage::joaat("prop_ld_fireaxe");
				tasks::request_model(tospawn);
				Local_Flying_Axe = OBJECT::CREATE_OBJECT(tospawn, COORDSPWA2, globals::in_multiplayer(), 0, false);
				"player_no_ragdoll"_tif->m_toggle_value.toggle = true;
				"player_no_ragdoll"_tif->m_number_value.integer = 1;

				auto KROX_NET_ID = NETWORK::OBJ_TO_NET(Local_Flying_Axe);
				NETWORK::NETWORK_REGISTER_ENTITY_AS_NETWORKED(Local_Flying_Axe);
				NETWORK::SET_NETWORK_ID_EXISTS_ON_ALL_MACHINES(KROX_NET_ID, true); {

					ENTITY::SET_ENTITY_AS_MISSION_ENTITY(Local_Flying_Axe, true, true);
					DECORATOR::DECOR_REGISTER("MissionType", 3);
					ENTITY::SET_ENTITY_SHOULD_FREEZE_WAITING_ON_COLLISION(Local_Flying_Axe, false);
					DECORATOR::DECOR_SET_INT(Local_Flying_Axe, xorstr_("MPBitset"), 0);
					DECORATOR::DECOR_SET_INT(Local_Flying_Axe, xorstr_("MissionType"), 0);
					tasks::add_blip_entity(151, 38, Local_Flying_Axe);
				}
			}
		}
		else {
			Local_Flying_Axe_Cor.x += (New_Local_Flying_Axe_Cor.x - Local_Flying_Axe_Cor.x) * 0.2;
			Local_Flying_Axe_Cor.y += (New_Local_Flying_Axe_Cor.y - Local_Flying_Axe_Cor.y) * 0.2;
			Local_Flying_Axe_Cor.z += (New_Local_Flying_Axe_Cor.z - Local_Flying_Axe_Cor.z) * 0.2;
			Local_Flying_Axe_Delay_LOC.setdelay(300ms);
			Vector3 Dev_Veh_C = ENTITY::GET_ENTITY_COORDS(Local_Flying_Axe, 0);
			if (Local_Flying_Axe_Delay_LOC.update()) {
				Vector3 rot = ENTITY::GET_ENTITY_ROTATION(Local_Flying_Axe, 2);
				if (Local_Flying_Axe_Idle) {
					New_Local_Flying_Axe_Cor = vectors::get()->get_360_iterator_vec_around_coord(globals::h_local_ped_pos(), 20, 2, New_Local_Flying_Axe_Cor_Pos, 6);
				}

				if (Local_Flying_Axe_Idle || Local_Flying_Axe_Attack) {
					ENTITY::SET_ENTITY_ROTATION(Local_Flying_Axe, rot.x + 180, rot.y + 180, rot.z + 180, 2, 0);
				}
				tasks::play_ptfx_bone_tick(Local_Flying_Axe, 0, xorstr_("scr_powerplay"), xorstr_("scr_powerplay"), xorstr_("sp_powerplay_beast_appear_trails"), 0.5);
				tasks::play_ptfx_bone_tick(Local_Flying_Axe, 0, xorstr_("scr_paletoscore"), xorstr_("scr_paletoscore"), xorstr_("scr_paleto_box_sparks"), 0.1);
			}
			for (auto entityIndex : tasks::get_world_entities(true, true, false)) {
				Local_Misc_Flying_Axe_Fuc(entityIndex);

			}
			PAD::DISABLE_CONTROL_ACTION(0, (int)ControllerInputs::INPUT_AIM, TRUE);
			if (PAD::IS_DISABLED_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_AIM) && !globals::h_local_vehicle(true) &&
				globals::c_local_ped()->m_weapon_manager->m_selected_weapon_hash == -1569615261)
			{
				Vector3 camrot = CAM::GET_GAMEPLAY_CAM_ROT(2);
				ENTITY::SET_ENTITY_ROTATION((globals::h_local_ped()), camrot.x, camrot.y, camrot.z, 2, 0);
				Local_Flying_Axe_Idle = false;
				if (!Local_Flying_Axe_Attack) {
					New_Local_Flying_Axe_Cor = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(globals::h_local_ped(), { 0, 0, 0 });
					if (SYSTEM::VDIST(ENTITY::GET_ENTITY_COORDS(Local_Flying_Axe, 0), globals::h_local_ped_pos()) < 5) {
						if (Local_Flying_Axe_Animation) {
							const char* KROX_ANIMA = "cover@first_person@weapon@grenade";
							const char* KROX_ANIMAID = "low_l_throw_long";
							tasks::play_animation_tick(globals::h_local_ped(), KROX_ANIMA, KROX_ANIMAID, 48);

						}
						int bone = ENTITY::GET_ENTITY_BONE_INDEX_BY_NAME(globals::h_local_ped(), xorstr_("IK_R_Hand"));
						ENTITY::ATTACH_ENTITY_TO_ENTITY(Local_Flying_Axe, globals::h_local_ped(), bone, Vector3(0, -0.05, -0.05), Vector3(-61, 28.4, -48.8), false, false, true, true, 0, true, 0);
						play_axe_sound_catch();
					}
				}
				else {
					if (ENTITY::IS_ENTITY_ATTACHED(Local_Flying_Axe)) {
						play_axe_sound_throw();
						ENTITY::DETACH_ENTITY(Local_Flying_Axe, 0, true);
						if (!Local_Flying_Axe_Animation) {
							const char* KROX_ANIMA = "weapons@first_person@aim_rng@generic@projectile@grenade_str";
							const char* KROX_ANIMAID = "throw_m_fb_forward";
							tasks::play_animation_tick(globals::h_local_ped(), KROX_ANIMA, KROX_ANIMAID, 48);
						}


					}
				}
				PAD::DISABLE_CONTROL_ACTION(0, (int)ControllerInputs::INPUT_ATTACK, TRUE);
				if (PAD::IS_DISABLED_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_ATTACK)) {
					Local_Flying_Axe_Attack = true;
					New_Local_Flying_Axe_Cor = vectors::get()->get_front_camera_coordinates_local(150);
					PAD::SET_CONTROL_SHAKE(0, 1, 5);
				}
			}
			else {
				Local_Flying_Axe_Attack = false;
				Local_Flying_Axe_Idle = true;
			}
			Vector3 Sub_Vect = Local_Flying_Axe_Cor - Dev_Veh_C;
			Vector3 Vecoloty_k = ENTITY::GET_ENTITY_VELOCITY(Local_Flying_Axe);
			if (tasks::get_control_of_entity_tick(Local_Flying_Axe))
				Local_Flying_Axe_Idle ? tasks::apply_force_to_position(Local_Flying_Axe, Sub_Vect, Vecoloty_k, 0.5 * value2, 0.3) :
				tasks::apply_force_to_position(Local_Flying_Axe, Sub_Vect, Vecoloty_k, 2.5 * value2, 0.3);

		}
	}
}
namespace insight {
	Entity weapon_triggerbot_entity;
	Entity weapon_triggerbot_entity_target;

	void weapon::triggerbot(toggle_feature* feature, bool& value) {
		if (!value)
			return;
		if (input::get()->is_input_aim_pressed()) {
			Entity handle;
			ray_cast cast = tasks::create_cast(&handle);
			PAD::DISABLE_CONTROL_ACTION(0, (int)ControllerInputs::INPUT_ATTACK, true);
			if (handle) {
				if (!PED::IS_PED_RELOADING(globals::h_local_ped())) {
					if (ENTITY::IS_ENTITY_A_VEHICLE(handle)) {
						int numseat = tasks::get_vehicle_non_free_seats(handle);
						weapon_triggerbot_entity = VEHICLE::GET_PED_IN_VEHICLE_SEAT(handle, numseat, 0);
					}
					if (ENTITY::IS_ENTITY_A_PED(weapon_triggerbot_entity) && !PED::IS_PED_DEAD_OR_DYING(weapon_triggerbot_entity, 1)) {
						weapon_triggerbot_entity_target = weapon_triggerbot_entity;
						goto skiplebel;
					}
					if (ENTITY::IS_ENTITY_A_PED(handle) && !PED::IS_PED_DEAD_OR_DYING(handle, 1)) {
						weapon_triggerbot_entity_target = handle;
						goto skiplebel;
					}
					return;
				skiplebel:
					if (ENTITY::DOES_ENTITY_EXIST(weapon_triggerbot_entity_target)) {
						int boneindex = vectors::get()->get_random_vector(features_utility::get()->aimbot_selected_bones);
						if (boneindex) {
							Vector3 GET_COORDINATES_TO_SHOOT = ENTITY::GET_ENTITY_BONE_POSTION(weapon_triggerbot_entity_target, boneindex);
							{ PED::SET_PED_SHOOTS_AT_COORD(globals::h_local_ped(), GET_COORDINATES_TO_SHOOT, true); }
						}
					}
				}
			}
		}
	}
}
namespace insight {
	Vector3 tornado_entitiesVector_cam;
	timer tornado_gun_timer(std::chrono::milliseconds(200));

	void weapon::tornado_gun(toggle_int_feature* feature, bool& value, int& value2) {
		if (!value)
			return;


		if (input::get()->is_input_aim_pressed())
		{
			tornado_entitiesVector_cam = vectors::get()->get_front_camera_coordinates_local(150);
			int fixedHeight = 0;
			if (value2 == 0)
			{
				for (auto entityIndex : tasks::get_world_entities(true, true, false))
				{
					Vector3 entityPos = ENTITY::GET_ENTITY_COORDS(entityIndex, 0);
					tornado_entitiesVector_cam.z = tornado_entitiesVector_cam.z - 1 + fixedHeight * 0.018000;
					Vector3 forceVec = tornado_entitiesVector_cam - entityPos;
					if (tasks::get_control_of_entity_tick(entityIndex))
						ENTITY::APPLY_FORCE_TO_ENTITY(entityIndex, 3, forceVec, Vector3(0.0f, 0.0f, 0.0f), 0, 0, 1, 1, 0, 1);
					fixedHeight++;
				}
			}
			else if (value2 == 1)
			{
				Vector3 pos360 = vectors::get()->get_360_vec_around_coord(tornado_entitiesVector_cam, 50, (fixedHeight), 360);

				if (tornado_gun_timer.update())
				{
					for (auto entityIndex : tasks::get_world_entities(true, true, false))
					{
						Vector3 entityPos = ENTITY::GET_ENTITY_COORDS(entityIndex, 0);
						pos360.z = pos360.z - 1 + fixedHeight * 0.018000;
						Vector3 forceVec = pos360 - entityPos;
						if (tasks::get_control_of_entity_tick(entityIndex))
							tasks::apply_force_to_position(entityIndex, forceVec, ENTITY::GET_ENTITY_VELOCITY(entityIndex), 0.4f, 0.2);
						fixedHeight++;
					}
				}
			}

		}
	}
}
namespace insight {
	Cam weapon_teleport_gun_entity;
	void weapon::teleport_gun(toggle_int_feature* feature, bool& value, int& value2) {
		if (!value)
			return;

		if (input::get()->is_input_aim_pressed())
		{
			Vector3 laser = tasks::get_laser_ending_coordinates();
			GRAPHICS::DRAW_MARKER(0, Vector3(laser.x, laser.y, laser.z + 2), Vector3(0, 0, 0), Vector3(0, 0, 0), Vector3(1.5f, 1.5f, 2.0f), 0, 120, 200, 200, true, true, 0, false, 0, 0, 0);
			float distanceInFeet = SYSTEM::VDIST(laser, globals::h_local_ped_pos()) * 3.28084f;
			float roundedDistance = std::roundf(distanceInFeet * 100) / 100;
			std::ostringstream oss;
			oss << std::fixed << std::setprecision(2) << roundedDistance;
			std::string formattedDistance = oss.str();
			render::get()->draw_text_coordinates(std::string(formattedDistance + " ft").c_str(), laser, 0, 120, 200, 200);
			if (tasks::is_player_shooting(globals::player_id))
			{
				Entity teleporting_ent;
				if (globals::h_local_vehicle(true))
				{
					teleporting_ent = globals::h_local_vehicle();
				}
				else
				{
					teleporting_ent = globals::h_local_ped();
				}
				if (value2 == 0) {
					tasks::teleport_animation(true, true);
					ENTITY::SET_ENTITY_COORDS(teleporting_ent, laser, false, true, true, false);
					tasks::teleport_animation(false, true);
					return;
				}

				if (value2 == 1) {
					ENTITY::SET_ENTITY_COORDS(teleporting_ent, laser, false, true, true, false);
					return;
				}
			}
		}
	}
}
namespace insight {
	struct punch_data {
		timer timer;
		Vector3 force;
		Vector3 hit;
	};
	std::unordered_map<Entity, punch_data> super_punch_data;

	void v_punch_f(int i)
	{
		Vector3 force = ENTITY::GET_ENTITY_COORDS(i, 0) - vectors::get()->get_front_camera_coordinates_local(100);
		Vector3 hit = Vector3(0, 0, 0);

		if (super_punch_data.find(i) == super_punch_data.end())
			super_punch_data.emplace(i, punch_data(timer(std::chrono::microseconds(10ms)), force, hit));
		ENTITY::CLEAR_ENTITY_LAST_DAMAGE_ENTITY(i);

	}
	Entity weapon_superpunch_entity;
	Entity weapon_superpunch_entity_last;
	void weapon::superpunch(toggle_feature* feature, bool& value) {
		if (!value) {
			return;
		}
		for (auto entity : tasks::get_world_entities(true, true, false))
		{
			if (ENTITY::DOES_ENTITY_EXIST(entity))
			{
				if (PED::IS_PED_PERFORMING_MELEE_ACTION(globals::h_local_ped()) && PED::IS_PED_IN_MELEE_COMBAT(globals::h_local_ped()))
				{
					if (MISC::GET_DISTANCE_BETWEEN_COORDS(ENTITY::GET_ENTITY_COORDS(entity, 0), globals::h_local_ped_pos(), 1) < 5.0f)
					{
						if (ENTITY::HAS_ENTITY_BEEN_DAMAGED_BY_ENTITY(entity, globals::h_local_ped(), 0))
						{
							v_punch_f(entity);
						}
					}
				}
			}

			for (auto& [entity, data] : super_punch_data)
			{
				if (data.timer.update())
				{
					ENTITY::CLEAR_ENTITY_LAST_DAMAGE_ENTITY(entity);
					super_punch_data.erase(entity);
				}
				else
				{
					if (tasks::get_control_of_entity_tick(entity))
					{
						tasks::get()->apply_force_to_position(entity, data.force, ENTITY::GET_ENTITY_VELOCITY(entity), 0.2, 0.3);
						ENTITY::SET_ENTITY_NO_COLLISION_ENTITY(entity, globals::h_local_ped(), true);
					}
				}

			}

		}
	}
}
namespace insight {
	void weapon::shrink_ray(toggle_feature* feature, bool& value) {
		if (!value)
			return;
		Vector3 impact_coords;
		if (tasks::is_player_shooting(globals::player_id)) {
			Entity handle;
			ray_cast cast = tasks::create_cast(&handle);
			if (cast.m_hit) {
				PED::SET_PED_CONFIG_FLAG(handle, 223, true);
			}
		}
	}
}
namespace insight {
	timer round_force_gun_timer(std::chrono::milliseconds(200));
	int round_force_gun_dis_addr = 0;
	void roundy_force_gun() {
		Vector3 impact_coords;
		if (input::get()->is_input_aim_pressed()) {
			Vector3 round_force_gun_cam = vectors::get()->get_front_camera_coordinates_local(150);
			if (round_force_gun_timer.update()) {
				int distance = 0;
				if (round_force_gun_dis_addr >= 180) {
					round_force_gun_dis_addr = 0;
				}
				else {
					for (size_t i = 0; i < 4; i++) {
						round_force_gun_dis_addr++;
					}
				}
				for (auto entityIndex : tasks::get_world_entities(true, true, false)) {
					int pos = round_force_gun_dis_addr + distance;
					Vector3 pos360 = vectors::get()->get_360_iterator_vec_around_coord(round_force_gun_cam, 40, 25, pos, 180);
					Vector3 entityPos = ENTITY::GET_ENTITY_COORDS(entityIndex, 0);
					Vector3 forceVec = pos360 - entityPos;
					if (tasks::get_control_of_entity_tick(entityIndex)) {
						tasks::apply_force_to_position(entityIndex, forceVec, ENTITY::GET_ENTITY_VELOCITY(entityIndex), 0.8f, 0.2);
						distance++;
					}
					if (tasks::get()->is_ped_shooting(globals::h_local_ped())) {
						Vector3 rock_shhot_pos = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(entityIndex, Vector3(0, 0, -5));
						MISC::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(rock_shhot_pos,
							Vector3(rock_shhot_pos.x, rock_shhot_pos.y, rock_shhot_pos.z - 100),
							999, 0, "WEAPON_RPG"_joaat, NULL, false, false, 200);
					}
				}
			}
		}
	}
	void weapon::round_force_gun(toggle_feature* feature, bool& value) {
		if (!value)
			return;
		roundy_force_gun();
	}
}
namespace insight {
	int rop_gun_entities[2];
	int rope_gun_entity;
	void weapon::rope_gun(toggle_feature* feature, bool& value) {
		if (!value)
			return;
		if (tasks::is_ped_shooting(globals::h_local_ped())) {
			Entity handle = tasks::create_cast_entites();
			if (handle)
			{
				if (!ENTITY::DOES_ENTITY_EXIST(rop_gun_entities[0]) && !ENTITY::DOES_ENTITY_EXIST(rop_gun_entities[1])) {
					Entity aimed = handle;
					rop_gun_entities[0] = aimed;
					Vector3 entCoord = ENTITY::GET_ENTITY_COORDS(rop_gun_entities[0], 1);
					float length = SYSTEM::VDIST(globals::h_local_ped_pos(), entCoord) + 20;
					PHYSICS::ROPE_LOAD_TEXTURES();
					rope_gun_entity = PHYSICS::ADD_ROPE(globals::h_local_ped_pos(), { 0, 0, 0 }, length, 4, length, 0.5f, 0.5f, false, false, true, 1.0f, false, 0);
				}
				else if (ENTITY::DOES_ENTITY_EXIST(rop_gun_entities[0]) && !ENTITY::DOES_ENTITY_EXIST(rop_gun_entities[1])) {
					Entity aimed = handle;
					rop_gun_entities[1] = aimed;
					Vector3 entCoord0 = ENTITY::GET_ENTITY_COORDS(rop_gun_entities[0], 1);
					Vector3 aimingCoords = ENTITY::GET_ENTITY_COORDS(rop_gun_entities[1], 1);
					PHYSICS::ATTACH_ENTITIES_TO_ROPE(rope_gun_entity, rop_gun_entities[0], rop_gun_entities[1], entCoord0, aimingCoords, SYSTEM::VDIST(entCoord0, aimingCoords), 1, 1, 0, 0);
					PHYSICS::PIN_ROPE_VERTEX(rope_gun_entity, PHYSICS::GET_ROPE_VERTEX_COUNT(rope_gun_entity) - 1, aimingCoords);
					PHYSICS::ACTIVATE_PHYSICS(rope_gun_entity);
					rop_gun_entities[0] = 0;
					rop_gun_entities[1] = 0;
				}
			}
		}
		if (ENTITY::DOES_ENTITY_EXIST(rop_gun_entities[0]) && !ENTITY::DOES_ENTITY_EXIST(rop_gun_entities[1])) {
			Vector3 rHand = PED::GET_PED_BONE_COORDS(globals::h_local_ped(), 6286, { 0, 0, 0 });
			PHYSICS::PIN_ROPE_VERTEX(rope_gun_entity, 0, rHand);
			Vector3 entCoord1 = ENTITY::GET_ENTITY_COORDS(rop_gun_entities[0], 1);
			PHYSICS::PIN_ROPE_VERTEX(rope_gun_entity, PHYSICS::GET_ROPE_VERTEX_COUNT(rope_gun_entity) - 1, entCoord1);
		}
	}
}
namespace insight {
	void weapon::revive_gun(toggle_feature* feature, bool& value) {
		if (!value)
			return;
		Vector3 impact_coords;
		if (tasks::is_player_shooting(globals::player_id)) {
			Entity handle;
			ray_cast cast = tasks::create_cast(&handle);
			if (cast.m_hit) {
				tasks::request_control(handle);
				PED::RESURRECT_PED(handle);
				PED::REVIVE_INJURED_PED(handle);
				PED::SET_PED_GENERATES_DEAD_BODY_EVENTS(handle, false);
				ENTITY::SET_ENTITY_MAX_HEALTH(handle, 400);
				PED::SET_PED_CONFIG_FLAG(handle, 187, false);
				PED::SET_PED_CONFIG_FLAG(handle, 166, false);
				TASK::CLEAR_PED_TASKS_IMMEDIATELY(handle);
				TASK::TASK_WANDER_STANDARD(handle, 0.0f, 0);
			}
		}
	}
}
namespace insight {

	Hash weapon_rapidfire_blacklists = 1119849093;
	void weapon::rapidfire(toggle_feature* feature, bool& value) {
		if (!value)
			return;

		if (input::get()->is_input_aim_pressed())
		{
			if (PAD::IS_CONTROL_PRESSED(2, (int)ControllerInputs::INPUT_VEH_ATTACK) || PAD::IS_CONTROL_PRESSED(2, (int)ControllerInputs::INPUT_ATTACK))
			{
				if (WEAPON::GET_SELECTED_PED_WEAPON(globals::h_local_ped()) == weapon_rapidfire_blacklists)
				{
					if (!WEAPON::IS_PED_WEAPON_READY_TO_SHOOT(globals::h_local_ped()))
					{
						Vector3 endcord = tasks::get_laser_ending_coordinates();
						PED::SET_PED_SHOOTS_AT_COORD(globals::h_local_ped(), endcord, true);
						WEAPON::REFILL_AMMO_INSTANTLY(globals::h_local_ped());

					}

				}
				else
				{
					Vector3 endcord = tasks::get_laser_ending_coordinates();
					PED::SET_PED_SHOOTS_AT_COORD(globals::h_local_ped(), endcord, true);
					WEAPON::REFILL_AMMO_INSTANTLY(globals::h_local_ped());

				}
			}
		}
	}

	struct husk_thrower_entities_more_bombs_dat {
		timer time;
		timer time2;
	};
	std::unordered_map<Entity, timer> husk_thrower_entities_timers;
	std::unordered_map<Entity, husk_thrower_entities_more_bombs_dat> husk_thrower_entities_more_bombs;
	struct husk_thrower_entities_more_bombs_extra_dat {
		Vector3 vec;
		int intt;
	};
	std::vector<husk_thrower_entities_more_bombs_extra_dat> husk_thrower_entities_more_bombs_extra;
	void tick_husk_thrower_entities_more_bombs_extra() {
		for (int i = 0; i < husk_thrower_entities_more_bombs_extra.size(); i++)
		{
			husk_thrower_entities_more_bombs_extra_dat& d = husk_thrower_entities_more_bombs_extra[i];
			if (d.intt != 360) {
				Vector3 cordds = vectors::get()->get_custom_angle_vec_around_coord(d.vec, 10.f, 0, 360, d.intt);
				FIRE::ADD_OWNED_EXPLOSION(globals::h_local_ped(), cordds, 3, 99, 1, 0, 0.1f);
				d.intt++;
			}
			else {
				husk_thrower_entities_more_bombs_extra.erase(husk_thrower_entities_more_bombs_extra.begin() + i);
			}
		}
	}
	void tick_husk_thrower_entities_more_bombs() {
		for (auto& [entity, dat] : husk_thrower_entities_more_bombs)
		{
			if (dat.time.update()) {
				tasks::play_ptfx_bone_tick(entity, 0, (char*)"scr_agencyheist", (char*)"scr_agencyheist", (char*)"scr_fbi_dd_breach_smoke", 0.1, 0, 0, 0, 0);
				AUDIO::PLAY_SOUND_FROM_ENTITY(0, "Air_Defences_Activated", entity, "DLC_sum20_Business_Battle_AC_Sounds", globals::in_multiplayer(), 999999);
			}
			if (ENTITY::HAS_ENTITY_COLLIDED_WITH_ANYTHING(entity)) {
				Vector3 cordds = ENTITY::GET_ENTITY_COORDS(entity, 0);
				FIRE::ADD_OWNED_EXPLOSION(globals::h_local_ped(), cordds, 49, 99, 1, 0, 0.1f);
				husk_thrower_entities_more_bombs_extra.push_back({ cordds ,0 });
				tasks::delete_entity(entity);
				husk_thrower_entities_more_bombs.erase(entity);
			}

		}
	}
	Object attached_pmpkin;
	void weapon::halloween_special_ball(toggle_feature* feature, bool& value)
	{
		if (!value)
			return;
		if (globals::c_local_weapon()->m_selected_weapon_hash == -1813897027) {
			Hash pmpkin = rage::joaat("prop_veg_crop_03_pump");
			Object obj = OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(globals::h_local_ped_pos(), 2, 290600267, 0, 0, 1);
			if (ENTITY::GET_ENTITY_ATTACHED_TO(obj) != globals::h_local_ped())
			{
				Entity new_entity = obj;
				if (husk_thrower_entities_timers.find(new_entity) == husk_thrower_entities_timers.end())
				{
					husk_thrower_entities_timers.emplace(new_entity, timer(std::chrono::milliseconds(100)));
				}
			}
		}

		for (auto& [entity, timer_] : husk_thrower_entities_timers)
		{
			if (ENTITY::DOES_ENTITY_EXIST(entity))
			{

				if (timer_.update())
				{
					tasks::play_ptfx_bone_tick(entity, 0, (char*)"scr_agencyheist", (char*)"scr_agencyheist", (char*)"scr_fbi_dd_breach_smoke", 0.1, 0, 0, 0, 0);
				}
				if (ENTITY::HAS_ENTITY_COLLIDED_WITH_ANYTHING(entity))
				{
					FIRE::ADD_OWNED_EXPLOSION(globals::h_local_ped(), ENTITY::GET_ENTITY_COORDS(entity, 0), 49, 99, 1, 0, 0.1f);

					Vector3 cor = ENTITY::GET_ENTITY_COORDS(entity, 1);
					tasks::play_ptfx_bone_tick(entity, 0, (char*)"scr_agencyheist", (char*)"scr_agencyheist", (char*)"scr_fbi_dd_breach_smoke", 0.1, 0, 0, 0, 0);
					for (int i = 0; i < 4; i++)
					{
						Vector3 shoot_at = vectors::get()->get_custom_angle_vec_around_coord(cor, 20, 20, 360, i * 90);
						MISC::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(cor, shoot_at, 99, 0, -1813897027, globals::h_local_ped(), 1, 0, 999);
					}

					std::vector<Entity> nearbyEntities = tasks::get_world_entities(0, 0, TRUE);
					for (const auto& entity : nearbyEntities) {
						if (ENTITY::GET_ENTITY_MODEL(entity) == 290600267 && tasks::get()->get_distance_between(entity, cor) < 20.f && !ENTITY::IS_ENTITY_ATTACHED_TO_ANY_PED(entity)) {
							if (husk_thrower_entities_more_bombs.find(entity) == husk_thrower_entities_more_bombs.end())
							{
								husk_thrower_entities_more_bombs.emplace(entity, husk_thrower_entities_more_bombs_dat(timer(std::chrono::milliseconds(100)), timer(std::chrono::milliseconds(4000))));
							}
						}
					}
				}
			}
			else
			{
				husk_thrower_entities_timers.erase(entity);
			}

		}
		tick_husk_thrower_entities_more_bombs();
		tick_husk_thrower_entities_more_bombs_extra();
	}
}
namespace insight {

	void weapon::projectile_gun(toggle_int_feature* feature, bool& value, int& value2) {
		if (!value)
			return;
		Vector3 impact_coords;
		if (tasks::is_player_shooting(globals::player_id)) {
			Vector3 cam = CAM::GET_GAMEPLAY_CAM_COORD();
			Vector3 cam_direction = vectors::get()->get_direction();
			Vector3 start_coords = cam + cam_direction * 5.f;
			Vector3 start_coords_of_projectile = tasks::get()->get_weapon_bone_coords(xorstr_("gun_muzzle"));
			Vector3 end_coords = start_coords + cam_direction * 1000.f;
			Hash weapon_hash = rage::joaat(eVehicleWeapons[value2].first);
			if (tasks::is_player_shooting(globals::player_id))
			{
				WEAPON::REQUEST_WEAPON_ASSET(weapon_hash, 31, 0);
				while (!WEAPON::HAS_WEAPON_ASSET_LOADED(weapon_hash)) {
					WEAPON::REQUEST_WEAPON_ASSET(weapon_hash, 31, 0);
					script::get_current()->yield(10ms);
				}
				MISC::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(start_coords_of_projectile, end_coords, 250, 1, weapon_hash, globals::h_local_ped(), 1, 0, 12500);
			}
		}
	}
}
namespace insight {
	void weapon::particle_impact(toggle_int_feature* feature, bool& value, int& value2) {
		if (!value)
			return;
		if (tasks::is_player_shooting(globals::player_id)) {
			if ("weapon_impact_particle_muzzle"_tf->m_value.toggle) {
				Object weapon = WEAPON::GET_CURRENT_PED_WEAPON_ENTITY_INDEX(globals::h_local_ped(), 0);
				tasks::play_ptfx_bone_woffsets_tick(weapon, ENTITY::GET_ENTITY_BONE_INDEX_BY_NAME(weapon, "gun_muzzle"), particles[value2].dict, particles[value2].dict,
					particles[value2].texture, "weapon_impact_particle_size"_FF->m_value.floating_point,
					Vector3(0, 0, 0), Vector3(0, 180, 0));

			}
			else {
				tasks::get()->play_ptfx_on_coordinates(particles[value2].dict, particles[value2].texture,
					tasks::get()->get_laser_ending_coordinates(), "weapon_impact_particle_size"_FF->m_value.floating_point, Vector3(0, 180, 0));
			}
		}
	}
	void set_height(float val) {
		if (auto ped_factory = *reinterpret_cast<std::add_pointer_t<std::uint64_t>>(insight::pointers::get()->g_ped_factory)) {
			if (auto player_ped = *reinterpret_cast<std::add_pointer_t<std::uint64_t>>(ped_factory + 0x8)) {
				if (auto player_wep = *reinterpret_cast<std::add_pointer_t<std::uint64_t>>(player_ped + 0x10B8)) {
					if (auto player_wep_obj = *reinterpret_cast<std::add_pointer_t<std::uint64_t>>(player_wep + 0x78)) {
						*reinterpret_cast<std::add_pointer_t<std::float_t>>(player_wep_obj + 0x8C) = val;
					}
				}
			}
		}
	}
	bool was_weapon_height_on = false;
	void weapon::weapon_height(toggle_float_feature* feature, bool& value, float& value2) {
		if (!value) {
			if (was_weapon_height_on) {
				set_height(1.f);
				was_weapon_height_on = false;
			}
			return;
		}
		set_height(value2);
		was_weapon_height_on = true;
	}
	void set_width(float val) {
		if (auto ped_factory = *reinterpret_cast<std::add_pointer_t<std::uint64_t>>(insight::pointers::get()->g_ped_factory)) {
			if (auto player_ped = *reinterpret_cast<std::add_pointer_t<std::uint64_t>>(ped_factory + 0x8)) {
				if (auto player_wep = *reinterpret_cast<std::add_pointer_t<std::uint64_t>>(player_ped + 0x10B8)) {
					if (auto player_wep_obj = *reinterpret_cast<std::add_pointer_t<std::uint64_t>>(player_wep + 0x78)) {
						*reinterpret_cast<std::add_pointer_t<std::float_t>>(player_wep_obj + 0x7C) = val;
					}
				}
			}
		}
	}
	bool was_weapon_width_on = false;
	void weapon::weapon_width(toggle_float_feature* feature, bool& value, float& value2) {
		if (!value) {
			if (was_weapon_width_on) {
				set_width(1.f);
				was_weapon_width_on = false;
			}
			return;
		}
		set_width(value2);
		was_weapon_width_on = true;
	}
	bool was_weapon_height_width_on = false;
	void weapon::weapon_height_width(toggle_float_feature* feature, bool& value, float& value2) {
		if (!value) {
			if (was_weapon_height_width_on) {
				"weapon_width"_tff->m_number_value.floating_point = 1.f;
				"weapon_height"_tff->m_number_value.floating_point = 1.f;
				"weapon_width"_tff->m_toggle_value.toggle = value;
				"weapon_height"_tff->m_toggle_value.toggle = value;
				was_weapon_height_width_on = false;
			}
			return;
		}
		"weapon_width"_tff->m_number_value.floating_point = value2;
		"weapon_height"_tff->m_number_value.floating_point = value2;
		"weapon_width"_tff->m_toggle_value.toggle = value;
		"weapon_height"_tff->m_toggle_value.toggle = value;
		was_weapon_height_width_on = true;
	}

	void weapon::upgrade_weapons_on_session_join(toggle_feature* feature, bool& value) {
		if (STREAMING::IS_PLAYER_SWITCH_IN_PROGRESS() && STREAMING::GET_PLAYER_SWITCH_STATE() == 8) {
			tasks::give_weapons_to_player(PLAYER::PLAYER_ID());
			tasks::upgrade_player_weapons(PLAYER::PLAYER_ID());
		}
	}

	void weapon::give_weapons_on_session_join(toggle_feature* feature, bool& value) {
		if (STREAMING::IS_PLAYER_SWITCH_IN_PROGRESS() && STREAMING::GET_PLAYER_SWITCH_STATE() == 8) {
			tasks::give_weapons_to_player(PLAYER::PLAYER_ID());
		}
	}
}
namespace insight {
	void weapon::paint_gun(toggle_float_feature* feature, bool& value, float& value2) {
		if (!value)
			return;
		Vector3 impact_coords;
		if (tasks::is_player_shooting(globals::player_id)) {
			Entity handle;
			ray_cast cast = tasks::create_cast(&handle);
			if (cast.m_hit) {
				if (ENTITY::IS_ENTITY_A_VEHICLE(handle)) {
					float ranodm = MISC::GET_RANDOM_FLOAT_IN_RANGE(0, 255);
					VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(handle, ranodm, ranodm, ranodm);
					VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(handle, ranodm, ranodm, ranodm);
					return;
				}
				else if (ENTITY::IS_ENTITY_A_PED(handle))
				{
					if (!PED::IS_PED_A_PLAYER(handle))
						PED::SET_PED_RANDOM_COMPONENT_VARIATION(handle, globals::get()->in_multiplayer()); return;
				}


				Vector3 c = tasks::get_laser_ending_coordinates();
				if ("weapon_impact_paint_rainbow"_tf->m_value.toggle)
				{
					features_utility::get()->Paint_Gun_Colors.x = vectors::get()->get_rainbow_fade_colors()[0];
					features_utility::get()->Paint_Gun_Colors.y = vectors::get()->get_rainbow_fade_colors()[1];
					features_utility::get()->Paint_Gun_Colors.z = vectors::get()->get_rainbow_fade_colors()[2];
				}
				GRAPHICS::ADD_DECAL(features_utility::get()->decal_paintgun /*splatters_blood2 */, c, 0 /*dirX*/, 0 /*dirY*/, -1 /*dirZ*/, 0, 1, 0,
					value2 /*width*/, value2 /*height*/, features_utility::get()->Paint_Gun_Colors.x / 255,
					features_utility::get()->Paint_Gun_Colors.y / 255, features_utility::get()->Paint_Gun_Colors.z / 255,
					1.0, 150.0, 0, 0, 0);

				return;
			}


		}
	}
}
namespace insight {
	struct nuke_gun_data {
		timer timer;
		Vector3 vec;
	};
	std::unordered_map<int, nuke_gun_data> nuke_gun_n_timer;

	void weapon::nuke_gun(toggle_int_feature* feature, bool& value, int& value2) {
		if (!value)
			return;
		Vector3 impact_coords;
		if (tasks::is_player_shooting(globals::player_id)) {
			if (value2 == 0)
			{
				tasks::nuke_real(tasks::get()->get_laser_ending_coordinates(), true);
			}
			else if (value2 == 1)
			{
				tasks::nuke_normal(tasks::get()->get_laser_ending_coordinates());
			}
			else if (value2 == 2)
			{
				tasks::nuke_x(tasks::get()->get_laser_ending_coordinates());
			}

		}
	}
}
namespace insight {
	timer weapon_noreload_tick(std::chrono::milliseconds(500));

	void weapon::noreload(toggle_int_feature* feature, bool& value, int& value2) {
		if (!value)
			return;
		if (value2 == 0) {
			if (weapon_noreload_tick.update())
			{
				if (!WEAPON::IS_PED_WEAPON_READY_TO_SHOOT(globals::h_local_ped()))
				{
					WEAPON::REFILL_AMMO_INSTANTLY(globals::h_local_ped());
				}
				if (PED::IS_PED_RELOADING(globals::h_local_ped()))
				{
					WEAPON::REFILL_AMMO_INSTANTLY(globals::h_local_ped());
				}
			}
		}
		if (value2 == 1) {
			if (PED::IS_PED_RELOADING(globals::h_local_ped()))
			{
				PED::FORCE_PED_AI_AND_ANIMATION_UPDATE(globals::h_local_ped(), 1, 0);
			}
		}

	}
}
namespace insight {
	void weapon::money_gun(toggle_int_feature* feature, bool& value, int& value2) {
		if (!value)
			return;
		if (tasks::is_player_shooting(globals::player_id)) {
			{
				tasks::spawn_money(value2, tasks::get_laser_ending_coordinates());
			}
		}
	}
}
namespace insight {
	Hash rockets_hash[] = {
		"xm_prop_x17_silo_rocket_01"_joaat,
		"w_lr_rpg_rocket"_joaat,
		"w_lr_homing_rocket"_joaat,
		"w_lr_firework_rocket"_joaat
	};
	Cam remote_control_rocket_cam = 0;
	float rocket_pos_angle = 0;
	bool get_player_last_pos = false;
	Vector3 last_ped_pos = { 0,0,0 };
	Vector3 rocket_pos = { 0,0,0 };
	Entity Rocket_Entity = 0;
	Entity Rocket_ball = 0;
	Vector3 rocket_rot = { 0,0,0 };
	void rocket_cam_tick() {
		if (!CAM::DOES_CAM_EXIST(remote_control_rocket_cam)) {
			remote_control_rocket_cam = CAM::CREATE_CAM("DEFAULT_SCRIPTED_CAMERA", 1);
			rocket_pos = ENTITY::GET_ENTITY_COORDS(Rocket_Entity, 0);
			Vector3 pos = vectors::get()->get_custom_angle_vec_around_coord(rocket_pos, 50, CAM::GET_GAMEPLAY_CAM_ROT(0).y, 360, rocket_pos_angle);
			CAM::SET_CAM_COORD(remote_control_rocket_cam, pos);
			CAM::SET_CAM_FOV(remote_control_rocket_cam, 60);
			CAM::RENDER_SCRIPT_CAMS(true, true, 700, 1, 1, 0);
			CAM::SET_CAM_ACTIVE(remote_control_rocket_cam, true);
			rocket_rot = { 0,0,0 };
		}
		else
		{
			rocket_pos = ENTITY::GET_ENTITY_COORDS(Rocket_Entity, 0);
			Vector3 pos = vectors::get()->get_custom_angle_vec_around_coord(rocket_pos, ENTITY::GET_ENTITY_MODEL(Rocket_Entity) == "xm_prop_x17_silo_rocket_01"_joaat ? 50 : 15, CAM::GET_GAMEPLAY_CAM_ROT(0).x, 360, rocket_pos_angle);
			CAM::SET_CAM_COORD(remote_control_rocket_cam, pos);
		}
	}
	void reset_rocket() {
		if (Rocket_Entity || Rocket_ball) {
			ENTITY::DELETE_ENTITY(&Rocket_Entity);
			ENTITY::DELETE_ENTITY(&Rocket_ball);
			Rocket_ball = 0;
			Rocket_Entity = 0;
			ENTITY::SET_ENTITY_VISIBLE(globals::h_local_ped(), 1, 0);
		}
		if (remote_control_rocket_cam) {
			Vector3 camCoords = CAM::GET_CAM_COORD(remote_control_rocket_cam);
			CAM::RENDER_SCRIPT_CAMS(false, true, 700, 1, 1, 1);
			CAM::SET_CAM_ACTIVE(remote_control_rocket_cam, false);
			CAM::DESTROY_CAM(remote_control_rocket_cam, true);
			remote_control_rocket_cam = 0;
		}
		if (get_player_last_pos) {
			ENTITY::SET_ENTITY_COORDS_NO_OFFSET(globals::h_local_ped(), last_ped_pos, 0, 0, 0);
			get_player_last_pos = false;
		}
	}
	bool was_missle_launcher_on = false;
	int timer_sound = 0;
	timer Sound_N_PTFX(std::chrono::milliseconds(100));
	timer PTFX(std::chrono::milliseconds(100));
	void weapon::missle_launcher(toggle_feature* feature, bool& value) {
		if (!value) {
			if (was_missle_launcher_on) {
				reset_rocket();
				was_missle_launcher_on = false;
				get_player_last_pos = false;
			}
			return;
		}
		if (!was_missle_launcher_on) {
			notify::send("Rocket Missle",
				globals::is_using_controller() ?
				"Usage : Left Stick For Left,Right And Boost. L1 And R1 For Up Down Rotation."
				:
				"Usage : W Boost, A For Left Rotation, D For Right Rotation.Q And E For Up Down Rotation.");
			was_missle_launcher_on = true;

		}
		if (!ENTITY::DOES_ENTITY_EXIST(Rocket_Entity) || !ENTITY::DOES_ENTITY_EXIST(Rocket_ball)) {
			Hash rocket_ = rockets_hash["weapon_missle_launcher_type"_if->m_value.integer];
			while (!STREAMING::HAS_MODEL_LOADED(rocket_)) {
				STREAMING::REQUEST_MODEL(rocket_);
				script::get_current()->yield();
			}
			rocket_pos = vectors::get()->get_front_camera_coordinates_local(5);
			rocket_pos.z += 100.f;
			if (!Rocket_Entity)
				Rocket_Entity = OBJECT::CREATE_OBJECT(rocket_, rocket_pos, globals::in_multiplayer(), 0, 1);
			Hash ball = rage::joaat("prop_paper_ball");
			while (!STREAMING::HAS_MODEL_LOADED(ball))
			{
				STREAMING::REQUEST_MODEL(ball);
				script::get_current()->yield();
			}
			if (!Rocket_ball)
				Rocket_ball = OBJECT::CREATE_OBJECT(ball, rocket_pos, globals::in_multiplayer(), 0, 1);
			ENTITY::ATTACH_ENTITY_TO_ENTITY(Rocket_Entity, Rocket_ball, 0, Vector3(0, 0, 0), Vector3(0, 0, 0), false, false, false, false, 0, true, 0);
		}
		else {
			rocket_cam_tick();
			if ("weapon_missle_launcher_esp"_tf->m_value.toggle) {
				for (int i = 0; i < 32; i++)
				{
					if (i != globals::player_id) {
						if (NETWORK::NETWORK_IS_PLAYER_CONNECTED(i)) {
							Ped ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i);
							float distance = tasks::get_distance_between(ped, ENTITY::GET_ENTITY_COORDS(Rocket_Entity, 0));
							if (distance < 1000) {
								Vector3 coords = ENTITY::GET_ENTITY_COORDS(ped, 0);
								std::string text = std::string(PLAYER::GET_PLAYER_NAME(i)) + xorstr_(" | ") + std::to_string((int)distance);
								render::get()->draw_text_coordinates(text.c_str(), coords, 255, 150, 150, 255);
								GRAPHICS::DRAW_LINE(ENTITY::GET_ENTITY_COORDS(Rocket_Entity, 0), coords, 255, 150, 150, 255);
							}
						}
					}
				}
			}
			PLAYER::DISABLE_PLAYER_FIRING(globals::player_id, TRUE);
			PAD::DISABLE_CONTROL_ACTION(0, (int)ControllerInputs::INPUT_RADIO_WHEEL_LR, true);
			PAD::DISABLE_CONTROL_ACTION(0, (int)ControllerInputs::INPUT_RADIO_WHEEL_UD, true);
			auto coords = ENTITY::GET_ENTITY_COORDS(Rocket_Entity, 0);
			coords.z += -5;
			coords.x += -5;
			coords.y += -5;
			if (!get_player_last_pos) {
				last_ped_pos = globals::h_local_ped_pos();
				get_player_last_pos = true;
			}
			ENTITY::SET_ENTITY_COORDS(globals::h_local_ped(), coords, 1, 1, 0, 0);
			ENTITY::SET_ENTITY_VISIBLE(globals::h_local_ped(), 0, 0);
			rocket_pos_angle = CAM::GET_GAMEPLAY_CAM_ROT(0).z;
			CAM::POINT_CAM_AT_ENTITY(remote_control_rocket_cam, Rocket_Entity, 0, 0, 0, 0);
			rocket_pos = ENTITY::GET_ENTITY_COORDS(Rocket_Entity, 0);
			float rocket_speed = ENTITY::GET_ENTITY_SPEED(Rocket_ball);
			Hash ent_hash = ENTITY::GET_ENTITY_MODEL(Rocket_Entity);
			if (PAD::IS_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_MOVE_UP_ONLY)) {
				if (tasks::get_control_of_entity_tick(Rocket_ball))
					ENTITY::APPLY_FORCE_TO_ENTITY(Rocket_ball, 1, Vector3(0, 0, 10 * "weapon_missle_launcher_speed"_FF->m_value.floating_point), Vector3(0.0f, 0.0f, 0.0f), 0, 1, 1, 1, 0, 1);
			}
			else {
				if (tasks::get_control_of_entity_tick(Rocket_ball))
					ENTITY::APPLY_FORCE_TO_ENTITY(Rocket_ball, 1, Vector3(0, 0, 1.1f * "weapon_missle_launcher_speed"_FF->m_value.floating_point), Vector3(0.0f, 0.0f, 0.0f), 0, 1, 1, 1, 0, 1);
			}
			if (PAD::IS_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_COVER)) {
				rocket_rot.y += 1.0f;
			}
			if (PAD::IS_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_PICKUP)) {
				rocket_rot.y -= 1.0f;
			}
			if (PAD::IS_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_MOVE_LEFT_ONLY)) {
				rocket_rot.z += 1.0f;
			}
			if (PAD::IS_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_MOVE_RIGHT_ONLY)) {
				rocket_rot.z -= 1.0f;
			}
			if (tasks::get_control_of_entity_tick(Rocket_ball))
				ENTITY::SET_ENTITY_MAX_SPEED(Rocket_ball, 999999999.f);
			if (ent_hash == "xm_prop_x17_silo_rocket_01"_joaat) {
				PTFX.setdelay(100ms);
			}
			else {
				PTFX.setdelay(500ms);
			}
			if ("weapon_missle_launcher_ptfx"_tif->m_toggle_value.toggle) {
				if (PTFX.update()) {
					float speed_ptfx = 0.1f + (rocket_speed / 300);
					if (ent_hash == "xm_prop_x17_silo_rocket_01"_joaat) {
						tasks::get()->play_ptfx_bone_woffsets_tick(Rocket_Entity, 0, "scr_exile1", "scr_exile1", "scr_ex1_cargo_engine_burst",
							speed_ptfx * "weapon_missle_launcher_ptfx"_tif->m_number_value.floating_point, Vector3(0, 1.2f, -26), Vector3(0, 180, 0));
						tasks::get()->play_ptfx_bone_woffsets_tick(Rocket_Entity, 0, "scr_exile1", "scr_exile1", "scr_ex1_cargo_engine_burst",
							speed_ptfx * "weapon_missle_launcher_ptfx"_tif->m_number_value.floating_point, Vector3(0, -0.8f, -26), Vector3(0, 180, 0));
					}
					else {
						tasks::get()->play_ptfx_bone_woffsets_tick(Rocket_Entity, 0, "scr_exile1", "scr_exile1", "scr_ex1_cargo_engine_burst",
							0.01f * "weapon_missle_launcher_ptfx"_tif->m_number_value.floating_point, Vector3(0, 0, -vectors::get()->getModelLength(Rocket_Entity)), Vector3(0, 180, 0));
					}
				}
			}
			if (rocket_speed >= 0) {
				timer_sound = ent_hash == "xm_prop_x17_silo_rocket_01"_joaat ? 300 - rocket_speed : 1000;
			}
			Sound_N_PTFX.setdelay(std::chrono::milliseconds(timer_sound));
			if (Sound_N_PTFX.update()) {
				if (ent_hash == "xm_prop_x17_silo_rocket_01"_joaat) {
					FIRE::ADD_EXPLOSION(ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(Rocket_Entity, Vector3(0, 0, -23.5)), 25, 999.F, "weapon_missle_launcher_audio"_tf->m_value.toggle, TRUE,
						"weapon_missle_launcher_shake"_tif->m_toggle_value.toggle ? "weapon_missle_launcher_shake"_tif->m_number_value.floating_point : 0, 0);
				}
				else {
					FIRE::ADD_EXPLOSION(ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(Rocket_Entity, Vector3(0, 0, -vectors::get()->getModelLength(Rocket_Entity))), 25, 999.F, "weapon_missle_launcher_audio"_tf->m_value.toggle, TRUE,
						"weapon_missle_launcher_shake"_tif->m_toggle_value.toggle ? "weapon_missle_launcher_shake"_tif->m_number_value.floating_point : 0, 0);
				}
			}
			ENTITY::SET_ENTITY_ROTATION(Rocket_ball, rocket_rot.x, rocket_rot.y, rocket_rot.z, 0, 0);
			if (ENTITY::HAS_ENTITY_COLLIDED_WITH_ANYTHING(Rocket_ball)) {
				"weapon_missle_launcher"_tf->m_value.toggle = false;
				tasks::nuke_real(ENTITY::GET_ENTITY_COORDS(Rocket_Entity, 0), 1);
				reset_rocket();
			}
		}

	}
}
namespace insight {
	void weapon::laser_sight(toggle_feature* feature, bool& value) {
		if (!value)
			return;
		if (input::get()->is_input_aim_pressed()) {
			auto weaponEntity = WEAPON::GET_CURRENT_PED_WEAPON_ENTITY_INDEX(globals::h_local_ped(), 0);
			Vector3 Coords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(weaponEntity, Vector3(0, 0, -0.01));
			GRAPHICS::DRAW_SPOT_LIGHT(tasks::get_laser_ending_coordinates(-3), vectors::get()->get_direction()
				, features_utility::get()->n_laser_sight_color.r, features_utility::get()->n_laser_sight_color.g,
				features_utility::get()->n_laser_sight_color.b, "weapon_laser_sight_fx_distance"_FF->m_value.floating_point
				, "weapon_laser_sight_fx_Brightness"_FF->m_value.floating_point, "weapon_laser_sight_fx_Hardness"_FF->m_value.floating_point, "weapon_laser_sight_fx_Radius"_FF->m_value.floating_point, "weapon_laser_sight_fx_Fall_Off"_FF->m_value.floating_point);
			GRAPHICS::DRAW_LINE(Coords, tasks::get_laser_ending_coordinates(), features_utility::get()->n_laser_sight_color.r,
				features_utility::get()->n_laser_sight_color.g,
				features_utility::get()->n_laser_sight_color.b, 255);
		}
	}
	struct WeaponInfoBackup {
		float explosion_shake_amplitude;
		float recoil_shake_amplitude;
		float recoil_accuracy_max;
		float recoil_error_time;
	};
	std::unordered_map<Hash, WeaponInfoBackup> weaponrecoil_bak;
	Hash last_weapon_recoil;
	void set_no_recoil(float shake1, float shake2, float accuracy, float errortime) {
		globals::c_local_weapon()->m_weapon_info->m_explosion_shake_amplitude = shake1;
		globals::c_local_weapon()->m_weapon_info->m_recoil_shake_amplitude = shake2;
		globals::c_local_weapon()->m_weapon_info->m_recoil_accuracy_max = accuracy;
		globals::c_local_weapon()->m_weapon_info->m_recoil_error_time = errortime;
	}
	void weapon::no_recoil(toggle_feature* feature, bool& value) {
		if (!value) {
			last_weapon_recoil = 0;
			for (auto& [hash, info] : weaponrecoil_bak) {
				if (hash == globals::c_local_weapon()->m_selected_weapon_hash) {
					set_no_recoil(info.explosion_shake_amplitude, info.recoil_shake_amplitude,
						info.recoil_accuracy_max, info.recoil_error_time);

					weaponrecoil_bak.erase(hash);
				}
			}
			return;
		}
		if (last_weapon_recoil != globals::c_local_weapon()->m_selected_weapon_hash) {

			if (weaponrecoil_bak.find(globals::c_local_weapon()->m_selected_weapon_hash) == weaponrecoil_bak.end())
				weaponrecoil_bak.emplace(globals::c_local_weapon()->m_selected_weapon_hash,
					WeaponInfoBackup(globals::c_local_weapon()->m_weapon_info->m_explosion_shake_amplitude,
						globals::c_local_weapon()->m_weapon_info->m_recoil_shake_amplitude,
						globals::c_local_weapon()->m_weapon_info->m_recoil_accuracy_max,
						globals::c_local_weapon()->m_weapon_info->m_recoil_error_time));

			last_weapon_recoil = globals::c_local_weapon()->m_selected_weapon_hash;
		}
		set_no_recoil(0, 0, 0, 0);
	}
	struct WeaponNo_Range_Backup {
		float range;
		float lock_range;
		float damage_fall_off_range_max;
		float damage_fall_off_range_min;
		float m_force_falloff_range_start;
		float m_force_falloff_range_end;
		float m_force_falloff_range_min;
	};
	std::unordered_map<Hash, WeaponNo_Range_Backup> weapon_range_bak;
	void set_range(float range, float lock_range, float damage_fall_off_range_max,
		float damage_fall_off_range_min, float m_force_falloff_range_start, float m_force_falloff_range_end, float m_force_falloff_range_min) {
		globals::c_local_weapon()->m_weapon_info->m_weapon_range = range;
		globals::c_local_weapon()->m_weapon_info->m_lock_on_range = lock_range;
		globals::c_local_weapon()->m_weapon_info->m_damage_fall_off_range_max = damage_fall_off_range_max;
		globals::c_local_weapon()->m_weapon_info->m_damage_fall_off_range_min = damage_fall_off_range_min;
		globals::c_local_weapon()->m_weapon_info->m_force_falloff_range_start = m_force_falloff_range_start;
		globals::c_local_weapon()->m_weapon_info->m_force_falloff_range_end = m_force_falloff_range_end;
		globals::c_local_weapon()->m_weapon_info->m_force_falloff_range_min = m_force_falloff_range_min;
	}
	Hash last_weapon_inf_range = 0;
	void weapon::inf_range(toggle_feature* feature, bool& value) {
		if (!value) {
			last_weapon_inf_range = 0;
			for (auto& [hash, info] : weapon_range_bak) {
				if (hash == globals::c_local_weapon()->m_selected_weapon_hash) {
					set_range(info.range, info.lock_range, info.damage_fall_off_range_max, info.damage_fall_off_range_min,
						info.m_force_falloff_range_start, info.m_force_falloff_range_end, info.m_force_falloff_range_min);
					weapon_range_bak.erase(hash);
				}
			}
			return;
		}
		if (last_weapon_inf_range != globals::c_local_weapon()->m_selected_weapon_hash) {

			if (weapon_range_bak.find(globals::c_local_weapon()->m_selected_weapon_hash) == weapon_range_bak.end())
				weapon_range_bak.emplace(globals::c_local_weapon()->m_selected_weapon_hash,
					WeaponNo_Range_Backup(globals::c_local_weapon()->m_weapon_info->m_weapon_range,
						globals::c_local_weapon()->m_weapon_info->m_lock_on_range,
						globals::c_local_weapon()->m_weapon_info->m_damage_fall_off_range_max,
						globals::c_local_weapon()->m_weapon_info->m_damage_fall_off_range_min,
						globals::c_local_weapon()->m_weapon_info->m_force_falloff_range_start,
						globals::c_local_weapon()->m_weapon_info->m_force_falloff_range_end,
						globals::c_local_weapon()->m_weapon_info->m_force_falloff_range_min));

			last_weapon_inf_range = globals::c_local_weapon()->m_selected_weapon_hash;
		}
		set_range(9999, 9999, 9999, 9999, 9999, 9999, 9999);
	}
	// cursed asf real. 
	struct wep_damage_info {
		Hash weapon;
		float damage;
		float damage2;
		float damage3;
	};
	std::unordered_map<Hash, wep_damage_info> weapondmg_bak;
	Hash weapon_dmg_last_weapon;
	void set_wep_damage(float dmg, float damg2, float dam3) {
		globals::c_local_weapon()->m_weapon_info->m_damage = dmg;
		globals::c_local_weapon()->m_weapon_info->m_network_ped_damage_modifier = damg2;
		globals::c_local_weapon()->m_weapon_info->m_network_player_damage_modifier = dam3;
	}
	void weapon::wep_damage(toggle_float_feature* feature, bool& value, float& value2) {
		if (!value) {
			weapon_dmg_last_weapon = 0;
			for (auto& [hash, info] : weapondmg_bak) {
				if (hash == globals::c_local_weapon()->m_selected_weapon_hash) {
					set_wep_damage(info.damage, info.damage2, info.damage3);
					weapondmg_bak.erase(hash);
				}
			}
			return;
		}
		if (weapon_dmg_last_weapon != globals::c_local_weapon()->m_selected_weapon_hash) {

			if (weaponrecoil_bak.find(globals::c_local_weapon()->m_selected_weapon_hash) == weaponrecoil_bak.end())
				weaponrecoil_bak.emplace(globals::c_local_weapon()->m_selected_weapon_hash,
					WeaponInfoBackup(globals::c_local_weapon()->m_weapon_info->m_explosion_shake_amplitude,
						globals::c_local_weapon()->m_weapon_info->m_damage,
						globals::c_local_weapon()->m_weapon_info->m_network_ped_damage_modifier,
						globals::c_local_weapon()->m_weapon_info->m_network_player_damage_modifier));

			weapon_dmg_last_weapon = globals::c_local_weapon()->m_selected_weapon_hash;
		}
		set_wep_damage(value2, value2, value2);
	}
	bool was_explosive_fist_on = false;
	void weapon::explosive_fist(toggle_feature* feature, bool& value) {
		if (!value) {
			if (was_explosive_fist_on) {
				globals::c_local_ped()->m_player_info->m_frame_flags = 0;
				was_explosive_fist_on = false;
			}
			return;
		}
		was_explosive_fist_on = true;
		globals::c_local_ped()->m_player_info->m_frame_flags |= eFrameFlagExplosiveMelee;
	}
	bool was_explosive_ammo_on = false;
	void weapon::explosive_ammo(toggle_feature* feature, bool& value) {
		if (!value) {
			if (was_explosive_ammo_on) {
				globals::c_local_ped()->m_player_info->m_frame_flags = 0;
				was_explosive_ammo_on = false;
			}
			return;
		}
		was_explosive_ammo_on = true;
		globals::c_local_ped()->m_player_info->m_frame_flags |= eFrameFlagExplosiveAmmo;
	}
	bool was_fire_ammo_on = false;
	void weapon::fire_ammo(toggle_feature* feature, bool& value) {
		if (!value) {
			if (was_fire_ammo_on) {
				globals::c_local_ped()->m_player_info->m_frame_flags = 0;
				was_fire_ammo_on = false;
			}
			return;
		}
		was_fire_ammo_on = true;
		globals::c_local_ped()->m_player_info->m_frame_flags |= eFrameFlagFireAmmo;
	}
}
namespace insight {
	std::vector<Entity> ins_gun_bullet_vec;
	bool was_instrumentofdeath_on = false;
	void weapon::instrumentofdeath(toggle_int_feature* feature, bool& value, int& value2) {
		if (!value)
		{
			if (was_instrumentofdeath_on)
			{
				for (const auto& entity : ins_gun_bullet_vec) {
					if (ENTITY::DOES_ENTITY_EXIST(entity))
					{
						tasks::delete_entity(entity);
					}
				}
				ins_gun_bullet_vec.clear();
				was_instrumentofdeath_on = false;
			}
			return;
		}
		was_instrumentofdeath_on = true;
		Vector3 spawn = vectors::get()->get_front_camera_coordinates_local(10);
		Vector3 pos = vectors::get()->get_front_camera_coordinates_local(50);

		if (input::get()->is_input_aim_pressed())
		{
			Hash hash = MISC::GET_HASH_KEY("w_lr_homing_rocket");
			if (tasks::is_player_shooting(globals::player_id))
			{
				while (!STREAMING::HAS_MODEL_LOADED(hash))
				{
					STREAMING::REQUEST_MODEL(hash);
					script::get_current()->yield();
				}
				Entity new_ent = OBJECT::CREATE_OBJECT(hash, spawn, 1, 0, 0);
				if (value2 == 1) {
					Vector3 bulletpos = ENTITY::GET_ENTITY_COORDS(new_ent, 0);
					Vector3 sub_vec = pos - bulletpos;
					ENTITY::APPLY_FORCE_TO_ENTITY(new_ent, 3, Vector3(sub_vec.x * 2.f, sub_vec.y * 2.f, sub_vec.z * 2.f), { 0.0f, 0.f, 0.f }, 0, 0, 1, 1, 0, 1);

				}
				ins_gun_bullet_vec.push_back(new_ent);
			}
		}

		for (int& ins_gun_bullet : ins_gun_bullet_vec) {
			if (!ENTITY::DOES_ENTITY_EXIST(ins_gun_bullet)) {
				auto it = std::find(ins_gun_bullet_vec.begin(), ins_gun_bullet_vec.end(), ins_gun_bullet);
				if (it != ins_gun_bullet_vec.end()) {
					it = ins_gun_bullet_vec.erase(it);
				}
			}
			Vector3 bulletpos = ENTITY::GET_ENTITY_COORDS(ins_gun_bullet, 0);
			if (value2 == 0)
				if (PED::GET_PED_CONFIG_FLAG(globals::h_local_ped(), CPED_CONFIG_FLAG_IsAimingGun, 0))
				{
					Vector3 sub_vec = pos - bulletpos;

					ENTITY::APPLY_FORCE_TO_ENTITY(ins_gun_bullet, 3, Vector3(sub_vec.x * 0.5f, sub_vec.y * 0.5f, sub_vec.z * 0.5f), { 0.0f, 0.f, 0.f }, 0, 0, 1, 1, 0, 1);
				}
			tasks::play_ptfx_bone_tick(ins_gun_bullet, 0, (char*)"scr_agencyheistb", (char*)"scr_agencyheistb", (char*)"scr_agency3b_heli_expl", 0.1f, false, 0.f, 0.f, 0.f);

			if (ENTITY::HAS_ENTITY_COLLIDED_WITH_ANYTHING(ins_gun_bullet))
			{
				FIRE::ADD_EXPLOSION(bulletpos, (int)eExplosionTag::EXP_TAG_SUBMARINE_BIG, 9999.f, 1, 0, 0.1f, false);
				ENTITY::DELETE_ENTITY(&ins_gun_bullet);
				auto it = std::find(ins_gun_bullet_vec.begin(), ins_gun_bullet_vec.end(), ins_gun_bullet);
				if (it != ins_gun_bullet_vec.end()) {
					it = ins_gun_bullet_vec.erase(it);
				}
				ins_gun_bullet = 0;
			}

		}
	}
}
namespace insight {
	Hash last_weapon_infammo;
	void weapon::infammo(toggle_feature* feature, bool& value) {
		if (!value)
			return;
		if (last_weapon_infammo != globals::c_local_ped()->m_weapon_manager->m_selected_weapon_hash)
		{
			WEAPON::SET_PED_INFINITE_AMMO(globals::h_local_ped(), false, last_weapon_infammo);
			last_weapon_infammo = globals::c_local_ped()->m_weapon_manager->m_selected_weapon_hash;
		}
		else
		{
			WEAPON::SET_PED_INFINITE_AMMO(globals::h_local_ped(), true, globals::c_local_ped()->m_weapon_manager->m_selected_weapon_hash);
		}

	}
}
namespace insight {
	Entity gravity_gun_entity = 0;
	Entity last_gravity_gun_entity = 0;
	static timer last_gravity_gun_entity_timer(std::chrono::milliseconds(600ms));
	static timer gravity_gun_timer(std::chrono::milliseconds(100ms));
	bool gravity_gun_was_aiming = false;

	void weapon::gravity_gun(toggle_int_feature* feature, bool& value, int& value2) {
		if (!value)
			return;
		if (last_gravity_gun_entity)
			if (last_gravity_gun_entity_timer.update()) {
				last_gravity_gun_entity = 0;
			}
		if (input::get()->is_input_aim_pressed()) {
			if (!gravity_gun_entity) {
				if (tasks::is_player_shooting(globals::player_id)) {
					gravity_gun_entity = tasks::create_cast_entites();
				}
			}
			else {
				gravity_gun_was_aiming = true;
				auto weaponEntity = WEAPON::GET_CURRENT_PED_WEAPON_ENTITY_INDEX(globals::h_local_ped(), 0);
				int bone = ENTITY::GET_ENTITY_BONE_INDEX_BY_NAME(weaponEntity, xorstr_("gun_muzzle"));
				auto coords = ENTITY::GET_WORLD_POSITION_OF_ENTITY_BONE(weaponEntity, ENTITY::GET_ENTITY_BONE_INDEX_BY_NAME(weaponEntity, xorstr_("gun_muzzle")));
				if ("weapon_gravity_gun_fx"_tf->m_value.toggle)
					if (gravity_gun_timer.update()) {
						if (gravity_gun_entity)
							tasks::play_ptfx_bone_woffsets_tick(weaponEntity, bone, xorstr_("weap_xs_weapons"), xorstr_("weap_xs_weapons"), xorstr_("muz_xs_sr_raygun"), 1.0, Vector3(0, 0, 0), Vector3(0, 180, 0));
					}
				if (gravity_gun_entity) {
					if (tasks::is_player_shooting(globals::player_id)) {
						if (tasks::get_control_of_entity_tick(gravity_gun_entity))
							tasks::apply_force_to_position(gravity_gun_entity,
								vectors::get()->get_front_camera_coordinates_local(200) - ENTITY::GET_ENTITY_COORDS(gravity_gun_entity, 0),
								ENTITY::GET_ENTITY_VELOCITY(gravity_gun_entity), "weapon_gravity_gun_throwforce"_FF->m_value.floating_point, 0.3);
						last_gravity_gun_entity = gravity_gun_entity;
						gravity_gun_entity = 0;
						last_gravity_gun_entity_timer.restart();
					}
					else {
						if (value2 == 0) {
							render::get()->draw_text_coordinates("Throw Me!", ENTITY::GET_ENTITY_COORDS(gravity_gun_entity, 0), 255, 255, 255, 255);
							if (tasks::get_control_of_entity_tick(gravity_gun_entity))
								tasks::apply_force_to_position(gravity_gun_entity,
									vectors::get()->get_front_camera_coordinates_local("weapon_gravity_gun_distance"_FF->m_value.floating_point) - ENTITY::GET_ENTITY_COORDS(gravity_gun_entity, 0),
									ENTITY::GET_ENTITY_VELOCITY(gravity_gun_entity), "weapon_gravity_gun_pickforce"_FF->m_value.floating_point, 0.3);
						}
						if (value2 == 1) {
							if (tasks::get_control_of_entity_tick(gravity_gun_entity))
								ENTITY::SET_ENTITY_COORDS_NO_OFFSET(gravity_gun_entity, vectors::get()->get_front_camera_coordinates_local("weapon_gravity_gun_distance"_FF->m_value.floating_point), false, false, false);
						}

					}
				}
			}
		}
		else {
			if (gravity_gun_was_aiming) {
				gravity_gun_entity = 0;
				gravity_gun_was_aiming = false;
			}
		}
	}
}
namespace insight {
	void weapon::force_gun(toggle_float_feature* feature, bool& value, float& value2) {
		if (!value)
			return;
		Vector3 impact_coords;
		if (tasks::is_player_shooting(globals::player_id)) {
			Entity handle;
			ray_cast cast = tasks::create_cast(&handle);
			if (cast.m_hit) {
				Vector3 force = cast.m_coords - globals::h_local_ped_pos();
				if (tasks::request_control(handle))
					ENTITY::APPLY_FORCE_TO_ENTITY(handle, 3, force * value2, { 0, 0, 0 }, 0, false, true, true, false, true);
			}
		}
	}
}
namespace insight {
	void weapon::flaming_ammo(toggle_feature* feature, bool& value) {
		if (!value)
			return;
		Vector3 impact_coords;
		if (tasks::is_player_shooting(globals::player_id)) {
			Entity handle;
			ray_cast cast = tasks::create_cast(&handle);
			if (cast.m_hit) {
				if (tasks::request_control(handle))
				{
					if (ENTITY::IS_ENTITY_A_PED(handle))
						FIRE::START_ENTITY_FIRE(handle);
					else if (ENTITY::IS_ENTITY_A_VEHICLE(handle))
					{
						Vector3 pos = ENTITY::GET_ENTITY_COORDS(handle, true);
						for (size_t i = 0; i < 4; i++)
						{
							FIRE::ADD_EXPLOSION(pos, 3, 99.0f, false, false, 0.0f, false);
							//real
						}
					}
				}
			}
		}
	}
}
namespace insight {
	int fxHandle1 = 0;
	bool was_flame_thrower_on = false;
	bool was_flame_thrower_on2 = false;
	void weapon::flame_thrower(toggle_feature* feature, bool& value) {
		if (!value)
		{
			if (was_flame_thrower_on)
			{
				WEAPON::SET_PED_INFINITE_AMMO(globals::h_local_ped(), false, 101631238);
				was_flame_thrower_on = false;
			}
			return;
		}
		if (!was_flame_thrower_on)
		{
			WEAPON::GIVE_DELAYED_WEAPON_TO_PED(globals::h_local_ped(), 101631238, 99, true);
			WEAPON::SET_PED_INFINITE_AMMO(globals::h_local_ped(), true, 101631238);
			was_flame_thrower_on = true;
		}
		//Thank You X-man i am lazy !!
		Hash whash;
		WEAPON::GET_CURRENT_PED_WEAPON(PLAYER::PLAYER_PED_ID(), &whash, 1);
		if (whash != 101631238)
		{
			if (was_flame_thrower_on2)
			{
				PLAYER::DISABLE_PLAYER_FIRING(globals::player_id, false);
				was_flame_thrower_on2 = false;
			}
			return;
		}
		was_flame_thrower_on2 = true;
		PLAYER::DISABLE_PLAYER_FIRING(globals::player_id, true);
		float scale = 2.0f;
		if (!STREAMING::HAS_NAMED_PTFX_ASSET_LOADED("core"))
			STREAMING::REQUEST_NAMED_PTFX_ASSET("core");
		if (!input::get()->is_input_aim_pressed())
			return;
		if (PAD::IS_DISABLED_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_ATTACK))
		{
			Entity wobject = WEAPON::GET_CURRENT_PED_WEAPON_ENTITY_INDEX(globals::h_local_ped(), 0);
			Hash wmodel = ENTITY::GET_ENTITY_MODEL(wobject);
			int gunBone = ENTITY::GET_ENTITY_BONE_INDEX_BY_NAME(wobject, "Gun_Nuzzle");
			tasks::request_control(wobject);
			if (!GRAPHICS::DOES_PARTICLE_FX_LOOPED_EXIST(fxHandle1))
			{
				GRAPHICS::USE_PARTICLE_FX_ASSET("core");
				fxHandle1 = GRAPHICS::START_NETWORKED_PARTICLE_FX_LOOPED_ON_ENTITY_BONE("ent_sht_flame", wobject, { 0.0f, 0.0f, 0.04f }, { 128.5f, 0.0f, 90.0f }, gunBone, scale, 0, 0, 0, 255, 255, 255, 255);
			}
			Vector3 pos = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(globals::h_local_ped(), { 0,3,0 });
			std::vector<Entity> nearbyEntities = tasks::get_world_entities(true, true, false);
			for (const auto& entity : nearbyEntities) {
				if (SYSTEM::VDIST(pos, ENTITY::GET_ENTITY_COORDS(entity, 0)) < 3) {
					if (ENTITY::IS_ENTITY_A_PED(entity))
						FIRE::START_ENTITY_FIRE(entity);
					else if (ENTITY::IS_ENTITY_A_VEHICLE(entity))
						FIRE::ADD_EXPLOSION(ENTITY::GET_ENTITY_COORDS(entity, 0), 3, 9, false, false, 0, false);
				}

			}
			GRAPHICS::STOP_PARTICLE_FX_LOOPED(fxHandle1, 1);
		}return;
	}
}
namespace insight {
	void weapon::explosion_impact(toggle_int_feature* feature, bool& value, int& value2) {
		if (!value)
			return;
		Vector3 impact_coords;
		if (tasks::is_player_shooting(globals::player_id)) {
			Entity handle;
			ray_cast cast = tasks::create_cast(&handle);
			if (cast.m_hit) {
				FIRE::ADD_EXPLOSION(cast.m_coords, value2, "weapon_impact_explosion_dmgscale"_FF->m_value.floating_point, "weapon_impact_explosion_audio"_tf->m_value.toggle
					, "weapon_impact_explosion_invisible"_tf->m_value.toggle, "weapon_impact_explosion_cam_shake"_FF->m_value.floating_point, !"weapon_impact_explosion_damage"_tf->m_value.toggle);
			}
		}
	}
}
namespace insight {
	Entity Bullet_dub_step = 0;
	std::vector<Entity> dub_step_entities;
	void dubstep_nearby_ent_get(int i)
	{
		if (Bullet_dub_step)
		{
			if (SYSTEM::VDIST(ENTITY::GET_ENTITY_COORDS(Bullet_dub_step, 0), ENTITY::GET_ENTITY_COORDS(i, 0)) < 10)
			{
				Entity new_entity = i;
				if (std::find(dub_step_entities.begin(), dub_step_entities.end(), new_entity) == dub_step_entities.end()) {
					dub_step_entities.push_back(new_entity);
				}
			}
		}
	}
	timer dub_step_ped(1000ms);
	timer gun_fx(1000ms);
	bool was_dubstep_gun_on = false;
	void weapon::dubstep_gun(toggle_feature* feature, bool& value) {
		if (!value)
		{
			if (was_dubstep_gun_on)
			{
				PlaySound(NULL, 0, 0);
				dub_step_entities.clear();
				Bullet_dub_step = 0;
				was_dubstep_gun_on = false;
			}
			return;
		}
		if (!was_dubstep_gun_on)
		{
			WEAPON::GIVE_DELAYED_WEAPON_TO_PED(globals::h_local_ped(), "weapon_railgun"_joaat, 99, true);
			was_dubstep_gun_on = true;
		}

		if (globals::c_local_ped() && globals::c_local_ped()->m_weapon_manager && globals::c_local_ped()->m_weapon_manager->m_selected_weapon_hash == rage::joaat("weapon_railgun"))
		{
			if (gun_fx.update())
			{
				Entity wobject = WEAPON::GET_CURRENT_PED_WEAPON_ENTITY_INDEX(globals::h_local_ped(), 0);
				tasks::get()->play_ptfx_bone_tick(wobject, 0, xorstr_("scr_powerplay"), xorstr_("scr_powerplay"), xorstr_("sp_powerplay_beast_appear_trails"),
					0.5, true, 55.f, 20.f, 147.f);
			}
			WEAPON::REFILL_AMMO_INSTANTLY(globals::h_local_ped());
			PLAYER::DISABLE_PLAYER_FIRING(globals::player_id, false);
			for (const auto& entity : dub_step_entities) {
				if (ENTITY::DOES_ENTITY_EXIST(entity))
				{
					if (ENTITY::IS_ENTITY_A_PED(entity))
					{
						if (PED::IS_PED_A_PLAYER(entity))
						{
							auto it = std::find(dub_step_entities.begin(), dub_step_entities.end(), entity);
							if (it != dub_step_entities.end()) {
								dub_step_entities.erase(it);
							}
						}
						else
						{
							if (!ENTITY::IS_ENTITY_DEAD(entity, 0))
							{
								if (tasks::get()->request_control(entity))
								{
									const char* anim_dic = xorstr_("misschinese2_crystalmazemcs1_ig");
									const char* anim_id = xorstr_("dance_loop_tao");
									if (!ENTITY::IS_ENTITY_PLAYING_ANIM(entity, anim_dic, anim_id, 3))
									{
										PED::SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(entity, true);
										dub_step_ped.setdelay(1000ms);
										if (dub_step_ped.update())
										{
											TASK::CLEAR_PED_TASKS_IMMEDIATELY(entity);
										}

										tasks::get()->play_ptfx_bone_tick(entity, 0, xorstr_("scr_rcbarry2"), xorstr_("scr_rcbarry2"), xorstr_("scr_exp_clown"), 0.3, 0, MISC::GET_RANDOM_FLOAT_IN_RANGE(0, 255), MISC::GET_RANDOM_FLOAT_IN_RANGE(0, 255), MISC::GET_RANDOM_FLOAT_IN_RANGE(0, 255));
										tasks::get()->play_animation_tick(entity, (char*)anim_dic, (char*)anim_id, 1);

									}
								}
							}
						}
					}
					if (ENTITY::IS_ENTITY_A_VEHICLE(entity))
					{
						if (VEHICLE::IS_VEHICLE_ON_ALL_WHEELS(entity))
						{
							if (tasks::get()->get_control_of_entity_tick(entity))
							{
								tasks::get()->play_ptfx_bone_tick(entity, 0, xorstr_("scr_rcbarry2"), xorstr_("scr_rcbarry2"), xorstr_("scr_exp_clown"), 0.3, 0, MISC::GET_RANDOM_FLOAT_IN_RANGE(0, 255), MISC::GET_RANDOM_FLOAT_IN_RANGE(0, 255), MISC::GET_RANDOM_FLOAT_IN_RANGE(0, 255));
								ENTITY::APPLY_FORCE_TO_ENTITY(entity, true, Vector3(MISC::GET_RANDOM_FLOAT_IN_RANGE(0, 6), MISC::GET_RANDOM_FLOAT_IN_RANGE(0, 6), MISC::GET_RANDOM_FLOAT_IN_RANGE(0, 6)),
									Vector3(MISC::GET_RANDOM_FLOAT_IN_RANGE(0, 2), MISC::GET_RANDOM_FLOAT_IN_RANGE(0, 2), MISC::GET_RANDOM_FLOAT_IN_RANGE(0, 2)),
									true, true, true, true, false, true);
							}
						}
					}
				}
				else
				{
					auto it = std::find(dub_step_entities.begin(), dub_step_entities.end(), entity);
					if (it != dub_step_entities.end()) {
						dub_step_entities.erase(it);
					}
				}
			}

			Vector3 spawn = vectors::get()->get_front_camera_coordinates_local(2);
			Vector3 pos = vectors::get()->get_front_camera_coordinates_local(500);
			bool is_attacking = PAD::IS_DISABLED_CONTROL_PRESSED(2, (int)ControllerInputs::INPUT_ATTACK) && PED::GET_PED_CONFIG_FLAG(globals::h_local_ped(), CPED_CONFIG_FLAG_IsAimingGun, 0);
			auto path = std::filesystem::path(std::getenv("appdata")).append("insight").append("sounds").append("dubstep.wav");

			static  bool prev_attacking = false;
			std::string soundPath = path.generic_string();
			if (!soundPath.empty()) {
				if (is_attacking != prev_attacking) {
					if (is_attacking) {
						if (!PlaySoundA(soundPath.c_str(), NULL, SND_FILENAME | SND_ASYNC)) {
							std::cout << xorstr_("Failed to play sound: ") << GetLastError() << std::endl;
						}
					}
					else {
						if (!PlaySound(NULL, 0, 0)) {
							std::cout << xorstr_("Failed to stop sound: ") << GetLastError() << std::endl;
						}
					}
					prev_attacking = is_attacking;
				}
			}

			if (is_attacking)
			{
				Hash hash = "prop_prototype_minibomb"_joaat;
				if (is_attacking)
				{
					while (!STREAMING::HAS_MODEL_LOADED(hash))
					{
						STREAMING::REQUEST_MODEL(hash);
						script::get_current()->yield();
					}
					if (!Bullet_dub_step)
					{
						Bullet_dub_step = OBJECT::CREATE_OBJECT(hash, spawn, 1, 0, 0);

						Vector3 bulletpos = ENTITY::GET_ENTITY_COORDS(Bullet_dub_step, 0);
						ENTITY::SET_ENTITY_ALPHA(Bullet_dub_step, 0, 0);
						Vector3 sub_vec = pos - bulletpos;
						ENTITY::APPLY_FORCE_TO_ENTITY(Bullet_dub_step, 3, sub_vec, { 0.0f, 0.f, 0.f }, 0, 0, 1, 1, 0, 1);

					}
				}

				if (Bullet_dub_step)
				{
					for (std::uint32_t i = 0; i < 4; ++i)
					{
						Vector3 index_sides = Vector3(MISC::GET_RANDOM_INT_IN_RANGE(3, -3), MISC::GET_RANDOM_INT_IN_RANGE(3, -3), MISC::GET_RANDOM_INT_IN_RANGE(3, -3));
						tasks::get()->play_ptfx_bone_woffsets_tick(Bullet_dub_step, 0, xorstr_("scr_powerplay"), xorstr_("scr_powerplay"), xorstr_("sp_powerplay_beast_appear_trails"), 1, index_sides, Vector3(0, 0, 0), true, MISC::GET_RANDOM_FLOAT_IN_RANGE(0, 255), MISC::GET_RANDOM_FLOAT_IN_RANGE(0, 255), MISC::GET_RANDOM_FLOAT_IN_RANGE(0, 255));
					}
					for (auto entity : tasks::get_world_entities(true, true, false))
					{
						dubstep_nearby_ent_get(entity);
					}

					timer START_DELETE_TIMER(5000ms);
					if (ENTITY::HAS_ENTITY_COLLIDED_WITH_ANYTHING(Bullet_dub_step) || START_DELETE_TIMER.update())
					{
						ENTITY::DELETE_ENTITY(&Bullet_dub_step);
						Bullet_dub_step = 0;
					}
				}
				else
					Bullet_dub_step = 0;

			}
			else
			{
				ENTITY::DELETE_ENTITY(&Bullet_dub_step);
				Bullet_dub_step = 0;
			}
		}
	}
}
namespace insight {
	void weapon::drive_it_gun(toggle_feature* feature, bool& value) {
		if (!value)
			return;
		Vector3 impact_coords;
		if (tasks::is_player_shooting(globals::player_id)) {
			Entity handle;
			ray_cast cast = tasks::create_cast(&handle);
			if (cast.m_hit) {
				if (auto ped = VEHICLE::GET_PED_IN_VEHICLE_SEAT(handle, -1, 1)) {
					TASK::CLEAR_PED_TASKS_IMMEDIATELY(ped);
				}
				PED::SET_PED_INTO_VEHICLE(globals::h_local_ped(), handle, -1);
			}
		}
	}
}
namespace insight {
	void weapon::destroy_ped(toggle_feature* feature, bool& value) {
		if (!value)
			return;
		Vector3 impact_coords;
		if (tasks::is_player_shooting(globals::player_id)) {
			Entity handle;
			ray_cast cast = tasks::create_cast(&handle);
			if (cast.m_hit) {
				tasks::request_control(handle);
				ENTITY::SET_ENTITY_HEALTH(handle, 0, 0);
				ENTITY::APPLY_FORCE_TO_ENTITY(handle, 3, { 0,0,-100 }, { 0, 0, 0 }, 0, false, true, true, false, true);

			}
		}
	}
}
namespace insight {
	void weapon::delete_gun(toggle_feature* feature, bool& value) {
		if (!value)
			return;
		Vector3 impact_coords;
		if (tasks::is_player_shooting(globals::player_id)) {
			Entity handle;
			ray_cast cast = tasks::create_cast(&handle);
			if (cast.m_hit) {
				if (tasks::get_control_of_entity_tick(handle))
					tasks::delete_entity(handle);
			}
		}
	}
}
namespace insight {
	bool was_dead_eye_on;
	void weapon::dead_eye(toggle_feature* feature, bool& value) {
		if (!value) {
			if (was_dead_eye_on) {
				MISC::SET_TIME_SCALE(1.f);
				was_dead_eye_on = false;
			}
			return;
		}

		if (input::get()->is_input_aim_pressed()) {
			was_dead_eye_on = true;
			MISC::SET_TIME_SCALE(0.6f);
			GRAPHICS::ANIMPOSTFX_PLAY("RaceTurbo", 0, 0);
		}
		else {
			MISC::SET_TIME_SCALE(1.0f);
		}
	}
}
namespace insight {
	bool was_shotgun_mode_on;
	void weapon::shotgun_mode(toggle_feature* feature, bool& value) {
		if (!value) {
			if (was_shotgun_mode_on) {
				if (auto WeaponInfo = globals::c_local_weapon()->m_weapon_info; WeaponInfo) {
					WeaponInfo->m_batch_spread = 0.01f;
					WeaponInfo->m_bullets_in_batch = 1;
				}
				was_dead_eye_on = false;
			}
			return;
		}
		if ("weapon_rapidfire"_tf->m_value.toggle) {
			"weapon_rapidfire"_tf->m_value.toggle = false;
			//cause = crashing
		}
		if (auto WeaponInfo = globals::c_local_weapon()->m_weapon_info; WeaponInfo) {
			WeaponInfo->m_batch_spread = 0.5f;
			WeaponInfo->m_bullets_in_batch = 30;
			WeaponInfo->m_force = 200.0f;
			WeaponInfo->m_speed = 5000.0f;
		}

		was_shotgun_mode_on = true;
	}
}
namespace insight {
	struct bullet_tracers_data_str {
		Vector3 pos1;
		Vector3 pos2;
		bool was_shotgun;
		color color;
	};
	std::vector<bullet_tracers_data_str> bullet_tracers_data;
	bool was_bullet_tracers_on = false;
	void weapon::bullet_tracers(toggle_feature* feature, bool& value) {
		if (!value) {
			if (was_bullet_tracers_on) {
				bullet_tracers_data.clear();
				was_bullet_tracers_on = false;
			}
			return;
		}
		was_bullet_tracers_on = true;
		for (size_t i = 0; i < bullet_tracers_data.size(); i++) {
			bullet_tracers_data_str data = bullet_tracers_data[i];
			GRAPHICS::DRAW_LINE(data.pos1, data.pos2, data.color.r, data.color.g, data.color.b, 255);
			float distanceInFeet = SYSTEM::VDIST(data.pos1, data.pos2) * 3.28084f;
			float roundedDistance = std::roundf(distanceInFeet * 100) / 100;
			std::ostringstream oss;
			oss << std::fixed << std::setprecision(2) << roundedDistance;
			std::string formattedDistance = oss.str();
			render::get()->draw_text_coordinates(std::string(formattedDistance + "ft").c_str(), data.pos2, 255, 255, 255, 255, 0.18);
			if (data.was_shotgun) {
				tasks::draw_marker(eMarkerType::MarkerTypeDebugSphere, data.pos2, 0.2f, 0, 120, 200, 200);
			}
		}
		Vector3 start_coords_of_projectile = tasks::get()->get_weapon_bone_coords("gun_muzzle");
		bool is_shotgun = tasks::get_weapon_type(globals::c_local_weapon()->m_selected_weapon_hash) == 1;
		if (tasks::is_player_shooting(globals::player_id)) {
			if ("weapon_bullet_tracers_limiter"_tif->m_toggle_value.toggle) {
				int limit = "weapon_bullet_tracers_limiter"_tif->m_number_value.integer;
				if (bullet_tracers_data.size() > limit) {
					bullet_tracers_data.erase(bullet_tracers_data.begin(), bullet_tracers_data.begin() + (bullet_tracers_data.size() - limit));
				}
			}bullet_tracers_data.push_back(bullet_tracers_data_str(start_coords_of_projectile, tasks::get()->get_laser_ending_coordinates(), is_shotgun, features_utility::get()->n_bullet_tracer_color));
		}
	}
}
namespace insight {
	void fuc_black_hole_gun(Vector3 pos, int entity, bool del)
	{
		Vector3 entitycor = ENTITY::GET_ENTITY_COORDS(entity, 0);
		if (SYSTEM::VDIST(entitycor, pos) < 50) {
			Vector3 sub_vec = pos - ENTITY::GET_ENTITY_COORDS(entity, 0);
			if (tasks::get_control_of_entity_tick(entity)) {
				if (del) {
					if (SYSTEM::VDIST(entitycor, pos) < 2)
					{
						tasks::delete_entity(entity);
					}
				}
				if (tasks::get_control_of_entity_tick(entity))
					ENTITY::APPLY_FORCE_TO_ENTITY(entity, 3, sub_vec, { 0.0f, 0.f, 0.f }, 0, 0, 1, 1, 0, 1);
			}
		}
	}
	std::vector<std::pair<Vector3, timer>> blackhole_gun_pos;
	void weapon::blackhole_gun(toggle_int_feature* feature, bool& value, int& value2) {
		if (!value)
			return;

		if (tasks::get()->is_player_shooting(globals::player_id)) {
			Vector3 pos = tasks::get()->get_laser_ending_coordinates();
			blackhole_gun_pos.emplace_back(pos, timer(std::chrono::seconds(2)));

		}

		for (size_t i = 0; i < blackhole_gun_pos.size();) {
			auto& [vector, timer] = blackhole_gun_pos[i];
			if (timer.update()) {
				blackhole_gun_pos.erase(blackhole_gun_pos.begin() + i);
			}
			else {
				bool del = value2 == 1;
				for (auto entity : tasks::get_world_entities(true, true, false))
				{
					fuc_black_hole_gun(vector, entity, del);
				}
				tasks::get()->draw_marker(eMarkerType::MarkerTypeDebugSphere, vector, 2, 20, 20, 20);
				++i;
			}
		}

	}
}
namespace insight {
	Vector3 generate_random_coordinates(const Vector3& center)
	{
		const int minX = center.x;
		const int maxX = center.x + 50;
		const int minY = center.y;
		const int maxY = center.y + 50;
		const int minZ = center.z + 55;
		const int maxZ = center.z + 65;

		const int x = MISC::GET_RANDOM_INT_IN_RANGE(minX, maxX);
		const int y = MISC::GET_RANDOM_INT_IN_RANGE(minY, maxY);
		const int z = MISC::GET_RANDOM_INT_IN_RANGE(minZ, maxZ);

		return Vector3(x, y, z);
	}
	void weapon::airstrike_gun(toggle_int_feature* feature, bool& value, int& value2) {
		if (!value)
			return;
		Vector3 impact_coords;
		if (tasks::is_player_shooting(globals::player_id)) {
			Entity handle;
			ray_cast cast = tasks::create_cast(&handle);
			{
				impact_coords = cast.m_coords;
				MISC::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(generate_random_coordinates(impact_coords),
					impact_coords,
					50, false, "weapon_impact_airstrike"_tf->m_value.integer, value2 == 1 ? globals::h_local_ped() : NULL, true, true, "weapon_impact_airstrike_speed"_FF->m_value.floating_point);
			}
		}
	}
}
namespace insight {
	void weapon::aimed_explosive(toggle_feature* feature, bool& value) {
		Entity del_entity;
		if (PLAYER::GET_ENTITY_PLAYER_IS_FREE_AIMING_AT(PLAYER::PLAYER_ID(), &del_entity)) {
			if (ENTITY::DOES_ENTITY_EXIST(del_entity) && tasks::request_control(del_entity)) {
				Vector3 tmp = ENTITY::GET_ENTITY_COORDS(del_entity, 1);
				FIRE::ADD_EXPLOSION(tmp, 0, 1000.f, true, false, 0.0f, false);
			}
		}
	}
}
namespace insight {
	bool was_aimbot_on = false;
	timer aimbot_val2_dealay(0ms);
	float first_time_fov = 0;

	Cam camera_f = 0;
	void weapon::aimbot(toggle_int_feature* feature, bool& value, int& value2) {
		if (!value) {
			if (was_aimbot_on) {
				globals::c_local_weapon()->m_weapon_info->m_camera_fov = first_time_fov;
				was_aimbot_on = false;
			}
			return;
		}
		if (value2 == 0) {
			was_aimbot_on = true;
			Vector3 aim_lock;
			Vector2 mouse_movement;
			if (features_utility::get()->aimbot_selected_bones.empty())
				return;
			uint32_t selected_bone = vectors::get()->get_random_vector(features_utility::get()->aimbot_selected_bones);
			int dx1, dy1;
			float local_fov_change = "weapon_aimbot_fov"_FF->m_value.floating_point;
			if (first_time_fov == 0) {
				first_time_fov = globals::c_local_weapon()->m_weapon_info->m_camera_fov;
			}
			globals::c_local_weapon()->m_weapon_info->m_camera_fov = local_fov_change;

			for (auto ped : tasks::get_world_entities(false, true, false)) {
				if (!ENTITY::IS_ENTITY_DEAD(ped, 0)) {
					int relation = PED::GET_RELATIONSHIP_BETWEEN_PEDS(ped, PLAYER::PLAYER_PED_ID());
					int type = PED::GET_PED_TYPE(ped);
					Vector3 world_position = ENTITY::GET_ENTITY_COORDS(ped, false);

					if (SYSTEM::VDIST2(ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true), world_position) > ("weapon_aimbot_distance"_FF->m_value.floating_point * "weapon_aimbot_distance"_FF->m_value.floating_point))
						continue;
					if ("weapon_aimbot_target"_if->m_value.integer == 0 && PED::IS_PED_A_PLAYER(ped))
					{
						goto aimbot_handler;
					}
					else
						if ("weapon_aimbot_target"_if->m_value.integer == 1 && !PED::IS_PED_A_PLAYER(ped))
						{
							goto aimbot_handler;
						}
						else
							if ("weapon_aimbot_target"_if->m_value.integer == 2) {
								goto aimbot_handler;
							}
							else
							{
								return;
							}
				aimbot_handler:
					{
						if (!ENTITY::HAS_ENTITY_CLEAR_LOS_TO_ENTITY(globals::h_local_ped(), ped, 17))
							continue;

						aim_lock = ENTITY::GET_WORLD_POSITION_OF_ENTITY_BONE(ped, PED::GET_PED_BONE_INDEX(ped, selected_bone));
						if ("weapon_aimbot_silent"_tf->m_value.toggle) {
							PLAYER::DISABLE_PLAYER_FIRING(globals::player_id, TRUE);
						}
						if ((aim_lock.x != 0) && (aim_lock.y != 0) && (aim_lock.z != 0)) // Ensure none of the coords are = to 0
						{
							Vector2 screen_dim, movement;
							GRAPHICS::GET_SCREEN_COORD_FROM_WORLD_COORD(aim_lock, &screen_dim.x, &screen_dim.y);
							if ((screen_dim.x >= 0) && (screen_dim.y >= 0)) {
								GRAPHICS::GET_ACTUAL_SCREEN_RESOLUTION(&dx1, &dy1);
								Vector2 io = { (float)dx1, (float)dy1 };
								Vector2 center(io.x / 2.f, io.y / 2.f);
								screen_dim.x *= io.x;
								screen_dim.y *= io.y;

								if (screen_dim.x > center.x) {
									movement.x = -(center.x - screen_dim.x);
									if (movement.x + center.x > center.x * 2)
										movement.x = 0;
								}
								else {
									movement.x = screen_dim.x - center.x;
									if (movement.x + center.x < 0)
										movement.x = 0;
								}
								if (screen_dim.y > center.y)
								{
									movement.y = -(center.y - screen_dim.y);
									if (movement.y + center.y > center.y * 2)
										movement.y = 0;
								}
								else {
									movement.y = screen_dim.y - center.y;
									if (movement.y + center.y < 0)
										movement.y = 0;
								}

								if (sqrt(pow(movement.x, 2) + pow(movement.y, 2)) < local_fov_change)
									local_fov_change = sqrt(pow(movement.x, 2) + pow(movement.y, 2));
								mouse_movement.x = movement.x;
								mouse_movement.y = movement.y;
							}
						}
						if ("weapon_aimbot_silent"_tf->m_value.toggle) {
							if (PAD::GET_DISABLED_CONTROL_NORMAL(0, (int)ControllerInputs::INPUT_ATTACK))
							{
								Vector3 padd = ENTITY::GET_ENTITY_BONE_POSTION(ped, PED::GET_PED_BONE_INDEX(ped, selected_bone));
								padd.z += 0.2f;
								Hash weaponhash;
								WEAPON::GET_CURRENT_PED_WEAPON(globals::h_local_ped(), &weaponhash, 1);
								MISC::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(padd, ENTITY::GET_ENTITY_BONE_POSTION(ped, PED::GET_PED_BONE_INDEX(ped, selected_bone)), WEAPON::GET_WEAPON_DAMAGE(weaponhash, 0), 0, weaponhash, globals::h_local_ped(), false, false, 100.f);
							}
						}
					}
				}
			}

			if (PAD::GET_DISABLED_CONTROL_NORMAL(0, (int)ControllerInputs::INPUT_AIM))
			{
				static bool update_time_now = true;
				static std::chrono::system_clock::time_point current_time;

				if (update_time_now)
				{
					current_time = std::chrono::system_clock::now();
					update_time_now = false;
				}

				std::chrono::duration<double> elapsed_time = std::chrono::system_clock::now() - current_time;
				if (elapsed_time.count() > 0.f)
				{
					float sensitivity = 2.0f;
					float smoothingFactor = 0.1f;
					float maxMovement = 10.0f;

					mouse_movement.x /= sensitivity;
					mouse_movement.y /= sensitivity;
					mouse_movement.x = mouse_movement.x * smoothingFactor + mouse_movement.x * (1 - smoothingFactor);
					mouse_movement.y = mouse_movement.y * smoothingFactor + mouse_movement.y * (1 - smoothingFactor);

					if (mouse_movement.x > maxMovement)
						mouse_movement.x = maxMovement;
					else if (mouse_movement.x < -maxMovement)
						mouse_movement.x = -maxMovement;

					if (mouse_movement.y > maxMovement)
						mouse_movement.y = maxMovement;
					else if (mouse_movement.y < -maxMovement)
						mouse_movement.y = -maxMovement;

					INPUT mouse_handle;
					mouse_handle.type = INPUT_MOUSE;
					mouse_handle.mi.dwFlags = MOUSEEVENTF_MOVE;
					mouse_handle.mi.dx = mouse_movement.x;
					mouse_handle.mi.dy = mouse_movement.y;
					SendInput(1, &mouse_handle, sizeof(mouse_handle));
					mouse_movement.x = 0;
					mouse_movement.y = 0;
					update_time_now = true;
				}
			}
		}
		else if (value == 1) {
			if (input::get()->is_input_aim_pressed()) {
				HUD::DISPLAY_SNIPER_SCOPE_THIS_FRAME();
				if (!CAM::DOES_CAM_EXIST(camera_f)) {
					camera_f = CAM::CREATE_CAM("DEFAULT_SCRIPTED_CAMERA", 1);
					CAM::SET_CAM_COORD(camera_f, CAM::GET_GAMEPLAY_CAM_COORD());
					CAM::SET_CAM_FOV(camera_f, CAM::GET_GAMEPLAY_CAM_FOV());
				}
				else {

					CAM::SET_CAM_COORD(camera_f, ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(globals::h_local_ped(), Vector3(0.5, -3, 1)));
					CAM::SET_CAM_FOV(camera_f, CAM::GET_GAMEPLAY_CAM_FOV());
					if (int ent = tasks::get()->get_closest_screen_entity()) {
						if (!ENTITY::IS_ENTITY_DEAD(ent, 0) && ENTITY::HAS_ENTITY_CLEAR_LOS_TO_ENTITY(ent, globals::h_local_ped(), 17) && ENTITY::IS_ENTITY_A_PED(ent)) {
							CAM::RENDER_SCRIPT_CAMS(true, true, 100, 1, 1, 0);
							CAM::SET_CAM_ACTIVE(camera_f, true);
							CAM::POINT_CAM_AT_PED_BONE(camera_f, ent, 0, Vector3(0, 0, 0), 0);
						}
						else {
							CAM::RENDER_SCRIPT_CAMS(false, true, 100, 1, 1, 1);
							CAM::SET_CAM_ACTIVE(camera_f, false);
						}

					}
				}
			}
			else {
				if (CAM::DOES_CAM_EXIST(camera_f)) {
					CAM::RENDER_SCRIPT_CAMS(false, true, 100, 1, 1, 1);
					CAM::SET_CAM_ACTIVE(camera_f, false);
					CAM::DESTROY_CAM(camera_f, true);
				}
			}
		}
	}
}
namespace insight {
	SuperProjectileConfig grenadeConfig;
	SuperProjectileManager grenadeManager;
	int time_default = 2700;
	int time = 2700;
	std::chrono::steady_clock::time_point attackStartTime;

	void weapon::projectile_grenade(toggle_int_feature* feature, bool& value, int& value2) {
		if (!value) {
			return;
		}
		if (globals::c_local_ped()->m_weapon_manager->m_selected_weapon_hash == 0x93E220BD) {
			if (PAD::IS_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_ATTACK)) {
				if (attackStartTime == std::chrono::steady_clock::time_point()) {
					attackStartTime = std::chrono::steady_clock::now();
				}
			}
			else {
				if (attackStartTime != std::chrono::steady_clock::time_point()) {
					std::chrono::steady_clock::time_point attackEndTime = std::chrono::steady_clock::now();
					std::chrono::milliseconds attackDuration = std::chrono::duration_cast<std::chrono::milliseconds>(attackEndTime - attackStartTime);
					time = time_default - attackDuration.count();
					attackStartTime = std::chrono::steady_clock::time_point();
				}
			}

			grenadeConfig.setObjectType(290600267);
			grenadeConfig.explosionTag = value2;
			grenadeConfig.explode_timing_mode = true;
			grenadeConfig.time = time;
			grenadeManager.setConfig(grenadeConfig);
			grenadeManager.setToggle(true);
			grenadeManager.update();
		}
		else {
			return;
		}
	}
}
namespace insight {
	SuperProjectileConfig molotovConfig;
	SuperProjectileManager molotovManager;

	void weapon::projectile_molotov(toggle_int_feature* feature, bool& value, int& value2) {
		if (!value) {
			return;
		}
		if (globals::c_local_ped()->m_weapon_manager->m_selected_weapon_hash == "weapon_molotov"_joaat) {

			molotovConfig.setObjectType(3414357965);
			molotovConfig.explosionTag = value2;
			molotovConfig.explode_timing_mode = false;
			molotovManager.setConfig(molotovConfig);
			molotovManager.setToggle(true);
			molotovManager.update();
		}
		else {
			return;
		}
	}
}