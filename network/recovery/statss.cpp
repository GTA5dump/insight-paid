

#include "cheat/script/script.hpp"
#include "cheat/menu/helper/ui.hpp"
#include "util/panels/panels.hpp"
#include "util/config/config.hpp"

#include "cheat/features/scripted_globals.hpp"

namespace insight {
	void script_ui::network_recovery_stats() {
		render::push<sub>("Stats", "Network_Recovery_Stats"_joaat, [](sub* ui) {
			ui->push(submenu("Time").add_target("Network_Recovery_Stats_Time"_joaat));
			ui->push(submenu("KD").add_target("Network_Recovery_Stats_Time"_joaat));
			ui->push(info("General"));
			ui->push(button("Max Stats").add_function([] {
				stats<int>::set("SCRIPT_INCREASE_STAM", 100);
				stats<int>::set("SCRIPT_INCREASE_STRN", 100);
				stats<int>::set("SCRIPT_INCREASE_LUNG", 100);
				stats<int>::set("SCRIPT_INCREASE_DRIV", 100);
				stats<int>::set("SCRIPT_INCREASE_FLY", 100);
				stats<int>::set("SCRIPT_INCREASE_SHO", 100);
				stats<int>::set("SCRIPT_INCREASE_STL", 100);
				notify::send("Recovery", "Maxed Out Stats");
			}));
		});
	}
}