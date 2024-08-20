
#include "cheat/features/features.hpp"
#include "cheat/script/script_utility.hpp"
namespace insight {
	void null_feature_toggle(toggle_feature* feature, bool& value) {
		return;	
	}

	void null_feature_float(float_feature* feature, float& value)  {
		return;
	}

	void null_feature_u64(u64_feature* feature, u64& value) {
		return;
	}

	void null_feature_int_toggle(toggle_int_feature* feature, bool& value, int& value2)  {
		return;
	}	
	void null_feature_float_toggle(toggle_float_feature* feature, bool& value, float& value2)  {
		return;
	}

	void null_feature_int(int_feature* feature, int& value) {
		return;
	}
}