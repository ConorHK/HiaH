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

    //Flags declared for verification checks, which break the loop if triggered.
    bool loopCheck, loopBreak;

    //Four tokens assigned..
    for (size_t i = 0; i < 4; i++)
    {
        //..for each player.
        for (size_t j = 0; j < numPlayers; j++)
        {
            //Verification reset every loop.
            loopCheck = true;
            while (loopCheck == true)
            {
                loopBreak = false;

                //Asking for and collecting user's choice.
                printf("%s, please enter a square: ", players[j].name);
                scanf("%d", &selectedSquare);
                selectedSquare--; //decrementing their choice as arrays start from 0 but the board starts from 1.
                printf("\n");

                //Check to see if input is valid.
                if (selectedSquare < 0 || selectedSquare > 5)
                {
                    puts("Error: Invalid input.");
                    loopBreak == true;
                }

                //Verification check to make sure that the user is placing the token on a square with the minimum number of tokens.
                if ((loopBreak == false) && (board[selectedSquare][0].numTokens == minNumOfTokens) && (board[selectedSquare][0].stack == NULL || board[selectedSquare][0].stack->col != players[j].col))
                {
                    push(board, players[j].col, selectedSquare, 0);
                    printLine();
                    printf("\n");
                    loopCheck = false;
                }

                //If they chose a square which has more tokens than the minNumOfTokens:
                else if (loopBreak == false)
                {
                    //Prints out the valid moves for clarity.
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

                    loopBreak == true;
                }

                //Updates the minimum number of tokens.
                if ((((numPlayers * i) + j + 1) % NUM_ROWS == 0) && loopBreak == false)
                {
                    minNumOfTokens++;
                }
            }

            print_board(board);
        }
    }
}

/*
 * Function that calls all the necessary functions for the game to run.
 * 
 * Input: board - a 6x9 array of squares that represents the board.
 *        players - the array of the players.
 *        numPlayers - the number of players . 
 */

void play_game(square board[NUM_ROWS][NUM_COLUMNS], player players[], int numPlayers)
{
    //Game status is true while the game is still running and false when the game is won or lost.
    bool win;
    int dieRoll;

    //Each loop represents a new round in-game.
    while (win == false)
    {
        //Each loop represents each players go.
        for (int i = 0; i < numPlayers; i++)
        {
            test(board); //REMEMBER TO REMOVE.

            //rollDie() function is stored in dieRoll variable to be passed in future calls.
            dieRoll = rollDie();

            //Players are given the option to move vertically.
            moveVertical(board, players[i]);

            //Token is moved horizontally.
            moveHorizontal(board, players, dieRoll);

            //Check to see if the game has been won.
            win = winCheck(board, &players);

            //Verification check that skips the next person's turn if someone has already won the game.
            if (win == true)
            {
                break;
            }
        }
    }
}

/*
 * Function generates a random number between 1 and 6, and prints out the value.
 * 
 * Output: Random number between 1 and 6.
 */
int rollDie()
{
    //Seed is generated based on time elapsed since 1 Jan 1970.
    srand(time(NULL));

    //Random number is generated and stored in dieRoll.
    int dieRoll = rand() % 6 + 1;

    //Value is printed to console.
    printf("\nDie rolling");
    delay(0.5);
    printf(".");
    delay(0.5);
    printf(".");
    printf(" %d!\n\n", dieRoll);
    delay(1);

    //Value is returned to play_game function.
    return dieRoll;
}

/*
 * Function that gives the player a choice to move their token up or down.
 * 
 * Input: board - a 6x9 array of squares that represents the board.
 *        Player who's turn it is.
 */
