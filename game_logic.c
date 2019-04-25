/*
 * File: game_logic.c
 * Project: f:\Documents\C\Semester 2\Hedgehogs in a Hurry\
 * Created Date: Saturday March 9th 2019 4:44:25 pm
 * Author: ConorHK, thomasreilly1011 (based on template by lpasquale) 
 * -----
 * Description: File responsible for initialzing the game.
 */

#include "stack.h"
#include "game_logic.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

void printLine();

/*
 * Returns the first letter associated with the color of the token
 * 
 * Input: t - pointer to a token
 * Output: initial of the color of the token
 */

char print_token(token *t)
{
    if ((*t).col == PINK)
        return 'P';
    if ((*t).col == RED)
        return 'R';
    if ((*t).col == BLU)
        return 'B';
    if ((*t).col == GREEN)
        return 'G';
    if ((*t).col == ORANGE)
        return 'O';
    if ((*t).col == YELLOW)
        return 'Y';
    return '\0';
}

/*
 * Prints the board
 * 
 * Input: the board to be printed. 
 */
void print_board(square board[NUM_ROWS][NUM_COLUMNS])
{
    printf("                THE BOARD\n");
    for (int i = 0; i < NUM_ROWS; i++)
    {

        //prints an horizontal line
        printLine();
        //prints the row number
        printf(" %d ", i + 1);
        char c = '\0';
        //if the square (i,j) is occupied,
        //c is assigned the initial of the color of the token that occupies the square
        for (int j = 0; j < NUM_COLUMNS; j++)
        {
            if (board[i][j].stack != NULL)
            {
                c = print_token(board[i][j].stack);
            }
            //if the square (i,j) is empty
            else
            {
                //c is assigned 'X' if the square represents an obstacle
                if (board[i][j].type == OBSTACLE)
                    c = 'X';
                //c is assigned an empty space otherwise
                else
                    c = ' ';
            }
            printf("| %c ", c);
        }
        printf("|\n");
    }
    printLine();
    //prints the number of the columns at the end of the board
    printf("     1   2   3   4   5   6   7   8   9\n");
}

void printLine()
{
    printf("   -------------------------------------\n");
}

/*
 * Place tokens in the first column of the board
 * 
 * Input: board - a 6x9 array of squares that represents the board
 *        players - the array of the players
 *        numPlayers - the number of players  
 */
void place_tokens(square board[NUM_ROWS][NUM_COLUMNS], player players[], int numPlayers)
{
    //The minimum number of tokens placed on a square in the first column of the board.
    int minNumOfTokens = 0;
    int selectedSquare = 0;

    for (size_t i = 0; i < 4; i++)
    {
        for (size_t j = 0; j < numPlayers; j++)
        {
        step:
            printf("%s, please enter a square: ", players[j].name);
            scanf("%d", &selectedSquare);
            selectedSquare--;
            printf("\n");

            //Check to see if input is valid.
            if (selectedSquare < 0 || selectedSquare > 5)
            {
                puts("Error: Invalid input.");
                goto step;
            }
            /*Verify whether the square selected by the 
            user has the minimum number of tokens and whether it does not 
            contain a token of the same color selected by the player */
            if ((board[selectedSquare][0].numTokens == minNumOfTokens) && (board[selectedSquare][0].stack == NULL || board[selectedSquare][0].stack->col != players[j].col))
            {
                push(board, players[j].col, selectedSquare, 0);
                printLine();
                printf("\n");
            }

            else
            {
                puts("Error: Invalid input.");
                printf("\nValid moves: ");
                for (size_t m = 0; m < 6; m++)
                {
                    if ((board[m][0].numTokens == minNumOfTokens) && (board[m][0].stack == NULL || board[m][0].stack->col != players[j].col))
                    {
                        printf("%d ", m + 1);
                    }
                }
                printf("\n");

                goto step;
            }

            //Updates the minimum number of tokens.
            if (((numPlayers * i) + j + 1) % NUM_ROWS == 0)
            {
                minNumOfTokens++;
            }

            print_board(board);
        }
    }
}

/*
 * Place tokens in the first column of the board
 * 
 * Input: board - a 6x9 array of squares that represents the board
 *        players - the array of the players
 *        numPlayers - the number of players  
 */

void play_game(square board[NUM_ROWS][NUM_COLUMNS], player players[], int numPlayers)
{
    //Game status is true while the game is still running and false when the game is won or lost.
    bool win;
    int dieRoll;

    //Each loop represents a new round ingame.
    while (win == false)
    {
        //Each loop represents each players go.
        for (int i = 0; i < numPlayers; i++)
        {
            dieRoll = rollDie();
            moveVertical(board, players[i]);
            moveHorizontal(board, players, dieRoll);
            win = winCheck(board, &players[i]);
            if (win == true)
            {
                break;
            }
        }
    }
}

int rollDie()
{
    srand(time(NULL));
    int dieRoll = rand() % 6 + 1;
    printf("\nDie rolling");
    delay(0.5);
    printf(".");
    delay(0.5);
    printf(".");
    printf(" %d!\n\n", dieRoll);
    delay(1);
    return dieRoll;
}

