#include <string>
#include <fstream>

class Code
{
public:
  Code();

  // Dest
  std::bitset<3> dest( std::string dest_in );

  // Comp
  std::bitset<7> comp( std::string comp_in );

  // Jump
  std::bitset<3> jump( std::string jump_in );

private:

};
