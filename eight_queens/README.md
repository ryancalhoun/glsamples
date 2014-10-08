eight_queens
=============

A screensaver-style visualization of a recursive solution to the eight queens problem. Moves are printed on the screen as they happen. The starting point and order of moves are randomized.

The curve of the outer edge of the queen is revolved around a vertical axis to create the surface. The shape was determined by me eyeballing an actual wooden queen piece and drawing dots on an index card.

I have a binary compiled Mar 5 2013, which for some reason, renders the queens is all inside-out or backwards. A binary that I compiled Aug 28 2014 has the same problem but is also missing almost all color. It amazes me how much a framework or platform can change over time, in ways that make the same code produce different behavior.

UPDATE: some of the rendering issues are related to the color depth of the X windows session. I had some success running in an Xvfb session with 16 bit color, but at 24 bit color all the queens are again inside-out.

[![Demo](http://img.youtube.com/vi/m-_2doOacbQ/0.jpg)](http://youtu.be/m-_2doOacbQ)
