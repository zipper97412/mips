#ADDI $t0, $zero, 5
#ADDI $t1, $zero, -3
ADD $t2, $t0, $t1
SUB $t3, $t0, $t2
MULT $t3,$t0
MFHI $t4
MFLO $t5
DIV $t0, $t3
MFLO $t6
MFLO $t7
AND $t8, $t0, $t3
OR $t9, $t0, $t1
XOR $s0, $t0, $t1
ROTR $t0, $t0, 2
SRL $t1, $t1, 2
SLL $t2, $t2, 1
SLT $t3, $t1, $t2
#SW $s0, 2($t1)
#LW $t4, 2($t1)
LUI $t5, 1
BEQ $t4, $s0, 2
BNE $t4, $s0, 2
BGTZ $t4, 2
BLEZ $t4, 2
#J 01010111010101101001010101
#JAL 11000101010101101101010101
#JR $t1
