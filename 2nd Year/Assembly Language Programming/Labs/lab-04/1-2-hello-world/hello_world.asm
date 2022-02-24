%include "../io.mac"

section .data
    myString: db "Hello, World!", 0
    mySecondString: db "Goodbye, World!", 0

section .text
    global main
    extern printf

main:
    mov ecx, 6
    jmp next

next:
    sub ecx, 1                      ; N = valoarea registrului ecx
    mov eax, 4
    mov ebx, 1
    cmp eax, ebx
    jg print                        ; TODO1: eax > ebx?
    ret

print:
    PRINTF32 `%s\n\x0`, myString
    cmp ecx, 0                              ; TODO2.2: afisati "Hello, World!" de N ori
    jg next
    PRINTF32 `%s\n\x0`, mySecondString      ; TODO2.1: afisati "Goodbye, World!"


    ret
