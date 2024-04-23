#include "application.hpp"

#include <GLFW/glfw3.h>

#include <cstdio>
#include <cstdlib>
#include <cassert>

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

        event::initialize(app.window);
  
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

    namespace state {

        bool const& running = app.running;
        u32 const& width = app.width, &height = app.height;

    } // namespace state

} // namespace application