#include "common.hpp"
namespace insight {
	struct ptfx_bullet_impact_dat
	{
		bool do_on_impact;
		int exp_type;
		bool is_audio;
		bool is_invisible;
		float cam_shake;
		bool owned;
		Ped ped;
	};
	struct ptfx_stuff_dat {
		const char* ptfx1;
		const char* ptfx2;
		int ptfx_scale;
		bool ptfx_use_color;
		float ptfx_red;
		float ptfx_green;
		float ptfx_blue;
	};
	struct ptfx_bullet_dat {
		Object bullet;
		Vector3 from;
		Vector3 to;
		timer ptfx_timer;
		int force;
		timer max_bullet_alive_time;
		ptfx_stuff_dat ptfx;
		ptfx_bullet_impact_dat impact;
	};
}
namespace insight {
	class bullet_ptfx {
	public:
		static std::vector<ptfx_bullet_dat> bullets;
		static void shoot_ptfx_bullet(Vector3 from, Vector3 to, int ptfx_timer, int force, int max_bullet_alive_time, ptfx_stuff_dat ptfx, ptfx_bullet_impact_dat impact);
		static void tick();
	public:
		static bullet_ptfx* get() {
			static bullet_ptfx i{};
			return &i;
		}
	};
}
