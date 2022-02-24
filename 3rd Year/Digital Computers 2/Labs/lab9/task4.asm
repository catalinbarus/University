DDRA        equ 0x01
    PORTA       equ 0x02
    TCCR0A      equ 0x19
    TCCR0B      equ 0x18
    TIMSK       equ 0x26
    OCR0A       equ 0x16
 
    rjmp        main            ; Adresa 0x0000
    reti                        ; Adresa 0x0001
    reti                        ; Adresa 0x0002
    reti                        ; Adresa 0x0003
    reti                        ; Adresa 0x0004
    reti                        ; Adresa 0x0005
    reti                        ; Adresa 0x0006
    reti                        ; Adresa 0x0007
    reti                        ; Adresa 0x0008
    rjmp        TIM0_COMPA_ISR  ; Adresa 0x0009
    reti                        ; Adresa 0x000A
    reti                        ; Adresa 0x000B
    reti                        ; Adresa 0x000C
    reti                        ; Adresa 0x000D
    reti                        ; Adresa 0x000E
    reti                        ; Adresa 0x000F
    reti                        ; Adresa 0x0010
 
TIM0_COMPA_ISR:
    ; TODO 4: Schimbați (toggle) starea pinului PA0.
    ldi r16, 1

    ; citim PINA
    in r17, 0x00

    or r17, r16

    ; scriem in PORTA
    out 0x02, r17

main:
    ; TODO 4: Configurați pinul PA0 ca și ieșire.

    ; out DDRA
    ldi r16, 0b00000001
    out 0x01, r16

 
    ; TODO 4: Porniți un timer care să genereze o întrerupere de comparație pe canalul A. Puneți
    ; valoarea 42 ca valoare de comparație pentru canalul A.

    ; initializam tccr0a
    ldi r16, 8'b00000000
    out 0x19, r16

    ; initializam tccr0b
    ldi r16, 8'b00000000
    out 0x18, r16

    ; initializam timsk
    ldi r16, 8'b00000000
    out 0x26, r16

    ; Setam tccr0a pe mod CTC
    sbi 0x19, 1

    ; setam la clkI/O (No prescaling)
    sbi 0x18, 0

    ; generam intrerupere pe canalul A
    sbi 0x26, 1

    ; Setează valoarea lui OCR0A la 42
    ldi r16, 42
    out 0x16, r16

    ; TODO 4: Activați întreruperile global.
    sei
 
    ; Deși programul pare să stea într-o buclă infinită, ar trebui să vedem că totuși starea
    ; pinului PA0 se schimbă.
    loop:
        rjmp loop