#include <iostream>
#include "MemoryManager.h"
#include "Mem.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "Test.h"
#include <time.h>

int main() {

    Mem mem(10000000);
    mem.allocMem(10000000);
    Table table(mem);
    Test mytest{};
    int n=2000000;

        //Основные тесты

        cout << mytest.Test1insertelements(&table, n) << endl;

        cout << mytest.Test2removeallelements(&table, n) << endl;

        cout << mytest.Test3removechetniyelements(&table, n) << endl;

        cout << mytest.Test4removenechetniyelements(&table, n) << endl;

        cout << mytest.removeallbyiterator(&table, n) << endl;

        //Тесты на проверку остались ли элементы

        cout<<"\n"<<endl;

        cout << mytest.findEvenTable(&table,  n) << endl;

        cout << mytest.findOddTable(&table,  n) << endl;


    return 0;
}


