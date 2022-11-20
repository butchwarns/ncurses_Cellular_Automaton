# ncurses_Cellular_Automaton
![[OPEN_SOURCE_HEART_BADGE]](https://badges.frapsoft.com/os/v1/open-source.png?v=103)
![[BSD_2_CLAUSE_LICENSE_BADGE]](https://img.shields.io/badge/License-BSD&#8722;2&#8722;Clause-blue.svg)

An elementary cellular automaton with a text-based user interface for your terminal.  

## Motivation
This project is my attempt at making "Rule 30", a cellular automaton introduced by Stephen Wolfram in 1983, somewhat explorable for the interested.
The **ncurses-Cellular-Automaton** lets you quickly try out all of the 256 rules on different starting conditions and get a feel for how an elementary CA works in real-time, on the command line.

I suggest reading Wolfram's (free) book [A New Kind of Science](https://www.wolframscience.com/nks/) for an introduction to the mechanics behind rule 30 and other cellular automata.

## A word of caution
The animation can flicker quite a bit at times, so please take care if you are sensitive to those kind of things!

## Project status
Functional work in progress. I do intend to add more features sometime in the future.
 
## Screenshots
![Rule 18 starting from a single cell](/images/rule_18_single_cell.png?raw=true "Rule 18 starting from a single cell")
![Rule 73 starting from random cells](/images/rule_73_random_cells.png?raw=true "Rule 73 starting from random cells")
![Rule 105 starting from a single cell](/images/rule_105_single_cell.png?raw=true "Rule 105 starting from a single cell")
![Rule 126 starting from random cells](/images/rule_126_random_cells.png?raw=true "Rule 126 starting from random cells")

## Tech/framework used
The ncurses library, wrapped in C++, is used to render all graphics on the terminal.
(It needs to be installed on your system in order to compile the program! Simply consult homebrew or the package manager of your choice..)

## Features
The **ncurses-Cellular-Automaton** is a command line program with a text-based user interface. It's a real-time implementation, that allows for continuous animation or stepwise operation. Both rule and initial conditions can be set or randomized. Rule randomization also works when the animation is running. You can always use the output of one rule and apply a different one to it. This gives some interesting sequences (if you're lucky). 

## Installation
The project is built using CMake and should be easily compiled on all UNIX-based operating systems.
Just run `build.sh` to invoke `make`.

`configure.sh` is used in case the `CMakeLists.txt` is updated.  
`rule.sh` just runs the executable in the build folder.

**MacOS/Linux:**
  1. `git clone` the repository
  2. Run `build.sh` to compile the program

 Make sure ncurses is installed on your system. Don't forget to get the development files on Linux :)  
 Should be something along the lines of `ncurses-devel`.
 
 **Windows:**
 
 Unfortunately, the ncurses library is only available to UNIX-like operating systems.  
 (There should be workarounds if you know your way around such things..)

## How to use?
Just pass a rule number to `rule.sh` (or pass it to the executable) to initialise the automaton. I suggest maximizing the terminal window beforehand to get the most detailed patterns. A hacky way to add more cells is decreasing the font size of your terminal, though the interface can become hard to read, if you go too far. Resizing the window or font needs to be done before the program is started.

The following keybindings control the software:

- `S` Run/halt the animation
- `N` Advance to next state
- `T` Enter rule (0-255) (<- TODO: Fix bug that crashes program occasionaly on entering new rule manually)
- `R` New random rule
- `X` Reset to initial state
- `I` Toggle randomization of inital conditions
- `Q` Quit program

The idea is to just try some things and see what the automaton comes up with. Sometimes it gives pretty suprising results, so don't hesitate to press `R` a couple of times while the animation is running. (If you do so starting from a single cell, you can get some cool rocket-like pixel spaceships!)

After randomizing the rule it can sometimes happen, that the automaton goes to a state of all black or white cells. If this occurs, you have to restart by pressing `X` to get back to other patterns again.

## Documentation
Documentation files are not hosted currently, but they are included in the project files. Open _/documentation/html/index.html_ in your browser to access the documentation in case you want an easier time understanding the code.

## License
The **ncurses-Cellular-Automaton** project is licensed under the BSD-2-Clause.

Copyright © 2021 Butch Warns

