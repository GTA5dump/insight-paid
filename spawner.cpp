#include "util/gta_util.hpp"
#include "cheat/script/script.hpp"
#include "cheat/menu/helper/ui.hpp"
#include "cheat/features/globals.hpp"
#include "util/panels/panels.hpp"
#include "util/config/config.hpp"
#include "cheat/menu/xml/modded_vehicle_loader.hpp"
#include "cheat/menu/xml/maps_loader.hpp"
#include "util/ini/ini_util.hpp"
#include "util/instructionals _buttons/instructionals buttons.hpp"
#include "cheat/menu/xml/xml.hpp"
#include "cheat/script/script_utility.hpp"
#include "game/gta/enums.hpp"
#include "util/script/fiber_pool.hpp"
#include "game/rage/vfx_types.hpp"
#include "cheat/features/features/features_utility.hpp"
namespace rage {
#pragma pack(push, 1)
	class hash_list
	{
	public:
		std::uint64_t* list; //0x0000
		std::int32_t capacity; //0x0008
		char pad_000C[4]; //0x000C
		std::int32_t free; //0x0010
		char pad_0014[4]; //0x0014
		std::uint64_t item_size; //0x0018
		char pad_0020[16]; //0x0020
		std::uint32_t* data; //0x0030
		char pad_0038[16]; //0x0038
		std::int32_t occupied; //0x0048
		const std::uint64_t get(std::int32_t index) const {
			if ((this->data[index >> 5] >> (index & 0x1F)) & 1)
				return this->list[index];
			return NULL;
		}
	}; // Size: 0x004C
#pragma pack(pop)
}


const char* get_vehicle_class_name(int id) {
	std::stringstream ss; ss << "VEH_CLASS_" << id;
	return HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(ss.str().c_str()) == "NULL" ? "Unknown Class" : HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(ss.str().c_str());
}

std::string m_guard_ability[] = {
	"Poor",
	"Average",
	"Professional"
};

int selected_vehicle_class;
std::string searchobject;
namespace insight {
	bodyguard_dat guard_spawn_struct = { "",0,1,0,1,5.f,1,5.f,timer(std::chrono::microseconds(0)),1,timer(std::chrono::microseconds(0)) ,100,100,100,1,0,2,100 };;
	void fuc_model_spawn(Hash hash,std::string name = "")
	{
			if (script_utility::get()->ped_spawner_sub == 0)
			{
				tasks::spawn_ped_locally(hash);
			}
			if (script_utility::get()->ped_spawner_sub == 1)
			{
				tasks::change_model(hash);
			}
			if (script_utility::get()->ped_spawner_sub == 2) {
				tasks::spawn_custom_attacker(globals::get_selected_ped(), hash,
					rage::joaat(weaponHashes[script_utility::get()->n_attacker_weapon_hash_selected]), 2000);
			}
			if (script_utility::get()->ped_spawner_sub == 3) {
				tasks::spawn_guard(hash, name, guard_spawn_struct);
			}
	}

}
namespace insight {

