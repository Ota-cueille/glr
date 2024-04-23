#pragma once
#include "utils.hpp"

#include <functional>

namespace event {

    enum class type { close, resize, refresh, keypress, size };
    
    struct Event {
        type t;
        union {
            struct{
                int key, scancode, action, mods;
            } keypress;
        };
        union {
            // resize events data
            struct {
                u32 width, height;
            } resize;
        };
    };

    using EventCallback = std::function<void(Event const&)>;

    void on(type t, EventCallback const& callback);
    void flush(type t, Event const& event);

} // namespace event