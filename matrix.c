/*
 * Créé le 20-09-2016 15:47:19 CEST
*/
/*
 * matrix.c
 *
 * Copyright 2016 Le KiWi <jean@antix1>
 *
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h> /* memcpy() */
#include "matrix.h"
#include "peg.h"

//~ Matrix matrixEnglish = {  // TEST TEST TEST
	//~ //0  0  2  3  4  5  6  7  8  9  00
	//~ {-0,-0,-0,-0,-0,-0,-0,-0,-0,-0,-0}, //0
	//~ {-0,-0,-0,-0,-0,-0,-0,-0,-0,-0,-0},	//0
	//~ {-0,-0,-0,-0, 0, 0, 0,-0,-0,-0,-0},	//2
	//~ {-0,-0,-0,-0, 0, 0, 0,-0,-0,-0,-0},	//3
    //~ {-0,-0, 0, 0, 0, 0, 0, 0, 0,-0,-0},	//4
    //~ {-0,-0, 0, 0, 0, 1, 1, 0, 0,-0,-0},	//5
    //~ {-0,-0, 0, 0, 0, 0, 0, 0, 0,-0,-0},	//6
    //~ {-0,-0,-0,-0, 0, 0, 0,-0,-0,-0,-0},	//7
	//~ {-0,-0,-0,-0, 0, 0, 0,-0,-0,-0,-0},	//8
	//~ {-0,-0,-0,-0,-0,-0,-0,-0,-0,-0,-0},	//9
	//~ {-0,-0,-0,-0,-0,-0,-0,-0,-0,-0,-0}	//00
//~ } ;

Matrix matrixEnglish = {
	//0  1  2  3  4  5  6  7  8  9  10
	{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1}, //0
	{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},	//1
	{-1,-1,-1,-1, 1, 1, 1,-1,-1,-1,-1},	//2
	{-1,-1,-1,-1, 1, 1, 1,-1,-1,-1,-1},	//3
    {-1,-1, 1, 1, 1, 1, 1, 1, 1,-1,-1},	//4
    {-1,-1, 1, 1, 1, 0, 1, 1, 1,-1,-1},	//5
    {-1,-1, 1, 1, 1, 1, 1, 1, 1,-1,-1},	//6
    {-1,-1,-1,-1, 1, 1, 1,-1,-1,-1,-1},	//7
	{-1,-1,-1,-1, 1, 1, 1,-1,-1,-1,-1},	//8
	{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},	//9
	{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1}	//10
} ;

Matrix matrixGerman = {
	//0  1  2  3  4  5  6  7  8  9  10
	{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1}, //0
	{-1,-1,-1,-1, 1, 1, 1,-1,-1,-1,-1},	//1
	{-1,-1,-1,-1, 1, 1, 1,-1,-1,-1,-1},	//2
	{-1,-1,-1,-1, 1, 1, 1,-1,-1,-1,-1},	//3
    {-1, 1, 1, 1, 1, 1, 1, 1, 1, 1,-1},	//4
    {-1, 1, 1, 1, 1, 0, 1, 1, 1, 1,-1},	//5
    {-1, 1, 1, 1, 1, 1, 1, 1, 1, 1,-1},	//6
    {-1,-1,-1,-1, 1, 1, 1, 1,-1,-1,-1},	//7
	{-1,-1,-1,-1, 1, 1, 1,-1,-1,-1,-1},	//8
	{-1,-1,-1,-1, 1, 1, 1,-1,-1,-1,-1},	//9
	{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1}	//10
} ;

Matrix matrixDiamond = {
	//0  1  2  3  4  5  6  7  8  9  10
	{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1}, //0
	{-1,-1,-1,-1,-1, 1,-1,-1,-1,-1,-1},	//1
	{-1,-1,-1,-1, 1, 1, 1,-1,-1,-1,-1},	//2
	{-1,-1,-1, 1, 1, 1, 1, 1,-1,-1,-1},	//3
    {-1,-1, 1, 1, 1, 1, 1, 1, 1,-1,-1},	//4
    {-1, 1, 1, 1, 1, 0, 1, 1, 1, 1,-1},	//5
    {-1,-1, 1, 1, 1, 1, 1, 1, 1,-1,-1},	//6
    {-1,-1,-1, 1, 1, 1, 1, 1,-1,-1,-1},	//7
	{-1,-1,-1,-1, 1, 1, 1,-1,-1,-1,-1},	//8
	{-1,-1,-1,-1,-1, 1,-1,-1,-1,-1,-1},	//9
	{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1}	//10
} ;

