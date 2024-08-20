#pragma once
namespace insight {
	class script_utility {
	public: 
		 bool doors_locked;
		 int Player_Vehicle_Doors_Entity;
	public:
		int weapon_projectile_select = 0;
	public:
		int ped_spawner_sub = 0;
		int ped_spawner_guard = 0;
	public:
		int lsc_sub = 0;
		int teleport_sub = 0;
		int teleport_type = 0;
	public:
		bool disable_chat_profanity = false;
	public:
		int scroll_size_speed_u = 0;
	public:
		int n_attacker_weapon_hash_selected = 0;
		int n_guard_weapon_hash_selected = 72;
	public:
		int watch_yo_jet_bro = 3256;
		int watch_yo_jet_bro_again = 3256;
	public:
	    bool sponner_cam_running;
		Vector3 sponner_spawn_entity_pos;
	public:
		static script_utility* get() {
			static script_utility i{};
			return &i;
		}
	public:
		static void initialize() {
			get();
		}
	};

}

#pragma once
