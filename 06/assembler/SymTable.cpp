#include <iostream>
#include <string>
#include <map>
#include <bitset>
#include "SymTable.hpp"

// Constructor
SymTable::SymTable(){
  std::map<std::string, int> table;
  std::map<std::string, int>::iterator table_it;
  current_addr = 16;
  // Add our predefined symbols on construct
  add( "SP", 0 );
  add( "LCL", 1 );
  add( "ARG", 2 );
  add( "THIS", 3 );
  add( "THAT", 4 );
  add( "SCREEN", 16384 );
  add( "KBD", 24576 );
  add( "R0", 0 );
  add( "R1", 1 );
  add( "R2", 2 );
  add( "R3", 3 );
  add( "R4", 4 );
  add( "R5", 5 );
  add( "R6", 6 );
  add( "R7", 7 );
  add( "R8", 8 );
  add( "R9", 9 );
  add( "R10", 10 );
  add( "R11", 11 );
  add( "R12", 12 );
  add( "R13", 13 );
  add( "R14", 14 );
  add( "R15", 15 );
}

void SymTable::add( std::string sym, int address ){
  table[sym] = address;
}

std::bitset<15> SymTable::find( std::string needle ){
  std::bitset<15> address = std::bitset<15>( 0 );
  for (table_it = table.begin(); table_it != table.end(); table_it++) {
    if( table_it->first == needle ){
      address = std::bitset<15>( table_it->second );
    }
  }
  return address;
}

bool SymTable::exists( std::string needle ){
  bool exists = false;
  for (table_it = table.begin(); table_it != table.end(); table_it++) {
    if( table_it->first == needle ){
      exists = true;
    }
  }
  return exists;
}

int SymTable::getCurrentAddr(){
  return current_addr;
}

void SymTable::incCurrentAddr(){
  current_addr++;
}

// Output everything in our SymTable
void SymTable::oAll(){
  for (table_it = table.begin(); table_it != table.end(); table_it++) {
    std::cout << table_it->first << ' ' << table_it->second << std::endl;
  }
}
