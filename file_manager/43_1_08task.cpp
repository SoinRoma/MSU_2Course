#include <string>
#include <stdio.h>
#include <vector>
#include "os_file.h"
#include <iostream>
#include <string.h>
#include <algorithm>
using namespace std;

typedef struct SFile //создаем структуру для элемента дерева. Элемент это или папка или файл
{
    bool DirOrFile;    // проверяем это папка или файл (1-папка 0-файл)
    string name;  //имя папки или файла
    int SizeFile; // переменная для определения размера файла.  Не путать с size()
    SFile* parent;  //указатель на родителя
    vector<SFile*> children;  //векторный массив детей
}SFile;

SFile *root = NULL; //В структуре создаём корень(самая верхняя папка) указатель на корень
SFile *currentDirectory; //наш путь где мы находимся
int free_space = 0;  //создаем переменную для хранения информации о выделенном нам свободном месте

typedef struct SForCopy //отдельная структура для копи
{
    int count;   //счётчик файлов
    int newsize;  //кол-во места нужное после копирования
}SForCopy;
//=============================================================================

int my_create(int disk_size) //функция для создания Файлового Менеджера
{

    //Если файловый манаджер уже создан, то при попытке создать его еще раз выводим ошибку
    if(root!=NULL)
        return 0;

    else
    {
        if (disk_size <= 0)  //проверка на дурака(если диск меньше нуля)
            return 0;
        else
        {
            root = new SFile;  //выделение памяти для корня
            root->name = "/"; //изначальное имя у корня
            free_space = disk_size; //Свободное место на диске
            root->DirOrFile = true;   //мы говорим что корень это папка
            root->SizeFile = 0;   // изначально размер у корня 0 нет детей
            currentDirectory = root;    //путь изначально равер самому корню т,е текущий путь равен самому корню
            return 1;
        }
    }
}

//=============================================================================

void destroy_children(SFile* directory)  //Функция для уничтожения Внутрених папок и файлов
{
    if(directory == currentDirectory)      //если полученный корень одинаков с текущей дирректорией
        currentDirectory = root;           //текущая дирректория и есть руут

    for (int i=0; i<directory->children.size(); i++)  //идем по массиву всех детей
    {
        if(directory->children[i]->DirOrFile)  //проверяем в директориии ребенка это папка или файл. если папка то ныряем глубже
            destroy_children(directory->children[i]);
        else // если это файл то мы его освобождаем
            free_space+=directory->children[i]->SizeFile;
    }
    delete directory;
}

int my_destroy() //Функция для разрушения Файлового Менеджера
{
    if (root!=NULL)   //если создан, то мы вызываем функцию для удаления папок и файлов внутри
    {
        destroy_children(root);
        root=NULL;
        return 1;
    }

    else   //если не создан, то и убивать нечего
        return 0;

}

//=============================================================================
//*****************************************************************************
//=============================================================================

vector<string> parsingFunction (string dirName)
{
    //Эта функция в новый массив запихивает разбитое имя пути без \
    //используется в my_create_dir в my_create_file в my_create_file

    vector<string> ParsedArray;  //будущий массив с разбитым путем на части
    string tempForString;        //Временная переменная для поиска имени папки
    int j = 0;                   //счетчик для абсолютного или относительного пути

    if(dirName[0]=='/')          //проверка на наличие в данном нам пути первого /
        j = 1;                   //если абсолютный путь, то начнем проверку со второго элемента

    for(int i = j; i < dirName.size(); i++)   //проходим по всему данному пути
    {
        if((dirName[i] <= 57 && dirName[i] >= 46)  || (dirName[i] <= 90 && dirName[i] >= 65) || (dirName[i] <= 122 && dirName[i] >= 97) || dirName[i]==95)
            //проверка всего пути на область допустимых символов по ASCI коду
        {
            if(dirName[i]=='/')  //если встретим /
            {
                if(tempForString.empty())    //и если темп пустой               /  ABC/d1/d2
                {
                    ParsedArray[0]="Fail";
                    return ParsedArray;
                    //то данный нам путь не верный в пути есть 2 //
                }
                else
                {
                    ParsedArray.push_back(tempForString); //?
                    //в нашу внутреннюю переменную стринг пихаем темп если встретили / и темп!=""
                    tempForString=""; //зануляем темп для дальнейшего поиска слов
                }
            }
            else  //если не / то в темп пихаем букву
            {
                tempForString+=dirName[i];
            }
        }
        else
        {
            ParsedArray[0]="Fail";
            return ParsedArray;
            //если встретили символ вне области допуска то возвращаем ошибку
        }
    }
    if(!tempForString.empty())  //мы закончили проходить по всему пути, но в конце не встретили / и темп оказался !=""
        ParsedArray.push_back(tempForString); //то это последняя папка в пути и мы ее добавляем в нашу временную переменную
    return ParsedArray; //возвращаем весь путь в виде массива без /
}
//=============================================================================

