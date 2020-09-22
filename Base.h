#pragma once

#include <poorpch.h>
#include <SFML\System\Vector2.hpp>

inline std::ostream& operator<<(std::ostream& os, const sf::Vector2i message)
{
	return os << "(" << message.x << ", " << message.y << ")";
}

inline std::ostream& operator<<(std::ostream& os, const sf::Vector2f message)
{
	return os << "(" << message.x << ", " << message.y << ")";
}

inline std::ostream& operator<<(std::ostream& os, const sf::IntRect message)
{
	return os << "(" << message.left << ", " << message.top << ", " << message.width << ", " << message.height << ")";
}

inline std::ostream& operator<<(std::ostream& os, const sf::FloatRect message)
{
	return os << "(" << message.left << ", " << message.top << ", " << message.width << ", " << message.height << ")";
}

template<class T>
void clog(const T message)
{
	std::cout << message << std::endl;
}
