#pragma once

struct Version
{
	static constexpr int Major = 1;
	static constexpr int Minor = 0;
	static constexpr int Patch = 0;
	static constexpr const char* ToString()
	{
		return "1.0.0";
	}
};