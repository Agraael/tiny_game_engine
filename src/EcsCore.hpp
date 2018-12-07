/*
** EPITECH PROJECT, 2021
** ECS
** File description:
** Created by MCESC, 11/26/2018
*/

#pragma once

#include <iostream>
#include <utility>
#include <algorithm>
#include <unordered_map>
#include "EcsComponent.hpp"
#include "EcsSystem.hpp"
#include "EcsEntity.hpp"
#include "utils.hpp"
#include "EcsInteraction.hpp"

namespace ECS
{

	class Core
	{
	public:
		Core() = default;
		virtual ~Core();

		// entity methods
		EntityHandler getEntity(uint64_t id);

		VAR_TEMPLATE_OF_BASE(Args, BaseComponent, 1)
		EntityHandler makeEntity(Args const& ... args) {
			auto entity = MAKE_ENTITY_HANDLER(entities_m.size());
			(addComponentInternal(entity, Args::TypeId, args), ...);
			entities_m.push_back(entity);
			std::for_each(R_ENTIRE(listener_m), [entity](ListenerHandler& listener){
				std::vector<CompTypeId> const& componentTypeId = listener->getComponentTypeIds();
				auto res1 = std::find_if(R_ENTIRE(componentTypeId), [entity](CompTypeId id){
					auto res2 = std::find_if(R_ENTIRE(entity->getComponents()), [id](std::pair<CompTypeId, CompIndex>& pair){
						return id == pair.first;
					});
					return res2 != entity->getComponents().end();
				});
				if (res1 != componentTypeId.end())
					listener->onMakeEntity(entity);
			});
			return entity;
		}

		VAR_TEMPLATE_OF_BASE(Args, Entity, 1)
		void removeEntity(Args& ... args) {
			(removeEntityInternal(args), ...);
		}

		VAR_TEMPLATE_OF_BASE(Args, Listener, 1)
		void addListener(Args& ... args) {
			(listener_m.push_back(&args), ...);
		}

		VAR_TEMPLATE_OF_BASE(Args, Listener, 1)
		void removeListener(Args& ... args) {
			([this, args](){
				auto newEnd = std::remove(R_ENTIRE(listener_m), &args);
				listener_m.erase(newEnd, listener_m.end());
			}(), ...);
		}

		// component methods
		template <class ComponentType>
		inline void addComponent(EntityHandler const& entity, ComponentType const& comp) {
			std::for_each(R_ENTIRE(listener_m), [entity](ListenerHandler& listener){
				std::vector<CompTypeId> const& componentTypeId = listener->getComponentTypeIds();
				auto res = std::find_if(R_ENTIRE(componentTypeId), [](CompTypeId id){
					return id == ComponentType::TypeId;
				});
				if (res != componentTypeId.end())
					listener->onAddComponent(entity, ComponentType::TypeId);
			});
			addComponentInternal(entity, ComponentType::TypeId, comp);
		}

		template <class ComponentType>
		inline bool removeComponent(EntityHandler const& entity) {
			std::for_each(R_ENTIRE(listener_m), [entity](ListenerHandler& listener){
				std::vector<CompTypeId> const& componentTypeId = listener->getComponentTypeIds();
				auto res = std::find_if(R_ENTIRE(componentTypeId), [](CompTypeId id){
					return id == ComponentType::TypeId;
				});
				if (res != componentTypeId.end())
					listener->onRemoveComponent(entity, ComponentType::TypeId);
			});
			return removeComponentInternal(entity, ComponentType::TypeId);
		}

		template <class ComponentType>
		ComponentType* getComponent(EntityHandler& entity) {
			return reinterpret_cast<ComponentType*>(getComponentInternal(entity, ComponentType::TypeId, components_m[ComponentType::TypeId]));
		}

		std::vector<EntityHandler> const& getEntities() const;
		void updateSystems(SystemList& systems, float delta);
	private:
		std::unordered_map<CompTypeId, MemoryChunk> components_m {};
		std::vector<EntityHandler> entities_m {};
		std::vector<ListenerHandler> listener_m {};

		void removeEntityInternal(EntityHandler entity);
		void deleteComponentInternal(CompTypeId id, CompIndex index);
		bool removeComponentInternal(EntityHandler entity, CompTypeId id);
		void addComponentInternal(std::shared_ptr<Entity> entity, CompTypeId id, ECS::BaseComponent const& component);
		BaseComponent* getComponentInternal(EntityHandler& entity, CompTypeId id, MemoryChunk& memoryChunk);
		void updateSystemWithMultipleComponent(float delta, BaseSystem& system,
		                                       std::vector<CompTypeId> const& componentTypes,
		                                       std::vector<BaseComponentHandler>& componentParams,
		                                       std::vector<MemoryChunk*>& componentMemories);
		CompTypeId findLeastCommonComponent(std::vector<CompTypeId> const& componentTypes, std::vector<CmpFlags> const& componentFlags);
	};
}
