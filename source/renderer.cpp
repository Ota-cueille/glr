#include "renderer.hpp"


#include <cstdio>

#include <glad/glad.h>

/* Ce serait sympa d'abstraire nous même l'initialisation d'opengl */
// typedef void (*GLFWglproc)(void);
// GLFWglproc glfwGetProcAddress(const char* procname);
#include <GLFW/glfw3.h>
/* --------------------------------------------------------------- */

static void gl_error(u32 source, u32 type, u32 id, u32 severity, i32 length, const char *message, const void*);

namespace renderer {

	void initialize() {
		gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

		glEnable(GL_DEBUG_OUTPUT);
		glDebugMessageCallback((GLDEBUGPROC)gl_error, nullptr);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glEnable(GL_DEPTH_TEST);
	}

	void terminate() {}

	void clear() { glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); }

	void clear(f32 r, f32 g, f32 b, f32 a) {
		glClearColor(r, g, b, a);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void clear(u8 r, u8 g, u8 b, u8 a) {
		glClearColor(r/255.0f, g/255.0f, b/255.0f, a/255.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void set_clear_color(f32 r, f32 g, f32 b, f32 a) { glClearColor(r, g, b, a); }
	void set_clear_color(u8 r, u8 g, u8 b, u8 a) { glClearColor(r/255.0f, g/255.0f, b/255.0f, a/255.0f); }

} // namespace renderer

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
