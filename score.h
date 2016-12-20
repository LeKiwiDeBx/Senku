/*
 * score.h
 *
 * Copyright 2016 Le KiWi <jean@antix1>
 *
 */
#ifndef _SCORE_H_
#define _SCORE_H_

#define MAX_CAR_NAME 13
#define MAX_SEC_BONUS 1 //debug:: 7 valeur originale
#define MIN_SEC_BONUS 0  //debug:: 2 valeur originale

typedef struct s_Score {
	int 	idScore ;
	char 	namePlayer[MAX_CAR_NAME];
	int    	remainingPeg ;
	double 	bonusElapseTime ;
	double 	scoreGame ;
} score;
typedef score *pScore ;

void scoreAdd() ;
void scoreInit() ;
void scoreNew() ;
void scoreSetTimeGame(int ) ;
void scoreSetCalculateBonusElapseTimer(double ) ;
int  scoreGetBonusTimeScore() ;
void scoreResetBonusTimeScore() ;
void scoreSetRemainingPeg(int );
#endif
