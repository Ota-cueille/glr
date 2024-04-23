#include "application.hpp"

#include <GLFW/glfw3.h>

#include <cstdio>
#include <cstdlib>
#include <cassert>

namespace application {

    struct ApplicationData {
        const char* name;
        u32 width, height;

        GLFWwindow* window;
    };

    static bool initialized = false;
    static ApplicationData data;

    void initialize(const char* name, u32 width, u32 height) {
        assert(!initialized && "Assertion Failed : Your application have already been initilized !");
        initialized = true;

        data.name = name;
        data.width = width;
        data.height = height;

        if(!glfwInit()) {
            fprintf(stderr, "");
            exit(-1);
        }

        data.window = glfwCreateWindow(width, height, name, nullptr, nullptr);
        if(data.window == nullptr) {
            glfwTerminate();
            fprintf(stderr, "");
            exit(-1);
        }
        events::initialize(data.window);

        glfwMakeContextCurrent(data.window);
        glfwSwapInterval(1); // set vsync

    }

    void terminate() {}

    void swapBuffers(){
        glfwSwapBuffers(data.window);
    }

} // namespace application