#include "merge-sort.hpp"
#include <algorithm>
#include <doctest.h>
#include <initializer_list>
#include <limits>
#include <ostream>
#include <vector>

bool operator==(ListElement const &a, ListElement const &b) {
    if (a.value != b.value) return false;
    if (!a.next && !b.next) return true;
    if (!a.next || !b.next) return false;
    return *(a.next) == *(b.next);
}

bool operator==(List const &a, List const &b) {
    if (!a.head && !b.head) return true;
    if (!a.head || !b.head) return false;
    return *(a.head) == *(b.head);
}

std::ostream &operator<<(std::ostream &s, List const &l) {
    s << "List{";
    auto *ptr = l.head.get();
    while (ptr != nullptr) {
        s << ptr->value;
        if (ptr->next != nullptr)
            s << ", ";
        ptr = ptr->next.get();
    }
    s << "}";
    return s;
}

TEST_SUITE_BEGIN("constructor");

TEST_CASE("Empty List") {
    auto a = List{};
    REQUIRE(a.head == nullptr);
}

TEST_CASE("List 1") {
    auto a = List{1};
    REQUIRE(a.head != nullptr);
    REQUIRE(a.head->value == 1);
    REQUIRE(a.head->next == nullptr);
}

TEST_CASE("List 1,2") {
    auto a = List{1,2};
    REQUIRE(a.head != nullptr);
    REQUIRE(a.head->value == 1);
    REQUIRE(a.head->next != nullptr);
    REQUIRE(a.head->next->value == 2);
    REQUIRE(a.head->next->next == nullptr);
}

TEST_CASE("List 1,2,...,0") {
    // NOLINTNEXTLINE
    auto ilist = {1,2,3,4,5,6,7,8,9,0};
    auto a = List(ilist);
    ListElement *ptr = a.head.get();
    for (auto elem : ilist) {
        REQUIRE(ptr != nullptr);
        CHECK(ptr->value == elem);
        ptr = ptr->next.get();
    }
    CHECK(ptr == nullptr);
}

TEST_SUITE_END();

TEST_SUITE_BEGIN("merge");

TEST_CASE("null") {
    REQUIRE(merge(List{}, List{}) == List{});
    REQUIRE(merge(List{1}, List{}) == List{1});
    REQUIRE(merge(List{}, List{1}) == List{1});
    REQUIRE(merge(List{3, 1, 2}, List{}) == List{3, 1, 2});
    REQUIRE(merge(List{}, List{1, 3, 2}) == List{1, 3, 2});
}

TEST_CASE("simple 123456") {
    REQUIRE(merge(List{1, 2, 3}, List{4, 5, 6}) == List{1, 2, 3, 4, 5, 6});
    REQUIRE(merge(List{4, 5, 6}, List{1, 2, 3}) == List{1, 2, 3, 4, 5, 6});
    REQUIRE(merge(List{1, 3, 5}, List{2, 4, 6}) == List{1, 2, 3, 4, 5, 6});
    REQUIRE(merge(List{1, 6}, List{2, 3, 4, 5}) == List{1, 2, 3, 4, 5, 6});
}

TEST_CASE("dup") {
    REQUIRE(merge(List{1, 2, 3}, List{1, 2, 3}) == List{1, 1, 2, 2, 3, 3});
    REQUIRE(merge(List{4, 5, 6}, List{1, 2, 3, 4}) ==
            List{1, 2, 3, 4, 4, 5, 6});
}

TEST_SUITE_END();

TEST_SUITE_BEGIN("sort");

void sort_tester(std::vector<int> range) {
    List list{};
    // Проход по массиву в обратном порядке
    for (auto it = rbegin(range); it != rend(range); ++it)
        list.head = std::make_unique<ListElement>(*it, std::move(list.head));
    mergesort(list);
    std::sort(begin(range), end(range));
    auto *ptr = list.head.get();
    for (auto number : range) {
        REQUIRE(ptr != nullptr);
        REQUIRE(ptr->value == number);
        ptr = ptr->next.get();
    }
    CHECK(ptr == nullptr);
}

TEST_CASE("null") {
    sort_tester({});
}

TEST_CASE("small") {
    sort_tester({3, 2, 1});
    sort_tester({1, 2, 3});
    sort_tester({3, 1, 2});
    sort_tester({2, 3, 1});
    sort_tester({2, 1, 3});
}

TEST_CASE("dup") {
    sort_tester({1, 2, 1, 3});
    sort_tester({1, 1, 1});
    sort_tester({1, 2, 3, 1, 2, 3});
    sort_tester({-1, -2, -3, -4});
}

auto make_simple_vector(int size, int prime) {
    std::vector<int> v;
    for (int i = 1; i < size; ++i)
        v.push_back(i * prime % size);
    return v;
}

TEST_CASE("larger") {
    sort_tester(make_simple_vector(10, 7)); // NOLINT
    sort_tester(make_simple_vector(100, 7)); // NOLINT
    sort_tester(make_simple_vector(128, 11)); // NOLINT
    sort_tester(make_simple_vector(128, 127)); // NOLINT
    sort_tester(make_simple_vector(128, 63)); // NOLINT
    sort_tester(make_simple_vector(128, 13)); // NOLINT
}

TEST_CASE("huge") {
    sort_tester(make_simple_vector(100'000, 7)); // NOLINT
    sort_tester(make_simple_vector(100'000, 654321)); // NOLINT
}

TEST_SUITE_END();

// Для проверки всех ошибок
extern "C" const char *__asan_default_options() {
    return "debug=1:detect_invalid_pointer_pairs=2:detect_leak=1:detect_leaks=1"
           ":leak_check_at_exit=true:color=always";
}
