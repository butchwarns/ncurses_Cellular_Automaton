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

#ifndef DISPLAY_H_
#define DISPLAY_H_

#include <ncurses.h>
#include <string>

/**
 * @brief Text-based user interface
 *
 * Handles all graphics work
 */

class Display {
public:
   /**
    * @brief Create main WINDOW* with given size
    *
    * @param rows Number of rows that can be shown on terminal screen
    * @param cols Number of columns that can be shown on terminal screen
    */

    Display(int rows, int cols);


   /**
    * @brief Delete main WINDOW*
    */

    virtual ~Display();


   /**
    * @brief Create a new curses WINDOW* with a box around it
    *
    * @param rows Window height in rows
    * @param cols Window width in columns
    * @param winY Position of top left window corner in lines down
    * @param winX Position of top left window corner in columns to the right
    *
    * @return Pointer to newly created WINDOW
    */

    WINDOW* createWindow (int rows, int cols, int winY, int winX);


   /**
    * @brief Clears the display, draws border and sets position back to one
    */

    void reset();


   /**
    * @brief Advances position by one line
    */

    void advancePosition();


   /**
    * @brief Sets position
    * @param _position Number of row to draw state at
    */

    void setPosition (int _position);


   /**
    * @brief Returns current position
    */

    int getPosition();


   /**
    * @brief Returns number of rows in main window
    *
    * @return Number of rows in main WINDOW
    */

    int getAutomatonWinRows();


   /**
    * @brief Displays state at specified line
    *
    * @param *state Pointer to the state array to be displayed
    * @param pos Line number to draw state at
    */

    void displayState (bool *state, int pos);


   /**
    * @brief Displays rule and binary representation
    */

    void displayRule (int rule, bool* ruleBits);


   /**
    * @brief Scrolls canvas up by one row, then adds new state
    *
    * @param state State to add to the canvas
    */

    void advanceCanvas (bool* state);


   /**
    * @brief Displays whole canvas
    */

    void displayCanvas();


private:
   /**
    * @brief Main window to draw cellular automaton graphics
    */

    WINDOW *automatonWin;


   /**
    * @brief Main automaton window rows
    */

    int automatonWinRows;


   /**
    * @brief Main automaton window columns
    */

    int automatonWinCols;


   /**
    * @brief Current position in lines drawn on the screen
    */

    int position;


   /**
    * @brief History of states for scrolling animation, allocated on heap
    */

    bool *canvas;


   /**
    * @brief History of states including next state used for animation
    */

    bool *nextCanvas;
};

#endif // DISPLAY_H_
