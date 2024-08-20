#include "cheat/features/tasks.hpp"
#include "cheat/features/features.hpp"
#include "cheat/render/render.hpp"
#include "util/input/input.hpp"
#include "util/math/math.hpp"
#include "util/script/fiber_pool.hpp"
#include "cheat/render/renderer.hpp"
namespace insight {
	Cam teleport_animation_cam = 0;
	bool teleport_animation_ignore_toggle = true;
	void tasks::teleport_animation(bool toggle, bool ignoretoggle) {
		if (toggle) {
			int ease_time = "teleport_settings_animation_ease_out"_FF->m_value.floating_point;
			if (ignoretoggle ? teleport_animation_ignore_toggle : "teleport_settings_animation"_tf->m_value.toggle) {
				if (!CAM::DOES_CAM_EXIST(teleport_animation_cam)) {
					teleport_animation_cam = CAM::CREATE_CAM("DEFAULT_SCRIPTED_CAMERA", 1);
					CAM::SET_CAM_COORD(teleport_animation_cam, CAM::GET_GAMEPLAY_CAM_COORD());
					CAM::SET_CAM_FOV(teleport_animation_cam, CAM::GET_GAMEPLAY_CAM_FOV());
					CAM::SET_CAM_ROT(teleport_animation_cam, CAM::GET_GAMEPLAY_CAM_ROT(0), 0);
					CAM::RENDER_SCRIPT_CAMS(true, false, 0, 1, 1, 0);
					CAM::SET_CAM_ACTIVE(teleport_animation_cam, true);
					script::get_current()->yield(std::chrono::milliseconds(50));

				}
			}
		}
		else
		{
			int ease_time = "teleport_settings_animation_ease_out"_FF->m_value.floating_point;
			if (ignoretoggle ? teleport_animation_ignore_toggle : "teleport_settings_animation"_tf->m_value.toggle) {
				if (CAM::DOES_CAM_EXIST(teleport_animation_cam)) {
					CAM::RENDER_SCRIPT_CAMS(false, true, ease_time, 1, 1, 1);
					CAM::SET_CAM_ACTIVE(teleport_animation_cam, false);
					CAM::DESTROY_CAM(teleport_animation_cam, true);
					//	script::get_current()->yield(std::chrono::milliseconds(ease_time));

				}
			}
		}

	}

