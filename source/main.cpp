#include <ncurses.h>
#include <unistd.h>
#include "Automaton.hpp"
#include "Display.hpp"
#include "Brain.hpp"

using namespace std;

int main(int argc, char *argv[]) {

    initscr(); // Initialise ncurses
    cbreak(); // Enable C-c to break out of programm for dev purposes
    noecho(); // Don't echo key presses
    curs_set (0); // Hide the cursor
    nodelay (stdscr, true); // make getch() non-blocking for main loop

    int maxY, maxX;
    getmaxyx (stdscr, maxY, maxX);

    // Make display the size of screen
    Display display (maxY, maxX);

    // Automaton state size subtracts the box border
    Automaton automaton (maxX - 2);

    // Brain to handle the programm logic
    Brain brain (&automaton, &display);

    // Main loop
    char c = ' ';

    brain.init();

    while (1)
        {
            c = getch(); // Wait for key press before exiting the program
            switch (c)
                {
                    case 'q':
                        endwin(); // End ncurses functionality
                        return 0;
                    case 's':
                        brain.runHalt();
                        break;
                }

            if (brain.isRunning())
                {
                    brain.next();
                    usleep (50000);
                }
        }


    return 0;
}
