#pragma once

#include <iostream>

namespace debug
{
	void Log(const char* message)
	{
		std::cout << message << std::endl;
	}

	void Err(const char* message)
	{
		std::cout << "ERROR: " << message << std::endl;
	}
}