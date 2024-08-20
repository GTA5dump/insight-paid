#include "cheat/features/features.hpp"
#include "cheat/features/globals.hpp"
#include "cheat/features/tasks.hpp"
#include "cheat/features/features/features_utility.hpp"
#include "util/input/input.hpp"
#include "util/math/math.hpp"
#include "util/notify/notify.hpp"

namespace insight {
	void features_utility::create_machine_sentry(Vector3 placement) {
		Hash H_MC = "hei_prop_carrier_defense_02"_joaat;
		tasks::request_model(H_MC);
		Object obj = OBJECT::CREATE_OBJECT(H_MC, placement, globals::in_multiplayer(), 0, 1);
		OBJECT::PLACE_OBJECT_ON_GROUND_OR_OBJECT_PROPERLY(obj);
		features_utility::get()->sentry_guns.push_back(obj);
		features_utility::get()->sentry_guns_dat.push_back(gun_data(true,false));
	}
	void features_utility::create_missle_sentry(Vector3 placement) {
		Hash H_MM = "hei_prop_carrier_defense_01"_joaat;
		tasks::request_model(H_MM);
		Object obj = OBJECT::CREATE_OBJECT(H_MM, placement, globals::in_multiplayer(), 0, 1);
		OBJECT::PLACE_OBJECT_ON_GROUND_OR_OBJECT_PROPERLY(obj);
		features_utility::get()->sentry_missles.push_back(missle_data(obj, timer(std::chrono::seconds(3s)), timer(std::chrono::milliseconds(50ms)),0,6,false,0,true,true));
	}
}
namespace insight {
	Entity sentry_weapon_controller_ent = 0;
	Cam sentry_weapon_controller_cam = 0;
	void sentry_weapon_controller_reset_cam() {
		if (CAM::DOES_CAM_EXIST(sentry_weapon_controller_cam)) {
			CAM::RENDER_SCRIPT_CAMS(false, true, 800, 1, 1, 1);
			CAM::SET_CAM_ACTIVE(sentry_weapon_controller_cam, false);
			CAM::DESTROY_CAM(sentry_weapon_controller_cam, true);
			sentry_weapon_controller_cam = 0;
		}
	}
	void sentry_weapon_controller_set(int ent) {
		if (sentry_weapon_controller_ent) {
			if (PAD::IS_DISABLED_CONTROL_JUST_PRESSED(0, (int)ControllerInputs::INPUT_ENTER)) {
				sentry_weapon_controller_ent = 0;
				sentry_weapon_controller_reset_cam();
			}
		}
		else {
			if (PAD::IS_DISABLED_CONTROL_JUST_PRESSED(0, (int)ControllerInputs::INPUT_ENTER)) {
				if (SYSTEM::VDIST(globals::h_local_ped_pos(), ENTITY::GET_ENTITY_COORDS(ent, 0)) < 3.f) {
					sentry_weapon_controller_ent = ent;
				}
			}
		}
	}
	features_utility::missle_data sentry_weapon_controller_data = { sentry_weapon_controller_ent, timer(std::chrono::seconds(3s)), timer(std::chrono::milliseconds(50ms)), 0, false, 0, true, true ,true};
	bool was_sentry_conon = false;
	void sentry_weapon_controller() {
		if (sentry_weapon_controller_ent) {
			was_sentry_conon = true;
			ENTITY::FREEZE_ENTITY_POSITION(globals::h_local_ped(), true);
			if (!CAM::DOES_CAM_EXIST(sentry_weapon_controller_cam)) {
				sentry_weapon_controller_cam = CAM::CREATE_CAM("DEFAULT_SCRIPTED_CAMERA", 1);
				CAM::SET_CAM_COORD(sentry_weapon_controller_cam, ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(sentry_weapon_controller_ent, Vector3(0, 10, 2)));
				CAM::SET_CAM_FOV(sentry_weapon_controller_cam, 50);
				CAM::RENDER_SCRIPT_CAMS(true, true, 700, 1, 1, 0);
				CAM::SET_CAM_ACTIVE(sentry_weapon_controller_cam, true);
			}
			else {
				float x, y;
				GRAPHICS::GET_SCREEN_COORD_FROM_WORLD_COORD(vectors::get()->get_front_camera_coordinates_local(100), &x, &y);
				GRAPHICS::DRAW_SPRITE("commonmenu", "common_medal", Vector2(x, y), 0.015f, 0.02f, 0, 255, 255, 255, 255, 1, 1);
				Vector3 cam_rot = CAM::GET_GAMEPLAY_CAM_ROT(2);
				CAM::SET_CAM_ROT(sentry_weapon_controller_cam, cam_rot, 2);
				CAM::SET_CAM_COORD(sentry_weapon_controller_cam, ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(sentry_weapon_controller_ent, Vector3(0, -2.f, 2.5f)));
				cam_rot.z = cam_rot.z + 180;
				ENTITY::SET_ENTITY_ROTATION(sentry_weapon_controller_ent, cam_rot.x, cam_rot.y, cam_rot.z, 2, 0);

				if (PAD::IS_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_ATTACK)) {
					if (ENTITY::GET_ENTITY_MODEL(sentry_weapon_controller_ent) == "hei_prop_carrier_defense_02"_joaat) {
						Vector3 shootpos = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(sentry_weapon_controller_ent, Vector3(0, -2.f, 2.5f));
						Vector3 shootat = vectors::get()->get_front_camera_coordinates_local(100);
						AUDIO::PLAY_SOUND_FROM_COORD(1, xorstr_("Drill_Pin_Break"), shootpos, xorstr_("DLC_HEIST_FLEECA_SOUNDSET"), true, 10, false);
						MISC::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(shootpos, shootat, 999.f, 0, "VEHICLE_WEAPON_TURRET_INSURGENT"_joaat,
							NULL, true, false, 999);
					}
					else {

						Vector3 shootpos = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(sentry_weapon_controller_ent, Vector3(0, -2.5f, 2.5f));
						Vector3 shootat = vectors::get()->get_front_camera_coordinates_local(100);
						if (sentry_weapon_controller_data.tick.update()) {
							sentry_weapon_controller_data.shoot_mode = true;
						}
						if (sentry_weapon_controller_data.shoot_mode) {
							if (sentry_weapon_controller_data.missle_tick.update()) {
								if (sentry_weapon_controller_data.missle_cout > sentry_weapon_controller_data.num_missle) {
									sentry_weapon_controller_data.shoot_mode = false;
								}
								AUDIO::PLAY_SOUND_FROM_COORD(1, xorstr_("Fire"), shootpos, xorstr_("DLC_BTL_Terrobyte_Turret_Sounds"), true, 10, false);
								MISC::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(shootpos, shootat, 999.f, 0, "VEHICLE_WEAPON_SPACE_ROCKET"_joaat,
									NULL, true, false, 9999);
								sentry_weapon_controller_data.missle_cout++;
							}
						}
						else
						{
							sentry_weapon_controller_data.missle_cout = 0;
						}

					}

				}
			}
		}
	}
	bool was_sentry_weapon_on = false;
	bool is_a_friend = false;
	void world::sentry_weapon(toggle_feature* feature, bool& value) {
		if (!features_utility::get()->sentry_guns.size() && !features_utility::get()->sentry_missles.size()) {
			return;
		}
		sentry_weapon_controller();
		if (was_sentry_conon) {
			ENTITY::FREEZE_ENTITY_POSITION(globals::h_local_ped(), false);
			was_sentry_conon = false;
		}
		for (size_t i = 0; i < features_utility::get()->sentry_guns.size(); i++) {
			Entity ent = features_utility::get()->sentry_guns[i];
			sentry_weapon_controller_set(features_utility::get()->sentry_guns[i]);
			if (sentry_weapon_controller_ent != features_utility::get()->sentry_guns[i]) {
				Vector3 cord = ENTITY::GET_ENTITY_COORDS(ent, 0);
				Entity closed;
				closed = tasks::get_random_ped_w_clearsight(ent, std::vector<int>(globals::h_local_ped()));
				if (features_utility::get()->sentry_guns_dat[i].no_players_shooting) {
					if (PED::IS_PED_A_PLAYER(closed)) {
						is_a_friend = true;
					}
				}
				else is_a_friend = false;
				bool shoot = closed && !is_a_friend || PED::IS_PED_A_PLAYER(closed);
				if (shoot) {
					if (features_utility::get()->sentry_guns_dat[i].shooting) {
						float yaw = vectors::get()->PointToPointYaw(cord, ENTITY::GET_ENTITY_COORDS(closed, 0)) + 90.0f;
						ENTITY::SET_ENTITY_ROTATION(ent, 0, 0, yaw, 2, 0);
						Vector3 shootpos = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(ent, Vector3(0, -2.f, 2.5f));
						AUDIO::PLAY_SOUND_FROM_COORD(1, xorstr_("Drill_Pin_Break"), shootpos, xorstr_("DLC_HEIST_FLEECA_SOUNDSET"), true, 10, false);
						MISC::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(shootpos, ENTITY::GET_ENTITY_COORDS(closed, 0), 999.f, 0, "VEHICLE_WEAPON_TURRET_INSURGENT"_joaat,
							NULL, true, false, 999);
					}
				}
			}
		}
		for (size_t i = 0; i < features_utility::get()->sentry_missles.size(); i++) {
			Entity ent = features_utility::get()->sentry_missles[i].entity;
			sentry_weapon_controller_set(ent);
			if (sentry_weapon_controller_ent != features_utility::get()->sentry_missles[i].entity) {
				Vector3 cord = ENTITY::GET_ENTITY_COORDS(ent, 0);
				Entity closed;
				if (features_utility::get()->sentry_missles[i].ground_targets && features_utility::get()->sentry_missles[i].sky_targets)
					closed = tasks::get_random_vehicle_w_clearsight(ent, std::vector<int>(globals::h_local_ped()));
				else
					if (features_utility::get()->sentry_missles[i].ground_targets)
						closed = tasks::get_random_ground_vehicle_w_clearsight(ent, std::vector<int>(globals::h_local_ped()));
					else
						if (features_utility::get()->sentry_missles[i].sky_targets)
							closed = tasks::get_random_air_vehicle_w_clearsight(ent, std::vector<int>(globals::h_local_ped()));

				if (closed) {
					if (features_utility::get()->get()->sentry_missles[i].shooting) {
						float yaw = vectors::get()->PointToPointYaw(cord, ENTITY::GET_ENTITY_COORDS(closed, 0)) + 90.0f;
						ENTITY::SET_ENTITY_ROTATION(ent, 0, 0, yaw, 2, 0);
						Vector3 shootpos = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(ent, Vector3(0, -2.2f, 2.5f));
						//	GRAPHICS::DRAW_LINE(shootpos, ENTITY::GET_ENTITY_COORDS(closed, 0), 255, 0, 0, 255);			
						if (features_utility::get()->get()->sentry_missles[i].tick.update()) {
							features_utility::get()->sentry_missles[i].shoot_mode = true;
						}
						if (features_utility::get()->sentry_missles[i].shoot_mode) {
							if (features_utility::get()->sentry_missles[i].missle_tick.update()) {
								if (features_utility::get()->sentry_missles[i].missle_cout > features_utility::get()->sentry_missles[i].num_missle) {
									features_utility::get()->sentry_missles[i].shoot_mode = false;
								}
								AUDIO::PLAY_SOUND_FROM_COORD(1, xorstr_("Fire"), shootpos, xorstr_("DLC_BTL_Terrobyte_Turret_Sounds"), true, 10, false);
								MISC::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(shootpos, ENTITY::GET_ENTITY_COORDS(closed, 0), 999.f, 0, "VEHICLE_WEAPON_SPACE_ROCKET"_joaat,
									NULL, true, false, 9999);
								features_utility::get()->sentry_missles[i].missle_cout++;
							}
						}
						else
						{
							features_utility::get()->sentry_missles[i].missle_cout = 0;
						}
					}
				}
			}
		}
	}
}