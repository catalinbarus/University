%include "../io.mac"

section .text
    global main
    extern printf

main:
    ;cele doua multimi se gasesc in eax si ebx
    mov eax, 139 ; Contine elementele: 1, 2, 8, 128
    mov ebx, 169 ; Contine elementele: 1, 8, 32, 128
    PRINTF32 `%u\n\x0`, eax ; afiseaza prima multime
    PRINTF32 `%u\n\x0`, ebx ; afiseaza cea de-a doua multime

    ; TODO1: reuniunea a doua multimi

    or eax, ebx
    PRINTF32 `Reuniunea este: \x0`
    PRINTF32 `%u\n\x0`, eax ; afiseaza reuniunea multimilor

    mov eax, 139

    ; TODO2: adaugarea unui element in multime

    or eax, 4 ; adaug in prima multime elementul 4
    PRINTF32 `Multimea dupa adaugarea unui element: \x0`
    PRINTF32 `%u\n\x0`, eax

    mov eax, 139

    ; TODO3: intersectia a doua multimi

    and eax, ebx
    PRINTF32 `Intersectia este: \x0`
    PRINTF32 `%u\n\x0`, eax ; afiseaza intersectia multimilor

    mov eax, 139


    ; TODO4: complementul unei multimi

    not eax
    PRINTF32 `Complementul multimii eax este: \x0`
    PRINTF32 `%u\n\x0`, eax ; afiseaza complementul multimii eax

    mov eax, 139

    ; TODO5: eliminarea unui element

    and eax, 131
    PRINTF32 `Multimea dupa eliminarea lui 8 este: \x0`
    PRINTF32 `%u\n\x0`, eax ; afiseaza multimea dupa elimiarea lui 8 din eax

    mov eax, 139

    ; TODO6: diferenta de multimi EAX-EBX

    xor ebx, eax
    and eax, ebx

    PRINTF32 `Diferenta multimilor eax si ebx este: \x0`
    PRINTF32 `%u\n\x0`, eax ; afiseaza eax-ebx

    xor eax, eax
    ret
