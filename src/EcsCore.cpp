/*
** EPITECH PROJECT, 2021
** ECS
** File description:
** Created by MCESC, 11/26/2018
*/

#include <algorithm>
#include <iostream>
#include <cstring>
#include "EcsCore.hpp"

ECS::Core::~Core()
{
	std::for_each(R_ENTIRE(components_m),
	              [](std::pair<uint64_t const, MemoryChunk>& it) {
		              size_t typeSize = BaseComponent::getTypeSize(it.first);
		              ComponentDeleteFunction deleteFunction = BaseComponent::getTypeDeleteFunction(it.first);
		              for(uint64_t i = 0; i < it.second.size(); i += typeSize)
			              deleteFunction(reinterpret_cast<BaseComponentHandler>(&it.second[i]));
	});
}

void ECS::Core::removeEntityInternal(ECS::EntityHandler entity)
{
	ComponentList& componentList = entity->getComponents();

	std::for_each(R_ENTIRE(listener_m), [entity](ListenerHandler& listener){
		std::vector<CompTypeId> const& componentTypeId = listener->getComponentTypeIds();
		auto res1 = std::find_if(R_ENTIRE(componentTypeId), [entity](CompTypeId id){
			auto res2 = std::find_if(R_ENTIRE(entity->getComponents()), [id](std::pair<CompTypeId, CompIndex>& pair){
				return id == pair.first;
			});
			return res2 != entity->getComponents().end();
		});
		if (res1 != componentTypeId.end())
			listener->onRemoveEntity(entity);
	});

	std::for_each(R_ENTIRE(componentList), [this](std::pair<CompTypeId, CompIndex>& it) {
		deleteComponentInternal(it.first, it.second);
	});
	uint64_t destIndex = entity->getIndex();
	uint64_t srcIndex = entities_m.size() - 1;
	entities_m[destIndex] = entities_m[srcIndex];
	entities_m[destIndex]->setIndex(destIndex);
	entities_m.pop_back();
}

void ECS::Core::deleteComponentInternal(ECS::CompTypeId id, ECS::CompIndex index)
{
	ComponentDeleteFunction deleteFunction = BaseComponent::getTypeDeleteFunction(id);
	MemoryChunk& memoryChunk = components_m[id];
	size_t typeSize = BaseComponent::getTypeSize(id);
	uint64_t srcIndex = memoryChunk.size() - typeSize;

	auto destComponent = reinterpret_cast<BaseComponentHandler>(&memoryChunk[index]);
	auto srcComponent = reinterpret_cast<BaseComponentHandler>(&memoryChunk[srcIndex]);
	deleteFunction(destComponent);
	if (index == srcIndex) {
		memoryChunk.resize(srcIndex);
		return;
	}
	std::memcpy(&memoryChunk[index], &memoryChunk[srcIndex], typeSize);
	ComponentList& srcComponents = srcComponent->entity->getComponents();
	auto res = std::find_if(R_ENTIRE(srcComponents), [id, index](std::pair<CompTypeId, CompIndex>& it) {
		return (id == it.first && index == it.second);
	});
	if (res != srcComponents.end())
		res->second = index;
	memoryChunk.resize(srcIndex);
}

void ECS::Core::addComponentInternal(EntityHandler entity, ECS::CompTypeId typeId, ECS::BaseComponent const& component)
{
	if (!BaseComponent::isTypeValid(typeId))
		throw std::runtime_error("addComponentInternal : Invalid typeId component");
	ComponentCreateFunction createFunction = BaseComponent::getTypeCreateFunction(typeId);
	entity->getComponents().emplace_back(typeId, createFunction(components_m[typeId], entity, component));
}

bool ECS::Core::removeComponentInternal(ECS::EntityHandler entity, ECS::CompTypeId id)
{
	ComponentList& componentList = entity->getComponents();
	auto res = std::find_if(R_ENTIRE(componentList), [id](std::pair<CompTypeId, CompIndex>& it) {
		return (id == it.first);
	});
	if (res != componentList.end()) {
		deleteComponentInternal(res->first, res->second);
		uint64_t srcIndex = componentList.size() - 1;
		auto destIndex = static_cast<uint64_t>(std::distance(componentList.begin(), res));
		componentList[destIndex] = componentList[srcIndex];
		componentList.pop_back();
		return true;
	}
	return false;
}

