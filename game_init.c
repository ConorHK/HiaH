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
#include <stdbool.h>
#include <stdlib.h>

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
            //Allocates 4 token spaces in memory to each square on the board to hold data on the stacks
            board[i][j].stack = (token *) malloc(sizeof(token)*4);

            board[i][j].stack[0].col = EMPTY;

            //**Initializes each square to 0 tokens.
            board[i][j].numTokens = 0;

            //**Sets initial colour of board to EMPTY
            // board[i][j].stack->col = EMPTY;
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

    //Assigning colours to players:
    bool flag[6];
    for (size_t i = 0; i < 6; i++)
    {
        flag[i] = false;
    }
    for (size_t i = 0; i < playerCount; i++)
    {
        colorSelection(players, flag, i);
    }

    //Returns the total amount of players initialized.
    return playerCount;
}

void colorSelection(player players[], bool flag[], int playerNumb)
{
    int colourChoice;
    char *colours[6] = {"RED", "BLU", "GREEN", "YELLOW", "PINK", "ORANGE"};

reChoose:
    printf("\nPlayer %d: %sPlease select a colour from the list below:\n", playerNumb + 1, players[playerNumb].name);
    for (size_t i = 0; i < 6; i++)
    {
        if (flag[i] != true)
        {
            printf("\t%d: %s\n", i + 1, colours[i]);
        }
        else
        {
            printf("\t   TAKEN\n");
        }
    }
    scanf("%d", &colourChoice);
    if (flag[colourChoice-1] == true)
    {
        printf("\nERROR: Colour already taken.\n");
        goto reChoose;
    }
    switch (colourChoice)
    {
    case 1:
        if (flag[0] == false)
        {
            players[playerNumb].col = RED;
            flag[0] = true;
            break;
        }

    case 2:
        if (flag[1] == false)
        {
            players[playerNumb].col = BLU;
            flag[1] = true;
            break;
        }

    case 3:
        if (flag[2] == false)
        {
            players[playerNumb].col = GREEN;
            flag[2] = true;
            break;
        }

    case 4:
        if (flag[3] == false)
        {
            players[playerNumb].col = YELLOW;
            flag[3] = true;
            break;
        }

    case 5:
        if (flag[4] == false)
        {
            players[playerNumb].col = PINK;
            flag[4] = true;
            break;
        }

    case 6:
        if (flag[5] == false)
        {
            players[playerNumb].col = ORANGE;
            flag[5] = true;
            break;
        }
    }
}