#include <iostream>

#include "heap.hpp"


int main()
{

    int source[] = { 0, 7, 6, 5, 8, 9, 4, 1, 2, 3 };
    LLHeap<int, CmpType::less> heap(source, sizeof(source)/sizeof(int));
    heap.make_heap();

    for (size_t i = 0; i < 9; i++)
    {
        heap.pop_back();       
    }

    for (auto it : source)
    {
        cout << it << endl;
    }

    system("pause");
}