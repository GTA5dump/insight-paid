#include "cheat/script/script.hpp"
#include "cheat/menu/helper/ui.hpp"
#include "cheat/features/globals.hpp"
#include "util/panels/panels.hpp"
#include "util/config/config.hpp"
#include "cheat/features/globals.hpp"
#include "cheat/features/features/features_utility.hpp"
#include "util/math/math.hpp"
#include "game/rage/vfx_types.hpp"
#include "cheat/pointers/pointers.hpp"
std::string cloud_names[] = {
	"Cloudy",
	"Rain",
	"Horizon",
	"Horizon Band 1",
	"Horizon Band 2",
	"Horizon Band 3",
	"Puffs",
	"Wispy",
	"Stormy",
	"Clear",
	"Snowy",
	"Contrails",
	"Altostratus",
	"Nimbus",
	"Cirrus",
	"Cirrocumulus",
	"Stratocumulus",
	"Stripey",
	"Horsey",
	"Shower"
};
const char* weather_fx_names[] = {
	"Rainstorm Drop", "Thunder Drop", "Snow Light Drop", "Snow Heavy Drop", "Blizzard Drop", "Underwater Drop", "Lake Fog Drop", "Woodland Pollen Drop", "Woodland Firefly Drop", "Wetland Flies Drop"
};
const char* weather_type[] = {
	"Clear Sky", "Partly Clear", "Cloudy", "Very Sunny", "Foggy", "Halloween", "Mild", "Overcast", "Rainy", "Smoky", "Snowy", "Light Snow"
};
int scroll_id_vfx;
float clouds_speed = 1.f;
float weathers_speed = 10.f;

int weather_mixer_1;
int weather_mixer_2;
float weather_mixer_precentage;

u32 weather_hashes[] = {
	0x27EA2814,  // BLIZZARD
	0x36A83D84,  // CLEAR
	0x6DB1A50D,  // CLEARING
	0x30FDAF5C,  // CLOUDS
	0x97AA0A79,  // EXTRASUNNY
	0xAE737644,  // FOGGY
	0xC91A3202,  // HALLOWEEN
	0xA4CA1326,  // NEUTRAL
	0xBB898D2D,  // OVERCAST
	0x54A69840,  // RAIN
	0x10DCF4B5,  // SMOG
	0xEFB6EFF6,  // SNOW
	0x23FB812B,  // SNOWLIGHT
	0xB677829F,  // THUNDER
	0xAAC9C895   // XMAS
};

const char* weather_names_hash[] = {
	  "Blizzard",
	  "Clear",
	  "Clearing",
	  "Cloudy",
	  "Extra Sunny",
	  "Foggy",
	  "Halloween",
	  "Neutral",
	  "Overcast",
	  "Rainy",
	  "Smog",
	  "Snowy",
	  "Snowy with Light",
	  "Thunderstorms",
	  "Christmas"
};

int wind_speed;
int wind_direction;
float water_intensity;
namespace insight {
	void script_ui::world_subs() {
		render::push<sub>("Weather", "World_Weather"_joaat, [](sub* ui) {
			ui->push(submenu("Clouds").add_target("World_Weather_Clouds"_joaat));
			ui->push(submenu("Modifier").add_target("World_Weather_Modifier"_joaat));
			ui->push(submenu("Mixer").add_target("World_Weather_Mixer"_joaat));
			ui->push(info("General"));
			ui->push(number<int>("Wind Speed")
				.add_number(&wind_speed).add_min(0).add_max(100).add_step(1).add_precision(0).set_action([] {
					MISC::SET_WIND_SPEED(wind_speed);
					}));
			ui->push(number<int>("Wind Direction")
				.add_number(&wind_direction).add_min(0).add_max(100).add_step(1).add_precision(0).set_action([] {
					MISC::SET_WIND_DIRECTION(wind_direction);
					}));
			});

		render::push<sub>("Modifier", "World_Weather_Modifier"_joaat, [](sub* ui) {
			ui->push(number<float>("Transition Speed")
				.add_number(&weathers_speed).add_min(0).add_max(2000).add_step(1).add_precision(0));
			for (int i = 0; i < 12; i++) {
				ui->push(button(weather_type[i]).add_function([i] {
					tasks::transition_weather(i, weathers_speed);
					}));
			}
			});

		render::push<sub>("Mixer", "World_Weather_Mixer"_joaat, [](sub* ui) {
			ui->push(array<const char*, int>("Weather 1")
				.add_array(&weather_names_hash).add_position(&weather_mixer_1).add_description("Main Weather"));
			ui->push(array<const char*, int>("Weather 2")
				.add_array(&weather_names_hash).add_position(&weather_mixer_2).add_description("Secondary Weather"));
			ui->push(number<float>("Weather 2 %")
				.add_number(&weather_mixer_precentage).add_min(0.f).add_max(1.f).add_step(0.05f).add_precision(2));
			ui->push(button("Mix Weather").add_function([] {
				MISC::SET_CURR_WEATHER_STATE(weather_hashes[weather_mixer_1], weather_hashes[weather_mixer_2], weather_mixer_precentage);
				}));
			});

		render::push<sub>("Clouds", "World_Weather_Clouds"_joaat, [](sub* ui) {
			ui->push(number<float>("Transition Speed")
				.add_number(&clouds_speed).add_min(0).add_max(2000.f).add_step(1.f).add_precision(1));
			for (int i = 0; i < 20; i++) {
				ui->push(button(cloud_names[i]).add_function([i] {
					tasks::transition_cloud(i, clouds_speed);
					}));
			}
			});

		render::push<sub>("Water", "World_Water"_joaat, [](sub* ui) {
			ui::feature_toggle(ui, "split_water"_tf);
			ui->push(number<float>("Wave Intensity")
				.add_number(&water_intensity).add_min(0).add_max(10.f).add_step(0.1f).add_precision(1)
				.set_action([] { WATER::SET_DEEP_OCEAN_SCALER(water_intensity); }));

			ui->push(button("Reset Wave Intensity")
				.set_action([] {WATER::RESET_DEEP_OCEAN_SCALER(); }));
			});

	/*	render::push<sub>("Visuals", "Miscellaneous_Visauls"_joaat, [](sub* ui) {

			if (insight::pointers::get()->g_visual_settings) {
				ui->push(number<float>("Shadow Light")
					.add_number(&insight::pointers::get()->g_visual_settings->m_shadow_light).add_min(-100).add_max(100).add_step(1).add_precision(2));

				ui->push(number<float>("Reflection")
					.add_number(&insight::pointers::get()->g_visual_settings->m_reflection).add_min(-100).add_max(100).add_step(1).add_precision(2));

				ui->push(number<float>("Gamma")
					.add_number(&insight::pointers::get()->g_visual_settings->m_gamma).add_min(-100).add_max(100).add_step(1).add_precision(2));

				ui->push(number<float>("Near Blur")
					.add_number(&insight::pointers::get()->g_visual_settings->m_blur).add_min(-100).add_max(100).add_step(1).add_precision(2));

				ui->push(number<float>("Far Blur")
					.add_number(&insight::pointers::get()->g_visual_settings->m_blur2).add_min(-100).add_max(100).add_step(1).add_precision(2));

				ui->push(number<float>("Sky Intensity")
					.add_number(&insight::pointers::get()->g_visual_settings->m_sky_intensity).add_min(-100).add_max(100).add_step(1).add_precision(2));

				ui->push(number<float>("Saturation")
					.add_number(&insight::pointers::get()->g_visual_settings->m_saturation).add_min(-100).add_max(100).add_step(1).add_precision(2));
			}
			});*/
	}
}