	void tasks::disable_kill_screen(bool toggle) {
		if (toggle) {
			GRAPHICS::ANIMPOSTFX_STOP_ALL();
			HUD::DISPLAY_RADAR(true);
			HUD::DISPLAY_HUD(true);
			AUDIO::BLOCK_DEATH_JINGLE(true);
			AUDIO::STOP_AUDIO_SCENE("MP_LEADERBOARD_SCENE");
			AUDIO::STOP_AUDIO_SCENE("MP_MISSION_NAME_SCENE");
		}
	}
	Ped customSpawn(ePedType pedType, Hash hash, Hash clone, Vector3 location, float heading, bool is_networked = true) {
		for (uint8_t i = 0; !STREAMING::HAS_MODEL_LOADED(hash) && i < 100; i++)
		{
			STREAMING::REQUEST_MODEL(hash);
			script::get_current()->yield();
		}

		if (!STREAMING::HAS_MODEL_LOADED(hash))
		{
			return 0;
		}

		auto ped = PED::CREATE_PED(pedType, hash, location, heading, is_networked, false);

		script::get_current()->yield();

		if (clone)
		{
			PED::CLONE_PED_TO_TARGET(clone, ped);
		}

		STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(hash);

		return ped;
	}
	void tasks::el_crash(int i) {
		for (int i = 0; i < 5; ++i) {
			g_fiber_pool->queue_job([=] {
				std::vector<int> ped(10);

				for (int i = 0; i < 10; ++i) {
					Hash mdl = rage::joaat("cs_taostranslator2");
					while (!STREAMING::HAS_MODEL_LOADED(mdl)) {
						STREAMING::REQUEST_MODEL(mdl);
						script::get_current()->yield();
					}
					tasks::request_model(mdl);

					Ped player_ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i);
					Vector3 coords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(player_ped, { 0.0, -1.0, 0.0 + 0.1 }); // or 0.3, 0.2, or 0.1
					ped[i] = customSpawn(PED_TYPE_PROSTITUTE, mdl, 0, coords, 0.0f);
					WEAPON::GIVE_DELAYED_WEAPON_TO_PED(ped[i], 0xB1CA77B1, 0, true);
					WEAPON::SET_PED_GADGET(ped[i], 0xB1CA77B1, true);

					ENTITY::SET_ENTITY_VISIBLE(ped[i], true, 0);
					script::get_current()->yield(25ms);
				}

				script::get_current()->yield(2500ms);
				for (int i = 0; i < 10; ++i) {
					tasks::delete_entity(ped[i]);
					script::get_current()->yield(25ms);
				}
				});
		}
	}
	void tasks::draw_esp_box(int ped, int r, int g, int b, int a, Player i)
	{
		float x, y;
		Vector3 v0, v1;
		Vector3 coords0from = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(ped, Vector3(-(v1.x + 0.3f), v1.y - 0.3f, -0.9f));
		Vector3 coords0to = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(ped, Vector3(-(v1.x + 0.3f), v1.y + 0.3f, -0.9f));
		Vector3 coords1from = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(ped, Vector3(+(v1.x + 0.3f), v1.y - 0.3f, -0.9f));
		Vector3 coords1to = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(ped, Vector3(+(v1.x + 0.3f), v1.y + 0.3f, -0.9f));
		Vector3 coords2from = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(ped, Vector3(v1.x + -0.3f, +(v1.y + 0.3f), -0.9f));
		Vector3 coords2to = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(ped, Vector3(v1.x + 0.3f, +(v1.y + 0.3f), -0.9f));
		Vector3 coords3from = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(ped, Vector3(v1.x + -0.3f, -(v1.y + 0.3f), -0.9f));
		Vector3 coords3to = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(ped, Vector3(v1.x + 0.3f, -(v1.y + 0.3f), -0.9f));
		Vector3 coords4from = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(ped, Vector3(-(v1.x + 0.3f), v1.y - 0.3f, 0.9f));
		Vector3 coords4to = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(ped, Vector3(-(v1.x + 0.3f), v1.y + 0.3f, 0.9f));
		Vector3 coords5from = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(ped, Vector3(+(v1.x + 0.3f), v1.y - 0.3f, 0.9f));
		Vector3 coords5to = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(ped, Vector3(+(v1.x + 0.3f), v1.y + 0.3f, 0.9f));
		Vector3 coords6from = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(ped, Vector3(v1.x + -0.3f, +(v1.y + 0.3f), 0.9f));
		Vector3 coords6to = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(ped, Vector3(v1.x + 0.3f, +(v1.y + 0.3f), 0.9f));
		Vector3 coords7from = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(ped, Vector3(v1.x + -0.3f, -(v1.y + 0.3f), 0.9f));
		Vector3 coords7to = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(ped, Vector3(v1.x + 0.3f, -(v1.y + 0.3f), 0.9f));
		Vector3 coords8from = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(ped, Vector3(v1.x + 0.3f, -(v1.y + 0.3f), -0.9f));
		Vector3 coords8to = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(ped, Vector3(v1.x + 0.3f, -(v1.y + 0.3f), 0.9f));
		Vector3 coords9from = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(ped, Vector3(v1.x + -0.3f, -(v1.y + -0.3f), -0.9f));
		Vector3 coords9to = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(ped, Vector3(v1.x + -0.3f, -(v1.y + -0.3f), 0.9f));
		Vector3 coords10from = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(ped, Vector3(v1.x + -0.3f, +(v1.y + -0.3f), -0.9f));
		Vector3 coords10to = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(ped, Vector3(v1.x + -0.3f, +(v1.y + -0.3f), 0.9f));
		Vector3 coords11from = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(ped, Vector3(v1.x + 0.3f, +(v1.y + 0.3f), -0.9f));
		Vector3 coords11to = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(ped, Vector3(v1.x + 0.3f, +(v1.y + 0.3f), 0.9f));
		GRAPHICS::DRAW_LINE(coords0from, coords0to, r,g,b,a);
		GRAPHICS::DRAW_LINE(coords1from, coords1to, r,g,b,a);
		GRAPHICS::DRAW_LINE(coords2from, coords2to, r,g,b,a);
		GRAPHICS::DRAW_LINE(coords3from, coords3to, r,g,b,a);
		GRAPHICS::DRAW_LINE(coords4from, coords4to, r,g,b,a);
		GRAPHICS::DRAW_LINE(coords5from, coords5to, r,g,b,a);
		GRAPHICS::DRAW_LINE(coords6from, coords6to, r,g,b,a);
		GRAPHICS::DRAW_LINE(coords7from, coords7to, r,g,b,a);
		GRAPHICS::DRAW_LINE(coords8from, coords8to,  r,g,b,a);
		GRAPHICS::DRAW_LINE(coords9from, coords9to,  r,g,b,a);
		GRAPHICS::DRAW_LINE(coords10from, coords10to, r,g,b,a);
		GRAPHICS::DRAW_LINE(coords11from, coords11to, r,g,b,a);
	}
	void tasks::draw_esp_line(int ped, int r, int g, int b, int a)
	{
		GRAPHICS::DRAW_LINE(globals::h_local_ped_pos(), ENTITY::GET_ENTITY_COORDS(ped, 0), r, g, b, a);
	}
	void tasks::draw_esp_name(int ped, int r, int g, int b, int a, const char* text)
	{
		render::get()->draw_text_coordinates(text,
			ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(ped, Vector3(0, 0, 1.f)),
			r, g, b, a);
	}

	void tasks::draw_marker(eMarkerType marker, Vector3 pos, float radius, int red, int green, int blue, int alpha, bool move_updown, bool lookatyou, bool rotation, bool draw_on_entity, Vector3 dir, Vector3 rot)
	{
		GRAPHICS::DRAW_MARKER((int)marker, pos, dir, rot, Vector3(radius, radius, radius), red, green, blue, alpha, move_updown, lookatyou, 0, rotation, NULL, NULL, draw_on_entity);
	}
	void tasks::draw_marker(eMarkerType marker, Vector3 pos, Vector3 radius, int red, int green, int blue, int alpha, bool move_updown, bool lookatyou, bool rotation, bool draw_on_entity, Vector3 dir, Vector3 rot)
	{
		GRAPHICS::DRAW_MARKER((int)marker, pos, dir, rot, radius, red, green, blue, alpha, move_updown, lookatyou, 0, rotation, NULL, NULL, draw_on_entity);
	}

	void tasks::play_animation_tick(Ped ped, const char* anim, const char* animid, int flag)
	{
		if (!ENTITY::IS_ENTITY_PLAYING_ANIM(ped, anim, animid, 3))
		{

			if (STREAMING::HAS_ANIM_DICT_LOADED((anim)))
			{

				TASK::TASK_PLAY_ANIM(ped, anim, animid, 8.00, 8.00, -1, flag, 0, TRUE, TRUE, FALSE);
			}
			else
			{
				STREAMING::REQUEST_ANIM_DICT(anim);
			}
		}
	}

	void tasks::play_animation_with_settings(Ped ped, const char* anim, const char* animid, float blendInSpeed, float blendOutSpeed, int duration, int flag, float playbackRate, BOOL lockX, BOOL lockY, BOOL lockZ)
	{
		if (!ENTITY::IS_ENTITY_PLAYING_ANIM(ped, anim, animid, 3))
		{
			if (STREAMING::HAS_ANIM_DICT_LOADED((anim)))
			{

				TASK::TASK_PLAY_ANIM(ped, anim, animid, blendInSpeed, blendOutSpeed, duration, flag, playbackRate, lockX, lockY, lockZ);
			}
			else
			{
				STREAMING::REQUEST_ANIM_DICT(anim);
			}
		}
	}
	void tasks::play_animation_adv_with_settings(Ped ped, const char* anim, const char* animid, float enterspeed, float exit_speed, int duration, int flag, float time)
	{
		if (!ENTITY::IS_ENTITY_PLAYING_ANIM(ped, anim, animid, 3))
		{
			if (STREAMING::HAS_ANIM_DICT_LOADED((anim)))
			{

				TASK::TASK_PLAY_ANIM_ADVANCED(ped, anim, animid, { 0,0,0 }, {0,0,0}, enterspeed, exit_speed, duration, flag, time,0, 0);
			}
			else
			{
				STREAMING::REQUEST_ANIM_DICT(anim);
			}
		}
	}

	std::vector<int> tick_checker(1000);
	void tasks::play_ptfx_bone_tick(int entity, int entityBone, const char* particleAsset, const char* particleFX, const char* fxName, float scale, bool useColor, float red, float green, float blue,Vector3 rot)
	{
		if (!GRAPHICS::DOES_PARTICLE_FX_LOOPED_EXIST(tick_checker[entityBone])) {
			STREAMING::REQUEST_NAMED_PTFX_ASSET(particleAsset);
			if (STREAMING::HAS_NAMED_PTFX_ASSET_LOADED(particleAsset)) {
				GRAPHICS::USE_PARTICLE_FX_ASSET(particleFX);
				Vector3 NULL_VEC = { 0,0,0 };
				tick_checker[entityBone] = GRAPHICS::START_PARTICLE_FX_NON_LOOPED_ON_ENTITY_BONE(fxName, entity, NULL_VEC, rot, entityBone, scale, true, true, true);
				if (useColor) {
					GRAPHICS::SET_PARTICLE_FX_NON_LOOPED_COLOUR(red / 255, green / 255, blue / 255);
				}
			}
			STREAMING::REMOVE_PTFX_ASSET();
		}
		else {
			GRAPHICS::STOP_PARTICLE_FX_LOOPED(tick_checker[entityBone], 0);
		}
	}
	void tasks::play_ptfx_bone_woffsets_tick(int entity, int entityBone, const char* particleAsset, const char* particleFX, const char* fxName, float scale, Vector3 offset, Vector3 rot, bool useColor, float red, float green, float blue)
	{
		if (!GRAPHICS::DOES_PARTICLE_FX_LOOPED_EXIST(tick_checker[entityBone])) {
			while (!STREAMING::HAS_NAMED_PTFX_ASSET_LOADED(particleAsset)) {
				STREAMING::REQUEST_NAMED_PTFX_ASSET(particleAsset);
				script::get_current()->yield();
			}
			GRAPHICS::USE_PARTICLE_FX_ASSET(particleFX);
			tick_checker[entityBone] = GRAPHICS::START_PARTICLE_FX_NON_LOOPED_ON_ENTITY_BONE(fxName, entity, offset, rot, entityBone, scale, true, true, true);
			if (useColor) {
				GRAPHICS::SET_PARTICLE_FX_NON_LOOPED_COLOUR(red / 255, green / 255, blue / 255);
			}
		}
	}

	void tasks::play_ptfx_on_ped_bone(int ped, const char* bone, int ptfx, float scale, bool useColor, float red, float green, float blue) {
		int boneindex = ENTITY::GET_ENTITY_BONE_INDEX_BY_NAME(ped, bone);
		tasks::play_ptfx_bone_woffsets_tick(ped, boneindex, particles[ptfx].dict, particles[ptfx].dict, particles[ptfx].texture, scale, Vector3(0, 0, 0), Vector3(0, 0, 0), useColor, red, green,blue);
	}

	void tasks::play_ptfx_on_ped_bone(int ped, int boneindex, int ptfx, float scale, bool useColor, float red, float green, float blue) {
		tasks::play_ptfx_bone_woffsets_tick(ped, boneindex, particles[ptfx].dict, particles[ptfx].dict, particles[ptfx].texture, scale, Vector3(0, 0, 0), Vector3(0, 0, 0), useColor, red, green, blue);
	}

	void tasks::play_ptfx_on_coordinates(const char* dict, const char* texture, Vector3 coords, float size, Vector3 dir) {
		while (!STREAMING::HAS_NAMED_PTFX_ASSET_LOADED(dict)) {
			STREAMING::REQUEST_NAMED_PTFX_ASSET(dict);
			script::get_current()->yield();
		}
		GRAPHICS::USE_PARTICLE_FX_ASSET(dict);
		GRAPHICS::START_NETWORKED_PARTICLE_FX_NON_LOOPED_AT_COORD(texture, coords, dir, size, 1, 1, 1, 1);
	}

	void tasks::change_model(Hash hash)
	{
		if (!STREAMING::IS_MODEL_IN_CDIMAGE(hash))
		{
			return;
		}
		while (!STREAMING::HAS_MODEL_LOADED(hash))
		{
			STREAMING::REQUEST_MODEL(hash);
			script::get_current()->yield();
		}
		PLAYER::SET_PLAYER_MODEL(globals::player_id, hash);

		PED::SET_PED_DEFAULT_COMPONENT_VARIATION(globals::h_local_ped());

		STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(hash);
	}

	ped_outfit_data tasks::get_ped_outfit_data(Ped ped, int componentId) {

		ped_outfit_data data;
		data.variation = PED::GET_PED_TEXTURE_VARIATION(ped, componentId);
		data.texture_id = PED::GET_PED_DRAWABLE_VARIATION(ped, componentId);
		data.number_of_variations = PED::GET_NUMBER_OF_PED_TEXTURE_VARIATIONS(ped, componentId, data.texture_id);
		data.number_of_textures = PED::GET_NUMBER_OF_PED_DRAWABLE_VARIATIONS(ped, componentId);
		return data;
	}
	ped_outfit_data tasks::get_ped_outfit_prop_data(Ped ped, int componentId) {
		ped_outfit_data data;
		data.variation = PED::GET_PED_PROP_TEXTURE_INDEX(ped, componentId);
		data.texture_id = PED::GET_PED_PROP_INDEX(ped, componentId);
		data.number_of_variations = 255;
		data.number_of_textures = PED::GET_NUMBER_OF_PED_PROP_DRAWABLE_VARIATIONS(ped, componentId);
		return data;
	}

	Blip tasks::add_blip_entity(int icon, int color, Entity entity)
	{
		Blip blip = HUD::ADD_BLIP_FOR_ENTITY(entity);
		HUD::SET_BLIP_DISPLAY(blip, 8);
		HUD::SET_BLIP_SPRITE(blip, icon);
		HUD::SET_BLIP_COLOUR(blip, color);
		return blip;
	}
	Blip tasks::add_blip_coords(int icon, int color, Vector3 coordinates)
	{
		Blip blip = HUD::ADD_BLIP_FOR_COORD(coordinates);
		HUD::SET_BLIP_DISPLAY(blip, 8);
		HUD::SET_BLIP_SPRITE(blip, icon);
		HUD::SET_BLIP_COLOUR(blip, color);
		return blip;
	}

	void tasks::ped_walkable_no_clip(float speed)
	{
		Vector3 camera_direction = vectors::get()->get_direction();
		float speed2 = speed;
		if (input::is_pressed(true, VK_LSHIFT)) {
			speed2 *= 3.f;
		}
		Entity target = !PED::IS_PED_IN_ANY_VEHICLE(globals::h_local_ped(), false) ? globals::h_local_ped() : globals::h_local_vehicle();
		Vector3 position = ENTITY::GET_ENTITY_COORDS(target, false);
		if (ENTITY::IS_ENTITY_A_PED(target))
			CAM::SET_FOLLOW_PED_CAM_VIEW_MODE(2);
		else
			CAM::SET_FOLLOW_VEHICLE_CAM_ZOOM_LEVEL(2);

		ENTITY::FREEZE_ENTITY_POSITION(target, true);

		Vector3 rotation = CAM::GET_GAMEPLAY_CAM_ROT(0);
		ENTITY::SET_ENTITY_ROTATION(target, rotation.x, rotation.y, rotation.z, 2, true);

		if (PAD::IS_DISABLED_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_MOVE_UP_ONLY))
		{
			ENTITY::SET_ENTITY_COORDS_NO_OFFSET(target, position + (camera_direction * speed2), true, true, true);
		}
		else if (PAD::IS_DISABLED_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_MOVE_DOWN_ONLY))
		{
			ENTITY::SET_ENTITY_COORDS_NO_OFFSET(target, position - (camera_direction * speed2), true, true, true);
		}
	}
	void tasks::strike_meteor(int player, int type)
	{
		Object Creat_meteor;
		int metero_timer = 0;
		const char* meteor_list[3] = { ("prop_rock_4_big"),("prop_rock_4_big2"),("prop_asteroid_01") };
		Player playerr = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player);
		Vector3 Coordi = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player), 0);
		const auto pos = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(playerr, Vector3(MISC::GET_RANDOM_FLOAT_IN_RANGE(0.f, 20.f), MISC::GET_RANDOM_FLOAT_IN_RANGE(0.f, 20.f), 50.f));
		Hash meteor = rage::joaat(meteor_list[type]);
		LOG(INFO) << meteor;
		if (!STREAMING::IS_MODEL_VALID(meteor)) {
			return;
		}
		tasks::request_model(meteor);
		if (STREAMING::HAS_MODEL_LOADED(meteor))
		{
			Creat_meteor = OBJECT::CREATE_OBJECT(meteor, pos, true, 0, TRUE);
			if (globals::in_multiplayer())
			{
				DECORATOR::DECOR_SET_INT(Creat_meteor, xorstr_("MPBitset"), 0);
				ENTITY::SET_ENTITY_SHOULD_FREEZE_WAITING_ON_COLLISION(Creat_meteor, TRUE);
				auto networkId = NETWORK::OBJ_TO_NET(Creat_meteor);
				if (NETWORK::NETWORK_GET_ENTITY_IS_NETWORKED(Creat_meteor))
					NETWORK::SET_NETWORK_ID_EXISTS_ON_ALL_MACHINES(networkId, true);
			}
			while (metero_timer != 100)
			{
				if (ENTITY::DOES_ENTITY_EXIST(Creat_meteor)) {
					tasks::play_ptfx_bone_tick(Creat_meteor, 0, xorstr_("scr_agencyheistb"), xorstr_("scr_agencyheistb"), xorstr_("scr_agency3b_heli_expl"), 1.f * type, false, 0.f, 0.f, 0.f);
					Vector3 meteore = ENTITY::GET_ENTITY_COORDS(Creat_meteor, 0);
					FIRE::ADD_EXPLOSION(meteore, 29, 100, false, true, 1, false);
					Vector3 results = Coordi - meteore;
					Vector3 results_Vec = ENTITY::GET_ENTITY_VELOCITY(Creat_meteor);
					tasks::apply_force_to_position(Creat_meteor, results, results_Vec, 3.5 * 3, 0.3);
					metero_timer++;
					script::get_current()->yield();
				}
				else return;

			}
			if (ENTITY::DOES_ENTITY_EXIST(Creat_meteor)) {
				ENTITY::SET_ENTITY_AS_NO_LONGER_NEEDED(&Creat_meteor);
				STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(meteor);
				Vector3 meteore = ENTITY::GET_ENTITY_COORDS(Creat_meteor, 0);
				FIRE::ADD_EXPLOSION(meteore, 29, 100, true, true, 1, false);
			}
		}

	}
	
	float tasks::get_vector_length(Vector3 vector)
	{
		float length = std::sqrt(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z);
		return length;
	}
	float tasks::get_model_length(Hash model)
	{
		Vector3 front, back;
		MISC::GET_MODEL_DIMENSIONS(model, &front, &back);
		float length = get_vector_length(front - back);
		return length;
	}
	const char* weather_type[] = {
		"clear", "clearing", "clouds", "extrasunny", "foggy", "halloween", "neutral", "overcast", "rain", "smog", "snow", "snowlight", "Blizzard", "thunder"
	};

	std::string cloud_hats[] = {
	"Cloudy 01",
	"RAIN",
	"Horizon",
	"horizonband1",
	"horizonband2",
	"horizonband3",
	"Puffs",
	"Wispy",
	"Stormy 01",
	"Clear 01",
	"Snowy 01",
	"Contrails",
	"altostratus",
	"Nimbus",
	"Cirrus",
	"cirrocumulus",
	"stratocumulus",
	"Stripey",
	"horsey",
	"shower"
	};

	void tasks::transition_weather(int id, float time) {
		MISC::SET_WEATHER_TYPE_OVERTIME_PERSIST(weather_type[id], time);
	}

	void tasks::transition_cloud(int id, float time) {
		MISC::SET_CLOUDS_ALPHA(time);
		MISC::LOAD_CLOUD_HAT(cloud_hats[id].c_str(), time);
	}
	void tasks::nuke_x(Vector3 pos)
	{
		for (int i = 0; i < 10; i++)
		{
			if (i < 3)
			{
				Vector3 nuke_cord = vectors::get()->get_360_vec_around_coord(pos, 25, i * 5, 20);
				FIRE::ADD_EXPLOSION(nuke_cord, (int)eExplosionTag::EXP_TAG_SUBMARINE_BIG, 1.0f, true, true, 1.0, false);
				tasks::get()->play_ptfx_on_coordinates("scr_xm_orbital", "scr_xm_orbital_blast", nuke_cord, 2.0f);
			}
			else if (i < 10 && i > 7)
			{
				Vector3 nuke_cord = vectors::get()->get_360_vec_around_coord(pos, 25, i * 5, 20);
				FIRE::ADD_EXPLOSION(nuke_cord, (int)eExplosionTag::EXP_TAG_SUBMARINE_BIG, 1.0f, true, true, 1.0, false);
				tasks::get()->play_ptfx_on_coordinates("scr_xm_orbital", "scr_xm_orbital_blast", nuke_cord, 2.0f);
			}
			else
			{
				Vector3 nuke_cord = vectors::get()->get_360_vec_around_coord(pos, 10, i * 5, 20);
				FIRE::ADD_EXPLOSION(nuke_cord, (int)eExplosionTag::EXP_TAG_SUBMARINE_BIG, 1.0f, true, true, 1.0, false);
				tasks::get()->play_ptfx_on_coordinates("scr_xm_orbital", "scr_xm_orbital_blast", nuke_cord);
			}
		}
	}

	void tasks::nuke_normal(Vector3 pos)
	{
		insight::g_fiber_pool->queue_job([pos] {
			for (int i = 0; i < 3; i++)
			{
				Vector3 nuke_cord = vectors::get()->get_360_vec_around_coord(pos, 40, i * 5, 360);
				FIRE::ADD_EXPLOSION(nuke_cord, (int)eExplosionTag::EXP_TAG_SUBMARINE_BIG, 1.0f, true, true, 1.0, false);
				tasks::get()->play_ptfx_on_coordinates("scr_xm_orbital", "scr_xm_orbital_blast", nuke_cord, 1.5f);
			}

			script::get_current()->yield(500ms);

			for (int i = 3; i < 7; i++)
			{
				Vector3 nuke_cord = vectors::get()->get_360_vec_around_coord(pos, 20, i * 5, 360);
				FIRE::ADD_EXPLOSION(nuke_cord, (int)eExplosionTag::EXP_TAG_SUBMARINE_BIG, 1.0f, true, true, 1.0, false);
				tasks::get()->play_ptfx_on_coordinates("scr_xm_orbital", "scr_xm_orbital_blast", nuke_cord, 1.0f);
			}

			script::get_current()->yield(500ms);

			for (int i = 7; i < 10; i++)
			{
				Vector3 nuke_cord = vectors::get()->get_360_vec_around_coord(pos, 40, i * 5, 360);
				FIRE::ADD_EXPLOSION(nuke_cord, (int)eExplosionTag::EXP_TAG_SUBMARINE_BIG, 1.0f, true, true, 1.0, false);
				tasks::get()->play_ptfx_on_coordinates("scr_xm_orbital", "scr_xm_orbital_blast", nuke_cord, 1.5f);
			}
			});
	}

	void use_fx_asset(const char* asset)
	{
		for (uint8_t i = 0; !STREAMING::HAS_NAMED_PTFX_ASSET_LOADED(asset) && i < 100; i++)
		{
			STREAMING::REQUEST_NAMED_PTFX_ASSET(asset);
			script::get_current()->yield();
		}

		GRAPHICS::USE_PARTICLE_FX_ASSET(asset);
	}

	void nuke_expl1(Vector3 Position, bool audio)
	{
		constexpr int offsets[36][3] = { {10, 0, 0}, {0, 10, 0}, {10, 10, 0}, {-10, 0, 0}, {0, -10, 0}, {-10, -10, 0}, {10, -10, 0}, {-10, 10, 0}, {20, 0, 0}, {0, 20, 0}, {20, 20, 0}, {-20, 0, 0}, {0, -20, 0}, {-20, -20, 0}, {20, -20, 0}, {-20, 10, 0}, {30, 0, 0}, {0, 30, 0}, {30, 30, 0}, {-30, 0, 0}, {0, -30, 0}, {-30, -30, 0}, {30, -30, 0}, {-30, 10, 0}, {10, 30, 0}, {30, 10, 0}, {-30, -10, 0}, {-10, -30, 0}, {-10, 30, 0}, {-30, 10, 0}, {30, -10, 0}, {10, -30, 0}, {0, 0, 10}, {0, 0, -10}, {0, 0, 20}, {0, 0, -20} };
		for (int i = 0; i < 36; i++)
		{
			const int* offset = offsets[i];
			FIRE::ADD_EXPLOSION(Vector3(Position.x + offset[0], Position.y + offset[1], Position.z + offset[2]), (int)eExplosionTag::EXP_TAG_SUBMARINE_BIG, 1.f, audio, TRUE, 1.f, FALSE);
		}
	}

	void nuke_expl2(Vector3 Position, bool audio)
	{
		constexpr int offsets[9][3] = { {0, 0, -10}, {10, 0, -10}, {0, 10, -10}, {10, 10, -10}, {-10, 0, -10}, {0, -10, -10}, {-10, -10, -10}, {10, -10, -10}, {-10, 10, -10} };
		for (int i = 0; i < 9; i++)
		{
			const int* offset = offsets[i];
			FIRE::ADD_EXPLOSION(Vector3(Position.x + offset[0], Position.y + offset[1], Position.z + offset[2]), (int)eExplosionTag::EXP_TAG_SUBMARINE_BIG, 1.f, audio, TRUE, 1.f, FALSE);
		}
	}

	void nuke_expl3(Vector3 Position, bool audio)
	{
		constexpr int offsets[9][3] = { {10, 0, 0}, {0, 10, 0}, {10, 10, 0}, {-10, 0, 0}, {0, -10, 0}, {-10, -10, 0}, {10, -10, 0}, {-10, 10, 0}, {0, 0, 0} };
		for (int i = 0; i < 9; i++)
		{
			const int* offset = offsets[i];
			FIRE::ADD_EXPLOSION(Vector3(Position.x + offset[0], Position.y + offset[1], Position.z + offset[2]), (int)eExplosionTag::EXP_TAG_SUBMARINE_BIG, 1.f, audio, TRUE, 1.f, FALSE);
		}
	}

	void tasks::nuke_real(Vector3 Position, bool audio) {
		insight::g_fiber_pool->queue_job([Position, audio] {
			for (int i = 0; i < 17; i++)
			{
				if (i == 0)
				{
					FIRE::ADD_EXPLOSION(Vector3(Position.x, Position.y, Position.z), (int)eExplosionTag::EXP_TAG_SUBMARINE_BIG, 1.f, audio, TRUE, 5.f, FALSE);
				}
				else if (i == 1)
				{
					FIRE::ADD_EXPLOSION(Vector3(Position.x, Position.y, Position.z), (int)eExplosionTag::EXP_TAG_SUBMARINE_BIG, 1.f, audio, TRUE, 1.f, FALSE);
				}
				use_fx_asset("scr_xm_orbital");
				GRAPHICS::START_NETWORKED_PARTICLE_FX_NON_LOOPED_AT_COORD("scr_xm_orbital_blast",
					Vector3(Position.x,
						Position.y,
						Position.z),
					Vector3(0.f,
						180.f,
						0.f),
					4.5f,
					TRUE,
					TRUE,
					TRUE,
					FALSE);
			}

			nuke_expl1(Position, audio);

			for (int i = 0; i < 2; i++)
			{
				if (i == 0)
				{
					FIRE::ADD_EXPLOSION(Vector3(Position.x, Position.y, Position.z - 10), (int)eExplosionTag::EXP_TAG_SUBMARINE_BIG, 1.f, audio, TRUE, 5.f, FALSE);
				}
				use_fx_asset("scr_xm_orbital");
				GRAPHICS::START_NETWORKED_PARTICLE_FX_NON_LOOPED_AT_COORD("scr_xm_orbital_blast",
					Vector3(Position.x,
						Position.y,
						Position.z - 10),
					Vector3(0.f,
						180.f,
						0.f),
					4.5f,
					TRUE,
					TRUE,
					TRUE,
					FALSE);
			}

			nuke_expl2(Position, audio);

			constexpr float positionsZ[35] = { 1, 3, 5, 7, 10, 12, 15, 17, 20, 22, 25, 27, 30, 32, 35, 37, 40, 42, 45, 47, 50, 52, 55, 57, 59, 61, 63, 65, 70, 75, 75, 75, 75, 80, 80 };

			for (int i = 0; i < 35; i++)
			{
				float size = 1.5f;
				float pos = positionsZ[i];
				if (i % 2 != 0)
				{
					FIRE::ADD_EXPLOSION(Vector3(Position.x, Position.y, Position.z + pos), (int)eExplosionTag::EXP_TAG_SUBMARINE_BIG, 1.f, audio, TRUE, 1.f, FALSE);
				}
				use_fx_asset("scr_xm_orbital");
				GRAPHICS::START_NETWORKED_PARTICLE_FX_NON_LOOPED_AT_COORD("scr_xm_orbital_blast",
					Vector3(Position.x,
						Position.y,
						Position.z + pos),
					Vector3(0.f,
						180.f,
						0.f),
					size,
					TRUE,
					TRUE,
					TRUE,
					FALSE);

				if (i >= 34)
				{
					size = 3.f;
				}
				else if (i >= 30)
				{
					size = 3.5f;
				}

				script::get_current()->yield(40ms);
			}
			FIRE::ADD_EXPLOSION(Vector3(Position.x, Position.y, Position.z), 37, 99, 1, 1, 3, 0);
			nuke_expl3(Position, audio);
			});
	}

	void tasks::set_script(const char* script,bool toggle,int stacksize) {
		if (toggle) {
			if (!SCRIPT::DOES_SCRIPT_EXIST(script)) {
				while (!SCRIPT::HAS_SCRIPT_LOADED(script)) {
					SCRIPT::REQUEST_SCRIPT(script);
					script::get_current()->yield();
				}
				SYSTEM::START_NEW_SCRIPT(script, stacksize);
			} return;
		}
		else {
			if (SCRIPT::DOES_SCRIPT_EXIST(script)) {
				MISC::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME(script);
			}
			return;
		}
	}
	void tasks::disable_phone() {
		if (AUDIO::IS_MOBILE_PHONE_CALL_ONGOING()) {
			AUDIO::STOP_SCRIPTED_CONVERSATION(0);
		}
		PAD::DISABLE_CONTROL_ACTION(2, (int)ControllerInputs::INPUT_PHONE, TRUE);
	}

	Entity swap_ped_retun;
	Ped tasks::swap_ped(int t, Ped p, Hash h2) //hope it works (!_!) 
	{
		if (ENTITY::DOES_ENTITY_EXIST(p) && !ENTITY::IS_ENTITY_DEAD(p, 0)) {
			while (!STREAMING::HAS_MODEL_LOADED(h2)) {
				STREAMING::REQUEST_MODEL(h2);
				script::get_current()->yield();
			}
			if (STREAMING::HAS_MODEL_LOADED(h2)) {
				if (ENTITY::GET_ENTITY_MODEL(p) != h2) {
					Vector3 c = ENTITY::GET_ENTITY_COORDS(p, 0);
					float heading = ENTITY::GET_ENTITY_HEADING(p);

					ENTITY::SET_ENTITY_AS_MISSION_ENTITY(p, 0, 0);
					ENTITY::DELETE_ENTITY(&p);
					if (!ENTITY::DOES_ENTITY_EXIST(p)) {
						auto ped_swap = PED::CREATE_PED(t, h2, c, heading, globals::in_multiplayer(), false);
						swap_ped_retun = ped_swap;
						PED::SET_PED_DEFAULT_COMPONENT_VARIATION(ped_swap);
						TASK::TASK_WANDER_STANDARD(ped_swap, heading, 10);

						ENTITY::SET_PED_AS_NO_LONGER_NEEDED(&ped_swap);
						return ped_swap;
					}
					else return false;
				}
			}
		}
		return swap_ped_retun;
	}
	void tasks::disable_sky(bool toggle, bool default_restore) {

		if (default_restore) {
			*(BYTE*)pointers::get()->g_disable_sky = 0x48;
			return;
		}
		*(BYTE*)pointers::get()->g_disable_sky = toggle ? 0xC3 : 0x48;
	}

}