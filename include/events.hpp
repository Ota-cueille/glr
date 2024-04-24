#pragma once
#include "utils.hpp"

#include <functional>

namespace event {

    enum class type {
        close,
        resize,
        refresh,
        
        key,
        key_pressed,
        key_released,
        key_hold,

        // printable character was pressed or held down by the user
        character,

        count
    };

    namespace key {
        enum class action : u8 { release, press, hold };

        enum class mods : u8 {
            none    = 0b00000000, // 0
            shift   = 0b00000001, // 1
            ctrl    = 0b00000010, // 2
            alt     = 0b00000100, // 4
            super   = 0b00001000, // 8
            caps    = 0b00010000, // 16
            num     = 0b00100000, // 32
        };

        mods operator|(mods mod1, mods mod2) noexcept;
        bool operator&(mods mod1, mods mod2) noexcept;
    }

    struct Event {
        type t;
        union {
            // key events data
            struct{
                int keycode, scancode;
                key::action action;
                key::mods mods;               
            } key;

            struct {
                u32 unicode;
            } character;

            // resize events data
            struct {
                u32 width, height;
            } resize;
        };
    };

    using EventCallback = std::function<void(Event const&)>;

    void on(type t, EventCallback const& callback);
    void dispatch(type t, Event const& event);

} // namespace event