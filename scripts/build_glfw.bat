@set mode=debug
@set architecture=x64

:process_configuration

@if "%1" == "" goto :build
@if "%2" == "" goto :build

@set %1=%2

@shift
@shift

@goto :process_configuration %*

:build

@if "%mode%"=="debug" (@set DEBUG_FLAG=-g) else (@set DEBUG_FLAG=)

@echo -- Build GLFW --
@echo off

: build glfw3
clang %DEBUG_FLAG% -c vendor/glfw3/src/context.c -o build/%mode%/obj/glfw-context.o -I vendor/glfw3/include -D_GLFW_WIN32 -D_CRT_SECURE_NO_WARNINGS
clang %DEBUG_FLAG% -c vendor/glfw3/src/init.c -o build/%mode%/obj/glfw-init.o -I vendor/glfw3/include -D_GLFW_WIN32 -D_CRT_SECURE_NO_WARNINGS
clang %DEBUG_FLAG% -c vendor/glfw3/src/input.c -o build/%mode%/obj/glfw-input.o -I vendor/glfw3/include -D_GLFW_WIN32 -D_CRT_SECURE_NO_WARNINGS
clang %DEBUG_FLAG% -c vendor/glfw3/src/monitor.c -o build/%mode%/obj/glfw-monitor.o -I vendor/glfw3/include -D_GLFW_WIN32 -D_CRT_SECURE_NO_WARNINGS
clang %DEBUG_FLAG% -c vendor/glfw3/src/platform.c -o build/%mode%/obj/glfw-platform.o -I vendor/glfw3/include -D_GLFW_WIN32 -D_CRT_SECURE_NO_WARNINGS
clang %DEBUG_FLAG% -c vendor/glfw3/src/vulkan.c -o build/%mode%/obj/glfw-vulkan.o -I vendor/glfw3/include -D_GLFW_WIN32 -D_CRT_SECURE_NO_WARNINGS
clang %DEBUG_FLAG% -c vendor/glfw3/src/window.c -o build/%mode%/obj/glfw-window.o -I vendor/glfw3/include -D_GLFW_WIN32 -D_CRT_SECURE_NO_WARNINGS

clang %DEBUG_FLAG% -c vendor/glfw3/src/egl_context.c -o build/%mode%/obj/glfw-egl_context.o -I vendor/glfw3/include -D_GLFW_WIN32 -D_CRT_SECURE_NO_WARNINGS
clang %DEBUG_FLAG% -c vendor/glfw3/src/osmesa_context.c -o build/%mode%/obj/glfw-osmesa_context.o -I vendor/glfw3/include -D_GLFW_WIN32 -D_CRT_SECURE_NO_WARNINGS

clang %DEBUG_FLAG% -c vendor/glfw3/src/null_init.c -o build/%mode%/obj/glfw-null_init.o -I vendor/glfw3/include -D_GLFW_WIN32 -D_CRT_SECURE_NO_WARNINGS
clang %DEBUG_FLAG% -c vendor/glfw3/src/null_monitor.c -o build/%mode%/obj/glfw-null_monitor.o -I vendor/glfw3/include -D_GLFW_WIN32 -D_CRT_SECURE_NO_WARNINGS
clang %DEBUG_FLAG% -c vendor/glfw3/src/null_joystick.c -o build/%mode%/obj/glfw-null_joystick.o -I vendor/glfw3/include -D_GLFW_WIN32 -D_CRT_SECURE_NO_WARNINGS
clang %DEBUG_FLAG% -c vendor/glfw3/src/null_window.c -o build/%mode%/obj/glfw-null_window.o -I vendor/glfw3/include -D_GLFW_WIN32 -D_CRT_SECURE_NO_WARNINGS

: glfw3 windows specific
clang %DEBUG_FLAG% -c vendor/glfw3/src/win32_init.c -o build/%mode%/obj/glfw-win32_init.o -I vendor/glfw3/include -D_GLFW_WIN32 -D_CRT_SECURE_NO_WARNINGS
clang %DEBUG_FLAG% -c vendor/glfw3/src/win32_module.c -o build/%mode%/obj/glfw-win32_module.o -I vendor/glfw3/include -D_GLFW_WIN32 -D_CRT_SECURE_NO_WARNINGS
clang %DEBUG_FLAG% -c vendor/glfw3/src/win32_joystick.c -o build/%mode%/obj/glfw-win32_joystick.o -I vendor/glfw3/include -D_GLFW_WIN32 -D_CRT_SECURE_NO_WARNINGS
clang %DEBUG_FLAG% -c vendor/glfw3/src/win32_monitor.c -o build/%mode%/obj/glfw-win32_monitor.o -I vendor/glfw3/include -D_GLFW_WIN32 -D_CRT_SECURE_NO_WARNINGS
clang %DEBUG_FLAG% -c vendor/glfw3/src/win32_time.c -o build/%mode%/obj/glfw-win32_time.o -I vendor/glfw3/include -D_GLFW_WIN32 -D_CRT_SECURE_NO_WARNINGS
clang %DEBUG_FLAG% -c vendor/glfw3/src/win32_thread.c -o build/%mode%/obj/glfw-win32_thread.o -I vendor/glfw3/include -D_GLFW_WIN32 -D_CRT_SECURE_NO_WARNINGS
clang %DEBUG_FLAG% -c vendor/glfw3/src/win32_window.c -o build/%mode%/obj/glfw-win32_window.o -I vendor/glfw3/include -D_GLFW_WIN32 -D_CRT_SECURE_NO_WARNINGS
clang %DEBUG_FLAG% -c vendor/glfw3/src/wgl_context.c -o build/%mode%/obj/glfw-wgl_context.o -I vendor/glfw3/include -D_GLFW_WIN32 -D_CRT_SECURE_NO_WARNINGS

@echo on