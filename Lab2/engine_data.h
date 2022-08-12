#pragma once

#include <cmath>
#include <corecrt_math_defines.h>
#include <cstdint>
#include <limits>
#include <stdexcept>

// Credit of Weather Vane, for use in math_helper::sqrt() https://stackoverflow.com/questions/29018864/any-way-to-obtain-square-root-of-a-number-without-using-math-h-and-sqrt
//#define MINDIFF 2.2250738585072014e-308   // smallest positive double
#define MINDIFF 2.25e-308                   // use for convergence check
#define DEPSILON std::numeric_limits<double>::epsilon()
#define PI M_PI

#pragma region structs

struct vec2
{
	vec2() : x(0), y(0)
	{
	}

	vec2(const double x, const double y)
		: x(x),
		y(y)
	{
	}

	~vec2() = default;

	double x;
	double y;

	vec2(const vec2& other) = default;

	vec2(vec2&& other) noexcept
		: x(other.x),
		y(other.y)
	{
	}

	vec2& operator=(const vec2& other)
	{
		if (this == &other)
			return *this;
		x = other.x;
		y = other.y;
		return *this;
	}

	vec2& operator=(vec2&& other) noexcept
	{
		if (this == &other)
			return *this;
		x = other.x;
		y = other.y;
		return *this;
	}

	vec2& operator+=(const double& other)
	{
		x = x + other;
		y = y + other;
		return *this;
	}

	vec2& operator+=(const vec2& other)
	{
		x = x + other.x;
		y = y + other.y;
		return *this;
	}

	vec2 operator+(const vec2& other) const
	{
		return { x + other.x, y + other.y };
	}

	vec2& operator-=(const vec2& other)
	{
		x = x - other.x;
		y = y - other.y;
		return *this;
	}

	vec2 operator-(const vec2& other) const
	{
		return { x - other.x, y - other.y };
	}

	double& operator[](const unsigned int index)
	{
		switch (index)
		{
		case 0:
			return this->x;
		case 1:
			return this->y;
		default: 
			return this->x;
		}
	}

	double squared_magnitude() const
	{
		return (x * x) + (y * y);
	}

	friend bool operator==(const vec2& lhs, const vec2& rhs)
	{
		return lhs.x - rhs.x <= MINDIFF
			&& lhs.y - rhs.y <= MINDIFF;
	}

	friend bool operator!=(const vec2& lhs, const vec2& rhs)
	{
		return !(lhs == rhs);
	}

	static vec2 zero() { return { 0, 0 }; }
};

struct vec3
{
	vec3() : x(0), y(0), z(0)
	{
	}

	explicit vec3(const vec2 v) : x(v.x), y(v.y), z(0)
	{
	}

	vec3(const double x, const double y, const double z)
		: x(x),
		y(y),
		z(z)
	{
	}

	~vec3() = default;

	double x;
	double y;
	double z;

	vec3& operator+=(const vec3& other)
	{
		x = x + other.x;
		y = y + other.y;
		z = z + other.z;
		return *this;
	}

	vec3 operator+(const vec3& other) const
	{
		return { x + other.x, y + other.y, z + other.z };
	}

	vec3& operator-=(const vec3& other)
	{
		x = x - other.x;
		y = y - other.y;
		z = z - other.z;
		return *this;
	}

	vec3 operator-(const vec3& other) const
	{
		return { x - other.x, y - other.y, z - other.z };
	}

	vec3(const vec3& other)
		: x(other.x),
		y(other.y),
		z(other.z)
	{
	}

	vec3(vec3&& other) noexcept
		: x(other.x),
		y(other.y),
		z(other.z)
	{
	}

	vec3& operator=(const vec3& other)
	{
		if (this == &other)
			return *this;
		x = other.x;
		y = other.y;
		z = other.z;
		return *this;
	}

	vec3& operator=(vec3&& other) noexcept
	{
		if (this == &other)
			return *this;
		x = other.x;
		y = other.y;
		z = other.z;
		return *this;
	}