Matrix matrixCopy ;

static void
__displayMatrix(Matrix) ;

static char
*__selectItem(int) ;

static void
__displayLoadChoice(int) ;

static int
__getCoordPegWhereWeGo(int)  ;

static void
__displayPegFromTo(int, int, int, Peg_Direction, int);

/*
 *
 * name: inconnu
 * @param
 * @return
 *
 */
int matrixLoad(int choice){
	if(choice >= 0 && choice <= 4 ){
		__displayLoadChoice(choice) ;
		switch (choice)
		{
			case 1 :
			memcpy(matrixCopy,matrixEnglish,HOR_MAX*VER_MAX*sizeof(int));
			break;
			case 2 :
			memcpy(matrixCopy,matrixGerman,HOR_MAX*VER_MAX*sizeof(int));
			break;
			case 3 :
			memcpy(matrixCopy,matrixDiamond,HOR_MAX*VER_MAX*sizeof(int));
			break;
			case 4 :
			printf("\nGood bye! ;)" );
			exit(EXIT_SUCCESS);
			break;
			default:
			return 0 ;
		}
		pMatrixLoad = matrixCopy ;
		__displayMatrix(matrixCopy) ;
		return 1 ;
	}
	return 0 ;
}
/*
 * test si coord est un Peg selectionnable pour prendre un pion
 * */
int
matrixSelectPeg(int row, int column){
	Peg_Direction direction ;
	int nbMove = 0 ; // nombre de mouvement possible
	int row_arrival, column_arrival;
	int PegGoTo = 0 ; //indice du trou tab_Peg[] ou aller
	pegFlushPeg();
	if(pMatrixLoad[row][column] == 1) {
		for(direction = NORTH ; direction <= WEST; direction++){//determine pour les 4 directions
		row_arrival = row ;// par defaut
		column_arrival = column ;
			switch (direction){
				case NORTH:				//conditions pour prendre un peg
				if(pMatrixLoad[row-1][column] == 1 && pMatrixLoad[row-2][column] == 0)
					row_arrival = row - 2 ;
				break;
				case SOUTH:
				if(pMatrixLoad[row+1][column] == 1 && pMatrixLoad[row+2][column] == 0)
					row_arrival = row + 2 ;
				break;
				case WEST:
				if(pMatrixLoad[row][column-1] == 1 && pMatrixLoad[row][column-2] == 0)
					column_arrival = column - 2 ;
				break;
				case EAST:
				if(pMatrixLoad[row][column+1] == 1 && pMatrixLoad[row][column+2] == 0)
					column_arrival = column + 2 ;
				break;
			}
			if(row_arrival != row || column_arrival != column){
				nbMove++ ;
				PegGoTo = pegBuildPeg(row_arrival,column_arrival, direction);
				__displayPegFromTo(PegGoTo, row, column, direction, nbMove);
			}
			else{
				pegFirstPeg(row, column);
			}
		}
	}
return nbMove ;
}

int
matrixUpdate(Peg_Direction where){
	int i;
	if(where == DEFAULT){
		i = pegReturnDefaultPeg();
		where = tab_Peg[i].direction ;
	}
	else{
		i = __getCoordPegWhereWeGo(where) ;
		if(!i)	{
			printf("Is not a valid direction, do NOTHING ! :((\n");
			__displayMatrix(pMatrixLoad);
			return 1 ;
		}
	}
	int coefRow = 0, coefColumn = 0;
	int row, column ;
	row = tab_Peg[i].coord.row ;
	column = tab_Peg[i].coord.column ;
	switch (where){
		case NORTH:
		coefRow =  1 ;  coefColumn =  0 ;	// coefficient d'effacement
		break;
		case SOUTH:
		coefRow = -1 ;  coefColumn =  0 ;
		break;
		case WEST:
		coefRow =  0 ; 	coefColumn =  1 ;
		break;
		case EAST:
		coefRow =  0 ; 	coefColumn = -1 ;
		break;
		default:
		return 0 ;
	}
	pMatrixLoad[row + coefRow][column + coefColumn] = 0;//erase
	pMatrixLoad[row + 2*coefRow][column + 2*coefColumn] = 0;//erase
	pMatrixLoad[row][column] = 1 ;
	__displayMatrix(pMatrixLoad);
	return 1 ;
}

