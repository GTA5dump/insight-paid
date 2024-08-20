#include "cheat/script/script.hpp"
#include "cheat/menu/helper/ui.hpp"
#include "cheat/features/globals.hpp"
#include "util/panels/panels.hpp"
#include "util/config/config.hpp"


namespace insight {
	std::string input_methods[] = {
		"Keyboard",
		"Controller",
	};

	void script_ui::network_spoofing_stats() {
		render::push<sub>("Stats", "Network_Spoofing_Stats"_joaat, [](sub* ui) {
			ui::push()->feature_toggle_int(ui, "network_spoof_kills"_tif, 0, 9999999, 10);
			ui::push()->feature_toggle_int(ui, "network_spoof_rank"_tif, 0, 8000, 10);
			ui::push()->feature_toggle_int(ui, "network_spoof_cash"_tif, 0, 2147483, 10);
			ui::push()->feature_toggle_int(ui, "network_spoof_bank"_tif, 0, 2147483, 10);
			ui::push()->array_feature_toggle(ui, "network_spoof_input"_tif, input_methods, 2);
		});
	}
}