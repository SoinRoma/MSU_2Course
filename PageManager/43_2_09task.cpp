#include <bits/stdc++.h>
#include "os_mem.h"
#include <vector>
using namespace std;

struct PageManager
{
    int size = -1;   // размер блока в байтах
    int addr = -1; // адрес размещения блока относительно начала всей памяти (в байтах)
    int virtual_page_num = -1;// количество виртуальных страниц
    vector<char> data;  //вектор для байтов (нужно в функциях get и set)
};

int numOfRealPages = 0;  //переменная для количества физических страниц
int sizePage = 0;  //переменная для размера одной страницы памяти
vector<PageManager> pages; //создаем вектор страниц
//-------------------------------------------------------

int my_create(int size, int num_pages) // создание менеджера памяти,
{
    if (numOfRealPages > 0) //если изначально страницы уже есть, то ошибка
        return 0;
     else
    {
        sizePage = size;  //присваиваем подающие значения в наши переменные
        numOfRealPages = num_pages;
        pages.resize(num_pages); //при помощи функции resize мы указываем количествов векторов в векторе
        for (int i = 0; i < numOfRealPages; i++)  //проходим по всему циклу (по всем страницам)
        {
            pages[i].size = size;
            pages[i].addr = i * size;
            pages[i].data.resize(size);
        }
        return 1;
    }
}
//-------------------------------------------------------

int my_destroy() // удаление менеджера памяти
{
    if(numOfRealPages == 0) //если страниц нету,т.е не создан
        return 0;
    else
    {
        numOfRealPages = 0;
        pages.clear(); //зачищаем страницы(векторы)
        return 1;
    }
}
//-------------------------------------------------------

int my_page_num(mem_handle_t block) // возвращает номер  страницы памяти, содержащей указанный блок
{   // возвращаемое значение: номер страницы в случае успеха, -1 в случае неудачи
    //  (если указанный блок целиком не содержится ни в одной странице)

    int blockBegin = block.addr;  //переменная для начала блока
    int blockEnd = blockBegin + block.size - 1;  //для конца блока

    for(int i = 0; i < numOfRealPages; i++)  //проходим по всем страницам
    {
        int left = i * pages[i].size;  //левый блок памяти = итая страница * размер этой же страницы
        int right = left + pages[i].size - 1;// аналогично и справым блоком памяти
        if(left <= blockBegin && blockEnd <= right) //если начало и конец блока памяти находится между левым и правым,
            return i; //то возвращаем страницу
    }
    return -1; //иначе ошибка
}
//-------------------------------------------------------

int my_get_byte(int addr, char *dst)
{   // считывает значение (байт) из ячейки виртуальной памяти, расположенной по указанному адресу addr,
    // и кладет в буфер dst
    // возвращаемое значение: 1 - успех, 2 - виртуальная страница отсутствует, 0 - неудача (например, адрес меньше 0)

    if(addr < 0)  //если адрес меньше нуля
        return 0;

    for(int i = 0; i < numOfRealPages; i++) //проходим по всем страницам
    {
        int left = pages[i].virtual_page_num * pages[i].size;
        int right = left + pages[i].size - 1;
        if(left <= addr && addr <= right) //если адрес размещения блока памяти  находится между ними, то кладем в буфер
        {
            *dst  = pages[i].data[addr - left];
            return 1;
        }
    }
    return 2; //если цикл не прошел, т.е нету виртуальной нету
}
//-------------------------------------------------------

int my_set_byte(int addr, char val)
{   // записывает по указанному виртуальному адресу addr указанное значение (байт) val
    // в случае, если соответствующая виртуальная страница отсутствует в памяти, данные не записываются
    // возвращаемое значение: 1 - успех, 2 - виртуальная страница отсутствует, 0 - неудача (например, адрес меньше 0)

    if(addr < 0) //если адрес меньше нуля
        return 0;

    for(int i = 0; i < numOfRealPages; i++)
    {
        if(pages[i].virtual_page_num != -1)
        {
            int left = pages[i].virtual_page_num * pages[i].size;
            int right = left + pages[i].size - 1;
            if(left <= addr && addr <= right)
            {
                pages[i].data[addr - left] = val;
                return 1;
            }
        }
    }
    return 2;
}
//-------------------------------------------------------

