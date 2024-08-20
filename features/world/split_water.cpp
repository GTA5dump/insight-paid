
#include "cheat/features/features.hpp"
#include "cheat/features/globals.hpp"
#include "cheat/features/tasks.hpp"
#include "cheat/features/features/features_utility.hpp"
#include "util/input/input.hpp"
#include "util/math/math.hpp"
#include "cheat/script/script_utility.hpp"
#include "util/notify/notify.hpp"
namespace insight {
	void world::split_water(toggle_feature* feature, bool& value) {
		if (!value)
			return;
		float offset[] = { -4, 4 };
		for (int i = 0; i < 5; i++) {
			Vector3 current_coords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1);
			if (i < 2) current_coords.x += offset[(i % 2 == 0)];
			else if (i < 4) current_coords.y += offset[(i % 2 == 0)];
			WATER::MODIFY_WATER({ current_coords.x, current_coords.y }, -500000.0f, 0.2f);
		}
	}



	Cam sponner_cam;
	Vector3 calculateDirectionFromRotation(Vector3* rotation)
	{
		float radiansZ = rotation->z * 0.0174532924f;
		float radiansX = rotation->x * 0.0174532924f;

		float num = std::abs((float)std::cos((double)radiansX));
		Vector3 direction;
		direction.x = (float)((double)((float)(-(float)std::sin((double)radiansZ))) * (double)num);
		direction.y = (float)((double)((float)std::cos((double)radiansZ)) * (double)num);
		direction.z = (float)std::sin((double)radiansX);

		return direction;
	}

	Entity raycastGetEntityInFrontOfCamera(bool drawDebugLines, Cam camera, Vector3 cameraRotation, Vector3 startingPosition)
	{
		Vector3 hitPoint, hitPointNormal;
		Entity hitEntity;
		BOOL hasHit;

		Vector3 cameraPosition = startingPosition;
		Vector3 cameraDirection = calculateDirectionFromRotation(&cameraRotation);
		Vector3 rayEndPoint = cameraPosition + (cameraDirection * 10000);
		int rayHandle = SHAPETEST::START_EXPENSIVE_SYNCHRONOUS_SHAPE_TEST_LOS_PROBE(cameraPosition, rayEndPoint, 4294967295, camera, 7);
		int rayResult = SHAPETEST::GET_SHAPE_TEST_RESULT(rayHandle, &hasHit, &hitPoint, &hitPointNormal, &hitEntity);
		if (drawDebugLines)
		{
			GRAPHICS::DRAW_LINE(cameraPosition, rayEndPoint, 255, 0, 0, 255);
		}
		return hitEntity;
	}
	bool was_spawner_spoooner_on = false;
	void destory_spooner_cam()
	{
		if (CAM::DOES_CAM_EXIST(sponner_cam))
		{
			CAM::RENDER_SCRIPT_CAMS(false, true, 700, 1, 1, 1);
			CAM::SET_CAM_ACTIVE(sponner_cam, false);
			CAM::DESTROY_CAM(sponner_cam, true);
			HUD::UNLOCK_MINIMAP_ANGLE();
			HUD::UNLOCK_MINIMAP_POSITION();
		}
	}
	Vector3 spawner_spoooner_rotation;
	void spawner_spoooner_cam_info(Cam camera, Vector3* forward, Vector3* right, Vector3* up) {
		Vector3 rot = CAM::GET_CAM_ROT(camera, 0);
		*forward = vectors::get()->get_cam_direction(rot);
		Vector3 worldRight = Vector3();
		worldRight.z = 1;
		Vector3 worldUp = Vector3();
		worldUp.x = 1;
		*right = vectors::get()->get_vector_cross(*forward, worldRight);
		*up = vectors::get()->get_vector_cross(*forward, worldUp);
	}
	Vector3 spawner_spoooner_cam_info_front;
	Vector3 spawner_spoooner_cam_info_right;
	Vector3 spawner_spoooner_cam_info_up;
	Vector3 target_pos;
	Vector4 cross_rect_color;
	Entity selected_ent;
	void world::spawner_spoooner(toggle_feature* feature, bool& value) {
		if (!value) {
			script_utility::get()->sponner_cam_running = false;
			if (was_spawner_spoooner_on) {
				destory_spooner_cam();
				was_spawner_spoooner_on = false;
			}
			return;
		}
		script_utility::get()->sponner_cam_running = true;
		if (!was_spawner_spoooner_on) {
			notify::send("spawner_spoooner"_tf->m_name,
				globals::is_using_controller() ?
				"Use (LEFT JOYSTICK) to move. For selecting entity use (AIM BUTTON) & For picking entity (ATTACK BUTTON) and (BOX BUTTON) for speed boost"
				:
				"Use (WSAD AND MOUSE) to move. For selecting entity use (RIGHT CLICK) & For picking entity use (LEFT CLICK) and (SPACE) Key for speed boost");

			was_spawner_spoooner_on = true;
		}

		if (!CAM::DOES_CAM_EXIST(sponner_cam)) {
			sponner_cam = CAM::CREATE_CAM("DEFAULT_SCRIPTED_CAMERA", 1);
			CAM::SET_CAM_COORD(sponner_cam, CAM::GET_GAMEPLAY_CAM_COORD());
			CAM::SET_CAM_FOV(sponner_cam, CAM::GET_GAMEPLAY_CAM_FOV());
			CAM::RENDER_SCRIPT_CAMS(true, true, 700, 1, 1, 0);
			CAM::SET_CAM_ACTIVE(sponner_cam, true);
			target_pos = CAM::GET_CAM_COORD(sponner_cam);
		}
		else {
			spawner_spoooner_rotation.x -= PAD::GET_DISABLED_CONTROL_NORMAL(0, (int)ControllerInputs::INPUT_LOOK_UD) * 4;
			spawner_spoooner_rotation.z -= PAD::GET_DISABLED_CONTROL_NORMAL(0, (int)ControllerInputs::INPUT_LOOK_LR) * 4;
			CAM::SET_CAM_ROT(sponner_cam, spawner_spoooner_rotation, 0);
			float Set_speed = 5;
			if (PAD::IS_DISABLED_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_FRONTEND_X))
			{
				Set_speed *= 10;
			}
			Vector3 camCoordZs = CAM::GET_CAM_COORD(sponner_cam);
			HUD::LOCK_MINIMAP_POSITION({ camCoordZs.x,camCoordZs.y });
			HUD::LOCK_MINIMAP_ANGLE(spawner_spoooner_rotation.z);
			if (PAD::IS_DISABLED_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_MOVE_UP_ONLY)) {
				camCoordZs.x += (spawner_spoooner_cam_info_front.x * 0.1 * Set_speed);
				camCoordZs.y += (spawner_spoooner_cam_info_front.y * 0.1 * Set_speed);
				camCoordZs.z += (spawner_spoooner_cam_info_front.z * 0.1 * Set_speed);
			}
			if (PAD::IS_DISABLED_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_MOVE_DOWN_ONLY)) {
				camCoordZs.x -= (spawner_spoooner_cam_info_front.x * 0.1 * Set_speed);
				camCoordZs.y -= (spawner_spoooner_cam_info_front.y * 0.1 * Set_speed);
				camCoordZs.z -= (spawner_spoooner_cam_info_front.z * 0.1 * Set_speed);
			}
			if (PAD::IS_DISABLED_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_MOVE_RIGHT_ONLY)) {
				camCoordZs.x += (spawner_spoooner_cam_info_right.x * 0.1 * Set_speed);
				camCoordZs.y += (spawner_spoooner_cam_info_right.y * 0.1 * Set_speed);
				camCoordZs.z += (spawner_spoooner_cam_info_right.z * 0.1 * Set_speed);
			}
			if (PAD::IS_DISABLED_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_MOVE_LEFT_ONLY)) {
				camCoordZs.x -= (spawner_spoooner_cam_info_right.x * 0.1 * Set_speed);
				camCoordZs.y -= (spawner_spoooner_cam_info_right.y * 0.1 * Set_speed);
				camCoordZs.z -= (spawner_spoooner_cam_info_right.z * 0.1 * Set_speed);
			}
			spawner_spoooner_cam_info(sponner_cam, &spawner_spoooner_cam_info_front, &spawner_spoooner_cam_info_right, &spawner_spoooner_cam_info_up);
			target_pos.x += (camCoordZs.x - target_pos.x) * 0.1;
			target_pos.y += (camCoordZs.y - target_pos.y) * 0.1;
			target_pos.z += (camCoordZs.z - target_pos.z) * 0.1;

			CAM::SET_CAM_COORD(sponner_cam, target_pos);

			CAM::STOP_CUTSCENE_CAM_SHAKING(0);
			PAD::DISABLE_ALL_CONTROL_ACTIONS(0);

			GRAPHICS::DRAW_RECT({ 0.5f, 0.5f }, 0.02f, 0.002f, cross_rect_color.x, cross_rect_color.y, cross_rect_color.z, cross_rect_color.w, 0);
			GRAPHICS::DRAW_RECT({ 0.5f, 0.5f }, 0.001f, 0.03f, cross_rect_color.x, cross_rect_color.y, cross_rect_color.z, cross_rect_color.w, 0);

			auto spawn_n_force_coords = vectors::get()->get_front_camera_coordinates(8, sponner_cam);
			script_utility::get()->sponner_spawn_entity_pos = spawn_n_force_coords;

			Entity aimed_ent = raycastGetEntityInFrontOfCamera(0, sponner_cam, spawner_spoooner_rotation, target_pos);
			if (aimed_ent != 0 && ENTITY::DOES_ENTITY_EXIST(aimed_ent) && ENTITY::IS_ENTITY_ON_SCREEN(aimed_ent)) {
				cross_rect_color = { 0,255,0,255 };
				auto coords = ENTITY::GET_ENTITY_COORDS(aimed_ent, 0);
				GRAPHICS::DRAW_LINE(globals::h_local_ped_pos(), coords, 255, 255, 255, 255);				
				if (PAD::IS_DISABLED_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_AIM)) {
					selected_ent = aimed_ent;
				}
			}
			else {
				cross_rect_color = { 255,0,0,255 };
			}

			if (selected_ent != 0 && ENTITY::DOES_ENTITY_EXIST(selected_ent) && ENTITY::IS_ENTITY_ON_SCREEN(selected_ent)) {
				cross_rect_color = { 0,255,0,255 };
				auto coords = ENTITY::GET_ENTITY_COORDS(selected_ent, 0);
				GRAPHICS::DRAW_LINE(globals::h_local_ped_pos(), coords, 255, 255, 255, 255);
					render::get()->draw_text_coordinates("Selected", coords, 255, 255, 255, 255);
				if (PAD::IS_DISABLED_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_ATTACK) && tasks::request_control(selected_ent)) {
					tasks::apply_force_to_position(selected_ent, spawn_n_force_coords - coords, ENTITY::GET_ENTITY_VELOCITY(selected_ent), 0.8f, 0.2);
				} 
			}
			else {
				selected_ent = 0;
			}
		}


	}
}
