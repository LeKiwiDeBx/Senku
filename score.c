/*
 * Créé le 17-10-2016 19:48:05 CEST
 * score.c
 *
 * Copyright 2016 Le KiWi <jean@antix1>
 *
**/
#include <stdio.h>
#include <stdlib.h>
#include <string.h> /* memcpy */
#include "score.h"

#define	SCORE_BEST_OF 10
#define PRN printf("\n")

typedef enum e_typeSort
{
	PEG,
	TIME,
	SCORE
} typeSort;

typedef score tabScore[SCORE_BEST_OF] ;

static tabScore tabSortScore ;
static score cursorCurrentScore ;
static pScore cursorScore ;

static int 		__compareScoreGame (void const* , void const* ) ;
static int  	__writeScore(pScore ) ;
static void		__sortScoreBy(tabScore, typeSort ) ;
static void 	__addBegin() ;
static void 	__addEnd() ;
static void 	__addInside(int ) ;
static void 	__updateCursorScore(score const* ) ;
static double 	__calculateScore(int, double ) ;
static void 	__insertRecord() ;

void
scoreTest(){
	int i ;
	scoreNew();
	score inputScore ;

		inputScore.idScore = 1;
		strcpy(inputScore.namePlayer, "Annus");
		inputScore.remainingPeg = 	2 ;
		inputScore.timeGame = 		257 ;
		inputScore.scoreGame = __calculateScore(inputScore.remainingPeg, inputScore.timeGame ) ;
	__updateCursorScore(&inputScore);
	__insertRecord() ;

		inputScore.idScore = 2;
		strcpy(inputScore.namePlayer, "Elezor");
		inputScore.remainingPeg = 1 ;
		inputScore.timeGame = 257 ;
		inputScore.scoreGame = __calculateScore(inputScore.remainingPeg, inputScore.timeGame ) ;
	__updateCursorScore(&inputScore);
	__insertRecord() ;

		inputScore.idScore = 3;
		strcpy(inputScore.namePlayer, "Promethan");
		inputScore.remainingPeg = 7 ;
		inputScore.timeGame = 1257 ;
		inputScore.scoreGame = __calculateScore(inputScore.remainingPeg, inputScore.timeGame ) ;
	__updateCursorScore(&inputScore);
	__insertRecord() ;

		inputScore.idScore = 4;
		strcpy(inputScore.namePlayer, "Lexithium");
		inputScore.remainingPeg = 3 ;
		inputScore.timeGame = 1118 ;
		inputScore.scoreGame = __calculateScore(inputScore.remainingPeg, inputScore.timeGame ) ;
	__updateCursorScore(&inputScore);
	__insertRecord() ;

		inputScore.idScore = 5;
		strcpy(inputScore.namePlayer, "BarKoff");
		inputScore.remainingPeg = 3 ;
		inputScore.timeGame = 1118 ;
		inputScore.scoreGame = __calculateScore(inputScore.remainingPeg, inputScore.timeGame ) ;
	__updateCursorScore(&inputScore);
	__insertRecord() ;

		inputScore.idScore = 6;
		strcpy(inputScore.namePlayer, "Ka Bahl Sung");
		inputScore.remainingPeg = 	2 ;
		inputScore.timeGame = 		257 ;
		inputScore.scoreGame = __calculateScore(inputScore.remainingPeg, inputScore.timeGame ) ;
	__updateCursorScore(&inputScore);
	__insertRecord() ;

		inputScore.idScore = 7;
		strcpy(inputScore.namePlayer, "Zikazou");
		inputScore.remainingPeg = 1 ;
		inputScore.timeGame = 257 ;
		inputScore.scoreGame = __calculateScore(inputScore.remainingPeg, inputScore.timeGame ) ;
	__updateCursorScore(&inputScore);
	__insertRecord() ;

		inputScore.idScore = 8;
		strcpy(inputScore.namePlayer, "Gie Hun Han");
		inputScore.remainingPeg = 7 ;
		inputScore.timeGame = 1257 ;
		inputScore.scoreGame = __calculateScore(inputScore.remainingPeg, inputScore.timeGame ) ;
	__updateCursorScore(&inputScore);
	__insertRecord() ;

		inputScore.idScore = 9;
		strcpy(inputScore.namePlayer, "Salbruth");
		inputScore.remainingPeg = 3 ;
		inputScore.timeGame = 1118 ;
		inputScore.scoreGame = __calculateScore(inputScore.remainingPeg, inputScore.timeGame ) ;
	__updateCursorScore(&inputScore);
	__insertRecord() ;

		inputScore.idScore = 10;
		strcpy(inputScore.namePlayer, "Fedoria");
		inputScore.remainingPeg = 3 ;
		inputScore.timeGame = 1118 ;
		inputScore.scoreGame = __calculateScore(inputScore.remainingPeg, inputScore.timeGame ) ;
	__updateCursorScore(&inputScore);
	__insertRecord() ;
for (i = 0; i < SCORE_BEST_OF; i++)
	{
		printf("namePlayer:%s\tpegRemain:%d\tscoreGame:%.f\n",tabSortScore[i].namePlayer, tabSortScore[i].remainingPeg, tabSortScore[i].scoreGame);
	}
	printf("\ninputScore of %s with score %.f\n",cursorScore->namePlayer, cursorScore->scoreGame);
		inputScore.idScore = 11;
		strncpy(inputScore.namePlayer, "#Name12Chars",MAX_CAR_NAME-1);
		inputScore.namePlayer[MAX_CAR_NAME] = '\0' ;
		inputScore.remainingPeg = 1 ;
		inputScore.timeGame = 1118 ;
		inputScore.scoreGame = __calculateScore(inputScore.remainingPeg, inputScore.timeGame ) ;
	__updateCursorScore(&inputScore);
	__insertRecord() ;


PRN ;
	for (i = 0; i < SCORE_BEST_OF; i++)
	{
printf("namePlayer:%s\tpegRemain:%d\tscoreGame:%.f\n",tabSortScore[i].namePlayer, tabSortScore[i].remainingPeg, tabSortScore[i].scoreGame);
	}
}

