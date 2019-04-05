/*
 * File: game_init.h
 * Project: f:\Documents\C\Semester 2\Hedgehogs in a Hurry\
 * Created Date: Saturday March 9th 2019 4:44:25 pm
 * Author: ConorHK, thomasreilly1011 (based on template by lpasquale) 
 * -----
 * Description: File responsible for initialzing the game.
 */
#include <stdbool.h>
//number of rows of the board
#define NUM_ROWS 6
//number of columns of the board
#define NUM_COLUMNS 9

//types of squares
enum stype
{
    NORMAL,
    OBSTACLE
};

//colors of tokens
enum color
{
    RED,
    BLU,
    GREEN,
    YELLOW,
    PINK,
    ORANGE,
    EMPTY
};

//defines a token.
//Note each token can be associated with a color
typedef struct token
{
    enum color col;

} token;

//Defines a square of the board.
typedef struct square
{
    //A square can be a NORMAL or an OBSTACLE square
    enum stype type;
    //the stack of tokens that can be placed on the board square
    token *stack;
    //The number of tokens of a square.
    int numTokens;
} square;

/*
 * You need to fill this data structure
 * with the information about the player
 * such as a name and a color.
 */
typedef struct player
{
    char name[50];
    enum color col;
    int numTokensLastCol;
} player;

/*
 * This function creates the board for the first time
 * 
 * Input: board - a 6x9 array of squares
 *
 */
void initialize_board(square board[NUM_ROWS][NUM_COLUMNS]);

/*
 * This function creates players for the first time
 * 
 * Input: the array of players to be initialized
 * Output: The number of players of the game
 *
 */
int initialize_players(player players[]);

void colorSelection(player players[], bool flag[], int playerNumb);
