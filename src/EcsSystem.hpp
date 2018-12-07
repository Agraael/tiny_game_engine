/*
** EPITECH PROJECT, 2021
** ECS
** File description:
** Created by MCESC, 11/26/2018
*/

#pragma once

#include "EcsComponent.hpp"
#include "utils.hpp"

namespace ECS
{
	enum CmpFlags : uint64_t
	{
		REQUIRED = 0,
		OPTIONAL = 1,
	};

	class BaseSystem
	{
	public:
		BaseSystem() = default;
		virtual ~BaseSystem() = default;
		virtual void updateComponents(std::vector<BaseComponentHandler>& components,
		                              [[maybe_unused]] float delta) = 0;

		[[nodiscard]] inline std::vector<CompTypeId> const& getComponentsTypes() const {
			return componentsTypes;
		}
		[[nodiscard]] inline std::vector<CmpFlags> const& getComponentsFlags() const {
			return componentsFlags;
		}
		[[nodiscard]] inline bool isValid() {
			for (auto& flag : componentsFlags) {
				if ((flag & CmpFlags::OPTIONAL) == false)
					return true;
			}
			return false;
		}

	protected:
		inline void addComponent(CompTypeId type, CmpFlags flag = CmpFlags::REQUIRED) {
			componentsTypes.push_back(type);
			componentsFlags.push_back(flag);
		}
	private:
		std::vector<CompTypeId> componentsTypes {};
		std::vector<CmpFlags> componentsFlags {};

	};

	using BaseSystemHandler = BaseSystem*;

	class SystemList
	{
	public:
		// systems_m methods
		[[nodiscard]] inline std::vector<BaseSystemHandler> const& getSystems() const {
				return systems_m;
		}
		[[nodiscard]] inline size_t getSize() {
			return systems_m.size();
		}
		[[nodiscard]] inline BaseSystem& operator[] (size_t index) {
			return *systems_m.at(index);
		}

		VAR_TEMPLATE_OF_BASE(Args, BaseSystem, 1)
		void addSystem(Args& ... args) {
			(addSystemInternal(args), ...);
		}

		VAR_TEMPLATE_OF_BASE(Args, BaseSystem, 1)
		bool removeSystem(Args& ... args) {
			bool err = (!removeSystemInternal(args) || ...);
			return !err;
		}

	private:
		std::vector<BaseSystemHandler> systems_m {};

		void addSystemInternal(BaseSystem& system);
		bool removeSystemInternal(BaseSystem& system);

	};
}
