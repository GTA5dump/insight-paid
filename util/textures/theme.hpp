#pragma once
namespace insight {
	class theme {
	public:
		static void save();
		static void load();
	public:
		static theme* get() {
			static theme i{};
			return &i;
		}
	};


}