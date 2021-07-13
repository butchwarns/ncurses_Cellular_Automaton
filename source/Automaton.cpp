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

#include "Automaton.hpp"

Automaton::Automaton (int _stateLength, int _rule) : stateLength (_stateLength), rule (_rule), randomizeState (false)
    {
        // Allocate memory
        state = new bool [stateLength];
        nextState = new bool [stateLength];
        neighbourhoodBits = new bool [3];
        ruleBits = new bool [8];

        // Initialise neighbourhood array as all false
        for (int i = 0; i < 3; i++)
            {
                neighbourhoodBits [i] = false;
            }

        // Initialise state arrays as all false
        reset();

        // Initialise rule bits as all false
        for (int bit = 0; bit < 8; bit++)
            {
                ruleBits [bit] = false;
            }
    }


Automaton::~Automaton()
    {
        // Free allocated memory
        delete state;
        delete nextState;
        delete neighbourhoodBits;
    }


void Automaton::init()
    {
       if (!randomizeState)
           {
               // Initialise state with one living cell in the middle
               for (int cell = 0; cell < stateLength; cell++)
                   {
                       if (cell == stateLength / 2)
                           state [cell] = true;
                       else
                           state [cell] = false;
                   }
           }
       else
           {
               // Seed uniformly distributed random number generation
               std::random_device randDevice;
               std::mt19937 mersenneTwister(randDevice());
               std::uniform_real_distribution<double> distribution (1.0, 10.0);

               // Initialise state with all random cells
               for (int cell = 0; cell < stateLength; cell++)
                   {
                       // Generate random cell
                       int randomValue = distribution (mersenneTwister);
                       if (randomValue > 5)
                           {
                               state [cell] = true;
                           }
                       else {
                           {
                               state [cell] = false;
                           }
                       }
                   }
       }

       // Initialise rule bit representation
       calculateRuleBits();
    }


void Automaton::reset()
    {
        // Set state arrays to all false
        for (int i = 0; i < stateLength; i++)
            {
                state [i] = false;
                nextState [i] = false;
            }
    }


void Automaton::setRule (int _rule)
    {
        // Set rule and calculate bit representation
        rule = _rule;
        calculateRuleBits();
    }


int Automaton::getRule()
    {
        return rule;
    }


void Automaton::calculateRuleBits()
    {
        for (int bit = 0; bit < 8; bit++)
            {
                // Isolate bit with bitmask
                int masked = rule & (int) pow (2, bit);

                // Shift bit to LSB, essentially making it boolean
                int shifted = masked >> bit;

                // Set bit in heap allocated array
                ruleBits [bit] = shifted;
            }
    }


bool* Automaton::getRuleBits()
    {
        return ruleBits;
    }


void Automaton::advanceState()
    {
        // Iterate over cells in current state
        for (int cell = 0; cell < stateLength; cell++)
            {
                // Find cell neighbourhood wrapping over array bounds
                neighbourhoodBits [0] = state [(cell - 1 + stateLength) % stateLength];
                neighbourhoodBits [1] = state [cell];
                neighbourhoodBits [2] = state [(cell + 1) % stateLength];

                // Convert neighbourhood to integer representation
                int neighbourhood = 0;
                for (int i = 0; i < 3; i++)
                    {
                        int bit = neighbourhoodBits [i] ? 1 : 0;
                        neighbourhood += (bit * (int) pow (2, 2 - i));
                    }

                // Apply rule using bits in reverse order to determine next state
                switch (neighbourhood)
                    {
                    case (0):
                        nextState [cell] = ruleBits [0];
                        break;
                    case (1):
                        nextState [cell] = ruleBits [1];
                        break;
                    case (2):
                        nextState [cell] = ruleBits [2];
                        break;
                    case (3):
                        nextState [cell] = ruleBits [3];
                        break;
                    case (4):
                        nextState [cell] = ruleBits [4];
                        break;
                    case (5):
                        nextState [cell] = ruleBits [5];
                        break;
                    case (6):
                        nextState [cell] = ruleBits [6];
                        break;
                    case (7):
                        nextState [cell] = ruleBits [7];
                        break;
                    }

            }

        // Next state becomes current state
        // Pointer swap reuses allocated memory
        bool* temp = state;
        state = nextState;
        nextState = temp;
    }


bool* Automaton::getState()
    {
        return state;
    }
