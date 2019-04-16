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
void move_token(square dest, square origin){
    dest.stack[dest.numTokens] = origin.stack[origin.numTokens];
    dest.stack[dest.numTokens].col = EMPTY;
    dest.numTokens--;
    origin.numTokens++;
}