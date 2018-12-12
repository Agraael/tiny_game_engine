/*
** EPITECH PROJECT, 2021
** ECS
** File description:
** Created by kraken, 05/12/18
*/

#include <tuple>
#include "Vector3.hpp"

void Math3d::Vector3::set(double x, double y, double z) noexcept
{
	this->x = x;
	this->y = y;
	this->z = z;
}

constexpr Math3d::Vector3& Math3d::Vector3::operator+=(Math3d::Vector3 const& rhs) noexcept
{
	this->x += rhs.x;
	this->y += rhs.y;
	this->z += rhs.z;
	return *this;
}

constexpr Math3d::Vector3 Math3d::Vector3::operator+(Math3d::Vector3 const& rhs) const noexcept
{
	return {
		this->x + rhs.x,
		this->y + rhs.y,
		this->z + rhs.z
	};
}

constexpr void Math3d::Vector3::add(Math3d::Vector3 const& rhs) noexcept
{
	*this += rhs;
}

constexpr Math3d::Vector3& Math3d::Vector3::operator-=(Math3d::Vector3 const& rhs) noexcept
{
	this->x -= rhs.x;
	this->y -= rhs.y;
	this->z -= rhs.z;
	return *this;
}

constexpr Math3d::Vector3 Math3d::Vector3::operator-(Math3d::Vector3 const& rhs) const noexcept
{
	return {
		this->x - rhs.x,
		this->y - rhs.y,
		this->z - rhs.z
	};
}

constexpr void Math3d::Vector3::sub(Math3d::Vector3 const& rhs) noexcept
{
	*this -= rhs;
}


constexpr Math3d::Vector3& Math3d::Vector3::operator*=(double scalar) noexcept
{
	this->x *= scalar;
	this->y *= scalar;
	this->z *= scalar;
	return *this;
}

constexpr Math3d::Vector3 Math3d::Vector3::operator*(double scalar) const noexcept
{
	return {
		this->x * scalar,
		this->y * scalar,
		this->z * scalar,
	};
}

constexpr Math3d::Vector3 Math3d::operator*(double scalar, Math3d::Vector3 const& rhs) noexcept
{
	return {
		rhs.x * scalar,
		rhs.y * scalar,
		rhs.z * scalar,
	};
}

constexpr void Math3d::Vector3::mult(double scalar) noexcept
{
	*this *= scalar;
}


constexpr Math3d::Vector3& Math3d::Vector3::operator/=(double scalar) noexcept
{
	this->x /= scalar;
	this->y /= scalar;
	this->z /= scalar;
	return *this;
}

constexpr Math3d::Vector3 Math3d::Vector3::operator/(double scalar) const noexcept
{
	return {
		this->x / scalar,
		this->y / scalar,
		this->z / scalar
	};
}

constexpr Math3d::Vector3 Math3d::operator/(double scalar, Math3d::Vector3 const& rhs) noexcept
{

	return {
		rhs.x / scalar,
		rhs.y / scalar,
		rhs.z / scalar,
	};
}

constexpr void Math3d::Vector3::div(double scalar) noexcept
{
	*this /= scalar;
}

constexpr double Math3d::Vector3::operator*(Math3d::Vector3 const& rhs) const noexcept
{
	return (this->x * rhs.x) + (this->y * rhs.y) + (this->z * rhs.z);
}

constexpr double Math3d::Vector3::dot(Math3d::Vector3 const& rhs) noexcept
{
	return *this * rhs;
}

std::ostream& Math3d::operator<<(std::ostream& os, Math3d::Vector3 const& vector3)
{
	os << "x: " << vector3.x << " y: " << vector3.y << " z: " << vector3.z;
	return os;
}

double Math3d::Vector3::magnitude() const noexcept
{
	return std::sqrt(std::pow(x, 2.0f) + std::pow(y, 2.0f) + std::pow(z, 2.0f));
}


void Math3d::Vector3::magnitude(double mag)
{
	if (mag < 0.0f)
		throw std::runtime_error("Vector3 : magnitude cannot be set to negative");
	normalize();
	*this *= mag;
}


constexpr Math3d::Vector3 Math3d::Vector3::cross(Math3d::Vector3 const& rhs) const noexcept
{
	return {
		(this->y * rhs.z) - (this->z * rhs.y),
		(this->z * rhs.x) - (this->x * rhs.z),
		(this->x * rhs.y) - (this->y * rhs.x)
	};
}

constexpr Math3d::Vector3& Math3d::Vector3::operator%=(Math3d::Vector3 const& rhs) noexcept
{
	this->x = (this->y * rhs.z) - (this->z * rhs.y);
	this->y = (this->z * rhs.x) - (this->x * rhs.z);
	this->z = (this->x * rhs.y) - (this->y * rhs.x);
	return *this;
}

