#include "Automaton.hpp"

Automaton::Automaton (int _stateLength) : stateLength (_stateLength), rule (105)
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
       // Initialise state with one living cell in the middle
       for (int cell = 0; cell < stateLength; cell++)
           {
               if (cell == stateLength / 2)
                   state [cell] = true;
               else
                   state [cell] = false;
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
