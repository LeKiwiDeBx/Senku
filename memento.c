
/*
 * File:   memento.c
 * Author: Administrateur
 *
 * Created on 6 novembre 2016, 19:06
 */

#include "memento.h"


static Peg statePeg ;

/**
 * @brief ajoute un memento à la liste
 * @param m
 * @return void
 */
void
caretakerAddMemento(pMemento pm){
    static int i = 0;
    mementoArrayList mArrayList ;
    mArrayList[i] = pm ;
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
void originatorSet(Peg state){
    statePeg = state ;
}

/**
 * @brief demande à memento une reference sur le dernier sauvegardé
 * @return un pointeur sur le memento
 */
pMemento originatorSaveToMemento(const int row, const int column){
    mvt mvtStart, mvtEnd ;
    mvtEnd.row = statePeg.coord.row ;
    mvtEnd.column = statePeg.coord.column ;
    //@TODO implementer le mvtEnd et hop
	mvtStart.row = row ;
	mvtStart.column = column ;
	/* ---> DEBUG     <--- */
	printf("DEBUG mvtStart.row:%d mvtStart.column:%d  mvtEnd.row:%d  mvtEnd.column:%d\n",
	mvtStart.row,mvtStart.column,mvtEnd.row,mvtEnd.column);
	exit(0);
	/* ---> FIN DEBUG <--- */
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
	pMemento pm ;
    return pm;
}
