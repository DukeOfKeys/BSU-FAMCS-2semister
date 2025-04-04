
int sort_choice(int *arr, int size_arr)
{
    __asm {
        mov esi, arr           
        mov ecx, size_arr     
        cmp ecx, 1           
        jle end_sort

        xor ebx, ebx         
        outer_loop :
        mov edx, ebx          
            mov edi, ebx         
            inc edi

            
            inner_loop :
        cmp edi, ecx          
            jge end_inner

            mov eax, [esi + edi * 4]  
            cmp eax, [esi + edx * 4] 
            jge skip_update_min

            mov edx, edi         
            skip_update_min :
        inc edi             
            jmp inner_loop

            end_inner :
       
        mov eax, [esi + ebx * 4]    
            mov edi, [esi + edx * 4]     
            mov[esi + ebx * 4], edi     
            mov[esi + edx * 4], eax     

            inc ebx           
            cmp ebx, ecx         
            jl outer_loop

            end_sort :
    }
    return 0;
}