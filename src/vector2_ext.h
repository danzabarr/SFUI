#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

namespace sf
{
	template <typename T>
	std::ostream& operator<<(std::ostream& os, const sf::Vector2<T>& vector)
	{
		return os << "(" << vector.x << ", " << vector.y << ")";
	}
};
