%include "../utils/printf32.asm"

; https://en.wikibooks.org/wiki/X86_Assembly/Arithmetic

section .data
    num1 dq 50000
    num2 dq 3000
    
section .text
extern printf
global main
main:
    
    ; TODO: Calculate quotient and remainder for 69094148 / 87621.

    sub rax, rax
    sub rdx, rdx
    sub rbx, rbx

    mov rax, qword [num1]
    mov rbx, 256
    div rbx

    mov rcx, eax

    mov rax, qword [num2]
    mov rbx, 16
    div rbx

    add rcx, eax

    xor rbx, rbx
    mov rbx, rax
   
    xor rbx, rbx
    mov rbx, rdx
    
    leave
    ret
