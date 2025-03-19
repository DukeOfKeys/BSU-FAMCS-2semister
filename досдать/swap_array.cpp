#include <iostream>
using namespace std;
int swap_array(int *arr, int size_arr);
int main()
{
    int arr[] = {1, 1, 1, 1, 4};
    swap_array(arr, 5);
}
int swap_array(int *arr, int size_arr)
{
    _asm {
		mov ecx, size_arr
		mov esi, arr
		mov eax, 0
		loop1:
		cmp eax, ecx
			jge loopend
			mov ebx, [esi + eax]
			xchg ebx, [esi + ecx*4 - 4]
			mov [esi + eax], ebx
			inc eax
			loop loop1
			loopend :

    }
    return 29;
}