#include <string>
#include <iostream>
#include <fstream>

class Assemble
{
public:
  Assemble( std::string filename_in );

  void openFile();
  void closeFile();
  void addLine( std::string line );

private:
  std::string filename;
  std::ofstream ofs;
};
