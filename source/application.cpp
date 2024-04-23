#include "application.hpp"

#include <GLFW/glfw3.h>

#include <cstdio>
#include <cstdlib>
#include <cassert>

static void close_event_handler  (GLFWwindow* window);
static void resize_event_handler (GLFWwindow* window, i32 width, i32 height);
static void refresh_event_handler(GLFWwindow* window);
static void key_event_handler(GLFWwindow* window, int key, int scancode, int action, int mods);

namespace application {

    struct ApplicationState {
        const char* name = nullptr;
        u32 width = 0, height = 0;

        GLFWwindow* window = nullptr;

        bool initialized = false, running = false;
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

        glfwSetWindowCloseCallback    (app.window, close_event_handler);
        glfwSetWindowRefreshCallback  (app.window, refresh_event_handler);
        glfwSetFramebufferSizeCallback(app.window, resize_event_handler);

        glfwSetKeyCallback(app.window, key_event_handler);

 
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
    event::flush(event::type::refresh, e);
}

void resize_event_handler(GLFWwindow* window, i32 width, i32 height) {
    event::Event e {
        .t = event::type::resize,
        .resize = {
            .width = cast(u32, width),
            .height = cast(u32, height),
        },
    };
    event::flush(event::type::resize, e);
}

void close_event_handler(GLFWwindow* window) {
    event::Event e {
        .t = event::type::close
    };
    event::flush(event::type::close, e);
}

void key_event_handler(GLFWwindow* window, int key, int scancode, int action, int mods) {
    event::Event e {
        .t = event::type::close,
        .key = {
            .keycode = key,
            .scancode = scancode,
            .action = cast(event::key::action,action),
            .mods = cast(event::key::mods,mods)
        }
    };
    event::flush(event::type::key, e);
}
