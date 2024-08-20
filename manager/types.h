#pragma once
#include "abstract.h"

namespace insight {
	class toggle_feature : public abstract_feature {
	public:
		toggle_feature(std::string id, std::string name, std::string description, fnptr<void(toggle_feature*, bool&)> callback) :
			abstract_feature(id, name, description, feature_type::toggle_feature),
			m_callback(callback) {
		}
		toggle_feature(std::string id, std::string name, fnptr<void(toggle_feature*, bool&)> callback) :
			toggle_feature(id, name, {}, callback) {
		}
		toggle_feature(std::string id, fnptr<void(toggle_feature*, bool&)> callback) :
			toggle_feature(id, {}, callback) {
		}
		~toggle_feature() {
			abstract_feature::~abstract_feature();
		}
		void init() override {
			m_looped = true;
			push_value(m_value);
			abstract_feature::init();
		}
		void run() override {
			m_callback(this, m_value.toggle);
			abstract_feature::run();
		}

		feature_type get_type() override {
			return feature_type::toggle_feature;
		}
	public:
		value m_value{};
	private:
		fnptr<void(toggle_feature*, bool&)> m_callback{};
	};

	class int_feature : public abstract_feature {
	public:
		int_feature(std::string id, std::string name, std::string description, fnptr<void(int_feature*, int&)> callback) :
			abstract_feature(id, name, description, feature_type::int_feature),
			m_callback(callback) {
		}
		int_feature(std::string id, std::string name, fnptr<void(int_feature*, int&)> callback) :
			int_feature(id, name, {}, callback) {
		}
		int_feature(std::string id, fnptr<void(int_feature*, int&)> callback) :
			int_feature(id, {}, callback) {
		}
		~int_feature() {
			abstract_feature::~abstract_feature();
		}

		feature_type get_type() override {
			return feature_type::int_feature;
		}
	public:
		void init() override {
			m_looped = false;
			push_value(m_value);
			abstract_feature::init();
		}
		void run() override {
			m_callback(this, m_value.i32);
			abstract_feature::run();
		}
	public:
		value m_value{};
	private:
		fnptr<void(int_feature*, int&)> m_callback{};
	};

	class toggle_int_feature : public abstract_feature {
	public:
		toggle_int_feature(std::string id, std::string name, std::string description, fnptr<void(toggle_int_feature*, bool&, int&)> callback) :
			abstract_feature(id, name, description, feature_type::toggle_int_feature),
			m_callback(callback) {
		}
		toggle_int_feature(std::string id, std::string name, fnptr<void(toggle_int_feature*, bool&, int&)> callback) :
			toggle_int_feature(id, name, {}, callback) {
		}
		toggle_int_feature(std::string id, fnptr<void(toggle_int_feature*, bool&, int&)> callback) :
			toggle_int_feature(id, {}, callback) {
		}
		~toggle_int_feature() {
			abstract_feature::~abstract_feature();
		}
	public:
		void init() override {
			m_looped = true;
			push_value(m_toggle_value);
			push_value(m_number_value);
			abstract_feature::init();
		}
		void run() override {
			m_callback(this, m_toggle_value.toggle, m_number_value.i32);
			abstract_feature::run();
		}

		feature_type get_type() override {
			return feature_type::toggle_int_feature;
		}
	public:
		value m_toggle_value{};
		value m_number_value{};
	private:
		fnptr<void(toggle_int_feature*, bool&, int&)> m_callback{};
	};

	class float_feature : public abstract_feature {
	public:
		float_feature(std::string id, std::string name, std::string description, fnptr<void(float_feature*, float&)> callback) :
			abstract_feature(id, name, description, feature_type::float_feature),
			m_callback(callback) {
		}
		float_feature(std::string id, std::string name, fnptr<void(float_feature*, float&)> callback) :
			float_feature(id, name, {}, callback) {
		}
		float_feature(std::string id, fnptr<void(float_feature*, float&)> callback) :
			float_feature(id, {}, callback) {
		}
		~float_feature() {
			abstract_feature::~abstract_feature();
		}

		feature_type get_type() override {
			return feature_type::float_feature;
		}
	public:
		void init() override {
			m_looped = false;
			push_value(m_value);
			abstract_feature::init();
		}
		void run() override {
			m_callback(this, m_value.floating_point);
			abstract_feature::run();
		}
	public:
		value m_value{};
	private:
		fnptr<void(float_feature*, float&)> m_callback{};
	};

	class toggle_float_feature : public abstract_feature {
	public:
		toggle_float_feature(std::string id, std::string name, std::string description, fnptr<void(toggle_float_feature*, bool&, float&)> callback) :
			abstract_feature(id, name, description, feature_type::toggle_float_feature),
			m_callback(callback) {
		}
		toggle_float_feature(std::string id, std::string name, fnptr<void(toggle_float_feature*, bool&, float&)> callback) :
			toggle_float_feature(id, name, {}, callback) {
		}
		toggle_float_feature(std::string id, fnptr<void(toggle_float_feature*, bool&, float&)> callback) :
			toggle_float_feature(id, {}, callback) {
		}
		~toggle_float_feature() {
			abstract_feature::~abstract_feature();
		}

		feature_type get_type() override {
			return feature_type::toggle_float_feature;
		}
	public:
		void init() override {
			m_looped = true;
			push_value(m_toggle_value);
			push_value(m_number_value);
			abstract_feature::init();
		}
		void run() override {
			m_callback(this, m_toggle_value.toggle, m_number_value.floating_point);
			abstract_feature::run();
		}
	public:
		value m_toggle_value{};
		value m_number_value{};
	private:
		fnptr<void(toggle_float_feature*, bool&, float&)> m_callback{};
	};

	class action_feature : public abstract_feature {
	public:
		action_feature(std::string id, std::string name, std::string description, fnptr<void(action_feature*)> callback) :
			abstract_feature(id, name, description, feature_type::action_feature),
			m_callback(callback) {
		}
		action_feature(std::string id, std::string name, fnptr<void(action_feature*)> callback) :
			action_feature(id, name, {}, callback) {
		}
		action_feature(std::string id, fnptr<void(action_feature*)> callback) :
			action_feature(id, {}, callback) {
		}
		~action_feature() {
			abstract_feature::~abstract_feature();
		}
	public:
		void init() override {
			m_looped = false;
			abstract_feature::init();
		}
		void run() override {
			m_callback(this);
			abstract_feature::run();
		}
	private:
		fnptr<void(action_feature*)> m_callback{};
	};

	class u64_feature : public abstract_feature {
	public:
		u64_feature(std::string id, std::string name, std::string description, fnptr<void(u64_feature*, u64&)> callback) :
			abstract_feature(id, name, description, feature_type::u64_feature),
			m_callback(callback) {
		}
		u64_feature(std::string id, std::string name, fnptr<void(u64_feature*, u64&)> callback) :
			u64_feature(id, name, {}, callback) {
		}
		u64_feature(std::string id, fnptr<void(u64_feature*, u64&)> callback) :
			u64_feature(id, {}, callback) {
		}

		~u64_feature() {
			abstract_feature::~abstract_feature();
		}

		feature_type get_type() override {
			return feature_type::u64_feature;
		}
	public:
		void init() override {
			m_looped = false;
			push_value(m_value);
			abstract_feature::init();
		}
		void run() override {
			m_callback(this, m_value.u64);
			abstract_feature::run();
		}
	public:
		value m_value{};
	private:
		fnptr<void(u64_feature*, u64&)> m_callback{};
	};
}