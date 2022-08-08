#include "List.h"
#include <stdio.h>
#include <stdlib.h>

// Конструкторы и Деструкторы

List::Element::Element(MemoryManager &mem, void *value, size_t elemSize) : _memory(mem)   {

    this->value =new char[elemSize];
    memcpy(&(this->value),&value,elemSize);
    this->size=elemSize;
    this->next= nullptr;
}

List::Element::~Element() {
    _memory.freeMem(value);
    value = nullptr;
}

List::List(MemoryManager &mem) : AbstractList(mem){}

List::~List() {

    this->clear();
    this->_head->~Element();
}

List::ListIterator::ListIterator( List::Element *elem): element(elem) {}

List::ListIterator::~ListIterator()= default;

//////////////////////////////////////

// Возвращает true, если есть следующий элемент, иначе false.
bool List::ListIterator::hasNext() {
    //return element->next != nullptr;
    if (element->value && element->next) //если текущий указывает на след и в текущем есть что то то возвр 1
    {
        return true;
    }
    return false;
}

//переход к следующему элементу
void List::ListIterator::goToNext() {
    if (element != nullptr) // если следующий элемент есть
        element = element->next;
}

//проверка на равенство. //сравнивает на равенство мой элемент на котором стоишь и поданный номер элемента
bool List::ListIterator::equals(Container::Iterator *right) {
    size_t tmp;

    if (element != nullptr && right != nullptr)
    {
        if (memcmp(right->getElement(tmp), element->value, element->size) == 0)
          return true;
    }

    return false;
}

//возвращает значение элемента. но в тихую возвращает размер(неявно)
void *List::ListIterator::getElement(size_t &size) {
    if (element == nullptr)
    {
        size = 0;
        return nullptr;
    }

    size = element->size;
    return element->value;
}

//////////////////////////////////////////

//возвращает размер списка
int List::size() {
    return (int) _size;
}

// Если контейнер пуст возвращает true, иначе false
bool List::empty() {
    return size() == 0;
}

//Функция возвращает значение, равное максимальной вместимости контейнера в байтах.
size_t List::max_bytes() {
    return _memory.maxBytes();
}

//очистка  // Удаление элемента из начала контейнера.
void List::clear() {

    while (_head) { pop_front(); }
    _size = 0;

}

//////////////////////////////////////////////

//Создание итератора, соответствующего данному типу контейнера.
Container::Iterator *List::newIterator() {
    return new ListIterator(nullptr);
}

// Функция возвращает указатель на итератор, указывающий на первый элемент
// контейнера.
Container::Iterator *List::begin() {
    if (empty()) { return nullptr; }

    return new ListIterator(_head);
}

// Функция возвращает указатель на итератор, указывающий позицию за последним
// элементом контейнера.
Container::Iterator *List::end() {
    if (empty()) { return nullptr; }

    Container::Iterator *iter = begin();

    while (iter->hasNext()) { iter->goToNext(); }

    return iter;
}

// Функция возвращает указатель на итератор, указывающий на первый найденный
// в контейнере элемент.
Container::Iterator *List::find(void *elem, size_t size) {
    Container::Iterator *iter = begin();

    if (iter == nullptr) { return nullptr; }

    size_t tmp = 0;

    for(  Container::Iterator *iter = begin();!iter||!iter->hasNext();iter-> goToNext())

    {
        if (memcmp(iter->getElement(tmp), elem, size) == 0) { return iter; }
    }

    return nullptr;

}

// Удаление элемента из позиции, на которую указывает итератор iter.
// После удаления итератор указывает на следующий за удаленным элемент.
void List::remove(Container::Iterator *right) {
    if (empty()) { return; }
    ListIterator *iter = (ListIterator *) right;
    if (iter == nullptr) {
        return;
    }

    if (_head == iter->element) {
        pop_front();
        right->goToNext();
        return;
    }
}

// Функция явно возвращает указатель на элемент, находящийся в начале контейнера.
// и не явно возвращает размер данных
void *List::front(size_t &size) {
    if (_head == nullptr) {
        return nullptr;
    }

    size = _head->size;
    return _head->value;

}

//добавляет в начало списка элемент
int List::push_front(void *elem, size_t elemSize) {

    Element *el = new Element(_memory, elem, elemSize);    //создаю новый элемент
    el->next = this->_head;     //его следующим ставим бывший первый
    this->_head = el;       //первым ставим новый элемент
    this->_size++;    //количество элементов увеличиваем
    return 0;

}

//удаление элемента из списка
void List::pop_front() {
    if (empty()) { return; }

    Element *old = _head;
    _head = _head->next;
    _size--;

    delete old;

}

// Добавление элемента в позицию, на которую указывает итератор iter.
int List::insert(Iterator *iter, void *elem, size_t elemSize) {
    if(iter!= nullptr)
    {
        ListIterator *it;
        it=(ListIterator*)iter;
        if(it->element != nullptr)
        {
            it->element->value =elem;
            it->element->size = elemSize;
            return 0;
        }
        return 1;
    }
    return 1;



}



