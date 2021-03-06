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
#include <string.h>

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
        strtok(players[i].name, "\n");
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

//Function that lets users select a colour.
void colorSelection(player players[], bool flag[], int playerNumb)
{
    //Declaring variables to store the user's colour choice and each of the options.
    int colourChoice;
    char *colours[6] = {"RED", "BLUE", "GREEN", "YELLOW", "PINK", "ORANGE"};

    //Declaring variables for loop break.
    int loopBreak = 0;
    bool loopFlag = false;

    //Loop for error check.
    while (loopBreak == 0)
    {
        //Resetting loopFlag to false after previous loop.
        loopFlag = false;
        
        //Displaying available colours for user to choose from and stores their input.
        printf("\nPlayer %d: %s\nPlease select a colour from the list below:\n", playerNumb + 1, players[playerNumb].name);
        for (size_t i = 0; i < 6; i++)
        {
            if (flag[i] != true) //if the flag is false then the colour hasn't been taken and its printed in the menu.
            {
                printf("\t%d: %s\n", i + 1, colours[i]);
            }
            else
            {
                printf("\t   TAKEN\n");
            }
        }
        printf("\nEnter choice: ");
        scanf("%d", &colourChoice);
        
        //Validation check to see if the choice is valid.
        if (flag[colourChoice - 1] == true)
        {
            printf("\nERROR: Colour already taken.\n");
            loopFlag = true;
        }

        //If so, then the colour is assigned to the user. There's a case for every possible colour choice.
        if (loopFlag == false)
        {
            switch (colourChoice)
            {
            case 1:
                if (flag[0] == false)
                {
                    players[playerNumb].col = RED;
                    flag[0] = true;
                    loopBreak = 1;
                    break;
                }

            case 2:
                if (flag[1] == false)
                {
                    players[playerNumb].col = BLU;
                    flag[1] = true;
                    loopBreak = 1;
                    break;
                }

            case 3:
                if (flag[2] == false)
                {
                    players[playerNumb].col = GREEN;
                    flag[2] = true;
                    loopBreak = 1;
                    break;
                }

            case 4:
                if (flag[3] == false)
                {
                    players[playerNumb].col = YELLOW;
                    flag[3] = true;
                    loopBreak = 1;
                    break;
                }

            case 5:
                if (flag[4] == false)
                {
                    players[playerNumb].col = PINK;
                    flag[4] = true;
                    loopBreak = 1;
                    break;
                }

            case 6:
                if (flag[5] == false)
                {
                    players[playerNumb].col = ORANGE;
                    flag[5] = true;
                    loopBreak = 1;
                    break;
                }
            }
        }
    }
}