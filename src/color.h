#include <iomanip>
#include <algorithm>

typedef unsigned char uint8;
typedef unsigned int uint32;

namespace sfui
{
	// Helper functions

	static uint8 ftoi8(float f)
	{
		return static_cast<uint8>(std::clamp(f, 0.f, 1.f) * 255);
	}

	static uint32 htoi32(std::string hex)
	{
		// removes optional #
		if (hex.size() > 0 && hex[0] == '#')
			hex = hex.substr(1);

		// discards extra digits
		if (hex.size() > 8)
			hex = hex.substr(0, 8);

		// validate digits
		for (size_t i = 0; i < hex.size(); i++)
		{
			bool numeric = hex[i] >= '0' && hex[i] <= '9';
			bool lower = hex[i] >= 'a' && hex[i] <= 'f';
			bool upper = hex[i] >= 'A' && hex[i] <= 'F';

			if (!numeric && !lower && !upper)
			{
				std::cout << "Warning: failed to convert to color from hex string \"" << hex << "\"" << std::endl;
				return 0;
			}
		}

		// adds alpha if missing
		if (hex.size() <= 6)
			hex += "00";

		// adds leading zeros
		while(hex.size() < 8)
			hex = "0" + hex;

		uint32 value = 0;
		for (size_t i = 0; i < hex.size(); i++)
		{
			value <<= 4;
			if (hex[i] >= '0' && hex[i] <= '9')
				value |= hex[i] - '0';
			else if (hex[i] >= 'a' && hex[i] <= 'f')
				value |= hex[i] - 'a' + 10;
			else if (hex[i] >= 'A' && hex[i] <= 'F')
				value |= hex[i] - 'A' + 10;
		}
		return value;
	}

	float* RGBtoHSV(float r, float g, float b)
	{
		float HSV[3] = { 0, 0, 0 };
		float& h = HSV[0];
		float& s = HSV[1];
		float& v = HSV[2];

		float max = std::max({ r, g, b });
		float min = std::min({ r, g, b });

		v = max;

		float diff = max - min;
		s = max == 0.0f ? 0.0f : diff / max;

		if (max == min) {
			h = 0.0f;
		}
		else {
			if (max == r) {
				h = (g - b) / diff + (g < b ? 6.0f : 0.0f);
			}
			else if (max == g) {
				h = (b - r) / diff + 2.0f;
			}
			else {
				h = (r - g) / diff + 4.0f;
			}

			h /= 6.0f;
		}

		return HSV;
	}

	/// <summary>
	/// Stores color data in a union of 1x uint32 and 4x uint8. 
	/// Data can be accessed as a composite or as individual channels.
	/// </summary>
	union ColorData
	{
		uint32 composite;
		uint8 channels[4];

		ColorData(uint32 rgba) :
			composite(rgba)
		{}

		ColorData(uint8 red, uint8 green, uint8 blue, uint8 alpha) :
			channels{ alpha, blue, green, red }
		{}
	};

	/// <summary>
	/// Holds a reference to one of the four bytes of a color data object.
	/// Deals with floating point to byte conversion, assignment, comparison and arithmetic.
	/// </summary>
	struct ColorChannel
	{
		uint8& value;

		ColorChannel(uint8& value) :
			value(value)
		{}

		ColorChannel(const ColorChannel& other) :
			value(other.value)
		{}

		// float conversion
		operator float() const
		{
			return static_cast<float>(value) / 255.f;
		}

		// float assignment
		ColorChannel& operator=(float value)
		{
			this->value = ftoi8(value);
			return *this;
		}

		// float comparison
		bool operator==(const float& other) const
		{
			return ftoi8(other) == value;
		}
		bool operator!=(const float& other) const
		{
			return ftoi8(other) != value;
		}

		// float arithmetic
		ColorChannel& operator+=(const float& other)
		{
			value = ftoi8(static_cast<float>(value) / 255.f + other);
			return *this;
		}

		ColorChannel& operator-=(const float& other)
		{
			value = ftoi8(static_cast<float>(value) / 255.f - other);
			return *this;
		}

		ColorChannel& operator*=(const float& other)
		{
			value = ftoi8(static_cast<float>(value) / 255.f * other);
			return *this;
		}

		ColorChannel& operator/=(const float& other)
		{
			value = ftoi8(static_cast<float>(value) / 255.f / other);
			return *this;
		}

		// float arithmetic
		float operator+(const float& other) const
		{
			return static_cast<float>(value) / 255.f + other;
		}

