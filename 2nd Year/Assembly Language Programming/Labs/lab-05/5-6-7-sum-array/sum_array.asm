%include "../utils/printf32.asm"

%define ARRAY_SIZE    10

section .data
    byte_array db 8, 19, 12, 3, 6, 200, 128, 19, 78, 102
    word_array dw 1893, 9773, 892, 891, 3921, 8929, 7299, 720, 2590, 28891
    dword_array dd 1392849, 12544, 879923, 8799279, 7202277, 971872, 28789292, 17897892, 12988, 8799201
    dword_array2 dd 1392, 12544, 7992, 6992, 7202, 27187, 28789, 17897, 12988, 17992
    print_format db "Array sum is ", 0
    index1 db 1
    index2 db 2
    value db 77
    array1 db 1, 2, 3, 4, 5, 6, 7, 8, 9, 10
    array2 db 11, 12, 13, 14, 15, 16, 17, 18, 19, 20

section .text
extern printf
global main
main:
    push ebp
    mov ebp, esp

    ; Pentru array1
xor dl, dl  ;dl = 0
xor si, si	;si = 0
mov dl, [value] ;dl=value  -> ca valoare nu ca adresa
mov si, [index1] ;si = index1, m-am folosit de offset
					  ; pentru a ma indeparta cu index1 valori de inceput 
					  ;(0 + index1 = index1) 
mov [array1 + si], dl	;array[index1] = value


    mov ecx, ARRAY_SIZE     ; Use ecx as loop counter.
    xor eax, eax            ; Use eax to store the sum.
    xor edx, edx            ; Store current value in dl; zero entire edx.

add_byte_array_element:
    mov dl, byte [byte_array + ecx - 1]
    add eax, edx
    loop add_byte_array_element ; Decrement ecx, if not zero, add another element.

    PRINTF32 `%s\x0`, print_format
    PRINTF32 `%u\n\x0`, eax


    ; TODO: Compute sum for elements in word_array and dword_array.

    mov ecx, ARRAY_SIZE     ; Use ecx as loop counter.
    xor eax, eax            ; Use eax to store the sum.
    xor edx, edx            ; Store current value in dl; zero entire edx.

add_word_array_element:
    mov dx, word [word_array + 2 * (ecx - 1)]
    add eax, edx
    loop add_word_array_element ; Decrement ecx, if not zero, add another element.

    PRINTF32 `%s\x0`, print_format
    PRINTF32 `%u\n\x0`, eax


    mov ecx, ARRAY_SIZE     ; Use ecx as loop counter.
    xor eax, eax            ; Use eax to store the sum.
    xor edx, edx            ; Store current value in dl; zero entire edx.

add_dword_array_element:
    mov edx, dword [dword_array + 4 * (ecx - 1)]
    add eax, edx
    loop add_dword_array_element ; Decrement ecx, if not zero, add another element.

    PRINTF32 `%s\x0`, print_format
    PRINTF32 `%u\n\x0`, eax

    mov ecx, ARRAY_SIZE     ; Use ecx as loop counter.
    xor eax, eax            ; Use eax to store the sum.
    xor edx, edx            ; Store current value in dl; zero entire edx.

add_dword2_array_element:

    mov eax, dword [dword_array2 + 4 * (ecx - 1)]
    mov edx, dword [dword_array2 + 4 * (ecx - 1)]
    mul edx

    add ebx, eax
    loop add_dword2_array_element ; Decrement ecx, if not zero, add another element.

    PRINTF32 `%s\x0`, print_format
    PRINTF32 `%u\n\x0`, ebx


    leave
    ret
