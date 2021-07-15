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

#include "Brain.hpp"

Brain::Brain(Automaton *_ca, Display *_disp) : ca (_ca), disp (_disp), running (false)
    {

    }

Brain::~Brain(){}


void Brain::init()
    {
        // Initialise automaton
        ca->init();

        // Display the rule and its bit representation
        disp->displayRule (ca->getRule(), ca->getRuleBits());

        // Display whether seed is randomized
        disp->displaySeedRandomized (ca->getStateRandomized());

        // Display seed
        next();
    }


void Brain::reset()
    {
        // Reset automaton and display
        ca->reset();
        disp->reset();
    }


void Brain::runHalt()
    {
        // Toggle animation
        running = !running;
    }


bool Brain::isRunning()
    {
        return running;
    }


void Brain::next()
    {
        // If last line is passed, go back to first line
        if (disp->getPosition() >= disp->getAutomatonWinRows() - 1)
           {
               // disp->reset();
               // disp->displayRule (ca->getRule(), ca->getRuleBits());

               disp->displayCanvas();
            }
        else
            {
                // Display current state
                disp->displayState (ca->getState(), disp->getPosition());
            }

        // Advance Automaton state
        ca->advanceState();

        // Move one line down
        disp->advancePosition();

        // Add next state to canvas
        disp->advanceCanvas (ca->getState());
    }


void Brain::restartRandomized()
    {
        // Reset automaton and display
        // reset();

        // Init again
        // init()

        // Set random rule
        randomize();

        // Display new rule
        disp->displayRule(ca->getRule(), ca->getRuleBits());
    }


void Brain::randomize()
    {
        // Seed uniformly distributed rng for random rule
        std::random_device randDevice;
        std::mt19937 mersenneTwister(randDevice());
        std::uniform_real_distribution<double> distribution (0.0, 255.0);

        int randomRule = distribution (mersenneTwister);
        ca->setRule (randomRule);
    }


void Brain::toggleRandomizeState()
   {
       ca->setStateRandomized (!ca->getStateRandomized());

       // Display change on GUI
       disp->displayGUI (ca->getRule(), ca->getRuleBits(), ca->getStateRandomized());

       // If not running and on starting position..
       if (!isRunning() && disp->getPosition() == 2)
           {
               reset();
               init();
           }
   }


void Brain::setRule ()
    {
        ca->setRule (disp->enterRule());
        disp->displayGUI (ca->getRule(), ca->getRuleBits(), ca->getStateRandomized());
    }