void moveVertical(square board[NUM_ROWS][NUM_COLUMNS], player currentPlayer)
{
    //Declaring choice variables.
    int choice;                           // used for choosing whether to move at all or not.
    int rowChoice, colChoice, moveChoice; //used for choosing which token to move and which direction (up/down).

    //Bools declared for use in verification checks to break loop.
    bool loopCheck = true, loopBreak;
    bool loopUpDownCheck = true;

    while (loopCheck == true)
    {
        //Verification check reset every loop.
        loopBreak = false;

        //Asking player if they want to move a token and storing input.
        printf("\n%s, would you like to move one of your tokens up/down?\n", currentPlayer.name);
        printf("1: Yes\n");
        printf("2: No\n");
        printf("\nEnter choice: ");
        scanf("%d", &choice);

        //Switch statement based on their choice:
        switch (choice)
        {
        //YES case:
        case 1:
            //Player is prompted for token co-ordinates and they're stored.
            printf("Please select a token: \n");
            printf("Row: ");
            scanf("%d", &rowChoice);
            rowChoice--; //choices are decremented as arrays start at 0 but the board starts at 1.
            printf("Column: ");
            scanf("%d", &colChoice);
            colChoice--;

            //Verification check to see if their choice is on the board.
            if (colChoice < 0 || colChoice > 8 || rowChoice < 0 || rowChoice > 5)
            {
                printf("\nERROR: Invalid choice.\n\n");
                delay(1);
                print_board(board);
                loopBreak = true;
            }

            //Check to see if the token is stuck on an obstacle, by calling obstacleCheck function.
            if (obstacleCheck(board, rowChoice, colChoice) == true)
            {
                loopBreak = true;
            }

            //Verification check to see if the player has a token of their own on the selected square.
            if ((board[rowChoice][colChoice].stack == NULL) || board[rowChoice][colChoice].stack->col != currentPlayer.col)
            {
                printf("\nERROR: You do not have a token on that space!\n\n");
                delay(1);
                print_board(board);
                loopBreak = true;
            }

            //If all verifications are passed:
            if ((loopBreak == false) && (board[rowChoice][colChoice].stack->col == currentPlayer.col))
            {
                while (loopUpDownCheck == true) //second verification loop.
                {
                    //If their choice is not on the edge of the board:
                    if (!(rowChoice == 0 || rowChoice == 5))
                    {
                        //Player is prompted for input which is subsequently stored.
                        printf("\nWould you like to move the token up or down?\n");
                        printf("1: Up\n");
                        printf("2: Down\n");
                        printf("\nEnter choice: ");
                        scanf("%d", &moveChoice);
                        delay(0.5);
                        loopCheck = false;
                    }

                    //If the choice is in the top row this ensures that the token is only moved down.
                    else if (rowChoice == 0)
                    {
                        printf("\nMoving token down.\n");
                        delay(0.5);
                        moveChoice = 2;
                        loopCheck = false;
                    }
                    //If the choice is in the bottom row this ensures that the token is only moved up.
                    else if (rowChoice == 5)
                    {
                        printf("\nMoving token up.\n");
                        delay(0.5);
                        moveChoice = 1;
                        loopCheck = false;
                    }

                    //Switch statement which pushes and pops from the relevant stacks based on the user's moveChoice.
                    switch (moveChoice)
                    {
                    //UP case:
                    case 1:
                        push(board, board[rowChoice][colChoice].stack->col, (rowChoice - 1), colChoice);
                        pop(board, rowChoice, colChoice);
                        loopUpDownCheck = false;
                        break;
                    //DOWN case:
                    case 2:
                        push(board, board[rowChoice][colChoice].stack->col, (rowChoice + 1), colChoice);
                        pop(board, rowChoice, colChoice);
                        loopUpDownCheck = false;
                        break;
                    //Verification check:
                    default:
                        printf("\nERROR: Invalid input.\n");
                        delay(1);
                        break;
                    }
                }
                print_board(board);
                break;
            //NO case:
            case 2:
                loopCheck = false;
                break;
            //Verification check:
            default:
                printf("ERROR: Invalid input.\n");
                delay(1);
                loopBreak = true;
                break;
            }
        }
    }
}

/*
 * Function that moves a token in the row corresponding to the die roll horizontally.
 * 
 * Input: board - a 6x9 array of squares that represents the board.
 *        Player array.
 *        Value of die roll.
 */
