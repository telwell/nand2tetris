// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Fill.asm

// Runs an infinite loop that listens to the keyboard input.
// When a key is pressed (any key), the program blackens the screen,
// i.e. writes "black" in every pixel;
// the screen should remain fully black as long as the key is pressed.
// When no key is pressed, the program clears the screen, i.e. writes
// "white" in every pixel;
// the screen should remain fully clear as long as no key is pressed.

(BEGIN)
  @KBD // 24576 in RAM
  D=M
  @NO_PRESS
  D;JEQ // Goto no press if D == 0
  @R1
  M=-1
  @INIT_LOOP
  0;JMP

(NO_PRESS)
  @R1
  M=0 // Set R1 to our desired value of 0 == false

(INIT_LOOP)
  @SCREEN
  D=A // Set D to the beginning of SCREEN
  @R2
  M=D // R2 will be our current pixel pointer

  @256
  D=A
  @R3
  M=D // R3 == 256. Our row counter

  @32
  D=A
  @R4
  M=D // R4 == 32. Our pixel column counter

(PIXEL_LOOP)
  @R1
  D=M // -1 or 0, hopefully
  @R2
  A=M // Go to the address stored at R2
  M=D // Set all pixels in word to black

  @R2
  M=M+1 // Increment pixel counter

  @R4
  M=M-1 // Decrement R4, pixel column counter
  D=M
  @DECREMENT_ROW_COUNTER
  D;JEQ

  @PIXEL_LOOP
  0;JMP

(DECREMENT_ROW_COUNTER)
  @32
  D=A
  @R4
  M=D // Reset R4

  @R3
  M=M-1 // Decrement row loop
  D=M

  @BEGIN
  D;JEQ

  @PIXEL_LOOP
  0;JMP
