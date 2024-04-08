#pragma once

namespace Adapter {
    template<typename Func, typename T, typename Position>
    class TransformIterator {
    public:
        using iter_type = typename std::remove_reference_t<T>::iterator;
        using value_type = typename std::iterator_traits<iter_type>::value_type;
        using difference_type = Position;
        using pointer = value_type*;
        using reference = value_type&;
        using iterator_category = std::forward_iterator_tag;

        TransformIterator() = default;

        TransformIterator(Func func, T array, Position pos, Position pos_end): func_(func), arr(array), pos_(pos), pos_end_(pos_end) {}

        TransformIterator& operator++() {
            ++pos_;
            return *this;
        }

        TransformIterator& operator--() {
            ---pos_;
            return *this;
        }

        TransformIterator operator++(int) {
            TransformIterator new_iter(*this);
            ++pos_;
            return new_iter;
        }

        TransformIterator operator--(int) {
            TransformIterator new_iter(*this);
            --pos_;
            return new_iter;
        }

        value_type operator*() const {
            auto it = arr.begin();
            std::advance(it, pos_);
            return func_(*it);
        }

        friend bool operator==(const TransformIterator& first, const TransformIterator& second) {
            return first.pos_ == second.pos_;
        }

        friend bool operator!=(const TransformIterator& first, const TransformIterator& second) {
            return !(first == second);
        }

    private:
        Func func_;
        T arr;
        Position pos_;
        Position pos_end_;
    };

    template<typename Iterator>
    class Transform {
    public:
        using value_type = typename Iterator::value_type;
        using iterator = Iterator;

        Transform() = default;

        Transform(Iterator begin, Iterator end): begin_(begin), end_(end) {}

        Iterator begin() const {
            return begin_;
        }

        Iterator end() const {
            return end_;
        }

    private:
        Iterator begin_;
        Iterator end_;
    };

    template<typename Func>
    struct TransformCall {
        Func func;

        template<typename T>
        friend auto operator|(T t, TransformCall transform_call) {
            using iter_type = typename std::remove_reference_t<T>::iterator;
            using diff_type = typename std::iterator_traits<iter_type>::difference_type;
            using value_type = typename std::iterator_traits<iter_type>::value_type;
            TransformIterator<Func, T, diff_type> begin_iter{transform_call.func, t, 0, std::distance(t.begin(), t.end())};
            TransformIterator<Func, T, diff_type> end_iter{transform_call.func, t, std::distance(t.begin(), t.end()), std::distance(t.begin(), t.end())};
            return Transform<TransformIterator<Func, T, diff_type>>{begin_iter, end_iter};
        }
    };

    struct TransformAdapter {
        template<typename Func>
        auto operator()(Func func) {
            return TransformCall<Func>{func};
        }
    };
} 

Adapter::TransformAdapter transform;