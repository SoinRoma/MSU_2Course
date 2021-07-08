#include "Table.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <cmath>
using namespace std;

//Функции итераторов

// Возвращает true, если есть следующий элемент, иначе false.
bool Table::TableIterator::hasNext() {
    int i;
    if (!listIter->hasNext())
    {
        for( i = position+1; i<hash_table->tSize;i++)
        {
            if(hash_table->_entries[i]!= nullptr)
            {
                return true;
            }
        }
        return false;
    }
    return false;
}

// Переход к следующему элементу.
void Table::TableIterator::goToNext() {
    int i;
    if(listIter->hasNext())
    {
        listIter->goToNext();
    }
    else
    {
        for(i = position+1;i<hash_table->tSize;i++)
        {
            if(hash_table->_entries[i] != nullptr)
            {
                position = 1;
                listIter = hash_table->_entries[i]->newIterator();
                break;
            }
        }
    }

}

// проверка на равенство итераторов
bool Table::TableIterator::equals(Container::Iterator *right) {

    if (listIter == nullptr || right == nullptr)
    { return false; }

    return listIter->equals(right);


}

// Возврашает явно указатель на элемент, на который указывает итератор в данный момент.
// Неявно возвращает размер данных
void *Table::TableIterator::getElement(size_t &size) {
    MyElement * tmp = (MyElement*)listIter->getElement(size);
    size = tmp->sizeValue;
    return tmp->value;

}

///////////////////////

// Функция возвращает значение, равное количеству элементов в контейнере.
int Table::size() {
    return conteinerSize;
}

// Если контейнер пуст возвращает true, иначе false
bool Table::empty() {
    return size() == 0;

}

// Функция возвращает значение, равное максимальной вместимости контейнера в байтах.
size_t Table::max_bytes() {
    return  tSize;
}

// Удаление всех элементов из контейнера.
void Table::clear()
{
    int i;
    if(_entries != nullptr)

    {
        for (i = 0; i< tSize; i++)
        {
            if(_entries[i] != nullptr)
            {
                _entries[i]->clear();
            }
        }
    }
    conteinerSize = 0;
    _entries = nullptr;
    free(_entries);
    _entries = nullptr;

}

////////////////////////////

Container::Iterator *Table::find(void *elem, size_t size) {
    int i, j;
    if(_entries != nullptr)
    {
        for(i = 0; i<tSize; i++)
        {
            if(_entries[i] != nullptr)
            {
                List::Iterator *iter;
                iter = _entries[i]->begin();
                for(j = 0; j< _entries[i]->size();j++)
                {
                    MyElement *tmp;
                    size_t sizeOfMyData;
                    tmp = (MyElement*)iter->getElement(sizeOfMyData);
                    if(size == tmp->sizeValue)
                    {
                        if(memcmp(&(tmp->value),&elem, size)==0)
                        {
                            TableIterator *iter2;
                            iter2 = new TableIterator(this, _entries[i], i, iter);
                            return iter2;
                        }
                    }
                    iter->goToNext();
                }
            }
        }
    }

    return nullptr;
}

Container::Iterator *Table::newIterator() {
    if(_entries != nullptr)
    {
        TableIterator *iter = new TableIterator(this,_entries[0], 0, nullptr);
        return  iter;
    }
    return nullptr;

}

Container::Iterator *Table::begin() {
    int i=0;
    if(_entries != nullptr)
    {
        for(i = 0; i< tSize; i++)
        {
            if(_entries[i] != nullptr)
            {
                TableIterator *iter = new TableIterator(this, _entries[i], i, nullptr);
                return iter;
            }
        }
    }
    return nullptr;
}

Container::Iterator *Table::end() {

    int i ;
    if(_entries != nullptr)
    {
        for( i = static_cast<int>(tSize - 1); i > 0; i--)
        {
            if(_entries[i] != nullptr)
            {
                List::Iterator *iter;
                iter = _entries[i]->end();
                return iter;
            }
        }
    }
    return nullptr;
}

/////////////////////////////

// Добавление элемента в контейнер, с сответствующим ключом.
int Table::insertByKey(void *key, size_t keySize, void *elem, size_t elemSize) {
    int position = static_cast<int>(hash_function(key, keySize)); // ищем позицию в таблице
    //функция size_t переводим в инт
    MyElement *newElement = new MyElement();  //создаем указатель на элемент
    newElement->value = elem;
    newElement->sizeValue = elemSize;

    memcpy(&(newElement->key), &key, keySize);
    newElement->sizeKey = keySize;

    if(_entries[position]== nullptr)  //если список пустой и память не выделена
    {
        _entries[position] = new List(*memory); //выделяю под список память
        _entries[position]->push_front(newElement, sizeof(newElement)); //кладу элемент
        conteinerSize++;
        return 0;
    }
    else  //если кто то стоит
    {
        List::Iterator *iterator;  //созд указатель на итератор
        size_t sizeOfMyData = 0;    //
        iterator = _entries[position]->begin();   //встаю на начало списка
        for(int i= 0; i < _entries[position]->size(); i++)    //иду по всем элементам
        {
            MyElement *tmp;
            tmp = (MyElement*)iterator->getElement(sizeOfMyData);  //получаю элемент
            if(tmp->sizeKey == keySize)
            {
                if(memcmp(&(tmp->key), &key, keySize)== 0)
                {
                    _entries[position]->insert(iterator, newElement, sizeof(newElement)); //если есть элемент с таким ключом то просто переписываем его значение
                    return 0;
                }
            }
            iterator->goToNext();
        }
        _entries[position]->push_front(newElement, sizeof(newElement));  //если такого элемента еще нет то вставляем
        conteinerSize++;
        return 0;
    }

}

