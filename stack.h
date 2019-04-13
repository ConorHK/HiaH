/*
 * File: c:\Users\Conor\Documents\C\Semester 2\SoftwareEngineering\Hedgehogs in a Hurry\stack.h
 * Project: c:\Users\Conor\Documents\C\Semester 2\SoftwareEngineering\Hedgehogs in a Hurry
 * Created Date: Friday April 12th 2019 12:47:25 pm
 * Author: ConorHK, thomasreilly
 * -----
 * Description: library for stack functions push pop.
 */
#include "game_init.h"
#include <stdio.h>
#include <stdlib.h>


//push
token * push(square board[NUM_ROWS][NUM_COLUMNS], token *top){
    token *curr = top;
    top = malloc(sizeof(token));
    top->col = 
}