	friend bool operator==(const vec3& lhs, const vec3& rhs)
	{
		return lhs.x == rhs.x
			&& lhs.y == rhs.y
			&& lhs.z == rhs.z;
	}

	friend bool operator!=(const vec3& lhs, const vec3& rhs)
	{
		return !(lhs == rhs);
	}

	static vec3 zero() { return { 0, 0, 0 }; }
};

struct color
{
	static constexpr unsigned int cornflower_blue = 0x006495ed;
	static constexpr unsigned int black = 0xFF000000;
	static constexpr unsigned int red = 0xFFFF0000;
	static constexpr unsigned int green = 0xFF00FF00;
	static constexpr unsigned int blue = 0xFF0000FF;
	static constexpr unsigned int yellow = 0xFFFFFF00;
	static constexpr unsigned int purple = 0xFFFF00FF;
	static constexpr unsigned int cyan = 0XFF00FFFF;

	color() : a(0), r(0), g(0), b(0)
	{
	}

	explicit color(const unsigned char v) : a(v), r(v), g(v), b(v)
	{
	}

	explicit color(const char r, const char g, const char b)
		: a(0xFF),
		r(r),
		g(g),
		b(b)
	{
	}

	explicit color(const char a, const char r, const char g, const char b)
		: a(a),
		r(r),
		g(g),
		b(b)
	{
	}

	unsigned char a;
	unsigned char r;
	unsigned char g;
	unsigned char b;

	uint32_t convert() const
	{
		return a << 24 | r << 16 | g << 8 | b;
	}
};

struct vertex
{
	vertex() : x(0), y(0), z(0), w(1), color(0)
	{
	}

	explicit vertex(const vec3 v, const color color) : x(v.x), y(v.y), z(v.z), w(1), color(color)
	{
	}

	explicit vertex(const double x, const double y, const double z, const double w, const color color)
		: x(x),
		y(y),
		z(z),
		w(w),
		color(color)
	{
	}

	double x;
	double y;
	double z;
	double w;

	color color;
};

struct vec4
{
	vec4() : x(0), y(0), z(0), w(0)
	{
	}

	explicit vec4(const vertex v) : x(v.x), y(v.y), z(v.z), w(1)
	{
	}

	vec4(const double x, const double y, const double z, const double w)
		: x(x),
		y(y),
		z(z),
		w(w)
	{
	}

	~vec4() = default;

	double x;
	double y;
	double z;
	double w;

	double dot_product(const vec4& other) const
	{
		return x * other.x + y * other.y + z * other.z + w + other.w;
	}

	vec4 operator*(const double& other) const
	{
		return { x * other, y * other, z * other, w * other };
	}

	double& operator[](const uint32_t index)
	{
		switch (index)
		{
		case 0:
			return x;
		case 1:
			return y;
		case 2:
			return z;
		case 3:
			return w;

		default:
			return x;
		}
	}

	vec4(const vec4& other) = default;

	vec4(vec4&& other) noexcept
		: x(other.x),
		y(other.y),
		z(other.z),
		w(other.w)
	{
	}

	vec4& operator=(const vec4& other)
	{
		if (this == &other)
			return *this;
		x = other.x;
		y = other.y;
		z = other.z;
		w = other.w;
		return *this;
	}

	vec4& operator=(vec4&& other) noexcept
	{
		if (this == &other)
			return *this;
		x = other.x;
		y = other.y;
		z = other.z;
		w = other.w;
		return *this;
	}

	friend bool operator==(const vec4& lhs, const vec4& rhs)
	{
		return lhs.x - rhs.x <= DEPSILON
			&& lhs.y - rhs.y <= DEPSILON
			&& lhs.z - rhs.z <= DEPSILON
			&& lhs.w - rhs.w <= DEPSILON;
	}

	friend bool operator!=(const vec4& lhs, const vec4& rhs)
	{
		return !(lhs == rhs);
	}

