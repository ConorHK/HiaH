/*
 * File: game_logic.h
 * Project: f:\Documents\C\Semester 2\Hedgehogs in a Hurry\
 * Created Date: Saturday March 9th 2019 4:44:25 pm
 * Author: ConorHK, thomasreilly1011 (based on template by lpasquale)
 * -----
 * Description: File responsible for initialzing the game.
 */
/*
 * Prints the board
 *
 * Input: the board to be printed.
 */
void print_board(square board[NUM_ROWS][NUM_COLUMNS]);

/*
 * Place tokens in the first column of the board
 *
 * Input: board - a 6x9 array of squares that represents the board
 *        players - the array of the players
 *        numPlayers - the number of players
 */
void place_tokens(square board[NUM_ROWS][NUM_COLUMNS], player players[], int numPlayers);

/*
 *  * Manages the logic of the game
 *
 * Input: board - a 6x9 array of squares that represents the board
 *        players - the array of the players
 *        numPlayers - the number of players
 */
void play_game(square board[NUM_ROWS][NUM_COLUMNS], player players[], int numPlayers);

/*
 * Returns a random number between 1 and 6.
 */
int rollDie();
/*
 * Gives the player the option to move a specified token up or down.
 *
 * Input: board - a 6x9 array of squares that represents the board
 *        current player - the player who's turn it is
 *        dieRoll - the number rolled on the die
 */
void moveVertical(square board[NUM_ROWS][NUM_COLUMNS], player currentPlayer);

/*
 * Gives the player the option to move a specified token up or down.
 *
 * Input: board - a 6x9 array of squares that represents the board
 *        currentPlayer - the player who's turn it is
 *        dieRoll - the number rolled on the die
 *
 */
void moveHorizontal(square board[NUM_ROWS][NUM_COLUMNS], player players[9], int dieRoll);

/*
 * Checks to see if the current player has 3 of their tokens in the final column.
 *
 * Input: board, address of the array of players. 
 * Output: true: if the player has 3 tokens in the final column.
 *          false: if the player hasn't 3 tokens in the final column.
 */
bool winCheck(square board[NUM_ROWS][NUM_COLUMNS], player *players[6]);

/*
 * Check to see if the token is on an obstacle.
 *
 * Input: board, row and column of the token.
 * Output: true: if the token is on an obstacle.
 *          false: if the token is not on an obstacle.
 */
bool obstacleCheck(square board[NUM_ROWS][NUM_COLUMNS], int row, int column);

/*
 * Function that causes a delay.
 *
 * Input: number of seconds to delay by.
 */
void delay(float number_of_seconds);
