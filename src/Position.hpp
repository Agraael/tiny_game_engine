/*
** EPITECH PROJECT, 2021
** ECS
** File description:
** Created by MCESC, 11/28/2018
*/

#pragma once

#include <iostream>
#include "EcsComponent.hpp"
#include "EcsSystem.hpp"

struct PositionComponent : public ECS::Component<PositionComponent>
{
	float x {0};
	float y {0};
};

struct MovementComponent : public ECS::Component<MovementComponent>
{
	float x {0};
	float y {0};
};

class PositionShowSystem : public ECS::BaseSystem
{
public:
	PositionShowSystem() {
		addComponent(PositionComponent::TypeId);
		addComponent(MovementComponent::TypeId, ECS::CmpFlags::OPTIONAL);
	}

	void updateComponents(std::vector<ECS::BaseComponentHandler>& components, [[maybe_unused]] float delta) final
	{
		auto* position = reinterpret_cast<PositionComponent*>(components[0]);
		auto* move = reinterpret_cast<MovementComponent*>(components[1]);

		if (move == nullptr) {
			std::cout << "no move" << std::endl;
			return;
		}
		std::cout << "Entity [" << position->entity->getId() << "] is at postion : ";
		std::cout << "[y = " << position->y << "] [x = " << position->x << "]" << std::endl;
	}
};
