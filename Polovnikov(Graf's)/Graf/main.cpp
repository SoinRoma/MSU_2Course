// Л Процедура
#include <iostream>
#include <stdlib.h>
#include <algorithm>
using namespace std;

int main()
{
    int n, sum = 0,temp=0;


    printf("Введетие количество элементов: ");
    cin>>n;
    int arr[n];
    //scanf("%d", &n);
    printf("Введите элементы :");
    for (int i = 0; i < n; i++)
    {
        cin >> temp;
        //scanf("%d", &temp);
        arr[i] = temp;
        sum = sum + arr[i];
    }
    if(sum%2==1)
    {
        printf("\n Сумма выходит нечетной. Алгоритм не выйдет ");
        return 0;
    }
    else
        {
        int tmp;
        for (int k = 0; k < n; k++)
        {
            for (int i = 0; i < n - 1; i++)
            {
                for (int j = 0; j < n - i - 1; j++)
                {
                    if (arr[j] < arr[j + 1])
                    {
                        // меняем элементы местами
                        tmp = arr[j];
                        arr[j] = arr[j + 1];
                        arr[j + 1] = tmp;
                    }
                }
            }

            int head;                       //  0 3 2 1 0       5
            head = arr[0];
            arr[0] = 0;
            for (int i = 0; i < head; i++)
            {
                if (arr[i + 1]-1 < 0)
                {
                    printf("\n Не возможно ");
                    return 0;
                }
                arr[i + 1]--;
            }
        }
    }
    printf("\n Получилось, Ваш массив: ");
    for (auto& i: arr)
        std::cout << i << ' ';
    return 0;
}
