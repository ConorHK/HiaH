
/*
 * File: c:\Users\Conor\Documents\C\Semester 2\SoftwareEngineering\Hedgehogs in a Hurry\stack.h
 * Project: c:\Users\Conor\Documents\C\Semester 2\SoftwareEngineering\Hedgehogs in a Hurry
 * Created Date: Friday April 12th 2019 12:47:25 pm
 * Author: ConorHK, thomasreilly
 * -----
 * Description: library for stack functions push pop.
 */
#include "game_init.h"
#include "game_logic.h"
#include <stdio.h>
#include <stdlib.h>

//push function that places a token on any position on the board, on top of the previous token.
token * push(square board[NUM_ROWS][NUM_COLUMNS], player play, int row, int column){
    token *curr = board[row][column].stack;
    board[row][column].stack = malloc(sizeof(token));
    board[row][column].stack->col = play.col;
    board[row][column].stack->nextPtr = curr;
    board[row][column].numTokens++;
    return board[row][column].stack;
}

//pop function that takes the topmost token off any position on the board.
token * pop(square board[NUM_ROWS][NUM_COLUMNS], int row, int column){
    token *curr = board[row][column].stack;
    if(curr != NULL){
        board[row][column].stack = curr->nextPtr;
        printf("Stack Data: %d\n", curr->col);
        free(curr);
    }
    board[row][column].numTokens--;
    return board[row][column].stack;
}

void moveToken(square board[NUM_ROWS][NUM_COLUMNS], player currentPlayer, int orow, int ocol, int drow, int dcol){
    pop(board, orow, ocol);
    push(board, currentPlayer, drow, dcol);
}
