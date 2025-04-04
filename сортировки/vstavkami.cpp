
int sort_vst(int *arr, int size_arr)
{
    __asm {
        mov esi, arr         
        mov ecx, size_arr    
        cmp ecx, 1           
        jle end_sort

        mov ebx, 1           
        outer_loop:
        cmp ebx, ecx          
            jge end_sort

            mov eax, [esi + ebx * 4] 
            mov edx, ebx          
            inner_loop :
        cmp edx, 0            
            jle end_inner

            mov edi, [esi + edx * 4 - 4]
            cmp edi, eax            
            jle end_inner

           
            mov[esi + edx * 4], edi
            dec edx                
            jmp inner_loop

            end_inner :
       
        mov[esi + edx * 4], eax
            inc ebx               
            jmp outer_loop

            end_sort :
    }
    return 0;
}