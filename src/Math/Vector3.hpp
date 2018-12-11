/*
** EPITECH PROJECT, 2021
** ECS
** File description:
** Created by kraken, 05/12/18
*/

#pragma once

#include <ostream>
#include <cmath>
#include "common.hpp"

namespace Math3d
{
	#define DEFAULT_0_VECTOR3 {0, 0, 0}
	#define DEFAULT_X_VECTOR3 {1, 0, 0}
	#define DEFAULT_Y_VECTOR3 {0, 1, 0}
	#define DEFAULT_Z_VECTOR3 {0, 0, 1}

	struct Vector3
	{
		constexpr Vector3() noexcept = default;
		constexpr Vector3(double new_x, double new_y, double new_z) noexcept
			: x(new_x), y(new_y), z(new_z) {}
		~Vector3() = default;
		constexpr Vector3(Vector3 const&) noexcept = default;
		constexpr Vector3& operator=(Vector3 const&) noexcept = default;

		double x {0};
		double y {0};
		double z {0};

		constexpr Vector3& operator+=(Vector3 const& rhs) noexcept;
		[[nodiscard]] constexpr Vector3 operator+(Vector3 const& rhs) const noexcept;
		constexpr void add(Vector3 const& rhs) noexcept;

		constexpr Vector3& operator-=(Vector3 const& rhs) noexcept;
		[[nodiscard]] constexpr Vector3 operator-(Vector3 const& rhs) const noexcept;
		constexpr void sub(Vector3 const& rhs) noexcept;


		constexpr Vector3& operator*=(double scalar) noexcept;
		[[nodiscard]] constexpr Vector3 operator*(double scalar) const noexcept;
		constexpr void mult(double scalar) noexcept;

		constexpr Vector3& operator/=(double scalar) noexcept;
		[[nodiscard]] constexpr Vector3 operator/(double scalar) const noexcept;
		constexpr void div(double scalar) noexcept;

		constexpr double dot(Vector3 const& rhs) noexcept;
		constexpr double operator*(Vector3 const& rhs) const noexcept;

		[[nodiscard]] double magnitude() const noexcept;
		void magnitude(double mag);
		void normalize() noexcept;

		constexpr Vector3 cross(Vector3 const& rhs) noexcept;
		constexpr Vector3& operator%=(Vector3 const& rhs) noexcept;
		[[nodiscard]] constexpr Vector3 operator%(Vector3 const& rhs) const noexcept;

		[[nodiscard]] degree angleXY(Vector3 const& rhs = DEFAULT_Y_VECTOR3) const noexcept;
		[[nodiscard]] degree angleXZ(Vector3 const& rhs = DEFAULT_Z_VECTOR3) const noexcept;
		[[nodiscard]] degree angleZY(Vector3 const& rhs = DEFAULT_Z_VECTOR3) const noexcept;

		void rotateXY(degree angle) noexcept;
		void rotateXZ(degree angle) noexcept;
		void rotateZY(degree angle) noexcept;

		[[nodiscard]] double distance(Vector3 const& rhs) const noexcept;
		[[nodiscard]] static double distance(Vector3 const& lhs, Vector3 const& rhs) noexcept;
	};

	std::ostream& operator<<(std::ostream& os, Vector3 const& vector3);
}