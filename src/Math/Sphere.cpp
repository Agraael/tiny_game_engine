/*
** EPITECH PROJECT, 2021
** ECS
** File description:
** Created by MCESC, 12/8/2018
*/

#include "Sphere.hpp"

double Math3d::Sphere::getRadius() const noexcept
{
	return radius.magnitude();
}

constexpr Math3d::Vector3 const& Math3d::Sphere::getCenter() const noexcept
{
	return center;
}

constexpr void Math3d::Sphere::setCenter(Math3d::Vector3 const& new_center) noexcept
{
	center = new_center;
}

constexpr void Math3d::Sphere::setCenter(double x, double y, double z) noexcept
{
	center.x = x;
	center.y = y;
	center.z = z;
}

constexpr void Math3d::Sphere::setRadius(Math3d::Vector3 const& new_radius) noexcept
{
	radius = new_radius;
}

void Math3d::Sphere::setRadius(double new_radius) noexcept
{
	radius.magnitude(new_radius);
}

bool Math3d::Sphere::intersect(Math3d::Sphere const& sphere) noexcept
{
	return (radius.magnitude() + sphere.getRadius()) >= center.distance(sphere.getCenter());
}

bool Math3d::Sphere::contain(Math3d::Vector3 const& point) noexcept
{
	return radius.magnitude() >= center.distance(point);
}

bool Math3d::Sphere::contain(Math3d::Sphere const& sphere) noexcept
{
	return radius.magnitude() >= (sphere.getRadius() + center.distance(sphere.getCenter()));
}

double Math3d::Sphere::volume() const noexcept
{
	return ((M_PI * 4) / 3) * std::pow(radius.magnitude(), 3.0);
}

