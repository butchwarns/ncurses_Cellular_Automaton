# ncurses_Cellular_Automaton
An elementary cellular automaton with a text-based user interface for your terminal.  

## Motivation
This project is my attempt at making "Rule 30", a cellular automaton introduced by Stephen Wolfram in 1983, somewhat more easily explorable for the interested.
The **ncurses-Cellular-Automaton** lets you quickly try out all of the 256 rules on different starting conditions and get a feel for how an elementary CA works in real-time.  

I suggest reading Wolfram's (free) book [A New Kind of Science](https://www.wolframscience.com/nks/) for an introduction to the mechanics behind rule 30 and other cellular automata.

## A word of caution
The animation can flicker quite a bit at times, so please take care if you are sensitive to those kind of things!

## Project status
Functional work in progress. I do intend to add more features in the future.

## Code style
[![js-standard-style](https://img.shields.io/badge/code%20style-stroustrup-brightgreen.svg?style=flat)](https://www.stroustrup.com/bs_faq2.html#layout-style)
 
## Screenshots
![Rule 18 starting from a single cell](/images/rule_18_single_cell.png?raw=true "Rule 18 starting from a single cell")
![Rule 73 starting from random cells](/images/rule_73_random_cells.png?raw=true "Rule 73 starting from random cells")
![Rule 105 starting from a single cell](/images/rule_105_single_cell.png?raw=true "Rule 105 starting from a single cell")
![Rule 126 starting from random cells](/images/rule_126_random_cells.png?raw=true "Rule 126 starting from random cells")

## Tech/framework used
The ncurses library, wrapped in C++, is used to render all graphics on the terminal.

## Features
The **ncurses-Cellular-Automaton** is a command line program with a text-based user interface. It's a real-time implementation, that allows for continuous animation or stepwise operation. Both rule and initial conditions can be set or randomized. Rule randomization also works when the animation is running. You can always use the output of one rule and apply a different one to it. This gives some interesting sequences (if you're lucky). 

## Installation
The project is built using CMake and is therefore easily compiled on most operating systems.
It is preconfigured for MacOS or other UNIX-based environments. Just run `build.sh` to invoke `make`.

`configure.sh` is used in case the `CMakeLists.txt` is updated.  
`rule.sh` just runs the executable in the build folder.

**MacOS:**
  1. `git clone` the repository
  2. Run `build.sh` to compile the program

**Windows:**
  - On Windows the configuration and build scripts can to be updated to create a VSCode project or similar.
  - **TODO** *add installation isntructions for Windows users.*
 
**Linux:**
  - You know what to do :)

## Documentation
**TODO** *add link to documentation*

## How to use?
Just pass a rule to `rule.sh` (or the executable) to initialise the automaton. I suggest maximizing the terminal window beforehand to get the most detailed patterns. 

The following keybindings control the software:

- `S` Run/halt the animation
- `N` Advance to next state
- `T` Enter rule (0-255)
- `R` New random rule
- `X` Reset to initial state
- `I` Toggle randomization of inital conditions
- `Q` Quit program

The idea is to just try some things and see what the automaton comes up with. Sometimes it gives pretty suprising results, so don't hesitate to press `R` a couple of times while the animation is running. (If you do so starting from a single cell, you can get some cool rocket-like pixel spaceships.)

After randomizing the rule it can sometimes happen, that the automaton goes to a state of all black or white cells. If this occurs, you have to restart by pressing `X` to get back to other patterns again.

## License

The **ncurses-Cellular-Automaton** project is released under the MIT license.

Copyright © 2021 Butch Warns

