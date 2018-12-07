/*
** EPITECH PROJECT, 2021
** ECS
** File description:
** Created by MCESC, 11/27/2018
*/

#pragma once

#define NO_COPY_AND_ASSIGN(T) \
	T(const T& other) = delete; \
	T& operator=([[maybe_unused]] T const& other) = delete;

#define P_ENTIRE(collection) collection->begin(), collection->end()
#define R_ENTIRE(collection) collection.begin(), collection.end()

#define LOG_ERROR "Error"
#define LOG_WARNING "Warning"
#define LOG_TYPE_RENDERER "Renderer"
#define LOG_TYPE_IO "IO"
#define DEBUG_LOG(category, level, message, ...) \
	fprintf(stderr, "[%s] ", category); \
	fprintf(stderr, "[%s] (%s:%d): ", level, __FILE__, __LINE__); \
	fprintf(stderr, message, ##__VA_ARGS__); \
	fprintf(stderr, "\n")
#define DEBUG_LOG_TEMP(message, ...) DEBUG_LOG("TEMP", "TEMP", message, ##__VA_ARGS__)
#define DEBUG_LOG_TEMP2(message) DEBUG_LOG("TEMP", "TEMP", "%s", message)

#define VAR_TEMPLATE_OF_BASE(TempName, BaseClass, minNb) template <typename ... TempName, \
	std::enable_if_t<(sizeof...(TempName) >= minNb)>* = nullptr, \
	typename = std::enable_if_t<std::conjunction_v<std::is_base_of<BaseClass, TempName>...>>>

#define VAR_TEMPLATE_IS_TYPE(TempName, BaseClass, minNb) template <typename ... TempName, \
	std::enable_if_t<(sizeof...(TempName) >= minNb)>* = nullptr, \
	typename = std::enable_if_t<std::conjunction_v<std::is_same<BaseClass, TempName>...>>>
