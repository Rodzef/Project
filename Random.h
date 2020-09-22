#pragma once

#include <random>

struct Random
{
public:
	Random() = delete;
	Random(const Random&) = delete;
	Random& operator=(const Random&) = delete;

	static float Next()
	{
		return s_Distribution(s_Engine);
	}

	static float Next(float min, float max)
	{
		return s_Distribution(s_Engine) * (max - min) + min;
	}

	static int32_t NextInt(int32_t min, int32_t max)
	{
		return static_cast<int32_t>(s_Distribution(s_Engine) * (max - min) + min);
	}

private:
	static std::mt19937 s_Engine;
	static std::uniform_real_distribution<float> s_Distribution;
};
