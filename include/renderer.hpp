#pragma once

#include "utils.hpp"

namespace renderer {

	void initialize();
	void terminate();

	void draw();

	void clear();
	void clear(f32 r, f32 g, f32 b, f32 a = 1.0f);
	void clear(u8 r, u8 g, u8 b, u8 a = 255);

	void set_clear_color(f32 r, f32 g, f32 b, f32 a = 1.0f);
	void set_clear_color(u8 r, u8 g, u8 b, u8 a = 255);

} // namespace renderer
