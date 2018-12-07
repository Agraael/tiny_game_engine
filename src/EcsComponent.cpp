/*
** EPITECH PROJECT, 2021
** ECS
** File description:
** Created by MCESC, 11/26/2018
*/

#include <memory>
#include "EcsComponent.hpp"

ECS::CompIndex ECS::BaseComponent::registerComponentType(ComponentCreateFunction createfn, ComponentDeleteFunction deletefn, size_t size)
{
	auto componentId = BaseComponent::componentTypeWrapper().size();
	BaseComponent::componentTypeWrapper().emplace_back(createfn, deletefn, size);
	return componentId;
}