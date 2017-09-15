#include <string>
#include "Code.hpp"

// Constructor
Code::Code(){}

// Dest for C_COMMANDs
std::bitset<3> Code::dest( std::string dest_in ) {
  std::bitset<3> dest;
  std::size_t a_found = dest_in.find("A");
  std::size_t m_found = dest_in.find("M");
  std::size_t d_found = dest_in.find("D");


  if ( m_found != std::string::npos ){ dest.set(0); }
  if ( d_found != std::string::npos ){ dest.set(1); }
  if ( a_found != std::string::npos ){ dest.set(2); }

  return dest;
}

// Comp for C_COMMANDs
std::bitset<7> Code::comp( std::string comp_in ) {
  std::bitset<7> comp;
  if( comp_in == "0" ){
    comp = 0b0101010;
  } else if( comp_in == "1" ){
    comp = 0b0111111;
  } else if( comp_in == "-1" ){
    comp = 0b0111010;
  } else if( comp_in == "D" ){
    comp = 0b0001100;
  } else if( comp_in == "A" || comp_in == "M" ){
    comp = 0b0110000;
  } else if( comp_in == "!D" ){
    comp = 0b0001101;
  } else if( comp_in == "!A" || comp_in == "!M" ){
    comp = 0b0110001;
  } else if( comp_in == "-D" ){
    comp = 0b0001111;
  } else if( comp_in == "-A" || comp_in == "-M" ){
    comp = 0b0110011;
  } else if( comp_in == "D+1" ){
    comp = 0b0011111;
  } else if( comp_in == "A+1" || comp_in == "M+1" ){
    comp = 0b0110111;
  } else if( comp_in == "D-1"){
    comp = 0b0001110;
  } else if( comp_in == "A-1" || comp_in == "M-1" ){
    comp = 0b0110010;
  } else if( comp_in == "D+A" || comp_in == "D+M" ){
    comp = 0b0000010;
  } else if( comp_in == "D-A" || comp_in == "D-M" ){
    comp = 0b0010011;
  } else if( comp_in == "A-D" || comp_in == "M-D" ){
    comp = 0b0000111;
  } else if( comp_in == "D|A" || comp_in == "D|M" ){
    comp = 0b0010101;
  }
  // Set our A bit?
  std::size_t m_found = comp_in.find("M");
  if ( m_found != std::string::npos ){ comp.set(6); }
  return comp;
}

// jump for C_COMMANDs
std::bitset<3> Code::jump( std::string jump_in ) {
  std::bitset<3> jump;
  if ( jump_in == "JGT" ){
    jump = 0b001;
  } else if ( jump_in == "JEQ" ){
    jump = 0b010;
  } else if ( jump_in == "JGE" ){
    jump = 0b011;
  } else if ( jump_in == "JLT" ){
    jump = 0b100;
  } else if ( jump_in == "JNE" ){
    jump = 0b101;
  } else if ( jump_in == "JLE" ){
    jump = 0b110;
  } else if ( jump_in == "JMP" ){
    jump = 0b111;
  }
  return jump;
}
