%include "../io.mac"

section .text
    global main
    extern printf

main:
    ;cele doua numere se gasesc in eax si ebx
    mov eax, 4
    mov ebx, 1
    ; TODO: aflati minimul

    cmp eax, ebx
    jg first
    jl second

first:
   	xchg eax, ebx
   	jmp print

second:
   	jmp print

print:
    PRINTF32 `%d\n\x0`, eax ; afiseaza minimul

    ret
