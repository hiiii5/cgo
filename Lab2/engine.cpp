#include "engine.h"

#include "engine_data.h"
#include "RasterSurface.h"
#include "renderer.h"

engine::engine(uint32_t width, uint32_t height): render_manager_(new renderer(width, height, color::cornflower_blue))
{
}

void engine::start()
{
	RS_Initialize("Dustin Roden", render_manager_->width, render_manager_->height);

	mat_4 a = mat_4::identity();
	mat_4 b = mat_4::roll(2 * PI);
	mat_4 c = a * b;
	// Used to signal worker threads to exit safely.
	signal_future_ = exit_signal_.get_future();

	// detach worker threads.
	std::thread{ [this]()
	{
		do
		{
			render();
			update();

		} while (signal_future_.wait_for(std::chrono::milliseconds(1)) == std::future_status::timeout);

	} }.detach();

	// join the update thread.
	std::thread{ [this]()
	{
		// Update until the window is shut down.
		while (RS_Update(render_manager_->get_frame(), render_manager_->get_screen_size())) {}

	} }.join();

	// Inform the engine to shut down.
	exit_signal_.set_value();

	RS_Shutdown();
}

void engine::update() const
{
	render_manager_->update_frame();
}
vec2 end { 0,0};
void engine::render() const
{
	render_manager_->clear_buffer();

	render_manager_->draw_line({ 100, 100 }, end += 1, color::green);
}
