#include "events.hpp"

#include <list>
#include <array>

namespace event {

    static std::array<std::list<EventCallback>, cast(u64, type::count)> callbacks;

    void on(type t, EventCallback const& callback) {
        u64 i = cast(u64, t);
        callbacks[i].push_back(callback);
    }

    void dispatch(type t, Event const& event) {
        for (auto const& callback : callbacks[cast(u64, t)]) callback(event);
    }

    namespace key {

        mods operator|(mods mod1, mods mod2) noexcept { return cast(mods, cast(u8, mod1) | cast(u8, mod2)); }
        bool operator&(mods mod1, mods mod2) noexcept { return cast(bool, cast(u8, mod1) & cast(u8, mod2)); }

    } // namespace key

} // namespace event