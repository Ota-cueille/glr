#pragma once
#include "utils.hpp"

#include <functional>

namespace event {

    enum class type { close, resize, refresh, key, size };
    
    namespace key {
        enum class action {press, release, keep};
        enum class mods {ctrl, alt, shift, caps, num};
    }

    struct Event {
        type t;
        union {
            // key events data
            struct{
                int keycode, scancode;
                event::key::action action;
                event::key::mods mods;               
            } key;

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