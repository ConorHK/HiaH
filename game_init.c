/*
 * File: game_init.c
 * Project: f:\Documents\C\Semester 2\Hedgehogs in a Hurry\
 * Created Date: Saturday March 9th 2019 4:44:25 pm
 * Author: ConorHK, thomasreilly1011 (based on template by lpasquale) 
 * -----
 * Description: File responsible for initialzing the game.
 */

#include "game_init.h"
#include <stdio.h>

/*
 * This function creates the board for the first time
 * 
 * Input: board - a 6x9 array of squares
 *
 */
void initialize_board(square board[NUM_ROWS][NUM_COLUMNS])
{

    for (int i = 0; i < NUM_ROWS; i++)
    {
        for (int j = 0; j < NUM_COLUMNS; j++)
        {
            //creates an obstacle square at positions (0,3), (1,6), (2,4), (3,5), (4,2) and (5,7)
            if ((i == 0 && j == 3) || (i == 1 && j == 6) || (i == 2 && j == 4) || (i == 3 && j == 5) || (i == 4 && j == 2) || (i == 5 && j == 7))
            {
                board[i][j].type = OBSTACLE;
            }
            else
            {
                //creates a normal square otherwise
                board[i][j].type = NORMAL;
            }
            board[i][j].stack = NULL;
            
            //**Initializes each square to 0 tokens.
            board[i][j].numTokens = 0;
        }
    }
}

/*
 * This function creates players for the first time
 * 
 * Input: the array of players to be initialized
 * Output: The number of players of the game
 */
int initialize_players(player players[])
{

    //Variable to keep track of how many players are in the game.
    int playerCount = 0;
    printf("\n");

    //Loop to collect names for up to 6 players.
    printf("\nInput an empty string to complete player name input.\n");
    for (size_t i = 0; i < 6; i++)
    {

        //Collecting player names.
        printf("\nPlease enter player name: ");
        fgets(players[i].name, 50, stdin);
        playerCount++;

        //Check to see if a newline is entered. If so, loop is broken.
        if (players[i].name[0] == '\n')
        {
            playerCount--;
            break;
        }
        players[i].numTokensLastCol = 0;
    }

    //Returns the total amount of players initialized.
    return playerCount;
}
