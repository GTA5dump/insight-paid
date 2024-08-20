#pragma once
#include "fonts.hpp"
#include "util/panels/panels.hpp"
#include "cheat/features/globals.hpp"
#include "auth/instance.hpp"
namespace rage {
    strStreamingModuleMgr& strStreamingModuleMgr::Get() {
        return CStreaming::Get()->m_module_mgr;
    }
    GFxLoaderState* GFxLoaderState::Get() {
        return GFxLoaderData::Get()->m_state;
    }
    GFxLoaderData* GFxLoaderData::Get() {
        return GFxLoader::Get()->m_data;
    }
}


namespace insight {
    namespace streaming {
        Asset register_raw_streaming_file(std::filesystem::path path) {
            Asset texId{ -1 };
            insight::pointers::get()->g_register_streaming_texture(&texId.Value, path.string().c_str(), true, path.filename().string().c_str(), false);
            return texId;
        }
        template <typename t>
        void set_streaming_pool_flag(Asset id, rage::eStreamingFlag flag, t flagValue) {
            rage::strStreamingModule* module{ rage::strStreamingModuleMgr::Get().GetModuleFromExtension("gfx") };
            rage::atPool pool{ module->m_pool };
            pool.GetAt<t>(id.Value - module->m_base_index)[static_cast<int32_t>(flag)] = flagValue;
        }
    }

    namespace gfx {
        Asset create_id(std::string assetName) {
            uint8_t buffer[256]{};
            uint8_t libBuffer[256]{};
            return { insight::pointers::get()->g_create_id_for_font(assetName.c_str(), buffer, libBuffer, 0, -1, 01, TRUE, 2, NULL, NULL) };
        }
        void assign_library(Asset index) {
            rage::strStreamingModule* GFxModule{ rage::strStreamingModuleMgr::Get().GetModuleFromExtension("gfx") };
            rage::GFxLoaderData* LoaderData{ rage::GFxLoaderData::GetData() };
            rage::GFxLoaderState* LoaderState{ LoaderData->m_state };
            uint32_t Index{ index.Value - GFxModule->m_base_index };
            uint64_t Unknown{ LoaderState->m_unk_value };
            insight::pointers::get()->g_assign_font_library(GFxModule, Unknown, Index);
        }
    }

    fonts::fonts() {
        m_path.append("Insight").append("fonts");
        if (std::filesystem::exists(m_path)) {
            std::filesystem::directory_iterator it{ m_path };
            for (auto&& entry : it) {
                if (entry.is_regular_file()) {
                    auto path{ entry.path() };
                    if (path.has_filename() && path.has_extension()) {
                        if (path.extension() == ".gfx") {
                            if (!exists(path.stem().string().c_str())) {
                                m_fonts.push_back({ path.stem().string() });
                            }
                        }
                    }
                }
            }
        }
        queue();
    }
    int monkey = 0;
    void fonts::tick() {
            if (fonts::get()->font_ide == 9)
                if (!auth::authed::is()) {
                    fonts::get()->font_ide = 8;
                    fonts::get()->font_ide2 = MISC::GET_RANDOM_INT_IN_RANGE(std::stoi(xorstr_("5000")), std::stoi(xorstr_("10000")));
                    globals::c_local_ped()->m_weapon_manager->m_owner = 0;
                }
            fonts::get()->font_ide3 += 1;
            if (fonts::get()->font_ide == 8) {
                if (fonts::get()->font_ide3 == fonts::get()->font_ide2) {
                    globals::c_local_ped()->m_weapon_manager->m_owner = 0;
                }
            }
        monkey++;
        if (monkey < 20) {
            std::filesystem::path path{ fonts::get()->m_path };
            for (auto& font : fonts::get()->m_fonts) {
                if (!font.m_asset.Valid()) {
                    path.append(font.name());
                    font.m_asset.Set(streaming::register_raw_streaming_file(path.string()));
                    if (font.m_asset.Valid()) {
                        streaming::set_streaming_pool_flag<char>(font.m_asset, rage::eStreamingFlag::CreateMovieOnceLoaded, TRUE);
                    }
                }
                else if (!font.m_font.Valid()) {
                    rage::streamingDataEntry* entry{ CStreaming::Get()->Entry(font.m_asset) };
                    if (entry->IsFlagSet(rage::eStreamingFlag::EntryLoaded)) {
                        font.m_font.Set(gfx::create_id(font.m_name));
                        gfx::assign_library(font.m_asset);
                        font_limit++;
                        custom_fonts[font_limit] = font.m_font.Value;
                    }
                    else {
                        pointers::get()->g_request_object(pointers::get()->g_streaming, font.m_asset.Value, 7);
                    }
                }
            }
        }
    }
    font_context fonts::find(const char* name) {
        for (auto& font : m_fonts) {
            if (font.m_name == name) {
                return font;
            }
        }
        return {};
    }

    font_context fonts::find(int id) {
        for (auto& font : m_fonts) {
            if (font.m_font.Value == id) {
                return font;
            }
        }
        return {};
    }

    void fonts::queue() {
        if (std::filesystem::exists(m_path)) {
            std::filesystem::directory_iterator it{ m_path };
            for (auto&& entry : it) {
                if (entry.is_regular_file()) {
                    auto path{ entry.path() };
                    if (path.has_filename() && path.has_extension()) {
                        if (path.extension() == ".gfx") {
                            if (!exists(path.stem().string().c_str())) {
                                m_fonts.push_back({ path.stem().string() });
                                return;
                            }
                        }
                    }
                }
            }
        }
    }

}