SFile * findDirFunction(int absolute, vector<string> way)  //мы получаем флаг абсолютный ли путь или нет и путь
{   //Находит директорию Только по папкам Ходит по всему дереву И ищет тот путь что ты ей дал
    //используется в me_create_dir  в me_create_file

    int found;  //флажок - найден
    SFile* temp;     // создаем указательль на структуру now = сейчас

    if (absolute == 1)  //Если абсолютный путь то структура now будет корнем
        temp = root;

    else              //иначе приравниваем к текущему
        temp = currentDirectory;

    for(int i = 0; i < way.size(); i++)   //пока i меньше чем колиство элементов в массиве
    {
        if (way[i] == "..")   //если в пути есть ..  то поднимаемся на верх и продолжаем
        {
            temp = temp->parent;
            continue;
        }
        if (way[i] == ".")   //если путь путь начинается с . то продолжаем от сюда
        {
            continue;
        }
        found = -1;    //переменная типа найден
        for(int j=0; j < temp->children.size(); j++) //прогоняем проверку по всем детям
        {
            if (temp->children[j]->DirOrFile == true && temp->children[j]->name == way[i])  //есди ребенок-папка и его имя совпадает
            {
                found = j;   //ставим флажок и выходим
            }
        }
        if(found== -1)   //если не нашли ничего возвращаем 0
        {
            return NULL;
        }
        else
        {
            temp = temp->children[found];  //то ныряем в него и проверяем дальше
        }
    }
    return temp;
}
//=============================================================================

SFile* findDirforChangeDir(bool isAbsolute, vector<string> parsedPath)//Вспомогательная функция поиска пути
{//используется в my_change_dir
    SFile* temp;

    if(isAbsolute)
        temp = root;   //если абсолютный путь то  начнем строить с корня

    else
        temp = currentDirectory;        //если нет, то начнем строить с текущей дирректории

    for(int i = 0; i < parsedPath.size(); i++)
    {
        if(parsedPath[i] == ".")
        {
            continue;
        }
        if(parsedPath[i] == "..")
        {
            temp = temp -> parent;
            continue;
        }

        int found = -1;   //ставим флаг

        for(int j = 0; j < temp->children.size(); j++)    //проходим по всем детям
        {
            if(temp->children[j]->name == parsedPath[i] && (temp->children[j]->DirOrFile == 1))  //если имя ребенка совпадает с элементом [i]
                //и этот ребенок папка
            {
                found = j; //то флаг равен j
            }
            if(temp->children[j]->name == parsedPath[i] && (temp->children[j]->DirOrFile == 0) && i == parsedPath.size()-1)
                //если им ребенка совпадает с элементом [i] массива и это файл и это последний элемент массива
            {
                found = j; //то флаг равен j
            }
        }

        if(found == -1)
            return NULL;

        else
            temp = temp -> children[found];//ныряем имеено в ребенка под индексом j
    }
    return temp;
}
//=============================================================================

string getDirectory(SFile* temp)  //функция собирающая путь из текущей дирректории и возвращающая строку       /ABC/d1/d2
{
    if(root==NULL) //если файловый манаджер не создан то и решать нечего
        return "";

    if (temp == root)        //если данная нам структура равна корню
    {
        string pathForRoot = "/";   //то возвращаем просто /
        return pathForRoot;
    }

    vector <string>  path;       //создаем переменную path

    while (temp->name != "/")      //пока в структуре не встретится / то есть корень
    {
        path.push_back(temp->name); //в массив слов запихиваем имена    d2  /  d1  /  ABC  /
        path.push_back("/");   //за ними /
        temp=temp->parent;    //ныряем в родителя
    }//мы получили массив слов собраный нашему пути

    reverse(path.begin(), path.end());  //инвертируем массив
    string pathString;       //переменная для сбора пути

    for(int i = 0; i < path.size(); i++)
        pathString += path[i];
    return pathString;
}
//=============================================================================
//*****************************************************************************
//=============================================================================

