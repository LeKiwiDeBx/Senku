/*
 *  * File:   memento.h
 * Author: Administrateur
 * Created on 6 novembre 2016, 19:06
 */

#ifndef MEMENTO_H
#define MEMENTO_H

#include "peg.h"

#define NB_UNDO 5	//nombre max de undo géré

typedef struct s_mvt {
    int row ;
    int column ;
} mvt;

typedef struct s_memento{
    int idRollback ;        // identifiant du mouvement
    mvt mvtStart ;          // coord depart du mouvement
    mvt mvtEnd ;            // coord arrivée du mouvement
 } memento ;

typedef memento* pMemento ;

typedef pMemento mementoArrayList[NB_UNDO] ;

pMemento mementoNew(mvt , mvt) ; 		// ecrit la structure
pMemento mementoGetSaveState() ;	// calcul les mvt precedent

pMemento originatorSaveToMemento() ; 		// appel mementoNew qui ecrit la struct
void originatorSet(Peg_Memento pegMemento) ;
void originatorRestoreFromMemento(pMemento pm) ;// appel mementoGetSaveState à l'indice caretakerGetMemento(int)
											// et modifie la matrice

void caretakerAddMemento(pMemento pm) ; // ajoute un pointeur dans mementoArrayList
pMemento caretakerGetMemento(int) ;     // retourne pointeur memento à l'indice donné
                                        // faudra gérer la Liste en detruisant juste après le numero UNDO?

#endif /* MEMENTO_H */
