#pragma once
#include <cstdint>
#include "math_helper.h"

struct color;
struct vec2;

class renderer
{
public:
	renderer(const uint32_t width, const uint32_t height, const uint32_t clear_color);

	const uint32_t width;
	const uint32_t height;

	void clear_buffer() const;

	void draw_pixel(const uint32_t& pixel, const uint32_t x, const uint32_t y) const;

	void draw_line(const vec2 start, const vec2 end, const uint32_t color = 0xFFFFFFFF) const;

	void update_frame() const;

	uint32_t* get_frame() const;

	uint32_t get_screen_size() const { return width * height; }

private:
	uint32_t* pixels_;
	uint32_t* old_pixels_;
	const uint32_t clear_color_;
};
