#pragma once

namespace Adapter {
    template<typename Func, typename T, typename Position>
    class FilterIterator {
    public:
        using iter_type = typename std::remove_reference_t<T>::iterator;
        using value_type = typename std::iterator_traits<iter_type>::value_type;
        using difference_type = Position;
        using pointer = value_type*;
        using reference = value_type&;
        using iterator_category = std::forward_iterator_tag;

        FilterIterator() = default;

        FilterIterator(Func func, T array, Position pos, Position pos_end): func_(func), arr(array), pos_(pos), pos_end_(pos_end) {
            move_next();
        }

        FilterIterator& operator++() {
            ++pos_;
            move_next();
            return *this;
        }

        FilterIterator& operator--() {
            --pos_;
            move_prev();
            return *this;
        }

        FilterIterator operator++(int) {
            FilterIterator new_iter(*this);
            move_next();
            ++pos_;
            return new_iter;
        }

        FilterIterator operator--(int) {
            FilterIterator new_iter(*this);
            move_prev();
            --pos_;
            return new_iter;
        }

        value_type operator*() const {
            auto it = arr.begin();
            std::advance(it, pos_);
            return *it;
        }

        friend bool operator==(const FilterIterator& first, const FilterIterator& second) {
            return first.pos_ == second.pos_;
        }

        friend bool operator!=(const FilterIterator& first, const FilterIterator& second) {
            return !(first == second);
        }

    private:
        void move_next() {
            while (pos_ < pos_end_ && !func_(*(std::next(arr.begin(), pos_)))) {
                ++pos_;
            }
        }

        void move_prev() {
            while (pos_ > 0 && !func_(*(std::prev(arr.begin(), pos_)))) {
                --pos_;
            }
        }

        Func func_;
        T arr;
        Position pos_;
        Position pos_end_;
    };

    template<typename Iterator>
    class Filter {
    public:
        using value_type = typename Iterator::value_type;
        using iterator = Iterator;

        Filter() = default;

        Filter(Iterator begin, Iterator end): begin_(begin), end_(end) {}

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
    struct FilterCall {
        Func func;

        template<typename T>
        friend auto operator|(T t, FilterCall filter_call) {
            using iter_type = typename std::remove_reference_t<T>::iterator;
            using diff_type = typename std::iterator_traits<iter_type>::difference_type;
            using value_type = typename std::iterator_traits<iter_type>::value_type;
            FilterIterator<Func, T, diff_type> begin_iter{filter_call.func, t, 0, std::distance(t.begin(), t.end())};
            FilterIterator<Func, T, diff_type> end_iter{filter_call.func, t, std::distance(t.begin(), t.end()), std::distance(t.begin(), t.end())};
            return Filter<FilterIterator<Func, T, diff_type>>{begin_iter, end_iter};
        }
    };

    struct FilterAdapter {
        template<typename Func>
        auto operator()(Func func) {
            return FilterCall<Func>{func};
        }
    };
} 

Adapter::FilterAdapter filter;