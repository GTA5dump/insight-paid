
#include "cheat/script/script.hpp"
#include "cheat/menu/helper/ui.hpp"
#include "util/panels/panels.hpp"
#include "util/config/config.hpp"
#include "cheat/features/globals.hpp"
#include "util/math/math.hpp"
#include "util/input/input.hpp"
#include "cheat/features/features/features_utility.hpp"
#include "cheat/menu/xml/xml.hpp"
#include "cheat/script/script_utility.hpp"
#include "util/script/fiber_pool.hpp"
#include "cheat/features/features.hpp"
#include <vehicle/CVehicleModelInfo.hpp>
namespace insight {
	std::string m_drift_mode[] = {
		"Key Pressed",
		"Always"
	};
	std::string m_vehicle_god_mode[] = {
		"Normal",
		"Normal W Proofs"
	};	
	std::string m_vehicle_rainbow_mode[] = {
		"Fade",
		"Instant"
	};
	std::string m_vehicle_wheelie[] = {
		"Going Forward",
		"Going Backward"
	};
	std::string m_vehicle_wheelie_force[] = {
	"Front",
	"Back",
	"Left",
	"Right",
	};
	std::string m_vehicle_acrobatics[] = {
	"Front",
	"Back",
	"Left",
	"Right",
	"Up",
	"Down",
	};
	inline int m_autodrive_modes_selected = 0;
	std::string m_autodrive_modes[] = {
		"Wander",
		"To Waypoint"
	};
	inline int m_autodrive_approach_selected = 0;
	std::string m_autodrive_approach[] = {
		"Avoid Traffic Extremely",
		"Normal",
		"Ignorance"
	};
	std::string m_speed_meter[] = {
		"Kilometers",
		"Miles"
	};

	void f_auto_drive_start()
	{
		if (globals::h_local_vehicle())
		{
			if (m_autodrive_modes_selected == 1)
			{
				if (HUD::IS_WAYPOINT_ACTIVE())
				{
					Vector3 waypoint = vectors::get()->get_waypoint_coordinates();
					tasks::drive_to_coordinates(globals::h_local_ped(), globals::h_local_vehicle(),
						"player_vehicle_autodrive_speed"_FF->m_value.floating_point, m_autodrive_approach_selected, waypoint,
						"player_vehicle_autodrive_stoprange"_FF->m_value.floating_point);
				}
				else { notify::send("Auto Drive", "Waypoint Not Set"); }
			}
			else
			{
				tasks::drive_wander(globals::h_local_ped(), globals::h_local_vehicle(), "player_vehicle_autodrive_speed"_FF->m_value.floating_point,
					m_autodrive_approach_selected);
			}
		}
		else
		{
			notify::send("Auto Drive", "You Must Be In Vehicle");
		}
	}

