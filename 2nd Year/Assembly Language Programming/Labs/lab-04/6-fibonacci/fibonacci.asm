%include "../io.mac"

section .text
    global main
    extern printf

main:
    mov eax, 7       ; vrem sa aflam al N-lea numar; N = 7

    ; TODO: calculati al N-lea numar fibonacci (f(0) = 0, f(1) = 1)

    mov ecx, 1
    mov ebx, 0
    mov edx, 1
if:
    cmp eax, ecx
    jg next_elem
    jmp finish

next_elem:
    mov eax, 0
   	add eax, ebx
   	add eax, edx
   	mov ebx, edx
   	mov edx, eax
    mov eax, 7
    add ecx, 1
    jmp if

finish:
    PRINTF32 `%d\n\x0`, edx

    ret
