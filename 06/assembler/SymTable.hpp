#include <string>
#include <map>
#include <bitset>

class SymTable
{
public:
  SymTable();

  // Add entry
  void add( std::string sym, int address );

  // Lookup by symbol
  std::bitset<15> find( std::string needle );

  // Check for existance
  bool exists( std::string needle );

  // Get the current address to save. Starts at 16
  int getCurrentAddr();
  void incCurrentAddr();

  // Debug functions
  void oAll();

private:
  std::map<std::string, int> table;
  std::map<std::string, int>::iterator table_it;
  int current_addr;
};
