/*
** EPITECH PROJECT, 2021
** ECS
** File description:
** Created by MCESC, 11/26/2018
*/

#pragma once

#include <vector>
#include <tuple>
#include <cstdint>
#include <memory>

#define NULL_ENTITY_HANDLER nullptr
#define BUILD_ENTITY_HANDLER(entity) std::shared_ptr<ECS::Entity>(entity)
#define MAKE_ENTITY_HANDLER(entity) std::make_shared<ECS::Entity>(entity)

namespace ECS
{
	class BaseComponent;
	class Entity;
	using EntityHandler = std::shared_ptr<Entity>;
	using MemoryChunk = std::vector<uint8_t>;
	using CompTypeId = uint64_t;
	using CompIndex = uint64_t;
	using BaseComponentHandler = BaseComponent*;
	using ComponentCreateFunction = CompIndex (*)(MemoryChunk& memory, EntityHandler entity, ECS::BaseComponent const& comp);
	using ComponentDeleteFunction = void (*)(BaseComponent* comp);
	using BaseComponentTypeList = std::vector<std::tuple<ECS::ComponentCreateFunction, ECS::ComponentDeleteFunction, size_t>>;

	class BaseComponent
	{
	public :
		static uint64_t registerComponentType(ComponentCreateFunction createfn,
		                                      ComponentDeleteFunction deletefn,
		                                      size_t size);

		inline static ComponentCreateFunction getTypeCreateFunction(uint64_t id) {
			return std::get<0>(BaseComponent::componentTypeWrapper()[id]);
		};
		inline static ComponentDeleteFunction getTypeDeleteFunction(uint64_t id) {
			return std::get<1>(BaseComponent::componentTypeWrapper()[id]);
		};
		static size_t getTypeSize(uint64_t id) {
			return std::get<2>(BaseComponent::componentTypeWrapper()[id]);
		};
		inline static bool isTypeValid(uint64_t id) {
			return id <componentTypeWrapper().size();
		};

		inline static uint64_t getComponentTypeNumber() {
			return componentTypeWrapper().size();
		}
		EntityHandler entity {NULL_ENTITY_HANDLER};

	private:
		inline static BaseComponentTypeList& componentTypeWrapper() {
			static BaseComponentTypeList componentTypes {};
			return componentTypes;
		}
	};


	template <typename T>
	class Component : public BaseComponent
	{
	public:
		static const ComponentCreateFunction createfn;
		static const ComponentDeleteFunction deletefn;
		static const CompTypeId TypeId;
		static const size_t Size;

	};

	template <typename ComponentType>
	uint64_t ComponentCreate(MemoryChunk& memory, EntityHandler entity, ECS::BaseComponent const& comp)
	{
		uint64_t index = memory.size();

		memory.resize(index + ComponentType::Size);
		auto item = new(&memory[index]) ComponentType(std::move(reinterpret_cast<ComponentType const&>(comp)));
		item->entity = entity;
		return index;
	}

	template <typename ComponentType>
	void ComponentDelete(BaseComponent* comp)
	{
		auto item = reinterpret_cast<ComponentType*>(comp);
		item->~ComponentType();
	}

	template <typename T>
	const CompIndex Component<T>::TypeId{BaseComponent::registerComponentType(ComponentCreate<T>, ComponentDelete<T>, sizeof(T))};
	template <typename T>
	const size_t Component<T>::Size {sizeof(T)};

	template <typename T>
	const ComponentCreateFunction Component<T>::createfn {ComponentCreate<T>};
	template <typename T>
	const ComponentDeleteFunction Component<T>::deletefn {ComponentDelete<T>};

	template <typename T>
	inline void assertComponentTemplate() {
		static_assert(std::is_base_of<T, BaseComponent>::value, "assertComponentTemplate : T must inherit from BaseComponent");
	}

}