	friend bool operator<(const vec4& lhs, const vec4& rhs)
	{
		if (lhs.x < rhs.x)
			return true;
		if (rhs.x < lhs.x)
			return false;
		if (lhs.y < rhs.y)
			return true;
		if (rhs.y < lhs.y)
			return false;
		if (lhs.z < rhs.z)
			return true;
		if (rhs.z < lhs.z)
			return false;
		return lhs.w < rhs.w;
	}

	friend bool operator<=(const vec4& lhs, const vec4& rhs)
	{
		return !(rhs < lhs);
	}

	friend bool operator>(const vec4& lhs, const vec4& rhs)
	{
		return rhs < lhs;
	}

	friend bool operator>=(const vec4& lhs, const vec4& rhs)
	{
		return !(lhs < rhs);
	}

	static vec4 zero() { return { 0, 0, 0, 0 }; }
};

struct mat_2
{
	mat_2(): m{}
	{
	}

	mat_2(const vec2 a, const vec2 b): m{}
	{
		m[0] = a.x;
		m[1] = a.y;
		m[2] = b.x;
		m[3] = b.y;
	}

	double m[4];

	mat_2 operator*(const double& other) const
	{
		mat_2 mm{};

		mm.m[0] = m[0] * other;
		mm.m[1] = m[1] * other;
		mm.m[2] = m[2] * other;
		mm.m[3] = m[3] * other;

		return mm;
	}

	mat_2 operator*(const mat_2& other) const
	{
		mat_2 mm{};

		// Dot product to get to the final multiplied matrix.
		mm.m[0] = m[0]*other.m[0] + m[1]*other.m[2];
		mm.m[1] = m[0]*other.m[1] + m[1]*other.m[3];
		mm.m[2] = m[2]*other.m[0] + m[3]*other.m[2];
		mm.m[3] = m[2]*other.m[1] + m[3]*other.m[3];

		return mm;
	}

	mat_2 inverse()
	{
		return  mat_2({m[3], -m[1]}, {-m[2], m[0]}) * (1.0 / determinant());
	}

	double determinant() const
	{
		return (m[0]*m[3] - m[1]*m[2]);
	}

	friend bool operator==(const mat_2& lhs, const mat_2& rhs)
	{
		return lhs.m[0] - rhs.m[0] <= DEPSILON
			&& lhs.m[1] - rhs.m[1] <= DEPSILON
			&& lhs.m[2] - rhs.m[2] <= DEPSILON
			&& lhs.m[3] - rhs.m[3] <= DEPSILON;
	}

	friend bool operator!=(const mat_2& lhs, const mat_2& rhs)
	{
		return !(lhs == rhs);
	}

	double operator[](const unsigned int index) const
	{
		if(index >= 4) throw std::out_of_range("Index out of bounds");

		return m[index];
	}

	static mat_2 identity() { return {{1, 0}, {0, 1}}; }
};

struct mat_4
{
	mat_4() : m{}
	{
	}

	explicit mat_4(double a[16])
	{
		m[0][0] = a[0];
		m[0][1] = a[1];
		m[0][2] = a[2];
		m[0][3] = a[3];
		m[1][0] = a[4];
		m[1][1] = a[5];
		m[1][2] = a[6];
		m[1][3] = a[7];
		m[2][0] = a[8];
		m[2][1] = a[9];
		m[2][2] = a[10];
		m[2][3] = a[11];
		m[3][0] = a[12];
		m[3][1] = a[13];
		m[3][2] = a[14];
		m[3][3] = a[15];
	}

	mat_4(const vec4& a, const vec4& b, const vec4& c, const vec4& d) : m{}
	{
		m[0] = a;
		m[1] = b;
		m[2] = c;
		m[3] = d;
	}

	vec4 m[4];

	mat_4(const mat_4& other) = default;

