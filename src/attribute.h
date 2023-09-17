#pragma once

#include <string>
#include <sstream>

namespace sfui
{

	static sf::Color parse_color(const std::string& string)
	{
		// Hexadecimal color
		int r = 0, g = 0, b = 0, a = 255;

		if (string.length() == 0)
			throw std::invalid_argument("Invalid color string");

		if (string[0] == '#')
			return sf::Color(std::stoi(string.substr(1), (size_t*)nullptr, 16));


		return sf::Color(r, g, b, a);
	}

	template <typename T>
	std::ostream& operator<<(std::ostream& os, const sf::Color& color)
	{
		//hex string
		return os << "RGB: " << color.r << ", " << color.g << "," << color.b;

		//int i = color.toInteger();

		//return os << "#" << std::hex << color.toInteger() << os << " RGBA: " << color.r << ", " << color.g << ", " << color.b << ", " << color.a;
	}
}
