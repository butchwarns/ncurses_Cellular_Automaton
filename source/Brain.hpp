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

#ifndef BRAIN_H_
#define BRAIN_H_

#include "Automaton.hpp"
#include "Display.hpp"

/**
 * @brief Program logic handler
 *
 * The Brain class handles program logic and coordinates the automaton model
 * as well as the user interface
 */

class Brain {
public:
   /**
    * @brief Initialises member references to Automaton and Display
    */

    Brain(Automaton *_ca, Display *_disp);


   /**
    * @brief Default
    */

    virtual ~Brain();


   /**
    * @brief Initialises the automaton and displays the seed
    */

    void init();


   /**
    * @brief Resets the automaton and display
    */

    void reset();


   /**
    * @brief Start or stop the animation
    */

    void runHalt();


   /**
    * @brief Returns true if the animation is running
    */

    bool isRunning();


   /**
    * @brief Displays next state and resets if reached last line
    *
    * Gets next state from automaton and passes is to the display.
    * Advances to next line.
    */

    void next();


   /**
    * @brief Resets automaton and display, then starts over with a random rule
    */

    void restartRandomized();

   /**
    * @brief Set new random rule
    */

    void randomize();

   /**
    * @brief Toggle the randomization of initial conditions
    */

    void toggleRandomizeState();


   /**
    * @brief Enter new rule
    */
    void setRule ();

private:
   /**
    * @brief Reference to automaton model class
    */

    Automaton *ca;


   /**
    * @brief Reference to user interface class
    */

    Display *disp;


   /**
    * @brief True if automaton animation is currently running
    */

    bool running;
};

#endif // BRAIN_H_
