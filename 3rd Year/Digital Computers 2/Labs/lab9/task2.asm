
main:
    
    ; Setam portul A ca output (DDRA)
    ldi r16, 8'b11111111
    out 0x01, r16

    ; t0
    sbi 0x02, 0
    sbi 0x02, 7

    cbi 0x02, 0
    cbi 0x02, 7

    ; t1
    sbi 0x02, 1
    sbi 0x02, 6

    cbi 0x02, 1
    cbi 0x02, 6

    ; t2
    sbi 0x02, 2
    sbi 0x02, 5

    cbi 0x02, 2
    cbi 0x02, 5

    ; t3
    sbi 0x02, 3
    sbi 0x02, 4

    cbi 0x02, 3
    cbi 0x02, 4

    ; t4
    sbi 0x02, 3
    sbi 0x02, 4

    cbi 0x02, 3
    cbi 0x02, 4

    ; t5
    sbi 0x02, 2
    sbi 0x02, 5

    cbi 0x02, 2
    cbi 0x02, 5

    ; t6
    sbi 0x02, 1
    sbi 0x02, 6

    cbi 0x02, 1
    cbi 0x02, 6

    ; t7
    sbi 0x02, 0
    sbi 0x02, 7

    cbi 0x02, 0
    cbi 0x02, 7


