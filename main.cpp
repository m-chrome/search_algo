#include <iostream>
#include <fstream>
#include <ctime>
#include <cstddef>
#include <vector>
#include <map>
#include <cstdlib>

#include "ticket.hpp"

using namespace std;
using namespace ticket;

template <class T>
void shiftDown(vector <T> &a, size_t i, size_t length)
{
    size_t left = 2*i+1;
    size_t right = left+1;
    size_t maxChild = left;
    while (maxChild < length)
    {
        if (right < length)
        {
            if (a[left] < a[right])
            {
                maxChild = right;
            }
        }
        if (a[i]<a[maxChild])
        {
            swap(a[i], a[maxChild]);
        }
        else
        {
            break;
        }
        i=maxChild;
        left=2*i+1;
        right=left+1;
        maxChild=left;
    }
}

template <class T>
void heap_sort(vector <T> &a)
{
    int i;
    int size = a.size();
    for(i=size/2 - 1; i>=0; i--)
    {
        shiftDown(a, i, size);
    }
    for(i=size-1; i>0; i--)
    {
        swap(a[0], a[i]);
        shiftDown(a, 0, i);
    }
}

class FindException {};

Ticket searchLinear(vector <Ticket> &a, size_t &key)
{
    for(auto &it: a)
    {
        if (it.date == key)
        {
            return it;
        }
    }
    throw FindException();
}

Ticket searchBinary(vector <Ticket> &a, size_t &key, size_t left, size_t right)
{
    if (left > right)
        throw FindException();
    size_t mid=(left+right)/2;
    if (a[mid].date==key) return a[mid];
    if (a[mid].date<key) return searchBinary(a, key, mid+1, right);
    if (a[mid].date>key) return searchBinary(a, key, left, mid-1);
}

int main()
{
    srand(time(0));
    // Открытие файла с данными по всем билетам
    ifstream data_list;
    data_list.open("ticket_list.txt");
    // Проверка на правильное открытие файла
    if (!data_list)
    {
        cout << "Can't open file!"<< endl;
        return 1;
    }

    size_t number, cost, date, prize;
    vector <Ticket> ticketsVector;
    map <size_t, TicketData> ticketsMap;

    // Заполняем билеты данными из файла
    while(data_list >> number >> cost >> date >> prize)
    {
        Ticket item(date, number, cost, prize);
        ticketsVector.push_back(item);
        ticketsMap.emplace(item.date, item.data);
    }

    cout << "List size: " << ticketsVector.size() << endl;

    // Тут храним ключ поиска
    date=0;

    // Нужно ввести ключ поиска
    cout << "Enter key 4 search: " << endl;
    cin >> date;
    cout << endl;
    double timer[]={0,0};

    // ---------------------------------------------------------------------------------------------

    // Прямой поиск  в неотсортированном векторе
    cout << "LINEAR SEARCH IN ORIGINAL LIST" << endl;
    timer[0]=(double)clock()/CLOCKS_PER_SEC;
    cout << searchLinear(ticketsVector, date);
    timer[1]=(double)clock()/CLOCKS_PER_SEC;
    printf("Runtime of linear search (in vector): %.7lf sec.\n\n", timer[1]-timer[0]);

    // ---------------------------------------------------------------------------------------------

    // Пирамидальная сортировка + бинарный поиск
    cout << "HEAP SORT + BINARY SORT" << endl;
    timer[0]=(double)clock()/CLOCKS_PER_SEC;
    heap_sort(ticketsVector);
    timer[1]=(double)clock()/CLOCKS_PER_SEC;
    double htime = timer[1] - timer[0];
    printf("Runtime of heap sort: %.7lf sec.\n", htime);
    timer[0]=(double)clock()/CLOCKS_PER_SEC;
    cout << searchBinary(ticketsVector, date, 0, ticketsVector.size());
    timer[1]=(double)clock()/CLOCKS_PER_SEC;
    double btime = timer[1] - timer[0];
    printf("Runtime of binary search: %.7lf sec.\n", btime);
    printf("Heap sort + binary search: %.7lf sec.\n\n", (double)(btime+htime));

    // ---------------------------------------------------------------------------------------------

    // Поиск по ключу в map
    cout << "MAP KEY SEARCH" << endl;
    timer[0]=(double)clock()/CLOCKS_PER_SEC;
    map <size_t, TicketData> ::iterator search = ticketsMap.find(date);
    if (search != ticketsMap.end())
    {
        cout << "Ticket was found!" << endl;
        cout << search->first << ' ' << search->second << endl;
    }
    else cout << "Not found 404!";
    timer[1]=(double)clock()/CLOCKS_PER_SEC;
    printf("Runtime of key search in map: %.7lf sec.\n", timer[1] - timer[0]);
    return 0;
}
