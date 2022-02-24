
main:
    
    ; Setam portul A ca output (DDRA)
    ldi r16, 8'b11111111
    out 0x01, r16

    ; Setam portul B ca input (DDRB)
    ldi r16, 8'b00000000
    out 0x05, r16

loop:

    ; Citim de pe portul B (PINB)
    in r16, 0x04

    ; Scriem pe portul A (PORTA)
    out 0x02, r16

    jmp loop
    