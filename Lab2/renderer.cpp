#include "renderer.h"
#include "engine_data.h"

renderer::renderer(const uint32_t width, const uint32_t height, const uint32_t clear_color): width(width),
	height(height),
	clear_color_(clear_color)
{
	const auto size = get_screen_size() * sizeof pixels_;
	pixels_ = new uint32_t[size];

	for (uint32_t i = 0; i < size; i++)
	{
		pixels_[i] = clear_color;
	}

	// Setup initial old pixel to match clear color for screen.
	old_pixels_ = new uint32_t[size];
	memcpy(old_pixels_, pixels_, size);
}

void renderer::clear_buffer() const
{
	for (uint32_t i = 0; i < get_screen_size() * sizeof pixels_; i++)
	{
		pixels_[i] = clear_color_;
	}
}

void renderer::draw_pixel(const uint32_t& pixel, const uint32_t x, const uint32_t y) const
{
	if (x >= width || y >= height) return;

	// Blend the old pixel with the new pixel.
	const unsigned short alpha = ((pixel & 0xFF000000) >> 24) / 255;

	auto& target = pixels_[y * width + x];

	if (alpha <= 0)
	{
		target ^= clear_color_;
		return;
	}

	const auto new_red = math_helper::lerp_d((target & 0x00FF0000) >> 16, (pixel & 0x00FF0000) >> 16, alpha);
	const auto new_green = math_helper::lerp_d((target & 0x0000FF00) >> 8, (pixel & 0x0000FF00) >> 8, alpha);
	const auto new_blue = math_helper::lerp_d((target & 0x000000FF), pixel & 0x000000FF, alpha);

	const uint32_t red = math_helper::floor(new_red) << 16;
	const uint32_t green = math_helper::floor(new_green) << 8;
	const uint32_t blue = math_helper::floor(new_blue);

	target = alpha << 24 | red | green | blue;

}

void renderer::draw_line(const vec2 start, const vec2 end, const uint32_t color) const
{
	// Get the points in x order.
	vec2 min;
	vec2 max;
	math_helper::get_min_and_max_x(min, max, start, end);

	// Solve for zero distance lines.
	if ((max - min).squared_magnitude() <= DEPSILON)
	{
		draw_pixel(color, math_helper::floor(start.x), math_helper::floor(start.y));
	}

	// Solve for vertical lines
	if (max.x - min.x <= DEPSILON)
	{
		math_helper::get_min_and_max_y(min, max, start, end);

		for (uint32_t y = math_helper::floor(min.y); y < math_helper::floor(max.y); y++)
		{
			draw_pixel(color, math_helper::floor(min.x), y);
		}
		return;
	}

	// Solve for horizontal lines
	if (max.y - min.y <= DEPSILON)
	{
		for (uint32_t x = math_helper::floor(min.x); x < math_helper::floor(max.x); ++x)
		{
			draw_pixel(color, x, math_helper::floor(min.y));
		}
		return;
	}

	// Solve for sloped lines.
	for (uint32_t x = math_helper::floor(min.x); x < math_helper::floor(max.x); ++x)
	{
		// Generate the y value from x.
		const auto y = math_helper::floor(math_helper::solve_line_2(x, start, end));
		draw_pixel(color, x, y);
	}
}

void renderer::update_frame() const
{
	memcpy(old_pixels_, pixels_, get_screen_size() * sizeof pixels_);
}

uint32_t* renderer::get_frame() const
{
	return old_pixels_;
}
