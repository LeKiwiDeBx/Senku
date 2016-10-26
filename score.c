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
static score inputScore ;  /* ONLY TEST */
static int bonusTimeScore = 0 ;
static int remainingPeg = 0 ;

static int 		__compareScoreGame (void const* , void const* ) ;
static void 	__addBegin() ;
static int 		__addEnd() ;
static void 	__addInside(int ) ;
static void 	__updateCursorScore(score const* ) ;
static double 	__calculateScore(int, double ) ;
static int 		__insertRecord(score *) ;
static void 	__setRemainingPeg(int ) ;
static void 	__setNamePlayer(int ) ;
static void 	__setBonusElapseTime(int) ;
static void 	__clean(const char *buffer, FILE *fp);

void
scoreTest(){
	int i ;
	scoreNew();

		//~ inputScore.idScore = 1;
		//~ strcpy(inputScore.namePlayer, "Annus");
		//~ inputScore.remainingPeg = 	2 ;
		//~ inputScore.bonusElapseTime = 		350 ;
	//~ __insertRecord(&inputScore) ;

		//~ inputScore.idScore = 2;
		//~ strcpy(inputScore.namePlayer, "Elezor");
		//~ inputScore.remainingPeg = 1 ;
		//~ inputScore.bonusElapseTime = 150 ;
	//~ __insertRecord(&inputScore) ;

		//~ inputScore.idScore = 3;
		//~ strcpy(inputScore.namePlayer, "Promethan");
		//~ inputScore.remainingPeg = 4 ;
		//~ inputScore.bonusElapseTime = 125 ;
	//~ __insertRecord(&inputScore) ;

		//~ inputScore.idScore = 4;
		//~ strcpy(inputScore.namePlayer, "Lexithium");
		//~ inputScore.remainingPeg = 3 ;
		//~ inputScore.bonusElapseTime = 100 ;
	//~ __insertRecord(&inputScore) ;

		//~ inputScore.idScore = 5;
		//~ strcpy(inputScore.namePlayer, "BarKoff");
		//~ inputScore.remainingPeg = 3 ;
		//~ inputScore.bonusElapseTime = 115;
	//~ __insertRecord(&inputScore) ;

		//~ inputScore.idScore = 6;
		//~ strcpy(inputScore.namePlayer, "Ka Bahl Sung");
		//~ inputScore.remainingPeg = 	2 ;
		//~ inputScore.bonusElapseTime = 260 ;
	//~ __insertRecord(&inputScore) ;

		//~ inputScore.idScore = 7;
		//~ strcpy(inputScore.namePlayer, "Zikazou");
		//~ inputScore.remainingPeg = 1 ;
		//~ inputScore.bonusElapseTime = 260 ;
	//~ __insertRecord(&inputScore) ;

		//~ inputScore.idScore = 8;
		//~ strcpy(inputScore.namePlayer, "Gie Hun Han");
		//~ inputScore.remainingPeg = 4 ;
		//~ inputScore.bonusElapseTime = 125 ;
	//~ __insertRecord(&inputScore) ;

		//~ inputScore.idScore = 9;
		//~ strcpy(inputScore.namePlayer, "Salbruth");
		//~ inputScore.remainingPeg = 3 ;
		//~ inputScore.bonusElapseTime = 115 ;
	//~ __insertRecord(&inputScore) ;

		//~ inputScore.idScore = 10;
		//~ strcpy(inputScore.namePlayer, "Fedoria");
		//~ inputScore.remainingPeg = 3 ;
		//~ inputScore.bonusElapseTime = 100 ;
	//~ __insertRecord(&inputScore) ;

for (i = 0; i < SCORE_BEST_OF; i++)
	{
		printf("namePlayer:%s\tpegRemain:%d\tscoreGame:%.f\n",tabSortScore[i].namePlayer, tabSortScore[i].remainingPeg, tabSortScore[i].scoreGame);
	}

		inputScore.idScore = 11;
		strncpy(inputScore.namePlayer, "#Name12Chars",MAX_CAR_NAME-1);
		inputScore.namePlayer[MAX_CAR_NAME] = '\0' ;
		inputScore.remainingPeg = 11 ;
		inputScore.bonusElapseTime = 325 ;

	if( !__insertRecord(&inputScore) )
		printf("DEBUG:: NOT INSERT %s\n", inputScore.namePlayer) ;


	printf("\ninputScore of %s with score %.f\n",cursorScore->namePlayer, cursorScore->scoreGame);
PRN ;
	for (i = 0; i < SCORE_BEST_OF; i++)
	{
printf("namePlayer:%s\tpegRemain:%d\tscoreGame:%.f\n",tabSortScore[i].namePlayer, tabSortScore[i].remainingPeg, tabSortScore[i].scoreGame);
	}
}

