#include "list.h"
#include <iostream>

task::list::iterator::iterator() {
    value = 0;
    next = prev = nullptr;
}

task::list::iterator::iterator(int value) {
    this->value = value;
    next = prev = nullptr;
}

int& task::list::iterator::operator*() {
    return value;
}

task::list::list() {
    length = 0;
    first = nullptr;
    last = new iterator();
}

task::list::list(size_t count, const int& value) {
    if (count == 0) {
        list();
        return;
    }
    first = new iterator(value);
    iterator* prev = first;
    for (size_t i = 1; i < count; i++) {
        iterator* current = new iterator(value);
        current->prev = prev;
        prev->next = current;
        prev = current;
    }
    last = new iterator();
    last->prev = prev;
    prev->next = last;
    length = count;
}

task::list::list(const list& other) {   
    length = 0;
    first = nullptr;
    last = new iterator();
    *this = other;
}

task::list::~list() {
    while (last != nullptr) {
        iterator* prev = last->prev;
        delete last;
        last = prev;
    }
}

task::list& task::list::operator=(const list& other) {   
    if (this == &other) {
        return *this;
    }
    clear();
    const iterator* cur = &other.back_iter();
    cur = cur->prev;
    while (cur != nullptr) {
        push_front(cur->value);
        cur = cur->prev;
    }
    return *this;
}

int& task::list::front() {
    return first->value;
}

const int& task::list::front() const {
    return first->value;
}

task::list::iterator& task::list::front_iter() {
    return *first;
}

const task::list::iterator& task::list::front_iter() const {
    return *first;
}

int& task::list::back() {
    return last->prev->value;
}

const int& task::list::back() const {
    return last->prev->value;
}

task::list::iterator& task::list::back_iter() {
    return *last;
}

const task::list::iterator& task::list::back_iter() const {
    return *last;
}

bool task::list::empty() const {
    return length == 0;
}

size_t task::list::size() const {
    return length;
}


void task::list::clear() {
    while (last!=nullptr) {
        iterator* prev = last->prev;
        delete last;
        last = prev;
    }
    first = nullptr;
    last = new iterator;
    length = 0;
}

void task::list::push_back(const int& value) {
    iterator* iter = new iterator(value);
    if (last->prev != nullptr) {
        last->prev->next = iter;
    }
    else {
        first = iter;
    }
    iter->prev = last->prev;
    iter->next = last;
    last->prev = iter;
    length++;
}

void task::list::pop_back() {
    iterator* prev = last->prev->prev;
    delete last->prev;
    if (prev != nullptr) {
        prev->next = last;
    }
    else {
        first = nullptr;
    }
    last->prev = prev;
    length--;
}

void task::list::push_front(const int& value) {   
    if (first == nullptr) {
        first = new iterator(value);
        first->next = last;
        last->prev = first;
        length++;
        return;
    }
    iterator* iter = new iterator(value);
    iter->next = first;
    first->prev = iter;
    first = first->prev;
    length++;
}

void task::list::pop_front() {   
    first = first->next;
    delete first->prev;
    first->prev = nullptr;
    length--;
}

void task::list::resize(size_t count) {
    if (length >= count) {
        for (int i = 0; i < length - count; i++) {
            pop_back();
        }
    }
    else {
        for (int i = 0; length < count; i++) {
            push_back(0);
        }
    }
}

void task::list::swap(list& other) {
    std::swap(first, other.first);
    std::swap(last, other.last);
    std::swap(length, other.length);
}

void task::list::remove(const int& value) {
    int delete_value = value;
    iterator* cur = last->prev, * tmp;
    while (cur != nullptr) {
        if (cur->value == delete_value) {
            cur->next->prev = cur->prev;
            if (cur->prev != nullptr) {
                cur->prev->next = cur->next;
            }
            else if (length != 1){
                first = cur->next;
            }
            else {
                first = nullptr;
            }
            tmp = cur->prev;
            delete cur;
            cur = tmp;
            length--;
        }
        else {
            cur = cur->prev;
        }
    }
}

void task::list::unique() {
    iterator* cur = last->prev, * tmp;
    while (cur != nullptr && cur->prev != nullptr) {
        if (cur->value == cur->prev->value) {
            cur->next->prev = cur->prev;
            cur->prev->next = cur->next;
            tmp = cur->prev;
            delete cur;
            cur = tmp;
            length--;
        }
        else {
            cur = cur->prev;
        }
    }
}

void task::list::sort() {
    for (int i = 0; i < length - 1; i++) {
        iterator* cur = last->prev;
        while (cur != nullptr && cur->prev != nullptr) {
            if (cur->prev->value > cur->value) {
                std::swap(cur->value, cur->prev->value);
            }
            cur = cur->prev;
        }
    }
}
