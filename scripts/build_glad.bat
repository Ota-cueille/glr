@setlocal
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

@echo -- Build GLAD --
@echo off

: build glad
clang %DEBUG_FLAG% -c vendor/glad/src/glad.c -o build/%mode%/obj/glad.o -I vendor/glad/include/

@echo on
@endlocal