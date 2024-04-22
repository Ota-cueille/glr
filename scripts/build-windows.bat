@setlocal
@echo -- Build Project : glr --


@rem default configuration
@set mode=debug
@set architecture=x64


@rem check for parameters
@if "%*" == "" (
    goto :build
) else (
    goto :process_configuration %*
)

@rem start build script
:build

@echo -- Build Configuration --
@echo {
@echo     mode         = %mode%
@echo     architecture = %architecture%
@echo }

if not exist "./build" mkdir "./build"
if not exist "./build/%mode%" mkdir "./build/%mode%"
if not exist "./build/%mode%/obj" mkdir "./build/%mode%/obj"

@call cmd /c "%CD%/scripts/build_glad.bat architecture=%architecture% mode=%mode%"
@call cmd /c "%CD%/scripts/build_glfw.bat architecture=%architecture% mode=%mode%"
@call cmd /c "%CD%/scripts/build_project.bat architecture=%architecture% mode=%mode%"

@rem exit normally
:end
@echo -- Build Complete --
@exit /b


@rem exit with failure
:abort
@echo -- Build Aborted --
@echo reason: %reason%
@exit /b 1


@rem helper to process input files
:process_configuration

@if "%1" == "" goto :build
@if "%2" == "" goto :build

@set %1=%2

@shift
@shift

@goto :process_configuration %*