int my_create_dir(const char* dir_name) // Создает директорию с указанным именем.
{ // В качестве аргумента принимает абсолютный или относительный путь

    if(root == NULL)
        return 0;

    else
    {
        string dirName = dir_name; //мы создали переменную стринг для пути который нам дали
        SFile* temp;  //эта структура будет нашим путем до файла/или папки
        vector<string> parsedPath = parsingFunction(dirName); //мы создали массив путей равных функции
        // которая понимает и разбивает данный нам путь на папки и файлы с поиском /

        if(parsedPath[0]== "Fail")//если в пути есть не допустимые символы или путь не верно построен то возвращаем ошибку
            return 0;

        dirName = parsedPath[parsedPath.size()-1]; //переменной dirName присваиваем последний элемент из массива пути сохраняем его

        if(dirName == "." || dirName == ".." || dirName == "/")//последний элемент не может быть .  ..  /
        {
            return 0;
        }

        parsedPath.pop_back();    //из массива удаляем последний элемаент

        if(dir_name[0] == '/') //если данный путь начинается с / то запускаем функцию findDir (1. way)
        {
            temp = findDirFunction(1, parsedPath);
        }

        else  //если данный путь не начинается с / то запускаем функцию findDir (0. way)
        {
            temp = findDirFunction(0, parsedPath);
        }

        if(temp==NULL)
        {
            return 0;
        }

        for(int i = 0; i < temp->children.size(); i++) //Он должен давать 0, потому что в папке dir2 уже есть файл с именем file1
            if(temp->children[i]->name == dirName)  //Они пытаются создать папку с таким же именем, это не допускается
                return 0;

        SFile* newCreateDir = new SFile; //создаем новую папку
        newCreateDir->DirOrFile = true;         //мы говорим что newCreateDir это папка
        newCreateDir->name = dirName;        //присваиваем ему имя которое сохранили
        newCreateDir->SizeFile = 0;      //внутри этой папки пусто поэтому 0
        newCreateDir->parent = temp;       //нашли ему отца из того пути что был дан
        temp->children.push_back(newCreateDir);  //сказали отцу что у него есть ребенок
        return 1;
    }
}
//=============================================================================

int my_create_file(const char* file_name, int file_size) // Создает файл с указанным именем и размером.
{ // Создание файла возможно только внутри уже существующей директории

    if(root == NULL)
        return 0;

    else
    {
        if(free_space<file_size)
        {
            return 0;
        }
        string fileName = file_name; //мы создали переменную стринг для пути который нам дали
        SFile* temp;
        //создаем строковый массив, который будет состоять из имен папок и файлов
        //т.е.   /ABC/d1/d2   - dirName
        //       parsedPath[0] = ABC     parsedPath[1] = d1     parsedPath[2] = d2
        vector<string> parsedPath = parsingFunction(fileName);
        //если в пути есть не допустимые символы или путь не верно построен то возвращаем ошибку
        //причины "Fail" смотреть в самой функции parsingFunction
        if(parsedPath[0]== "Fail")
        {
            return 0;
        }

        fileName = parsedPath[parsedPath.size()-1]; //переменной dirName присваиваем последний элемент из массива пути сохраняем его

        if(fileName == "." || fileName == ".." || fileName == "/")//последний элемент не может быть .  ..  /
        {
            return 0;
        }

        parsedPath.pop_back(); //из массива удаляем последний элемаент

        if(file_name[0] == '/') //если данный путь начинается с / то запускаем функцию findDir (1. way)
        {
            temp = findDirFunction(1, parsedPath);
        }

        else  //если данный путь не начинается с / то запускаем функцию findDir (0. way)
        {
            temp = findDirFunction(0, parsedPath);
        }

        if(temp==NULL)
        {
            return 0;
        }

        for(int i=0; i<temp->children.size(); i++)  //проверка есть у темпа дети с такими же именами
        {
            if(temp->children[i]->name==fileName)
            {
                return 0;
            }
        }
        SFile* newCreateFile = new SFile; //создаем новую папку
        newCreateFile->DirOrFile = false;         //мы говорим что newCreateDir это папка
        newCreateFile->name = fileName;        //присваиваем ему имя которое сохранили
        newCreateFile->SizeFile = file_size;      //внутри этой папки пусто поэтому 0
        newCreateFile->parent = temp;       //нашли ему отца из того пути что был дан
        temp->children.push_back(newCreateFile);  //сказали отцу что у него есть ребенок
        free_space-=file_size;    //заполняем место на диске
        return 1;
    }
}
//=============================================================================

