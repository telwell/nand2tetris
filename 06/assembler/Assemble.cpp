#include <string>
#include <iostream>
#include <fstream>
#include "Assemble.hpp"

// Constructor
Assemble::Assemble( std::string filename_in ){
  filename = filename_in;
  std::ofstream ofs;
}

void Assemble::openFile(){
  ofs.open( filename );
}

void Assemble::closeFile(){
  ofs.close();
}

void Assemble::addLine( std::string line ){
  ofs << line << std::endl;
}
