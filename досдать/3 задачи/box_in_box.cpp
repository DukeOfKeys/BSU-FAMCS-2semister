/*
Можно ли коробку размером A x B x C упаковать в посылку размером X x Y x Z? При упаковке каждая грань коробки должна быть параллельна какой-то грани посылки.
*/
#include <iostream>
using namespace std;
int can_be_placed(int *sizes_box, int *post_box);

int main()
{
    int array1[] = {1, 2, 3};
    int array2[] = {2, 3, 4};
    cout << can_be_placed(array1, array2) << endl;
    cout << array1[0] << " " << array1[1] << " " << array1[2] << endl;
    cout << array2[0] << " " << array2[1] << " " << array2[2] << endl;
}

int can_be_placed(int *sizes_box, int *post_box)
{
    int answer = 1;
    _asm {
		mov esi, sizes_box
		mov ecx, 2
		loop1:
		mov eax, ecx
		mov ecx, 2
			loop11:
			mov ebx, [esi + ecx * 4 ]
			cmp ebx, [esi + ecx*4 -4]
			jg if1
			endif1:
		loop loop11
		mov ecx, eax
		loop loop1



		mov esi, post_box
			mov ecx, 2
			loop2:
		mov eax, ecx
			mov ecx, 2
			loop22 :
			mov ebx, [esi + ecx * 4]
			cmp ebx, [esi + ecx * 4 - 4]
			jg if2
			endif2 :
		loop loop22
			mov ecx, eax
			loop loop2
			

			mov esi, sizes_box
			mov edi, post_box
			mov ecx, 3
			loop3:
			mov eax, [edi + ecx* 4 -4]
			cmp eax, [esi + ecx*4 -4]
			jg wrong_size
			loop loop3





			jmp skip_statements
			if1:
			mov ebx, [esi + ecx * 4 ]
			xchg [esi + ecx * 4 - 4], ebx
			mov [esi + ecx * 4], ebx
			jmp endif1

			if2 :
			mov ebx, [esi + ecx * 4]
				xchg[esi + ecx * 4 - 4], ebx
				mov[esi + ecx * 4], ebx
				jmp endif2

			wrong_size:
			mov eax,0
			mov answer, eax
				skip_statements:

    }
    return answer;
}