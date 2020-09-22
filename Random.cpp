#include <poorpch.h>
#include "Random.h"

std::mt19937 Random::s_Engine = std::mt19937(std::random_device()());
std::uniform_real_distribution<float> Random::s_Distribution(0.0f, 1.0f);