int
matrixCanMovePeg(){
	Peg_Direction direction ;
	int row, column ;
	for(row = 0; row < HOR_MAX; row++) {
		for(column = 0; column < VER_MAX; column++){
			if(pMatrixLoad[row][column] == 1) {
				for(direction = NORTH ; direction <= WEST; direction++){
				switch (direction){
						case NORTH:				//conditions pour prendre un peg
						if(pMatrixLoad[row-1][column] == 1 && pMatrixLoad[row-2][column] == 0)
							return 1 ;
						break;
						case SOUTH:
						if(pMatrixLoad[row+1][column] == 1 && pMatrixLoad[row+2][column] == 0)
							return 1 ;
						break;
						case WEST:
						if(pMatrixLoad[row][column-1] == 1 && pMatrixLoad[row][column-2] == 0)
							return 1 ;
						break;
						case EAST:
						if(pMatrixLoad[row][column+1] == 1 && pMatrixLoad[row][column+2] == 0)
							return 1 ;
						break;
					}
				}
			}
		}//for column
	}//for row
return 0 ;
}

int
matrixCountRemainPeg(){
	int row, column, count = 0 ;
	for(row = 0; row < HOR_MAX; row++) {
		for(column = 0; column < VER_MAX; column++){
			if(pMatrixLoad[row][column] == 1) count++ ;
		}
	}
	return count ;
}

void
__displayPegFromTo(int whereToGo,int row, int column, Peg_Direction direction, int nbMove){
	char *sDir[] = {"","[N|n]ORTH","[E|e]AST","[S|s]OUTH","[W|w]EST"} ;
	sDir[0] = (nbMove == 1)? "by default, type Enter":"";
	printf("|----------------------------------------------------|\n") ;
	printf("| From Peg [row: %d column: %d] direction: %s\n",row,column,sDir[direction]);
	printf("| => Go to [row: %d column: %d] %s\n",tab_Peg[whereToGo].coord.row,tab_Peg[whereToGo].coord.column, sDir[0]);
	printf("|----------------------------------------------------|\n") ;
}

int
__getCoordPegWhereWeGo(int where){
	int i;
	for (i = 0; i < 5; i++)	{
		if(tab_Peg[i].direction == where)
		return i;
	}
	return 0;
}

void
__displayLoadChoice(int choice){
	switch (choice){
		case 1:
		printf("Loading English\n");
		break;
		case 2:
		printf("Loading German\n");
		break;
		case 3:
		printf("Loading Diamond\n");
		break;
		case 4:
		printf("Quit !\n");
		break;
		default:
		printf("\nGAASP! Can't load shape :(");
	}
}

void
__displayMatrix(Matrix matrix){
	int row, column;
	char *sign ;
	printf("\n%2s", " ");
	for(column = 0 ; column < VER_MAX ; column++){
		printf("%- 3d|", column) ;
	}
	printf("\n");
	for(row = 0 ; row < HOR_MAX ; row++){
	printf("%2d",row);
		for(column = 0; column <VER_MAX ; column++){
			sign = __selectItem(matrix[row][column]);
			printf("%2s|", sign);
			}
	printf("\n");
	}
}

char
*__selectItem(int item){
	char *ret ;
	static int num = 1;
	char buff[255] ;
	switch (item)
	{
		case -1:
		ret = "___";
			break;
		case 0:
		ret = " . ";
			break;
		case 1:
		sprintf(buff, "<%2d>", num++);
		ret = buff ;
		ret = "_O_" ;
			break ;
		case 2:
		ret = "<0>" ;
			break ;
		default:
			break ;
	}
	return ret ;
}
