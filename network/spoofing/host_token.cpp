#include "cheat/script/script.hpp"
#include "cheat/menu/helper/ui.hpp"
#include "cheat/features/globals.hpp"
#include "util/panels/panels.hpp"
#include "util/config/config.hpp"

namespace insight {

	std::string holder;

	void script_ui::network_spoofing_host_token() {
		render::push<sub>("Host Token", "Network_Spoofing_Host_Token"_joaat, [](sub* ui) {
			ui::push()->feature_toggle(ui, "spoof_host_token"_tf);
			ui->push(keyboard("Host Token").add_input(&holder).add_right_text(holder).set_action([] {
				"spoof_host_token_u64"_tu->m_value.u64 = std::stoull(holder);
			}));
			ui->push(info("Presets"));
			ui->push(button("Strong").set_action([] {
				"spoof_host_token_u64"_tu->m_value.u64 = 0x0;
				holder = std::to_string(0x0);
			}));
			ui->push(button("Meduim").set_action([] {
				"spoof_host_token_u64"_tu->m_value.u64 = 0x5CEA;
				holder = std::to_string(0x5CEA);
			}));
			ui->push(button("Weak").set_action([] {
				"spoof_host_token_u64"_tu->m_value.u64 = 0x005ACEA;
				holder = std::to_string(0x0935ACEA);
			}));
		});
	}

}