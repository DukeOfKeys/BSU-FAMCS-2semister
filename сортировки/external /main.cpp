#include <iostream>
using namespace std;
extern "C" void sorting(int *arr, int size_arr);
int main()
{
    int arr[] = {5, 3, 8, 1, 2};
    sorting(arr, 5);
    for (int index = 0; index < 5; index++)
    {
        cout << arr[index] << " ";
    }
}