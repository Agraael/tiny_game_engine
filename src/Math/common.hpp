/*
** EPITECH PROJECT, 2021
** ECS
** File description:
** Created by kraken, 05/12/18
*/

#pragma once

#include <cmath>

namespace Math3d
{
	using radian = double;
	using degree = double;

	static double precision {100000};

	[[gnu::pure, nodiscard]] constexpr degree radianToDegree(radian val) noexcept {
		return (val  * (180.0 / M_PI));
	}
	[[gnu::pure, nodiscard]] constexpr radian degreeToRadian(degree val) noexcept {
		return (val  * (M_PI / 180));
	}

	[[nodiscard]] inline double roundTo0(double val) {
		return round(val * precision) / precision;
	}
}