/*
 * File: c:\Users\Conor\Documents\C\Semester 2\SoftwareEngineering\Hedgehogs in a Hurry\stack.c
 * Project: c:\Users\Conor\Documents\C\Semester 2\SoftwareEngineering\Hedgehogs in a Hurry
 * Created Date: Friday April 19th 2019 4:06:31 pm
 * Author: ConorHK
 * -----
 * Description: contains push and pop functions to add/remove tokens to any position on the board.
 */

#include "stack.h"
#include <stdlib.h>
#include <stdio.h>

//push function that places a token on any position on the board, on top of the previous token.
token * push(square board[NUM_ROWS][NUM_COLUMNS], player play, int row, int column){
    token *curr = board[row][column].stack;
    board[row][column].stack = malloc(sizeof(token));
    board[row][column].stack->col = play.col;
    board[row][column].stack->nextPtr = curr;
    return board[row][column].stack;
}

//pop function that takes the topmost token off any position on the board.
token * pop(square board[NUM_ROWS][NUM_COLUMNS], int row, int column){
    token *curr = board[row][column].stack;
    if(curr != NULL){
        board[row][column].stack = curr->nextPtr;
        free(curr);
    }
    return board[row][column].stack;
}
