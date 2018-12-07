/*
** EPITECH PROJECT, 2021
** ECS
** File description:
** Created by kraken, 02/12/18
*/

#pragma once

#include "EcsComponent.hpp"

namespace ECS
{
	class Listener
	{
	public:
		virtual ~Listener() = default;
		virtual void onMakeEntity(EntityHandler entity) = 0;
		virtual void onRemoveEntity(EntityHandler entity) = 0;
		virtual void onAddComponent(EntityHandler entity, CompTypeId id) = 0;
		virtual void onRemoveComponent(EntityHandler entity, CompTypeId id) = 0;

		std::vector<CompTypeId> const& getComponentTypeIds() const {
			return componentTypeIds;
		}

	protected:
		void addComponentType(CompTypeId id) {
			componentTypeIds.push_back(id);
		}

	private:
		std::vector<CompTypeId> componentTypeIds {};
	};

	using ListenerHandler = Listener*;

	class Interaction
	{
	public:
		virtual ~Interaction() = default;
		virtual void interact(std::vector<CompTypeId>& interactors,
		                      std::vector<CompTypeId>& interactees,
		                      float delta) = 0;
	protected:
		void addInteractorComponentType(CompTypeId id) {
			interactorComponentTypeId.push_back(id);
		}
		void addInteracteeComponentType(CompTypeId id) {
			interacteeComponentTypeId.push_back(id);
		}


	private:
		std::vector<CompTypeId> interactorComponentTypeId {};
		std::vector<CompTypeId> interacteeComponentTypeId {};
	};

	using InteractionHandler = Interaction*;
}