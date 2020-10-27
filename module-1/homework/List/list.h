#pragma once
#include <cstddef>
#include <iostream>

namespace task {

    class list {

    public:

        int length;

        class iterator {
        public:
            int value;
            iterator* next, * prev;

            iterator();
            iterator(int value);

            int& operator*();
        };

        list();
        list(size_t count, const int& value = int());
        list(const list& other);

        ~list();
        list& operator=(const list& other);


        int& front();
        const int& front() const;
        iterator& front_iter();
        const iterator& front_iter() const;

        int& back();
        const int& back() const;
        iterator& back_iter();
        const iterator& back_iter() const;


        bool empty() const;
        size_t size() const;
        void clear();


        void push_back(const int& value);
        void pop_back();
        void push_front(const int& value);
        void pop_front();
        void resize(size_t count);
        void swap(list& other);


        void remove(const int& value);
        void unique();
        void sort();

        friend std::ostream& operator<<(std::ostream& out, const list lst);

        iterator* first, * last;

    };

}  // namespace task