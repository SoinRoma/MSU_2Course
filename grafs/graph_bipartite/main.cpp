#include <iostream>
#include <vector>
using namespace std;


typedef struct SVertex{ //структура вершин и соседей
    int color;
    vector<SVertex*> sosed;
}SVertex;

int n; //глобальная переменная
bool bad= false;
int main()
{
    cout<<"Введите размер массива: ";
    cin>>n;
    int arr[n][n];          //таблица смежности
    SVertex vertexes[n];    //массив вершин
    int tm = 0;
    cout<<"Введите элементы массива(Вводите только 1 или 0): ";
    for (int i = 0; i < n; i++)
    {
        vertexes[i].color=0;
        cout<<"\n"; //заполняем массив Н Н
        for (int j = 0; j < n; j++){
            cin >> tm;
            if((tm!=0)&&(tm!=1))
            {
                cout<<"Ну просил же. Заканчиваем...";
                return 0;
            }
            arr[i][j] = tm;
            if(arr[i][j]==1) //если на пересечении стоит 1 говорим что соседи
            {
                vertexes[i].sosed.push_back(&(vertexes[j]));
            }
        }
    }

    int red;  //1
    int yellow;  //2
    for(int i=0; i<n; i++)
    {
        red=0; yellow=0;
        if (vertexes[i].color == 0)  //если не окрашена то ставим 1
        {
            for (int j = 0; j < vertexes[i].sosed.size(); j++)
            {
                if(vertexes[i].sosed[j]->color==1)
                {
                    //если хоть один сосед красный
                    red = 1;
                }
                if(vertexes[i].sosed[j]->color==2)
                {
                    //если хоть один сосед желтый
                    yellow = 1;
                }
            }
            if((red==0)&&(yellow==0))
            {
                //если никто не красный и не желтый то красим вершину в кравсный, а соседе   в желтый
                vertexes[i].color=1;
                for(int k=0; k<vertexes[i].sosed.size(); k++)
                {
                    vertexes[i].sosed[k]->color=2;
                }
            }
            if((red==1)&&(yellow==0))   //если вокруг есть хоть одна красная то красим вершину в желтый
            {
                vertexes[i].color=2;
                for(int k=0; k<vertexes[i].sosed.size(); k++)
                {
                    vertexes[i].sosed[k]->color=1;
                }
            }
            if((red==0)&&(yellow==1))   //если вокруг есть желтая вершина то красим ее в красный
            {
                vertexes[i].color=1;
                for(int k=0; k<vertexes[i].sosed.size(); k++)
                {
                    vertexes[i].sosed[k]->color=2;
                }
            }
            if((red==1)&&(yellow==1))   //если вокруг есть и красная и желтая вершины то ГГВП
            {
                cout << "Не выйдет. Не получилось поставить цвета" << endl;
                bad= true;
                break;

            }
        }


        if (vertexes[i].color == 1)  //если вершина окрашена уже то пойдем окрашивать соседей
        {
            //    bad = dfs( i, 1, vertexes[i]);
            for (int j = 0; j < vertexes[i].sosed.size(); j++) { //идем по соседям (помни вершина красная)
                if(vertexes[i].sosed[j]->color==1)
                {
                    red = 1;
                }
                if(vertexes[i].sosed[j]->color==2)
                {
                    yellow = 1;
                }
            }
            if((red==0)&&(yellow==0))  //если все чистые красим соседей в желтый цвет
            {
                for(int k=0; k<vertexes[i].sosed.size(); k++)
                {
                    vertexes[i].sosed[k]->color=2;
                }
            }
            if((red==1)&&(yellow==0))  //если сосед вышел красным то ГГВП вершина то у нас красная
            {
                cout << "Вышло так, что сосед такого же цвета что и вершина. Ошибка" << endl;
                bad=true;
                break;

            }
            if((red==0)&&(yellow==1)) //если хоть один сосед желтый то красим остальных соседей в желтый
            {
                for(int k=0; k<vertexes[i].sosed.size(); k++)
                {
                    vertexes[i].sosed[k]->color=2;
                }
            }
            if((red==1)&&(yellow==1))//если соседи и красный и желтые то это ошибка
            {
                cout << "Не выйдет. Не получилось поставить цвета" << endl;
                bad=true;
                break;
            }
        }

        if (vertexes[i].color == 2)  //если вершина окрашена уже то пойдем окрашивать соседей
        {
            //    bad = dfs( i, 1, vertexes[i]);
            for (int j = 0; j < vertexes[i].sosed.size(); j++) { //идем по соседям (помни вершина желтая)
                if(vertexes[i].sosed[j]->color==1)
                {
                    red = 1;
                }
                if(vertexes[i].sosed[j]->color==2)
                {
                    yellow = 1;
                }
            }
            if((red==0)&&(yellow==0))  //если все чистые красим соседей в красный цвет
            {
                for(int k=0; k<vertexes[i].sosed.size(); k++)
                {
                    vertexes[i].sosed[k]->color=1;
                }
            }
            if((red==1)&&(yellow==0))  //если сосед вышел красным то красим остальных соседей в красный
            {
                for(int k=0; k<vertexes[i].sosed.size(); k++)
                {
                    vertexes[i].sosed[k]->color=1;
                }
            }
            if((red==0)&&(yellow==1)) //если хоть один сосед желтый то это ошибка
            {
                cout << "Вышло так, что сосед такого же цвета что и вершина. Ошибка" << endl;
                bad=true;
                break;

            }
            if((red==1)&&(yellow==1))//если соседи и красный и желтые то это ошибка
            {
                cout << "Не выйдет. Не получилось поставить цвета" << endl;
                bad=true;
                break;
            }
        }

    }
    if(bad!=true)
    {
        cout << "ВЫШЛО!" << endl;
    }//получилось
    return 0;
}



/*
 6
 0 0 0 1 1 1
 0 0 0 1 1 1
 0 0 0 1 1 1
 1 1 1 0 0 0
 1 1 1 0 0 0
 1 1 1 0 0 0
 для К,33 двудольный
 */

 //3
// 0 1 1
// 1 0 1
// 1 1 0
// для К3 не двудоьный



