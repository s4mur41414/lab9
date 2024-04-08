#include <gtest/gtest.h>

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include "../lib/take.h"
#include "../lib/values.h"
#include "../lib/keys.h"
#include "../lib/filter.h"
#include "../lib/transform.h"
#include "../lib/reverse.h"
#include "../lib/drop.h"

TEST(TransformTest, Squares) {
std::vector<int> v = {1, 2, 3, 4};
auto result = v | transform([](int i) { return i * i; });

std::vector<int> expected = {1, 4, 9, 16};
std::vector<int> output(result.begin(), result.end());

EXPECT_EQ(output, expected);
}

TEST(FilterTest, OddNumbers) {
std::vector<int> v = {1, 2, 3, 4, 5, 6};
auto result = v | filter([](int i) { return i % 2 != 0; });

std::vector<int> expected = {1, 3, 5};
std::vector<int> output(result.begin(), result.end());

EXPECT_EQ(output, expected);
}

TEST(TakeTest, FirstThree) {
std::vector<int> v = {1, 2, 3, 4, 5, 6};
auto result = v | take(3);

std::vector<int> expected = {1, 2, 3};
std::vector<int> output(result.begin(), result.end());

EXPECT_EQ(output, expected);
}

TEST(DropTest, SkipFirstThree) {
std::vector<int> v = {1, 2, 3, 4, 5, 6};
auto result = v | drop(3);

std::vector<int> expected = {4, 5, 6};
std::vector<int> output(result.begin(), result.end());

EXPECT_EQ(output, expected);
}

TEST(ReverseTest, ReversedVector) {
std::vector<int> v = {1, 2, 3, 4, 5, 6};
auto result = v | reverse();

std::vector<int> expected = {6, 5, 4, 3, 2, 1};
std::vector<int> output(result.begin(), result.end());

EXPECT_EQ(output, expected);
}

TEST(KeysTest, MapKeys) {
std::map<int, std::string> m = {{1, "one"}, {2, "two"}, {3, "three"}};
auto result = m | keys();

std::vector<int> expected = {1, 2, 3};
std::vector<int> output(result.begin(), result.end());

EXPECT_EQ(output, expected);
}

TEST(ValuesTest, MapValues) {
std::map<int, std::string> m = {{1, "one"},
                                {2, "two"},
                                {3, "three"}};
auto result = m | values();

std::vector <std::string> expected = {"one", "two", "three"};
std::vector <std::string> output(result.begin(), result.end());

EXPECT_EQ(output, expected
);
}