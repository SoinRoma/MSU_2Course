#pragma once
#include <string.h>
#include <stdlib.h>
#include <stdlib.h>
#include <stdio.h>
#include "ListAbstract.h"
#include "MemoryManager.h"

class List : public AbstractList {

    class Element{
        MemoryManager &_memory; //адрес выделенной памяти

    public:
        Element *next;  //указатель на следующий элемент
        size_t size; //размер нашего элемента
        void* value; //значение элемента

        Element(MemoryManager &mem, void* value, size_t elemSize);//конструктор
        ~Element(); //диструктор

    };
    size_t _size=0; //размер листа
    Element *_head= nullptr;  //начало списка
public:

    explicit List(MemoryManager &mem);
    ~List() override;

    size_t freeSpace;

class ListIterator: public Container::Iterator{  //итератор для листа
    public:
        Element *element= nullptr;

    explicit ListIterator( List::Element *elem);
        ~ListIterator();

        void *getElement(size_t &size) override;
        bool hasNext() override;
        void goToNext() override;
        bool equals(Iterator *right) override;
    };




    int size() override;
    void clear() override;
    bool empty() override;


    size_t max_bytes() override;
    Iterator *find(void *elem, size_t size) override;
    Iterator *newIterator() override;
    Iterator *begin() override;
    Iterator *end() override;
    void remove(Iterator *iter) override;

    int push_front(void *elem, size_t elemSize) override;
    void pop_front() override;
    void *front(size_t &size) override;
    int insert(Iterator *iter, void *elem, size_t elemSize) override;

};



