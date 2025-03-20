/*
Определить, является ли год (положительное целое число) високосным. Високосным считается год, делящийся на 4, за исключением тех годов, которые делятся на 100 и не делятся на 400 (например, 300, 1300 и 1900 годы не являются високосными, а 1200 и 2000 – являются).
*/
#include <iostream>
using namespace std;
int visokosniy_god(int god);
int main()
{
    cout << visokosniy_god(1200) << " " << endl;
}
int visokosniy_god(int god)
{
    int answer = 1;
    _asm {
	mov edx, 0
	mov eax, god
	mov ebx, 4
	div ebx
	cmp edx, 0
	jne if_no
	
	mov eax, god
	mov edx, 0
	mov ebx, 100
	div ebx
	cmp edx, 0
	jne skip_it


	mov eax, god
	mov edx, 0
	mov ebx, 400
	div ebx
	cmp edx, 0
	jne if_no

	jmp skip_it
	if_no:
		mov eax, 0
		mov answer, eax
	skip_it:
    }

    return answer;
}