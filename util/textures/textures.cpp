#include "textures.hpp"
#include "cheat/pointers/pointers.hpp"
#include "natives.hpp"
#include "cheat/render/renderer.hpp"
#include "util/script/fiber_pool.hpp"
#include "game/rage/sysUseAllocator.hpp"
#define VALID_TEXTURE_EXT(ext) ext == ".png" || ext == ".jpg" || ext == ".jpeg" || ext == ".bmp")

namespace insight {

	void add_dictionary_to_pool(rage::pgDictionary* dictionary, std::string name) {
		if (auto grcTextureStore = insight::pointers::get()->g_texture_store; grcTextureStore) {
			uint32_t hash{ rage::joaat(name) };
			uint32_t output{};
			uint32_t index{ *insight::pointers::get()->g_setup_store_item(grcTextureStore, &output, &hash) };
			insight::pointers::get()->g_add_dictionary_to_pool(grcTextureStore, index, dictionary);
		}
	}

	rage::pgDictionary* create_dictionary(size_t size) {
		rage::sysUseAllocator allocator; 
		rage::pgDictionary* customDictionary = (rage::pgDictionary*)allocator.operator new(64); 
		if (customDictionary) {
			customDictionary = insight::pointers::get()->g_setup_dictionary(customDictionary, size);
			return customDictionary;
		}
		return nullptr;
	}

	rage::grcTexture* create_texture(std::filesystem::path filepath) {
		rage::grcTexture* texture{};
		if (auto grcTextureFactory = *insight::pointers::get()->g_texture_factory; grcTextureFactory) {
			texture = grcTextureFactory->CreateTexture(filepath.stem().string().c_str(), NULL);
		}
		texture->Set(filepath.stem().string(), insight::g_renderer->create_texture(filepath));
		return texture;
	}

	textures::textures() {
		m_path.append("insight").append("textures");
		if (std::filesystem::exists(m_path)) {
			std::filesystem::directory_iterator it{ m_path };
			for (auto&& entry : it) {
				if (entry.is_regular_file()) {
					auto path{ entry.path() };
					if (path.has_filename() && (path.extension() == ".png" || path.extension() == ".jpg" || path.extension() == ".jpeg" || path.extension() == ".bmp")) {
						m_files.push_back({ path.filename().string() });
					}
				}
			}

			m_dictionary = create_dictionary(m_files.size() * 2);

			if (m_dictionary) {
				add_dictionary_to_pool(m_dictionary, "textures");
				if (!m_files.empty()) {
					for (auto& file : m_files) {
						load_image(std::filesystem::path(m_path).append(file));
					}			
				}
			}
		}
	}

	void textures::tick() {
		GRAPHICS::REQUEST_STREAMED_TEXTURE_DICT("textures", FALSE);
	}

	void textures::load_image(std::filesystem::path path) {
		if (rage::grcTextureFactory* factory{ *insight::pointers::get()->g_texture_factory }; factory) {
			std::string name{ path.stem().string() };
			rage::grcTexture* texture{ factory->CreateTexture(name.c_str(), 0) };
			texture->Set(name, insight::g_renderer->create_texture(path));
			insight::pointers::get()->g_add_texture_to_dictionary(m_dictionary, rage::joaat(name), texture);
		}
	}

	texture_context textures::get(std::string name) {
		for (auto& texture : m_textures) {
			if (texture.m_name == name)
				return texture;
		}
		return {};
	}
}