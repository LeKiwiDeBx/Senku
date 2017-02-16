/*
 * matrix.h
 *
 * Copyright 2016 Le KiWi <jean@antix1>
 *
 */

#ifndef _MATRIX_H_
#define _MATRIX_H_

#include "peg.h"
#include "memento.h"

/*
 * Constants
 */
#define HOR_MAX 11 /* nb rows    */
#define VER_MAX 11 /* nb columns */
#define PX_FILE "matrix.xml" /* file XML des jeux */
/*
 *	Types & Vars
 */
typedef int Matrix[HOR_MAX][VER_MAX];
int (*pMatrixLoad)[VER_MAX]; //pointeur sur le tableau Matrix multidimensionnel
Matrix matrixCopy;

/**
 * @name typedef struct s_matrixOfBoard
 * @brief structure de la matrice du jeu (shape)
 * @id identifiant unique
 * @char nom humain(!)
 * @pShape pointeur sur un tableau de type Matrix (schema du shape)
 */
typedef struct s_matrixOfBoard {
    int id;
    char *name;
    const Matrix *pShape;
} matrixOfBoard;
/**
 * @brief structure qui contient la matrice (shape) en cours du jeu
 *        de type matrixOfBoard
 */
matrixOfBoard currentMatrixOfBoard;

/*
 *	Functions
 */
int matrixLoad(int);
int matrixSelectPeg(int, int);
int matrixUpdate();
int matrixCanMovePeg();
int matrixCountRemainPeg();
void matrixListMatrix(char **nameShape, int *size);
void matrixRotate(Matrix pMatrixRotate) ;
#endif
