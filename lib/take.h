#pragma once

namespace Adapter {
    template<typename T, typename Count>
    class Take {
    public:
        using iterator = typename std::remove_reference_t<T>::iterator;
        using value_type = typename std::iterator_traits<iterator>::value_type;

        Take() = default;

        Take(T array, Count count): arr{array}, count_{count} {}

        auto begin() const {
            return arr.begin();
        }

        auto end() const {
            return arr.begin() + count_;
        }

    private:
        T arr;
        Count count_;
    };

    template<typename Count>
    struct TakeCall {
        Count count;

        template<typename T>
        friend auto operator|(T r, TakeCall take_call) {
            return Take<T, Count>{r, take_call.count};
        }
    };

    struct TakeAdapter {
        template<typename T>
        auto operator()(T count) {
            return TakeCall<T>{count};
        }
    };
}

Adapter::TakeAdapter take;