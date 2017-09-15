#include <iostream>
#include "Parser.hpp"
#include "Code.hpp"
#include "SymTable.hpp"
#include "Assemble.hpp"

using namespace std;

int main (int argc, char *argv[]) {
  // We were only supplied the name of the program
  if (argc == 1) {
    cout << "Must supply a filename in and out" << endl;
  } else if (argc > 3) {
    cout << "Can only supply in/out filenames" << endl;
  } else {
    // Instantiate our classes
    Parser p( argv[1] );
    Code c;
    SymTable st;
    Assemble a( argv[2] );

    cout << "Input filename is: " << p.getFileName() << endl;
    cout << "Output filename is: " << argv[2] << endl;

    // First pass. Add all L_COMMANDS.
    // Get these first b/c otherwise there was a bug
    // where L_COMMANDS were getting added as symbols
    // and messing up the addresses for the actual symbols.
    p.openFile();
    while( p.hasMoreCommands() ){
      if( !p.getCurrentCommand().empty() ){
        if( p.commandType() == "L_COMMAND" ) {
          st.add( p.symbol(), p.getLineNum() );
        }
      }
      p.next();
    }
    p.closeFile();
    // End First Pass

    // Begin SECOND PASS: A_COMMANDS. Get our symbols.
    p.openFile();
    while( p.hasMoreCommands() ){
      if( !p.getCurrentCommand().empty() ){
        if( p.commandType() == "A_COMMAND" ){
          // We don't care about direct addresses
          string sym = p.symbol();
          if( !p.isInt( sym ) ){
            // If the symbol isn't predefined or saved already
            if( !st.exists( sym ) ){
              // Then this is a user defined address
              // cout << "ADDING SYM: " << sym << endl;
              st.add( sym, st.getCurrentAddr() );
              st.incCurrentAddr(); // Don't forget to inc the currentAdd
            }
          }
        }
      }
      p.next(); // Go to next line in parser.
    }
    p.closeFile();
    // End First Pass

    // TODO: Remove
    // st.oAll();

    // ASSEMBLE!!!!!!!!!!
    p.openFile();
    a.openFile();
    while( p.hasMoreCommands() ) {
      if( !p.getCurrentCommand().empty() && p.commandType() != "COMMENT" ) {
        // p.oCurrentCommand(); Uncomment for debug help
        string line;
        if ( p.commandType() == "A_COMMAND" ) {
          string add_str = p.symbol();
          if ( p.isInt( add_str) ) {
            line = bitset<16>( p.toInt( add_str) ).to_string();
          } else {
            string found = st.find( add_str ).to_string();
            line += "0";
            line += found;
          }
        } else if ( p.commandType() == "C_COMMAND" ) {
          line += "111"; // C commands always start with this
          line += c.comp( p.comp() ).to_string(); // includes a bit
          line += c.dest( p.dest() ).to_string();
          line += c.jump( p.jump() ).to_string();
        }
        if( !line.empty() ){
          a.addLine( line ); // actually add the line
        }
      }
      p.next(); // Go to next line in parser.
    }
    p.closeFile(); // Close input
    a.closeFile(); // Close output
  }

  return 0;
}
