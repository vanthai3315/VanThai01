#pragma once

#include "Standard_Library.h"
template <typename Func, typename... Args>
double measureExecutionTime(Func&& func, Args&&... args)
{
	auto start = std::chrono::high_resolution_clock::now();

	std::invoke(std::forward<Func>(func), std::forward<Args>(args)...);

	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
	return duration.count() / 1000.0;
}