void moveVertical(square board[NUM_ROWS][NUM_COLUMNS], player currentPlayer)
{
    int choice;
    int rowChoice, colChoice, moveChoice;

reChoose:
    printf("\n%s, would you like to move one of your tokens up/down?\n", currentPlayer.name);
    printf("1: Yes\n");
    printf("2: No\n");
    printf("\nEnter choice: ");
    scanf("%d", &choice);

    switch (choice)
    {
    case 1:
        printf("Please select a token: \n");
        printf("Row: ");
        scanf("%d", &rowChoice);
        rowChoice--;
        printf("Column: ");
        scanf("%d", &colChoice);
        colChoice--;

        if (colChoice < 0 || colChoice > 8 || rowChoice < 0 || rowChoice > 5)
        {
            printf("\nERROR: Invalid choice.\n\n");
            delay(1);
            print_board(board);
            goto reChoose;
        }

        if ((board[rowChoice][colChoice].stack == NULL) || board[rowChoice][colChoice].stack->col != currentPlayer.col)
        {
            printf("\nERROR: You do not have a token on that space!\n\n");
            delay(1);
            print_board(board);
            goto reChoose;
        }
        if (board[rowChoice][colChoice].stack->col == currentPlayer.col)
        {
        upOrDown:
            if (!(rowChoice == 0 || rowChoice == 5))
            {
                printf("\nWould you like to move the token up or down?\n");
                printf("1: Up\n");
                printf("2: Down\n");
                printf("\nEnter choice: ");
                scanf("%d", &moveChoice);
                delay(0.5);
            }
            else if (rowChoice == 0)
            {
                printf("\nMoving token down.\n");
                delay(0.5);
                moveChoice = 2;
            }
            else if (rowChoice == 5)
            {
                printf("\nMoving token up.\n");
                delay(0.5);
                moveChoice = 1;
            }

            switch (moveChoice)
            {
            case 1:
                push(board, board[rowChoice][colChoice].stack->col, (rowChoice - 1), colChoice);
                pop(board, rowChoice, colChoice);
                break;
            case 2:
                push(board, board[rowChoice][colChoice].stack->col, (rowChoice + 1), colChoice);
                pop(board, rowChoice, colChoice);
                break;
            default:
                printf("\nERROR: Invalid input.\n");
                delay(1);
                goto upOrDown;
                break;
            }
            print_board(board);
            break;
        case 2:
            break;

        default:
            printf("ERROR: Invalid input.\n");
            delay(1);
            goto reChoose;
            break;
        }
    }
}

void moveHorizontal(square board[NUM_ROWS][NUM_COLUMNS], player players[9], int dieRoll)
{
    int tokens = 0, column = 0;
    int choice;
    bool obstacle = false;

    for (int i = 0; i < NUM_COLUMNS; i++)
    {
        if (board[dieRoll - 1][i].numTokens > 0)
        {
            tokens++;
            column = i;
        }
    }

    if (tokens > 1)
    {
    rchoice:
        printf("\n%d tokens on row %d to choose from! Which column would you like to move from?\n", tokens, dieRoll);
        printf("Enter choice: ");
        scanf("%d", &choice);
        choice--;
        if (choice < 0 || choice > 8)
        {
            printf("\nInvalid Input!\n");
            goto rchoice;
        }
        if (board[dieRoll - 1][choice].numTokens == 0)
        {
            printf("\nThere are no tokens on this tile!\n");
            goto rchoice;
        }
        else
        {
            obstacle = obstacleCheck(board, (dieRoll - 1), choice);
            if (obstacle == false)
            {
                printf("\nMoving the token on column %d forward!\n", choice + 1);
                push(board, board[dieRoll - 1][choice].stack->col, (dieRoll - 1), (choice + 1));
                pop(board, (dieRoll - 1), choice); //Remove token from chosen tile
                printLine();
            }
            else
            {
                goto rchoice;
            }
        }
    }
    else if (tokens == 0)
    {
        printf("\nThere are no tokens on this row!\n");
    }
    else
    {
        obstacle = obstacleCheck(board, (dieRoll - 1), column);
        if (column != 8 && obstacle == false)
        {
            printf("\nMoving the token on column %d forward!\n", column + 1);
            push(board, board[dieRoll - 1][column].stack->col, dieRoll - 1, column + 1);
            pop(board, dieRoll - 1, column);
            printLine();
        }
        else
        {
            printf("\nNo tokens available to move.\n");
        }
    }
    printf("\n");
    print_board(board);
    delay(0.5);
}

bool winCheck(square board[NUM_ROWS][NUM_COLUMNS], player *currentPlayer)
{
    for (size_t i = 0; i < 6; i++)
    {
        // printf("\ncurrentPlayer.col = %d\t board col = %d\n", currentPlayer.col, board[i][8].stack->col);
        if ((board[i][8].stack != NULL) && (currentPlayer->col == board[i][8].stack->col))
        {
            ;
            currentPlayer->numTokensLastCol++;
        }
    }
    if (currentPlayer->numTokensLastCol >= 3)
    {
        printf("\n\n%s is the winner!\n", currentPlayer->name);
        return true;
    }
    else
    {
        return false;
    }
}

bool obstacleCheck(square board[NUM_ROWS][NUM_COLUMNS], int row, int column)
{
    if (board[row][column].type == OBSTACLE)
    { //Is the token on an obstacle square
        if (board[row][column + 1].numTokens > 0 || board[row][column - 1].numTokens > 0)
        { //Are there tokens on either side of the obstacle square
            return false;
        }
        else
        {
            printf("Your token is stuck on an obstacle!\n");
            return true;
        }
    }
    return false;
}
void delay(float number_of_seconds)
{
    // Converting time into milliseconds
    float milli_seconds = 1000 * number_of_seconds;

    //Starting the timer
    clock_t start_time = clock();

    // looping till required time is not achieved
    while (clock() < start_time + (int)milli_seconds);
}