string interconversion(int virtual_page)  //это вспомогательная функция для перевода цыфр в строку
{
    string result;
    do
    {
        char c = static_cast<char>((virtual_page % 10) + '0');
        result += c;
        virtual_page /= 10;
    }
    while(virtual_page);
    reverse(result.begin(), result.end());
    return result;
}
//-------------------------------------------------------

int my_save_page(int real_page, int virtual_page)//записывает страницу физической памяти real_page в файл с именем page virtual_page
{   // данные записываются в бинарном формате
    // в случае успеха выводит на экран сообщение: save_page <real_page> <virtual_page>
    // возвращаемое значение: 1 - успех, 0 - неудача (например, файл не открывается)

    if(numOfRealPages == 0) //если реальных страниц 0 то ошибка
    {
        return 0;
    }

    string fileName = "page_"; //присваивает имя в виртуальной странице
    fileName += interconversion(virtual_page); //цифры добавляем к имени как строку
    ofstream out(fileName, ios::binary); //октрывает файл для выввода

    for(int i = 0; i < pages[real_page].data.size(); i++)//идём по своему файлу и по ячейкам записываем в выходной файл на сервере
    {
        char c = pages[real_page].data[i]; //беру значение из ячейки
        out.write((char*)&c, sizeof(c));  //записываем
    }
    out.close();//закрытие

    printf("save_page %d %d\n", real_page, virtual_page);
    return 1;
}
//-------------------------------------------------------

int my_load_page(int virtual_page, int real_page)//считывает из файла virtual page и загружает её в физическую страницу
{   // данные считываются в бинарном формате
    // если файл с таким именем отсутствует, физическая страница заполняется нулями.
    // в случае успеха выводит на экран сообщение: load_page <virtual_page> <real_page>
    // возвращаемое значение: 1 - успех (отсутствующий файл также является успехом),
    // 0 - неудача (например номер страницы меньше нуля или больше общего числа страниц)

    if(numOfRealPages == 0)
        return 0;

    if(real_page < 0 || real_page >= numOfRealPages)
        return 0;

    string fileName = "page_";
    fileName += interconversion(virtual_page);

    ifstream in(fileName,ios::binary);
    if(!in) //если  страницы с таким именем нету, то запишем нули на все ячейки памяти,которые нам подаются
    {
        pages[real_page].virtual_page_num = virtual_page;
        for(int i = 0; i < pages[real_page].data.size(); i++)
            pages[real_page].data[i] = 0;
    }
    else //если страница есть
    {
        pages[real_page].virtual_page_num = virtual_page; //говорим из какой страницы загружена моя страница
        for(int i = 0; i < pages[real_page].data.size(); i++)//проходим во всем ячейкам данные на эту страницу
        { //и записываем в свои ячейки
            char temporary; //создаем временуюперемунную,типа чар ,тк это символ
            //режим чтения файла
            in.read((char*)&temporary, sizeof(temporary)); //в темп записывает указатель на адрес ячейки памяти
            pages[real_page].data[i] = temporary; //и теперь записываем в ячейку памяти полуенные данные
        }
    }
    in.close(); //закрывает файл

    printf("load_page %d %d\n", virtual_page, real_page);
    return 1;
}
//-------------------------------------------------------

void setup_memory_manager(memory_manager_t *mm)
{
    mm->create = my_create;
    mm->destroy = my_destroy;
    mm->page_num = my_page_num;
    mm->get_byte = my_get_byte;
    mm->set_byte = my_set_byte;
    mm->save_page = my_save_page;
    mm->load_page = my_load_page;
}
//-------------------------------------------------------
