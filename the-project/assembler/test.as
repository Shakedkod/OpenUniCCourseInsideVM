MAIN: add r3, LIST
LOOP: prn #48
mcro a_mc
cmp K, #-6
 bne &END
mcroend
 lea STR, r6
 inc r6
 a_mc
 mov r3, K
 sub r1, r4
 bne END
a_mc
a_mc
 dec K
 jmp &LOOP
END: stop
STR: .string “abcd”
a_mc
LIST: .data 6, -9
 .data -100
K: .data 31 