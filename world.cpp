
#include "cheat/script/script.hpp"
#include "cheat/menu/helper/ui.hpp"
#include "cheat/features/globals.hpp"
#include "util/panels/panels.hpp"
#include "util/config/config.hpp"
#include "cheat/features/globals.hpp"
#include "cheat/features/features/features_utility.hpp"
#include "util/math/math.hpp"
#include "cheat/script/script_utility.hpp"
namespace insight {
	std::string m_blackhole_type[] = {
	"Super",
	"Super & Delete",
	"Sprial"
	};
	std::string m_magneto_entites_world[] = {
	"Peds",
	"Vehicles",
	"Both"
	};
	std::string m_magneto_type_world[] = {
		"On Top",
		"At Bottom",
		"On Left",
		"On Right",
		"In Front",
		"At Back",
		"Tornado Mode Beta"
	};
	std::string m_strike_shoot_pos_world[] = {
		"From Sky",
		"From Ground"
	};
	std::string m_shoot_at_world[] = {
		"At Cars",
		"At Peds",
		"At Sky",
		"At Ground"
	};
	std::string m_meteor_world[] = {
	"Tiny",
	"Standard",
	"Huge",
	"Random"
	};
	std::string m_strike_speed[] = {
	"Slow",
	"Medium",
	"Fast",
	};
	std::string m_waypoint_nuke[] = {
	"Realistic",
	"Normal",
	"X Pattern"
	};
	bool blackhole_pos_set = false;

	float m_azimuth_east_red;
	float m_azimuth_east_green;
	float m_azimuth_east_blue;
	float m_azimuth_east_intensity = 1.0f;

	float m_azimuth_west_red;
	float m_azimuth_west_green;
	float m_azimuth_west_blue;
	float m_azimuth_west_intensity = 1.0f;

	float m_azimuth_transition_red;
	float m_azimuth_transition_green;
	float m_azimuth_transition_blue;
	float m_azimuth_transition_intensity = 1.0f;

	float m_zenith_red;
	float m_zenith_green;
	float m_zenith_blue;
	float m_zenith_intensity = 1.0f;

	float m_zenith_transition_red;
	float m_zenith_transition_green;
	float m_zenith_transition_blue;
	float m_zenith_transition_intensity = 1.0f;

	float m_cloud_mid_red;
	float m_cloud_mid_green;
	float m_cloud_mid_blue;
	float m_cloud_mid_intensity = 1.0f;

	float m_cloud_base_red;
	float m_cloud_base_green;
	float m_cloud_base_blue;
	float m_cloud_base_intensity = 1.0f;
}


