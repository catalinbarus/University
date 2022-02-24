%include "../utils/printf32.asm"

; https://en.wikibooks.org/wiki/X86_Assembly/Arithmetic

section .data
    num1 db 43
    num2 db 39
    num1_w dw 1349
    num2_w dw 9949
    num1_d dd 134932
    num2_d dd 994912
    celsius db 10
    fahren db 60
    print_mesaj dd 'Rezultatul este: 0x', 0

section .text
extern printf
global main
main:
    push ebp
    mov ebp, esp

    ; Multiplication for db
    mov al, byte [num1]
    mov bl, byte [num2]
    mul bl
    
    ; Print result in hexa
    PRINTF32 `%s\x0`, print_mesaj
    xor ebx, ebx
    mov bx, ax
    PRINTF32 `%hx\n\x0`, eax

    ; TODO: Implement multiplication for dw and dd data types.
    xor eax, eax
    xor ebx, ebx

    mov al, byte [celsius]
    mov bl, 9
    mul bl
    PRINTF32 `%d\n\x0`, eax
    PRINTF32 `%d\n\x0`, eax

    xor ebx, ebx
    mov bl, 5
    div bl
    PRINTF32 `%d\n\x0`, eax
    add ax, 32

    PRINTF32 `%d\n\x0`, eax

    xor eax, eax
    xor ebx, ebx

    mov al, byte [fahren]
    sub eax, 32

    PRINTF32 `%d\n\x0`, eax

    mov bl, 5
    mul bl
    PRINTF32 `%d\n\x0`, eax

    xor ebx, ebx
    mov bl, 9
    div bl

    xor ebx, ebx
    mov bl, al
    PRINTF32 `%d\n\x0`, ebx










    ; Multiplication for dw
    mov ax, word [num1_w]
    mov bx, word [num2_w]
    mul bx

    and eax, 0x0000ffff
    shl edx, 16
    or eax, edx

    PRINTF32 `%d\n\x0`, eax

    ; Multiplication for dd
    mov eax, dword [num1_d]
    mov ebx, dword [num2_d]
    mul ebx


    PRINTF32 `%d\n\x0`, eax
    PRINTF32 `%d\n\x0`, edx  

    leave
    ret
