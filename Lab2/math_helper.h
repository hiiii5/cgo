#pragma once
#include <cstdint>

struct vec2;

class math_helper
{
public:
	static vec2 get_parallel_vec(const vec2& a, const vec2& b);

	static vec2 get_gradient_vec(const vec2& a, const vec2& b);

	static double lerp_d(const double& a, const double& b, const float ratio);

	static float lerp_f(const double& a, const double& b, const float ratio);

	static uint32_t floor(const double a);

	static double solve_line(const double& cur_x, const vec2& p1, const vec2& p2);

	static double solve_line_2(const double& x, const vec2& p1, const vec2& p2);

	static uint32_t get_2d_index(const double& x, const double& y, const uint32_t buffer_width);

	static void get_min_and_max_x(vec2& min, vec2& max, const vec2& start, const vec2& end);

	static void get_min_and_max_y(vec2& min, vec2& max, const vec2& start, const vec2& end);

	// Credit of Weather Vane https://stackoverflow.com/questions/29018864/any-way-to-obtain-square-root-of-a-number-without-using-math-h-and-sqrt
	static double sqrt(const double square);
};