	void flatten(double a[16])
	{
		a[0]  = m[0][0];
		a[1]  = m[0][1];
		a[2]  = m[0][2];
		a[3]  = m[0][3];
		a[4]  = m[1][0];
		a[5]  = m[1][1];
		a[6]  = m[1][2];
		a[7]  = m[1][3];
		a[8]  = m[2][0];
		a[9]  = m[2][1];
		a[10] = m[2][2];
		a[11] = m[2][3];
		a[12] = m[3][0];
		a[13] = m[3][1];
		a[14] = m[3][2];
		a[15] = m[3][3];
	}

	mat_4& scale(const double size)
	{
		this = *this * (identity()*size);

		return *this;
	}

	mat_4 operator*(const double& other) const
	{
		return { m[0] * other, m[1] * other, m[2] * other, m[3] * other };
	}

	mat_4 operator*(mat_4& other)
	{
		mat_4 ret{};

		for (int i = 0; i < 3; ++i)
			for (int j = 0; j < 3; ++j)
				for (int k = 0; k < 3; ++k) {
					ret.m[i][j] += m[i][k] * other.m[k][j];
				}

		return ret;
	}

	mat_4& operator*=(mat_4& other)
	{
		for (auto& i : m)
		{
			for (int j = 0; j < 4; ++j)
			{
				i[j] = 0;

				for (int k = 0; k < 4; ++k)
				{
					i[j] += i[k] * other.m[k][j];
				}
			}
		}

		return *this;
	}

	mat_4 operator*=(mat_4& other) const
	{
		mat_4 ret{};

		for (auto& i : ret.m)
		{
			for (int j = 0; j < 4; ++j)
			{
				i[j] = 0;

				for (int k = 0; k < 4; ++k)
				{
					i[j] += i[k] * other.m[k][j];
				}
			}
		}

		return ret;
	}

	friend bool operator==(const mat_4& lhs, const mat_4& rhs)
	{
		return lhs.m[0] == rhs.m[0]
			&& lhs.m[1] == rhs.m[1]
			&& lhs.m[2] == rhs.m[2]
			&& lhs.m[3] == rhs.m[3];
	}

	friend bool operator!=(const mat_4& lhs, const mat_4& rhs)
	{
		return !(lhs == rhs);
	}

	friend bool operator<(const mat_4& lhs, const mat_4& rhs)
	{
		for (auto& m1 : lhs.m)
		{
			for (auto& m2 : rhs.m)
			{
				if (m1 < m2) return false;
			}
		}

		return true;
	}

	friend bool operator<=(const mat_4& lhs, const mat_4& rhs)
	{
		return !(rhs < lhs);
	}

	friend bool operator>(const mat_4& lhs, const mat_4& rhs)
	{
		return rhs < lhs;
	}

	friend bool operator>=(const mat_4& lhs, const mat_4& rhs)
	{
		return !(lhs < rhs);
	}

	static mat_4 zero()
	{
		return {
			{0, 0, 0, 0},
			{0, 0, 0, 0},
			{0, 0, 0, 0},
			{0, 0, 0, 1}
		};
	}

	static  mat_4 identity()
	{
		return {
			{1,0,0,0},
			{0,1,0,0},
			{0,0,1,0},
			{0,0,0,1}
		};
	}

	static mat_4 roll(const double angle)
	{
		return {
			{1, 0, 0, 0},
			{0, std::cos(angle), - std::sin(angle), 0},
			{0, std::sin(angle), std::cos(angle), 0},
			{0, 0, 0, 1}
		};
	}

	static mat_4 pitch(const double angle)
	{
		return {
			{std::cos(angle), 0, std::sin(angle), 0},
			{0, 1, 0, 0},
			{-std::sin(angle), 0, std::cos(angle), 0},
			{0, 0, 0, 1}
		};
	}

	static mat_4 yaw(const double angle)
	{
		return {
			{std::cos(angle), -std::sin(angle), 0, 0},
			{std::sin(angle), std::cos(angle), 0, 0},
			{0, 0, 0, 0},
			{0, 0, 0, 1}
		};
	}

	/*mat_4 inverse()
	{
		double im[16];

		im[0] = 
	}*/
};

#pragma endregion
