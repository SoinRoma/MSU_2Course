#include "Table.h"
#include <time.h>
#pragma once
using namespace std;
class Test
{

private:
    int *elems;
    int **p_value;
public:


    double Test1insertelements(Table *table, int numOfElem);

    double Test2removeallelements(Table *table, int numOfElem);

    double Test3removechetniyelements(Table *table, int numOfElem);

    double Test4removenechetniyelements(Table *table, int numOfElem);

    double removeallbyiterator(Table *table, int numOfElem);

    char* findEvenTable(Table *table, int numOfElem);

    char* findOddTable(Table *table, int numOfElem);


};



