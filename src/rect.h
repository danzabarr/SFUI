#pragma once

#include <ostream>
#include <type_traits>

namespace sfui
{
	template <typename T>
	struct ReferencePoint
	{
		T& x;
		T& y;

		ReferencePoint() = delete;
		ReferencePoint(const ReferencePoint& other) = delete;

		ReferencePoint(T& x, T& y) :
			x(x), y(y)
		{}

		ReferencePoint& operator=(const ReferencePoint& other)
		{
			x = other.x;
			y = other.y;
			return *this;
		}

		ReferencePoint& operator=(const sf::Vector2<T>& other)
		{
			x = other.x;
			y = other.y;
			return *this;
		}

		friend std::ostream& operator<<(std::ostream& os, const ReferencePoint<T>& other)
		{
			os << "(" << other.x << ", " << other.y << ")";
			return os;
		}
	};

	template <typename T> requires std::is_arithmetic_v<T>
	struct Sum
	{
		T& t0;
		T& t1;

		Sum(T& t0, T& t1) :
			t0(t0), t1(t1)
		{}

		Sum(const Sum& sum) :
			Sum(sum.t0, sum.t1)
		{}

		operator T() const
		{
			return t1 + t0;
		}

		Sum<T>& operator=(const Sum<T>& sum)
		{
			t0 = sum.t0;
			t1 = sum.t1;
			return *this;
		}

		static friend bool operator==(const Sum<T>& lhs, const T& rhs)
		{
			return lhs.t1 + lhs.t2 == rhs;
		}

		static friend bool operator!=(const Sum<T>& lhs, const T& rhs)
		{
			return !(lhs == rhs);
		}

		static friend bool operator <(const Sum<T>& lhs, const T& rhs)
		{
			return lhs.t1 + lhs.t0 < rhs;
		}

		Sum<T>& operator=(T value)
		{
			T diff = value - (t1 + t0);
			t0 += diff / 2;
			t1 += diff / 2;
			return *this;
		}

		Sum<T>& operator+=(T value)
		{
			t0 += value / 2;
			t1 += value / 2;
			return *this;
		}

		Sum<T>& operator-=(T value)
		{
			t0 += value / 2;
			t1 += value / 2;
			return *this;
		}

		static friend std::ostream& operator<<(std::ostream& os, const Sum<T>& sum)
		{
			os << (sum.t1 + sum.t0);
			return os;
		}
	};

	template<typename T> requires std::is_arithmetic_v<T>
	struct Difference
	{
		Difference(T& t0, T& t1) :
			t0(t0), t1(t1)
		{}

		operator T() const
		{
			return t1 - t0;
		}

		T operator=(const T& size)
		{
			T diff = size - (t1 - t0);
			t0 -= diff / 2;
			t1 += diff / 2;
			return size;
		}

		T operator=(const Difference<T>& dimension)
		{
			T diff = (dimension.t1 - dimension.t0) - (t1 - t0);
			t0 -= diff / 2;
			t1 += diff / 2;
			return dimension;
		}

		T operator+=(const T& size)
		{
			t0 -= size / 2;
			t1 += size / 2;
			return size;
		}

		T operator-=(const T& size)
		{
			t0 += size / 2;
			t1 -= size / 2;
			return size;
		}

		T& t0;
		T& t1;
	};

	template<typename T> requires std::is_arithmetic_v<T>
	struct Rect
	{
		T x0;
		T y0;
		T x1;
		T y1;

		T& x;
		T& y;
		Difference<T> width;
		Difference<T> height;

		ReferencePoint<T> top_left;
		ReferencePoint<T> top_right;
		ReferencePoint<T> bottom_left;
		ReferencePoint<T> bottom_right;

		Rect() :
			Rect(0, 0, 0, 0)
		{}

		Rect(T x, T y, T width, T height) :
			x0(x), y0(y), x1(x + width), y1(y + height),
			x(x0), y(y0), width(x0, x1), height(y0, y1),
			top_left(x0, y0), top_right(x1, y0), bottom_left(x0, y1), bottom_right(x1, y1)
		{}

		Rect(const Rect<T>& box) :
			Rect(box.x, box.y, box.width, box.height)
		{}

		Rect<T>& operator=(const Rect<T>& box)
		{
			x = box.x;
			y = box.y;
			width = box.width;
			height = box.height;
			return *this;
		}

