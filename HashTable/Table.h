#include "TableAbstract.h"
#include "MemoryManager.h"
#include "List.h"
#include "Mem.h"

class Table: public AbstractTable {
private:

    size_t tSize; //размер таблицы
    size_t conteinerSize; // количество всех элементов

    //std::vector<List *> _entries;  //массив списков

    List** _entries;
    MemoryManager *memory;

    class MyElement      //класс для данных с ключем и значением
    {
    public:
        void *key;   //указатель на ключ
        void *value; //указатель на значение
        size_t  sizeKey;  //размер ключа
        size_t  sizeValue;//размер значения
    };

public:
    Table(MemoryManager &mem): AbstractTable(mem) {
        tSize = mem.size();
        _entries = (List**)malloc(tSize*sizeof(List*)); //создаю массив указателей на списки
        memory = &mem;
        for(int i = 0; i <tSize; i++)
        {
            _entries[i]= 0;   //конструктор инициализация нулями
        }
        conteinerSize = 0; // размер контейнера = 0

    }

    int insertByKey(void *key, size_t keySize, void *elem, size_t elemSize);
    void removeByKey(void *key, size_t keySize);
    void* at(void *key, size_t keySize, size_t &valueSize);
    size_t hash_function(void *key, size_t keySize);

    int size();
    void clear();
    bool empty();
    size_t max_bytes();

    Iterator* findByKey(void *key, size_t keySize);


    class TableIterator: public Container::Iterator
    {
    public:
        Table *hash_table;  //указатель на таблицу
        List *nowList; //указатель на текущий список
        List::Iterator *listIter;  //указатель на итератор списка
        int position;

        TableIterator(Table *ttable2, List *thisList, int posit, List::Iterator *myiterator) :hash_table(ttable2),nowList(thisList)
        {
            if(myiterator != NULL)
            {
                listIter = myiterator;
            }
            else
            {
                listIter = nowList->newIterator();
                position=posit;
            }

        }

        bool hasNext();
        void goToNext();
        bool equals(Container::Iterator *right);
        void* getElement(size_t &size);

    };

    Container::Iterator* find(void *elem, size_t size); // not implemented
    Container::Iterator* end();
    Container::Iterator* begin();
    Container::Iterator* newIterator();
    void remove (Container::Iterator *iter);

};


