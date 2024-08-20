#pragma once
#include "rage/Joaat.hpp"
#include <network/CNetGamePlayer.hpp>
#include "abstract.h"
namespace insight {
	union value {
		const char* str;
		bool toggle;
		float floating_point;
		int integer;
		int8_t i8;
		uint8_t u8;
		int16_t i16;
		uint16_t u16;
		int32_t i32;
		uint32_t u32;
		int64_t i64;
		uint64_t u64;
		value* reference;
		CNetGamePlayer* game_player;
		rage::netPlayer* net_player;
		rage::rlGamerInfo* gamer_info;
	};

	enum class feature_type : uint8_t {
		abstract_feature,
		toggle_feature,
		int_feature,
		float_feature,
		u64_feature,
		toggle_int_feature,
		toggle_float_feature,
		action_feature,
		variadic_feature,
	};

	class abstract_feature {
	public:
		abstract_feature(std::string id, std::string name, std::string description, feature_type type) :
			m_id(id), m_name(name), m_description(description), m_lookup_id(rage::joaat(m_id)), m_type(type)
		{}
		abstract_feature(std::string id, std::string name, feature_type type) : abstract_feature(id, name, {}, type) {}
		abstract_feature(std::string id, feature_type type) : abstract_feature(id, {}, type) {}
		virtual ~abstract_feature() {
			deallocate();
		}
		virtual void init() {
			if (!m_looped) {
				if (m_type != feature_type::abstract_feature && m_type != feature_type::int_feature && m_type != feature_type::float_feature && m_type != feature_type::action_feature)
					m_looped = true;
			}
			m_initialized = true;
		}
		virtual void run() {}
		void deallocate() {
			m_values.clear();
		}
		void push_value(value& v) {
			m_values.emplace_back(&v);
		}
		value* get_value(size_t index) {
			if (index > m_values.size() - 1) {
				throw std::runtime_error("Value index cannot be over value size!");
			}
			return m_values[index];
		}
		value* v() {
			return get_value(0);
		}
		
		virtual feature_type get_type() {
			return feature_type::abstract_feature;
		}
	public:
		feature_type m_type{};
		std::string m_id{};
		std::string m_name{};
		std::string m_description{};
		std::string category;
		uint32_t m_lookup_id{};
		bool m_looped{};
		bool m_initialized{};

	private:
		std::vector<value*> m_values{};
	};
}