static void
__insertRecord(){
	typeSort orderBy = SCORE ;
	int i ;
	double currentRecordByType, recordFirstByType, recordBeforeLastByType, recordLastByType  ;
	switch (orderBy)
	{
		case SCORE:
			 currentRecordByType = cursorScore->scoreGame ;
			 recordFirstByType = tabSortScore[0].scoreGame ;
			 recordBeforeLastByType = tabSortScore[SCORE_BEST_OF-2].scoreGame ;
			 recordLastByType = tabSortScore[SCORE_BEST_OF-1].scoreGame ;
			break;
		default:
		break;
	}

	if(cursorScore->scoreGame > tabSortScore[0].scoreGame){
		printf("__addBegin\n");
		__addBegin();
	} else if (cursorScore->scoreGame < tabSortScore[SCORE_BEST_OF-2].scoreGame && cursorScore->scoreGame > tabSortScore[SCORE_BEST_OF-1].scoreGame )
	{
		printf("__addEnd\n");
		__addEnd();
	}
	else{
		for (i = 0; i < SCORE_BEST_OF ; i++)
		{
		if(cursorScore->scoreGame <= tabSortScore[i].scoreGame
		&& cursorScore->scoreGame > tabSortScore[i+1].scoreGame )
		{	printf("__addInside %d\n", i+1);
			__addInside(i+1);
			break ;
		}
		}
	}

}

static double
__calculateScore(int remainPeg, double timeBonus){
	return ((double)1000*(6 -remainPeg) + timeBonus) ;
}

static int
__writeScore(pScore self){
	return 0;
}

static void
__sortScoreBy(tabScore tab , typeSort type){
;
}

void
scoreNew(){
	int i ;
	for(i = 0; i < SCORE_BEST_OF; i++){
		tabSortScore[i].idScore = i + 1;
		strcpy(tabSortScore[i].namePlayer,"Unknown") ;
		tabSortScore[i].remainingPeg = 666;
		tabSortScore[i].scoreGame = 2100 ;
		tabSortScore[i].timeGame = 0 ;
	}
	cursorScore = memcpy(&cursorCurrentScore, &tabSortScore[0], sizeof(tabSortScore[0]) );
}
/*
 *
 * name: __addBegin
 * @param
 * @return
 * Insere un enregistrement pointé en debut de tableau temporaire,
 * recopie le tableau trié moins l'enregistrement de fin à la suite du tab temporaire
 * recopie tout le tableau temp dans le tableau trié
 */
static void
__addBegin(){
	tabScore tabTempScore ;
	memcpy(tabTempScore, cursorScore, sizeof(score));
	memcpy(tabTempScore + 1, tabSortScore, (SCORE_BEST_OF -1)*sizeof (score) );
	memcpy(tabSortScore , tabTempScore, sizeof(tabTempScore) );
;}
/*
 *
 * name: __addEnd
 * @param
 * @return
 * Insere un enregistrement au premier endroit de libre avant la fin
 * sinon on ecrase le dernier enregistrement
 */
static void
__addEnd(){
	int i = 0 ;
	while(tabSortScore[i].remainingPeg != 0 && i < SCORE_BEST_OF-1) i++;
	if(i< SCORE_BEST_OF )
		memcpy(&tabSortScore[i], cursorScore, sizeof(score));
;}

/*
 *
 * name: __addInside
 * @param
 * @return
 * Insere dans le tableau des scores un enregistrement d'indice posInsert
 * sauvegarde le debut du tableau avant la position d'insertion du record
 * insere le record
 * recopie la fin du tableau
 */
static void
__addInside(int posInsert){
	tabScore tabTempScore ;
	if(posInsert < SCORE_BEST_OF && posInsert > 0){
		memcpy(tabTempScore, tabSortScore, posInsert*sizeof(score)) ;
		memcpy(tabTempScore + posInsert, cursorScore, sizeof(score));
		memcpy(tabTempScore + posInsert + 1, tabSortScore + posInsert, (SCORE_BEST_OF - posInsert - 1)*sizeof(score));
		memcpy(tabSortScore , tabTempScore, sizeof(tabTempScore) );
	}
;}
/*
 *
 * name: __updateCursorScore
 * @param  inputScore pointeur sur le record à inserer
 * @return
 * met à jour le curseur (data et adresse) sur le record courant
 */
static void
__updateCursorScore(score const* inputScore){
	cursorScore = memcpy(&cursorCurrentScore, inputScore, sizeof(score) );
}

static int
__compareScoreGame(void const *a, void const *b){
   score const *pa = a;
   score const *pb = b;
   return pb->scoreGame - pa->scoreGame;
}
