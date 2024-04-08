#pragma once

namespace Adapter {
    template<typename T, typename Count>
    class Drop {
    public:
        using iter_type = typename std::remove_reference_t<T>::iterator;
        using value_type = typename std::iterator_traits<iter_type>::value_type;

        Drop() = default;

        Drop(T array, Count count): arr{array}, count_{count} {}

        auto begin() const {
            return arr.begin() + count_;
        }

        auto end() const {
            return arr.end();
        }

    private:
        T arr;
        Count count_;
    };

    template<typename Count>
    struct DropCall {
        Count count;

        template<typename T>
        friend auto operator|(T t, DropCall drop_call) {
            return Drop<T, Count>{t, drop_call.count};
        }
    };

    struct DropAdapter {
        template<typename T>
        auto operator()(T count) {
            return DropCall<T>{count};
        }
    };
}

Adapter::DropAdapter drop;