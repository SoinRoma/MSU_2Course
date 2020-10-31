/*
 Страничный менеджер
В каждой задаче данного подраздела требуется реализовать менеджер страниц с указанным набором функций.
 Считается, что доступная виртуальная память не ограничена и делится на страницы фиксированного размера
 (размер страницы задается при вызове функции create).
 Количество физических страниц задается функцией create.
 Каждое обращение к виртуальной памяти порождает обращение к физической памяти
 в соответствии с текущей таблицей страниц (таблица должна быть реализована в менеджере).
9)   Реализовать метод, сохраняющий заданную физическую страницу в файл (функция save_page),
 и метод, загружающий страницу из файла (функция load_page). Данные в файлах хранятся в бинарном формате.
 Каждый метод распечатывает номер страницы, которую он загрузил или сохранил.
 Реализуемые функции: create, destroy, page_num, get_byte, set_byte, save_page, load_page.
*/

#include <bits/stdc++.h>
#include "os_mem.h"

using namespace std;
int main()
{
    memory_manager_t mm;
    setup_memory_manager(&mm);
    int result;
    result =  mm.create(32, 100) != 0;printf("1 expented 1 = %d\n", result); // expected: 1, passed
    result = mm.page_num(mem_handle_t(0, 32));printf("2 expented 0 = %d\n", result); // expected: 0, passed
    result = mm.page_num(mem_handle_t(0, 64));printf("3 expented -1 = %d\n", result); // expected: -1, passed
    result = mm.page_num(mem_handle_t(40, 10));printf("4 expented 1 = %d\n", result); // expected: 1, passed
    result = mm.page_num(mem_handle_t(320, 1));printf("5 expented 10 = %d\n", result); // expected: 10, passed
    result = mm.page_num(mem_handle_t(30, 8));printf("6 expented -1 = %d\n", result); // expected: -1, passed
    result = mm.set_byte(0, 'a');printf("7 expented 2 = %d\n", result); // expected: 2, passed
   // result = mm.get_byte(0, &res);printf("expented 2 =%d\n", result); // expected: 2, passed
    result = mm.load_page(2, 0);printf("8 expented 1 = %d\n", result); // expected: 1, passed
    result = mm.load_page(3, 99);printf("9 expented 1 = %d\n", result); // expected: 1, passed
    result = mm.load_page(4, 100);printf("10 expented 0 = %d\n", result); // expected: 0, passed
    result = mm.set_byte(0, 'a');printf("11 expented 2 = %d\n", result); // expected: 2, passed
    result = mm.set_byte(64, 'a');printf("12expented 1 = %d\n", result); // expected: 1, passed
    result = mm.save_page(0, 2);printf("13 expented 1 = %d\n", result); // expected: 1, failed
    return 0;
}
