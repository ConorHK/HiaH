/*
 * File: c:\Users\Conor\Documents\C\Semester 2\SoftwareEngineering\Hedgehogs in a Hurry\stack.c
 * Project: c:\Users\Conor\Documents\C\Semester 2\SoftwareEngineering\Hedgehogs in a Hurry
 * Created Date: Friday April 19th 2019 4:06:31 pm
 * Author: ConorHK
 * -----
 * Description:
 */

#include "stack.h"

token * push(square board[NUM_ROWS][NUM_COLUMNS], token *top, player play){
    token *curr = top;
    top = malloc(sizeof(token));
    top->col = play.col; //exchange value
    top->nextPtr = curr;
    return top;
}

token * pop(square board[NUM_ROWS][NUM_COLUMNS], token *top){
    token *curr = top;
    if(curr != NULL){
        top = curr->nextPtr;
        printf("Stack Data: %d\n", curr->col);
        free(curr);
    }
    return top;
}
