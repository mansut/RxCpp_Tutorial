#if 1
#include "rxcpp/rx.hpp"
namespace rx=rxcpp;
namespace rxu=rxcpp::util;
namespace rxsc=rxcpp::schedulers;

#include "rxcpp/rx-test.hpp"

        auto sc = rxsc::make_test();
        const rxsc::test::messages<int> on;
#else
#include <memory>
#include <vector>
#include <functional>

namespace detail {

template<typename T>
struct notification_base
    : public std::enable_shared_from_this<notification_base<T>>
{
    typedef std::shared_ptr<notification_base<T>> type;
    typedef std::function<void(T)> observer_type;

    virtual ~notification_base() {}
    virtual void accept(const observer_type& o) const =0;
};

}

template<typename T>
struct notification
{
    typedef typename detail::notification_base<T>::type type;

    typedef detail::notification_base<T> base;

    struct value_notification : public base {
        value_notification(T value) : value(std::move(value)) {
        }
        value_notification(const value_notification& o) : value(o.value) {}
        value_notification(const value_notification&& o) : value(std::move(o.value)) {}
        value_notification& operator=(value_notification o) { value = std::move(o.value); return *this; }
        virtual void accept(const typename base::observer_type& o) const {
            o(value);
        }
        const T value;
    };

    template<typename U>
    static type value(U v) {
        return std::make_shared<value_notification>(std::move(v));
    }
};

template<class T>
class recorded
{
    T v;
public:
    recorded(T v)
        : v(v) {
    }
    T value() const {
        return v;
    }
};

template<class T>
struct made
{
    struct base : std::enable_shared_from_this<base>
    {
        virtual ~base(){}
    };

    made(std::shared_ptr<base> b) : b(b) {}
    std::shared_ptr<base> b;
};

struct worker
{
    struct Inner : std::enable_shared_from_this<Inner>
    {
        virtual ~Inner() {}
    };

    std::shared_ptr<Inner> inner = std::make_shared<Inner>();
};
worker create() { return{}; };

struct state_base : std::enable_shared_from_this<state_base>
{
    virtual ~state_base() {}
};

struct Tester
{
    template<class T>
    made<T> make(std::vector<recorded<std::shared_ptr<detail::notification_base<T>>>> messages) const;

    struct state_type : state_base 
    {
        virtual ~state_type() {}
    };

    std::shared_ptr<state_type> state = std::make_shared<state_type>();
};

template<class T>
class hot : public made<T>::base
{
    typedef recorded<std::shared_ptr<detail::notification_base<T>>> recorded_type;
    std::shared_ptr<Tester::state_type> sc;
    mutable std::vector<recorded_type> mv;
    mutable std::vector<std::function<void()>> s;
    mutable std::vector<std::function<void(T)>> o;
    mutable worker controller;
public:
    hot(std::shared_ptr<Tester::state_type> sc, worker w, std::vector<recorded_type> mv)
        : sc(sc)
        , mv(mv)
        , controller(w)
    {
        for (auto& message : mv) {
            auto n = message.value();
            s.push_back(
                [this, n]() {
                    auto local = this->o;
                    for (auto& o : local) {
                        n->accept(o);
                    }
                });
        }
    }
    virtual ~hot() {}
};

template<class T>
made<T> Tester::make(std::vector<recorded<std::shared_ptr<detail::notification_base<T>>>> messages) const
{
    return made<T>(std::make_shared<hot<T>>(state, create(), std::move(messages)));
}

struct SC
{
    template<class T>
    std::shared_ptr<hot<T>> make_hot_observable(std::vector<recorded<std::shared_ptr<detail::notification_base<T>>>> messages) const{
        return tester->make(std::move(messages));
    }

    template<class T>
    auto make_hot_observable(std::initializer_list<T> il) const
        -> decltype(tester->make(std::vector<T>())) {
        return      tester->make(std::vector<T>(il));
    }

    std::shared_ptr<Tester> tester = std::make_shared<Tester>();
};
SC sc;

struct ON
{
    typedef detail::notification_base<int> notification_type;
    typedef recorded<std::shared_ptr<detail::notification_base<int>>> recorded_type;

    template<typename U>
    static recorded_type next(long , U v) {
        return recorded_type(notification<int>::value(v));
    }

    static recorded_type completed(long ) {
        return recorded_type(notification<int>::value(0));
    }
};
ON on;
#endif

extern        auto xs = sc.make_hot_observable({
            on.next(150, 1),
            on.next(210, 2),
            on.next(220, 3),
            on.next(230, 4),
            on.next(240, 5),
            on.completed(250)
        });


int main() {
    return 0;
}
