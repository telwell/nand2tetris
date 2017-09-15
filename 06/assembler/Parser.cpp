#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <boost/algorithm/string.hpp>
#include "Parser.hpp"

// NOTES: This will be useful for arrays:
// https://stackoverflow.com/questions/14684328/how-to-add-something-at-the-end-of-a-c-array

// Constructor
Parser::Parser( std::string file ) {
  lineNum = 0;
  filename = file;
  std::ifstream ifs;
  current_command = std::string();
}

void Parser::incLineNum() {
  lineNum++;
}

int Parser::getLineNum() {
  return lineNum;
}

std::string Parser::getFileName() {
  return filename;
}

void Parser::openFile() {
  ifs.open ( filename );
}

void Parser::closeFile() {
  ifs.close();
}


// COMMAND LOGIC
bool Parser::hasMoreCommands() {
  return ( ifs.good() ? true : false );
}

std::string Parser::getCurrentCommand() {
  return current_command;
}

// Output current command
void Parser::oCurrentCommand() {
  if ( !current_command.empty() ) {
    std::cout << this->commandType() << std::endl;
    std::cout << lineNum << ": " << current_command << std::endl;
  }
}

// Return command type of current_command
std::string Parser::commandType() {
  if( !current_command.empty() ){
    switch(current_command.at(0)){
      case '@':
        return "A_COMMAND";
      case '(':
        return "L_COMMAND";
      // TODO: Make this more robust.
      case '/':
        return "COMMENT";
      default:
        return "C_COMMAND";
    }
  } else {
    return "EMPTY";
  }
}

std::string Parser::symbol() {
  std::string out;
  bool hit = false;
  if ( commandType() == "A_COMMAND" || commandType() == "L_COMMAND" ) {
    for( std::string::size_type i = 0; i < current_command.size(); ++i ) {
      if ( current_command[i] == '\r' || current_command[i] == ')' ){ break; } // eol
      if ( hit ) {
        out += current_command[i];
      }
      // Only start logging after @ or (
      if ( !hit && (current_command[i] == '@' || current_command[i] == '(') ){ hit = true; }
    }
  }
  boost::trim( out );
  return out;
}

// Return true if the string is an integer
// https://stackoverflow.com/questions/8222127/changing-integer-to-binary-string-of-digits
bool Parser::isInt( std::string &in ) {
  if( in.empty() ) return false ;
  char *p;
  strtol(in.c_str(), &p, 10) ;
  return ( *p == 0 ); // will be true if it's NOT an int
}

// Now actually return the int. Should only be used after running isInt()
int Parser::toInt( std::string &in ){
  char *p;
  return strtol(in.c_str(), &p, 10) ;
}

// Dest for C_COMMANDs
std::string Parser::dest() {
  std::string dest;
  if ( commandType() == "C_COMMAND" ) {
    std::size_t semi_found = current_command.find(";");
    if ( semi_found == std::string::npos ){
      // We didn't find a ;, this is not a jump command. Therefore, we have a dest
      for(std::string::size_type i = 0; i < current_command.size(); ++i) {
        if ( current_command[i] == '=' || current_command[i] == '\r' || current_command[i] == '/' ){ break; }
        dest += current_command[i];
      }
    }
  }
  boost::trim( dest );
  return dest;
}

// Comp for C_COMMANDs
std::string Parser::comp() {
  std::string comp;
  bool hit = false;
  if ( commandType() == "C_COMMAND" ) {
    std::size_t semi_found = current_command.find(";");
    if ( semi_found == std::string::npos ){
      // We didn't find a ;. This is NOT a jump line
      for(std::string::size_type i = 0; i < current_command.size(); ++i) {
        if ( current_command[i] == '/' ){ break; } // Stop if we have inline comments
        if ( hit && current_command[i] != '\r') {
          comp += current_command[i];
        }
        // Only start logging after the =
        if ( !hit && current_command[i] == '=' ){ hit = true; }
      }
    } else {
      // This IS a jump line.
      for(std::string::size_type i = 0; i < current_command.size(); ++i) {
        if ( current_command[i] == ';' || current_command[i] == '\r' || current_command[i] == '/' ){ break; }
        comp += current_command[i];
      }
    }
  }
  boost::trim( comp );
  return comp;
}

// jump for C_COMMANDs
std::string Parser::jump() {
  std::string jump;
  bool hit = false;
  if ( commandType() == "C_COMMAND" ) {
    for(std::string::size_type i = 0; i < current_command.size(); ++i) {
      if ( current_command[i] == '/' ){ break; } // Stop if we have inline comments
      if ( hit && current_command[i] != '\r' ) {
        jump += current_command[i];
      }
      // Only start logging after the ;
      if ( !hit && current_command[i] == ';' ){ hit = true; }
    }
  }
  boost::trim( jump );
  return jump;
}

void Parser::next() {
  if ( ifs.is_open() ) {
    std::string line;
    // This is fricken magical: http://en.cppreference.com/w/cpp/io/manip/ws
    ifs >> std::ws;
    std::getline ( ifs, line );
    if ( commandType() == "A_COMMAND" || commandType() == "C_COMMAND" ){
      this->incLineNum();
    }
    current_command = line;
  }
}
