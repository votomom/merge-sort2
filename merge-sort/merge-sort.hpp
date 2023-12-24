#pragma once
#include <initializer_list>
#include <memory>

struct ListElement {
    int value;
    std::unique_ptr<ListElement> next;

    ListElement(int avalue, std::unique_ptr<ListElement> &&anext = nullptr)
        : value(avalue), next(std::move(anext)) {}
};

struct List {
    std::unique_ptr<ListElement> head;
    List(std::initializer_list<int>);
    List() = default;

    // Для того, чтобы избежать рекурсии при удалении
    List(List const &) = delete;
    List(List &&) = default;
    List& operator=(List const&) = delete;
    List& operator=(List&&) = default;
    ~List() {
        auto ptr = std::move(head);
        while (ptr) {
            auto tmp = std::move(ptr->next);
            ptr = std::move(tmp);
        }
    }
};

extern List merge(List, List) noexcept;

extern void mergesort(List&) noexcept;