	std::string m_vehicle_flymode[] = {
	"Smooth No Clip",
	"No Clip W Rotating",
	"Advance Flying"
	};
	struct s_vehicleabilities
	{
		std::string name;
		VehicleAbility Value;
	};
	const std::vector<s_vehicleabilities> m_vehicle_abilities{
	{"Boost",VehicleAbility::BOOST},
	{"Jump",VehicleAbility::JUMP},
	{"Parachute",VehicleAbility::PARACHUTE},
	{"Ramp Buggy",VehicleAbility::RAMPBUGGY}
	};
	void check_abilities_flags()
	{
		if (!globals::c_local_vehicle()) {
			return;
		}
		CVehicleModelInfo* modelinfo = (CVehicleModelInfo*)globals::c_local_vehicle()->m_model_info;

		uint16_t ability = modelinfo->m_ability_flag;

		bool does_has_jump_abilities = (ability & static_cast<uint16_t>(VehicleAbility::JUMP)) != 0;
		if (does_has_jump_abilities)
		{
			"vehicle_abilities_jump"_tf->m_value.toggle = 1;
		}
		else { "vehicle_abilities_jump"_tf->m_value.toggle = 0; }
		bool does_has_ramp_abilities = (ability & static_cast<uint16_t>(VehicleAbility::RAMPBUGGY)) != 0;
		if (does_has_ramp_abilities)
		{
			"vehicle_abilities_ramp"_tf->m_value.toggle = 1;
		}
		else { "vehicle_abilities_ramp"_tf->m_value.toggle = 0; }
		bool does_has_rocket_abilities = (ability & static_cast<uint16_t>(VehicleAbility::BOOST)) != 0;
		if (does_has_rocket_abilities)
		{
			"vehicle_abilities_rocket"_tf->m_value.toggle = 1;
		}
		else { "vehicle_abilities_rocket"_tf->m_value.toggle = 0; }
		bool does_has_boost_abilities = (ability & static_cast<uint16_t>(VehicleAbility::PARACHUTE)) != 0;
		if (does_has_boost_abilities)
		{
			"vehicle_abilities_parachuting"_tf->m_value.toggle = 1;
		}
		else { "vehicle_abilities_parachuting"_tf->m_value.toggle = 0; }

	}
	std::string m_vehicle_rockets_tys[] = {
	"Single",
	"Duel"
	};
	std::string m_vehicle_rockets_speed_tys[] = {
	"Slow",
	"Medium",
	"Fast",
	};
	std::string m_drive_thru_type[] = {
	"Vehicles",
	"Peds",
	"Objects",
	"All"
	};		
	std::string m_drive_tow_type[] = {
	"Normal",
	"W Flying"
	};	
	std::string m_doors_type[] = {
	"Drive Front",
	"Passenger Front",
	"Drive Rear",
	"Passenger Rear",
	"Bonnet",
	"Trunk"
	};
	int m_doors_fuc_type_selected[10] = {0,0,0,0,0,0,0,0,0,0};
	std::string m_doors_fuc_type[] = {
	"Close",
	"Open",
	"Break",
	"Delete"
	};
	int m_local_prostitute_car_selection = 0;
	std::string m_local_prostitute_car[] = {
	"Blow Job","Sex"
	};
	std::string m_local_vehicle_attachments[] = {
	"UFO", "GTA VC Tires","Tree Roller","Front Ramp","Back Ramp"
	};

}
namespace insight {
	void script_ui::vehicle() {
		render::push<sub>("Vehicle", "Vehicle"_joaat, [](sub* ui) {
			ui->push(submenu("Customize").add_target("Player_Vehicle_LosSantosCustom"_joaat).set_action([=] {
				script_utility::get()->lsc_sub = 0;
			}));
			ui->push(submenu("Multipliers").add_target("Player_Vehicle_Multipliers"_joaat));
			ui->push(submenu("Modifiers").add_target("Player_Vehicle_Modifiers"_joaat));
			ui->push(submenu("Weapons").add_target("Player_Vehicle_Weapons"_joaat));
			ui->push(submenu("Boost").add_target("Player_Vehicle_hornboost"_joaat));
			ui->push(submenu("Wheelie").add_target("Player_Vehicle_Wheelie"_joaat));
			ui->push(submenu("Auto Drive").add_target("Player_Vehicle_Autodrive"_joaat));
			ui->push(submenu("Fly").add_target("Player_Vehicle_Flying"_joaat));
			ui->push(submenu("Flags").add_target("Player_Vehicle_Flags"_joaat));
			ui->push(submenu("Options").add_target("Player_Vehicle_Options"_joaat));
			ui->push(submenu("Attachments").add_target("Player_Vehicle_Attachments"_joaat));
			ui->push(submenu("Acrobatics").add_target("Player_Vehicle_Acrobatics"_joaat));
			});

		render::push<sub>("Multipliers", "Player_Vehicle_Multipliers"_joaat, [](sub* ui) {
			ui::push()->feature_toggle_float(ui, "player_vehicle_acceleration"_tff, 0.f, 100.f, 1.f, 0);
			ui::push()->feature_toggle_float(ui, "player_vehicle_breakleration"_tff, 0.f, 100.f, 1.f, 0);
			ui::push()->feature_toggle_float(ui, "vehicle_quickacceleration"_tff, 0.f, 100.f, 1.f, 0);

			ui::push()->feature_toggle_float(ui, "player_plane_acceleration"_tff, 0.f, 100.f, 1.f, 0);
			ui::push()->feature_toggle_float(ui, "player_plane_breakleration"_tff, 0.f, 100.f, 1.f, 0);
			ui::push()->feature_toggle_float(ui, "plane_quickacceleration"_tff, 0.f, 100.f, 1.f, 0);

			ui::push()->feature_toggle(ui, "vehicle_quickbreak"_tf);
			});
		render::push<sub>("Modifiers", "Player_Vehicle_Modifiers"_joaat, [](sub* ui) {
			bool veh = globals::h_local_vehicle(true) != 0;
			if (veh)
				ui->push(submenu("Vehicle Handling").add_target("Player_Vehicle_Modifiers_Handling"_joaat));
			else ui->push(button("Vehicle Handling ~r~Locked").set_description("~o~Unlock: Must Be In Vehicle"));

				bool has_wep = VEHICLE::DOES_VEHICLE_HAVE_WEAPONS(globals::h_local_vehicle());
				if (has_wep)
				ui->push(submenu("Weapon Modifier").add_target("Vehicle_Weapon_Modifiers"_joaat)); 
				else
					ui->push(button("Weapon Modifiers ~r~Locked").set_description("~o~Unlock: Vehicle Must Be Equipped with Weapons"));

				ui->push(submenu("Drift Mode").add_target("Player_Vehicle_Modifiers_Handling_Drift"_joaat));
				if (veh)
				ui->push(number<float>("Gravity").add_number(&globals::c_local_vehicle()->m_gravity).
					add_min(-2147483).add_max(2147483).add_precision(2).add_step(0.1f));
				else ui->push(button("Gravity ~r~Locked").set_description("~o~Unlock: Must Be In Vehicle"));
			
			ui::push()->array_feature_toggle(ui, "player_vehicle_god_mode"_tif, m_vehicle_god_mode, 2);

			ui::push()->feature_toggle_float(ui, "vehicle_plane_turbulence"_tff, 0.f, 10.f, 0.1f, 1);
			ui->push(button("Upgrade Ride")
				.set_action([=] {insight::g_fiber_pool->queue_job([&] {
					tasks::upgrade_vehicle(globals::h_local_vehicle());
					});
					}));
			ui->push(button("Repair")
				.set_action([=] {insight::g_fiber_pool->queue_job([&] {
					tasks::fix_vehicle(globals::h_local_vehicle());
					});
					}));

			});
		render::push<sub>("Weapon", "Vehicle_Weapon_Modifiers"_joaat, [](sub* ui) {
			// yes it is cursed :(
			bool does_have_wep = false;
			std::vector<Hash> weps;
			weps.clear();
			if (auto pCVehicle = globals::c_local_vehicle()) {
				for (const auto& a : eVehicleWeapons_Gold) {
					if (ENTITY::GET_ENTITY_MODEL(globals::h_local_vehicle()) == a.hash) {
						weps.push_back(tasks::get_vehicle_weapon(a.offset1, a.offset2));
					}
				}
			}
			if (VEHICLE::DOES_VEHICLE_HAVE_WEAPONS(globals::h_local_vehicle())) {
				for (const auto& weapon : eVehicleWeapons2) {
					for (int i = 0; i < weps.size(); i++) {
						if (weps[i] == weapon.hash) {
							does_have_wep = true;
						}
						else {
							does_have_wep = false;
						}
					}
					ui->push(button((does_have_wep ? "~r~" : "") + weapon.name)
						.set_action([=] {
							if (auto pCVehicle = globals::c_local_vehicle()) {
								for (const auto& a : eVehicleWeapons_Gold) {
									if (ENTITY::GET_ENTITY_MODEL(globals::h_local_vehicle()) == a.hash) {			
										tasks::set_vehicle_weapon(weapon.hash, a.offset1, a.offset2);
									}
								}					
							}
							VEHICLE::SET_VEHICLE_FIXED(globals::h_local_vehicle());
							}));
					
				}
			}
						
			});			
		render::push<sub>("Handling", "Player_Vehicle_Modifiers_Handling"_joaat, [](sub* ui) {
			if (globals::c_local_vehicle())
			{
				ui->push(submenu("Mass").add_target("Player_Vehicle_Modifiers_Handling_Mass"_joaat));
				ui->push(submenu("Center Of Mass").add_target("Player_Vehicle_Modifiers_Handling_MassCenter"_joaat));
				ui->push(submenu("Driving & Acceleration").add_target("Player_Vehicle_Modifiers_Handling_Drive_n_Acceleration"_joaat));
				ui->push(submenu("Braking & Handbrake").add_target("Player_Vehicle_Modifiers_Handling_Break_n_Handbrake"_joaat));
				ui->push(submenu("Steering & Traction").add_target("Player_Vehicle_Modifiers_Handling_Steering_n_Traction"_joaat));
				ui->push(submenu("Suspension").add_target("Player_Vehicle_Modifiers_Handling_Suspension"_joaat));
				ui->push(submenu("Roll & Stability").add_target("Player_Vehicle_Modifiers_Handling_Roll_n_Stability"_joaat));
				ui->push(submenu("Damage").add_target("Player_Vehicle_Modifiers_Handling_Damage"_joaat));
				ui->push(submenu("Miscellaneous").add_target("Player_Vehicle_Modifiers_Handling_Miscellaneous"_joaat));
				ui->push(submenu("Load & Save").add_target("Player_Vehicle_Modifiers_Handling_Saved"_joaat));

			}				
			});		
		render::push<sub>("Mass", "Player_Vehicle_Modifiers_Handling_Mass"_joaat, [](sub* ui) {
			if (globals::c_local_vehicle())
			{
		//		CHandlingData* handling = globals::c_local_vehicle()->m_handling_data;
				ui->push(number<float>("Mass").add_number(&globals::c_local_vehicle()->m_handling_data->m_mass).
					add_min(-2147483).add_max(2147483).add_precision(2).add_step(0.1f));
				ui->push(number<float>("Initial Drag Coefficient").add_number(&globals::c_local_vehicle()->m_handling_data->m_initial_drag_coeff).
					add_min(-2147483).add_max(2147483).add_precision(2).add_step(0.1f));
				ui->push(number<float>("Downforce Multiplier").add_number(&globals::c_local_vehicle()->m_handling_data->m_downforce_multiplier).
					add_min(-2147483).add_max(2147483).add_precision(2).add_step(0.1f));
			}				
			});		
		render::push<sub>("Center Of Mass", "Player_Vehicle_Modifiers_Handling_MassCenter"_joaat, [](sub* ui) {
			if (globals::c_local_vehicle())
			{
			//	CHandlingData* handling = globals::c_local_vehicle()->m_handling_data;
				ui->push(number<float>("Centre Of Mass X").add_number(&globals::c_local_vehicle()->m_handling_data->m_centre_of_mass.x).
					add_min(-2147483).add_max(2147483).add_precision(2).add_step(0.1f));
				ui->push(number<float>("Centre Of Mass Y").add_number(&globals::c_local_vehicle()->m_handling_data->m_centre_of_mass.y).
					add_min(-2147483).add_max(2147483).add_precision(2).add_step(0.1f));
				ui->push(number<float>("Centre Of Mass Z").add_number(&globals::c_local_vehicle()->m_handling_data->m_centre_of_mass.z).
					add_min(-2147483).add_max(2147483).add_precision(2).add_step(0.1f));

				ui->push(number<float>("Inertia Multiplier X").add_number(&globals::c_local_vehicle()->m_handling_data->m_inertia_mult.x).
					add_min(-2147483).add_max(2147483).add_precision(2).add_step(0.1f));			
				ui->push(number<float>("Inertia Multiplier Y").add_number(&globals::c_local_vehicle()->m_handling_data->m_inertia_mult.y).
					add_min(-2147483).add_max(2147483).add_precision(2).add_step(0.1f));
				ui->push(number<float>("Inertia Multiplier Z").add_number(&globals::c_local_vehicle()->m_handling_data->m_inertia_mult.z).
					add_min(-2147483).add_max(2147483).add_precision(2).add_step(0.1f));
			}				
			});		
		render::push<sub>("Driving & Acceleration", "Player_Vehicle_Modifiers_Handling_Drive_n_Acceleration"_joaat, [](sub* ui) {
			if (globals::c_local_vehicle())
			{
			//	CHandlingData* handling = globals::c_local_vehicle()->m_handling_data;
				ui->push(number<float>("Buoyancy").add_number(&globals::c_local_vehicle()->m_handling_data->m_buoyancy).
					add_min(-2147483).add_max(2147483).add_precision(2).add_step(0.1f));
				ui->push(number<float>("Drive Bias Rear").add_number(&globals::c_local_vehicle()->m_handling_data->m_drive_bias_rear).
					add_min(-2147483).add_max(2147483).add_precision(2).add_step(0.1f));
				ui->push(number<float>("Drive Bias Front").add_number(&globals::c_local_vehicle()->m_handling_data->m_drive_bias_front).
					add_min(-2147483).add_max(2147483).add_precision(2).add_step(0.1f));
				ui->push(number<float>("Acceleration").add_number(&globals::c_local_vehicle()->m_handling_data->m_acceleration).
					add_min(-2147483).add_max(2147483).add_precision(2).add_step(0.1f));
				ui->push(number<float>("Drive Inertia").add_number(&globals::c_local_vehicle()->m_handling_data->m_drive_inertia).
					add_min(-2147483).add_max(2147483).add_precision(2).add_step(0.1f));
				ui->push(number<float>("Upshift").add_number(&globals::c_local_vehicle()->m_handling_data->m_upshift).
					add_min(-2147483).add_max(2147483).add_precision(2).add_step(0.1f));
				ui->push(number<float>("Downshift").add_number(&globals::c_local_vehicle()->m_handling_data->m_downshift).
					add_min(-2147483).add_max(2147483).add_precision(2).add_step(0.1f));
				ui->push(number<float>("Initial Drive Force").add_number(&globals::c_local_vehicle()->m_handling_data->m_initial_drive_force).
					add_min(-2147483).add_max(2147483).add_precision(2).add_step(0.1f));
				ui->push(number<float>("Drive Max Flat Velocity").add_number(&globals::c_local_vehicle()->m_handling_data->m_drive_max_flat_velocity).
					add_min(-2147483).add_max(2147483).add_precision(2).add_step(0.1f));
				ui->push(number<float>("Initial Drive Max Flat Velocity").add_number(&globals::c_local_vehicle()->m_handling_data->m_initial_drive_max_flat_vel).
					add_min(-2147483).add_max(2147483).add_precision(2).add_step(0.1f));
			}				
			});		
		render::push<sub>("Braking & Handbrake", "Player_Vehicle_Modifiers_Handling_Break_n_Handbrake"_joaat, [](sub* ui) {
			if (globals::c_local_vehicle())
			{
			//	CHandlingData* handling = globals::c_local_vehicle()->m_handling_data;
				ui->push(number<float>("Brake Force").add_number(&globals::c_local_vehicle()->m_handling_data->m_brake_force).
					add_min(-2147483).add_max(2147483).add_precision(2).add_step(0.1f));
				ui->push(number<float>("Brake Bias Rear").add_number(&globals::c_local_vehicle()->m_handling_data->m_brake_bias_rear).
					add_min(-2147483).add_max(2147483).add_precision(2).add_step(0.1f));
				ui->push(number<float>("Brake Bias Front").add_number(&globals::c_local_vehicle()->m_handling_data->m_brake_bias_front).
					add_min(-2147483).add_max(2147483).add_precision(2).add_step(0.1f));
				ui->push(number<float>("Handbrake Force").add_number(&globals::c_local_vehicle()->m_handling_data->m_handbrake_force).
					add_min(-2147483).add_max(2147483).add_precision(2).add_step(0.1f));
			}				
			});		
		render::push<sub>("Steering & Traction", "Player_Vehicle_Modifiers_Handling_Steering_n_Traction"_joaat, [](sub* ui) {
			if (globals::c_local_vehicle())
			{
			//	CHandlingData* handling = globals::c_local_vehicle()->m_handling_data;
				ui->push(number<float>("Steering Lock").add_number(&globals::c_local_vehicle()->m_handling_data->m_steering_lock).
					add_min(-2147483).add_max(2147483).add_precision(2).add_step(0.1f));
				ui->push(number<float>("Steering Lock Ratio").add_number(&globals::c_local_vehicle()->m_handling_data->m_steering_lock_ratio).
					add_min(-2147483).add_max(2147483).add_precision(2).add_step(0.1f));
				ui->push(number<float>("Traction Curve Max").add_number(&globals::c_local_vehicle()->m_handling_data->m_traction_curve_max).
					add_min(-2147483).add_max(2147483).add_precision(2).add_step(0.1f));
				ui->push(number<float>("Traction Curve Lateral").add_number(&globals::c_local_vehicle()->m_handling_data->m_traction_curve_lateral).
					add_min(-2147483).add_max(2147483).add_precision(2).add_step(0.1f));
				ui->push(number<float>("Traction Curve Min").add_number(&globals::c_local_vehicle()->m_handling_data->m_traction_curve_min).
					add_min(-2147483).add_max(2147483).add_precision(2).add_step(0.1f));
				ui->push(number<float>("Traction Curve Ratio").add_number(&globals::c_local_vehicle()->m_handling_data->m_traction_curve_ratio).
					add_min(-2147483).add_max(2147483).add_precision(2).add_step(0.1f));
				ui->push(number<float>("Curve Lateral").add_number(&globals::c_local_vehicle()->m_handling_data->m_curve_lateral).
					add_min(-2147483).add_max(2147483).add_precision(2).add_step(0.1f));
				ui->push(number<float>("Curve Lateral Ratio").add_number(&globals::c_local_vehicle()->m_handling_data->m_curve_lateral_ratio).
					add_min(-2147483).add_max(2147483).add_precision(2).add_step(0.1f));
				ui->push(number<float>("Traction Spring Delta Max").add_number(&globals::c_local_vehicle()->m_handling_data->m_traction_spring_delta_max).
					add_min(-2147483).add_max(2147483).add_precision(2).add_step(0.1f));
				ui->push(number<float>("Traction Spring Delta Max Ratio").add_number(&globals::c_local_vehicle()->m_handling_data->m_traction_spring_delta_max_ratio).
					add_min(-2147483).add_max(2147483).add_precision(2).add_step(0.1f));
				ui->push(number<float>("Low Speed Traction Loss Multiplier").add_number(&globals::c_local_vehicle()->m_handling_data->m_low_speed_traction_loss_mult).
					add_min(-2147483).add_max(2147483).add_precision(2).add_step(0.1f));
				ui->push(number<float>("Camber Stiffness").add_number(&globals::c_local_vehicle()->m_handling_data->m_camber_stiffness).
					add_min(-2147483).add_max(2147483).add_precision(2).add_step(0.1f));
				ui->push(number<float>("Traction Bias Front").add_number(&globals::c_local_vehicle()->m_handling_data->m_traction_bias_front).
					add_min(-2147483).add_max(2147483).add_precision(2).add_step(0.1f));
				ui->push(number<float>("Traction Bias Rear").add_number(&globals::c_local_vehicle()->m_handling_data->m_traction_bias_rear).
					add_min(-2147483).add_max(2147483).add_precision(2).add_step(0.1f));
				ui->push(number<float>("Traction Loss Multiplier").add_number(&globals::c_local_vehicle()->m_handling_data->m_traction_loss_mult).
					add_min(-2147483).add_max(2147483).add_precision(2).add_step(0.1f));
			}				
			});		
		render::push<sub>("Suspension", "Player_Vehicle_Modifiers_Handling_Suspension"_joaat, [](sub* ui) {
			if (globals::c_local_vehicle())
			{
			//	CHandlingData* handling = globals::c_local_vehicle()->m_handling_data;
				ui->push(number<float>("Suspension Force").add_number(&globals::c_local_vehicle()->m_handling_data->m_suspension_force).
					add_min(-2147483).add_max(2147483).add_precision(2).add_step(0.1f));
				ui->push(number<float>("Suspension Compression Damping").add_number(&globals::c_local_vehicle()->m_handling_data->m_suspension_comp_damp).
					add_min(-2147483).add_max(2147483).add_precision(2).add_step(0.1f));
				ui->push(number<float>("Suspension Rebound Damping").add_number(&globals::c_local_vehicle()->m_handling_data->m_suspension_rebound_damp).
					add_min(-2147483).add_max(2147483).add_precision(2).add_step(0.1f));
				ui->push(number<float>("Suspension Upper Limit").add_number(&globals::c_local_vehicle()->m_handling_data->m_suspension_upper_limit).
					add_min(-2147483).add_max(2147483).add_precision(2).add_step(0.1f));
				ui->push(number<float>("Suspension Lower Limit").add_number(&globals::c_local_vehicle()->m_handling_data->m_suspension_lower_limit).
					add_min(-2147483).add_max(2147483).add_precision(2).add_step(0.1f));
				ui->push(number<float>("Suspension Raise").add_number(&globals::c_local_vehicle()->m_handling_data->m_suspension_raise).
					add_min(-2147483).add_max(2147483).add_precision(2).add_step(0.1f));
				ui->push(number<float>("Suspension Bias Front").add_number(&globals::c_local_vehicle()->m_handling_data->m_suspension_bias_front).
					add_min(-2147483).add_max(2147483).add_precision(2).add_step(0.1f));
				ui->push(number<float>("Suspension Bias Rear").add_number(&globals::c_local_vehicle()->m_handling_data->m_suspension_bias_front).
					add_min(-2147483).add_max(2147483).add_precision(2).add_step(0.1f));
			}				
			});		
		render::push<sub>("Roll & Stability", "Player_Vehicle_Modifiers_Handling_Roll_n_Stability"_joaat, [](sub* ui) {
			if (globals::c_local_vehicle())
			{
			//	CHandlingData* handling = globals::c_local_vehicle()->m_handling_data;
				ui->push(number<float>("Anti Rollbar Force").add_number(&globals::c_local_vehicle()->m_handling_data->m_anti_rollbar_force).
					add_min(-2147483).add_max(2147483).add_precision(2).add_step(0.1f));
				ui->push(number<float>("Anti Rollbar Bias Front").add_number(&globals::c_local_vehicle()->m_handling_data->m_anti_rollbar_bias_front).
					add_min(-2147483).add_max(2147483).add_precision(2).add_step(0.1f));
				ui->push(number<float>("Anti Rollbar Bias Rear").add_number(&globals::c_local_vehicle()->m_handling_data->m_anti_rollbar_bias_rear).
					add_min(-2147483).add_max(2147483).add_precision(2).add_step(0.1f));
				ui->push(number<float>("Roll Centre Height Front").add_number(&globals::c_local_vehicle()->m_handling_data->m_roll_centre_height_front).
					add_min(-2147483).add_max(2147483).add_precision(2).add_step(0.1f));
				ui->push(number<float>("Roll Centre Height Rear").add_number(&globals::c_local_vehicle()->m_handling_data->m_roll_centre_height_rear).
					add_min(-2147483).add_max(2147483).add_precision(2).add_step(0.1f));			
			}				
			});	
		render::push<sub>("Damage", "Player_Vehicle_Modifiers_Handling_Damage"_joaat, [](sub* ui) {
			if (globals::c_local_vehicle())
			{
				//CHandlingData* handling = globals::c_local_vehicle()->m_handling_data;
				ui->push(number<float>("Collision Damage Multiplier").add_number(&globals::c_local_vehicle()->m_handling_data->m_collision_damage_mult).
					add_min(-2147483).add_max(2147483).add_precision(2).add_step(0.1f));
				ui->push(number<float>("Weapon Damage Multiplier").add_number(&globals::c_local_vehicle()->m_handling_data->m_weapon_damamge_mult).
					add_min(-2147483).add_max(2147483).add_precision(2).add_step(0.1f));
				ui->push(number<float>("Deformation Multiplier").add_number(&globals::c_local_vehicle()->m_handling_data->m_deformation_mult).
					add_min(-2147483).add_max(2147483).add_precision(2).add_step(0.1f));
				ui->push(number<float>("Engine Damage Multiplier").add_number(&globals::c_local_vehicle()->m_handling_data->m_engine_damage_mult).
					add_min(-2147483).add_max(2147483).add_precision(2).add_step(0.1f));			
			}				
			});	
		render::push<sub>("Miscellaneous", "Player_Vehicle_Modifiers_Handling_Miscellaneous"_joaat, [](sub* ui) {
			if (globals::c_local_vehicle())
			{
				//CHandlingData* handling = globals::c_local_vehicle()->m_handling_data;
				ui->push(number<float>("Petrol Tank Volume").add_number(&globals::c_local_vehicle()->m_handling_data->m_petrol_tank_volume).
					add_min(-2147483).add_max(2147483).add_precision(2).add_step(0.1f));
				ui->push(number<float>("Oil Volume").add_number(&globals::c_local_vehicle()->m_handling_data->m_oil_volume).
					add_min(-2147483).add_max(2147483).add_precision(2).add_step(0.1f));
				ui->push(number<float>("Seat Offset Distance X").add_number(&globals::c_local_vehicle()->m_handling_data->m_seat_offset_dist.x).
					add_min(-2147483).add_max(2147483).add_precision(2).add_step(0.1f));
				ui->push(number<float>("Seat Offset Distance Y").add_number(&globals::c_local_vehicle()->m_handling_data->m_seat_offset_dist.y).
					add_min(-2147483).add_max(2147483).add_precision(2).add_step(0.1f));
				ui->push(number<float>("Seat Offset Distance Z").add_number(&globals::c_local_vehicle()->m_handling_data->m_seat_offset_dist.z).
					add_min(-2147483).add_max(2147483).add_precision(2).add_step(0.1f));
			}				
			});	
		render::push<sub>("Load & Save", "Player_Vehicle_Modifiers_Handling_Saved"_joaat, [](sub* ui) {
			if (globals::c_local_vehicle())
			{

				ui->push(button("Save")
					.set_action([=] {
						auto filePath = std::filesystem::path(std::getenv(xorstr_("appdata"))).append(xorstr_("insight")).
							append(xorstr_("xml")).append(xorstr_("handlings")).append(tasks::get_keyboard_input() + xorstr_(".xml"));
							xml::get()->SaveHandlingDataToFile(filePath.generic_string());
							notify::send(xorstr_("Saved"), xorstr_("Saved.") + tasks::get_keyboard_input());				
						}));

				//
				ui->push(info(xorstr_("Saved")));
				auto filePath = std::filesystem::path(std::getenv(xorstr_("appdata"))).append(xorstr_("insight")).append(xorstr_("xml")).append(xorstr_("handlings"));
				std::filesystem::directory_iterator dirIt{ filePath.string() };
				for (auto&& dirEntry : dirIt) {
					if (dirEntry.is_regular_file()) {
						auto path = dirEntry.path();
						if (path.has_filename()) {
							if (path.extension().string() == xorstr_(".xml")) {
								ui->push(button(path.stem().string()).add_function([path] {							
										insight::xml::get()->LoadHandlingDataFromFile(path.generic_string());
										notify::send(xorstr_("File"), path.stem().generic_string() + " is Loaded");							
									}));
							}
						}
					}
				}
			}
			});	

		render::push<sub>("Drift Handling", "Player_Vehicle_Modifiers_Handling_Drift"_joaat, [](sub* ui) {
			ui::push()->array_feature_toggle(ui, "vehicle_drift_mode"_tif, m_drift_mode, 2);

			ui->push(info("Settings"));
			ui->push(number<float>("Front Bais").add_number(&features_utility::get()->m_drift_mode_handling.f_bais).
				add_min(-2147483).add_max(2147483).add_precision(2).add_step(0.1f));
			ui->push(number<float>("Inertia").add_number(&features_utility::get()->m_drift_mode_handling.inertia).
				add_min(-2147483).add_max(2147483).add_precision(2).add_step(0.1f));
			ui->push(number<float>("Curve Traction Max").add_number(&features_utility::get()->m_drift_mode_handling.traction_max).
				add_min(-2147483).add_max(2147483).add_precision(2).add_step(0.1f));
			ui->push(number<float>("Curve Traction Min").add_number(&features_utility::get()->m_drift_mode_handling.traction_min).
				add_min(-2147483).add_max(2147483).add_precision(2).add_step(0.1f));
			ui->push(button("Reset To Default")
				.set_action([=] {
					features_utility::get()->m_drift_mode_handling = features_utility::get()->m_drift_mode_default;// why do slaves work
					}));		

			});
		render::push<sub>("Weapons", "Player_Vehicle_Weapons"_joaat, [](sub* ui) {
			ui::push()->array_feature_toggle(ui, "player_vehicle_rockets"_tif, m_vehicle_rockets_tys, 2);
			ui->push(array<std::string, int>("vehicle_rockets_speed"_tf->m_name).add_array(&m_vehicle_rockets_speed_tys).add_position(&"vehicle_rockets_speed"_tf->m_value.integer).
				set_description("vehicle_rockets_speed"_tf->m_description));
			ui::push()->feature_toggle(ui, "vehicle_rockets_owned"_tf);
			ui->push(submenu("Projectile").add_target("Player_Vehicle_Weapons_Selct"_joaat).set_action([=] {
				script_utility::get()->weapon_projectile_select = 0;
				}));
			});
		render::push<sub>("Weapons", "Player_Vehicle_Weapons_Selct"_joaat, [](sub* ui) {

			for (size_t i = 0; i < eVehicleWeapons.size(); i++)
			{
				if (script_utility::get()->weapon_projectile_select == 0)
				{
					bool is_selected = "vehicle_rockets_owned"_tf->m_value.integer == rage::joaat(eVehicleWeapons[i].first);
					ui->push(button(is_selected ? "~r~" + eVehicleWeapons[i].second : eVehicleWeapons[i].second)
						.set_action([=] {
							features_utility::get()->vehicle_weapons_hash = rage::joaat(eVehicleWeapons[i].first);
							}));
				}
				else if (script_utility::get()->weapon_projectile_select == 1)
				{
					bool is_selected = "weapon_impact_airstrike"_tf->m_value.integer == rage::joaat(eVehicleWeapons[i].first);
					ui->push(button(is_selected ? "~r~" + eVehicleWeapons[i].second  : eVehicleWeapons[i].second)
						.set_action([=] {
							"weapon_impact_airstrike"_tf->m_value.integer = rage::joaat(eVehicleWeapons[i].first);
							}));
				}			
				else if (script_utility::get()->weapon_projectile_select == 2)
				{
					bool is_selected = player_options::get()->n_create_airstrike_exp[globals::get_selected_id()] == rage::joaat(eVehicleWeapons[i].first);
					ui->push(button(is_selected ? "~r~" + eVehicleWeapons[i].second  : eVehicleWeapons[i].second)
						.set_action([=] {
							player_options::get()->n_create_airstrike_exp[globals::get_selected_id()] = rage::joaat(eVehicleWeapons[i].first);
							}));
				}else if (script_utility::get()->weapon_projectile_select == 3)
				{
					
					bool is_selected = features_utility::get()->airstrike_Hash == rage::joaat(eVehicleWeapons[i].first);
					ui->push(button(is_selected ? "~r~" + eVehicleWeapons[i].second  : eVehicleWeapons[i].second)
						.set_action([=] {
							features_utility::get()->airstrike_Hash = rage::joaat(eVehicleWeapons[i].first);
							}));
				}
			}
			});

		render::push<sub>("Horn Boost", "Player_Vehicle_hornboost"_joaat, [](sub* ui) {
			ui::push()->feature_toggle_float(ui, "vehicle_hornboost"_tff, 0.f, 100.f, 1.f, 0);
			ui::push()->feature_toggle(ui, "vehicle_hornboost_ptfx"_tf);
			ui::push()->feature_toggle(ui, "vehicle_hornboost_horn"_tf);
			ui::push()->feature_toggle(ui, "vehicle_hornboost_screenfx"_tf);
			ui->push(info("Nos"));
			ui::push()->feature_toggle(ui, "vehicle_super_exaust"_tf);
			ui::push()->feature_toggle(ui, "vehicle_super_exaust_fx"_tf);
			ui::push()->feature_float(ui, "vehicle_super_exaust_shakeness"_FF, 0.f, 2.f, 0.1f, 1);
			ui::push()->feature_float(ui, "vehicle_super_exaust_boost"_FF, 0.f, 10.f, 0.1f, 1);
			ui::push()->feature_float(ui, "vehicle_super_exaust_fx_size"_FF, 0.f, 3.f, 0.1f, 1);
			ui::push()->feature_toggle(ui, "vehicle_super_exaust_screen_fx"_tf);
			ui::push()->feature_toggle(ui, "vehicle_super_exaust_sound"_tf);
			});

		render::push<sub>("Wheelie", "Player_Vehicle_Wheelie"_joaat, [](sub* ui) {
			ui::push()->array_feature_toggle(ui, "player_vehicle_wheelie_fb"_tif, m_vehicle_wheelie, 2);
			ui->push(array<std::string, int>("player_vehicle_wheelie_force"_tif->m_name).add_array(&m_vehicle_wheelie_force).add_position(&"player_vehicle_wheelie_force"_tif->m_number_value.integer).add_function([] {}));
			ui::push()->feature_float(ui, "player_vehicle_wheelie_force_multiplier"_FF, 0.f, 10.f, 0.5f, 1);
			ui::push()->feature_float(ui, "player_vehicle_wheelie_on_speed"_FF, 0, 2147483, 1.0f, 0);
			});

		render::push<sub>("Acrobatics", "Player_Vehicle_Acrobatics"_joaat, [](sub* ui) {
			ui::push()->feature_float(ui, "player_vehicle_acrobatics_multiplier"_FF, 0.f, 2.f, 0.1f, 1);
			for (int i = 0; i < sizeof(m_vehicle_acrobatics) / sizeof(m_vehicle_acrobatics[0]); i++)
			{
				ui->push(button(m_vehicle_acrobatics[i])
					.set_action([=] {
						tasks::vehicle_acrobatics(globals::h_local_vehicle(), i, "player_vehicle_acrobatics_multiplier"_FF->m_value.floating_point);
						}));
			}
			});

		render::push<sub>("Auto Drive", "Player_Vehicle_Autodrive"_joaat, [](sub* ui) {
			ui->push(array<std::string, int>("Drive Mode").add_array(&m_autodrive_modes).add_position(&m_autodrive_modes_selected));
			ui->push(array<std::string, int>("Drive Approach").add_array(&m_autodrive_approach).add_position(&m_autodrive_approach_selected));
			ui::push()->feature_float(ui, "player_vehicle_autodrive_speed"_FF, 0.f, 200.f, 1.f, 0);
			if (m_autodrive_modes_selected)
			{
				ui::push()->feature_float(ui, "player_vehicle_autodrive_stoprange"_FF, 0.f, 50.f, 1.f, 0);
			}
			ui->push(button("Start Drive Task")
				.set_action([=] {
					f_auto_drive_start();
					}));
			ui->push(button("End Drive Task")
				.set_action([=] {
					TASK::CLEAR_PED_TASKS(globals::h_local_ped());
					}));
			});
		render::push<sub>("Flying", "Player_Vehicle_Flying"_joaat, [](sub* ui) {
			ui::push()->array_feature_toggle(ui, "player_vehicle_flymode"_tif, m_vehicle_flymode, 3);

		//	ui::push()->feature_float(ui, "player_vehicle_flymode_speed"_FF, 0.1f, 3.0f, 0.1f, 1);
			if ("player_vehicle_flymode"_tif->m_number_value.integer == 0) {
				ui::push()->feature_toggle_float(ui, "player_vehicle_flymode1_allowAcceleration"_tff, 0.1f, 10.f, 0.1f, 1);
				ui::push()->feature_toggle_float(ui, "player_vehicle_flymode1_allowDeceleration"_tff, 0.1f, 10.f, 0.1f, 1);
			}
			if ("player_vehicle_flymode"_tif->m_number_value.integer == 1) {
				ui::push()->feature_float(ui, "player_vehicle_flymode2_speed"_FF, 0.0f, 1000.f, 0.1f, 1);
				ui::push()->feature_float(ui, "player_vehicle_flymode2_rotationX"_FF, 0.0f, 100.f, 0.1f, 1);
				ui::push()->feature_float(ui, "player_vehicle_flymode2_rotationY"_FF, 0.0f, 100.f, 0.1f, 1);
				ui::push()->feature_float(ui, "player_vehicle_flymode2_rotationZ"_FF, 0.0f, 100.f, 0.1f, 1);
				ui::push()->feature_float(ui, "player_vehicle_flymode2_rotation_speed"_FF, 0.0f, 100.f, 0.1f, 1);
			}
			if ("player_vehicle_flymode"_tif->m_number_value.integer == 2) {
				ui::push()->feature_float(ui, "player_vehicle_flymode3_flying_speed"_FF, 0.0f, 1000.f, 0.1f, 1);
				ui::push()->feature_float(ui, "player_vehicle_flymode3_rotation_speed"_FF, 0.0f, 100.f, 0.1f, 1);
			}

			});
		render::push<sub>("Attachments", "Player_Vehicle_Attachments"_joaat, [](sub* ui) {
			for (int i = 0; i < std::size(m_local_vehicle_attachments); i++)
			{
				ui->push(button(m_local_vehicle_attachments[i]).set_action([=] {
					insight::g_fiber_pool->queue_job([&] {
						tasks::vehicle_attachments(globals::h_local_vehicle(), i);
						});
					}));
			}
			ui->push(button(xorstr_("Clear All Attachments")).set_action([=] {
				insight::g_fiber_pool->queue_job([&] {
					tasks::clear_vehicle_attachments(globals::h_local_vehicle());
					});
				}));
			});
		render::push<sub>("Flags", "Player_Vehicle_Flags"_joaat, [](sub* ui) {
			ui->push(submenu("Abilities").add_target("Player_Vehicle_Flags_Abilities"_joaat).set_action([=] {
				check_abilities_flags();
				}));
			ui::push()->feature_toggle(ui, "vehicle_super_mk2"_tf);
			ui::push()->feature_toggle(ui, "vehicle_instant_rocket_boost"_tf);
			ui::push()->feature_toggle(ui, "vehicle_instant_jump_boost"_tf);
			ui::push()->feature_toggle(ui, "vehicle_heavy"_tf);
			ui::push()->feature_toggle(ui, "vehicle_seatbelt"_tf);
			ui::push()->feature_toggle(ui, "vehicle_slipery_tyres"_tf);
			ui::push()->feature_toggle(ui, "vehicle_drive_underwater"_tf);
			ui::push()->array_feature_toggle(ui, "player_vehicle_drivethru"_tif, m_drive_thru_type, 4);
			ui->push(info("Matrix"));
			ui::push()->feature_toggle_float(ui, "vehicle_wheels_width"_tff, 0.f, 100.f, 0.1f, 1);
			ui::push()->feature_toggle_float(ui, "vehicle_wheels_height"_tff, 0.f, 100.f, 0.1f, 1);
			ui::push()->feature_toggle_float(ui, "vehicle_set_size"_tff, 0.f, 100.f, 0.1f, 1);
			});

		render::push<sub>("Abilities", "Player_Vehicle_Flags_Abilities"_joaat, [](sub* ui) {
			ui::push()->feature_toggle(ui, "vehicle_abilities_jump"_tf);
			ui::push()->feature_toggle(ui, "vehicle_abilities_ramp"_tf);
			ui::push()->feature_toggle_float(ui, "vehicle_abilities_rocket"_tff, 0.f, 3.f, 0.1f, 1);

			ui::push()->feature_toggle_float(ui, "vehicle_abilities_parachuting"_tff, 0.f, 3.f, 0.1f, 1);



			});
		render::push<sub>("Abilities", "Player_Vehicle_Options"_joaat, [](sub* ui) {
			ui->push(submenu("On Exit").add_target("Player_Vehicle_On_Exit"_joaat));
			ui->push(submenu("Doors").add_target("Player_Vehicle_Doors"_joaat).set_action([=] {
				script_utility::get()->Player_Vehicle_Doors_Entity = globals::h_local_vehicle();
				script_utility::get()->doors_locked = VEHICLE::GET_VEHICLE_DOORS_LOCKED_FOR_PLAYER(script_utility::get()->Player_Vehicle_Doors_Entity, globals::player_id);
			}));
			ui->push(submenu("Particle FX").add_target("Player_Vehicle_PTFX"_joaat));
			ui::push()->array_feature_toggle(ui, "vehicle_speed_meter"_tif, m_speed_meter, 2);
			ui::push()->feature_toggle(ui, "vehicle_auto_fix"_tf);
			ui::push()->feature_toggle(ui, "vehicle_invisible"_tf);
			ui::push()->array_feature_toggle(ui, "vehicle_towmode"_tif, m_drive_tow_type, 2);
			ui::push()->feature_toggle(ui, "vehicle_auto_flip"_tf);
			ui::push()->feature_toggle(ui, "vehicle_anti_lockon"_tf);
			ui::push()->feature_toggle_float(ui, "player_vehicle_headlight_intensity"_tff, 0.f, 100.f, 1.f, 0);
			ui::push()->feature_toggle(ui, "vehicle_instant_enter_n_exit"_tf);
			ui::push()->feature_toggle(ui, "bike_container_rider"_tf);
				ui::push()->array_feature_toggle(ui, "vehicle_paint_rainbow"_tif, m_vehicle_rainbow_mode, 2);
				if ("vehicle_paint_rainbow"_tif->m_toggle_value.toggle) {
					if ("vehicle_paint_rainbow"_tif->m_number_value.integer == 0) {
						ui::push()->feature_float(ui, "vehicle_paint_rainbow_speed1"_FF, 0.0f, 5.f, 0.1f, 1);
					}
					else if ("vehicle_paint_rainbow"_tif->m_number_value.integer == 1) {
						ui::push()->feature_float(ui, "vehicle_paint_rainbow_speed2"_FF, 0.0f, 5.f, 0.1f, 1);
					}
				}
			ui->push(array<std::string, int>(xorstr_("Prostitute")).add_array(&m_local_prostitute_car).add_position(&m_local_prostitute_car_selection).set_use_enter_only(true).set_action([=] {
				insight::g_fiber_pool->queue_job([&] {
					if (globals::h_local_vehicle())
						tasks::stripper_car(globals::h_local_vehicle(), m_local_prostitute_car_selection);
					});
				}));

			});	
	render::push<sub>("Particles", "Player_Vehicle_PTFX"_joaat, [](sub* ui) {
		ui::push()->array_feature_toggle(ui, "vehicle_ptfx_f_right_tire"_tif, particle_effects, std::size(particle_effects));
		ui::push()->feature_float(ui, "vehicle_ptfx_f_right_tire_scale"_FF, 0.0f, 5.f, 0.1f, 1);
		ui::push()->feature_float(ui, "vehicle_ptfx_f_right_tire_scale_d"_FF, 0.0f, 10.f, 0.1f, 1);
	
		ui::push()->array_feature_toggle(ui, "vehicle_ptfx_f_left_tire"_tif, particle_effects, std::size(particle_effects));
		ui::push()->feature_float(ui, "vehicle_ptfx_f_left_tire_scale"_FF, 0.0f, 5.f, 0.1f, 1);
		ui::push()->feature_float(ui, "vehicle_ptfx_f_left_tire_scale_d"_FF, 0.0f, 10.f, 0.1f, 1);
	
		ui::push()->array_feature_toggle(ui, "vehicle_ptfx_r_right_tire"_tif, particle_effects, std::size(particle_effects));
		ui::push()->feature_float(ui, "vehicle_ptfx_r_right_tire_scale"_FF, 0.0f, 5.f, 0.1f, 1);
		ui::push()->feature_float(ui, "vehicle_ptfx_r_right_tire_scale_d"_FF, 0.0f, 10.f, 0.1f, 1);
	
		ui::push()->array_feature_toggle(ui, "vehicle_ptfx_r_left_tire"_tif, particle_effects, std::size(particle_effects));
		ui::push()->feature_float(ui, "vehicle_ptfx_r_left_tire_scale"_FF, 0.0f, 5.f, 0.1f, 1);	
		ui::push()->feature_float(ui, "vehicle_ptfx_r_left_tire_scale_d"_FF, 0.0f, 10.f, 0.1f, 1);	
		});		
		render::push<sub>("On Exit", "Player_Vehicle_On_Exit"_joaat, [](sub* ui) {
			ui::push()->feature_toggle(ui, "vehicle_keep_engine_on"_tf);
			ui::push()->feature_toggle(ui, "vehicle_auto_stop_on_exit"_tf);
			ui::push()->feature_toggle(ui, "vehicle_auto_lock_on_exit"_tf);
			});		
		render::push<sub>("Doors", "Player_Vehicle_Doors"_joaat, [](sub* ui) {
			ui->push(toggle("Lock").add_toggle(&script_utility::get()->doors_locked).set_action([=] {
				if (script_utility::get()->doors_locked)
				{
					VEHICLE::SET_VEHICLE_DOORS_LOCKED_FOR_ALL_PLAYERS(script_utility::get()->Player_Vehicle_Doors_Entity, true);
					VEHICLE::SET_VEHICLE_DOORS_LOCKED_FOR_NON_SCRIPT_PLAYERS(script_utility::get()->Player_Vehicle_Doors_Entity, true);
					VEHICLE::SET_VEHICLE_DOORS_LOCKED(script_utility::get()->Player_Vehicle_Doors_Entity, 2);

				}
				else
				{
					VEHICLE::SET_VEHICLE_DOORS_LOCKED_FOR_ALL_PLAYERS(script_utility::get()->Player_Vehicle_Doors_Entity, false);
					VEHICLE::SET_VEHICLE_DOORS_LOCKED_FOR_NON_SCRIPT_PLAYERS(script_utility::get()->Player_Vehicle_Doors_Entity, false);
					VEHICLE::SET_VEHICLE_DOORS_LOCKED(script_utility::get()->Player_Vehicle_Doors_Entity, 0);

				}
				}));

			for (int i = 0; i < VEHICLE::GET_NUMBER_OF_VEHICLE_DOORS(script_utility::get()->Player_Vehicle_Doors_Entity); i++)
			{
				bool txt_empty = m_doors_type[i].empty();
				ui->push(array<std::string, int>(txt_empty ? "Unk" : m_doors_type[i]).add_array(&m_doors_fuc_type).
					add_position(&m_doors_fuc_type_selected[i]).set_action([=] {
						if (input::get()->is_enter_pressed())
						{
							if (m_doors_fuc_type_selected[i] == 0)
							{
								VEHICLE::SET_VEHICLE_DOOR_SHUT(script_utility::get()->Player_Vehicle_Doors_Entity, i, false);
							}
							else if (m_doors_fuc_type_selected[i] == 1)
							{
								VEHICLE::SET_VEHICLE_DOOR_OPEN(script_utility::get()->Player_Vehicle_Doors_Entity, i, false, false);
							}
							else if (m_doors_fuc_type_selected[i] == 2)
							{
								VEHICLE::SET_VEHICLE_DOOR_BROKEN(script_utility::get()->Player_Vehicle_Doors_Entity, i, false);
							}		
							else if (m_doors_fuc_type_selected[i] == 3)
							{
								VEHICLE::SET_VEHICLE_DOOR_BROKEN(script_utility::get()->Player_Vehicle_Doors_Entity, i, true);
							}
						}
						}));

			}
			});		
	}
}