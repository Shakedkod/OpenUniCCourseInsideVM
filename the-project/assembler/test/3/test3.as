mcro mc_dot_3_or_4
    mov r1, A
    cmp #6, A
mcroend
mcro this_is_only_the_second
    not A
    inc r2
mcroend
mcro third
    red A
    prn r5
mcroend

MAIN:   mc_dot_3_or_4
        third
        this_is_only_the_second
        third
        third

.entry MAIN
.extern A