/*
Определить, хватит ли денег на покупку x тетрадей по цене m рублей, y карандашей по n рублей и книги за k рублей, если есть в наличии  p купюр по 1000 рублей и r купюр по 500 рублей
*/
#include <iostream>
using namespace std;
int is_enough_money(int ex_book, int ex_book_price, int pencil, int pencil_price, int k1_banknote, int half1k_banknote);
int main()
{
    cout << is_enough_money(1, 100, 5, 5, 0, 1) << endl;
}
int is_enough_money(int ex_book, int ex_book_price, int pencil, int pencil_price, int k1_banknote, int half1k_banknote)
{
    int answer = 1;
    _asm {
	mov eax, ex_book
	mov ebx, ex_book_price
	imul eax, ebx
	push eax
	mov eax, pencil
	mov ebx, pencil_price
	imul eax, ebx
	push eax
	mov eax, k1_banknote
	mov ebx, half1k_banknote
	imul ebx, 500
	imul eax, 1000
	add ebx, eax
	pop eax
	sub ebx, eax
	pop eax
	sub ebx, eax
	mov answer, ebx
    }
    return answer;
}