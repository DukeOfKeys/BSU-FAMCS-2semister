#include <iostream>
using namespace std;
int main()
{
    int a, b, nod;
    cin >> a >> b;
    _asm {

		mov eax, a
		mov ebx, b
		

		loop1:
		cmp eax, ebx
			je end1
			jl if1
			sub eax, ebx
			jmp loop1
			if1:
			sub ebx, eax
			jmp loop1
			end1:
			mov nod, eax
    }
    cout << nod << endl;
}