#pragma once
#include "handle.hpp"
#include "module.hpp"
#include "pattern.hpp"
#include "pattern_batch.hpp"
#include "range.hpp"

struct patch {
	void* location;
	std::vector<uint8_t> original_bytes;
};
inline std::vector<patch> g_patches;

inline void restore_patches() {
	for (auto& patch : g_patches) {
		memcpy(patch.location, patch.original_bytes.data(), patch.original_bytes.size());
	}
}
