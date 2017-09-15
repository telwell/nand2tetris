#Info
This is for the course [nand2tetris](http://nand2tetris.org) chapter 6. Making an
assembler for the HACK machine we built in chapters 1-5.

This is my first foray into the world of C++, so please be gentle if you review this code. Though,
I would love any recommendations you have to give on this code and how I could improve it.

Honestly, I don't know how C programmers debug! On a mac, at least, [LLDB](https://gist.github.com/ryanchang/a2f738f0c3cc6fbd71fa) was not intuitive and
though I've used gdb before, I couldn't seem to get it to work on my mac. I found an [online GDB](https://www.onlinegdb.com/) tool that really helped me but it took a while to get it
up and running, I wish I could have done it locally.

By the end I grasped [pointers](http://www.cplusplus.com/doc/tutorial/pointers/) and address
operators a bit more, but I didn't use them extensively throughout my code. Anyway,
here is my working assembler!

#Instructions
Easiest way to compile this is with something like:
```g++ -I /usr/local/ main.cpp Parser.cpp Code.cpp SymTable.cpp Assemble.cpp -o main.o```

Then you can run the output with something like:
```./main.o ../pong/Pong.asm ../pong/Pong.hack```
where Pong.asm is the assembly file and Pong.hack is the user-specified output file.
There is no check involved you can call your output whatever you want.

Note, you need to include /usr/local in here because I use the boost library
http://www.boost.org/ in my Parser (best way I found to remove pesky whitespace).

Seems to work like a charm! Though, I know that it can be cleaned up.
