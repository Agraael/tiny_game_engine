/*
** EPITECH PROJECT, 2021
** ECS
** File description:
** Created by kraken, 05/12/18
*/

#include <tuple>
#include "Vector3.hpp"

Math3d::Vector3& Math3d::Vector3::operator+=(Math3d::Vector3 const& rhs)
{
	this->x += rhs.x;
	this->y += rhs.y;
	this->z += rhs.z;
	return *this;
}

Math3d::Vector3 Math3d::Vector3::operator+(Math3d::Vector3 const& rhs)
{
	return {
		this->x + rhs.x,
		this->y + rhs.y,
		this->z + rhs.z
	};
}

Math3d::Vector3& Math3d::Vector3::operator-=(Math3d::Vector3 const& rhs)
{
	this->x -= rhs.x;
	this->y -= rhs.y;
	this->z -= rhs.z;
	return *this;
}

Math3d::Vector3 Math3d::Vector3::operator-(Math3d::Vector3 const& rhs)
{
	return {
		this->x - rhs.x,
		this->y - rhs.y,
		this->z - rhs.z
	};
}

Math3d::Vector3& Math3d::Vector3::operator*=(double scalar)
{
	this->x *= scalar;
	this->y *= scalar;
	this->z *= scalar;
	return *this;
}

Math3d::Vector3 Math3d::Vector3::operator*(double scalar)
{
	return {
		this->x * scalar,
		this->y * scalar,
		this->z * scalar,
	};
}

Math3d::Vector3& Math3d::Vector3::operator/=(double scalar)
{
	this->x /= scalar;
	this->y /= scalar;
	this->z /= scalar;
	return *this;
}

Math3d::Vector3 Math3d::Vector3::operator/(double scalar)
{
	return {
		this->x / scalar,
		this->y / scalar,
		this->z / scalar
	};
}

double Math3d::Vector3::operator*(Math3d::Vector3 const& rhs)
{
	return (this->x * rhs.x) + (this->y * rhs.y) + (this->z * rhs.z);
}

double Math3d::Vector3::dot(Math3d::Vector3 const& rhs)
{
	return *this * rhs;
}

std::ostream& Math3d::operator<<(std::ostream& os, Math3d::Vector3 const& vector3)
{
	os << "x: " << vector3.x << " y: " << vector3.y << " z: " << vector3.z;
	return os;
}

double Math3d::Vector3::magnitude() const
{
	return std::sqrt(std::pow(x, 2.0f) + std::pow(y, 2.0f) + std::pow(z, 2.0f));
}

Math3d::Vector3 Math3d::Vector3::cross(Math3d::Vector3 const& rhs)
{
	return {
		(this->y * rhs.z) - (this->z) * (rhs.y),
		(this->z * rhs.x) - (this->x * rhs.z),
		(this->x * rhs.y) - (this->y * rhs.x)
	};
}

Math3d::Vector3& Math3d::Vector3::operator%=(Math3d::Vector3 const& rhs)
{
	this->x = (this->y * rhs.z) - (this->z) * (rhs.y);
	this->y = (this->z * rhs.x) - (this->x * rhs.z);
	this->z = (this->x * rhs.y) - (this->y * rhs.x);
	return *this;
}

Math3d::Vector3 Math3d::Vector3::operator%(Math3d::Vector3 const& rhs)
{
	return {
		(this->y * rhs.z) - (this->z) * (rhs.y),
		(this->z * rhs.x) - (this->x * rhs.z),
		(this->x * rhs.y) - (this->y * rhs.x)
	};
}

Math3d::radian Math3d::Vector3::angleXY(Math3d::Vector3 const& rhs)
{
	Vector3 a(this->x, this->y, 0.0f);
	Vector3 b(rhs.x, rhs.y, 0.0f);

	return std::acos((a * b) / (a.magnitude() * b.magnitude()));
}

Math3d::radian Math3d::Vector3::angleXZ(Math3d::Vector3 const& rhs)
{
	Vector3 a(this->x, 0.0f, this->z);
	Vector3 b(rhs.x, 0.0f, rhs.z);

	return std::acos((a * b) / (a.magnitude() * b.magnitude()));

}

Math3d::radian Math3d::Vector3::angleZY(Math3d::Vector3 const& rhs)
{
	Vector3 a(0.0f, this->y, this->z);
	Vector3 b(0.0f, rhs.y, rhs.z);

	return std::acos((a * b) / (a.magnitude() * b.magnitude()));
}

void Math3d::Vector3::normalize()
{
	double mag = magnitude();

	if (mag > 0.0f)
		*this *= (1.0f / mag);
}

void Math3d::Vector3::rotateXY(Math3d::radian angle)
{
	double tmp_x = x;
	double tmp_y = y;

	this->x = (std::cos(angle) * tmp_x) - (std::sin(angle) * tmp_y);
	this->y = (std::sin(angle) * tmp_x) + (std::cos(angle) * tmp_y);
}

void Math3d::Vector3::rotateXZ(Math3d::radian angle)
{
	double tmp_x = x;
	double tmp_z = z;

	this->x = (std::cos(angle) * tmp_x) + (std::sin(angle) * tmp_z);
	this->z = -(std::sin(angle) * tmp_x) + (std::cos(angle) * tmp_z);
}

void Math3d::Vector3::rotateZY(Math3d::radian angle)
{
	double tmp_y = y;
	double tmp_z = z;

	this->y = (std::cos(angle) * tmp_y) - (std::sin(angle) * tmp_z);
	this->z = (std::sin(angle) * tmp_y) + (std::cos(angle) * tmp_z);
}

