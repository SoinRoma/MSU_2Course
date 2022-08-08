#include "Test.h"
#include <iostream>
#include <ctime>

//Основные тесты

double Test::Test1insertelements(Table *table, int numOfElem) {
    elems = (int*)malloc(numOfElem*sizeof(int));
    p_value = (int**)malloc(numOfElem*sizeof(int*));
    for (int i = 0; i < numOfElem; i++) {
        elems[i] = i;
        p_value[i] = &(elems[i]);
    }
    clock_t start = clock();

    for (int i = 0; i <numOfElem; i++) {
        table->insertByKey(p_value[i], sizeof(p_value[i]), p_value[i], sizeof(p_value[i]));
    }
    clock_t end = clock();
    cout << "Created all the elements in : ";
    return (double)(end - start) / CLOCKS_PER_SEC;

}

double Test::Test2removeallelements(Table *table, int numOfElem){

    clock_t start2 = clock();
    for (int i = 0; i < numOfElem; i++) {
        table->removeByKey(p_value[i], sizeof(p_value[i]));
    }
    clock_t end2 = clock();
    cout << "Removed all elements in : ";
    return (double)(end2 - start2) / CLOCKS_PER_SEC;

}

double Test::Test3removechetniyelements(Table *table, int numOfElem){

    clock_t start = clock();
    for (int i = 0; i < numOfElem; i++) {
        if (i % 2 == 0) {
            table->removeByKey(p_value[i], sizeof(p_value[i]));
        }
    }
    clock_t end = clock();
    cout << "Removed even elements in : ";
    return (double)(end - start) / CLOCKS_PER_SEC;

}

double Test::Test4removenechetniyelements(Table *table, int numOfElem){

    clock_t start = clock();
    for (int i = 0; i < numOfElem; i++) {
        if (i % 2 != 0) {
            table->removeByKey(p_value[i], sizeof(p_value[i]));
        }
    }
    clock_t end = clock();
    cout << "Removed odd elements in :  ";
    return (double)(end - start) / CLOCKS_PER_SEC;

}

double Test::removeallbyiterator(Table *table, int numOfElem){

    Table::Iterator *it;
    it = table->begin();
    clock_t start2 = clock();
    for (int i = 0; i < numOfElem; i++) {
        table->remove(it);
    }
    clock_t end2 = clock();
    cout << "Removed elements by iterator in : ";
    return (double)(end2 - start2) / CLOCKS_PER_SEC;
}


//Тесты на проверку остались ли элементы

char * Test::findEvenTable(Table * table, int numOfElem){

    int i;
    for ( i = 0; i < numOfElem; i++)
    {
        if (i % 2 == 0)
        {
           if (table->findByKey(p_value[i], sizeof(p_value[i])) != nullptr)
           {
               void * this_num;

               size_t size;
               this_num = table->at(p_value[i], sizeof(p_value[i]), size);
                //cout << *(int*)this_num << endl;
                return const_cast<char *>("Error! even elements found!");
            }
        }
    }
   return const_cast<char *>("Don't found even elements!");
}

char * Test::findOddTable(Table * table, int numOfElem){

    for (int i = 0; i < numOfElem; i++)
    {
        if (i % 2 != 0)
        {
            if (table->findByKey(p_value[i], sizeof(p_value[i])) != nullptr)
            {
                void * this_num;
                size_t size;
                this_num = table->at(p_value[i], sizeof(p_value[i]), size);
                //cout << *(int*)this_num << endl;
                return const_cast<char *>("Error! odd elements found!");
            }
        }
    }
    return const_cast<char *>("Don't found odd elements!");
}



