#include "common.hpp"
#include "natives.hpp"
#include "util/script/script_mgr.hpp"
#include "ptfx_bullet.hpp"
#include "cheat/features/tasks.hpp"
namespace insight {
	std::vector<ptfx_bullet_dat> bullet_ptfx::bullets;
	void bullet_ptfx::shoot_ptfx_bullet(Vector3 from, Vector3 to, int ptfx_timer , int force,
	int max_bullet_alive_time, ptfx_stuff_dat ptfx, ptfx_bullet_impact_dat impact) {
		Hash obj_model = "prop_golf_ball"_joaat;
		while (!STREAMING::HAS_MODEL_LOADED(obj_model)) {
			STREAMING::REQUEST_MODEL(obj_model);
			script::get_current()->yield();
		}
		Object bullet = OBJECT::CREATE_OBJECT(obj_model, from, NETWORK::NETWORK_IS_SESSION_ACTIVE(), 0, 1);
		ENTITY::SET_ENTITY_ALPHA(bullet, 0, 0);
		bullets.push_back(ptfx_bullet_dat(bullet, from, to,timer(std::chrono::milliseconds(ptfx_timer)),
		force, timer(std::chrono::milliseconds(max_bullet_alive_time)), ptfx, impact));
	}	
	void bullet_ptfx::tick() {
		for (int i = 0; i < bullets.size(); i++)
		{
			ptfx_bullet_dat bullet = bullets[i];
			Vector3 force = bullet.to - ENTITY::GET_ENTITY_COORDS(bullet.bullet, 0);
			tasks::apply_force_to_position(bullet.bullet, force, ENTITY::GET_ENTITY_VELOCITY(bullet.bullet), 
			2.5f * bullet.force, 0.3f);
			if (bullet.ptfx_timer.update()) {
				tasks::play_ptfx_bone_tick(bullet.bullet, 0, bullet.ptfx.ptfx1, bullet.ptfx.ptfx1,
					bullet.ptfx.ptfx2, bullet.ptfx.ptfx_scale, bullet.ptfx.ptfx_use_color, bullet.ptfx.ptfx_red,
					bullet.ptfx.ptfx_green, bullet.ptfx.ptfx_blue, { 0,0,0 });
			}

			if (ENTITY::HAS_ENTITY_COLLIDED_WITH_ANYTHING(bullet.bullet) || bullet.max_bullet_alive_time.update()) {
				if (bullet.impact.do_on_impact) {
					if (bullet.impact.owned) {
						FIRE::ADD_OWNED_EXPLOSION(bullet.impact.ped, ENTITY::GET_ENTITY_COORDS(bullet.bullet,0), bullet.impact.exp_type, 9999.f,
							bullet.impact.is_audio, bullet.impact.is_invisible, bullet.impact.cam_shake);
					}
					else {
						FIRE::ADD_EXPLOSION(ENTITY::GET_ENTITY_COORDS(bullet.bullet, 0), bullet.impact.exp_type, 9999.f, bullet.impact.is_audio, bullet.impact.is_invisible, bullet.impact.cam_shake, 0);
					}
				}
				ENTITY::DELETE_ENTITY(&bullet.bullet);
				bullets.erase(bullets.begin() + i);
				i--;
			}
		}
	}
}