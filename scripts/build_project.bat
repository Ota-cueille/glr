:process_configuration

@if "%1" == "" goto :build
@if "%2" == "" goto :build

@set %1=%2

@shift
@shift

@goto :process_configuration %*

:build

set dir=%ProgramFiles(x86)%/Windows Kits/10/Lib/

@if "%mode%"=="debug" (
    set DEBUG_FLAG=-g
) else (
    set DEBUG_FLAG=
)

: récupération de la version du sdk
@for /f "delims=" %%F in ('dir /b "%dir%\*"') do (
    set version=%%~nxF
)

set sdkpath=%dir%/%version%/um/%architecture%

@echo off

: build project

: build source files
clang++ %DEBUG_FLAG% -std=c++20 -c source/main.cpp -o build/%mode%/obj/main.o -I include/ -I vendor/glad/include/ -I vendor/glfw3/include -I vendor/glm/include

: build final executable
clang++ %DEBUG_FLAG% -std=c++20 -o build/%mode%/a.exe build/%mode%/obj/*.o "%sdkpath%/User32.Lib" "%sdkpath%/Gdi32.Lib" "%sdkpath%/shell32.lib"

@echo on