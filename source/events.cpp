#include <GLFW/glfw3.h>

#include <list>
#include <array>
#include "events.hpp"

namespace events {
    static std::array<std::list<EventCallback>,cast(u64,types::size)> callbackHandler;

    void on(types eventType, const std::function<void(const Event&)>& callback){
        u64 i = cast(u64,eventType);
        callbackHandler[i].push_back(callback);
    }

    void poll(){
        glfwPollEvents();
    }

    template <types eventType>
    void exec(Event const & event){
        for (auto const & callback : callbackHandler[cast(u64,eventType)]){
            callback(event);
        }
    }

    void refresh(GLFWwindow* window){
        Event event = {.type = types::refresh};
        exec<types::refresh>(event);
    }

    void resize(GLFWwindow* window, i32 width, i32 height){
        Event event = {.type = types::refresh,.height = height, .width = width};
        exec<types::resize>(event);
    }

    void close(GLFWwindow* window){
        Event event = {.type = types::refresh};
        exec<types::close>(event);
    }

    void initialize(void * window){
        GLFWwindow* w = cast(GLFWwindow*,window);

        glfwSetWindowCloseCallback(w, close);
        glfwSetFramebufferSizeCallback(w, resize);
        glfwSetWindowRefreshCallback(w, refresh);
    }
}