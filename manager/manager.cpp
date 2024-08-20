#include "manager.h"

namespace insight {
	void feature_manager::remove(uint32_t id) {
		for (size_t i = 0; i < m_features.size(); ++i) {
			auto& f = m_features[i];
			if (f->m_lookup_id == id) {
				delete f;
				m_features.erase(m_features.begin() + i);
				break; 
			}
		}
	}

	void feature_manager::init() {
		for (auto& f : m_features) {
			f->init();
		}
	}

	void feature_manager::tick_all_features() {
		for (auto& f : m_features) {
			f->run();
		}
	}

	void feature_manager::tick(std::string str) {
		for (auto& f : m_features) {
			if (f->category == str) {
				f->run();
			}
		}
	}

	void feature_manager::clear() {
		for (auto& f : m_features) {
			delete f;
		}
		m_features.clear();
	}
}