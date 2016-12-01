/*
 * senku  ### Jeu de pions solitaire ###
 * main.c
 * Le 03/09/2016
 * Copyright 2016 Le KiWi <jean@antix1>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 *       __         __ ___ _      ___
 *      / /  ___   / //_(_) | /| / (_)
 *     / /__/ -_) / ,< / /| |/ |/ / /
 *    /____/\__/ /_/|_/_/ |__/|__/_/   présente
 *
 *       _____            __
 *      / ___/___  ____  / /____  __
 *      \__ \/ _ \/ __ \/ //_/ / / /
 *     ___/ /  __/ / / / ,< / /_/ /
 *    /____/\___/_/ /_/_/|_|\__,_/     (c) 2016
 *
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <glib.h>
#include "board.h"
/*
  AND THE SHOW...
 */
void OnDestroy( GtkWidget *pWidget, gpointer pData ) ;

int
main( int argc, char *argv[] ) {
    GtkWidget *window ;
    GtkWidget *grid ;
    GtkWidget *lbTitle1, *lbTitle2, *lbl4 ;
    GtkWidget *pVbox ;
    gtk_init( &argc, &argv ) ;

    window = gtk_window_new( GTK_WINDOW_TOPLEVEL ) ;
    gtk_window_set_position( GTK_WINDOW( window ), GTK_WIN_POS_CENTER ) ;
    gtk_window_set_title( GTK_WINDOW( window ), "Senku GTK Beta 2.0" ) ;
    gtk_window_set_default_size( GTK_WINDOW( window ), 360, 340 ) ;

    GtkWidget *pGridMain = gtk_grid_new( ) ;
    gtk_container_add( GTK_CONTAINER( window ), pGridMain ) ;

    //    Grille du Senku
    grid = gtk_grid_new( ) ;
    gtk_container_add( GTK_CONTAINER( pGridMain ), grid ) ;
    gtk_grid_set_row_spacing( GTK_GRID( grid ), 5 ) ;
    gtk_grid_set_column_spacing( GTK_GRID( grid ), 5 ) ;
    int i, k ;
    for (k = 0 ; k < 10 ; k++) {
        for (i = 0 ; i < 10 ; i++) {
            lbl4 = gtk_label_new( " O " ) ;
            gtk_grid_attach( GTK_GRID( grid ), lbl4, i, k, 1, 1 ) ;
        }
    }
    //    Menu droit
    pVbox = gtk_vbox_new( TRUE, 0 ) ;
    GtkWidget *plbTime = gtk_label_new( "Time:" ) ;
    gtk_box_pack_start( GTK_BOX( pVbox ), plbTime, FALSE, FALSE, 0 ) ;
    GtkWidget *plbTimeValue = gtk_label_new( " 0 s" ) ;
    gtk_box_pack_start( GTK_BOX( pVbox ), plbTimeValue, FALSE, FALSE, 0 ) ;

    GtkWidget *plbPegs = gtk_label_new( "Pegs remaining:" ) ;
    gtk_box_pack_start( GTK_BOX( pVbox ), plbPegs, FALSE, FALSE, 0 ) ;
    GtkWidget *plbPegsValue = gtk_label_new( " 0 " ) ;
    gtk_box_pack_start( GTK_BOX( pVbox ), plbPegsValue, FALSE, FALSE, 0 ) ;

    GtkWidget *plbBonus = gtk_label_new( "Bonus:" ) ;
    gtk_box_pack_start( GTK_BOX( pVbox ), plbBonus, FALSE, FALSE, 0 ) ;
    GtkWidget *plbBonusValue = gtk_label_new( " 0 " ) ;
    gtk_box_pack_start( GTK_BOX( pVbox ), plbBonusValue, FALSE, FALSE, 0 ) ;

    gtk_container_add( GTK_CONTAINER( pGridMain ), pVbox ) ;

    // label comments game in progress
    gtk_orientable_set_orientation( GTK_ORIENTABLE( pGridMain ), GTK_ORIENTATION_VERTICAL ) ;
    GtkWidget *plbComments = gtk_label_new( "Comments in progress..." ) ;
    gtk_container_add( GTK_CONTAINER( pGridMain ), plbComments ) ;

    // Bouton bas    
    GtkWidget *pHbox = gtk_hbox_new( TRUE, 0 ) ;
    //    g_object_set (GTK_WIDGET(pHbox), "expand", TRUE, NULL);
    GtkWidget *pButtonUndo = gtk_button_new_with_label( "Undo" ) ;
    gtk_box_pack_start( GTK_BOX( pHbox ), pButtonUndo, TRUE, TRUE, 15 ) ;
    GtkWidget *pButtonQuit = gtk_button_new_with_label( "Quit" ) ;
    gtk_box_pack_end( GTK_BOX( pHbox ), pButtonQuit, TRUE, TRUE, 15 ) ;

    gtk_container_add( GTK_CONTAINER( pGridMain ), pHbox ) ;



    g_signal_connect( G_OBJECT( window ), "destroy", G_CALLBACK( OnDestroy ), NULL ) ;
    gtk_widget_show_all( window ) ;
    gtk_main( ) ;
    EXIT_SUCCESS ;
    /*
        {
        if (boardInit( ))
            printf( "\nGood bye! Thanks for playing this game ;)\n" ) ;
        else
            printf( "\nSorry but Init game Senku FAILURE :( \n" ) ;
        return 0;
        }
     */
}

/**
 * @brief   Arret de la boucle evenementielle   
 */
void
OnDestroy( GtkWidget *pWidget, gpointer pData ) {
    gtk_main_quit( ) ;
}