		friend bool operator==(const Rect<T>& lhs, const Rect<T>& rhs)
		{
			return lhs.x == rhs.x && lhs.y == rhs.y && lhs.width == rhs.width && lhs.height == rhs.height;
		}

		friend bool operator!=(const Rect<T>& lhs, const Rect<T>& rhs)
		{
			return !(lhs == rhs);
		}

		friend std::ostream& operator<<(std::ostream& os, const Rect<T>& box)
		{
			os << "Box(" << box.x << ", " << box.y << ", " << box.width << ", " << box.height << ")";
			return os;
		}
	};

	template <typename T> requires std::is_arithmetic_v<T>
	struct Inset
	{
		T top;
		T left;
		T bottom;
		T right;

		Sum<T> width;
		Sum<T> height;

		ReferencePoint<T> top_left;
		ReferencePoint<T> top_right;
		ReferencePoint<T> bottom_left;
		ReferencePoint<T> bottom_right;

		Inset(T top, T left, T bottom, T right) :
			top(top), left(left), bottom(bottom), right(right),
			width(this->left, this->right), height(this->top, this->bottom),
			top_left(this->left, this->top), top_right(this->right, this->top),
			bottom_left(this->left, this->bottom), bottom_right(this->right, this->bottom)
		{}

		Inset() :
			Inset(0, 0, 0, 0)
		{}

		Inset(const Inset<T>& inset) :
			Inset(inset.top, inset.left, inset.bottom, inset.right)
		{}

		Inset(T width, T height) :
			Inset(height / 2, width / 2, height / 2, width / 2)
		{}

		Inset<T>& operator=(const Inset<T>& inset)
		{
			top = inset.top;
			left = inset.left;
			bottom = inset.bottom;
			right = inset.right;
			return *this;
		}

		Inset<T> operator+(const Inset<T>& inset)
		{
			return Inset<T>(top + inset.top, left + inset.left, bottom + inset.bottom, right + inset.right);
		}

		Inset<T> operator-(const Inset<T>& inset)
		{
			return Inset<T>(top - inset.top, left - inset.left, bottom - inset.bottom, right - inset.right);
		}

		Inset<T>& operator+=(const Inset<T>& inset)
		{
			top += inset.top;
			left += inset.left;
			bottom += inset.bottom;
			right += inset.right;
			return *this;
		}

		Inset<T>& operator-=(const Inset<T>& inset)
		{
			top -= inset.top;
			left -= inset.left;
			bottom -= inset.bottom;
			right -= inset.right;
			return *this;
		}

		Inset<T>& operator*(const T scalar)
		{
			top *= scalar;
			left *= scalar;
			bottom *= scalar;
			right *= scalar;
			return *this;
		}

		Inset<T>& operator/(const T scalar)
		{
			top /= scalar;
			left /= scalar;
			bottom /= scalar;
			right /= scalar;
			return *this;
		}

		Inset<T>& operator*=(const T scalar)
		{
			top *= scalar;
			left *= scalar;
			bottom *= scalar;
			right *= scalar;
			return *this;
		}

		Inset<T>& operator/=(const T scalar)
		{
			top /= scalar;
			left /= scalar;
			bottom /= scalar;
			right /= scalar;
			return *this;
		}

		friend bool operator==(const Inset<T>& lhs, const Inset<T>& rhs)
		{
			return lhs.top == rhs.top && lhs.left == rhs.left && lhs.bottom == rhs.bottom && lhs.right == rhs.right;
		}

		friend bool operator!=(const Inset<T>& lhs, const Inset<T>& rhs)
		{
			return !(lhs == rhs);
		}

		friend std::ostream& operator<<(std::ostream& os, const Inset<T>& inset)
		{
			os << "Inset [";
			os << "top: " << inset.top << ", ";
			os << "left: " << inset.left << ", ";
			os << "bottom: " << inset.bottom << ", ";
			os << "right: " << inset.right;
			os << "] (";
			os << "width: " << inset.width << ", ";
			os << "height: " << inset.height;
			os << ")";
			return os;
		}

		static const Inset<T> Zero;
	};

	template <typename T> requires std::is_arithmetic_v<T>
	const Inset<T> Inset<T>::Zero = Inset<T>(0, 0, 0, 0);
}
