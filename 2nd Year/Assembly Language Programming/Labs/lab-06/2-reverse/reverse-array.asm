%include "../utils/printf32.asm"

%define ARRAY_LEN 7

section .data

input dd 122, 184, 199, 242, 263, 845, 911
output times ARRAY_LEN dd 0

section .text

extern printf
global main
main:

    ; TODO push the elements of the array on the stack
    ; TODO retrieve the elements (pop) from the stack into the output array

    xor ecx, ecx
    xor ebx, ebx
    mov ebx, ARRAY_LEN

resume_stack:

    mov eax, dword [input + 4*ecx]
    push eax
    inc ecx
    cmp ecx, ebx

    jl resume_stack

    xor ecx, ecx
    xor eax, eax

    PRINTF32 `Reversed array: \n\x0`

    xor eax, eax
    xor ecx, ecx

print_array:
    pop eax
    mov [output + 4 * ecx], eax
    mov edx, [output + 4 * ecx]
    PRINTF32 `%d\n\x0`, edx
    inc ecx
    cmp ecx, ARRAY_LEN
    jb print_array

    xor eax, eax
    ret