void moveHorizontal(square board[NUM_ROWS][NUM_COLUMNS], player players[9], int dieRoll)
{
    //Declaring variables.
    int tokens = 0, column = 0; //Tokens is used to see how many tokens are in the selected row.
    int choice;
    bool obstacle = false;

    //Declaring bools for verification checks.
    bool loopCheck = true, loopBreak;

    //Loop that checks how many tokens are in the selected row.
    for (int i = 0; i < NUM_COLUMNS; i++)
    {
        if (board[dieRoll - 1][i].numTokens > 0)
        {
            tokens++;
            column = i;
        }
    }

    //If there is more than 1 token on the selected row:
    if (tokens > 1)
    {
        while (loopCheck == true) //verification check.
        {
            loopBreak = false;

            //Player is prompted to selected one token from the multiple in that row.
            printf("\n%d tokens on row %d to choose from! Which column would you like to move from?\n", tokens, dieRoll);
            printf("Enter choice: ");
            scanf("%d", &choice);
            choice--;

            //Verification check.
            if (choice < 0 || choice > 8)
            {
                printf("\nInvalid Input!\n");
                loopBreak = true;
            }

            //Verification check: if there are any tokens on the selected column.
            if (board[dieRoll - 1][choice].numTokens == 0)
            {
                printf("\nThere are no tokens on this tile!\n");
                loopBreak = true;
            }
            //If it passes verification:
            else
            {
                //Check to see if the token is on an obstacle.
                obstacle = obstacleCheck(board, (dieRoll - 1), choice);
                if (obstacle == false) // if not:
                {
                    //Moves the token to the right.
                    printf("\nMoving the token on column %d forward!\n", choice + 1);
                    push(board, board[dieRoll - 1][choice].stack->col, (dieRoll - 1), (choice + 1));
                    pop(board, (dieRoll - 1), choice);
                    printLine();
                    loopCheck = false;
                }
                //Obstacle == true case:
                else
                {
                    loopBreak = true;
                }
            }
        }
    }
    //Verification check.
    else if (tokens == 0)
    {
        printf("\nThere are no tokens on this row!\n");
    }
    //If there is only 1 token on the selected row:
    else
    {
        //Check to see if the token is on an obstacle.
        obstacle = obstacleCheck(board, (dieRoll - 1), column);
        if (column != 8 && obstacle == false) // if not, and if the column isn't the last column.
        {
            //Moves the token to the right.
            printf("\nMoving the token on column %d forward!\n", column + 1);
            push(board, board[dieRoll - 1][column].stack->col, dieRoll - 1, column + 1);
            pop(board, dieRoll - 1, column);
            printLine();
        }
        //Obstacle == true case:
        else
        {
            printf("\nNo tokens available to move.\n");
        }
    }
    printf("\n");
    print_board(board);
    delay(0.5);
}

/*
 * Function that allocates points and checks to see if anyone has won.
 * 
 * Input: board - a 6x9 array of squares that represents the board.
 *        Address of Player array.
 * 
 * Output: bool value saying whether the game has been won or not. 'True' being game has been won.
 */
bool winCheck(square board[NUM_ROWS][NUM_COLUMNS], player *players[6])
{
    //Cycles through players:
    for (size_t j = 0; j < 6; j++)
    {
        //Cycles through rows:
        for (size_t i = 0; i < 6; i++)
        {
            //If the player has a token on the last column..
            if ((board[i][8].stack != NULL) && (players[j]->col == board[i][8].stack->col))
            {
                //.. a point is allocated and the token is popped off the board.
                players[j]->numTokensLastCol++;
                pop(board, i, 8);

                //If the player hasn't won yet it shows how many more points are needed.
                if (players[j]->numTokensLastCol < 3)
                {
                    printf("%s: Your token is home! %d more tokens needed to win.\n\n", players[j]->name, 3 - players[j]->numTokensLastCol);
                }
            }
        }

        //If the player has 3 or more points:
        if (players[j]->numTokensLastCol >= 3)
        {
            //They win and true is returned to play_game function.
            printf("\n\n%s is the winner!\n", *players[j]->name);
            return true;
        }
        //Otherwise game continues.
        else
        {
            return false;
        }
    }
}

/*
 * Function that checks to see if the token is allowed to move.
 * 
 * Input: board - a 6x9 array of squares that represents the board.
 *        Value of row and column the token resides on.
 */
bool obstacleCheck(square board[NUM_ROWS][NUM_COLUMNS], int row, int column)
{
    //If the token on an obstacle square:
    if (board[row][column].type == OBSTACLE)
    {
        //If there is tokens on either side of the obstacle square:
        if (board[row][column + 1].numTokens > 0 || board[row][column - 1].numTokens > 0)
        {
            //False is returned: no obstruction.
            return false;
        }
        //Otherwise token is stuck:
        else
        {
            printf("Your token is stuck on an obstacle!\n");
            return true;
        }
    }
    return false;
}

/*
 * Function that causes a delay in code execution.
 * 
 * Input: Number of seconds to be delayed by.
 */
void delay(float number_of_seconds)
{
    //Converting time into milliseconds:
    float milli_seconds = 1000 * number_of_seconds;

    //Starting the timer:
    clock_t start_time = clock();

    //Looping till required time is not achieved:
    while (clock() < start_time + (int)milli_seconds)
        ;
}

//DONT FORGET TO REMOVE:
void test(square board[NUM_ROWS][NUM_COLUMNS])
{
    int choice;
    int or, oc, dr, dc, col;

    printf("Would you like to place a token?\n1: Yes\n2: No\n");
    scanf("%d", &choice);

    if (choice == 1)
    {
        printf("Enter the destination row & column in the format, and then the color of the token (dr dc col)\n");
        scanf("%d %d %d", &dr, &dc, &col);
        push(board, col, dr - 1, dc - 1);
    }
}