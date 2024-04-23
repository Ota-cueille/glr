#include "utils.hpp"

#include <functional>

namespace event {

    enum class type { close, resize, refresh, size };
    
    struct Event {
        type t;
        union {
            // resize events data
            struct {
                u32 height, width;
            } resize;
        };
    };

    using EventCallback = std::function<void(Event const&)>;

    void on(type t, EventCallback const& callback);

    void poll();
    void initialize(void* window);

} // namespace event