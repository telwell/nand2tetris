// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Mult.asm

// Multiplies R0 and R1 and stores the result in R2.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)

// Setup our negative flag
@R3
M=-1

// First let's test for zero
(ZERO)
  @R0 // Test if R0 == 0
  D=M
  @IS_ZERO
  D;JEQ

  @R1 // Test if R0 == 0
  D=M
  @IS_ZERO
  D;JEQ

// Now look for negative inputs
(NEGS)
  @R0 // Test if R0 < 0
  D=M
  @R0_IS_NEG
  D;JLT

(NEGS_CONT)
  @R1 // Test if R1 < 0
  D=M
  @R1_IS_NEG
  D;JLT
  @PRE_LOOP
  0;JMP

(R0_IS_NEG)
  @R0
  M = -M
  @R3
  M = M+1 // Increment R3
  @NEGS_CONT
  0;JMP

(R1_IS_NEG)
  @R1
  M = -M
  @R3
  M = M+1 // Increment R3

// Setup the Loop
(PRE_LOOP)
  @R2
  M=0

// Otherwise begin the loop
(LOOP)
  @R0
  D=M
  @R2
  M=M+D
  @R1
  M=M-1
  D=M
  @LOOP
  D;JGT
  @END
  0;JMP

// one of the inputs is zero so set R2 to 0 and END
(IS_ZERO)
  @R2
  M=0

// Infinite loop to end the program
(END)
  @END
  0;JMP
