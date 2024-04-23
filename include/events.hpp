
#include <functional>
#include "utils.hpp"

namespace events {
    enum class types {
        click,close,resize,refresh,hover,size
    };
    
    struct Event {
        types type;
        i32 height;
        i32 width;
    };

    using EventCallback = std::function<void(const Event&)>;

    void on(types eventType,const std::function<void(const Event&)>& callback);

    template <types eventType>
    void exec(Event const & event);

    void poll();
    void initialize(void * window);
}