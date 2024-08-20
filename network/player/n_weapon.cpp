

#include "cheat/script/script.hpp"
#include "cheat/menu/helper/ui.hpp"
#include "util/panels/panels.hpp"
#include "util/config/config.hpp"
#include "cheat/features/globals.hpp"
#include "cheat/features/features/features_utility.hpp"
#include "util/script/script_global.hpp"
#include <network/Network.hpp>
#include "cheat/pointers/pointers.hpp"
#include"cheat/features/features.hpp"
#include "util/script/fiber_pool.hpp"
#include "cheat/features/features/features_utility.hpp"
#include "cheat/script/script_utility.hpp"
#include "game/gta/enums.hpp"

namespace insight {
	void script_ui::network_weapon_options() {
		render::push<sub>("Weapon", "Network_Players_Selected_Weapon"_joaat, [](sub* ui) {
			tasks::draw_player_info(globals::get_selected_id());
			ui->push(submenu(xorstr_("Locker")).add_target("Network_Players_Selected_Weapon_Locker"_joaat));

			ui->push(toggle("network_delete_gun"_tf->m_name)
				.add_toggle(&player_options::get()->n_delete_gun_value[globals::get_selected_id()])
				.add_description("network_delete_gun"_tf->m_description));

			ui->push(toggle("network_tryhard_gun"_tf->m_name)
				.add_toggle(&player_options::get()->n_try_hard_gun_value[globals::get_selected_id()])
				.add_description("network_tryhard_gun"_tf->m_description));

			ui->push(toggle("network_flamming_ammo_gun"_tf->m_name)
				.add_toggle(&player_options::get()->n_flammingammo_gun_value[globals::get_selected_id()])
				.add_description("network_flamming_ammo_gun"_tf->m_description));

			ui->push(toggle("network_magnet_gun"_tf->m_name)
				.add_toggle(&player_options::get()->n_magnet_gun_value[globals::get_selected_id()])
				.add_description("network_magnet_gun"_tf->m_description));

			ui->push(array_toggle<std::string, int>("network_projectile_gun"_tf->m_name)
				.add_toggle(&player_options::get()->n_projectile_gun_value[globals::get_selected_id()])
				.add_position(&player_options::get()->n_projectile_gun_type_value[globals::get_selected_id()])
				.add_description("network_projectile_gun"_tf->m_description)
				.add_array2(eVehicleWeapons_Names, 28));

			ui->push(array_toggle<std::string, int>("network_impact_exp_gun"_tf->m_name)
				.add_toggle(&player_options::get()->n_exp_gun_value[globals::get_selected_id()])
				.add_position(&player_options::get()->n_exp_gun_type_value[globals::get_selected_id()])
				.add_description("network_impact_exp_gun"_tf->m_description)
				.add_array2(eExplosionsType, 73));

			ui->push(array_toggle<std::string, int>("network_particle_gun"_tf->m_name)
				.add_toggle(&player_options::get()->n_ptfx_gun_value[globals::get_selected_id()])
				.add_position(&player_options::get()->n_ptfx_gun_type_value[globals::get_selected_id()])
				.add_description("network_particle_gun"_tf->m_description)
				.add_array2(particle_effects, std::size(particle_effects)));

			});
		render::push<sub>("Locker", "Network_Players_Selected_Weapon_Locker"_joaat, [](sub* ui) {
			tasks::draw_player_info(globals::get_selected_id());
			ui->push(button(xorstr_("Give All Weapons"))
				.set_action([=] {
					tasks::give_weapons_to_player(globals::get_selected_id());
					}));	
			ui->push(button(xorstr_("Remove All Weapons"))
				.set_action([=] {
					tasks::remove_weapons_from_player(globals::get_selected_id());
					}));
			ui->push(info("Upgrades"));

			ui->push(button(xorstr_("Upgrade Current Weapon"))
				.set_action([=] {
					tasks::upgrade_player_current_weapon(globals::get_selected_id());
					}));


			ui->push(button(xorstr_("Upgrade All Weapons"))
				.set_action([=] {
					tasks::upgrade_player_weapons(globals::get_selected_id());
					}));

			});

	}
}