static int
__insertRecord(score *inputScore){
	int i ;
	__updateCursorScore(inputScore);
	//~ printf("namePlayer:%s\tpegRemain:%d\ttimeGame:%.f\n",inputScore->namePlayer,inputScore->remainingPeg,inputScore->bonusElapseTime) ;
	cursorScore->scoreGame = __calculateScore(inputScore->remainingPeg, inputScore->bonusElapseTime ) ;
	if(cursorScore->scoreGame > tabSortScore[0].scoreGame){
		printf("__addBegin\n");
		__setNamePlayer(0);
		__setRemainingPeg(remainingPeg) ;
		__setBonusElapseTime(bonusTimeScore) ;
		__addBegin();
		return 1 ;
	}
	else if(cursorScore->scoreGame < tabSortScore[SCORE_BEST_OF-2].scoreGame
			&& cursorScore->scoreGame > tabSortScore[SCORE_BEST_OF-1].scoreGame){
		printf("__addEnd\n");
		__setBonusElapseTime(bonusTimeScore) ;
		__setRemainingPeg(remainingPeg) ;
		__setNamePlayer( __addEnd() );
		return 1 ;
	}
	else{
		for (i = 0; i < SCORE_BEST_OF-1 ; i++){
			if(cursorScore->scoreGame <= tabSortScore[i].scoreGame
			   && cursorScore->scoreGame > tabSortScore[i+1].scoreGame ){
				 printf("__addInside %d\n", i+1);
				 __setNamePlayer(i);
				 __setBonusElapseTime(bonusTimeScore) ;
				 __setRemainingPeg(remainingPeg) ;
				__addInside(i+1);
				return 1 ;
			}
		}
	}
return 0 ;
}

void
scoreSetCalculateBonusElapseTimer(double elapseTimer){
	/* cast sauvage !!!! :(*/
	int i;
	i = (int) elapseTimer ;
	switch(i){
		case 7:bonusTimeScore+=10;printf("Bonus: + %d points!\n",10);break ;
		case 6:bonusTimeScore+=15;printf("Bonus: + %d points!\n",15);break ;
		case 5:bonusTimeScore+=20;printf("Bonus: + %d points!\n",20);break ;
		case 4:bonusTimeScore+=25;printf("Bonus: + %d points!\n",25);break ;
		case 3:bonusTimeScore+=30;printf("Bonus: + %d points!\n",30);break ;
		case 2:bonusTimeScore+=35;printf("Bonus: + %d points!\n",35);break ;
		default:;
	}
}

int
scoreGetBonusTimeScore(){
	return bonusTimeScore ;
}

void
scoreSetRemainingPeg(int number){
	/*TODO test de l'affectation du cursorScore->remainingPeg */
	remainingPeg = number ;
}

static void
__setBonusElapseTime(int bonus){
	cursorScore->bonusElapseTime = bonus ;
	printf("Bonus  %d\n", bonus);
}

static void
__setRemainingPeg(int remainPeg){
	if(remainPeg)
		cursorScore->remainingPeg = remainPeg ;
}

static void
__setNamePlayer(int pos){
	char chaine[MAX_CAR_NAME] = "";
	printf("DEBUG:: What's Your Fucking name in pos=%d, guy?\n", pos);
	fgets(chaine, sizeof(chaine), stdin);
    __clean(chaine, stdin);
	strncpy(cursorScore->namePlayer, chaine, MAX_CAR_NAME);
}

static void
__clean(const char *buffer, FILE *fp){
    char *p = strchr(buffer,'\n');
    if (p != NULL)
        *p = 0;
    else{
        int c;
        while ((c = fgetc(fp)) != '\n' && c != EOF);
    }
}


static double
__calculateScore(int remainPeg, double timeBonus){
	int pegFloorToCalc = 7 ;
	if(remainPeg < pegFloorToCalc)
		return ((double)1000*(6 -remainPeg) + timeBonus) ;
	else
		return timeBonus ;
}

void
scoreNew(){
	int i ;
	for(i = 0; i < SCORE_BEST_OF; i++){
		tabSortScore[i].idScore = i + 1;
		strcpy(tabSortScore[i].namePlayer,"Unknown") ;
		tabSortScore[i].remainingPeg = 0;
		tabSortScore[i].scoreGame = 0 ;
		tabSortScore[i].bonusElapseTime = 0 ;
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
 * @return la position d'insertion en fin de liste
 * Insere un enregistrement au premier endroit de libre avant la fin
 * sinon on ecrase le dernier enregistrement
 */
static int
__addEnd(){
	int i = 0 ;
	while(tabSortScore[i].remainingPeg != 0 && i < SCORE_BEST_OF-1) i++;
	if(i< SCORE_BEST_OF )
		memcpy(&tabSortScore[i], cursorScore, sizeof(score));
	return i ;
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
