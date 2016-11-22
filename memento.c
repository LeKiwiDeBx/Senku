
/*
 * File:   memento.c
 * Author: Administrateur
 *
 * Created on 6 novembre 2016, 19:06
 */

#include "memento.h"
#include "matrix.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define SIZE_TAB(array) (sizeof(array)/sizeof(array[0]))

static Peg_Memento statePeg ;
static pMemento pm ;
static mementoArrayList mArrayList = {NULL} ; //tableau de pointeur de memento

/**
 * @brief ajoute un memento à la liste
 * @param m
 * @return void
 */
void
caretakerAddMemento( pMemento pmArray ) {
    int i ;
    mArrayList[NB_UNDO - 1] = NULL ; //sentinelle

    for (i = 0 ; i < NB_UNDO - 1 ; i++) {
        
        if (mArrayList[i] == NULL) {
            mArrayList[i] = pmArray ;
            break ;
        }
        else if(i == NB_UNDO -2) {
            //decalage vers la gauche du tableau --> FIFO
            printf( "FIFO\n" ) ;
            memmove( mArrayList, mArrayList + 1, (NB_UNDO - 2) * sizeof (pMemento) ) ;
            mArrayList[NB_UNDO - 2] = pmArray ;
            break;
        }
    }
    /* ---> DEBUG     <--- */
/*
    int k ;
    for (k = 0 ; k < NB_UNDO -2 && mArrayList[k]!= NULL; k++) {
        printf( "DEBUG caretakerAddMemento:%d %d %d %d %d\n", k,
                mArrayList[k]->mvtStart.row,
                mArrayList[k]->mvtStart.column,
                mArrayList[k]->mvtEnd.row,
                mArrayList[k]->mvtEnd.column ) ;
    }
*/
    /* END OF DEBUG */
}

/**
 * @brief renvoi le memento a un indice donné du UNDO
 * @param un undo cad un retour arriere immediat
 * @return un pointeur sur le memento
 */
pMemento
caretakerGetMemento( int undo ) {
    int j ;
    if (undo) {
        if (!mArrayList[0]) return NULL ;  //liste vide
        for (j = 1 ; j < NB_UNDO ; j++) {
            if (mArrayList[j] == NULL)  {
                if (memcpy( pm, mArrayList[j - 1], sizeof (memento) ) != NULL) {
                   printf( "DEBUG caretakerGetMemento:mArrayList[%d] srow:%d scolumn:%d erow:%d ecolumn:%d\n", j-1,
                            mArrayList[j-1]->mvtStart.row,
                            mArrayList[j-1]->mvtStart.column,
                            mArrayList[j-1]->mvtEnd.row,
                            mArrayList[j-1]->mvtEnd.column ) ;
                   printf( "DEBUG caretakerGetMemento:pm srow:%d scolumn:%d erow:%d ecolumn:%d\n",
                            pm->mvtStart.row,
                            pm->mvtStart.column,
                            pm->mvtEnd.row,
                            pm->mvtEnd.column ) ;
                    mArrayList[j - 1] = NULL ;
                    return pm ;
                }
            }
        }
    }   
    return NULL ;
}

/**
 * @brief positionne la variable static de l'etat à sauver
 * @param state Peg à sauver
 */
void
originatorSet( Peg_Memento state ) {
    statePeg = state ;
}

/**
 * @brief demande à memento une reference sur le dernier sauvegardé
 * @return un pointeur sur le memento
 */
pMemento
originatorSaveToMemento( ) {
    mvt mvtStart, mvtEnd, mvtBetween ;
    mvtEnd.row = statePeg.coordEnd.row ;
    mvtEnd.column = statePeg.coordEnd.column ;
    mvtBetween.row = statePeg.coordBetween.row ;
    mvtBetween.column = statePeg.coordBetween.column ;
    mvtStart.row = statePeg.coordStart.row ;
    mvtStart.column = statePeg.coordStart.column ;
    return mementoNew( mvtStart, mvtBetween, mvtEnd ) ;
}

/**
 * @brief appel mementoGetSaveState à l'indice caretakerGetMemento(int)et modifie la matrice
 * @param le memento à restaurer
 * @return succes ou pas
 */
int 
originatorRestoreFromMemento( pMemento pm ) {
    Peg_Memento state ;
    if(pm != NULL) {
        state = mementoGetSaveState( pm ) ;
        pMatrixLoad[state.coordStart.row][state.coordStart.column] = 1 ;
        pMatrixLoad[state.coordBetween.row][state.coordBetween.column] = 1 ;
        pMatrixLoad[state.coordEnd.row][state.coordEnd.column] = 0 ;
        return 1 ;
    }
    return 0 ;
}

/**
 * @brief calcul les mvt precedent
 * @return un memento que l'on vient de sauver
 */
Peg_Memento
mementoGetSaveState( pMemento pm ) {
/*
    printf( "mementoGetSaveState %d %d %d %d\n",pm->mvtStart.row,  pm->mvtStart.column, pm->mvtEnd.row,  pm->mvtEnd.column ) ;
*/
    statePeg.coordStart.row = pm->mvtStart.row ;
    statePeg.coordStart.column = pm->mvtStart.column ;
    statePeg.coordBetween.row = pm->mvtBetween.row ;
    statePeg.coordBetween.column = pm->mvtBetween.column ;
    statePeg.coordEnd.row = pm->mvtEnd.row ;
    statePeg.coordEnd.column = pm->mvtEnd.column ;
    return statePeg ;
}

/**
 * @brief le memento à créer
 * @param 1 mvt de depart
 * @param 2 mvt de fin
 */
pMemento
mementoNew( mvt mvtStart, mvt mvtBetween, mvt mvtEnd ) {
    static int mvtId = 1 ;
    pm = (pMemento) malloc( sizeof (memento) ) ;
    if (pm != NULL) {
        pm->idRollback = mvtId ;
        pm->mvtStart = mvtStart ;
        pm->mvtBetween = mvtBetween ;
        pm->mvtEnd = mvtEnd ;
        mvtId++ ;
    }
    else {
        exit( EXIT_FAILURE ) ;
    }
    return pm ;
}
