.entry MAIN
MAIN:   mov #5,r1
        mov #5, r1
        mov r1, A
        cmp #6, A
        cmp r1,A
        cmp r1,#6
        cmp r1, A
        add A, r0
        add r2,B
        add #2 ,r3
        sub A, r0
        sub r2,B
        sub #2 ,r3
        lea B, r2
        lea B,r2
        lea B,A
        lea B ,A
        lea B , A
        lea B, A
        clr r2
        clr A
        clr B
        not r1
        not A
        inc r2
        inc B
        dec r5
        dec A

RESTART:    jmp &MAIN
            jmp &MORE
            jmp &END

MORE:   bne RESTART
        jsr MAIN
        red r1
        red A
        prn r5
        prn B
        rts

A: .data 5
.extern B
C: .string "Hello World Man"
.string "The Open University of Israel\n"

END: stop