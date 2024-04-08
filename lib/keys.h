#pragma once

namespace Adapter {
    template<typename T, typename Position>
    class KeysIterator {
    public:
        using iter_type = typename std::remove_reference_t<T>::iterator;
        using value_type = typename std::iterator_traits<iter_type>::value_type;
        using difference_type = Position;
        using pointer = typename std::iterator_traits<iter_type>::pointer;
        using reference = typename std::iterator_traits<iter_type>::reference;
        using iterator_category = std::forward_iterator_tag;

        KeysIterator() = default;

        KeysIterator(T array, Position pos, Position pos_end): arr(array), pos_(pos), pos_end_(pos_end) {}

        KeysIterator& operator++() {
            ++pos_;
            return *this;
        }

        KeysIterator& operator--() {
            ---pos_;
            return *this;
        }

        KeysIterator operator++(int) {
            KeysIterator new_iter(*this);
            ++pos_;
            return new_iter;
        }

        KeysIterator operator--(int) {
            KeysIterator new_iter(*this);
            --pos_;
            return new_iter;
        }

        typename value_type::first_type operator*() const {
            auto it = arr.begin();
            std::advance(it, pos_);
            return it->first;
        }

        friend bool operator==(const KeysIterator& first, const KeysIterator& second) {
            return first.pos_ == second.pos_;
        }

        friend bool operator!=(const KeysIterator& first, const KeysIterator& second) {
            return !(first == second);
        }

    private:
        T arr;
        Position pos_;
        Position pos_end_;
    };

    template<typename Iterator>
    class Keys {
    public:
        using value_type = typename Iterator::value_type::first_type;
        using iterator = Iterator;

        Keys() = default;

        Keys(Iterator begin, Iterator end): begin_(begin), end_(end) {}

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

    struct KeysCall {
        template<typename T>
        friend auto operator|(T t, KeysCall keys_call) {
            using iter_type = typename std::remove_reference_t<T>::iterator;
            using diff_type = typename std::iterator_traits<iter_type>::difference_type;
            using value_type = typename std::iterator_traits<iter_type>::value_type;
            KeysIterator<T, diff_type> begin_iter{t, 0, std::distance(t.begin(), t.end())};
            KeysIterator<T, diff_type> end_iter{t, std::distance(t.begin(), t.end()), std::distance(t.begin(), t.end())};
            return Keys<KeysIterator<T, diff_type>>{begin_iter, end_iter};
        }
    };

    struct KeysAdapter {
        auto operator()() {
            return KeysCall{};
        }
    };
}

Adapter::KeysAdapter keys;