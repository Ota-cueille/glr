: rem Build Script for Windows ARM64

set sdkversion=10.0.22621.0
set architecture=arm64
set sdkpath=C:/Program Files (x86)/Windows Kits/10/Lib/%sdkversion%/um/%architecture%

: build dependencies

: build glad
clang -g -c vendor/glad/src/glad.c -o build/debug/obj/glad.o -I vendor/glad/include/

: build glfw3
clang -g -c vendor/glfw3/src/context.c -o build/debug/obj/glfw-context.o -I vendor/glfw3/include -D_GLFW_WIN32 -D_CRT_SECURE_NO_WARNINGS
clang -g -c vendor/glfw3/src/init.c -o build/debug/obj/glfw-init.o -I vendor/glfw3/include -D_GLFW_WIN32 -D_CRT_SECURE_NO_WARNINGS
clang -g -c vendor/glfw3/src/input.c -o build/debug/obj/glfw-input.o -I vendor/glfw3/include -D_GLFW_WIN32 -D_CRT_SECURE_NO_WARNINGS
clang -g -c vendor/glfw3/src/monitor.c -o build/debug/obj/glfw-monitor.o -I vendor/glfw3/include -D_GLFW_WIN32 -D_CRT_SECURE_NO_WARNINGS
clang -g -c vendor/glfw3/src/platform.c -o build/debug/obj/glfw-platform.o -I vendor/glfw3/include -D_GLFW_WIN32 -D_CRT_SECURE_NO_WARNINGS
clang -g -c vendor/glfw3/src/vulkan.c -o build/debug/obj/glfw-vulkan.o -I vendor/glfw3/include -D_GLFW_WIN32 -D_CRT_SECURE_NO_WARNINGS
clang -g -c vendor/glfw3/src/window.c -o build/debug/obj/glfw-window.o -I vendor/glfw3/include -D_GLFW_WIN32 -D_CRT_SECURE_NO_WARNINGS

clang -g -c vendor/glfw3/src/egl_context.c -o build/debug/obj/glfw-egl_context.o -I vendor/glfw3/include -D_GLFW_WIN32 -D_CRT_SECURE_NO_WARNINGS
clang -g -c vendor/glfw3/src/osmesa_context.c -o build/debug/obj/glfw-osmesa_context.o -I vendor/glfw3/include -D_GLFW_WIN32 -D_CRT_SECURE_NO_WARNINGS

clang -g -c vendor/glfw3/src/null_init.c -o build/debug/obj/glfw-null_init.o -I vendor/glfw3/include -D_GLFW_WIN32 -D_CRT_SECURE_NO_WARNINGS
clang -g -c vendor/glfw3/src/null_monitor.c -o build/debug/obj/glfw-null_monitor.o -I vendor/glfw3/include -D_GLFW_WIN32 -D_CRT_SECURE_NO_WARNINGS
clang -g -c vendor/glfw3/src/null_joystick.c -o build/debug/obj/glfw-null_joystick.o -I vendor/glfw3/include -D_GLFW_WIN32 -D_CRT_SECURE_NO_WARNINGS
clang -g -c vendor/glfw3/src/null_window.c -o build/debug/obj/glfw-null_window.o -I vendor/glfw3/include -D_GLFW_WIN32 -D_CRT_SECURE_NO_WARNINGS

: glfw3 windows specific
clang -g -c vendor/glfw3/src/win32_init.c -o build/debug/obj/glfw-win32_init.o -I vendor/glfw3/include -D_GLFW_WIN32 -D_CRT_SECURE_NO_WARNINGS
clang -g -c vendor/glfw3/src/win32_module.c -o build/debug/obj/glfw-win32_module.o -I vendor/glfw3/include -D_GLFW_WIN32 -D_CRT_SECURE_NO_WARNINGS
clang -g -c vendor/glfw3/src/win32_joystick.c -o build/debug/obj/glfw-win32_joystick.o -I vendor/glfw3/include -D_GLFW_WIN32 -D_CRT_SECURE_NO_WARNINGS
clang -g -c vendor/glfw3/src/win32_monitor.c -o build/debug/obj/glfw-win32_monitor.o -I vendor/glfw3/include -D_GLFW_WIN32 -D_CRT_SECURE_NO_WARNINGS
clang -g -c vendor/glfw3/src/win32_time.c -o build/debug/obj/glfw-win32_time.o -I vendor/glfw3/include -D_GLFW_WIN32 -D_CRT_SECURE_NO_WARNINGS
clang -g -c vendor/glfw3/src/win32_thread.c -o build/debug/obj/glfw-win32_thread.o -I vendor/glfw3/include -D_GLFW_WIN32 -D_CRT_SECURE_NO_WARNINGS
clang -g -c vendor/glfw3/src/win32_window.c -o build/debug/obj/glfw-win32_window.o -I vendor/glfw3/include -D_GLFW_WIN32 -D_CRT_SECURE_NO_WARNINGS
clang -g -c vendor/glfw3/src/wgl_context.c -o build/debug/obj/glfw-wgl_context.o -I vendor/glfw3/include -D_GLFW_WIN32 -D_CRT_SECURE_NO_WARNINGS

: build project

: build source files
clang++ -g -std=c++20 -c source/main.cpp -o build/debug/obj/main.o -I include/ -I vendor/glad/include/ -I vendor/glfw3/include -I vendor/glm/include

: build final executable
clang++ -g -std=c++20 -o build/debug/a.exe build/debug/obj/*.o "%sdkpath%/User32.Lib" "%sdkpath%/Gdi32.Lib" "%sdkpath%/shell32.lib"
