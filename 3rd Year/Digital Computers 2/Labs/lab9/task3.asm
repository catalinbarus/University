main:

	; initializam tccr0a
	ldi r16, 8'b00000000
	out 0x19, r16

	; configuram timerul pe fast pwm, top 0xFF
	sbi 0x19, 0
	sbi 0x19, 1

	; initializam tccr0b
	ldi r16, 8'b00000000
	out 0x18, r16

	; setam la clkI/O (No prescaling)
	sbi 0x18, 0

	; setam timerul 
	; Clear OC0A on Compare Match, 
	; set OC0A at BOTTOM (non-inverting mode)
	sbi 0x19, 7

	; Setează valoarea lui OCR0A la 63
	ldi r16, 63
	out 0x16, r16



