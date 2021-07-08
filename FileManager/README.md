# Файловый менеджер
Во всех задачах необходимо реализовать файловый менеджер с определенным набором функций. 
Для решения задач необходимо использовать структуру file_manager_t из файла os_file.h. 
Там же можно найти более подробное описание каждой функции.
Необходимо реализовать все функции, указанные в списке к Вашей задаче.

Все функции должны быть определены в одном файле, который называется SS_1_NNtask.cpp, где SS - номер студента в списке, NN - номер задачи. 
Функция main, демонстрирующая работу программы, должна быть определена в файле SS_1_NNmain.cpp.

Использовать функции и контейнеры STL не разрешается.

Важно: Все реализуемые функции не должны выводить ничего, кроме того, что требуется этих функциях. 
Исключение составляет тестирующая функция main - там вывод на экран допускается и даже приветствуется. 
Также ни функции файлового менеджера, ни функция main не должны запрашивать ввода с клавиатуры, в частности, не должно быть вызова функции getch(), так как она запрашивает ввод с клавиатуры.

Важно: При тестировании на сервере используется специальная утилита проверки корректности работы с памятью. 
Поэтому если Ваша программа работает с памятью некорректно (например, выходит за границы выделенного с помощью malloc или new адресного пространства), эта утилита выдаст сообщение о такой ошибке и программа завершится со статусом RE (Runtime Error). 
То, что в Visual Studio программа не вылетает на тех же тестовых данных, аргументом не является, ошибки работы с памятью должны быть устранены.


Задача: реализовать функции:

create

destroy

create_dir

create_file

remove

change_dir

get_cur_dir

copy