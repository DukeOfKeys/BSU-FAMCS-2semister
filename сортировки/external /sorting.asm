.486
.model flat;
.data;
.code 
public _sorting
_sorting proc

 push ebp
    mov ebp, esp
    push esi
    push edi
    push ebx
    
    mov esi, [ebp + 8]   ; arr
    mov ecx, [ebp + 12]  ; n
    dec ecx
    
outer_loop:
    mov edx, ecx
    mov edi, esi
    
inner_loop:
    mov eax, [edi]
    mov ebx, [edi + 4]
    cmp eax, ebx
    jle no_swap
    
    mov [edi], ebx
    mov [edi + 4], eax
    
no_swap:
    add edi, 4
    dec edx
    jnz inner_loop
    
    loop outer_loop
    
    pop ebx
    pop edi
    pop esi
    pop ebp
ret
_sorting endp
end
