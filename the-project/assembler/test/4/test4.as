; every possible error for the first pass is going to be here
thislineisjustfartoolongforthisassemblertocomprehendsoIwillwriteitheretotestit.Hitoeveryonewhochecksthis.
; symbol errors
?Symbol:
#symbol:
hello\:
hello :
hello   :
this_is_Thelongest26485NameOfASymbol:
emptySymbol:
firstSymbol: .data 5
firstSymbol:
add:
sub:
mcro emptyMac1
    add #1, firstSymbol
mcroend
emptyMac1: .data 5

; data errors
.str
.int
    ; string errors
.string
.string "hi
.string "hi""hi"
    ; integer errors
.data
.data 7,
.data 7,-8+3
.data 7a
.data hi

; instruction errors
