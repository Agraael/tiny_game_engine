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
	#define DEFAULT_X_VECTOR3 {1, 0, 0}
	#define DEFAULT_Y_VECTOR3 {0, 1, 0}
	#define DEFAULT_Z_VECTOR3 {0, 0, 1}

	struct Vector3
	{
		Vector3() = default;
		Vector3(double new_x, double new_y, double new_z) noexcept
			: x(new_x), y(new_y), z(new_z)
		{}
		~Vector3() = default;
		Vector3(Vector3 const&) = default;
		Vector3& operator=(Vector3 const&) = default;

		double x {0};
		double y {0};
		double z {0};

		Vector3& operator+=(Vector3 const& rhs);
		Vector3 operator+(Vector3 const& rhs);
		Vector3& operator-=(Vector3 const& rhs);

		Vector3 operator-(Vector3 const& rhs);
		Vector3& operator*=(double scalar);
		Vector3 operator*(double scalar);
		Vector3& operator/=(double scalar);
		Vector3 operator/(double scalar);

		double dot(Vector3 const& rhs);
		double operator*(Vector3 const& rhs);

		double magnitude() const;
		void normalize();

		Vector3 cross(Vector3 const& rhs);
		Vector3& operator%=(Vector3 const& rhs);
		Vector3 operator%(Vector3 const& rhs);

		radian angleXY(Vector3 const& rhs = DEFAULT_Y_VECTOR3);
		radian angleXZ(Vector3 const& rhs = DEFAULT_Z_VECTOR3);
		radian angleZY(Vector3 const& rhs = DEFAULT_Z_VECTOR3);

		void rotateXY(radian angle);
		void rotateXZ(radian angle);
		void rotateZY(radian angle);
	};

	std::ostream& operator<<(std::ostream& os, Vector3 const& vector3);
}