// Удаление элемента с сответствующим ключом из контейнера.
void Table::removeByKey(void *key, size_t keySize) {
   /* int position = static_cast<int>(hash_function(key, keySize));
    if(_entries[position] != nullptr)
    {
        List::Iterator* iterator;
        iterator = _entries[position]->begin();
        for(int i = 0; i < _entries[position]->size(); i++)
        {
            size_t  sizeOfMyData;
            MyElement* tmp;
            tmp = (MyElement*)iterator->getElement(sizeOfMyData);
            if(tmp->sizeKey == keySize)
            {
                if(!memcmp(&(tmp->key), &key, keySize)) //нашли ключ
                {
                    _entries[position]->remove(iterator);//с этой позиции в списке удаляем
                    if(_entries[position]->empty()) //если список пустой
                    {
                        _entries[position] = nullptr; //обнуляем список
                    }
                    conteinerSize--;
                    break;
                }
            }
            iterator->goToNext();
        }
    }*/
    int hash = static_cast<int>(hash_function(key, keySize));
    List:: Iterator *iterator = (List:: Iterator*) _entries[hash]->begin();
    MyElement* tmp;
    size_t size;
    if (iterator)
    {
        while (iterator ->hasNext())
        {
            tmp = (MyElement*)iterator ->getElement(size);
            if(!memcmp(tmp ->key, key, keySize) && (keySize == tmp ->sizeKey))
            {
                _entries[hash]->remove(iterator);
                conteinerSize--;
                break;
            }
            else iterator ->goToNext();
        }
        if (!iterator -> hasNext())
        {
            tmp = (MyElement*)iterator->getElement(size);
            if(!memcmp(tmp ->key, key, keySize) && (keySize == tmp ->sizeKey))
            {
                _entries[hash]->remove(iterator);
                conteinerSize--;
            }
        }
    }
}

// Функция возвращает указатель на итератор, указывающий на найденный в контейнере элемент с сответствующим ключом.
// Если элемент не найден, возвращается нулевой указатель.
Container::Iterator *Table::findByKey(void *key, size_t keySize) {
    /*int position = static_cast<int>(hash_function(key, keySize));
    List::Iterator *iterator;
    iterator = _entries[position]->begin();
    MyElement* tmp; size_t sizeOfmyData;
    for(int i = 0; i < _entries[position]->size(); i++)
    {
        tmp = (MyElement*)iterator->getElement(sizeOfmyData);
        if(tmp->sizeKey == keySize)
        {
            if(memcmp(&(tmp->key), &key, keySize) == 0)
            {
                TableIterator *iterat =new  TableIterator(this, _entries[position], position, iterator);
                return iterat;
            }
        }
        iterator->goToNext();
    }
    return nullptr;*/

    int hash = hash_function(key, keySize);
    if (_entries[hash] != nullptr)
    {
        MyElement *tmp;
        size_t size;
        List::Iterator *iterator = (List::Iterator *) _entries[hash]->begin();
        if (!iterator) return NULL;
        while (iterator->hasNext()) {
            tmp = (MyElement *) iterator->getElement(size);
            if (!memcmp(tmp->key, key, keySize) && (tmp->sizeKey == keySize)) {
                TableIterator *iter = new TableIterator(this, _entries[hash], hash, iterator);
                return iter;
            } else iterator->goToNext();
        }
        if (iterator) {
            tmp = (MyElement *) iterator->getElement(size);
            if (!memcmp(tmp->key, key, keySize) && (tmp->sizeKey == keySize)) {
                TableIterator *iter = new TableIterator(this, _entries[hash], hash, iterator);
                return iter;
            }
        }
    }
    return nullptr;
}

// доступ к элементу с ключом key
void *Table::at(void *key, size_t keySize, size_t &valueSize) {
    int i;
    int position = static_cast<int>(hash_function(key, keySize));
    List::Iterator *iterator;
    iterator = _entries[position]->begin();
    MyElement* tmp; size_t sizeOfmyData;
    for (i = 0; i< _entries[position]->size(); i++)
    {
        tmp = (MyElement*)iterator->getElement(sizeOfmyData); //приведение в тип элемента
        if(tmp->sizeKey == keySize)
        {
            if(memcmp(&(tmp->key), &key, keySize) == 0)
            {
                valueSize = sizeOfmyData; //неявное возвращение
                return  tmp->value;
            }
        }
        iterator->goToNext();
    }
    return nullptr;

}

// хэш функция
size_t Table::hash_function(void *key, size_t keySize) {

    //http://vak.ru/doku.php/proj/hash/sources#rot13_hash_function

    // Хеш функия Алгоритм RC

    /*char*str = (char*)key;
    unsigned int b = 378551;
    unsigned int a = 63689;
    unsigned int hash = 0;
    for (int i = 0; i < keySize; i++)
    {
        hash = hash*a + (unsigned char)(*str);
        a = a*b;
    }

    return hash%tSize;
*/

// Хеш функия Алгоритм CRC-32
    auto b = static_cast<char *>(key);
    size_t h = ((size_t)b[0] & 0xFFu);
    //0xffu - это номер 255 в шестнадцатеричной нотации, определяемый как интерпретируемый как unsigned для компилятора.
    //these_MAX определяет, что это максимальное значение, которое может иметь тип данных до того, как произойдет переполнение.

    for (int i = 1; i < keySize; i++)
    { h |= ((size_t)b[i] & 0xFFu) << (i * 8u); }

    return h;



}


void Table::remove(Container::Iterator *iter) {
    TableIterator *itr = (TableIterator*)iter;
    List::Iterator* dItr;
    dItr = itr->listIter;
    _entries[itr->position]->remove(dItr);
    conteinerSize--;


}


















