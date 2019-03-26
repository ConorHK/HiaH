*Problem Definition*

Design and implement the game engine for a C application to play the board game Igel Ärgern (commonly translated as "Hedgehogs in a Hurry").



Rules are very easy to find on the web (begin by reading this document that describes the basic rules of the game as well as others at boardgamegeek.com); and I will demonstrate the game in class. Therefore, I provide only a very brief overview here:
The standard game is played on a grid with 6 rows and 9 columns. The game allows 2--6 players. Each player has four tokens (representing hedgehogs) that he or she must move from the left column to the right column. Tokens sharing a square stack on top of each other. Only the token on the top of a stack may move.

*On his/her turn a player:*

rolls the dice,
optionally moves one of his/her token up or down one row (we call this a "sideways" move, because the token is moved sideways relative to the direction of travel toward the finish line), and
chooses one token (either his or another player's) in the row indicated by the dice roll and moves it one space to the right (i.e., "forward").
The winner of the game is the player who can move three of his/her tokens in the last column of the board.

*Requirements:*

Implement the game logic for Igel Ärgern. In addition to playing a basic game of Igel Ärgern. 

A Graphical User Interface will not be required to  be implemented but it is sufficient that you allow players to play from the command line. You can draw the board on the command line at each turn of the game.
You are only required to implement basic obstacles. Note that 1 obstacle square should be present for each row of the board. Obstacle squares should also be placed in different columns of the board and cannot be placed in the first and the last column on the board. A token that falls into an obstacle is  stuck there until every other token has caught up (i.e. no token is placed in a column on the left of the obstacle in any row). A way to implement obstacle squares could be to turn an obstacle square into a normal one once there is no token placed in a column on the left of the obstacle in any row. 
Use the Git distributed version control to commit your code regularly from the beginning of your project.

*Code Design Requirements:*

●      Comment your code, where necessary.
●      Use functions where you can.
Separate your code into independent modules as much as you can.