int my_remove(const char* name, int recursive) // Удаляет файл или директорию с указанным именем.
{
    // Если указана непустая директория и флаг recursive равен 0, то директория не удаляется и выдается ошибка.
    // Если указана директория и флаг recursive равен 1, то директория удаляется вместе со всем ее содержимым.
    // Если получилось так, что текущая директория была удалена - текущей становится корневая директория.

    string  dirName (name);   //записываем в строку путь
    vector<string> parsedPath = parsingFunction(dirName);  //разбиваем путь на массив с именами
    string lastName = parsedPath.back(); //записываем в строку последнее имя
    parsedPath.pop_back(); //удаляем из массива последний элемент
    SFile* temp; //создаем временную структуру

    if(dirName[0]=='/')
        temp = findDirforChangeDir(true , parsedPath);

    else
        temp = findDirforChangeDir(false , parsedPath);   //переходим к текщей дирректории

    if(parsedPath.size()==0 && lastName == ".")//если массив оказался пустым и сохраненное имя- точка,то темп=карент
    {
        temp = currentDirectory;
        lastName = currentDirectory->name;
    }

    if(temp==NULL)
        return 0;

    vector <SFile*> :: iterator iterator1 = temp->children.begin();
    //берем переменную iterator1 это счетчик среди всех детей

    while(iterator1 != temp->children.end())      //пока итератор не равен последнему номеру
    { //если имя элемента под этим номером = iterator равен нашему последнему имени lastName
        if ((*iterator1)->name == lastName) //если имя ребенка под этим итератором= тому что ищем, то выйдем
        {
            break;
        }

        else
        {
            iterator1++;  //если не совпадает то идем дальше по номерам
        }
    }

    if(iterator1 == temp->children.end())  //если все таки дойдем до конца то такого файла или папки нету
        return 0;

    if(!(*iterator1)->DirOrFile)  //если же мы нашли ребенка под этим номером является файлом
    {
        free_space+= (*iterator1)->SizeFile;   //возвращаем свободное место
        delete((*iterator1));                  //удаляем этот элемент
        temp->children.erase(iterator1++);     //
        return 1;
    }

    //если элемент под номером пустой или равен корю то вывести ошибку
    if((*iterator1) == NULL || (*iterator1) == root)
        return 0;

    //если внутри ребенка есть еще дети или данный флажок = 0 то вывести ошибку
    if((*iterator1)->children.size() > 0 && !recursive)
        return 0;

    destroy_children(*iterator1); //запускаем функцию убийства детей
    temp->children.erase(iterator1++);  //удаляем ребенка
    return 1;
}
//=============================================================================

int my_change_dir(const char* path) // Меняет текущую директорию
{ // В качестве аргумента принимает абсолютный или относительный путь новой текущей директории

    if(root == NULL)
        return 0;

    else
    {
        string givenpath(path);
        vector<string> parsedPath = parsingFunction(givenpath); //мы создали массив имен в порядке нашего пути
        SFile *temp;
        if (givenpath[0] == '/')
        {
            temp = findDirforChangeDir(1, parsedPath);  //отдаем функции знак что у нас абсолютный путь и массив
        }
        else
        {
            temp = findDirforChangeDir(0, parsedPath);  //отдаем функции знак что у нас относительный путь и массив
        }
        if(temp==NULL)
        {
            return 0;
        }
        currentDirectory = temp;  //если вышло то текущий теперь это наш темп
        return 1;
    }
}
//=============================================================================

void my_get_cur_dir(char *dst)    // Возвращает полный путь текущей директории (кладет в буфер dst)
{
    if(root == NULL)    //если манаджер не создан то возвращаем пустоту
    {
        string pathString = "";
        strcpy(dst, pathString.c_str());
        return ;
    }

    string pathString = getDirectory(currentDirectory);   //собираем строку из всех имен в текущей дирректории
    strcpy(dst, pathString.c_str());  //записываем в dst строку без нуля
}
//=============================================================================

