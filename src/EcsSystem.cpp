/*
** EPITECH PROJECT, 2021
** ECS
** File description:
** Created by MCESC, 11/26/2018
*/

#include <algorithm>
#include "EcsSystem.hpp"
#include "utils.hpp"

void ECS::SystemList::addSystemInternal(ECS::BaseSystem& system)
{
	if (system.isValid()) {
		systems_m.push_back(&system);
		return;
	}
	throw std::runtime_error("addSystemInternal : invalid system");
}


bool ECS::SystemList::removeSystemInternal(ECS::BaseSystem& system)
{
	auto sys = std::ref(system);
	auto res = std::find_if(R_ENTIRE(systems_m), [sys](BaseSystemHandler elem){
		return &sys.get() == elem;
	});
	if (res != systems_m.end()) {
		systems_m.erase(res);
		return true;
	}
	return false;
}

