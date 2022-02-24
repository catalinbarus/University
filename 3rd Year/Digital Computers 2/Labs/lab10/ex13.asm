main:
	
	; Timer mod Normal

	; initializam tccr0a
	ldi r16, 8'b00000000
	out 0x19, r16

	; initializam tccr0b
	ldi r16, 8'b00000000
	out 0x18, r16

	; folosim prescaler de 256
	sbi 0x18, 2

	; set Clear OC0B on Compare Match
	sbi 0x19, 5

	; Setează valoarea lui OCR0B la 127
	ldi r16, 127
	out 0x15, r16



	