		float operator-(const float& other) const
		{
			return static_cast<float>(value) / 255.f - other;
		}

		float operator*(const float& other) const
		{
			return static_cast<float>(value) / 255.f * other;
		}

		float operator/(const float& other) const
		{
			return static_cast<float>(value) / 255.f / other;
		}
	};

	struct Color
	{
	public:
		ColorData data;
		ColorChannel red;
		ColorChannel green;
		ColorChannel blue;
		ColorChannel alpha;

	public:

		Color() :
			data(0),
			red(data.channels[3]), green(data.channels[2]), blue(data.channels[1]), alpha(data.channels[0])
		{}

		Color(uint32 rgba) :
			data(rgba),
			red(data.channels[3]), green(data.channels[2]), blue(data.channels[1]), alpha(data.channels[0])
		{}

		Color(std::string hex) :
			data(htoi32(hex)),
			red(data.channels[3]), green(data.channels[2]), blue(data.channels[1]), alpha(data.channels[0])
		{}

		Color(float red, float green, float blue, float alpha = 1.f) :
			data(ftoi8(red), ftoi8(green), ftoi8(blue), ftoi8(alpha)),
			red(data.channels[3]), green(data.channels[2]), blue(data.channels[1]), alpha(data.channels[0])
		{}

		Color(const Color& other) :
			data(other.data),
			red(data.channels[3]), green(data.channels[2]), blue(data.channels[1]), alpha(data.channels[0])
		{}

		// uint32 conversion
		operator uint32() const
		{
			return data.composite;
		}

		// Color assignment
		Color& operator=(const Color& other)
		{
			data.composite = other.data.composite;
			return *this;
		}

		// uint32 assignment
		Color& operator=(const uint32 rgba)
		{
			data.composite = rgba;
			return *this;
		}

		// string assignment
		//Color& operator=(const std::string& hex)
		//{
		//	data.composite = htoi32(hex);
		//	return *this;
		//}

		// float arithmetic (just scaling)
		Color& operator*=(const float& other)
		{
			red *= other;
			green *= other;
			blue *= other;
			alpha *= other;
			return *this;
		}

		Color& operator/=(const float& other)
		{
			red /= other;
			green /= other;
			blue /= other;
			alpha /= other;
			return *this;
		}

		friend Color operator*(const Color& lhs, const float& rhs)
		{
			Color result(lhs);
			result *= rhs;
			return result;
		}

		friend Color operator/(const Color& lhs, const float& rhs)
		{
			Color result(lhs);
			result /= rhs;
			return result;
		}

		// Color arithmetic
		Color& operator+=(const Color& other)
		{
			red += other.red;
			green += other.green;
			blue += other.blue;
			alpha += other.alpha;
			return *this;
		}

		Color& operator-=(const Color& other)
		{
			red -= other.red;
			green -= other.green;
			blue -= other.blue;
			alpha -= other.alpha;
			return *this;
		}

		Color& operator*=(const Color& other)
		{
			red *= other.red;
			green *= other.green;
			blue *= other.blue;
			alpha *= other.alpha;
			return *this;
		}

		Color& operator/=(const Color& other)
		{
			red /= other.red;
			green /= other.green;
			blue /= other.blue;
			alpha /= other.alpha;
			return *this;
		}

		Color operator+(const Color& other) const
		{
			Color result(*this);
			result += other;
			return result;
		}

		Color operator-(const Color& other) const
		{
			Color result(*this);
			result -= other;
			return result;
		}

		Color operator*(const Color& other) const
		{
			Color result(*this);
			result *= other;
			return result;
		}

		Color operator/(const Color& other) const
		{
			Color result(*this);
			result /= other;
			return result;
		}
	};

	std::ostream& operator<<(std::ostream& os, const ColorChannel& channel)
	{
		return os << std::hex << std::setfill('0') << std::uppercase << std::setw(2) << (uint32)channel.value;
	}

	std::ostream& operator<<(std::ostream& os, const Color& color)
	{
		os << "#" << std::hex << std::setfill('0') << std::uppercase << std::setw(8) << color.data.composite;

		float r = color.red;
		float g = color.green;
		float b = color.blue;
		float a = color.alpha;

		os << " r=" << std::fixed << std::setprecision(2) << r;
		os << " g=" << std::fixed << std::setprecision(2) << g;
		os << " b=" << std::fixed << std::setprecision(2) << b;
		os << " a=" << std::fixed << std::setprecision(2) << a;

		return os;
	}
}
