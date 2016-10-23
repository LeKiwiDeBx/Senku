/*
 * Créé le 05-09-2016 14:01:44 CEST
*/
/*
 * board.c
 */

#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <math.h>

#include "board.h"
#include "matrix.h"
#include "timer.h"
#include "score.h"

#ifndef _LINUX_
#define _LINUX_   /* execution de system clear */
#endif

static void
__displayHeader() ;

static void
__displayMenu() ;

static void
__displayResult(int) ;

static void
__displaySetCoordToSelect(int*, int*) ;

static int
__displaySetCoordToMove() ;

static int
__getMenuChoice() ;

static int
__displayPlayAgain() ;

static void
__displayTimer(double , double ) ;

int
boardInit(){
	do {
	#ifdef _LINUX_
		system("clear");
	#endif
		__displayHeader() ;
		__displayMenu()  ;
		/* DEBUG +++++++++++++++++++++++++++++++*/
		scoreTest();
		exit(EXIT_SUCCESS);
		/* END OF DEBUG +++++++++++++++++++++++++++++++*/
		while(!matrixLoad(__getMenuChoice() ) );
		boardPlay();
	}while ( __displayPlayAgain() ) ;
	return 1 ;
}

int
boardPlay(){
	int row = 0, column = 0, nbMove = 0 ;
	int *pRow = &row , *pColumn = &column;
	timerSetStartTimer();
	timerSetElapseTimer() ;
		while( matrixCanMovePeg() ){
			timerSetElapseTimer() ;
			__displaySetCoordToSelect(pRow, pColumn) ;
			timerSetElapseTimer() ;
			nbMove = matrixSelectPeg(*pRow, *pColumn) ;
			if(nbMove){
				matrixUpdate(__displaySetCoordToMove());
			}
			__displayTimer(timerGetElapseTimer(), timerGetTotalTimer() );
		}
	timerSetStopTimer();
	__displayResult( matrixCountRemainPeg() );
	return 1;
}

void
__displayHeader() {
printf("\t       __         __ ___ _      ___\n");
printf("\t      / /  ___   / //_(_) | /| / (_)\n");
printf("\t     / /__/ -_) / ,< / /| |/ |/ / /\n");
printf("\t    /____/\\__/ /_/|_/_/ |__/|__/_/   présente\n");
printf("\t\n");
printf("\t       _____            __\n");
printf("\t      / ___/___  ____  / /____  __\n");
printf("\t      \\__ \\/ _ \\/ __ \\/ //_/ / / /\n");
printf("\t     ___/ /  __/ / / / ,< / /_/ /\n");
printf("\t    /____/\\___/_/ /_/_/|_|\\__,_/     (c) 2016\n");
printf("\t\n");
printf("!==  Senku ver Beta 1.1	   	    (c) 2016   Le KiWi  ==!\n\n");
printf("\n");

}

void
__displayMenu(){
	printf("!==\t\t\t\t       \t\t\t\t==!\n");
	printf("!==\t\t\t\tM E N U\t\t\t\t==!\n");
	printf("!==\t\t\t\t       \t\t\t\t==!\n");
	printf("!==\t\t\t# [1] Shape English       \t\t==!\n");
	printf("!==\t\t\t# [2] Shape German        \t\t==!\n");
	printf("!==\t\t\t# [3] Shape Diamond       \t\t==!\n");
	printf("!==\t\t\t# [4] Quit                \t\t==!\n");
	printf("!==\t\t\t\t       \t\t\t\t==!\n");
}

int
__getMenuChoice(){
	int num = 0;int c;
	printf("\nYour choice: ");
		if (!scanf(" %2d[1-4]", &num)) {
			while ( ((c = getchar()) != '\n') && c != EOF);
			printf("\nEnter a number between 1 and 4! try again");
		}
	scanf("%*[^\n]");
	getchar();  // enleve '\n' restant
	return num ;
}

void
__displaySetCoordToSelect(int *numX, int *numY){
	int c;
	printf("\nSelect a peg's row and column number format like Xrow Ycol: ");
	while ( scanf(" %2i %2i", numX, numY)!=2 || *numX > 9 || *numY > 9) {
		while ( ((c = getchar()) != '\n') && c != EOF) ;
		*numX = 0 ; *numY = 0 ;
		printf("Erreur de saisie ! try again\n");
		printf("Select a peg's row and column number format like Xrow Ycol: ");
	}
	scanf("%*[^\n]");
	getchar();  // enleve '\n' restant
}

int
__displaySetCoordToMove(){
	char *sDir[] = {"","NORTH","EAST","SOUTH","WEST","the first BY DEFAULT", "unknown!"} ;
	char dir ;
	int i = 0 ;
	printf("\nType the first letter for the direction: ");
	if (!scanf("%1c", &dir)) {
		int c;
		printf("Erreur de saisie !\n");
		while ( ((c = getchar()) != '\n') && c != EOF); //vide buffer
		exit(EXIT_FAILURE) ;
	}
	switch (toupper(dir))
	{
		case 'N':
		i = 1 ;
		break;
		case 'E':
		i = 2 ;
		break;
		case 'S':
		i = 3 ;
		break;
		case 'W':
		i = 4 ;
		break;
		case '\n':
		i = 5 ;
		break;
		default:
		i = 6 ;
	}
	printf("You choose direction %s\n", sDir[i]) ;
	return i;
}

void
__displayTimer(double elapseTimer, double totalTimer){
	printf("  _\n");
	printf(" \\ /  Elapsed Time of Reflexion: %2.f sec.\n",elapseTimer) ;
	printf(" /_\\  Total Time: %2.fmin %02.fsec\n",timerGetMktime(totalTimer)->mkt_min, timerGetMktime(totalTimer)->mkt_sec);
}

void
__displayResult(int remainingPegs){
	printf("|------------------------------------------------|\n");

	if(remainingPegs > 2)
	printf("  /!\\ NO MORE MOVE :( Try again... /!\\\n");
	else if(remainingPegs == 2)
	printf("  /!\\ NO MORE MOVE :/ The victory is imminent! /!\\\n");
	else
	printf(" Oo. Oh Yeaah! You WIN, you are a real Senku :)) .oO\n");

	printf("   ==> Score is remaining Pegs : %d <==\n",remainingPegs);
	printf("|------------------------------------------------|\n");
}

int
__displayPlayAgain(){
	char buffer[] = {'\0'} ;
	printf("\n|----------------------------------------|\n");
	printf("  Play again [Yes|No]? : ");
	if (!scanf("%s", buffer)) {
		int c;
		printf("Erreur de saisie !  Press Enter\n");
		while ( ((c = getchar()) != '\n') && c != EOF);
	}
	getchar();
	return ( !strncmp(buffer,"Y",1 )  || !strncmp(buffer,"y",1 )  )? 1:0;
}

