/*
** EPITECH PROJECT, 2021
** ECS
** File description:
** Created by kraken, 02/12/18
*/

#pragma once

#include "EcsInteraction.hpp"
#include "UtilsComponent.hpp"
#include "EcsCore.hpp"

class CollisionEngine : public ECS::Listener
{
public:
	explicit CollisionEngine(ECS::Core& core) :
		ECS::Listener(), core_ecs(core)
	{
		addComponentType(TransformComponent::TypeId);
		addComponentType(ColliderComponent::TypeId);
	}

	void onMakeEntity(ECS::EntityHandler entity) final;
	void onRemoveEntity(ECS::EntityHandler entity) final;
	void onAddComponent(ECS::EntityHandler entity, ECS::CompTypeId id) final;
	void onRemoveComponent(ECS::EntityHandler entity, ECS::CompTypeId id) final;

	VAR_TEMPLATE_OF_BASE(Args, ECS::Interaction, 1)
	void addInteraction(Args& ... args) {
		(addInteractionInternal(args), ...);
	}

	VAR_TEMPLATE_OF_BASE(Args, ECS::Interaction, 1)
	void removeInteraction(Args& ... args) {
		(removeInteractionInternal(args), ...);
	}

	void processInteractions(float delta);

private:

	struct EntityInternal {
		ECS::EntityHandler handle;
		std::vector<ECS::CompTypeId>& interactors;
		std::vector<ECS::CompTypeId>& interactees;
	};

	ECS::Core& core_ecs;
	std::vector<ECS::EntityHandler> entities {};
	std::vector<ECS::EntityHandler> entitiesToRemove {};
	std::vector<ECS::InteractionHandler> interactions {};
	uint32_t compare_axis {0};


	void addInteractionInternal(ECS::Interaction& interaction) {
		interactions.push_back(&interaction);
	}
	void removeInteraction(ECS::Interaction& interaction) {
		auto inter = std::ref(interaction);
		auto res = std::find_if(R_ENTIRE(interactions), [inter](ECS::InteractionHandler elem){
			return &inter.get() == elem;
		});
		if (res != interactions.end())
			interactions.erase(res);
	}
};