SForCopy SizeandCount(SFile* temp)
{
    SForCopy tempForTwo; //временная под два значения (счётчик ко-ва файлов и счётчик размера)
    tempForTwo.newsize=0;  //изначально по нулям
    tempForTwo.count=0;

    for(int i=0;i<temp->children.size();i++)
    {
        if((temp->children[i]->DirOrFile)&&(!temp->children[i]->children.empty())) //если папка то опускаемся глубже
        {
            temp=temp->children[i];
        }
        else //если файл
        {
            if(!temp->children[i]->DirOrFile)
            {
            tempForTwo.count++;
            tempForTwo.newsize=tempForTwo.newsize+temp->children[i]->SizeFile;  //размер равен сумме размеров всех файлов внутри
            }
        }
    }
    return tempForTwo;
}

void RecursiyaforCopy(SFile* Dir, SFile* temp) //рекурсия для создания наших шариков
{
    for(int i=0;i<temp->children.size(); i++)
    {
        SFile *NewDir = new SFile;
        NewDir->name=temp->children[i]->name;
        NewDir->DirOrFile=temp->children[i]->DirOrFile;
        NewDir->SizeFile=temp->children[i]->SizeFile;
        NewDir->parent = Dir;
        Dir->children.push_back(NewDir);
        if(temp->children[i]->DirOrFile && (!temp->children[i]->children.empty()))
        //проверяем у ребенка папка он или нет и у него должны быть не пустые дети
            RecursiyaforCopy(Dir->children[i], temp->children[i]);
    }
}
int my_copy(const char *old_path, const char *new_path)  // Копирует файл или директорию в другое место.
{
    // При попытке скопировать файл или каталог в самого себя должен выдавать ошибку (-1)
    // При попытке скопировать в файл или несуществующую директорию выдавать ошибку

    if(root == NULL)
        return 0;

    else
    {
        string Old(old_path);    //записываем в строку старый путь
        string New(new_path);    //записываем в строку новый путь
        string NewName; //имя новой папки
        SFile* temp; //создаем указатель на временную структуру которая будут указывать вплотную наш файл
        SFile* tempWithoutOne; //временная структура для нового пути
        SForCopy tempory;

        if (Old == New)  //если одинаковы ошибка
            return -1;

        vector<string> OldPath = parsingFunction(Old);  //разбиваем их на массивы
        if(OldPath[0]=="Fail")
          return -1;

        vector<string> NewPath = parsingFunction(New);  //создаем массив имен из нового пути
        if(NewPath[0]=="Fail")
         return -1;

        NewName=NewPath[NewPath.size()-1];
        NewPath.pop_back();//удалчем последнее имя нового пути

        if (Old[0] == '/') //если старый путь начинается с / то запускаем функцию findDir (1. way)
            temp = findDirforChangeDir(1, OldPath);

        else  //если данный путь не начинается с / то запускаем функцию findDir (0. way)
            temp = findDirforChangeDir(0, OldPath);

        if(temp==NULL)
            return -1;

        if(temp->DirOrFile) //если папка то пойдем по детям чтобы посмотреть все размеры и количества
        tempory= SizeandCount (temp);

        else //если это файл
        {
            tempory.count = 1; //это единственный файл и по детям идти не надо
            tempory.newsize=temp->SizeFile;
        }
        if(tempory.newsize>free_space)
            return -1;

        if (New[0] == '/')      //если новый путь начинается с / то запускаем функцию findDir (1. way)
            tempWithoutOne = findDirFunction(1, NewPath);
        else                        //если данный путь не начинается с / то запускаем функцию findDir (0. way)
            tempWithoutOne = findDirFunction(0, NewPath);
        if(tempWithoutOne==NULL)
            return -1;

        SFile* Dir =new SFile; //новая дирректория которую будем вставлсять
        Dir->name=NewName;   //у скопированной папки меняю имя на которое надо
        Dir->DirOrFile=temp->DirOrFile;
        Dir->SizeFile=temp->SizeFile;
        RecursiyaforCopy (Dir, temp);
        //Отправляем в функцию конечный кусок и то что собираемся копировать
        tempWithoutOne->children.push_back(Dir); //нашему пути даю ребенка*/
        Dir->parent=tempWithoutOne; //скопированному пути даю отца
        return tempory.count; //возвращаем ко-во файлов
    }
}
//=============================================================================

void setup_file_manager(file_manager_t *fm)
{
    fm->create = my_create;
    fm->destroy = my_destroy;
    fm->create_dir = my_create_dir;
    fm->create_file = my_create_file;
    fm->remove = my_remove;
    fm->change_dir = my_change_dir;
    fm->get_cur_dir = my_get_cur_dir;
    fm->copy = my_copy;
}
//=============================================================================