ECS::BaseComponentHandler ECS::Core::getComponentInternal(ECS::EntityHandler& entity, ECS::CompTypeId id, MemoryChunk& memoryChunk)
{
	ComponentList& componentList = entity->getComponents();
	auto res = std::find_if(R_ENTIRE(componentList), [id, memoryChunk](std::pair<CompTypeId, CompIndex>& it) {
		return (id == it.first);
	});
	if (res != componentList.end())
		return reinterpret_cast<BaseComponentHandler>(&memoryChunk[res->second]);
	return nullptr;
}

void ECS::Core::updateSystems(SystemList& systems, float delta)
{
	std::vector<BaseComponentHandler> componentParams {};
	std::vector<MemoryChunk*> componentMemories {};

	std::for_each(R_ENTIRE(systems.getSystems()), [this, delta, componentParams, componentMemories] (BaseSystemHandler system)  mutable {
		std::vector<CompTypeId> const& componentTypes = system-> getComponentsTypes();
		if (componentTypes.size() == 1) {
			size_t typeSize = BaseComponent::getTypeSize(componentTypes[0]);
			MemoryChunk& memoryChunk = components_m[componentTypes[0]];
			for(uint64_t i = 0; i < memoryChunk.size(); i += typeSize) {
				auto component = reinterpret_cast<BaseComponentHandler>(&memoryChunk[i]);
				componentParams[0] = component;
				system->updateComponents(componentParams, delta);
			}
		}
		else {
			updateSystemWithMultipleComponent(delta, *system, componentTypes, componentParams, componentMemories);
		}
	});
}

void ECS::Core::updateSystemWithMultipleComponent(float delta, ECS::BaseSystem& system,
                                                  std::vector<ECS::CompTypeId> const& componentTypes,
	                                          std::vector<ECS::BaseComponentHandler>& componentParams,
	                                          std::vector<MemoryChunk*>& componentMemories)
{
	componentParams.resize(std::max(componentParams.size(), componentTypes.size()));
	componentMemories.resize(std::max(componentMemories.size(), componentTypes.size()));

	for (uint64_t index = 0; index < componentTypes.size(); ++index)
		componentMemories[index] = &components_m[index];

	std::vector<CmpFlags> const& componentFlags = system.getComponentsFlags();
	uint64_t minSizeIndex = findLeastCommonComponent(componentTypes, componentFlags);
	size_t typeSize = BaseComponent::getTypeSize(componentTypes[minSizeIndex]);
	MemoryChunk& memoryChunk = *componentMemories[minSizeIndex];
	for(uint64_t i = 0; i < memoryChunk.size(); i += typeSize) {
		componentParams[minSizeIndex] = reinterpret_cast<BaseComponentHandler>(&memoryChunk[i]);
		EntityHandler& componentList = componentParams[minSizeIndex]->entity;

		bool isValid {true};
		for (uint64_t j = 0; j < componentTypes.size(); ++j) {
			if (j == minSizeIndex)
				continue;
			componentParams[j] = getComponentInternal(componentList, componentTypes[j], *componentMemories[j]);
			if (componentParams[j] == nullptr && (componentFlags[j] & CmpFlags::OPTIONAL) == false) {
				isValid = false;
				break;
			}
		}
		if (isValid)
			system.updateComponents(componentParams, delta);
	}
}

ECS::CompTypeId ECS::Core::findLeastCommonComponent(std::vector<ECS::CompTypeId> const& componentTypes, std::vector<CmpFlags> const& componentFlags)
{
	uint64_t minSize = UINT8_MAX;
	CompIndex minIndex = UINT8_MAX;

	for(uint64_t i = 0; i < componentTypes.size(); i++) {
		if ( (componentFlags[i] & CmpFlags::OPTIONAL) == true)
			continue;
		size_t typeSize = BaseComponent::getTypeSize(componentTypes[i]);
		uint64_t size = components_m[componentTypes[i]].size() / typeSize;
		if (size <= minSize) {
			minSize = size;
			minIndex = i;
		}
	}
	return minIndex;
}

ECS::EntityHandler ECS::Core::getEntity(uint64_t id)
{
	auto res = std::find_if(R_ENTIRE(entities_m), [id](EntityHandler& entity){
		return entity->getId() == id;
	});
	if (res == entities_m.end())
		return NULL_ENTITY_HANDLER;
	return *res;
}

std::vector<ECS::EntityHandler> const& ECS::Core::getEntities() const
{
	return entities_m;
}
