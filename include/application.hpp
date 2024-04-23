#pragma once

#include "utils.hpp"
#include "events.hpp"

namespace application {

    void initialize(const char* name, u32 width = 640, u32 height = 480);
    void terminate();
    void swapBuffers();

} // namespace application