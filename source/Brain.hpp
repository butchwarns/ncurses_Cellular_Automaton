#ifndef BRAIN_H_
#define BRAIN_H_

#include "Automaton.hpp"
#include "Display.hpp"

/**
 * @brief Program logic handler
 *
 * The Brain handles program logic and coordinates the automaton model
 * as well as the user interface.
 */
class Brain {
public:
   /**
    * @brief Initialises member variables
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
