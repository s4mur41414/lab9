#pragma once

struct reverse {
};

template<typename T>
class Reverse {
public:
    Reverse(const T& array) : arr(array) {}

    auto base_begin() const {
        return arr.begin();
    }

    auto base_end() const {
        return arr.end();
    }

    auto begin() const {
        return std::make_reverse_iterator(base_end());
    }

    auto end() const {
        return std::make_reverse_iterator(base_begin());
    }

private:
    const T& arr;
};

template<typename T>
Reverse<T> operator|(const T& array, const reverse&) {
    return Reverse<T>(array);
}