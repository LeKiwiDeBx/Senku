/*
 * board.h
 *
 * Copyright 2016 Le KiWi <jean@antix1>
 *
 */

#ifndef _BOARD_H_
#define _BOARD_H_
#include "matrix.h"
typedef struct s_Board
{ /*TODO test pour le même matrix pour le tableau de score faire en gros Board->set = MatrixLoad */
	Matrix	*set;
} Board;

int boardInit() ;
int boardPlay() ;
#endif
