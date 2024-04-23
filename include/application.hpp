#pragma once

#include "utils.hpp"
#include "events.hpp"

namespace application {

    void initialize(const char* name, u32 width = 640, u32 height = 480);
    void terminate();
    void swap_buffers();
    void poll_events();

    namespace state {

        extern bool const& running;
        extern u32 const& width, &height;

    } // namespace state

} // namespace application