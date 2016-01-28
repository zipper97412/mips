ADDI $t0, $zero, 5
ADDI $t1, $zero, -3
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
ADDI $t1, $zero, -3
HALT
