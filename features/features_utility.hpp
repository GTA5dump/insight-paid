#pragma once
#include <rage/vector.hpp>
#include "cheat/menu/sub/option_flag.h"
namespace insight {
	struct m_drift_mode_handling_data {
		float f_bais = 0.9f;
		float inertia = 40.0f;
		float traction_max = 1.5f;
		float traction_min = 0.6f;
	};
	struct force_teleport_player_struct {
		std::int16_t g_player_net_id;
		rage::fvector3 g_position;
	};
	struct bodyguard_dat {
		std::string name;
		Entity ent;
		bool godmode;
		Hash weapon;
		bool autokill_when_near;
		float autokill_when_near_range;
		bool keep_guards_near;
		float keep_guards_near_range;
		timer keep_guards_near_range_timer;
		bool aim_to_kill;
		timer getting_in_timer;
		float max_health;
		float health;
		int armor;
		bool attack_player;
		bool freeze;
		int combat_ability;
		int accuracy;

	};
};
namespace insight {
	inline std::unordered_map<std::uint16_t, force_teleport_player_struct> force_teleport_player_data;
	
	class features_utility {
	public://weapons		
		std::vector<std::uint32_t> aimbot_selected_bones = { 0x796E };
		int decal_paintgun = 1030;
		Vector3 Paint_Gun_Colors = { 255, 0, 0 };
		eExplosionTag data_grenade = eExplosionTag::GRENADE;
		Hash vehicle_weapons_hash = "weapon_rpg"_joaat;
		color n_bullet_tracer_color = { 255,255,250 };
		color n_laser_sight_color = { 255,0,0};

	public://network
		bool jew_crash = false;
		bool nitro_crash = false;
		bool woops_crash = false;
		bool mods_crash = false;
		bool vehicle_crash = false;
		bool fragment_crash = false;
		bool objects_crash = false;
		bool parachute_crash = false;
		bool ong_crash = false;
		bool parachute_crash2 = false;
		bool testy_crash = false;

		 timer player_info_line = timer(std::chrono::seconds(1s));
		 bool player_info_line_draw = false;
		 Vector3 player_info_line_vec = { 0,0,0 };
	public://vehicle
		m_drift_mode_handling_data m_drift_mode_handling;
		m_drift_mode_handling_data m_drift_mode_default;
	public://world
		Vector3 blackhole_pos;
		int m_meteor_world_selected = 0;
		int m_flag_heli_chauf = 4;
		Hash airstrike_Hash = "WEAPON_RPG"_joaat;

		static void create_machine_sentry(Vector3 placement);
		static void create_missle_sentry(Vector3 placement);
		struct missle_data {
			int entity;
			timer tick;
			timer missle_tick;
			int missle_cout = 0;
			int num_missle = 6;
			bool shoot_mode = false;
			int yaw = 0;
			bool ground_targets = true;
			bool sky_targets = true;
			bool shooting = true;
		};
		struct gun_data {
			bool shooting;
			bool no_players_shooting;
		};
		std::vector<int> sentry_guns;
		std::vector<gun_data> sentry_guns_dat;
		std::vector<missle_data> sentry_missles;
		int sentry_selected = 0;
		int sentry_selected_type = 0;
	public:
		 bool spawn_placement_from_xml_node_first_time = false;
		 bool load_placements_from_xml_file_in_progress = false;
	public:
		std::vector<bodyguard_dat> m_bodyguards;
	public:
		rage::fvector4 m_azimuth_east_color;
		rage::fvector4 m_azimuth_west_color;
		rage::fvector4 m_zenith_color;
		rage::fvector4 m_sun_color;
		rage::fvector4 m_cloud_color;
		rage::fvector4 m_moon_color;
		rage::fvector4 m_wheels_color;
		rage::fvector4 m_veh_light_min_color;
		rage::fvector4 m_veh_light_max_color;
		rage::fvector4 m_waypoint_path_color = {255,255,255,255};
		int m_waypoint_path_marker = 2;
		rage::fvector4 m_ped_trails_color;
	public:
		bool misc_initialized = false;
	public:
	    bool is_player_spectating[32] = {false};
		Vector3 players_cam_data[32] = { Vector3(0,0,0)};
	public:
		int a_opened = 50;
	public:
		Vector3 spoofed_pos_coordinates = { 0,0,0 };
	public:
		static features_utility* get() {
			static features_utility i{};
			return &i;
		}
	public:
		static void initialize() {
			get();
		}
	};

}

#pragma once
