#include "events.hpp"

#include <list>
#include <array>

#include <GLFW/glfw3.h>

static void close_event_handler  (GLFWwindow* window);
static void resize_event_handler (GLFWwindow* window, i32 width, i32 height);
static void refresh_event_handler(GLFWwindow* window);

namespace event {

    static std::array<std::list<EventCallback>, cast(u64, type::size)> callbacks;

    void on(type t, std::function<void(Event const&)> const& callback) {
        u64 i = cast(u64, t);
        callbacks[i].push_back(callback);
    }

    void poll() { glfwPollEvents(); }

    void initialize(void* window) {
        GLFWwindow* w = cast(GLFWwindow*, window);
        glfwSetWindowCloseCallback    (w, close_event_handler);
        glfwSetFramebufferSizeCallback(w, resize_event_handler);
        glfwSetWindowRefreshCallback  (w, refresh_event_handler);
    }

} // namespace events

using namespace event;

template <type EventType>
void exec(Event const& event) {
    for (auto const& callback : callbacks[cast(u64, EventType)]) callback(event);
}

void refresh_event_handler(GLFWwindow* window) {
    Event e {
        .t = type::refresh
    };
    exec<type::refresh>(e);
}

void resize_event_handler(GLFWwindow* window, i32 width, i32 height) {
    Event e {
        .t = type::resize,
        .resize = {
            .width = cast(u32, width),
            .height = cast(u32, height),
        },
    };
    exec<type::resize>(e);
}

void close_event_handler(GLFWwindow* window) {
    Event e {
        .t = type::close
    };
    exec<type::close>(e);
}
