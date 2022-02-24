main:
	
	; initializam tccr0a
	ldi r16, 8'b00000000
	out 0x19, r16

	; initializam tccr0b
	ldi r16, 8'b00000000
	out 0x18, r16

	; setam timer-ul in modul CTC
	sbi 0x19, 1

	; no prescaler
	sbi 0x18, 0

	; Toggle OC0A on Compare Match
	sbi 0x19, 6

	; Setează valoarea lui OCR0A la 55
	ldi r16, 55
	out 0x16, r16


	