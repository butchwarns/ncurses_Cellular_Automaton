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
