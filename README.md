# ncurses_Cellular_Automaton
An elementary cellular automaton with a text-based user interface for your terminal.  

## Motivation
This project is my attempt at making rule 30, a cellular automaton introduced by Stephen Wolfram in 1983, somewhat more easily explorable for the interested.
The **ncurses-Cellular-Automaton** lets you quickly try out all of the 256 rules on different starting conditions and get a feel for how an elementary CA works in real-time. I suggest reading Wolfram's (free) book [A New Kind of Science](https://www.wolframscience.com/nks/) for an introduction to the mechanics behind rule 30 and other cellular automata.

## A word of caution
The animation can flicker quite a bit at times, so please take care if you are sensitive to those kind of things!

## Project status
Functional work in progress. I do intend to add more features in the future.

## Code style
[![js-standard-style](https://img.shields.io/badge/code%20style-stroustrup-brightgreen.svg?style=flat)](https://www.stroustrup.com/bs_faq2.html#layout-style)
 
## Screenshots
**TODO** *Include logo/demo screenshot etc.*

## Tech/framework used
The ncurses library, wrapped in C++, is used to render all graphics on the terminal.

## Features
The **ncurses-Cellular-Automaton** is a command line program with a text-based user interface. It's a real-time implementation, that allows for continuous animation or stepped operation. Both rule and initial conditions can be set or randomized. Rule randomization also works when the animation is running, so you can use the output of one rule and apply a different one. This gives some interesting sequences (if you're lucky). 

## Installation
The project is built using CMake and is therefore easily compiled on most operating systems.
It is preconfigured for MacOS or other UNIX-based environments. Just run `build.sh` to invoke `make`.

`configure.sh` is used in case the `CMakeLists.txt` is updated.  
`rule.sh` just runs the executable in the build folder.

**MacOS:**
  1. `git clone` the repository
  2. Run `build.sh` to compile the program

**Windows:**
  - On Windows the configuration and build scripts need to be updated to create a VSCode project or similar.
  - **TODO** *add installation isntructions for Windows users.*
 
**Linux:**
  - You know what to do :)

## Documentation
**TODO** *add link to documentation*

## How to use?
Just pass a rule to `rule.sh` (or the executable) to initialise the automaton.  
After that, the following keybindings control the software:

- `S` Run / halt the animation
- `N` Advance to next state
- `R` Randomize Rule
- `X` Reset to initial state
- `I` Toggle randomization of inital conditions
- `Q` Quit program

**TODO** *improve usage instructions*

## License

The **ncurses-Cellular-Automaton** project is released under the MIT license.

Copyright © 2021 Butch Warns

