/*
** EPITECH PROJECT, 2021
** ECS
** File description:
** Created by MCESC, 11/26/2018
*/

#pragma  once

#include <cstdint>
#include "EcsComponent.hpp"

namespace ECS
{
	using ComponentList = std::vector<std::pair<CompTypeId, CompIndex>>;

	class Entity
	{
	public:
		explicit Entity(uint64_t index) : index_m(index), uniqueId(nextId()) {};

		[[nodiscard]] inline ComponentList& getComponents() {return components;}
		[[nodiscard]] inline uint64_t getIndex() const {return index_m;}
		[[nodiscard]] inline uint64_t getId() const {return uniqueId;}
		inline void setIndex(uint64_t index) {index_m = index;}


	private:
		ComponentList components {};
		uint64_t index_m;
		const uint64_t uniqueId;

		inline static uint64_t nextId() {
			static uint64_t val {0};
			return val++;
		}
	};
}
