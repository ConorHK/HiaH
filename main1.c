/*
 * File: main1.c
 * Project: f:\Documents\C\Semester 2\Hedgehogs in a Hurry\
 * Created Date: Saturday March 9th 2019 4:44:25 pm
 * Author: ConorHK, thomasreilly1011 (based on template by lpasquale) 
 * -----
 * Description: File responsible for initialzing the game.
 */

#include "game_init.h"
#include "game_logic.h"
// #include "game_logic.h"

int main(int argc, char **argv)
{

    //the board is defined as a 2-Dimensional array of squares
    square board[NUM_ROWS][NUM_COLUMNS];

    //an array containing the players (MAX 6 players)
    player players[6];

    //the number of players
    int numPlayers = 0;

    //creates the squares of the board
    initialize_board(board);

    //prints the board
    print_board(board);

    //creates the players
    numPlayers = initialize_players(players);

    print_board(board);

    //asks each player to place their tokens
    //on the first column of the board
    place_tokens(board, players, numPlayers);

    //manages the turns of the game and identifies a winner
    play_game(board, players, numPlayers);

    return 0;
}
