#include "http.hpp"
#include "nlohmann/json.hpp"
#include "cheat/pointers/pointers.hpp"
#include <socialclub/ScInfo.hpp>
#pragma comment(lib, "libcrypto.lib")
#pragma comment(lib, "libcurl_a.lib")
namespace insight {
	nlohmann::json send_request(nlohmann::json body, std::string endpoint) {
		curl_wrapper curl{};
		std::vector<std::string> headers = {
			"X-Requested-With: XMLHttpRequest",
			"Content-Type: application/json; charset=utf-8",
			std::format("Authorization: SCAUTH val=\"{}\"", pointers::get()->g_social_club_info->m_ticket)
		};
		std::string response{ curl.post(endpoint, body.dump(), headers) };
		nlohmann::json j{ nlohmann::json::parse(response) };
		if (j["Status"]) {
			return j;
		}
		return {};
	}
}