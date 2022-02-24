main:
	; initializam tccr0a
	ldi r16, 8'b00000000
	out 0x19, r16

	; initializam tccr0b
	ldi r16, 8'b00000000
	out 0x18, r16

	; configuram timerul pe fast pwm, top OCRA
	sbi 0x19, 0
	sbi 0x19, 1
	sbi 0x18, 3

	; setează ceasul Timer/Counter0 să folosească un prescaler de 8
	sbi 0x18, 1

	; setam OC0B on Compare Match, clear OC0B at BOTTOM(inverting mode)
	sbi 0x19, 4
	sbi 0x19, 5

	; Setează valoarea lui OCR0B la 34
	ldi r16, 34
	out 0x15, r16

	; Setează valoarea lui OCR0A la 130
	ldi r16, 130
	out 0x16, r16