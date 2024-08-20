#pragma once
#include "types.h"
#include "abstract.h"
#define ONCE(a) do a while (false)

namespace insight {
	class feature_manager {
	public:
		template<typename t>
		void add(t feature, const std::string category) {
			feature_manager::get()->m_features.push_back(new t(feature));
			feature_manager::get()->m_features.back()->category = category;
		}
		void remove(uint32_t id);
		void init();
		void tick_all_features();
		void tick(std::string str);
		void clear();
		template <typename t>
		t* get_feature(uint32_t id) {
			for (auto& f : m_features) {
				if (f->m_lookup_id == id) {
					return (t*)f;
				}
			}
			return nullptr;
		}
		template <typename t>
		t* get_feature(const char* id) {
			for (auto& f : m_features) {
				if (f->m_id == id) {
					return (t*)f;
				}
			}
			return nullptr;
		}
		template<typename t>
		std::vector<t*> get_features_by_category(const std::string& category) {
			std::vector<t*> features;
			for (auto& f : m_features) {
				if (f->category == category) {
					t* typedFeature = dynamic_cast<t*>(f);
					if (typedFeature) {
						features.push_back(typedFeature);
					}
				}
			}
			return features;
		}
	public:
		static feature_manager* get()
		{
			static feature_manager i{};

			return &i;
		}
	public:
		static void initialize() {
			get();
		}
	public:
		std::vector<abstract_feature*> m_features{};
	};
}

namespace insight {
	inline abstract_feature* operator ""_abf(const char* str, size_t) {
		return feature_manager::get()->get_feature<abstract_feature>(str);
	}

	inline toggle_feature* operator ""_tf(const char* str, size_t) {
		return feature_manager::get()->get_feature<toggle_feature>(str);
	}

	inline int_feature* operator ""_if(const char* str, size_t) {
		return feature_manager::get()->get_feature<int_feature>(str);
	}

	inline toggle_int_feature* operator ""_tif(const char* str, size_t) {
		return feature_manager::get()->get_feature<toggle_int_feature>(str);
	}

	inline float_feature* operator ""_FF(const char* str, size_t) {
		return feature_manager::get()->get_feature<float_feature>(str);
	}

	inline toggle_float_feature* operator ""_tff(const char* str, size_t) {
		return feature_manager::get()->get_feature<toggle_float_feature>(str);
	}

	inline u64_feature* operator ""_tu(const char* str, size_t) {
		return feature_manager::get()->get_feature<u64_feature>(str);
	}

	inline action_feature* operator ""_AF(const char* str, size_t) {
		return feature_manager::get()->get_feature<action_feature>(str);
	}
}