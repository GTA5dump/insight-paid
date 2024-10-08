#pragma once
#include <script/scrThread.hpp>
#include "cheat/pointers/pointers.hpp"
#include <script/GtaThread.hpp>
#include <ped/CPedFactory.hpp>
#include <network/CNetworkPlayerMgr.hpp>
#include <script/scrProgramTable.hpp>

namespace insight::gta_util
{
	inline CPed* get_local_ped()
	{
		if (auto ped_factory = *pointers::get()->g_ped_factory)
		{
			return ped_factory->m_local_ped;
		}

		return nullptr;
	}

	inline CVehicle* get_local_vehicle()
	{
		if (const auto ped = get_local_ped(); ped)
		{
			if (const auto veh = ped->m_vehicle; veh)
			{
				return veh;
			}
		}
		return nullptr;
	}

	inline CPlayerInfo* get_local_playerinfo()
	{
		if (auto ped_factory = *pointers::get()->g_ped_factory)
		{
			if (auto ped = ped_factory->m_local_ped)
			{
				return ped->m_player_info;
			}
		}

		return nullptr;
	}

	inline CNetworkPlayerMgr* get_network_player_mgr()
	{
		return *pointers::get()->g_network_player_mgr;
	}
	inline Network* get_network()
	{
		return *pointers::get()->g_network;
	}

	template <typename F, typename ...Args>
	void execute_as_script(rage::joaat_t script_hash, F&& callback, Args &&...args)
	{
		auto tls_ctx = rage::tlsContext::get();
		for (auto thread : *pointers::get()->g_script_threads)
		{
			if (!thread || !thread->m_context.m_thread_id || thread->m_context.m_script_hash != script_hash)
				continue;

			auto og_thread = tls_ctx->m_script_thread;

			tls_ctx->m_script_thread = thread;
			tls_ctx->m_is_script_thread_active = true;

			std::invoke(std::forward<F>(callback), std::forward<Args>(args)...);

			tls_ctx->m_script_thread = og_thread;
			tls_ctx->m_is_script_thread_active = og_thread != nullptr;

			return;
		}
	}

	inline GtaThread* find_script_thread(rage::joaat_t hash)
	{
		for (auto thread : *pointers::get()->g_script_threads)
		{
			if (thread
				&& thread->m_context.m_thread_id
				&& thread->m_handler
				&& thread->m_script_hash == hash)
			{
				return thread;
			}
		}

		return nullptr;
	}

	inline rage::scrProgram* find_script_program(rage::joaat_t hash)
	{
		for (auto& script : *pointers::get()->g_script_program_table)
		{
			if (script.m_program && script.m_program->m_name_hash == hash)
				return script.m_program;
		}

		return nullptr;
	}
}
