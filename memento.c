
/*
 * File:   memento.c
 * Author: Administrateur
 *
 * Created on 6 novembre 2016, 19:06
 */

#include "memento.h"

/**
 * @brief ajoute un memento à la liste
 * @param m
 * @return void
 */
void
caretakerAddMemento(pMemento m){
    static int i = 0;
    mementoArrayList mArrayList ;
    mArrayList[i] = m ;
}
            
/**
 * @brief renvoi le memento a un indice donné du UNDO
 * @param indice de memento en général 1 cad un retour arriere immediat
 * @return un pointeur sur le memento
 */
pMemento
caretakerGetMemento(int){
    pMemento m ;
    return m;
}

/**
 * @brief demande à memento une reference sur le dernier sauvegardé
 * @return un pointeur sur le memento
 */
pMemento originatorSaveToMemento(){
    mvt mvtStart, mvtEnd ;
    return mementoNew(mvtStart , mvtEnd) ;
}

/**
 * @brief appel mementoGetSaveState à l'indice caretakerGetMemento(int)et modifie la matrice
 * @param le memento à restaurer
 */
void
originatorRestoreFromMemento(pMemento){
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
void 
mementoNew(mvt mvtStart, mvt mvtEnd){
    ;
}