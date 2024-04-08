#pragma once

namespace Adapter {
    template<typename T, typename Position>
    class ValuesIterator {
    public:
        using iter_type = typename std::remove_reference_t<T>::iterator;
        using value_type = typename std::iterator_traits<iter_type>::value_type;
        using difference_type = Position;
        using pointer = typename std::iterator_traits<iter_type>::pointer;
        using reference = typename std::iterator_traits<iter_type>::reference;
        using iterator_category = std::forward_iterator_tag;

        ValuesIterator() = default;

        ValuesIterator(T array, Position pos, Position pos_end): arr(array), pos_(pos), pos_end_(pos_end) {}

        ValuesIterator& operator++() {
            ++pos_;
            return *this;
        }

        ValuesIterator& operator--() {
            ---pos_;
            return *this;
        }

        ValuesIterator operator++(int) {
            ValuesIterator new_iter(*this);
            ++pos_;
            return new_iter;
        }

        ValuesIterator operator--(int) {
            ValuesIterator new_iter(*this);
            --pos_;
            return new_iter;
        }

        typename value_type::second_type operator*() const {
            auto it = arr.begin();
            std::advance(it, pos_);
            return it->second;
        }

        friend bool operator==(const ValuesIterator& left, const ValuesIterator& right) {
            return left.pos_ == right.pos_;
        }

        friend bool operator!=(const ValuesIterator& left, const ValuesIterator& right) {
            return !(left == right);
        }

    private:
        T arr;
        Position pos_;
        Position pos_end_;
    };

    template<typename Iterator>
    class Values {
    public:
        using value_type = typename Iterator::value_type::second_type;
        using iterator = Iterator;

        Values() = default;

        Values(Iterator begin, Iterator end): begin_(begin), end_(end) {
        }

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

    struct ValuesCall {
        template<typename T>
        friend auto operator|(T&& t, ValuesCall values_call) {
            using iter_type = typename std::remove_reference_t<T>::iterator;
            using diff_type = typename std::iterator_traits<iter_type>::difference_type;
            using value_type = typename std::iterator_traits<iter_type>::value_type;
            ValuesIterator<T, diff_type> begin_iter{t, 0, std::distance(t.begin(), t.end())};
            ValuesIterator<T, diff_type> end_iter{t, std::distance(t.begin(), t.end()), std::distance(t.begin(), t.end())};
            return Values<ValuesIterator<T, diff_type>>{begin_iter, end_iter};
        }
    };

    struct ValuesAdapter {
        auto operator()() {
            return ValuesCall{};
        }
    };
} 

Adapter::ValuesAdapter values;