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
 *    /____/\__/ /_/|_/_/ |__/|__/_/   [°} présente
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
#include <glib/gprintf.h>
#include "board.h"

/*
 * AND THE SHOW...
*/

/* 
 * And the Widget's land begin here...
 */
GtkWidget *pWindowMain ;

void OnDestroy( GtkWidget *pWidget, gpointer pData ) ;
void OnPlay( GtkWidget *pWidget, gpointer pData ) ;
gboolean OnRadioToggled( GtkWidget* pWidget, GdkEvent *event, gpointer pData ) ;
int which_radio_is_selected( GSList *group ) ;

int
main( int argc, char *argv[] ) {
    
    GtkWidget *pGridMatrix ;
    GtkWidget *lbTitle1, *lbTitle2, *lbl4 ;
    GtkWidget *pVbox ;
    gtk_init( &argc, &argv ) ;

    //  Creation window main
    pWindowMain = gtk_window_new( GTK_WINDOW_TOPLEVEL ) ;
    gtk_window_set_position( GTK_WINDOW( pWindowMain ), GTK_WIN_POS_CENTER ) ;
    gtk_window_set_title( GTK_WINDOW( pWindowMain ), "Senku GTK Beta 2.0" ) ;
    gtk_window_set_default_size( GTK_WINDOW( pWindowMain ), 360, 340 ) ;
    gtk_container_set_border_width( GTK_CONTAINER( pWindowMain ), 10 ) ;
    GtkWidget *pGridMain = gtk_grid_new( ) ;
    gtk_container_add( GTK_CONTAINER( pWindowMain ), pGridMain ) ;

    //    Grille du Senku (provisoire)
    pGridMatrix = gtk_grid_new( ) ;
    gtk_container_add( GTK_CONTAINER( pGridMain ), pGridMatrix ) ;
    gtk_grid_set_row_spacing( GTK_GRID( pGridMatrix ), 5 ) ;
    gtk_grid_set_column_spacing( GTK_GRID( pGridMatrix ), 5 ) ;
//    int i, k ;
//    for (k = 0 ; k < 10 ; k++) {
//        for (i = 0 ; i < 10 ; i++) {
//            lbl4 = gtk_label_new( " O " ) ;
//            gtk_grid_attach( GTK_GRID( pGridMatrix ), lbl4, i, k, 1, 1 ) ;
//        }
//    }
    // matrix avec gtkEvent
    GtkWidget *pMatrix_event = gtk_event_box_new () ;
    gtk_grid_attach (GTK_GRID(pGridMatrix), pMatrix_event, 0, 0, 10, 10);
//    gtk_event_box_set_above_child(GTK_EVENT_BOX(pMatrix_event), TRUE) ;
    int i, k ;
    for (k = 0 ; k < 10 ; k++) {
        for (i = 0 ; i < 10 ; i++) {
            lbl4 = gtk_label_new( " O " ) ;
            gtk_grid_attach( GTK_GRID( pGridMatrix ), lbl4, i, k, 1, 1 ) ;
            gtk_widget_set_events(pMatrix_event, GDK_BUTTON_MOTION_MASK); //"button_press_event"
            g_signal_connect(G_OBJECT(pMatrix_event), "button_press_event", G_CALLBACK(OnDestroy), NULL);
        }
    }
    
    //    Menu droit
    pVbox = gtk_vbox_new( TRUE, 0 ) ;
    gtk_box_set_homogeneous( GTK_BOX( pVbox ), FALSE ) ;
    gtk_box_set_spacing( GTK_BOX( pVbox ), 10 ) ;
    gtk_widget_set_margin_left( GTK_WIDGET( pVbox ), 20 ) ;

    GtkWidget *plbTime = gtk_label_new( "Time:" ) ;
    GtkWidget *plbTimeValue = gtk_label_new( " 0 s" ) ;
    gtk_box_pack_start( GTK_BOX( pVbox ), plbTime, FALSE, FALSE, 10 ) ;
    gtk_box_pack_start( GTK_BOX( pVbox ), plbTimeValue, FALSE, FALSE, 0 ) ;
    gtk_widget_set_halign( GTK_WIDGET( plbTime ), GTK_ALIGN_START ) ;
    gtk_widget_set_halign( GTK_WIDGET( plbTimeValue ), GTK_ALIGN_START ) ;

    GtkWidget *plbPegs = gtk_label_new( "Pegs remaining:" ) ;
    GtkWidget *plbPegsValue = gtk_label_new( " 0 " ) ;
    gtk_box_pack_start( GTK_BOX( pVbox ), plbPegs, FALSE, FALSE, 0 ) ;
    gtk_box_pack_start( GTK_BOX( pVbox ), plbPegsValue, FALSE, FALSE, 0 ) ;
    gtk_widget_set_halign( GTK_WIDGET( plbPegs ), GTK_ALIGN_START ) ;
    gtk_widget_set_halign( GTK_WIDGET( plbPegsValue ), GTK_ALIGN_START ) ;

    GtkWidget *plbBonus = gtk_label_new( "Bonus:" ) ;
    GtkWidget *plbBonusValue = gtk_label_new( " 0 " ) ;
    gtk_box_pack_start( GTK_BOX( pVbox ), plbBonus, FALSE, FALSE, 0 ) ;
    gtk_box_pack_start( GTK_BOX( pVbox ), plbBonusValue, FALSE, FALSE, 0 ) ;
    gtk_widget_set_halign( GTK_WIDGET( plbBonus ), GTK_ALIGN_START ) ;
    gtk_widget_set_halign( GTK_WIDGET( plbBonusValue ), GTK_ALIGN_START ) ;
    gtk_container_add( GTK_CONTAINER( pGridMain ), pVbox ) ;

    /** 
     * label comments game in progress 
     */
    gtk_orientable_set_orientation( GTK_ORIENTABLE( pGridMain ), GTK_ORIENTATION_VERTICAL ) ;
    GtkWidget *pfrComments = gtk_frame_new( NULL ) ;
    gtk_frame_set_label( GTK_FRAME( pfrComments ), "Comments: " ) ;
    GtkWidget *plbComments = gtk_label_new( "Comments in progress..." ) ;
    gtk_container_add( GTK_CONTAINER( pfrComments ), plbComments ) ;
    gtk_widget_set_margin_top( GTK_WIDGET( pfrComments ), 20 ) ;
    gtk_widget_set_halign( GTK_WIDGET( plbComments ), GTK_ALIGN_START ) ;
    gtk_grid_attach( GTK_GRID( pGridMain ), pfrComments, 0, 1, 2, 1 ) ;

    // Button bottom 
    GtkWidget *pHbox = gtk_hbox_new( TRUE, 0 ) ;
    gtk_widget_set_margin_top( GTK_WIDGET( pHbox ), 20 ) ;
    gtk_widget_set_halign( GTK_WIDGET( pHbox ), GTK_ALIGN_END ) ;
    GtkWidget *pButtonUndo = gtk_button_new_with_label( "Undo" ) ;
    gtk_box_pack_start( GTK_BOX( pHbox ), pButtonUndo, FALSE, FALSE, 15 ) ;
    GtkWidget *pButtonQuit = gtk_button_new_with_label( "Quit" ) ;

    gtk_box_pack_end( GTK_BOX( pHbox ), pButtonQuit, TRUE, TRUE, 15 ) ;
    gtk_grid_attach( GTK_GRID( pGridMain ), pHbox, 1, 2, 1, 1 ) ;
    g_signal_connect( G_OBJECT( pWindowMain ), "destroy", G_CALLBACK( OnDestroy ), NULL ) ;
    g_signal_connect( G_OBJECT( pButtonQuit ), "clicked", G_CALLBACK( OnDestroy ), NULL ) ;

    /**
     * Dialog box Menu 
     * 
     */
    GtkWidget *pBoxMenu = gtk_window_new( GTK_WINDOW_TOPLEVEL ) ;
    gtk_window_set_title( GTK_WINDOW( pBoxMenu ), "Shapes choice" ) ;
    gtk_window_set_modal( GTK_WINDOW( pBoxMenu ), TRUE ) ;
    gtk_window_set_position(GTK_WINDOW(pBoxMenu), GTK_WIN_POS_CENTER ) ;
    gtk_window_set_decorated(GTK_WINDOW( pBoxMenu ), FALSE) ;
    gtk_window_set_deletable(GTK_WINDOW( pBoxMenu ), FALSE) ;
    
    gtk_window_set_transient_for( GTK_WINDOW( pBoxMenu ), GTK_WINDOW( pWindowMain ) ) ;
    gtk_window_resize( GTK_WINDOW( pBoxMenu ), 280, 300 ) ;
    
    
    // options
    GtkWidget *pBoxMenuOption = gtk_box_new( GTK_ORIENTATION_VERTICAL, 20 ) ;
    gtk_box_set_homogeneous( GTK_BOX( pBoxMenuOption ), FALSE ) ;
    
    GtkWidget *pfrTitle = gtk_frame_new( NULL ) ;
    gtk_frame_set_label( GTK_FRAME( pfrTitle ), "   Senku ver Beta 1.4  GTK release   (c) 2016   [°} Le KiWi   " ) ;
    GtkWidget *plbTitle = gtk_label_new( "\n\nShapes choice\n______________" ) ;
    gtk_container_add( GTK_CONTAINER( pfrTitle ), plbTitle ) ;
    gtk_box_pack_start( GTK_BOX( pBoxMenuOption ), pfrTitle, TRUE, FALSE, 25 ) ;
    
    
    GtkWidget *radio ;
    radio = gtk_radio_button_new_with_label( NULL, "Shape English" ) ;
    gtk_toggle_button_set_active( GTK_TOGGLE_BUTTON( radio ), TRUE ) ;
    gtk_box_pack_start( GTK_BOX( pBoxMenuOption ), radio, FALSE, FALSE, 0 ) ;
    radio = gtk_radio_button_new_with_label_from_widget( GTK_RADIO_BUTTON( radio ), "Shape German" ) ;
    gtk_box_pack_start( GTK_BOX( pBoxMenuOption ), radio, FALSE, FALSE, 0 ) ;
    radio = gtk_radio_button_new_with_label_from_widget( GTK_RADIO_BUTTON( radio ), "Shape Diamond" ) ;
    gtk_box_pack_start( GTK_BOX( pBoxMenuOption ), radio, FALSE, FALSE, 0 ) ;
    // boutons
    GtkWidget *pBoxMenuButton = gtk_box_new( GTK_ORIENTATION_HORIZONTAL, 20 ) ;
    GtkWidget *pBtnMenuQuit = gtk_button_new_with_label( "Quit" ) ;
    GtkWidget *pBtnMenuPlay = gtk_button_new_with_label( "Play" ) ;
    gtk_box_pack_start( GTK_BOX( pBoxMenuButton ), pBtnMenuPlay, TRUE, TRUE, 20 ) ;
    gtk_box_pack_start( GTK_BOX( pBoxMenuButton ), pBtnMenuQuit, FALSE, FALSE, 20 ) ;
    gtk_box_pack_start( GTK_BOX( pBoxMenuOption ), pBoxMenuButton, TRUE, FALSE, 15 ) ;
    //les signaux
    g_signal_connect( G_OBJECT( pBtnMenuQuit ), "clicked", G_CALLBACK( OnDestroy ), NULL ) ;
    g_signal_connect( G_OBJECT( pBtnMenuPlay ), "clicked",  G_CALLBACK( OnPlay ), radio ) ;
//  g_signal_connect( G_OBJECT( pBoxMenu ), "delete-event", G_CALLBACK( OnRadioToggled ), radio ) ;
    gtk_container_add( GTK_CONTAINER( pBoxMenu ), pBoxMenuOption ) ;
    gtk_widget_show_all( pBoxMenu ) ;
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

void
OnDestroy( GtkWidget *pWidget, gpointer pData ) {
    gtk_main_quit( ) ;
}

void
OnPlay( GtkWidget* pWidget, gpointer pData ) {
    GtkWidget *pWindow = gtk_widget_get_toplevel( GTK_WIDGET( pData ) ) ;
    GtkRadioButton *radio = GTK_RADIO_BUTTON( pData ) ;
    which_radio_is_selected( gtk_radio_button_get_group(GTK_RADIO_BUTTON(radio) ) ) ;
    gtk_widget_show_all( pWindowMain ) ;
    gtk_widget_destroy( pWindow ) ;
}

int
OnRadioToggled( GtkWidget* pWidget, GdkEvent *event, gpointer pData ) {
//    GtkRadioButton *radioBtn =  pData ; /* we passed a radio button as data */
//    which_radio_is_selected( gtk_radio_button_get_group(GTK_RADIO_BUTTON(radioBtn) ) ) ;
//    return FALSE ;
}

int
which_radio_is_selected( GSList *group ) {
    GSList *Group = group ;
    int i = 0, j= 0;
    j = g_slist_length(group) ;
    for ( ; group != NULL ; group = group->next) {
        GtkRadioButton *radio = group->data ;
        i = g_slist_position(Group, group) ;
        if (gtk_toggle_button_get_active( GTK_TOGGLE_BUTTON( radio ) )) {
            g_print("Hello :)\n") ;
            g_print( "DEBUG :: Radio button \"%s\" is the %d active\n", gtk_button_get_label( GTK_BUTTON( radio ) ), j-i) ;
            return (j-i);
        } 
    }
    return 0;
}