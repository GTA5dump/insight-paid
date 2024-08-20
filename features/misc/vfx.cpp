#include "cheat/features/features.hpp"
#include "util/math/math.hpp"
#include "cheat/features/features/features_utility.hpp"
#include "game/rage/vfx_types.hpp"
#include "game/gta/enums.hpp"
#include "util/notify/notify.hpp"
namespace insight {
	void UpdateColorFading(rage::fvector4& color, float fadeSpeed, float brightness = 100.f) {
		color.x = vectors::get()->get_rainbow_fade_colors(fadeSpeed)[0] / brightness;
		color.y = vectors::get()->get_rainbow_fade_colors(fadeSpeed)[1] / brightness;
		color.z = vectors::get()->get_rainbow_fade_colors(fadeSpeed)[2] / brightness;
	}
	void miscellaneous::vfx_m_azimuth_east(toggle_int_feature* feature, bool& value, int& value2) {
		if (!value) {
			return;
		}
		if (value2 == 1) {
			UpdateColorFading(features_utility::get()->m_azimuth_east_color,
			"m_azimuth_east_color_fade_speed"_FF->m_value.floating_point);
		}
	}
	void miscellaneous::vfx_m_azimuth_west(toggle_int_feature* feature, bool& value, int& value2) {
		if (!value) {
			return;
		}
		if (value2 == 1) {
			UpdateColorFading(features_utility::get()->m_azimuth_west_color,
			"m_azimuth_west_color_fade_speed"_FF->m_value.floating_point);
		}
	}
	void miscellaneous::vfx_m_zenith(toggle_int_feature* feature, bool& value, int& value2) {
		if (!value) {
			return;
		}
		if (value2 == 1) {
			UpdateColorFading(features_utility::get()->m_zenith_color,
			"m_zenith_color_fade_speed"_FF->m_value.floating_point);
		}
	}
	void miscellaneous::vfx_m_sun(toggle_int_feature* feature, bool& value, int& value2) {
		if (!value) {
			return;
		}
		if (value2 == 1) {
			UpdateColorFading(features_utility::get()->m_sun_color,
			"m_sun_color_fade_speed"_FF->m_value.floating_point);
		}
	}
	void miscellaneous::vfx_m_cloud(toggle_int_feature* feature, bool& value, int& value2) {
		if (!value) {
			return;
		}
		if (value2 == 1) {
			UpdateColorFading(features_utility::get()->m_cloud_color,
			"m_cloud_fade_speed"_FF->m_value.floating_point);
		}
	}
	void miscellaneous::vfx_m_moon(toggle_int_feature* feature, bool& value, int& value2) {
		if (!value) {
			return;
		}
		if (value2 == 1) {
			UpdateColorFading(features_utility::get()->m_moon_color,
			"m_moon_fade_speed"_FF->m_value.floating_point);
		}
	}
	bool manipulate_tyre_data_first = true;
	void manipulate_tyre_data(bool enable_tracks, bool reset_color, color color, bool constant = true) {
		if (manipulate_tyre_data_first) {
			pointers::get()->m_vfx_wheel_cached = (vfx_types::CWheelVfx*)malloc((sizeof(vfx_types::CWheelVfx) * pointers::get()->m_vfx_wheel.second) * 4);
			memcpy(pointers::get()->m_vfx_wheel_cached, pointers::get()->m_vfx_wheel.first, (sizeof(vfx_types::CWheelVfx) * pointers::get()->m_vfx_wheel.second) * 4);
			manipulate_tyre_data_first = false;
		}
		vfx_types::CWheelVfx* vfx_wheel = pointers::get()->m_vfx_wheel.first;
		vfx_types::CWheelVfx* vfx_wheel_cache_ = pointers::get()->m_vfx_wheel_cached;

		for (uint32_t i = 0; i < (uint32_t)(pointers::get()->m_vfx_wheel.second * 4); i++) {

			if (!reset_color) {
				if (enable_tracks) {
					vfx_wheel[i].m_decal_id = "m_wheel_vfx_decal_id"_if->m_value.integer;
					vfx_wheel[i].m_decal_id2 = 53;
					vfx_wheel[i].m_decal_id3 = 64;
					vfx_wheel[i].m_decal_id4 = 255;
					vfx_wheel[i].m_unk1 = true;
					vfx_wheel[i].m_unk2 = true;
					vfx_wheel[i].m_unk3 = true;
					vfx_wheel[i].m_unk4 = true;
					
					if (constant) {
						vfx_wheel[i].m_pressure_min = 0.0f;
						vfx_wheel[i].m_pressure_max = 255.0f;
					}
					else {
						vfx_wheel[i].m_pressure_min = 0.0f;
						vfx_wheel[i].m_pressure_max = 0.0f;

					}
				}
				vfx_wheel[i].m_tint_r = color.r;
				vfx_wheel[i].m_tint_g = color.g;
				vfx_wheel[i].m_tint_b = color.b;
			}
			else {
				vfx_wheel[i].m_decal_id = vfx_wheel_cache_[i].m_decal_id;
				vfx_wheel[i].m_decal_id2 = vfx_wheel_cache_[i].m_decal_id2;
				vfx_wheel[i].m_decal_id3 = vfx_wheel_cache_[i].m_decal_id3;
				vfx_wheel[i].m_decal_id4 = vfx_wheel_cache_[i].m_decal_id4;
				vfx_wheel[i].m_unk1 = vfx_wheel_cache_[i].m_unk1;
				vfx_wheel[i].m_unk2 = vfx_wheel_cache_[i].m_unk2;
				vfx_wheel[i].m_unk3 = vfx_wheel_cache_[i].m_unk3;
				vfx_wheel[i].m_unk4 = vfx_wheel_cache_[i].m_unk4;
				vfx_wheel[i].m_pressure_min = vfx_wheel_cache_[i].m_pressure_min;
				vfx_wheel[i].m_pressure_max = vfx_wheel_cache_[i].m_pressure_max;
				vfx_wheel[i].m_tint_r = vfx_wheel_cache_[i].m_tint_r;
				vfx_wheel[i].m_tint_g = vfx_wheel_cache_[i].m_tint_g;
				vfx_wheel[i].m_tint_b = vfx_wheel_cache_[i].m_tint_b;
			}
		}
	}
	bool was_vfx_m_wheel_on = false;
	void miscellaneous::vfx_m_wheel(toggle_int_feature* feature, bool& value, int& value2) {
		if (!value) {
			if (was_vfx_m_wheel_on) {
				manipulate_tyre_data(false, true, color(1, 1, 1));
				was_vfx_m_wheel_on = false;
			}
			return;
		}
		was_vfx_m_wheel_on = true;
		color clor = color(features_utility::get()->m_wheels_color.x, features_utility::get()->m_wheels_color.y, features_utility::get()->m_wheels_color.z);
		manipulate_tyre_data(true, false, clor, "m_wheel_vfx_tracks"_tf->m_value.toggle);
		if (value2 == 1) {
			UpdateColorFading(features_utility::get()->m_wheels_color, "m_wheel_vfx_fade_speed"_FF->m_value.floating_point, 1);
		}
	}
	void manipulate_light_data(bool enable_lights, bool reset_color, color colormin,color colormax,
	float intensity_min , float intensity_max, float range_min, float range_max, float falloff_min, float falloff_max) {
		if (manipulate_tyre_data_first) {
			pointers::get()->m_vfx_wheel_cached = (vfx_types::CWheelVfx*)malloc((sizeof(vfx_types::CWheelVfx) * pointers::get()->m_vfx_wheel.second) * 4);
			memcpy(pointers::get()->m_vfx_wheel_cached, pointers::get()->m_vfx_wheel.first, (sizeof(vfx_types::CWheelVfx) * pointers::get()->m_vfx_wheel.second) * 4);
			manipulate_tyre_data_first = false;
		}
		vfx_types::CWheelVfx* vfx_wheel = pointers::get()->m_vfx_wheel.first;
		vfx_types::CWheelVfx* vfx_wheel_cache_ = pointers::get()->m_vfx_wheel_cached;

		for (uint32_t i = 0; i < (uint32_t)(pointers::get()->m_vfx_wheel.second * 4); i++) {

			if (!reset_color) {
				if (enable_lights) {
					vfx_wheel[i].m_lights_on = true;				
				}
				vfx_wheel[i].m_lights_col_min_r = colormin.r;
				vfx_wheel[i].m_lights_col_min_g = colormin.g;
				vfx_wheel[i].m_lights_col_min_b = colormin.b;
				vfx_wheel[i].m_lights_col_max_r = colormax.r;
				vfx_wheel[i].m_lights_col_max_g = colormax.g;
				vfx_wheel[i].m_lights_col_max_b = colormax.b;
				vfx_wheel[i].m_lights_intensity_min = intensity_min;
				vfx_wheel[i].m_lights_intensity_max = intensity_max;
				vfx_wheel[i].m_lights_range_min = range_min;
				vfx_wheel[i].m_lights_range_max = range_max;
				vfx_wheel[i].m_lights_falloff_min = falloff_min;
				vfx_wheel[i].m_lights_falloff_max = falloff_max;
				vfx_wheel[i].m_friction_thresh_min = 0.f;
				vfx_wheel[i].m_friction_thresh_max = 0.f;
				vfx_wheel[i].m_disp_thresh_min = 0.f;
				vfx_wheel[i].m_disp_thresh_max = 0.f;
				vfx_wheel[i].m_burn_friction_evo_min = 0.f;
				vfx_wheel[i].m_burn_friction_evo_max = 0.f;
				vfx_wheel[i].m_burn_friction_temp_min = 0.f;
				vfx_wheel[i].m_burn_friction_temp_max = 0.f;

			}
			else {
				vfx_wheel[i].m_lights_on = vfx_wheel_cache_[i].m_lights_on;
				vfx_wheel[i].m_lights_col_min_r = vfx_wheel_cache_[i].m_lights_col_min_r;
				vfx_wheel[i].m_lights_col_min_g = vfx_wheel_cache_[i].m_lights_col_min_g;
				vfx_wheel[i].m_lights_col_min_b = vfx_wheel_cache_[i].m_lights_col_min_b;
				vfx_wheel[i].m_lights_col_max_r = vfx_wheel_cache_[i].m_lights_col_max_r;
				vfx_wheel[i].m_lights_col_max_g = vfx_wheel_cache_[i].m_lights_col_max_g;
				vfx_wheel[i].m_lights_col_max_b = vfx_wheel_cache_[i].m_lights_col_max_b;
				vfx_wheel[i].m_lights_intensity_min = vfx_wheel_cache_[i].m_lights_intensity_min;
				vfx_wheel[i].m_lights_intensity_max = vfx_wheel_cache_[i].m_lights_intensity_max;
				vfx_wheel[i].m_lights_range_min = vfx_wheel_cache_[i].m_lights_range_min;
				vfx_wheel[i].m_lights_range_max = vfx_wheel_cache_[i].m_lights_range_max;
				vfx_wheel[i].m_lights_falloff_min = vfx_wheel_cache_[i].m_lights_falloff_min;
				vfx_wheel[i].m_lights_falloff_max = vfx_wheel_cache_[i].m_lights_falloff_max;
				vfx_wheel[i].m_friction_thresh_min = vfx_wheel_cache_[i].m_friction_thresh_min;
				vfx_wheel[i].m_friction_thresh_max = vfx_wheel_cache_[i].m_friction_thresh_max;
				vfx_wheel[i].m_disp_thresh_min = vfx_wheel_cache_[i].m_disp_thresh_min;
				vfx_wheel[i].m_disp_thresh_max = vfx_wheel_cache_[i].m_disp_thresh_max;
				vfx_wheel[i].m_burn_friction_evo_min = vfx_wheel_cache_[i].m_burn_friction_evo_min;
				vfx_wheel[i].m_burn_friction_evo_max = vfx_wheel_cache_[i].m_burn_friction_evo_max;
				vfx_wheel[i].m_burn_friction_temp_min = vfx_wheel_cache_[i].m_burn_friction_temp_min;
				vfx_wheel[i].m_burn_friction_temp_max = vfx_wheel_cache_[i].m_burn_friction_temp_max;
			}
		}
	}
	bool was_vfx_m_light_on = false;
	void miscellaneous::vfx_m_light(toggle_int_feature* feature, bool& value, int& value2) {
		if (!value) {
			if (was_vfx_m_light_on) {
				manipulate_light_data(false, true, color(1, 1, 1),color(1, 1, 1),0,0, 0, 0,0,0);
				was_vfx_m_light_on = false;
			}
			return;
		}
		was_vfx_m_light_on = true;
		color clor_min = color(features_utility::get()->m_veh_light_min_color.x, features_utility::get()->m_veh_light_min_color.y, features_utility::get()->m_veh_light_min_color.z);
		color clor_max = color(features_utility::get()->m_veh_light_max_color.x, features_utility::get()->m_veh_light_max_color.y, features_utility::get()->m_veh_light_max_color.z);
		manipulate_light_data(true, false, clor_min, clor_max,"m_veh_m_lights_intensity_min"_FF->m_value.floating_point,
			"m_veh_m_lights_intensity_max"_FF->m_value.floating_point, "m_veh_m_lights_range_min"_FF->m_value.floating_point,
			"m_veh_m_lights_range_max"_FF->m_value.floating_point,"m_veh_m_lights_falloff_min"_FF->m_value.floating_point,
			"m_veh_m_lights_falloff_max"_FF->m_value.floating_point);
		if (value2 == 1) {
			UpdateColorFading(features_utility::get()->m_veh_light_min_color, "m_veh_lights_vfx_fade_speed"_FF->m_value.floating_point, 1);
			UpdateColorFading(features_utility::get()->m_veh_light_max_color, "m_veh_lights_vfx_fade_speed"_FF->m_value.floating_point, 1);
		}
	}
	float store_vfx_m_fog_on = 0;
	bool was_vfx_m_fog_on = false;
	void miscellaneous::vfx_m_fog_level(toggle_float_feature* feature, bool& value, float& value2) {
		if (!value) {
			if (was_vfx_m_fog_on) {
				pointers::get()->g_visual_settings->m_fog_level = store_vfx_m_fog_on;
				was_vfx_m_fog_on = false;
			}
			value2 = pointers::get()->g_visual_settings->m_fog_level * 100.f;
			return;
		}
		was_vfx_m_fog_on = true;
		if (store_vfx_m_fog_on == 0) {
			store_vfx_m_fog_on = pointers::get()->g_visual_settings->m_fog_level;
		}
		pointers::get()->g_visual_settings->m_fog_level = value2 / 100.f;
	}
	float store_vfx_m_sun_on = 0;
	bool was_vfx_distance_sun_on = false;
	void miscellaneous::vfx_m_unk_0x8(toggle_float_feature* feature, bool& value, float& value2) {
		if (!value) {

			if (was_vfx_distance_sun_on) {
				pointers::get()->g_visual_settings->m_distance_from_sun = store_vfx_m_sun_on;
				was_vfx_distance_sun_on = false;
			}
			value2 = pointers::get()->g_visual_settings->m_distance_from_sun;
			return;
		}
		was_vfx_distance_sun_on = true;
		if (store_vfx_m_sun_on == 0) {
			store_vfx_m_sun_on = pointers::get()->g_visual_settings->m_distance_from_sun;
		}
		pointers::get()->g_visual_settings->m_distance_from_sun = value2;
	}
	float store_vfx_m_unk_on = 0;
	bool was_vfx_unk_on = false;
	void miscellaneous::vfx_m_distance_from_sun(toggle_float_feature* feature, bool& value, float& value2) {
		if (!value) {

			if (was_vfx_unk_on) {
				pointers::get()->g_visual_settings->m_unk_0x8 = store_vfx_m_unk_on;
				was_vfx_unk_on = false;
			}
			value2 = pointers::get()->g_visual_settings->m_distance_from_sun;
			return;
		}
		was_vfx_unk_on = true;
		if (store_vfx_m_unk_on == 0) {
			store_vfx_m_unk_on = pointers::get()->g_visual_settings->m_unk_0x8;
		}
		pointers::get()->g_visual_settings->m_unk_0x8 = value2;
	}	
	float store_vfx_m_fov_on = 0;
	bool was_vfx_m_fov_on = false;
	void miscellaneous::vfx_m_fov(toggle_float_feature* feature, bool& value, float& value2) {
		if (!value) {

			if (was_vfx_m_fov_on) {
				pointers::get()->g_visual_settings->m_fov = store_vfx_m_fov_on;
				was_vfx_m_fov_on = false;
			}
			value2 = pointers::get()->g_visual_settings->m_distance_from_sun;
			return;
		}
		was_vfx_m_fov_on = true;
		if (store_vfx_m_fov_on == 0) {
			store_vfx_m_fov_on = pointers::get()->g_visual_settings->m_fov;
		}
		pointers::get()->g_visual_settings->m_fov = value2;
	}
	enum VfxGroup_e 
	{
		VFXGROUP_UNDEFINED = 0xFFFFFFFF,
		VFXGROUP_VOID = 0x0,
		VFXGROUP_GENERIC = 0x1,
		VFXGROUP_CONCRETE = 0x2,
		VFXGROUP_CONCRETE_DUSTY = 0x3,
		VFXGROUP_TARMAC = 0x4,
		VFXGROUP_TARMAC_BRITTLE = 0x5,
		VFXGROUP_STONE = 0x6,
		VFXGROUP_BRICK = 0x7,
		VFXGROUP_MARBLE = 0x8,
		VFXGROUP_PAVING = 0x9,
		VFXGROUP_SANDSTONE = 0xA,
		VFXGROUP_SANDSTONE_BRITTLE = 0xB,
		VFXGROUP_SAND_LOOSE = 0xC,
		VFXGROUP_SAND_COMPACT = 0xD,
		VFXGROUP_SAND_WET = 0xE,
		VFXGROUP_SAND_UNDERWATER = 0xF,
		VFXGROUP_SAND_DEEP = 0x10,
		VFXGROUP_SAND_WET_DEEP = 0x11,
		VFXGROUP_ICE = 0x12,
		VFXGROUP_SNOW_LOOSE = 0x13,
		VFXGROUP_SNOW_COMPACT = 0x14,
		VFXGROUP_GRAVEL = 0x15,
		VFXGROUP_GRAVEL_DEEP = 0x16,
		VFXGROUP_DIRT_DRY = 0x17,
		VFXGROUP_MUD_SOFT = 0x18,
		VFXGROUP_MUD_DEEP = 0x19,
		VFXGROUP_MUD_UNDERWATER = 0x1A,
		VFXGROUP_CLAY = 0x1B,
		VFXGROUP_GRASS = 0x1C,
		VFXGROUP_GRASS_SHORT = 0x1D,
		VFXGROUP_HAY = 0x1E,
		VFXGROUP_BUSHES = 0x1F,
		VFXGROUP_TREE_BARK = 0x20,
		VFXGROUP_LEAVES = 0x21,
		VFXGROUP_METAL = 0x22,
		VFXGROUP_WOOD = 0x23,
		VFXGROUP_WOOD_DUSTY = 0x24,
		VFXGROUP_WOOD_SPLINTER = 0x25,
		VFXGROUP_CERAMIC = 0x26,
		VFXGROUP_CARPET_FABRIC = 0x27,
		VFXGROUP_CARPET_FABRIC_DUSTY = 0x28,
		VFXGROUP_PLASTIC = 0x29,
		VFXGROUP_PLASTIC_HOLLOW = 0x2A,
		VFXGROUP_RUBBER = 0x2B,
		VFXGROUP_LINOLEUM = 0x2C,
		VFXGROUP_PLASTER_BRITTLE = 0x2D,
		VFXGROUP_CARDBOARD = 0x2E,
		VFXGROUP_PAPER = 0x2F,
		VFXGROUP_FOAM = 0x30,
		VFXGROUP_FEATHERS = 0x31,
		VFXGROUP_TVSCREEN = 0x32,
		VFXGROUP_GLASS = 0x33,
		VFXGROUP_GLASS_BULLETPROOF = 0x34,
		VFXGROUP_CAR_METAL = 0x35,
		VFXGROUP_CAR_PLASTIC = 0x36,
		VFXGROUP_CAR_GLASS = 0x37,
		VFXGROUP_PUDDLE = 0x38,
		VFXGROUP_LIQUID_WATER = 0x39,
		VFXGROUP_LIQUID_BLOOD = 0x3A,
		VFXGROUP_LIQUID_OIL = 0x3B,
		VFXGROUP_LIQUID_PETROL = 0x3C,
		VFXGROUP_LIQUID_MUD = 0x3D,
		VFXGROUP_FRESH_MEAT = 0x3E,
		VFXGROUP_DRIED_MEAT = 0x3F,
		VFXGROUP_PED_HEAD = 0x40,
		VFXGROUP_PED_TORSO = 0x41,
		VFXGROUP_PED_LIMB = 0x42,
		VFXGROUP_PED_FOOT = 0x43,
		VFXGROUP_PED_CAPSULE = 0x44,
		NUM_VFX_GROUPS = 0x45,
	};
	vfx_types::CLiquidVfx manipulate_ped_trails_data_m_backup[5];
	bool anipulate_ped_trails_first = false;
	void manipulate_ped_trails_data(bool reset_color, color color) {
		if (!anipulate_ped_trails_first) {
			memcpy(manipulate_ped_trails_data_m_backup, pointers::get()->g_visual_group_settings, sizeof(manipulate_ped_trails_data_m_backup));
			anipulate_ped_trails_first = true;
		}
		vfx_types::CLiquidVfx* ped_trails = pointers::get()->g_visual_group_settings + VFXGROUP_PED_FOOT;
		if (!reset_color) {
			ped_trails->r = color.r;
			ped_trails->g = color.g;
			ped_trails->b = color.b;
		}
		else {
			memcpy(ped_trails, manipulate_ped_trails_data_m_backup, sizeof(manipulate_ped_trails_data_m_backup));
			anipulate_ped_trails_first = false;
		}

	}
	bool was_vfx_m_ped_trails_on = false;
	void miscellaneous::vfx_m_ped_trails(toggle_int_feature* feature, bool& value, int& value2) {
		if (!value) {
			if (was_vfx_m_ped_trails_on) {
				manipulate_ped_trails_data(true, color(1, 1, 1));
				was_vfx_m_ped_trails_on = false;
			}
			return;
		}
		was_vfx_m_ped_trails_on = true;
		color colors = color(features_utility::get()->m_ped_trails_color.x, features_utility::get()->m_ped_trails_color.y, features_utility::get()->m_ped_trails_color.z);
		manipulate_ped_trails_data(false, colors);
		if (value2 == 1) {
			UpdateColorFading(features_utility::get()->m_ped_trails_color, "m_foot_vfx_fade_speed"_FF->m_value.floating_point, 1);
			UpdateColorFading(features_utility::get()->m_ped_trails_color, "m_foot_vfx_fade_speed"_FF->m_value.floating_point, 1);
		}
	}
	void miscellaneous::vfx_need_for_speed(toggle_int_feature* feature, bool& value, int& value2) {
		if (!value) {
			
			return;
		}
		if (HUD::IS_WAYPOINT_ACTIVE()) {
			for (int i = 0; i < pointers::get()->g_wapoint_points_data->m_count; i++)
			{
				if (i != pointers::get()->g_wapoint_points_data->m_count+1) {
					rage::vector4<float> point = pointers::get()->g_wapoint_points_data->m_points[i+1];
					Vector3 pos = { point.x,point.y,point.z };
					rage::vector4<float> point_next = pointers::get()->g_wapoint_points_data->m_points[i + 2];
					Vector3 next_pos = { point_next.x,point_next.y,point_next.z };
					pos.z += "m_enable_waypoint_markers_z_pos"_FF->m_value.floating_point;
					Vector3 rotation = vectors::get()->calculate_rotation_from_v3s(pos, next_pos); 
					rotation.y += 180;
					tasks::draw_marker((eMarkerType)features_utility::get()->m_waypoint_path_marker, pos, "m_enable_waypoint_markers_size"_FF->m_value.floating_point, features_utility::get()->m_waypoint_path_color.x, features_utility::get()->m_waypoint_path_color.y,
						features_utility::get()->m_waypoint_path_color.z, features_utility::get()->m_waypoint_path_color.w, "m_enable_waypoint_markers_move_up_down"_tf->m_value.toggle,
						false, false, false, Vector3(0,0,0), rotation);
				}
			}
		}
		if (value2 == 1) {
			UpdateColorFading(features_utility::get()->m_waypoint_path_color, "m_enable_waypoint_markers_fade_speed"_FF->m_value.floating_point, 1);
			UpdateColorFading(features_utility::get()->m_waypoint_path_color, "m_enable_waypoint_markers_fade_speed"_FF->m_value.floating_point, 1);
		}

	}
	float default_shadow_light = 0;
	bool was_vfx_screen_shadow_light_on = false;
	void miscellaneous::vfx_screen_shadow_light(toggle_float_feature* feature, bool& value, float& value2) {
		if (!value) {
			if (default_shadow_light == 0) {
				default_shadow_light = pointers::get()->g_visualvfx->m_shadow_light;
			}
			if (was_vfx_screen_shadow_light_on) {
				pointers::get()->g_visualvfx->m_shadow_light = default_shadow_light;
				was_vfx_screen_shadow_light_on = false;
			}
			value2 = pointers::get()->g_visualvfx->m_shadow_light;
			return;
		}
		was_vfx_screen_shadow_light_on = true;
		 pointers::get()->g_visualvfx->m_shadow_light = value2;
	}	
	float default_reflection = 0;
	bool was_vfx_screen_reflection_on = false;
	void miscellaneous::vfx_screen_reflection(toggle_float_feature* feature, bool& value, float& value2) {
		if (!value) {
			if (default_reflection == 0) {
				default_reflection = pointers::get()->g_visualvfx->m_reflection;
			}
			if (was_vfx_screen_reflection_on) {
				pointers::get()->g_visualvfx->m_reflection = default_reflection;
				was_vfx_screen_reflection_on = false;
			}
			value2 = pointers::get()->g_visualvfx->m_reflection;
			return;
		}
		was_vfx_screen_reflection_on = true;
		 pointers::get()->g_visualvfx->m_reflection = value2;
	}	
	float default_gamma = 0;
	bool was_vfx_screen_gamma = false;
	void miscellaneous::vfx_screen_gamma(toggle_float_feature* feature, bool& value, float& value2) {
		if (!value) {
			if (default_gamma == 0) {
				default_gamma = pointers::get()->g_visualvfx->m_gamma;
			}
			if (was_vfx_screen_gamma) {
				pointers::get()->g_visualvfx->m_gamma = default_gamma;
				was_vfx_screen_gamma = false;
			}
			value2 = pointers::get()->g_visualvfx->m_gamma;
			return;
		}
		was_vfx_screen_gamma = true;
		pointers::get()->g_visualvfx->m_gamma = value2;
	}	
	float default_blur = 0;
	bool was_vfx_screen_blur_on = false;
	void miscellaneous::vfx_screen_blur(toggle_float_feature* feature, bool& value, float& value2) {
		if (!value) {
			if (default_blur == 0) {
				default_blur = pointers::get()->g_visualvfx->m_blur;
			}
			if (was_vfx_screen_blur_on) {
				pointers::get()->g_visualvfx->m_blur = default_blur;
				was_vfx_screen_blur_on = false;
			}
			was_vfx_screen_blur_on = true;
			value2 = pointers::get()->g_visualvfx->m_blur;
			return;
		}
		was_vfx_screen_blur_on = true;
	 pointers::get()->g_visualvfx->m_blur = value2;
	}	
	float default_blur2 = 0;
	bool was_vfx_screen_blur2_on = false;
	void miscellaneous::vfx_screen_blur2(toggle_float_feature* feature, bool& value, float& value2) {
		if (!value) {
			if (default_blur2 == 0) {
				default_blur2 = pointers::get()->g_visualvfx->m_blur2;
			}
			if (was_vfx_screen_blur2_on) {
				pointers::get()->g_visualvfx->m_blur2 = default_blur2;
				was_vfx_screen_blur2_on = false;
			}
			value2 = pointers::get()->g_visualvfx->m_blur2;
			return;
		}
		was_vfx_screen_blur2_on = true;
		pointers::get()->g_visualvfx->m_blur2 = value2;
	}
	float default_sky_intensity = 0;
	bool was_vfx_screen_sky_intensity_on = false;
	void miscellaneous::vfx_screen_sky_intensity(toggle_float_feature* feature, bool& value, float& value2) {
		if (!value) {
			if (default_sky_intensity == 0) {
				default_sky_intensity = pointers::get()->g_visualvfx->m_sky_intensity;
			}
			if (was_vfx_screen_sky_intensity_on) {
				pointers::get()->g_visualvfx->m_sky_intensity = default_sky_intensity;
				was_vfx_screen_sky_intensity_on = false;
			}
			value2 = pointers::get()->g_visualvfx->m_sky_intensity;
			return;
		}
		was_vfx_screen_sky_intensity_on = true;
		 pointers::get()->g_visualvfx->m_sky_intensity = value2;
	}	
	float default_m_saturation = 0;
	bool was_vfx_screen_saturation_on = false;
	void miscellaneous::vfx_screen_saturation(toggle_float_feature* feature, bool& value, float& value2) {
		if (!value) {
			if (default_m_saturation == 0) {
				default_m_saturation = pointers::get()->g_visualvfx->m_saturation;
			}
			if (was_vfx_screen_saturation_on) {
				pointers::get()->g_visualvfx->m_saturation = default_m_saturation;
				was_vfx_screen_saturation_on = false;
			}
			value2 = pointers::get()->g_visualvfx->m_saturation;
			return;
		}
		was_vfx_screen_saturation_on = true;
		 pointers::get()->g_visualvfx->m_saturation = value2;
	}
	bool was_turn_off_sky_on = false;
	void miscellaneous::turn_off_sky(toggle_feature* feature, bool& value) {
		if (!value) {
			if (was_turn_off_sky_on) {
				tasks::get()->disable_sky(false);
				was_turn_off_sky_on = false;
			}
			return;
		}
		was_turn_off_sky_on = true;
		tasks::get()->disable_sky(true);
	}

}