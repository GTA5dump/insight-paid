#pragma once
#include "util/script/script_global.hpp"
#include "cheat/features/globals.hpp"
#include "cheat/features/scripted_globals.hpp"
#include "util/script/script.hpp"
namespace insight
{
	void scripted_globals::request_bullshark_testosterone() {
		*script_global(2672524).at(3690).as<int*>() = 1;
	}

	void scripted_globals::request_ballistic_armor() {
		*script_global(2794162).at(896).as<int*>() = 1;
	}

	void scripted_globals::request_ammo_drop() {
		*script_global(2794162).at(891).as<int*>() = 1;
	}

	void scripted_globals::request_boat_pickup() {
		*script_global(2794162).at(892).as<int*>() = 1;
	}

	void scripted_globals::request_helicopter_pickup() {
		*script_global(2794162).at(893).as<int*>() = 1;
	}

	void scripted_globals::request_backup_helicopter() {
		*script_global(2794162).at(4491).as<int*>() = 1;
	}

	void scripted_globals::request_airstrike() {
		*script_global(2794162).at(4492).as<int*>() = 1;
	}
	void scripted_globals::request_avenger()
	{
		*script_global(2794162).at(938).as<int*>() = 1;
	}

	void scripted_globals::request_kosatka()
	{
		*script_global(2794162).at(960).as<int*>() = 1;
	}

	void scripted_globals::request_mobile_operations_center()
	{
		*script_global(2794162).at(930).as<int*>() = 1;
	}

	void scripted_globals::request_terrorbyte()
	{
		*script_global(2794162).at(943).as<int*>() = 1;
	}

	void scripted_globals::request_acidlab()
	{
		*script_global(2794162).at(944).as<int*>() = 1;
	}

	void scripted_globals::request_acidlab_bike()
	{
		*script_global(2794162).at(994).as<int*>() = 1;
	}
	void scripted_globals::request_taxi()
	{
		*script_global(2794162).at(853).as<int*>() = 1;
	}
	void scripted_globals::request_rcbandito()
	{
		*script_global(2794162).at(6879).as<int*>() = 1;
		script::get_current()->yield(2000ms);
		*script_global(2794162).at(6879).as<int*>() = 0;
	}
	void scripted_globals::request_minitank() {
		*script_global(2794162).at(6880).as<int*>() = 1;
		script::get_current()->yield(2000ms);
		*script_global(2794162).at(6880).as<int*>() = 0;
	}
	//Global_2794162.f_6879 = 0; rcbandito
	//Global_2794162.f_6880 = 0; minitank
};