	void script_ui::spawner() {
		render::push<sub>("Spawner", "Spawner"_joaat, [](sub* ui) {
			ui::push()->feature_toggle(ui, "spawner_spoooner"_tf);
			ui->push(submenu("Settings").add_target("Spawner_Settings"_joaat));
			ui->push(submenu("Vehicles").add_target("Spawner_Vehicles"_joaat));
			ui->push(submenu("Objects").add_target("Spawner_Objects"_joaat)); // bugga 
			ui->push(submenu("Peds").add_target("Player_Models"_joaat).set_action([=] {
				xml::get()->load_ped_models();
				script_utility::get()->ped_spawner_sub = 0;
				})); // buigga
			ui->push(submenu("Bodyguards").add_target("Player_Models"_joaat).set_action([=] {
				xml::get()->load_ped_models();
				script_utility::get()->ped_spawner_sub = 3;
				})); // buigga
			//ped_spawner_sub
			ui->push(info("Externals"));
			ui->push(submenu("XML").add_target("Spawner_XML"_joaat)); // bugga
		});

		render::push<sub>("Settings", "Spawner_Settings"_joaat, [](sub* ui) {
			ui::push()->feature_toggle(ui, "spawner_delete_last"_tf);
			ui::push()->feature_toggle(ui, "spawner_in_air"_tf);
			ui::push()->feature_toggle(ui, "spawner_notification"_tf);
			ui::push()->feature_toggle(ui, "spawner_in_vehicle"_tf);
			ui::push()->feature_toggle(ui, "spawner_add_blip"_tf);
			ui::push()->feature_toggle(ui, "spawner_invincible"_tf);
			ui::push()->feature_toggle(ui, "spawner_maxed_out"_tf);
			ui::push()->feature_toggle(ui, "spawner_gifted"_tf);
			ui::push()->feature_toggle(ui, "spawner_fade"_tf);
		});
		render::push<sub>("Vehicles", "Spawner_Vehicles"_joaat, [](sub* ui) {
			ui->push(button("Input")
				.set_action([=] {
						std::string rest = tasks::get()->get_keyboard_input();
						tasks::spawn_vehicle_locally(rage::joaat(rest));
					}));
			for (std::int32_t i = 0; i < 23; i++) {
				ui->push(submenu(get_vehicle_class_name(i)).add_target("Spawner_Vehicle_Class_Selected"_joaat).add_function([i] {
					selected_vehicle_class = i;
				}));
			}
		});
		render::push<sub>("Objects", "Spawner_Objects"_joaat, [](sub* ui) {
			ui->push(submenu("All").add_target("Spawner_Objects_All"_joaat)); // bugga 
			for (int i = 0; i < ini::get()->favorite_objects_name.size(); i++)
			{
				ui->push(button(ini::get()->favorite_objects_name[i]).add_function([=] {
					Hash hash = rage::joaat(ini::get()->favorite_objects_hash[i]);
					tasks::get()->spawn_object_locally(hash);
					}));
			}
		});
		render::push<sub>("Objects", "Spawner_Objects_All"_joaat, [](sub* ui) {
			
			for (int i = 0; i < ini::get()->all_objects.size(); i++)
			{
				if (PAD::IS_DISABLED_CONTROL_JUST_PRESSED(0, (int)ControllerInputs::INPUT_SCRIPT_RLEFT))
				{
					ini::get()->add_favorite_object(ini::get()->all_objects[i], tasks::get_keyboard_input()); // needs some working hmm
					ini::get()->load_favorite_objects_ini();
				}
		
				if (searchobject.empty())
				{
					ui->push(button(ini::get()->all_objects[i]).add_function([=] {
						tasks::get()->spawn_object_locally(rage::joaat(ini::get()->all_objects[i]));
						}));
				}
				else if (ini::get()->all_objects[i].find(searchobject) != std::string::npos)
				{
					ui->push(button(ini::get()->all_objects[i]).add_function([=] {
						tasks::get()->spawn_object_locally(rage::joaat(ini::get()->all_objects[i]));
						}));		

				}
			}
			instructionals::get()->objects_instructional();
			PAD::DISABLE_CONTROL_ACTION(0, (int)ControllerInputs::INPUT_SCRIPT_RLEFT, 1);
			PAD::DISABLE_CONTROL_ACTION(0, (int)ControllerInputs::INPUT_REPLAY_PREVIEW, 1);
			PAD::DISABLE_CONTROL_ACTION(0, (int)ControllerInputs::INPUT_REPLAY_TIMELINE_PLACE_CLIP, 1);
										   
			if (PAD::IS_DISABLED_CONTROL_JUST_PRESSED(0, (int)ControllerInputs::INPUT_REPLAY_PREVIEW))
			{
				searchobject = tasks::get_keyboard_input();
				//SEARCH
			}			
			if (PAD::IS_DISABLED_CONTROL_JUST_PRESSED(0, (int)ControllerInputs::INPUT_REPLAY_TIMELINE_PLACE_CLIP))
			{
				searchobject.clear();
				//Clear
			}
		});
		render::push<sub>("Ped Models", "Player_Models"_joaat, [](sub* ui) {
			if (script_utility::get()->ped_spawner_sub == 3) {
				ui->push(submenu("Settings").add_target("Guard_Spawn_Settings"_joaat));
			}
			ui->push(submenu("Popular").add_target("Player_Models_Popular"_joaat));
			ui->push(submenu("Story").add_target("Player_Models_Story"_joaat));
			if (script_utility::get()->ped_spawner_sub != 2)
				ui->push(submenu("Animal").add_target("Player_Models_Animal"_joaat));
			ui->push(submenu("Emergency").add_target("Player_Models_Emergency"_joaat));
			ui->push(submenu("Role Models").add_target("Player_Models_Role"_joaat));
			ui->push(submenu("Ambient").add_target("Player_Models_Ambient"_joaat));
			ui->push(submenu("Misc").add_target("Player_Models_Misc"_joaat));
			if (script_utility::get()->ped_spawner_sub == 3) {
				ui->push(info("Manage Guard"));
				for (int i = 0; i < features_utility::get()->m_bodyguards.size(); i++)
				{

					ui->push(submenu(features_utility::get()->m_bodyguards[i].name).add_target("Bodyguards_sub"_joaat).set_action([=] {
						script_utility::get()->ped_spawner_guard = i;
						})); // buigga
				}
			}

			});
		render::push<sub>("Guard", "Bodyguards_sub"_joaat, [](sub* ui) {
			int indexToCheck = script_utility::get()->ped_spawner_guard;
			if (indexToCheck >= 0 && indexToCheck < features_utility::get()->m_bodyguards.size()) {
				ui->push(array<std::string, int>(xorstr_("Change Weapon"))
					.add_position(&script_utility::get()->n_guard_weapon_hash_selected)
					.add_array2(weaponNames_Cleaned, 98).set_action([=] {
						features_utility::get()->m_bodyguards[script_utility::get()->ped_spawner_guard].weapon = rage::joaat(weaponHashes[script_utility::get()->n_guard_weapon_hash_selected]);
						}));
				toggle_feature* feature = "spawner_godmode"_tf;
				ui->push(toggle(feature->m_name).add_toggle(&features_utility::get()->m_bodyguards[script_utility::get()->ped_spawner_guard].godmode).
					add_description(feature->m_description));

				toggle_feature* feature2 = "spawner_guard_aim_to_kill"_tf;
				ui->push(toggle(feature2->m_name).add_toggle(&features_utility::get()->m_bodyguards[script_utility::get()->ped_spawner_guard].aim_to_kill).
					add_description(feature2->m_description));

				toggle_feature* feature3 = "spawner_guard_auto_kill_nearby"_tf;
				ui->push(number_toggle<float>(feature3->m_name).add_toggle(&features_utility::get()->m_bodyguards[script_utility::get()->ped_spawner_guard].autokill_when_near)
					.add_number(&features_utility::get()->m_bodyguards[script_utility::get()->ped_spawner_guard].autokill_when_near_range).add_min(0).add_max(200).add_precision(0).
					add_step(1.0f).add_description(feature3->m_description));

				toggle_feature* feature4 = "spawner_guard_range"_tf;
				ui->push(number_toggle<float>(feature4->m_name).add_toggle(&features_utility::get()->m_bodyguards[script_utility::get()->ped_spawner_guard].autokill_when_near)
					.add_number(&features_utility::get()->m_bodyguards[script_utility::get()->ped_spawner_guard].keep_guards_near_range).add_min(0).add_max(200).add_precision(0).
					add_step(1.0f).add_description(feature4->m_description));
	
				toggle_feature* feature5 = "spawner_guard_frozen"_tf;
				ui->push(toggle(feature5->m_name).add_toggle(&features_utility::get()->m_bodyguards[script_utility::get()->ped_spawner_guard].freeze).
					add_description(feature5->m_description));

				
				toggle_feature* feature7 = "spawner_guard_accuracy"_tf;
				ui->push(number<int>(feature7->m_name).add_number(&features_utility::get()->m_bodyguards[script_utility::get()->ped_spawner_guard].accuracy).
					add_min(0).add_max(100).add_precision(0).add_step(1).add_description(feature7->m_description));

				toggle_feature* feature33 = "spawner_guard_attack_players"_tf;
				ui->push(toggle(feature33->m_name).add_toggle(&features_utility::get()->m_bodyguards[script_utility::get()->ped_spawner_guard].attack_player).
					add_description(feature33->m_description));

				ui->push(array<std::string, int>("Ability").add_array(&m_guard_ability).add_position(&features_utility::get()->m_bodyguards[script_utility::get()->ped_spawner_guard].combat_ability));
				
				ui->push(button("Delete")
					.set_action([=] {
						tasks::delete_entity(features_utility::get()->m_bodyguards[script_utility::get()->ped_spawner_guard].ent);
						}));

			}
			});
		render::push<sub>("Guard Settings", "Guard_Spawn_Settings"_joaat, [](sub* ui) {
			toggle_feature* feature4 = "spawner_guard_max_health"_tf;
			ui->push(number<float>(feature4->m_name).add_number(&guard_spawn_struct.max_health).
				add_min(0).add_max(4000.f).add_precision(0).add_step(10).add_description(feature4->m_description));

			toggle_feature* feature44 = "spawner_guard_health"_tf;
			ui->push(number<float>(feature44->m_name).add_number(&guard_spawn_struct.health).
				add_min(0).add_max(4000.f).add_precision(0).add_step(10).add_description(feature44->m_description));

			toggle_feature* feature444 = "spawner_guard_armor"_tf;
			ui->push(number<int>(feature444->m_name).add_number(&guard_spawn_struct.armor).
				add_min(0).add_max(100).add_precision(0).add_step(1).add_description(feature444->m_description));


			toggle_feature* feature = "spawner_godmode"_tf;
			ui->push(toggle(feature->m_name).add_toggle(&guard_spawn_struct.godmode).
				add_description(feature->m_description));

			toggle_feature* feature4444 = "spawner_guard_auto_kill_nearby"_tf;
			ui->push(number<float>(feature4444->m_name).add_number(&guard_spawn_struct.autokill_when_near_range).
				add_min(0).add_max(100).add_precision(0).add_step(1).add_description(feature4444->m_description));

			toggle_feature* feature44444 = "spawner_guard_range"_tf;
			ui->push(number<float>(feature44444->m_name).add_number(&guard_spawn_struct.keep_guards_near_range).
				add_min(0).add_max(100).add_precision(0).add_step(1).add_description(feature44444->m_description));

			toggle_feature* feature2 = "spawner_guard_aim_to_kill"_tf;
			ui->push(toggle(feature2->m_name).add_toggle(&guard_spawn_struct.aim_to_kill).
				add_description(feature2->m_description));

			toggle_feature* feature3 = "spawner_guard_frozen"_tf;
			ui->push(toggle(feature3->m_name).add_toggle(&guard_spawn_struct.freeze).
				add_description(feature3->m_description));

			toggle_feature* feature33 = "spawner_guard_attack_players"_tf;
			ui->push(toggle(feature33->m_name).add_toggle(&guard_spawn_struct.attack_player).
				add_description(feature33->m_description));

			toggle_feature* feature6 = "spawner_guard_accuracy"_tf;
			ui->push(number<int>(feature6->m_name).add_number(&guard_spawn_struct.accuracy).
				add_min(0).add_max(100).add_precision(0).add_step(1).add_description(feature6->m_description));

			ui->push(array<std::string, int>("Ability").add_array(&m_guard_ability).add_position(&guard_spawn_struct.combat_ability));

			});
		render::push<sub>("Popular Peds", "Player_Models_Popular"_joaat, [](sub* ui) {
			for (int i = 0; i < xml::get()->g_ped_models.popular.size(); i++)
			{
				ui->push(button(xml::get()->g_ped_models.popular[i].name)
					.set_action([=] {
						fuc_model_spawn(xml::get()->g_ped_models.popular[i].hash, xml::get()->g_ped_models.popular[i].name);
						}));
			}});
		render::push<sub>("Story Ped", "Player_Models_Story"_joaat, [](sub* ui) {
			for (int i = 0; i < xml::get()->g_ped_models.story.size(); i++)
			{
				ui->push(button(xml::get()->g_ped_models.story[i].name)
					.set_action([=] {		
						fuc_model_spawn(xml::get()->g_ped_models.story[i].hash, xml::get()->g_ped_models.story[i].name);
						}));
			}});
		render::push<sub>("Animal Ped", "Player_Models_Animal"_joaat, [](sub* ui) {
			for (int i = 0; i < xml::get()->g_ped_models.animal.size(); i++)
			{
				ui->push(button(xml::get()->g_ped_models.animal[i].name)
					.set_action([=] {
						fuc_model_spawn(xml::get()->g_ped_models.animal[i].hash, xml::get()->g_ped_models.animal[i].name);
						}));
			}});
		render::push<sub>("Emergency Ped", "Player_Models_Emergency"_joaat, [](sub* ui) {
			for (int i = 0; i < xml::get()->g_ped_models.emergency.size(); i++)
			{
				ui->push(button(xml::get()->g_ped_models.emergency[i].name)
					.set_action([=] {
						fuc_model_spawn(xml::get()->g_ped_models.emergency[i].hash, xml::get()->g_ped_models.emergency[i].name);
						}));
			}});
		render::push<sub>("Role Ped", "Player_Models_Role"_joaat, [](sub* ui) {
			for (int i = 0; i < xml::get()->g_ped_models.role.size(); i++)
			{
				ui->push(button(xml::get()->g_ped_models.role[i].name)
					.set_action([=] {
						fuc_model_spawn(xml::get()->g_ped_models.role[i].hash, xml::get()->g_ped_models.role[i].name);
						}));
			}});
		render::push<sub>("Ambient Ped", "Player_Models_Ambient"_joaat, [](sub* ui) {
			for (int i = 0; i < xml::get()->g_ped_models.ambient.size(); i++)
			{
				ui->push(button(xml::get()->g_ped_models.ambient[i].name)
					.set_action([=] {
						fuc_model_spawn(xml::get()->g_ped_models.ambient[i].hash, xml::get()->g_ped_models.ambient[i].name);
						}));
			}});
		render::push<sub>("Misc Ped", "Player_Models_Misc"_joaat, [](sub* ui) {
			for (int i = 0; i < xml::get()->g_ped_models.misc.size(); i++)
			{
				ui->push(button(xml::get()->g_ped_models.misc[i].name)
					.set_action([=] {
						fuc_model_spawn(xml::get()->g_ped_models.misc[i].hash, xml::get()->g_ped_models.misc[i].name);
						}));
			}});

		render::push<sub>("Vehicles", "Spawner_XML"_joaat, [](sub* ui) {
			ui->push(submenu("Vehicles").add_target("Spawner_XML_Vehicles"_joaat)); // bugga
			ui->push(submenu("Maps").add_target("Spawner_XML_Maps"_joaat)); // bugga
		});
		render::push<sub>("Vehicle", "Spawner_XML_Vehicles"_joaat, [](sub* ui) {
			auto filePath = std::filesystem::path(std::getenv(xorstr_("appdata"))).append(xorstr_("insight")).append(xorstr_("xml")).append(xorstr_("modded vehicles"));
			std::filesystem::directory_iterator dirIt{ filePath.string() };
			for (auto&& dirEntry : dirIt) {
				if (dirEntry.is_regular_file()) {
					auto path = dirEntry.path();
					if (path.has_filename()) {
						if (path.extension().string() == xorstr_(".xml")) {
							ui->push(button(path.stem().string()).add_function([path] {
								insight::xmlvehicleloader::load_xml_vehicle(path.stem().string(),globals::h_local_ped_pos(),0);
								}));
						}
					}
				}
			}
			});

		render::push<sub>("Maps", "Spawner_XML_Maps"_joaat, [](sub* ui) {
			auto filePath = std::filesystem::path(std::getenv(xorstr_("appdata"))).append(xorstr_("insight")).append(xorstr_("xml")).append(xorstr_("maps"));
			std::filesystem::directory_iterator dirIt{ filePath.string() };
			for (auto&& dirEntry : dirIt) {
				if (dirEntry.is_regular_file()) {
					auto path = dirEntry.path();
					if (path.has_filename()) {
						if (path.extension().string() == xorstr_(".xml")) {
							ui->push(button(path.stem().string()).add_function([path] {
								insight::g_fiber_pool->queue_job([path] {
									insight::xmlmaploader::load_placements_from_xml_file(path.stem().string());
									});
								}));
						}
					}
				}
			}
		});

		render::push<sub>("Vehicles", "Spawner_Vehicle_Class_Selected"_joaat, [](sub* ui) {
			if (insight::pointers::get()->g_hash_list != nullptr) {
				for (std::int32_t i = 0; i < insight::pointers::get()->g_hash_list->capacity; i++) {
					std::uint64_t info = insight::pointers::get()->g_hash_list->get(i);
					if (info != NULL) {
						if ((*(BYTE*)(info + 157) & 0x1F) == 5) {
							std::string make_ptr = (char*)((uintptr_t)info + 0x2A4);
							std::string model_ptr = (char*)((uintptr_t)info + 0x298);
							if (VEHICLE::GET_VEHICLE_CLASS_FROM_NAME(rage::joaat(model_ptr)) == selected_vehicle_class) {
								std::string manufacturerLabel = HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(make_ptr.c_str());
								std::string nameLabel = HUD::GET_FILENAME_FOR_AUDIO_CONVERSATION(model_ptr.c_str());
								std::string final_label = std::format("{}{}", (manufacturerLabel != "NULL" || manufacturerLabel.empty() ? manufacturerLabel + " " : ""), nameLabel);

								ui->push(vehicleo(final_label.c_str())
									.add_function([=] { tasks::spawn_vehicle_locally(*(u32*)(info + 0x18)); }).add_vehicle_hash(*(u32*)(info + 0x18)));
							}
						}
					}
				}
				if (ui->get_option(ui->get_selected_option())->get_vehicle_hash()) {
					vehicle_info_panel(ui->get_option(ui->get_selected_option())->get_vehicle_hash());
				}
			}
		});
	}
}
