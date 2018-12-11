/*
** EPITECH PROJECT, 2021
** ECS
** File description:
** Created by MCESC, 12/8/2018
*/

#pragma once

#include "Vector3.hpp"

namespace Math3d
{
	class Sphere
	{
	public:
		constexpr Sphere() noexcept = default;
		constexpr Sphere(Vector3 const& new_center, Vector3 const& new_radius) noexcept
			: center(new_center), radius(new_radius) {}
		constexpr Sphere(Vector3 const& new_center, double new_radius) noexcept
			: center(new_center), radius(Vector3(1,0,0) * new_radius) {}
		constexpr Sphere(double x, double y, double z, Vector3 const& new_radius) noexcept
			: center(Vector3(x, y, z)), radius(new_radius) {}
		constexpr Sphere(double x, double y, double z, double new_radius) noexcept
			: center(Vector3(x, y, z)), radius(Vector3(1,0,0) * new_radius) {}

		~Sphere() = default;
		constexpr Sphere(Sphere const&) noexcept = default;
		Sphere& operator=(Sphere const&) noexcept = default;

		[[nodiscard]] double getRadius() const noexcept;
		constexpr void setRadius(Vector3 const&) noexcept;
		void setRadius(double) noexcept;

		[[nodiscard]] constexpr Vector3 const& getCenter() const noexcept;
		constexpr void setCenter(Vector3 const&) noexcept;
		constexpr void setCenter(double x, double y, double z) noexcept;

		bool intersects(Vector3 const& point);

	private:
		Vector3 center DEFAULT_0_VECTOR3;
		Vector3 radius DEFAULT_X_VECTOR3;
	};
}