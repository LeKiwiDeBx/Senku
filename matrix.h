/*
 * matrix.h
 *
 * Copyright 2016 Le KiWi <jean@antix1>
 *
 */

#ifndef _MATRIX_H_
#define _MATRIX_H_

/*
 * Constants
*/
#define HOR_MAX 11 /* nb rows    */
#define VER_MAX 11 /* nb columns */

/*
 *	Types & Vars
*/
typedef int Matrix[HOR_MAX][VER_MAX] ;
int (*pMatrixLoad)[VER_MAX] ; //pointeur sur le tableau Matrix multidimensionnel


typedef struct s_matrixOfBoard{
	int id ;
	char *name ;
	Matrix *pShape ;
} matrixOfBoard;
matrixOfBoard currentMatrixOfBoard ;
/*
 *	Functions
*/
int matrixLoad(int) ;
int matrixSelectPeg(int, int) ;
int matrixUpdate()  ;
int matrixCanMovePeg() ;
int matrixCountRemainPeg() ;

#endif
