#include "events.hpp"

#include <list>
#include <array>

namespace event {

    static std::array<std::list<EventCallback>, cast(u64, type::size)> callbacks;

    void on(type t, std::function<void(Event const&)> const& callback) {
        u64 i = cast(u64, t);
        callbacks[i].push_back(callback);
    }

    void exec(type t, Event const& event) {
        for (auto const& callback : callbacks[cast(u64, t)]) callback(event);
    }

} // namespace events