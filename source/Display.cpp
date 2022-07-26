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

#include "Display.hpp"

Display::Display(int _automatonWinRows, int _automatonWinCols) : automatonWinRows(_automatonWinRows), automatonWinCols(_automatonWinCols),
                                                                 position(1)
{

    // Create new window
    automatonWin = createWindow(automatonWinRows, automatonWinCols, 0, 0);

    // Set canvas size to automatonWin size without border
    int canvasCellNum = (_automatonWinRows - 2) * (_automatonWinCols - 2);

    // Create canvases for scrolling animation
    canvas = new bool[canvasCellNum];
    nextCanvas = new bool[canvasCellNum];

    // Initialise canvases as all false
    for (int cell = 0; cell < canvasCellNum; cell++)
    {
        canvas[cell] = false;
        nextCanvas[cell] = false;
    }
}

Display::~Display()
{
    delwin(automatonWin);
}

WINDOW *Display::createWindow(int rows, int cols, int winY, int winX)
{
    // Create window
    WINDOW *window = newwin(rows, cols, winY, winX);
    // Inform ncurses about new window
    refresh();

    // Draw box around window
    box(window, 0, 0);

    // Make box visible
    wrefresh(window);

    // Return pointer to created window
    return window;
}

void Display::reset()
{
    // Clear screen
    werase(automatonWin);

    // Redraw box
    box(automatonWin, 0, 0);

    // Make changes visible
    wrefresh(automatonWin);

    // Set position back to first line
    position = 1;
}

void Display::displayGUI(int rule, bool *ruleBits, bool seedRandomized)
{
    displayRule(rule, ruleBits);
    displaySeedRandomized(seedRandomized);
}

void Display::advancePosition()
{
    position += 1;
}

void Display::setPosition(int _position)
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

void Display::displayState(bool *state, int pos)
{
    // Iterate over cells and print the living ones
    for (int cell = 0; cell < (automatonWinCols - 2); cell++)
    {
        if (state[cell])
            mvwaddch(automatonWin, pos, cell + 1, ACS_CKBOARD);
        else
            mvwaddch(automatonWin, pos, cell + 1, ' ');
    }

    wrefresh(automatonWin);
}

void Display::displayRule(int rule, bool *ruleBits)
{
    // Pad rule number with leading zeros
    std::stringstream strstr;
    strstr << std::setw(3) << std::setfill('0') << rule;

    // Print rule in top left corner
    std::string ruleStr = "Rule: " + strstr.str();
    mvwaddstr(automatonWin, 0, 0, ruleStr.c_str());
    wrefresh(automatonWin);

    // Print rule bits also in top left corner
    std::string ruleBitStr = " | ";
    for (int bit = 7; bit >= 0; bit--)
    {
        if (ruleBits[bit])
            ruleBitStr.push_back('1');
        else
            ruleBitStr.push_back('0');
    }
    ruleBitStr.push_back(' ');
    waddstr(automatonWin, ruleBitStr.c_str());
    wrefresh(automatonWin);
}

void Display::displaySeedRandomized(bool seedRandomized)
{
    // Create string
    std::string yesNo = seedRandomized ? "YES" : "NO";
    std::string seedRandomizedStr = "";

    if (seedRandomized)
    {
        seedRandomizedStr = " Seed Randomized: " + yesNo;
    }
    else
    {
        seedRandomizedStr = " Seed Randomized: " + yesNo;
    }

    // Print in top right corner
    int topRight = automatonWinCols - seedRandomizedStr.length();

    mvwaddstr(automatonWin, 0, topRight, seedRandomizedStr.c_str());
    wrefresh(automatonWin);
}

void Display::advanceCanvas(bool *state)
{
    int canvasRows = automatonWinRows - 2;
    int canvasCols = automatonWinCols - 2;

    // Shift all lines up by one dropping the oldest one
    for (int row = 0; row < (canvasRows - 1); row++)
    {
        for (int cell = 0; cell < canvasCols; cell++)
        {
            nextCanvas[(row * canvasCols) + cell] = canvas[((row + 1) * canvasCols) + cell];
        }
    }

    // Add new state in last line of next canvas
    for (int cell = 0; cell < canvasCols; cell++)
    {
        nextCanvas[((canvasRows - 1) * canvasCols) + cell] = state[cell];
    }

    // Pointer swap to reuse memory
    bool *temp = canvas;
    canvas = nextCanvas;
    nextCanvas = temp;
}

void Display::displayCanvas()
{
    // For each row
    for (int row = 0; row < automatonWinRows - 2; row++)
    {
        // Iterate over cells and print the living ones
        for (int cell = 0; cell < (automatonWinCols - 2); cell++)
        {
            if (canvas[row * (automatonWinCols - 2) + cell])
                mvwaddch(automatonWin, row + 1, cell + 1, ACS_CKBOARD);
            else
                mvwaddch(automatonWin, row + 1, cell + 1, ' ');
        }
    }
    wrefresh(automatonWin);
}

int Display::enterRule()
{
    std::string enterStr = "Enter Rule:         ";

    // Print message in top left corner
    mvwaddstr(automatonWin, 0, 0, enterStr.c_str());

    // Show the cursor and echo key presses
    curs_set(1);
    echo();
    wrefresh(automatonWin);

    // Have user enter the rule
    wmove(automatonWin, 0, 12);

    char numberStr[4] = "123";
    wgetnstr(automatonWin, numberStr, 3);
    if (numberStr == nullptr)
    {
        mvwaddstr(automatonWin, 0, 0, "INVALID RULE!        ");
        wrefresh(automatonWin);
        return 0;
    }

    // Convert to int
    std::stringstream strstr(numberStr);

    int rule = 0;
    strstr >> rule;

    // Hide cursor again and don't echo key presses
    curs_set(0);
    noecho();
    wrefresh(automatonWin);

    if (rule >= 0 && rule <= 255)
    {
        return rule;
    }
    else
    {
        return 0;
    }
}
