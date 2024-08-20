#include "cheat/script/script.hpp"
#include "cheat/menu/helper/ui.hpp"
#include "cheat/features/globals.hpp"
#include "util/panels/panels.hpp"
#include "util/config/config.hpp"
#include "cheat/features/globals.hpp"
#include "cheat/features/features/features_utility.hpp"
#include "game/rage/vfx_types.hpp"
#include "game/rage/grcTextureStore.hpp"

namespace insight {
	struct backup_textures {
		rage::grcTextureStored texture;
		Hash dir;
		std::string name;
	};
	std::vector<backup_textures> g_backup_texture;
const char* hud_color_lables_names[] = {
	"Pure White",
	"White",
	"Black",
	"Grey",
	"Grey Light",
	"Grey Dark",
	"Red",
	"Red Light",
	"Red Dark",
	"Blue",
	"Blue Light",
	"Blue Dark",
	"Yellow",
	"Yellow Light",
	"Yellow Dark",
	"Orange",
	"Orange Light",
	"Orange Dark",
	"Green",
	"Green Light",
	"Green Dark",
	"Purple",
	"Purple Light",
	"Purple Dark",
	"Pink",
	"Radar Health",
	"Radar Armour",
	"Radar Damage",
	"Player 1",
	"Player 2",
	"Player 3",
	"Player 4",
	"Player 5",
	"Player 6",
	"Player 7",
	"Player 8",
	"Player 9",
	"Player 10",
	"Player 11",
	"Player 12",
	"Player 13",
	"Player 14",
	"Player 15",
	"Player 16",
	"Player 17",
	"Player 18",
	"Player 19",
	"Player 20",
	"Player 21",
	"Player 22",
	"Player 23",
	"Player 24",
	"Player 25",
	"Player 26",
	"Player 27",
	"Player 28",
	"Player 29",
	"Player 30",
	"Player 31",
	"Player 32",
	"Simple Blip Default",
	"Menu Blue",
	"Menu Grey Light",
	"Menu Blue Extra Dark",
	"Menu Yellow",
	"Menu Yellow Dark",
	"Menu Green",
	"Menu Grey",
	"Menu Grey Dark",
	"Menu Highlight",
	"Menu Standard",
	"Menu Dimmed",
	"Menu Extra Dimmed",
	"Brief Title",
	"Mid Grey MP",
	"Player 1 Dark",
	"Player 2 Dark",
	"Player 3 Dark",
	"Player 4 Dark",
	"Player 5 Dark",
	"Player 6 Dark",
	"Player 7 Dark",
	"Player 8 Dark",
	"Player 9 Dark",
	"Player 10 Dark",
	"Player 11 Dark",
	"Player 12 Dark",
	"Player 13 Dark",
	"Player 14 Dark",
	"Player 15 Dark",
	"Player 16 Dark",
	"Player 17 Dark",
	"Player 18 Dark",
	"Player 19 Dark",
	"Player 20 Dark",
	"Player 21 Dark",
	"Player 22 Dark",
	"Player 23 Dark",
	"Player 24 Dark",
	"Player 25 Dark",
	"Player 26 Dark",
	"Player 27 Dark",
	"Player 28 Dark",
	"Player 29 Dark",
	"Player 30 Dark",
	"Player 31 Dark",
	"Player 32 Dark",
	"Bronze",
	"Silver",
	"Gold",
	"Platinum",
	"Gang 1",
	"Gang 2",
	"Gang 3",
	"Gang 4",
	"Same Crew",
	"Freemode",
	"Pause BG",
	"Friendly",
	"Enemy",
	"Location",
	"Pickup",
	"Pause Singleplayer",
	"Freemode Dark",
	"Inactive Mission",
	"Damage",
	"Pink Light",
	"PM Item Highlight",
	"Script Variable",
	"Yoga",
	"Tennis",
	"Golf",
	"Shooting Range",
	"Flight School",
	"North Blue",
	"Social Club",
	"Platform Blue",
	"Platform Green",
	"Platform Grey",
	"Facebook Blue",
	"In-Game BG",
	"Darts",
	"Waypoint",
	"Michael",
	"Franklin",
	"Trevor",
	"Golf P1",
	"Golf P2",
	"Golf P3",
	"Golf P4",
	"Waypoint Light",
	"Waypoint Dark",
	"panel Light",
	"Michael Dark",
	"Franklin Dark",
	"Trevor Dark",
	"Objective Route",
	"Pause Map Tint",
	"Pause Deselect",
	"PM Weapons Purchasable",
	"PM Weapons Locked",
	"End Screen BG",
	"Chop",
	"Pausemap Tint Half",
	"North Blue Official",
	"Script Variable 2",
	"H",
	"H Dark",
	"T",
	"T Dark",
	"HS Hard",
	"Controller Michael",
	"Controller Franklin",
	"Controller Trevor",
	"Controller Chop",
	"Video Editor Video",
	"Video Editor Audio",
	"Video Editor Text",
	"HB Blue",
	"HB Yellow",
	"Video Editor Score",
	"Video Editor Audio Fadeout",
	"Video Editor Text Fadeout",
	"Video Editor Score Fadeout",
	"Heist Background",
	"Video Editor Ambient",
	"Video Editor Ambient Fadeout",
	"GB",
	"G",
	"B",
	"Low Flow",
	"Low Flow Dark",
	"G1",
	"G2",
	"G3",
	"G4",
	"G5",
	"G6",
	"G7",
	"G8",
	"G9",
	"G10",
	"G11",
	"G12",
	"G13",
	"G14",
	"G15",
	"Adversary",
	"Degen Red",
	"Degen Yellow",
	"Degen Green",
	"Degen Cyan",
	"Degen Blue",
	"Degen Magenta",
	"Stunt 1",
	"Stunt 2",
	"Special Race Series",
	"Special Race Series Dark",
	"CS",
	"CS Dark",
	"Tech Green",
	"Tech Green Dark",
	"Tech Red",
	"Tech Green Very Dark"
};
std::string m_vfx_color[] = {
	"Settings", "Rainbow"
};
int selected_hud_label;
std::string m_chuf_flags_world[] = {
"Tiny",
"Standard",
"Huge",
"Random"
};

}
namespace insight {
	void script_ui::miscellaneous() {
		render::push<sub>("Miscellaneous", "Miscellaneous"_joaat, [](sub* ui) {
			ui->push(submenu("Game Textures Swaping").add_target("Miscellaneous_Game_Texture_Swapping"_joaat));
			ui->push(submenu("Disables").add_target("Miscellaneous_Disables"_joaat));
			ui->push(submenu("Radio").add_target("Miscellaneous_Radio"_joaat));
			ui->push(submenu("VFX").add_target("Miscellaneous_VFX"_joaat));
			ui->push(submenu("Heli Chauffeur").add_target("Miscellaneous_Heli_Chauffeur"_joaat));
			ui->push(info("General"));
			ui::push()->feature_toggle(ui, "bypass_restricted_areas"_tf);
			ui::push()->feature_toggle(ui, "potato_pc_mode"_tf);
			ui::push()->feature_toggle(ui, "snow_trails"_tf);
			ui::push()->feature_toggle_float(ui, "camera_zoom"_tff, 0, 150);
			ui::push()->feature_toggle_float(ui, "gta_1_camera"_tff, 0, 150);

			ui->push(button("Disable Transaction Promot").add_function([] {
				if (HUD::BUSYSPINNER_IS_ON()) HUD::BUSYSPINNER_OFF();
				}));
			ui->push(button("Rest Graphics In Your Area").add_function([] {
				STREAMING::SET_FOCUS_ENTITY(globals::h_local_ped());
				}));
			ui->push(button("Bail To Single Player").add_function([] {
				NETWORK::NETWORK_BAIL(0, 0, 0);
				}));
			});
		render::push<sub>("Radio", "Miscellaneous_Game_Texture_Swapping"_joaat, [](sub* ui) {
			ui->push(button("Replace All The Textures").add_function([] {
				for (const auto& pair : pointers::get()->g_texture_store->GetAllDictionaries()) {
					if (pair.first == 2724885213)
						continue;
					for (const std::string& name : pair.second->GetAllTextureNames()) {
						for (const std::string& replacement : pointers::get()->g_texture_store->FindDictionary(2724885213)->GetAllTextureNames()) {
							if (name == replacement) {
								rage::grcTextureStored clone_texture = pair.second->FindTexture(name)->CreateCopy();
								bool found = false;
								for (int i = 0; i < g_backup_texture.size(); i++)
								{
									if (g_backup_texture[i].name == name) {
										found = true;
									}
								}
								if (!found) {
									g_backup_texture.push_back({ clone_texture,pair.first,name });
								}
								LOG(INFO) << name;
								rage::grcTexture* texture_to_swap = pointers::get()->g_texture_store->FindDictionary(2724885213)->FindTexture(replacement);
								pair.second->FindTexture(name)->Swap(texture_to_swap);
							}
						}
					}
				}
				}));
			ui->push(button("Restore Original Textures").add_function([] {
				for (int i = 0; i < g_backup_texture.size(); i++)
				{
					pointers::get()->g_texture_store->FindDictionary(g_backup_texture[i].dir)->FindTexture(g_backup_texture[i].name)->Swap(g_backup_texture[i].texture);
				}
				}));
			ui->push(button("How To Use").add_function([] {
				notify::send("Texture Replacement",
				"To replace a texture, open [OpenIV], locate the desired [ytd] texture, identify its name, add a matching PNG or JPG file with the same name to the [insight/textures] folder, and click the [Replace Textures] button.",{0,0,0,255},10000);
				}));
			});
		/*
					ui->push(button("Stop")
				.set_action([=] {
					rage::grcTexture* replacetex = pointers::get()->g_texture_store->FindDictionary(2724885213)->FindTexture("stars");
					pointers::get()->g_texture_store->FindDictionary(4177616949)->FindTexture("starfield")->Swap(replacetex);
					for (const auto& pair : pointers::get()->g_texture_store->GetAllDictionaries()) {
					
						for (const std::string& name : pair.second->GetAllTextureNames()) {
							
						}
					}
					ui->push(button("WTF")
						.set_action([=] {
							rage::grcTexture* replacetex = pointers::get()->g_texture_store->FindDictionary(2724885213)->FindTexture("stars");
							pointers::get()->g_texture_store->FindDictionary(4177616949)->FindTexture("starfield")->Swap(replacetex);
							}));

		*/
		render::push<sub>("Radio", "Miscellaneous_Radio"_joaat, [](sub* ui) {
			ui::push()->feature_toggle(ui, "player_mobile_radio"_tf);
			ui->push(button("Skip Track").add_function([] {
				AUDIO::SKIP_RADIO_FORWARD();
				}));
			});

		render::push<sub>("Disable", "Miscellaneous_Disables"_joaat, [](sub* ui) {
			ui::push()->feature_toggle(ui, "disable_hud"_tf);
			ui::push()->feature_toggle(ui, "disable_minimap"_tf);
			ui::push()->feature_toggle(ui, "disable_notifications"_tf);
			ui::push()->feature_toggle(ui, "disable_game_recording"_tf);
			ui::push()->feature_toggle(ui, "disable_phone"_tf);
			ui::push()->feature_toggle(ui, "disable_stunt_jump"_tf);
			ui::push()->feature_toggle(ui, "disable_cinematic"_tf);
			ui::push()->feature_toggle(ui, "disable_cutscenes"_tf);
			ui::push()->feature_toggle(ui, "disable_chat_profanity"_tf);
			});
		render::push<sub>("VFX", "Miscellaneous_VFX"_joaat, [](sub* ui) {
			ui->push(submenu("Azimuth").add_target("Miscellaneous_VFX_Azimuth"_joaat));
			ui->push(submenu("Zenith").add_target("Miscellaneous_VFX_Zenith"_joaat));
			ui->push(submenu("Sun").add_target("Miscellaneous_VFX_Sun"_joaat));
			ui->push(submenu("Sky").add_target("Miscellaneous_VFX_Sky"_joaat));
			ui->push(submenu("Influence & Scatter").add_target("Miscellaneous_VFX_Influence"_joaat));
			ui->push(submenu("Stars & Moon").add_target("Miscellaneous_VFX_Moon"_joaat));
			ui->push(submenu("Wheel").add_target("Miscellaneous_VFX_Wheels"_joaat));
			ui->push(submenu("Waypoint Pathing").add_target("Miscellaneous_VFX_Waypoint"_joaat));
			ui->push(submenu("Screen").add_target("Miscellaneous_VFX_Screen"_joaat));
			//ui->push(submenu("Foot Trails").add_target("Miscellaneous_VFX_Foot"_joaat));
			ui::push()->feature_toggle_float(ui, "m_vfx_fog"_tff, 0, 150, 0.001f, 3);
			ui::push()->feature_toggle(ui, "m_disable_sky"_tf);
			//	ui::push()->feature_toggle_float(ui, "m_vfx_distance_sun"_tff, 0, 0.99,0.001f,3); not that polished offset
			//	ui::push()->feature_toggle_float(ui, "m_vfx_distance_unk"_tff, 0, 0.99,0.001f,3); not that polished offset
			//	ui::push()->feature_toggle_float(ui, "m_vfx_distance_fov"_tff, 0, 0.99,0.001f,3); not that polished offset

			});
		render::push<sub>("Azimuth", "Miscellaneous_VFX_Azimuth"_joaat, [](sub* ui) {
			ui->push(submenu("East").add_target("Miscellaneous_VFX_Azimuth_East"_joaat));
			ui->push(submenu("West").add_target("Miscellaneous_VFX_Azimuth_West"_joaat));
			ui::push()->feature_float(ui, "m_azimuth_transition_intensity"_FF, 0.f, 200, 0.1f);
			ui::push()->feature_float(ui, "m_azimuth_transition_position"_FF, 0.f, 200, 0.1f);

			});
		render::push<sub>("East", "Miscellaneous_VFX_Azimuth_East"_joaat, [](sub* ui) {
			ui::push()->array_feature_toggle(ui, "m_azimuth_east_color"_tif, m_vfx_color, 2);
			if ("m_azimuth_east_color"_tif->m_number_value.integer == 0) {
				ui->push(number<float>("Red").add_number(&features_utility::get()->m_azimuth_east_color.x).add_min(0.0f).add_max(255.f).add_precision(2).add_step(0.01));
				ui->push(number<float>("Green").add_number(&features_utility::get()->m_azimuth_east_color.y).add_min(0.0f).add_max(255.f).add_precision(2).add_step(0.01));
				ui->push(number<float>("Blue").add_number(&features_utility::get()->m_azimuth_east_color.z).add_min(0.0f).add_max(255.f).add_precision(2).add_step(0.01));
			}
			else {
				ui::push()->feature_float(ui, "m_azimuth_east_color_fade_speed"_FF, 0.f, 10, 0.1f);
			}
			ui::push()->feature_float(ui, "m_azimuth_east_color_intensity"_FF, 0.f, 200, 0.1f);
			});
		render::push<sub>("West", "Miscellaneous_VFX_Azimuth_West"_joaat, [](sub* ui) {
			ui::push()->array_feature_toggle(ui, "m_azimuth_west_color"_tif, m_vfx_color, 2);
			if ("m_azimuth_west_color"_tif->m_number_value.integer == 0) {
				ui->push(number<float>("Red").add_number(&features_utility::get()->m_azimuth_west_color.x).add_min(0.0f).add_max(255.f).add_precision(2).add_step(0.01));
				ui->push(number<float>("Green").add_number(&features_utility::get()->m_azimuth_west_color.y).add_min(0.0f).add_max(255.f).add_precision(2).add_step(0.01));
				ui->push(number<float>("Blue").add_number(&features_utility::get()->m_azimuth_west_color.z).add_min(0.0f).add_max(255.f).add_precision(2).add_step(0.01));
			}
			else {
				ui::push()->feature_float(ui, "m_azimuth_west_color_fade_speed"_FF, 0.f, 10, 0.1f);
			}
			ui::push()->feature_float(ui, "m_azimuth_west_color_intensity"_FF, 0.f, 200, 0.1f);
			});

		render::push<sub>("Zenith", "Miscellaneous_VFX_Zenith"_joaat, [](sub* ui) {
			ui::push()->array_feature_toggle(ui, "m_zenith_color"_tif, m_vfx_color, 2);
			if ("m_zenith_color"_tif->m_number_value.integer == 0) {
				ui->push(number<float>("Red").add_number(&features_utility::get()->m_zenith_color.x).add_min(0.0f).add_max(255.f).add_precision(2).add_step(0.01));
				ui->push(number<float>("Green").add_number(&features_utility::get()->m_zenith_color.y).add_min(0.0f).add_max(255.f).add_precision(2).add_step(0.01));
				ui->push(number<float>("Blue").add_number(&features_utility::get()->m_zenith_color.z).add_min(0.0f).add_max(255.f).add_precision(2).add_step(0.01));
			}
			else {
				ui::push()->feature_float(ui, "m_zenith_color_fade_speed"_FF, 0.f, 10, 0.1f);
			}
			ui::push()->feature_float(ui, "m_zenith_color_intensity"_FF, 0.f, 200, 0.1f);
			ui::push()->feature_float(ui, "m_zenith_blend_start"_FF, 0.f, 200, 0.1f);
			ui::push()->feature_float(ui, "m_zenith_transition_east_blend"_FF, 0.f, 200, 0.1f);
			ui::push()->feature_float(ui, "m_zenith_transition_intensity"_FF, 0.f, 200, 0.1f);
			ui::push()->feature_float(ui, "m_zenith_transition_position"_FF, 0.f, 200, 0.1f);
			ui::push()->feature_float(ui, "m_zenith_transition_west_blend"_FF, 0.f, 200, 0.1f);

			});
		render::push<sub>("Sun", "Miscellaneous_VFX_Sun"_joaat, [](sub* ui) {
			ui::push()->array_feature_toggle(ui, "m_sun_color"_tif, m_vfx_color, 2);
			if ("m_sun_color"_tif->m_number_value.integer == 0) {
				ui->push(number<float>("Red").add_number(&features_utility::get()->m_sun_color.x).add_min(0.0f).add_max(255.f).add_precision(2).add_step(0.01));
				ui->push(number<float>("Green").add_number(&features_utility::get()->m_sun_color.y).add_min(0.0f).add_max(255.f).add_precision(2).add_step(0.01));
				ui->push(number<float>("Blue").add_number(&features_utility::get()->m_sun_color.z).add_min(0.0f).add_max(255.f).add_precision(2).add_step(0.01));
			}
			else {
				ui::push()->feature_float(ui, "m_sun_color_fade_speed"_FF, 0.f, 10, 0.1f);
			}
			ui::push()->feature_float(ui, "m_sun_color_size"_FF, 0.f, 200, 0.1f);
			ui::push()->feature_float(ui, "m_sun_color_hdr"_FF, 0.f, 200, 0.1f);
			ui::push()->feature_float(ui, "m_sun_color_miephase"_FF, 0.f, 200, 0.1f);
			ui::push()->feature_float(ui, "m_sun_color_miescatter"_FF, 0.f, 200, 0.1f);
			ui::push()->feature_float(ui, "m_sun_color_mie_intensity_mult"_FF, 0.f, 200, 0.1f);
			});
		render::push<sub>("Sky", "Miscellaneous_VFX_Sky"_joaat, [](sub* ui) {
			ui::push()->array_feature_toggle(ui, "m_cloud_color"_tif, m_vfx_color, 2);
			if ("m_cloud_color"_tif->m_number_value.integer == 0) {
				ui->push(number<float>("Red").add_number(&features_utility::get()->m_cloud_color.x).add_min(0.0f).add_max(255.f).add_precision(2).add_step(0.01));
				ui->push(number<float>("Green").add_number(&features_utility::get()->m_cloud_color.y).add_min(0.0f).add_max(255.f).add_precision(2).add_step(0.01));
				ui->push(number<float>("Blue").add_number(&features_utility::get()->m_cloud_color.z).add_min(0.0f).add_max(255.f).add_precision(2).add_step(0.01));
			}
			else {
				ui::push()->feature_float(ui, "m_cloud_fade_speed"_FF, 0.f, 10, 0.1f);
			}
			ui::push()->feature_float(ui, "m_cloud_density_mult"_FF, 0.f, 200, 0.1f);
			ui::push()->feature_float(ui, "m_cloud_density_bias"_FF, 0.f, 200, 0.1f);
			ui::push()->feature_float(ui, "m_cloud_dither_strength"_FF, 0.f, 200, 0.1f);
			ui::push()->feature_float(ui, "m_cloud_edge_strength"_FF, 0.f, 200, 0.1f);
			ui::push()->feature_float(ui, "m_cloud_fadeout"_FF, 0.f, 200, 0.1f);
			ui::push()->feature_float(ui, "m_cloud_hdr"_FF, 0.f, 200, 0.1f);
			ui::push()->feature_float(ui, "m_cloud_offset"_FF, 0.f, 200, 0.1f);
			ui::push()->feature_float(ui, "m_cloud_overall_color"_FF, 0.f, 200, 0.1f);
			ui::push()->feature_float(ui, "m_cloud_overall_strength"_FF, 0.f, 200, 0.1f);
			ui::push()->feature_float(ui, "m_cloud_shadow_strength"_FF, 0.f, 200, 0.1f);
			ui::push()->feature_float(ui, "m_small_cloud_density_mult"_FF, 0.f, 200, 0.1f);
			ui::push()->feature_float(ui, "m_small_cloud_detail_strength"_FF, 0.f, 200, 0.1f);
			});
		render::push<sub>("Influence & Scatter", "Miscellaneous_VFX_Influence"_joaat, [](sub* ui) {
			ui::push()->feature_toggle(ui, "m_influence_tog"_tf);
			ui::push()->feature_float(ui, "m_sun_influence_radius"_FF, 0.f, 200, 0.1f);
			ui::push()->feature_float(ui, "m_sun_scatter_inten"_FF, 0.f, 200, 0.1f);
			ui::push()->feature_float(ui, "m_moon_influence_radius"_FF, 0.f, 200, 0.1f);
			ui::push()->feature_float(ui, "m_moon_scatter_inten"_FF, 0.f, 200, 0.1f);
			});
		render::push<sub>("Stars & Moon", "Miscellaneous_VFX_Moon"_joaat, [](sub* ui) {
			ui::push()->array_feature_toggle(ui, "m_moon"_tif, m_vfx_color, 2);
			if ("m_moon"_tif->m_number_value.integer == 0) {
				ui->push(number<float>("Red").add_number(&features_utility::get()->m_moon_color.x).add_min(0.0f).add_max(255.f).add_precision(2).add_step(0.01));
				ui->push(number<float>("Green").add_number(&features_utility::get()->m_moon_color.y).add_min(0.0f).add_max(255.f).add_precision(2).add_step(0.01));
				ui->push(number<float>("Blue").add_number(&features_utility::get()->m_moon_color.z).add_min(0.0f).add_max(255.f).add_precision(2).add_step(0.01));
			}
			else {
				ui::push()->feature_float(ui, "m_moon_fade_speed"_FF, 0.f, 10, 0.1f);
			}
			ui::push()->feature_float(ui, "m_moon_disc_size"_FF, 0.f, 200, 0.1f);
			ui::push()->feature_float(ui, "m_moon_intensity"_FF, 0.f, 200, 0.1f);
			ui::push()->feature_float(ui, "m_stars_intensity"_FF, 0.f, 200, 0.1f);
			});
		render::push<sub>("Wheels", "Miscellaneous_VFX_Wheels"_joaat, [](sub* ui) {
			ui::push()->array_feature_toggle(ui, "m_wheel_vfx"_tif, m_vfx_color, 2);
			if ("m_wheel_vfx"_tif->m_number_value.integer == 0) {
				ui->push(number<float>("Red").add_number(&features_utility::get()->m_wheels_color.x).add_min(0.0f).add_max(255.f).add_precision(2).add_step(0.01));
				ui->push(number<float>("Green").add_number(&features_utility::get()->m_wheels_color.y).add_min(0.0f).add_max(255.f).add_precision(2).add_step(0.01));
				ui->push(number<float>("Blue").add_number(&features_utility::get()->m_wheels_color.z).add_min(0.0f).add_max(255.f).add_precision(2).add_step(0.01));
			}
			else {
				ui::push()->feature_float(ui, "m_wheel_vfx_fade_speed"_FF, 0.f, 10, 0.1f);
			}
			ui::push()->feature_toggle(ui, "m_wheel_vfx_tracks"_tf);
			ui::push()->feature_int(ui, "m_wheel_vfx_decal_id"_if, 0, 258, 1, 1);
			ui->push(info("Lighting"));

			ui::push()->array_feature_toggle(ui, "m_veh_lights_vfx"_tif, m_vfx_color, 2);
			if ("m_veh_lights_vfx"_tif->m_number_value.integer == 0) {
				ui->push(number<float>("Red Min").add_number(&features_utility::get()->m_veh_light_min_color.x).add_min(0.0f).add_max(255.f).add_precision(2).add_step(0.01));
				ui->push(number<float>("Green Min").add_number(&features_utility::get()->m_veh_light_min_color.y).add_min(0.0f).add_max(255.f).add_precision(2).add_step(0.01));
				ui->push(number<float>("Blue Min").add_number(&features_utility::get()->m_veh_light_min_color.z).add_min(0.0f).add_max(255.f).add_precision(2).add_step(0.01));
				ui->push(number<float>("Red Max").add_number(&features_utility::get()->m_veh_light_max_color.x).add_min(0.0f).add_max(255.f).add_precision(2).add_step(0.01));
				ui->push(number<float>("Green Max").add_number(&features_utility::get()->m_veh_light_max_color.y).add_min(0.0f).add_max(255.f).add_precision(2).add_step(0.01));
				ui->push(number<float>("Blue Max").add_number(&features_utility::get()->m_veh_light_max_color.z).add_min(0.0f).add_max(255.f).add_precision(2).add_step(0.01));
			}
			else {
				ui::push()->feature_float(ui, "m_veh_lights_vfx_fade_speed"_FF, 0.f, 10, 0.1f);
			}
			ui::push()->feature_float(ui, "m_veh_m_lights_intensity_min"_FF, 0.f, 255, 0.1f);
			ui::push()->feature_float(ui, "m_veh_m_lights_intensity_max"_FF, 0.f, 255, 0.1f);
			ui::push()->feature_float(ui, "m_veh_m_lights_range_min"_FF, 0.f, 255, 0.1f);
			ui::push()->feature_float(ui, "m_veh_m_lights_range_max"_FF, 0.f, 255, 0.1f);
			ui::push()->feature_float(ui, "m_veh_m_lights_falloff_min"_FF, 0.f, 255, 0.1f);
			ui::push()->feature_float(ui, "m_veh_m_lights_falloff_max"_FF, 0.f, 255, 0.1f);

			});
		render::push<sub>("Waypoint", "Miscellaneous_VFX_Waypoint"_joaat, [](sub* ui) {
			ui::push()->array_feature_toggle(ui, "m_enable_waypoint_markers"_tif, m_vfx_color, 2);
			if ("m_enable_waypoint_markers"_tif->m_number_value.integer == 0) {
				ui->push(number<float>("Red").add_number(&features_utility::get()->m_waypoint_path_color.x).add_min(0.0f).add_max(255.f).add_precision(2).add_step(0.01));
				ui->push(number<float>("Green").add_number(&features_utility::get()->m_waypoint_path_color.y).add_min(0.0f).add_max(255.f).add_precision(2).add_step(0.01));
				ui->push(number<float>("Blue").add_number(&features_utility::get()->m_waypoint_path_color.z).add_min(0.0f).add_max(255.f).add_precision(2).add_step(0.01));
			}
			else {
				ui::push()->feature_float(ui, "m_enable_waypoint_markers_fade_speed"_FF, 0.f, 10, 0.1f);
			}
			ui->push(number<float>("Alpha").add_number(&features_utility::get()->m_waypoint_path_color.w).add_min(0.0f).add_max(255.f).add_precision(2).add_step(0.01));
			ui::push()->feature_float(ui, "m_enable_waypoint_markers_size"_FF, 0.f, 10, 0.1f);
			ui::push()->feature_float(ui, "m_enable_waypoint_markers_z_pos"_FF, 0.f, 10, 0.1f);
			ui::push()->feature_toggle(ui, "m_enable_waypoint_markers_move_up_down"_tf);
			ui->push(info("Marker Type"));
			for (int i = 0; i < MarkerTypeNames.size(); i++)
			{
				bool is_selected = (int)MarkerTypeNames[i].marker == (int)features_utility::get()->m_waypoint_path_marker;
				ui->push(button(is_selected ? "~r~" + MarkerTypeNames[i].name : "" + MarkerTypeNames[i].name).add_function([=] {
					features_utility::get()->m_waypoint_path_marker = (int)MarkerTypeNames[i].marker;
					}));
			}
			});
		render::push<sub>("Screen", "Miscellaneous_VFX_Screen"_joaat, [](sub* ui) {
			ui::push()->feature_toggle_float(ui, "m_vfx_screen_shadow_light"_tff, -2000, 2000);
			ui::push()->feature_toggle_float(ui, "m_vfx_screen_reflection"_tff, -2000, 2000);
			ui::push()->feature_toggle_float(ui, "m_vfx_screen_gamma"_tff, -2000, 2000);
			ui::push()->feature_toggle_float(ui, "m_vfx_screen_blur"_tff, -2000, 2000);
			ui::push()->feature_toggle_float(ui, "m_vfx_screen_blur2"_tff, -2000, 2000);
			ui::push()->feature_toggle_float(ui, "m_vfx_screen_sky_intensity"_tff, -2000, 2000);
			ui::push()->feature_toggle_float(ui, "m_vfx_screen_saturation"_tff, -2000, 2000);
			//scarface moment
			});

		render::push<sub>("Foot Trails", "Miscellaneous_VFX_Foot"_joaat, [](sub* ui) {
			ui::push()->array_feature_toggle(ui, "m_foot_vfx"_tif, m_vfx_color, 2);
			if ("m_foot_vfx"_tif->m_number_value.integer == 0) {
				ui->push(number<float>("Red").add_number(&features_utility::get()->m_ped_trails_color.x).add_min(0.0f).add_max(255.f).add_precision(2).add_step(0.01));
				ui->push(number<float>("Green").add_number(&features_utility::get()->m_ped_trails_color.y).add_min(0.0f).add_max(255.f).add_precision(2).add_step(0.01));
				ui->push(number<float>("Blue").add_number(&features_utility::get()->m_ped_trails_color.z).add_min(0.0f).add_max(255.f).add_precision(2).add_step(0.01));
			}
			else {
				ui::push()->feature_float(ui, "m_foot_vfx_fade_speed"_FF, 0.f, 10, 0.1f);
			}
			});
		render::push<sub>("Heli Chauffeur", "Miscellaneous_Heli_Chauffeur"_joaat, [](sub* ui) {
			ui->push(button("Spawn Chauffeur").add_function([] {
				tasks::heli_chauffeur("heli_chauffeur_max_speed"_FF->m_value.floating_point,
				features_utility::get()->m_flag_heli_chauf, "heli_chauffeur_max_height"_FF->m_value.floating_point, "heli_chauffeur_min_height"_FF->m_value.floating_point
				, "heli_chauffeur_slow_distance"_FF->m_value.floating_point,0); }));

			//ui->push(array<std::string, int>(xorstr_("Flag"))
			//	.add_position(&features_utility::get()->m_flag_heli_chauf)
			//	.add_array2(m_chuf_flags_world, std::size(m_chuf_flags_world))); 
			ui::push()->feature_float(ui, "heli_chauffeur_max_speed"_FF, 1.f, 1000, 1.f);
			ui::push()->feature_float(ui, "heli_chauffeur_max_height"_FF, 0.f, 300, 1.f);
			ui::push()->feature_float(ui, "heli_chauffeur_min_height"_FF, 0.f, 300, 1.f);
			ui::push()->feature_float(ui, "heli_chauffeur_slow_distance"_FF, 0.f, 100, 1.f);
			ui->push(button("Rappel").add_function([] {
				tasks::heli_chauffeur("heli_chauffeur_max_speed"_FF->m_value.floating_point,
				features_utility::get()->m_flag_heli_chauf, "heli_chauffeur_max_height"_FF->m_value.floating_point, "heli_chauffeur_min_height"_FF->m_value.floating_point
				, "heli_chauffeur_slow_distance"_FF->m_value.floating_point, 1);
				}));
			ui->push(button("Stop").add_function([] {
				TASK::CLEAR_PED_TASKS_IMMEDIATELY(globals::h_local_ped());
				}));
			});
	}
}