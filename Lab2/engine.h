#pragma once
#include <future>
class renderer;
struct vec2;

class engine
{
public:
	explicit engine(uint32_t width = 500, uint32_t height = 500);

	void start();

	void update() const;

	void render() const;

protected:
	const renderer* render_manager_;
	std::promise<void> exit_signal_;
	std::future<void> signal_future_;
};
