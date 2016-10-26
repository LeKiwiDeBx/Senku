/*
 * score.h
 *
 * Copyright 2016 Le KiWi <jean@antix1>
 *
 */
#ifndef _SCORE_H_
#define _SCORE_H_

#define MAX_CAR_NAME 13

typedef struct s_Score {
	int 	idScore ;
	char 	namePlayer[MAX_CAR_NAME];
	int    	remainingPeg ;
	double 	bonusElapseTime ;
	double 	scoreGame ;
} score;
typedef score *pScore ;

void scoreAdd() ;
void scoreNew() ;
void scoreTest() ;
void scoreSetTimeGame(int ) ;
void scoreSetCalculateBonusElapseTimer(double ) ;
int  scoreGetBonusTimeScore() ;
void scoreSetRemainingPeg(int );
#endif
