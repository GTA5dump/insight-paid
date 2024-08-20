#include "cheat/features/tasks.hpp"
#include "cheat/features/globals.hpp"
#include "cheat/features/features.hpp"
#include "cheat/features/scripted_globals.hpp"
#include "util/notify/notify.hpp"
#include "util/security/xorstr.hpp"


namespace insight {

	void network::n_spinning_alien_cage(Vector3 pos, bool visible) {
		pos.z = pos.z - 1;
		Object obj2 = OBJECT::CREATE_OBJECT(rage::joaat(xorstr_("apa_mp_apa_yacht_radar_01a")), pos, true, 0, 0);
		Object obj_ufo = OBJECT::CREATE_OBJECT(4032262659, pos, true, 0, 0);
		Object obj = OBJECT::CREATE_OBJECT(3532384181, pos, true, 0, 0);
		Object obj3 = OBJECT::CREATE_OBJECT(rage::joaat(xorstr_("hei_prop_hei_tree_fallen_02")), pos, true, 0, 0);
		Object obj4 = OBJECT::CREATE_OBJECT(1673275445, pos, true, 0, 0);
		Object obj43 = OBJECT::CREATE_OBJECT(1673275445, pos, true, 0, 0);
		Object obj433 = OBJECT::CREATE_OBJECT(1673275445, pos, true, 0, 0);
		Object obj5 = OBJECT::CREATE_OBJECT(3532384181, pos, true, 0, 0);

		script::get_current()->yield(100ms);
		ENTITY::ATTACH_ENTITY_TO_ENTITY(obj, obj2, 1, Vector3(0.0f, 0.f, 0.0f), Vector3(0.0f, 0.0f, 0.f), 0, true, true, false, 1, true, 0);
		ENTITY::ATTACH_ENTITY_TO_ENTITY(obj3, obj2, 1, Vector3(0.0f, 0.f, 1.2f), Vector3(0.0f, 0.0f, 0.f), 50, true, true, false, 1, true, 0);
		ENTITY::ATTACH_ENTITY_TO_ENTITY(obj4, obj2, 1, Vector3(0.0f, 0.f, 0.0f), Vector3(0.0f, 0.0f, 0.f), 0, true, true, false, 1, true, 0);
		ENTITY::ATTACH_ENTITY_TO_ENTITY(obj43, obj2, 1, Vector3(0.0f, 0.f, 0.0f), Vector3(0.0f, 0.0f, 200.f), 0, true, true, false, 1, true, 0);
		ENTITY::ATTACH_ENTITY_TO_ENTITY(obj433, obj2, 1, Vector3(0.0f, 0.f, 0.0f), Vector3(0.0f, 0.0f, 90.f), 0, true, true, false, 1, true, 0);
		ENTITY::ATTACH_ENTITY_TO_ENTITY(obj_ufo, obj2, 1, Vector3(0.0f, 0.f, 0.0f), Vector3(0.0f, 0.0f, 180.f), 0, true, true, false, 1, true, 0);
		ENTITY::ATTACH_ENTITY_TO_ENTITY(obj5, obj2, 1, Vector3(0.0f, 0.f, 0.0f), Vector3(0.0f, 0.0f, 0.f), 0, true, true, false, 1, true, 0);
		ENTITY::SET_ENTITY_VISIBLE(obj2, false, false);
		ENTITY::SET_ENTITY_VISIBLE(obj3, 0, 0);
		script::get_current()->yield(100ms);

		ENTITY::SET_ENTITY_VISIBLE(obj_ufo, visible, 0);
		ENTITY::SET_ENTITY_VISIBLE(obj4, visible, 0);
		ENTITY::SET_ENTITY_VISIBLE(obj43, visible, 0);
		ENTITY::SET_ENTITY_VISIBLE(obj433, visible, 0);
		ENTITY::SET_ENTITY_VISIBLE(obj5, visible, 0);
		script::get_current()->yield();


	}
	void network::n_fun_cages(int32_t ped, Vector3 pos, bool visible, int type)
	{
		if (type == 3)
		{
			//bkr_prop_biker_tube_l
			Hash cage = "bkr_prop_biker_tube_l"_joaat;
			tasks::get()->request_model(cage);
			cage = OBJECT::CREATE_OBJECT(cage, pos, globals::in_multiplayer(), 0, 0);
			ENTITY::FREEZE_ENTITY_POSITION(cage, true);
			ENTITY::SET_ENTITY_ROTATION(cage, 0.0, 90.0, 0.0, 1, true);
			if (!visible)
			ENTITY::SET_ENTITY_VISIBLE(cage, false, false);
			return;
		}

		if (type == 4)
		{
			//bkr_prop_biker_tube_l
			Hash cage = "prop_gold_cont_01"_joaat;
			tasks::get()->request_model(cage);
			cage = OBJECT::CREATE_OBJECT(cage, Vector3(pos.x, pos.y, pos.z-1.f), globals::in_multiplayer(), 0, 0);
			ENTITY::FREEZE_ENTITY_POSITION(cage, true);
			if (!visible)
				ENTITY::SET_ENTITY_VISIBLE(cage, false, false);
			return;
		}	
		Entity Cage_Ent[4];
		Hash cage_hash = rage::joaat("apa_prop_ss1_mpint_garage2");		
		{
			Vector3 rot = { 0,0,160 };
			Vector3 rot2 = { 0,0,70 };
			script::get_current()->yield(100ms);
			const auto poss = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(ped, Vector3(0, 3, -1));
			tasks::get()->request_model(cage_hash);
			Cage_Ent[0] = OBJECT::CREATE_OBJECT(cage_hash, poss, globals::in_multiplayer(), 0, 0);
			ENTITY::SET_ENTITY_ROTATION(Cage_Ent[0], rot2.x, rot2.y, rot2.z, 2, 0);
			ENTITY::FREEZE_ENTITY_POSITION(Cage_Ent[0], true);


			const auto pos1 = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(ped, Vector3(0, -3, -1));
			tasks::get()->request_model(cage_hash);
			Cage_Ent[1] = OBJECT::CREATE_OBJECT(cage_hash, pos1, globals::in_multiplayer(), 0, 0);
			ENTITY::SET_ENTITY_ROTATION(Cage_Ent[1], rot2.x, rot2.y, rot2.z, 2, 0);
			ENTITY::FREEZE_ENTITY_POSITION(Cage_Ent[1], true);


			const auto pos2 = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(ped, Vector3(3, 0, -1));
			tasks::get()->request_model(cage_hash);
			Cage_Ent[2] = OBJECT::CREATE_OBJECT(cage_hash, pos2, globals::in_multiplayer(), 0, 0);
			ENTITY::SET_ENTITY_ROTATION(Cage_Ent[2], rot.x, rot.y, rot.z, 2, 0);
			ENTITY::FREEZE_ENTITY_POSITION(Cage_Ent[2], true);

			const auto pos3 = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(ped, Vector3(-3, 0, -1));
			tasks::get()->request_model(cage_hash);
			Cage_Ent[3] = OBJECT::CREATE_OBJECT(cage_hash, pos3, globals::in_multiplayer(), 0, 0);
			ENTITY::SET_ENTITY_ROTATION(Cage_Ent[3], rot.x, rot.y, rot.z, 2, 0);
			ENTITY::FREEZE_ENTITY_POSITION(Cage_Ent[3], true);
			if (!visible)
			for (size_t i = 0; i < 3; i++)
			{			
					ENTITY::SET_ENTITY_VISIBLE(Cage_Ent[i], false, false);
			}
			if (type == 1)
			{
				FIRE::ADD_EXPLOSION(poss, 21, 100, true, false, 0, false);
				FIRE::ADD_EXPLOSION(pos1, 21, 100, true, false, 0, false);
				FIRE::ADD_EXPLOSION(pos2, 21, 100, true, false, 0, false);
				FIRE::ADD_EXPLOSION(pos3, 21, 100, true, false, 0, false);

			}
			if (type == 2)
			{
				FIRE::ADD_EXPLOSION(pos, 3, 100, false, false, 0, false);
				tasks::play_ptfx_on_coordinates(xorstr_("core"), xorstr_("ent_sht_flame"), pos, 5);

			}

		}

	}
	std::string illusiontubes[6] =
	{
		"sr_prop_spec_tube_l_01a",
		"sr_prop_spec_tube_l_02a",
		"sr_prop_spec_tube_l_03a",
		"sr_prop_spec_tube_l_04a",
		"sr_prop_spec_tube_l_05a",
		"sr_prop_spec_tube_refill"
	};
	void network::n_illusion_cages(Vector3 pos, bool visible, int type)
	{
		//bkr_prop_biker_tube_l
		Hash cageh = rage::joaat(illusiontubes[type]);
		tasks::get()->request_model(cageh);
		int  cage = OBJECT::CREATE_OBJECT(cageh, Vector3(pos.x, pos.y, pos.z  + (type == 5 ? -4 : 0)), true, 0, 0);
		ENTITY::FREEZE_ENTITY_POSITION(cage, true);
		ENTITY::SET_ENTITY_ROTATION(cage, 0.0, 90.0, 0.0, 1, true);
		if (!visible)
			ENTITY::SET_ENTITY_VISIBLE(cage, false, false);
		return;


	}
}
