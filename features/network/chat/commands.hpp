
namespace insight {
	class chat_cds
	{
	public:
		static void create_model(int palyer, std::string chat_msg, bool _ped, bool _vehicle, bool _object);
		static void kill_player(bool toggle, int player, std::string chat_msg);
		static void explode_player(bool toggle, int player, std::string chat_msg);
		static void kms(bool toggle, int player, std::string chat_msg);
		static bool money_rp(bool toggle, int player, std::string chat_msg);
		static void fix_veh(bool toggle, int player, std::string chat_msg);
		static void upgrade_veh(bool toggle, int player, std::string chat_msg);

	public:
		static chat_cds* get() {
			static chat_cds i{};
			return &i;
		}
	};
	//class chat_cmd {
	//public:
	// 		static void create_model(int palyer,std::string chat_msg);
	//public:
	//	static chat_cmd* get() {
	//		static chat_cmd i{};
	//		return &i;
	//	}
	//};
}
