; every possible error for the second pass is going to be here
add #4, symbolThatDoesNotExists
bne &symbolThatDoesNotExists
.entry symbolThatDoesNotExists
.extern externalOne
jsr &externalOne