:process_configuration

@if "%1" == "" goto :build
@if "%2" == "" goto :build

@set %1=%2

@shift
@shift

@goto :process_configuration %*

:build

: build glad
clang -g -c vendor/glad/src/glad.c -o build/%mode%/obj/glad.o -I vendor/glad/include/