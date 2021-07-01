#ifndef DISPLAY_H_
#define DISPLAY_H_

#include <ncurses.h>
#include <string>

/**
 * @brief Text-based user interface
 *
 * Handles all graphics work.
 */
class Display {
public:
   /**
    * @brief Allocate memory and set size of the main window
    *
    * @param rows Rows that can be shown on terminal screen
    * @param cols Columns that can be shown on terminal screen
    */
    Display(int rows, int cols);

   /**
    * @brief Free allocated memory
    */
    virtual ~Display();

   /**
    * @brief Create a new window
    *
    * @param rows Window height in rows
    * @param cols Window width in columns
    * @param winY Position of top left window corner in lines down
    * @param winX Position of top left window corner in columns to the right
    *
    * @return Pointer to created ncurses window
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
    * @param _position Row to draw state at
    */
    void setPosition (int _position);

   /**
    * @brief Returns current position
    */
    int getPosition();

   /**
    * @brief Returns rows of main window
    */
    int getAutomatonWinRows();

   /**
    * @brief Displays state in specified line
    *
    * @param *state Pointer to the state array to be displayed
    * @param pos Line number to draw state at
    */
    void displayState (bool *state, int pos);

   /**
    * @brief Displays rule and binary representation
    */
    void displayRule (int rule, bool* ruleBits);

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
};

#endif // DISPLAY_H_
