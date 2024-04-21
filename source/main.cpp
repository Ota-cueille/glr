#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "utils.hpp"

bool running = true;

void on_window_close(GLFWwindow* window) { running = false; }

int main(int ac, char* av[]) {
	/* Initialize rendering context */
	if(!glfwInit()) {
		return -1;
	}

	GLFWwindow* window = glfwCreateWindow(100, 100, "window", nullptr, nullptr);
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	glfwSetWindowCloseCallback(window, on_window_close);

	while(running) {
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
