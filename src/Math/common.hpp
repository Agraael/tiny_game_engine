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

	#ifndef M_PI
		#define M_PI 3.141592653589793238463
	#endif

	static double precision {100000};

	[[gnu::pure, nodiscard]] constexpr inline degree radianToDegree(radian val) noexcept {
		return (val  * (180.0 / M_PI));
	}
	[[gnu::pure, nodiscard]] constexpr inline radian degreeToRadian(degree val) noexcept {
		return (val  * (M_PI / 180));
	}

	[[nodiscard]] inline double double_round(double val, double precision_val = precision) noexcept{
		return round(val * precision_val) / precision_val;
	}

	[[nodiscard]] inline bool double_equal(double a, double b, double epsilon = 1/precision) noexcept{
		return std::abs(a - b) < epsilon;
	}
}