%include "../utils/printf32.asm"

section .text
extern printf
global main
main:
    push ebp
    mov ebp, esp

    mov eax, 211    ; to be broken down into powers of 2
    mov ebx, 1      ; stores the current power

    ; TODO - print the powers of 2 that generate number stored in EAX

    PRINTF32 `%d\n\x0`, ebx

next:
   	add ebx, ebx
   	cmp eax, ebx
   	jg test
   	jmp done

test:
   	test eax, ebx
   	jnz print
   	jmp next

print:
    PRINTF32 `%d\n\x0`, ebx
    cmp eax, ebx
    jg next

done:
    leave
    ret
