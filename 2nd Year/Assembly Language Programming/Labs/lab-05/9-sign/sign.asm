%include "../utils/printf32.asm"

%define ARRAY_SIZE    10

section .data
    no_array dd 8, 19, -12, 3, 6, 200, 128, -19, 78, 102
    print_positive db "Number of positive numbers: ", 0
    print_negative db "Number of negative numbers: ", 0


section .text
extern printf
global main
main:
    push ebp
    mov ebp, esp

    mov ecx, ARRAY_SIZE     ; Use ecx as loop counter.
    sub eax, eax 
    sub ebx, ebx           
    sub edx, edx            

array:

    mov edx, dword [no_array + 4 * (ecx - 1)]
    cmp edx, 0
    jg positive
    jl negative

positive:
    add eax, 1
    jmp next

negative:
    add ebx, 1
    jmp next

next: 

    loop array

    PRINTF32 `%s\x0`, print_positive
    PRINTF32 `%u\n\x0`, eax

    PRINTF32 `%s\x0`, print_negative
    PRINTF32 `%u\n\x0`, ebx


    leave
    ret