﻿# ASCatto
A minimalist text editor

This is just a toy project made to quickly do some small edit on config files and stuff like that.

To use it simply compile it with make and you will have a single executable. Use the executable with the file you want to edit as the first argument.
To access help just press h while running the program.

![Alt text](https://i.imgur.com/xG27KdU.png "Editing a line")

The idea behind ASCatto is to make a text editor where there is no cursor (the user can access every part of the file with ease) but the user can also view a part of the file in most of the screen.

ASCatto is written in C and the interface is made with ncurses.

Recent modification:
* Help menu is improved.
* Lines are not overlaping anymore.

To do:
- [x] Let the user view lines larger than the terminal screen.
- [x] Make the line editing mode more easy to use.
- [x] Make it easier to navigate in the text-viewing widows.
- [ ] Handle non-ASCII characters.
