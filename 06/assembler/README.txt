Easiest way to compile this is with something like:
g++ -I /usr/local/ main.cpp Parser.cpp Code.cpp SymTable.cpp Assemble.cpp -o main.o

Then you can run the output with something like:
./main.o ../pong/Pong.asm ../pong/Pong.hack
where Pong.asm is the assembly file and Pong.hack is the user-specified output file.
There is no check involved you can call your output whatever you want.

Note, you need to include /usr/local in here because I use the boost library
http://www.boost.org/ in my Parser (best way I found to remove pesky whitespace).

Seems to work like a charm! Though, I know that it can be cleaned up.