namespace insight {
	void script_ui::world() {
		render::push<sub>("World", "World"_joaat, [](sub* ui) {
			ui->push(submenu("Time").add_target("World_Time"_joaat));
			ui->push(submenu("Weather").add_target("World_Weather"_joaat));
			ui->push(submenu("Water").add_target("World_Water"_joaat));
			ui->push(submenu("Black Hole").add_target("World_BlackHole"_joaat));
			ui->push(submenu("Magneto").add_target("World_Magneto"_joaat));
			ui->push(submenu("Meteor Shower").add_target("World_Meteor"_joaat));
			ui->push(submenu("Strike").add_target("World_Strike"_joaat));
			ui->push(submenu("Sentry").add_target("World_Sentry"_joaat));
			ui->push(info("General"));
			ui::push()->array_feature_toggle(ui, "nuke_waypoint"_tif, m_waypoint_nuke, 3);
			ui::push()->feature_toggle_int(ui, "angry_plane_mode"_tif, 1, 30, 1);
			ui::push()->feature_toggle_float(ui, "anti_aircraft"_tff, 0, 1000, 5);
			ui::push()->feature_toggle(ui, "riot_mode"_tf);
			ui::push()->feature_toggle(ui, "jump_around_mode"_tf);
			ui::push()->feature_toggle(ui, "cum_mode"_tf);


			render::push<sub>("Black Hole", "World_BlackHole"_joaat, [](sub* ui) {
				ui::push()->array_feature_toggle(ui, "black_hole"_tif, m_blackhole_type, 3);

				if ("black_hole"_tif->m_toggle_value.toggle) {
					if (blackhole_pos_set) {
						features_utility::get()->blackhole_pos = vectors::get()->get_front_camera_coordinates_local(10);
						blackhole_pos_set = false;
					}
				}
				else {
					blackhole_pos_set = true;
				}
				ui::push()->feature_float(ui, "black_hole_z"_FF, -2147483, 2147483, 1.0f, 0);
				ui::push()->feature_float(ui, "black_hole_range"_FF, -2147483, 2147483, 1.0f, 0);
				});

			render::push<sub>("Magneto", "World_Magneto"_joaat, [](sub* ui) {
				ui::push()->array_feature_toggle(ui, "magneto_mode"_tif, m_magneto_entites_world, 3);

				ui->push(array<std::string, int>("magneto_mode_type"_if->m_name)
					.add_position(&"magneto_mode_type"_if->m_value.integer)
					.add_array2(m_magneto_type_world, 7));

				ui::push()->feature_float(ui, "magneto_mode_entites_attract_range"_FF, 0, 2147483, 0.1f, 1);
				ui::push()->feature_float(ui, "magneto_mode_up_down"_FF, -2147483, 2147483, 0.1f, 1);
				ui::push()->feature_float(ui, "magneto_mode_range"_FF, -2147483, 2147483, 0.1f, 1);
				if ("magneto_mode_type"_if->m_value.integer == 6) {
					ui::push()->feature_int(ui, "magneto_mode_delay"_if, 0, 100, 1, 1);
				}
				ui::push()->feature_toggle(ui, "magneto_mode_super_force"_tf);
				if (!"magneto_mode_super_force"_tf->m_value.toggle)
					ui::push()->feature_float(ui, "magneto_mode_force_intensity"_FF, 0, 10, 0.1f, 1);
				});

			render::push<sub>("Strike", "World_Strike"_joaat, [](sub* ui) {
				ui::push()->array_feature_toggle(ui, "airstike_mode"_tif, m_strike_shoot_pos_world, 2);

				ui->push(array<std::string, int>("airstike_mode_shoot_at"_if->m_name)
					.add_position(&"airstike_mode_shoot_at"_if->m_value.integer)
					.add_array2(m_shoot_at_world, 4));	
				ui->push(array<std::string, int>("airstike_mode_speed"_tf->m_name).add_array(&m_strike_speed).add_position(&"airstike_mode_speed"_tf->m_value.integer).
					set_description("airstike_mode_speed"_tf->m_description));
				ui::push()->feature_int(ui, "airstike_mode_delay"_if, 0, 1000, 5, 1);
				ui->push(submenu("Projectile").add_target("Player_Vehicle_Weapons_Selct"_joaat).set_action([=] {
					script_utility::get()->weapon_projectile_select = 3;
					}));
				});
			render::push<sub>("Sentry", "World_Sentry"_joaat, [](sub* ui) {
				ui->push(button("Place Sentry Machine").set_description("Targets Peds")
					.set_action([=] {
						features_utility::get()->create_machine_sentry(vectors::get()->get_front_camera_coordinates_local(10));
						}));
				ui->push(button("Place Sentry Missle").set_description("Targets Vehicles")
					.set_action([=] {
						features_utility::get()->create_missle_sentry(vectors::get()->get_front_camera_coordinates_local(10));
						}));
				for (int i = 0; i < features_utility::get()->sentry_guns.size(); i++) {
					ui->push(submenu("Machine " + std::to_string(i)).add_target("World_Sentry_Selected"_joaat).set_action([=] {
						features_utility::get()->sentry_selected = i;
						features_utility::get()->sentry_selected_type = 0;
						}));
				}

					for (int i = 0; i < features_utility::get()->sentry_missles.size(); i++) {
						ui->push(submenu("Missle " + std::to_string(i)).add_target("World_Sentry_Selected"_joaat).set_action([=] {
							features_utility::get()->sentry_selected = i;
							features_utility::get()->sentry_selected_type = 1;

							}));

					}
				});
			render::push<sub>("Sentry", "World_Sentry_Selected"_joaat, [](sub* ui) {
				if (features_utility::get()->sentry_selected_type == 0) {
					ui->push(toggle("Shooting").add_toggle(&features_utility::get()->sentry_guns_dat[features_utility::get()->sentry_selected].shooting));
					ui->push(toggle("No Players Shooting").add_toggle(&features_utility::get()->sentry_guns_dat[features_utility::get()->sentry_selected].no_players_shooting));
					ui->push(button("Delete")
						.set_action([=] {
							tasks::get()->delete_entity(features_utility::get()->sentry_guns[features_utility::get()->sentry_selected]);
							if (features_utility::get()->sentry_selected >= 0 && features_utility::get()->sentry_selected < features_utility::get()->features_utility::get()->sentry_guns.size()) {
								features_utility::get()->sentry_guns.erase(features_utility::get()->features_utility::get()->sentry_guns.begin() + features_utility::get()->sentry_selected);
							}
							}));
				}
				else if (features_utility::get()->sentry_selected_type == 1) {		
					    ui->push(toggle("Shooting").add_toggle(&features_utility::get()->sentry_missles[features_utility::get()->sentry_selected].shooting));
						ui->push(toggle("Ground Targets").add_toggle(&features_utility::get()->sentry_missles[features_utility::get()->sentry_selected].ground_targets));
						ui->push(toggle("Sky Targets").add_toggle(&features_utility::get()->sentry_missles[features_utility::get()->sentry_selected].sky_targets));
						//features_utility::get()->sentry_missles[features_utility::get()->sentry_selected].shooting
						ui->push(number<int>("Number Of Missles").add_number(&features_utility::get()->sentry_missles[features_utility::get()->sentry_selected].num_missle).add_min(1).add_max(20).add_precision(0).add_step(1));
						ui->push(button("Delete")
							.set_action([=] {
								tasks::get()->delete_entity(features_utility::get()->sentry_missles[features_utility::get()->sentry_selected].entity);
								if (features_utility::get()->sentry_selected >= 0 && features_utility::get()->sentry_selected < features_utility::get()->features_utility::get()->sentry_missles.size()) {
									features_utility::get()->sentry_missles.erase(features_utility::get()->features_utility::get()->sentry_missles.begin() + features_utility::get()->sentry_selected);
								}
								}));
				}
				});

			render::push<sub>("Meteors", "World_Meteor"_joaat, [](sub* ui) {
				ui::push()->feature_toggle_int(ui, "metorite_strike"_tif, 1, 30, 1);
				ui::push()->feature_float(ui, "metorite_strike_fx_size"_FF, 0, 10, 0.1f, 1);
				ui::push()->feature_float(ui, "metorite_strike_speed"_FF, 0, 10, 0.1f, 1);
				ui->push(array<std::string, int>(xorstr_("Meteor Size"))
					.add_position(&features_utility::get()->m_meteor_world_selected)
					.add_array2(m_meteor_world, 4));
				});

			render::push<sub>("Time", "World_Time"_joaat, [](sub* ui) {
				ui::push()->feature_toggle(ui, "freeze_time"_tf);
				ui::push()->feature_toggle(ui, "sync_local_time"_tf);
				ui::push()->feature_toggle(ui, "always_day"_tf);
				ui::push()->feature_toggle(ui, "always_night"_tf);
				ui::push()->feature_toggle_float(ui, "time_lapse"_tff, 0.1f, 25.f, 0.1f);
				});

			});

		render::push<sub>("Magneto", "World_Magneto"_joaat, [](sub* ui) {
			ui::push()->array_feature_toggle(ui, "magneto_mode"_tif, m_magneto_entites_world, 3);

			ui->push(array<std::string, int>("magneto_mode_type"_if->m_name)
				.add_position(&"magneto_mode_type"_if->m_value.integer)
				.add_array2(m_magneto_type_world, 7));

			ui::push()->feature_float(ui, "magneto_mode_entites_attract_range"_FF, 0, 2147483, 0.1f, 1);
			ui::push()->feature_float(ui, "magneto_mode_up_down"_FF, -2147483, 2147483, 0.1f, 1);
			ui::push()->feature_float(ui, "magneto_mode_range"_FF, -2147483, 2147483, 0.1f, 1);
			if ("magneto_mode_type"_if->m_value.integer == 6) {
				ui::push()->feature_int(ui, "magneto_mode_delay"_if, 0, 100, 1, 1);
			}
			ui::push()->feature_toggle(ui, "magneto_mode_super_force"_tf);
			if (!"magneto_mode_super_force"_tf->m_value.toggle)
				ui::push()->feature_float(ui, "magneto_mode_force_intensity"_FF, 0, 10, 0.1f, 1);
			});

		render::push<sub>("Strike", "World_Strike"_joaat, [](sub* ui) {
			ui::push()->array_feature_toggle(ui, "airstike_mode"_tif, m_strike_shoot_pos_world, 2);

			ui->push(array<std::string, int>("airstike_mode_shoot_at"_if->m_name)
				.add_position(&"airstike_mode_shoot_at"_if->m_value.integer)
				.add_array2(m_shoot_at_world, 4));
			ui->push(array<std::string, int>("airstike_mode_speed"_tf->m_name).add_array(&m_strike_speed).add_position(&"airstike_mode_speed"_tf->m_value.integer).
				set_description("airstike_mode_speed"_tf->m_description));
			ui::push()->feature_int(ui, "airstike_mode_delay"_if, 0, 1000, 5, 1);
			ui->push(submenu("Projectile").add_target("Player_Vehicle_Weapons_Selct"_joaat).set_action([=] {
				script_utility::get()->weapon_projectile_select = 3;
				}));
			});

		render::push<sub>("Meteors", "World_Meteor"_joaat, [](sub* ui) {
			ui::push()->feature_toggle_int(ui, "metorite_strike"_tif, 1, 30, 1);
			ui::push()->feature_float(ui, "metorite_strike_fx_size"_FF, 0, 10, 0.1f, 1);
			ui::push()->feature_float(ui, "metorite_strike_speed"_FF, 0, 10, 0.1f, 1);
			ui->push(array<std::string, int>(xorstr_("Meteor Size"))
				.add_position(&features_utility::get()->m_meteor_world_selected)
				.add_array2(m_meteor_world, 4));
			});

		render::push<sub>("Time", "World_Time"_joaat, [](sub* ui) {
			ui::push()->feature_toggle(ui, "freeze_time"_tf);
			ui::push()->feature_toggle(ui, "sync_local_time"_tf);
			ui::push()->feature_toggle(ui, "always_day"_tf);
			ui::push()->feature_toggle(ui, "always_night"_tf);
			ui::push()->feature_toggle_float(ui, "time_lapse"_tff, 0.1f, 25.f, 0.1f);
			ui->push(info("Time Change"));
			ui->push(number<int>("time_hour"_if->m_name).add_number(&"time_hour"_if->m_value.integer).add_min(0).add_max(24).add_precision(0).add_step(1).add_description("time_hour"_if->m_description).set_action([] {
				NETWORK::NETWORK_OVERRIDE_CLOCK_TIME("time_hour"_if->m_value.integer, "time_minute"_if->m_value.integer, "time_second"_if->m_value.integer);
			}));
			ui->push(number<int>("time_minute"_if->m_name).add_number(&"time_minute"_if->m_value.integer).add_min(0).add_max(24).add_precision(0).add_step(1).add_description("time_minute"_if->m_description).set_action([] {
				NETWORK::NETWORK_OVERRIDE_CLOCK_TIME("time_hour"_if->m_value.integer, "time_minute"_if->m_value.integer, "time_second"_if->m_value.integer);
			}));
			ui->push(number<int>("time_second"_if->m_name).add_number(&"time_second"_if->m_value.integer).add_min(0).add_max(24).add_precision(0).add_step(1).add_description("time_second"_if->m_description).set_action([] {
				NETWORK::NETWORK_OVERRIDE_CLOCK_TIME("time_hour"_if->m_value.integer, "time_minute"_if->m_value.integer, "time_second"_if->m_value.integer);
				}));
		});
	}
}