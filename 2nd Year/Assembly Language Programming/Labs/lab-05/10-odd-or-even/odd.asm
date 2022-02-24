%include "../utils/printf32.asm"

%define ARRAY_SIZE    10

section .data
    no_array dd 8, 19, 12, 3, 6, 200, 128, 19, 78, 102
    odd_check dd 0
    print_even db "Number of even numbers: ", 0
    print_odd db "Number of odd numbers: ", 0


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
    sub edi, edi
    sub esi, esi

array:

	mov eax, dword [no_array + 4 * (ecx - 1)]
	mov ebx, 2
	div ebx

	cmp edx, 0
	jg odd
	je even

odd:
	add esi, 1
	jmp next

even:
	add edi, 1
	jmp next

next:

	loop array 


    PRINTF32 `%s\x0`, print_even
    PRINTF32 `%u\n\x0`, edi

    PRINTF32 `%s\x0`, print_odd
    PRINTF32 `%u\n\x0`, esi


    leave
    ret           