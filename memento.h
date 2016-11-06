/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   memento.h
 * Author: Administrateur
 *
 * Created on 6 novembre 2016, 19:06
 */

#ifndef MEMENTO_H
#define MEMENTO_H
typedef struct s_mvt {
    int row ;
    int column ;
}mvt;
typedef struct s_memento{
    int idRollback ;        //identifiant du mouvement
    mvt mvtStart ;          //coord depart du mouvement
    mvt mvtEnd ;            //coord arrivée du mouvement
 } memento ;
 
typedef memento* pMemento ;
void mementoNew(mvt , mvt) ;
pMemento mementoGetSaveState() ;

#endif /* MEMENTO_H */
