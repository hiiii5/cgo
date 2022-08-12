#include "math_helper.h"
#include "engine_data.h"

vec2 math_helper::get_parallel_vec(const vec2& a, const vec2& b)
{
	return { b.x - a.x, b.y - a.y };
}

vec2 math_helper::get_gradient_vec(const vec2& a, const vec2& b)
{
	return { a.y - b.y, b.x - a.x };
}

double math_helper::lerp_d(const double& a, const double& b, const float ratio)
{
	return (b - a) * static_cast<double>(ratio) + a;
}

float math_helper::lerp_f(const double& a, const double& b, const float ratio)
{
	return static_cast<float>((b - a) * static_cast<double>(ratio) + a);
}

uint32_t math_helper::floor(const double a)
{
	return static_cast<uint32_t>(a);
}

double math_helper::solve_line(const double& cur_x, const vec2& p1, const vec2& p2)
{
	const double a = p1.y - p2.y;
	const double b = p2.x - p1.x;
	const double c = (p1.x - p2.x) * p1.y + (p2.y - p1.y) * p1.x;

	return (a * cur_x + c) / b;
}

double math_helper::solve_line_2(const double& x, const vec2& p1, const vec2& p2)
{
	vec2 max;
	vec2 min;
	get_min_and_max_x(min, max, p1, p2);

	return (p2.y - p1.y) / (p2.x - p1.x) * (x - p1.x) + p1.y;
}

uint32_t math_helper::get_2d_index(const double& x, const double& y, const uint32_t buffer_width)
{
	return static_cast<uint32_t>(y * buffer_width + x);
}

void math_helper::get_min_and_max_x(vec2& min, vec2& max, const vec2& start, const vec2& end)
{
	if (start.x > end.x)
	{
		min = end;
		max = start;
	}
	else
	{
		min = start;
		max = end;
	}
}

void math_helper::get_min_and_max_y(vec2& min, vec2& max, const vec2& start, const vec2& end)
{
	if (start.y > end.y)
	{
		min = end;
		max = start;
	}
	else
	{
		min = start;
		max = end;
	}
}

double math_helper::sqrt(const double square)
{
	double root = square / 3, diff = 1;
	if (square <= 0) return 0;
	do {
		const double last = root;
		root = (root + square / root) / 2;
		diff = root - last;
	} while (diff > MINDIFF || diff < -MINDIFF);
	return root;
}
