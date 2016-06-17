#include "main.hpp"

//Welcome to the Migration Age source code. Apologies in advance for any
//issues regarding poor commenting or just shitty C++ code in general.

Engine engine;

int main () 
{
    while ( !TCODConsole::isWindowClosed() )
    {
        engine.update();
        TCODConsole::flush();
        engine.handleKeys();
    }
    return 0;
}
