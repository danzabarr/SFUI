#pragma once
#include <algorithm>
#include <sstream>
namespace sfui
{
	typedef unsigned int uint32;
	typedef unsigned char uint8;
	
	template<typename T>
	struct Proxy
	{
		virtual void operator= (T& value) = 0;

		virtual void operator= (Proxy<T>& proxy) = 0;

		virtual operator T() = 0;
	};

	struct Color
	{
		uint32 value;

		struct : public Proxy<uint8>
		{
			virtual void operator= (uint8& red)
			{
				Color& color = (*reinterpret_cast<Color*>(reinterpret_cast<uint8*>(&red) - 3));
				color.value = (color.value & 0xFFFFFF00) | red;
			}

			virtual void operator= (Proxy<uint8>& proxy)
			{
				Color& color = *reinterpret_cast<Color*>(reinterpret_cast<uint8*>(&proxy) - 3);
				color.value = (color.value & 0xFFFFFF00) | proxy;
			}

			virtual operator uint8()
			{
				Color& color = *reinterpret_cast<Color*>(reinterpret_cast<uint8*>(this) - 3);
				return color.value & 0xFF;
			}

		} red;

		Color() :
			value(0)
		{}

		Color(uint32 rgba) :
			value(rgba)
		{}

		Color(const Color& color) :
			value(color.value)
		{}

		Color(uint32 value)
			: value(value) 
		{}

		Color(uint8 r, uint8 g, uint8 b, uint8 a = 255) :
			value((a << 24) | (b << 16) | (g << 8) | r) 
		{}

		Color(float r, float g, float b, float a = 1.f) :
			value
			(
				(static_cast<uint32>(std::clamp(a, 0.f, 1.f) * 255) << 24) | 
				(static_cast<uint32>(std::clamp(b, 0.f, 1.f) * 255) << 16) |
				(static_cast<uint32>(std::clamp(g, 0.f, 1.f) * 255) << 8) |
				static_cast<uint32>(std::clamp(r, 0.f, 1.f) * 255)
			)
		{}

		uint32 operator() (const Color& color)
		{
			return color.value;
		}

		Color operator= (const Color& color)
		{
			value = color.value;
			return *this;
		}

		Color operator= (const uint32& rgba)
		{
			value = rgba;
			return *this;
		}

		Color operator= (const char* hex)
		{
			
		}

		static Color fromHex(const char* hex)
		{
			uint8 r = 0, g = 0, b = 0, a = 255;

			if (hex[0] == '#')
			{
				if (strlen(hex) == 7)
				{
					r = std::stoi(std::string(hex + 1, 2), (size_t*)nullptr, 16);
					g = std::stoi(std::string(hex + 3, 2), (size_t*)nullptr, 16);
					b = std::stoi(std::string(hex + 5, 2), (size_t*)nullptr, 16);
				}
				else if (strlen(hex) == 9)
				{
					r = std::stoi(std::string(hex + 1, 2), (size_t*)nullptr, 16);
					g = std::stoi(std::string(hex + 3, 2), (size_t*)nullptr, 16);
					b = std::stoi(std::string(hex + 5, 2), (size_t*)nullptr, 16);
					a = std::stoi(std::string(hex + 7, 2), (size_t*)nullptr, 16);
				}
				else
				{
					throw std::invalid_argument("Invalid color string");
				}
			}
			else
			{
				throw std::invalid_argument("Invalid color string");
			}
		}

		uint8 red() const
		{
			return (value >> 24) & 0xFF;
		}

		uint8 green() const
		{
			return (value >> 16) & 0xFF;
		}

		uint8 blue() const
		{
			return (value >> 8) & 0xFF;
		}

		uint8 alpha() const
		{
			return value & 0xFF;
		}

		static const Color White;
		static const Color Black;
		static const Color Red;
		static const Color Green;
		static const Color Blue;
		static const Color Yellow;
		static const Color Magenta;
		static const Color Cyan;
		static const Color Transparent;
	};

	const Color Color::White = 0xFFFFFFFF;
	const Color Color::Black = 0xFF000000;
	const Color Color::Red = 0xFFFF0000;
	const Color Color::Green = 0xFF00FF00;
	const Color Color::Blue = 0xFF0000FF;
	const Color Color::Yellow = 0xFFFFFF00;
	const Color Color::Magenta = 0xFFFF00FF;
	const Color Color::Cyan = 0xFF00FFFF;
	const Color Color::Transparent = 0x00000000;
}

using namespace sfui;

int main()
{
	Color red = Color::Red;
}