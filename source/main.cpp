/*
ncurses-Cellular-Automaton

Copyright 2021 Butch Warns

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
of the Software, and to permit persons to whom the Software is furnished to do
so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include <ncurses.h>
#include <unistd.h>
#include <sstream>
#include <random>
#include "Automaton.hpp"
#include "Display.hpp"
#include "Brain.hpp"

using namespace std;

int main (int argc, char *argv[]) {

    initscr(); // Initialise ncurses
    cbreak(); // Enable C-c to break out of programm for dev purposes
    noecho(); // Don't echo key presses
    curs_set (0); // Hide the cursor
    nodelay (stdscr, true); // make getch() non-blocking for main loop

    // Get terminal dimensions
    int maxY, maxX;
    getmaxyx (stdscr, maxY, maxX);

    // Make main window the size of screen
    Display display (maxY, maxX);


    // Rule to apply
    int rule = 0;

    // Seed uniformly distributed rng for random rule
    std::random_device randDevice;
    std::mt19937 mersenneTwister(randDevice());
    std::uniform_real_distribution<double> distribution (0.0, 255.0);

    // Convert command line argument
    if (argc > 1)
        {
            std::stringstream convert (argv[1]);
            convert >> rule;

            // If rule is out of bounds, default to 105
            if (rule > 255 || rule < 0)
                {
                    // Generate random rule
                    rule = distribution (mersenneTwister);
                }
        }
    else
        {
            // Generate random rule
            rule = distribution (mersenneTwister);
        }


    // Make Automaton with state size respecting window border
    Automaton automaton (maxX - 2, rule);

    // Make Brain to handle the programm logic
    Brain brain (&automaton, &display);


    // Main loop
    char c = ' ';

    brain.init();

    while (1)
        {
            // Wait for key press before exiting the program
            c = getch();
            switch (c)
                {
                    // End ncurses functionality
                    // and quit program
                    case 'q':
                        endwin();
                        return 0;
                    // Start/stop animation
                    case 's':
                        brain.runHalt();
                        break;
                    // Advance state
                    case 'n':
                        brain.next();
                        break;
                    case 'r':
                        brain.restartRandomized();
                        break;
                    case 'x':
                        brain.reset();
                        brain.init();
                        break;
                    case 'i':
                        brain.toggleRandomizeState();
                        break;
                    case 't':
                        if (!brain.isRunning())
                            {
                                brain.setRule();
                            }
                        break;
                }

            if (brain.isRunning())
                {
                    // Advance state and display
                    brain.next();

                    // Wait for nicer animation
                    usleep (80000);
                }
        }

    return 0;
}
