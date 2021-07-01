#include "Brain.hpp"

Brain::Brain(Automaton *_ca, Display *_disp) : ca (_ca), disp (_disp), running (false)
    {

    }

Brain::~Brain(){}

void Brain::init()
    {
        ca->init();
        disp->displayRule (ca->getRule(), ca->getRuleBits());
    }

void Brain::reset()
    {

    }

void Brain::runHalt()
    {
        running = !running;
    }

bool Brain::isRunning()
    {
        return running;
    }

void Brain::next()
    {
        disp->displayState (ca->getState(), disp->getPosition());
        ca->advanceState();
        disp->advancePosition();
        if (disp->getPosition() == disp->getAutomatonWinRows() - 1)
            {
               disp->reset();
               disp->displayRule (ca->getRule(), ca->getRuleBits());
            }
    }