constexpr Math3d::Vector3 Math3d::Vector3::operator%(Math3d::Vector3 const& rhs) const noexcept
{
	return {
		(this->y * rhs.z) - (this->z * rhs.y),
		(this->z * rhs.x) - (this->x * rhs.z),
		(this->x * rhs.y) - (this->y * rhs.x)
	};
}

Math3d::degree Math3d::Vector3::angleXY(Math3d::Vector3 const& rhs) const noexcept
{
	return Math3d::radianToDegree(std::atan2(this->y, this->x) - std::atan2(rhs.y, rhs.x));
}

Math3d::degree Math3d::Vector3::angleXZ(Math3d::Vector3 const& rhs) const noexcept
{
	return Math3d::radianToDegree(std::atan2(this->x, this->z) - std::atan2(rhs.x, rhs.z));
}

Math3d::degree Math3d::Vector3::angleZY(Math3d::Vector3 const& rhs) const noexcept
{
	return Math3d::radianToDegree(std::atan2(this->y, this->z) - std::atan2(rhs.y, rhs.z));
}

Math3d::degree Math3d::Vector3::angleAbsXY(Math3d::Vector3 const& rhs) const noexcept
{
	Vector3 a(this->x, this->y, 0.0f);
	Vector3 b(rhs.x, rhs.y, 0.0f);

	return Math3d::radianToDegree(std::acos((a * b) / (a.magnitude() * b.magnitude())));
}

Math3d::degree Math3d::Vector3::angleAbsXZ(Math3d::Vector3 const& rhs) const noexcept
{
	Vector3 a(this->x, 0.0f, this->z);
	Vector3 b(rhs.x, 0.0f, rhs.z);

	return Math3d::radianToDegree(std::acos((a * b) / (a.magnitude() * b.magnitude())));

}

Math3d::degree Math3d::Vector3::angleAbsZY(Math3d::Vector3 const& rhs) const noexcept
{
	Vector3 a(0.0f, this->y, this->z);
	Vector3 b(0.0f, rhs.y, rhs.z);

	return Math3d::radianToDegree(std::acos((a * b) / (a.magnitude() * b.magnitude())));
}

void Math3d::Vector3::normalize() noexcept
{
	double mag = magnitude();

	if (mag > 0.0f)
		*this *= (1.0f / mag);
}

void Math3d::Vector3::rotateXY(Math3d::degree angle) noexcept
{
	double tmp_x = x;
	double tmp_y = y;

	angle = degreeToRadian(angle);
	this->x = Math3d::double_round((std::cos(angle) * tmp_x) - (std::sin(angle) * tmp_y));
	this->y = Math3d::double_round((std::sin(angle) * tmp_x) + (std::cos(angle) * tmp_y));
}

void Math3d::Vector3::rotateXZ(Math3d::degree angle) noexcept
{
	double tmp_x = x;
	double tmp_z = z;

	angle = degreeToRadian(angle);
	this->x = Math3d::double_round((std::cos(angle) * tmp_x) + (std::sin(angle) * tmp_z));
	this->z = Math3d::double_round(-(std::sin(angle) * tmp_x) + (std::cos(angle) * tmp_z));
}

void Math3d::Vector3::rotateZY(Math3d::degree angle) noexcept
{
	double tmp_y = y;
	double tmp_z = z;

	angle = degreeToRadian(angle);
	this->y = Math3d::double_round((std::cos(angle) * tmp_y) - (std::sin(angle) * tmp_z));
	this->z = Math3d::double_round((std::sin(angle) * tmp_y) + (std::cos(angle) * tmp_z));
}

double Math3d::Vector3::distance(Math3d::Vector3 const& rhs) const noexcept
{
	return (*this - rhs).magnitude();
}

double Math3d::Vector3::distance(Math3d::Vector3 const& lhs, Math3d::Vector3 const& rhs) noexcept
{
	return (lhs - rhs).magnitude();
}

constexpr double Math3d::Vector3::max() const noexcept
{
	return std::max({x, y, z});
}

double Math3d::Vector3::maxAbs() const noexcept
{
	return std::max({std::abs(x), std::abs(y), std::abs(z)});
}

constexpr double Math3d::Vector3::min() const noexcept
{
	return std::min({x, y, z});
}

double Math3d::Vector3::minAbs() const noexcept
{
	return std::min({std::abs(x), std::abs(y), std::abs(z)});
}

constexpr Math3d::Vector3 Math3d::Vector3::reflect(Math3d::Vector3 const& vector, Math3d::Vector3 const& normalVec) noexcept
{
	return (-2.0f * (vector * normalVec) * normalVec + vector);
}

constexpr Math3d::Vector3 Math3d::Vector3::reflect(Math3d::Vector3 const& normalVec) const noexcept
{
	return (-2.0f * (*this * normalVec) * normalVec + *this);
}
