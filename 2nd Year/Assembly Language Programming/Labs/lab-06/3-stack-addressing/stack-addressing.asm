%include "../utils/printf32.asm"

%define NUM 5

section .data
    string1 dd "mere"
    string2 dd "are "
    string3 dd "Ana "
   
section .text

extern printf
global main
main:
    mov ebp, esp

    ; TODO 1: replace every push by an equivalent sequence of commands (use direct addressing of memory. Hint: esp)
    mov ecx, NUM
push_nums:
    sub esp, 4
    mov [esp], ecx
    loop push_nums

    xor ebx, ebx
    mov ebx, 0
    sub esp, 4
    mov [esp], ebx
    sub esp, 4
    xor ebx, ebx
    mov ebx, [string1]
    mov [esp], ebx
    sub esp, 4
    xor ebx, ebx
    mov ebx, [string2]
    mov [esp], ebx
    sub esp, 4
    xor ebx, ebx
    mov ebx, [string3]
    mov [esp], ebx

    lea esi, [esp]
    PRINTF32 `%s\n\x0`, esi

    ; TODO 2: print the stack in "address: value" format in the range of [ESP:EBP]
    ; use PRINTF32 macro - see format above

   ; xor ecx, ecx

next:

    cmp esp, ebp
    jl increment

increment:
    PRINTF32 `%p\n\x0`, esp
    PRINTF32 `%hhu\n\x0`, esp
    add esp, 4
    cmp esp, ebp
    jl next

    ; TODO 3: print the string

    xor edi, edi
    mov edi, [esp - 36]
    PRINTF32 `%s\n\x0`, edi

    ; TODO 4: print the array on the stack, element by element.

    ; restore the previous value of the EBP (Base Pointer)
    mov esp, ebp

    ; exit without errors
    xor eax, eax
    ret
