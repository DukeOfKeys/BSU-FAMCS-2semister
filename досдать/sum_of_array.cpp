#include <iostream>
using namespace std;
int sum_of_array(int *arr, int size_arr);
int main()
{
    int array[] = {1, 4, 5, 6, 74, 21};
    cout << sum_of_array(array, 6) << endl;
    return 0;
}

int sum_of_array(int *arr, int size_arr)
{
    int sum_arr = 0;
    _asm {
	mov esi, arr
	mov eax, 0
	mov ecx, size_arr
	loop1:
	add eax, [esi]
	add esi, 4
	loop loop1
	mov sum_arr, eax
    }
    return sum_of_array;
}