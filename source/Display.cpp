#include "Display.hpp"

Display::Display(int _automatonWinRows, int _automatonWinCols) :
    automatonWinRows (_automatonWinRows), automatonWinCols (_automatonWinCols),
    position (1)
    {
       automatonWin = createWindow (automatonWinRows, automatonWinCols, 0, 0);
    }

Display::~Display()
    {
        delwin (automatonWin);
    }

WINDOW* Display::createWindow (int rows, int cols, int winY, int winX)
    {
        // Create window
        WINDOW *window = newwin (rows, cols, winY, winX);
        // Inform ncurses about new window
        refresh();

        // Draw box around window
        box (window, 0, 0);

        // Make box visible
        wrefresh (window);

        // Return pointer to created window
        return window;
    }

void Display::reset()
    {
        //Clear screen
        werase (automatonWin);

        // Redraw box
        box (automatonWin, 0, 0);

        // Make changes visible
        wrefresh (automatonWin);

        // Set position back to first line
        position = 1;
    }

void Display::advancePosition()
    {
        position += 1;
    }

void Display::setPosition (int _position)
    {
        position = _position;
    }

int Display::getPosition()
    {
        return position;
    }

int Display::getAutomatonWinRows()
    {
        return automatonWinRows;
    }

void Display::displayState (bool *state, int pos)
    {
        // Iterate over cells and print the living ones
        for (int cell = 0; cell < (automatonWinCols - 2); cell++)
            {
                if (state [cell])
                    mvwaddch (automatonWin, pos, cell + 1, ACS_DIAMOND);
                else
                    mvwaddch (automatonWin, pos, cell + 1, ' ');
            }
        wrefresh (automatonWin);
    }

void Display::displayRule (int rule, bool* ruleBits)
    {
        // Print rule in top left corner
        std::string ruleStr = "Rule: " + std::to_string(rule);
        mvwaddstr (automatonWin, 0, 0, ruleStr.c_str());
        wrefresh (automatonWin);

        // Print rule bits also in top left corner
        std::string ruleBitStr =" | ";
        for (int bit = 7; bit >= 0; bit--)
            {
                if (ruleBits [bit])
                    ruleBitStr.push_back ('1');
                else
                    ruleBitStr.push_back ('0');
            }
        ruleBitStr.push_back (' ');
        waddstr (automatonWin, ruleBitStr.c_str());
        wrefresh (automatonWin);
    }
