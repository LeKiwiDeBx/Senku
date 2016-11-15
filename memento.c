
/*
 * File:   memento.c
 * Author: Administrateur
 *
 * Created on 6 novembre 2016, 19:06
 */

#include "memento.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static Peg_Memento statePeg ;
static pMemento pm ;
static mementoArrayList mArrayList ; //tableau de pointeur de memo
/**
 * @brief ajoute un memento à la liste
 * @param m
 * @return void
 */
void
caretakerAddMemento(pMemento pmArray){
    static int i = 0;
    mArrayList[i] = pmArray ;
    if(i < NB_UNDO){
        mArrayList[i] = pmArray ;
        i++ ;
    }
    else {
        i = NB_UNDO - 1;
        //decalage vers la gauche du tableau --> FIFO
        memmove(mArrayList, mArrayList + 1, (NB_UNDO-1)*sizeof(mementoArrayList));
        mArrayList[i] = pmArray ;
    }
    /* ---> DEBUG     <--- */
     printf("DEBUG caretaker:%d\n",i);
    //exit(0);
    /* END OF DEBUG */
}

/**
 * @brief renvoi le memento a un indice donné du UNDO
 * @param indice de memento en général 1 cad un retour arriere immediat
 * @return un pointeur sur le memento
 */
pMemento
caretakerGetMemento(int index){
    pMemento m ;
    return m;
}
/**
 * @brief positionne la variable static de l'etat à sauver
 * @param state Peg à sauver
 */
void originatorSet(Peg_Memento state){
    statePeg = state ;
}

/**
 * @brief demande à memento une reference sur le dernier sauvegardé
 * @return un pointeur sur le memento
 */
pMemento originatorSaveToMemento(){
    mvt mvtStart, mvtEnd ;
    mvtEnd.row = statePeg.coordEnd.row ;
    mvtEnd.column = statePeg.coordEnd.column ;
    mvtStart.row = statePeg.coordStart.row ;
    mvtStart.column = statePeg.coordStart.column ;
    return mementoNew(mvtStart , mvtEnd) ;
}

/**
 * @brief appel mementoGetSaveState à l'indice caretakerGetMemento(int)et modifie la matrice
 * @param le memento à restaurer
 */
void
originatorRestoreFromMemento(pMemento pm){
    mementoGetSaveState() ;
    //@TODO: ecrire la matrice
}

/**
 * @brief calcul les mvt precedent
 * @return un memento que l'on vient de sauver
 */
pMemento
mementoGetSaveState(){
    pMemento saveState ;
    return saveState ;
}
/**
 * @brief le emento à créer
 * @param 1 mvt de depart
 * @param 2 mvt de fin
 */
pMemento
mementoNew(mvt mvtStart, mvt mvtEnd){
    static mvtId = 1 ;
    pm  = (pMemento) malloc(sizeof(memento)) ;
    if(pm != NULL){
        pm->idRollback = mvtId ;
        pm->mvtStart = mvtStart ;
        pm->mvtEnd = mvtEnd ;
        mvtId++ ;
    } else {
        printf("/nAlloc crash !!!!!!!!!!!!!!!!/n");
        exit(EXIT_FAILURE) ;
    }
    return pm;
}
