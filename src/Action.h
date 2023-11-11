#pragma once
#include <functional>
#include <list>

template<typename ... Args>
struct Action : public std::shared_ptr<std::list<std::function<void(Args...)>>> {

    using Handler = std::function<void(Args...)>;
    using listener_list = std::list<Handler>;

    struct Listener {
        std::weak_ptr<listener_list> the_action;
        typename listener_list::iterator it;

        Listener() {}

        Listener(Action &s, Handler function) {
            Observe(s, function);
        }

        Listener(Listener &&other) {
            the_action = other.the_action;
            it = other.it;
            other.the_action.reset();
        }

        Listener(const Listener &other) = delete;

        Listener &operator=(const Listener &other) = delete;

        Listener &operator=(Listener &&other) {
            Reset();
            the_action = other.the_action;
            it = other.it;
            other.the_action.reset();
            return *this;
        }

        void Observe(Action &action, Handler function) {
            Reset();
            the_action = action;
            it = action->insert(action->end(), function);
        }

        void Reset() {
            if (!the_action.expired()) the_action.lock()->erase(it);
            the_action.reset();
        }

        ~Listener() { Reset(); }
    };

    Action() : std::shared_ptr<listener_list>(std::make_shared<listener_list>()) {}

    Action(const Action &) = delete;

    Action &operator=(const Action &) = delete;

    void Notify(Args... args) {
        for (auto &f: **this) f(args...);
    }

    Listener Connect(Handler h) {
        return Listener(*this, h);
    }
};