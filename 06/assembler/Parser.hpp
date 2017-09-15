#include <string>
#include <fstream>

class Parser
{
public:
  Parser(std::string file);
  void incLineNum();

  // File methods
  void openFile();
  void closeFile();
  void next();

  // Getters
  int getLineNum();
  std::string getFileName();

  // Command
  std::string getCurrentCommand();
  void oCurrentCommand();
  bool hasMoreCommands();
  std::string commandType();

  // Symbol
  std::string symbol();
  bool isInt( std::string &in );
  int toInt( std::string &in );

  // Dest
  std::string dest();

  // Comp
  std::string comp();

  // Jump
  std::string jump();

private:
  int lineNum;
  std::string filename;
  std::ifstream ifs;
  std::string current_command;
};
