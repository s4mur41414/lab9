#include <iostream>
#include <vector>
#include <string>
#include <map>
#include "lib/drop.h"
#include "lib/take.h"
#include "lib/values.h"
#include "lib/keys.h"
#include "lib/filter.h"
#include "lib/transform.h"
#include "lib/reverse.h"

int main() {
    std::vector<int> v = {1, 2, 3, 4, 5, 6};

    for (int i: v | filter([](int i) { return i % 2; }) | transform([](int i) { return i * i; }))
        std::cout << i << " ";
}