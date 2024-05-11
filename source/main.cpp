#include <cstdio>

#include <glm/glm.hpp>

#include "utils.hpp"
#include "events.hpp"
#include "application.hpp"
#include "renderer.hpp"

int main(int ac, char* av[]) {
	application::initialize("window");
	renderer::initialize();
	renderer::set_clear_color(0.9f, 0.85f, 0.8f);

	event::on(event::type::refresh, [] (const event::Event& e) -> void {
		renderer::clear();
		renderer::draw();
		application::swap_buffers();
	});

	event::on(event::type::character, [] (const event::Event& e) -> void {
		// assumes ascii only
		printf("> key pressed %c\n", cast(u8, e.character.unicode));
	});

	while(application::state::running) {
		renderer::clear();
		renderer::draw();

		application::swap_buffers();
		application::poll_events();
	}

	renderer::terminate();
	application::terminate();
	return 0;
}
