#include <cstdio>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "utils.hpp"
#include "events.hpp"
#include "application.hpp"

struct {
	u32 vao = 0, vbo = 0;
	u32 triangle_program = 0;
} renderer;

static void gl_error(u32 source, u32 type, u32 id, u32 severity, i32 length, const char *message, const void*);
static u32 compile_shader(const char* path, u32 type);

int main(int ac, char* av[]) {
	/* INIT OPENGL */
	application::initialize("window");

	event::on(event::type::refresh, [] (const event::Event& e) -> void {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glBindVertexArray(renderer.vao);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		application::swap_buffers();
	});

	event::on(event::type::key, [] (const event::Event& e) -> void {
		printf("%d",e.key.keycode);
	});

	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback((GLDEBUGPROC)gl_error, nullptr);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_DEPTH_TEST);

	glClearColor(0.9f, 0.85f, 0.8f, 1.0f);

	/* TRIANGLE */

	/* 1. DATA */
	f32 vertices[] = {
		-0.5f, -0.5f, // down left
		 0.5f, -0.5f, // down right
		 0.0f,  0.5f, // up   middle
	};

	/* 2. OPENGL : VAO, VBO */
	glCreateVertexArrays(1, &renderer.vao);
	glBindVertexArray(renderer.vao);

	glCreateBuffers(1, &renderer.vbo);
	glBindBuffer(GL_ARRAY_BUFFER, renderer.vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), cast(void*, vertices), GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), cast(const void*, 0));

	glBindVertexArray(0);

	/* 3. TRIANGLE SHADER */
	renderer.triangle_program = glCreateProgram();
	
	u32 triangle_vertex_shader = compile_shader("./assets/shader/triangle.vert", GL_VERTEX_SHADER);
	glAttachShader(renderer.triangle_program, triangle_vertex_shader);

	u32 triangle_fragment_shader = compile_shader("./assets/shader/triangle.frag", GL_FRAGMENT_SHADER);
	glAttachShader(renderer.triangle_program, triangle_fragment_shader);

	glLinkProgram(renderer.triangle_program);
	glDeleteShader(triangle_vertex_shader);
	glDeleteShader(triangle_fragment_shader);

	while(application::state::running) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUseProgram(renderer.triangle_program);
		glBindVertexArray(renderer.vao);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		application::swap_buffers();
		application::poll_events();
	}

	application::terminate();
	return 0;
}

u32 compile_shader(const char* path, u32 type) {
	char _[4096] = { '\0' }; char* buf = _;
	FILE* shader_source_file = fopen(path, "rb");
	fread(buf, sizeof(char), 4096, shader_source_file);
	fclose(shader_source_file);

	u32 id = glCreateShader(type);
	glShaderSource(id, 1, &buf, nullptr);
	glCompileShader(id);
	return id;
}

void gl_error(u32 source, u32 type, u32 id, u32 severity, i32 length, const char *message, const void*) {
    const char* source_name;
    switch (source)
    {
        case GL_DEBUG_SOURCE_API:             source_name = "API"; break;
        case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   source_name = "window system"; break;
        case GL_DEBUG_SOURCE_SHADER_COMPILER: source_name = "shader compiler"; break;
        case GL_DEBUG_SOURCE_THIRD_PARTY:     source_name = "third party"; break;
        case GL_DEBUG_SOURCE_APPLICATION:     source_name = "application"; break;
        case GL_DEBUG_SOURCE_OTHER:           source_name = "other"; break;
    }
    const char* type_name;
    switch (type)
    {
        case GL_DEBUG_TYPE_ERROR:               type_name = "error"; break;
        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: type_name = "deprecated behaviour"; break;
        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  type_name = "undefined behaviour"; break;
        case GL_DEBUG_TYPE_PORTABILITY:         type_name = "portability"; break;
        case GL_DEBUG_TYPE_PERFORMANCE:         type_name = "performance"; break;
        case GL_DEBUG_TYPE_MARKER:              type_name = "marker"; break;
        case GL_DEBUG_TYPE_PUSH_GROUP:          type_name = "push group"; break;
        case GL_DEBUG_TYPE_POP_GROUP:           type_name = "pop group"; break;
        case GL_DEBUG_TYPE_OTHER:               type_name = "other"; break;
    }
    const char* severity_name;
    switch (severity)
    {
        case GL_DEBUG_SEVERITY_HIGH:         severity_name = "high"; break;
        case GL_DEBUG_SEVERITY_MEDIUM:       severity_name = "medium"; break;
        case GL_DEBUG_SEVERITY_LOW:          severity_name = "low"; break;
        case GL_DEBUG_SEVERITY_NOTIFICATION: severity_name = "notification"; break;
    }
    fprintf(stderr, "GL ERROR[source: %s, type: %s, severity: %s]: %s\n", source_name, type_name, severity_name, message);
}
