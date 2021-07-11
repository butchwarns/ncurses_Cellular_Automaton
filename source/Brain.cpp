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

        // Display seed
        next();
    }


void Brain::reset()
    {

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
