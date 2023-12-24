#include "merge-sort.hpp"
#include <memory>

List::List(std::initializer_list<int> list) {
    // Задание №1: сделать список из list
    ListElement * tail = nullptr;
    for (auto number : list) {
        // TODO: Добавить в создаваемый односвязный список
        if (tail == nullptr) {
            // TODO: Создать первый элемент списка в head
        } else {
            // TODO: Создать элемент списка в tail->next
        }
    }
}

auto merge(List a, List b) noexcept -> List {
    // Слияние двух упорядоченных списков
    List result;
    ListElement *tail =
        nullptr; // должен указывать на последний элемент списка result
    while (a.head && b.head) {
        // Выбираем меньший из a.head.value и b.head.value
        // и переносим a.head или b.head в конец result,
        // после чего переносим tail->next обратно
        // в a.head или b.head
    }
    // переносим оставшийся список в конец result
    return result;
}

auto mergesort(List &list) noexcept -> void {
    // Сортировка слиянием
    // 1. Определяем середину списка (см. ветку list-algo семинаров)
    ListElement *middle = nullptr;
    // 2. Переносим вторую половину в новый список
    List second;
    // second.head = std::move(middle->next);
    // 3. Для каждой половины запускаем mergesort
    // 4. Делаем merge от результатов,
    // не забыв std::move в аргументах,
    // присваивая результат в list
}
