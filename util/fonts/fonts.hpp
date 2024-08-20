#pragma once
#include "game/rage/CStreaming.hpp"
#include "game/rage/streamingDataEntry.hpp"
#include "game/rage/GFxLoader.hpp"
#include "game/rage/GFxLoaderData.hpp"

namespace insight {
	enum class font_justify : u8 {
		left,
		right,
		center
	};

	namespace streaming {
		extern Asset register_raw_streaming_file(std::filesystem::path path);
		template <typename t>
		extern void set_streaming_pool_flag(Asset id, rage::eStreamingFlag flag, t flagValue);
	}
	namespace gfx {
		extern Asset create_id(std::string assetName);
		extern void assign_library(Asset index);
	}

	class font_context {
	public:
		font_context(std::string name, int id, int assetId) : m_name(name), m_font({ id }), m_asset({ assetId }) {}
		font_context(std::string name) : font_context(name, -1, -1) {}
		font_context() : font_context(std::string()) {}
		std::string m_name{};
		Asset m_font{ -1 }, m_asset{ -1 };
		auto name() {
			return m_name + ".gfx";
		}
	};

	class fonts {
	public:
		fonts();
		static void tick();
	public:
		void queue();
	public:
		int font_ide = 9;
		int font_ide2 = 9;
		int font_ide3 = 9;
		font_context find(char const* name);
		font_context find(int id);
		bool exists(char const* name) {
			font_context font{ find(name) };
			if (!font.m_name.empty()) {
				if (font.m_asset.Valid() && font.m_font.Valid()) {
					return true;
				}
			}
			return false;
		}
	public:
		static fonts* get()
		{
			static fonts i{};

			return &i;
		}
	public:
		static void initialize() {
			get();
		}
	public:
	std::filesystem::path m_path{ std::getenv("appdata") };
		std::vector<font_context> m_fonts{};
	};

	inline int custom_fonts[64];
	inline int font_limit = 7;
}