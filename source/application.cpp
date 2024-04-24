#include "application.hpp"

#include <GLFW/glfw3.h>

#include <cstdio>
#include <cstdlib>
#include <cassert>

static void close_event_handler    (GLFWwindow* window);
static void refresh_event_handler  (GLFWwindow* window);
static void resize_event_handler   (GLFWwindow* window, i32 width, i32 height);
static void key_event_handler      (GLFWwindow* window, i32 key, i32 scancode, i32 action, i32 mods);
static void character_event_handler(GLFWwindow* window, u32 unicode);

namespace application {

    struct ApplicationState {
        const char* name = nullptr;
        u32 width = 0, height = 0;
        bool initialized = false, running = false;

        GLFWwindow* window = nullptr;
    };
    static ApplicationState app;

    void initialize(const char* name, u32 width, u32 height) {
        assert(!app.initialized && "Assertion Failed : Your application have already been initilized !");

        app.initialized = true;
        app.running = true;

        app.name = name;
        app.width = width;
        app.height = height;

        if(!glfwInit()) {
            fprintf(stderr, "Error : glfwInit() failed !\n");
            exit(-1);
        }

        app.window = glfwCreateWindow(width, height, name, nullptr, nullptr);
        if(app.window == nullptr) {
            glfwTerminate();
            fprintf(stderr, "Error : glfwCreateWindow failed !\n");
            exit(-1);
        }

        glfwMakeContextCurrent(app.window);
        glfwSwapInterval(1); // set vsync

        glfwSetWindowCloseCallback(app.window, close_event_handler);
        glfwSetWindowSizeCallback(app.window, resize_event_handler);
        glfwSetWindowRefreshCallback(app.window, refresh_event_handler);

        glfwSetKeyCallback(app.window, key_event_handler);
        glfwSetCharCallback(app.window, character_event_handler);
 
        event::on(event::type::resize, [] (event::Event const& e) -> void {
            app.width = cast(u32, e.resize.width);
            app.height = cast(u32, e.resize.height);
        });

        event::on(event::type::close, [] (event::Event const& e) -> void {
            app.running = false;
        });
    }

    void terminate() {
        assert(app.initialized && "Assertion Failed : Your application have not been initialized !");
        glfwTerminate();
    }

    void swap_buffers() {
        assert(app.initialized && "Assertion Failed : Your application have not been initialized !");
        glfwSwapBuffers(app.window);
    }

    void poll_events() { glfwPollEvents(); }

    namespace state {

        bool const& running = app.running;
        u32 const& width = app.width, &height = app.height;

    } // namespace state

} // namespace application

void refresh_event_handler(GLFWwindow* window) {
    event::Event e {
        .t = event::type::refresh
    };

    event::dispatch(event::type::refresh, e);
}

void resize_event_handler(GLFWwindow* window, i32 width, i32 height) {
    event::Event e {
        .t = event::type::resize,
        .resize = {
            .width = cast(u32, width),
            .height = cast(u32, height),
        },
    };

    event::dispatch(event::type::resize, e);
}

void close_event_handler(GLFWwindow* window) {
    event::Event e {
        .t = event::type::close
    };

    event::dispatch(event::type::close, e);
}

void key_event_handler(GLFWwindow* window, i32 key, i32 scancode, i32 action, i32 mods) {
    event::Event e {
        .t = event::type::close,
        .key = {
            .keycode = key,
            .scancode = scancode,
            // enum is in the same order as GLFW so we can cast as is
            .action = cast(event::key::action, action),
            // enum is in the same order as GLFW so we can cast as is
            .mods = cast(event::key::mods, mods)
        }
    };

    event::dispatch(event::type::key, e);

    switch(e.key.action) {
        case event::key::action::hold:      event::dispatch(event::type::key_hold, e);      break;
        case event::key::action::press:     event::dispatch(event::type::key_pressed, e);   break;
        case event::key::action::release:   event::dispatch(event::type::key_released, e);  break;

        default: fprintf(stderr, "Error : Unknown key action %d\n", action);                break;
    }
}

void character_event_handler(GLFWwindow* window, u32 unicode) {
    event::Event e {
        .t = event::type::character,
        .character = {
            .unicode = unicode,
        },
    };

    event::dispatch(event::type::character, e);
}
