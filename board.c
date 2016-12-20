/* board.c
 * Créé le 05-09-2016 14:01:44 CEST
 * 
 */

/**
 * headers C
 */
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <math.h>
/**
 * headers GTK/Glib
 */
#include <gtk/gtk.h>
#include <glib.h>
#include <glib/gprintf.h>
/**
 * headers Senku project
 */
#include "board.h"
#include "matrix.h"
#include "timer.h"
#include "score.h"
#include "memento.h"

#ifndef _LINUX_
#define _LINUX_   /* execution de system clear */
#endif

#define IMG_PEG_MOVE    "image/circle_gold32.png"
#define IMG_PEG_SELECT  "image/circle_gold_select32.png"
#define IMG_PEG_DELETE  "image/circle_white32.png"
#define IMG_PEG_BOARD   "image/marble_1.png"
#define NO_MORE_MOVE    "No more move!"
static void
__displayHeader( ) ;
static void
__g_displayHeader( ) ;

static void
__displayMenu( ) ;

static void
__displayResult( int ) ;

static void
__displaySetCoordToSelect( int*, int* ) ;

static int
__displaySetCoordToMove( ) ;

static int
__getMenuChoice( ) ;

static int
__displayPlayAgain( ) ;

static void
__displayTimer( double, double ) ;

static void
__displayBonusTimeScore( ) ;

Board onlyOneBoard ;

//static

typedef struct s_coord {
    int x ;
    int y ;
} Coord ;
Coord eventCoord ;
Coord *pEventCoord ;

typedef enum e_actionSelect {
    ACTION_SELECT_PEG,
    ACTION_SELECT_TAKE_NORTH,
    ACTION_SELECT_TAKE_EAST,
    ACTION_SELECT_TAKE_SOUTH,
    ACTION_SELECT_TAKE_WEST,
    ACTION_SELECT_UNSELECT_PEG = 10,
} actionSelect ;

/* *****************************************************************************
 * And the Widget's land begin here... 
 * ****************************************************************************/
/* fenetre principal application */
GtkWidget *pWindowMain ;
/* grille principale */
GtkWidget *pGridMain ;
/* grille matrice qui contient le shape*/
GtkWidget *pGridMatrix ;
/* boite qui contient les etiquettes indicatrices verticale à droite*/
GtkWidget *pVbox ;
/* label pegs remaining value */
GtkWidget *plbTime = NULL ;
GtkWidget *plbTimeValue = NULL ;
GtkWidget *plbBonus = NULL ;
GtkWidget *plbBonusValue = NULL ;
GtkWidget *plbPegs = NULL ;
GtkWidget *plbPegsValue = NULL ;
GtkWidget *pfrComments = NULL ;
GtkWidget *plbComments = NULL ;
GtkWidget *pBoxMenu = NULL ;
GtkWidget *pHbox = NULL ;
GtkWidget *pButtonUndo = NULL ;
GtkWidget *pButtonQuit = NULL ;
GtkWidget *pfrTitle = NULL ;
GtkWidget *pBoxMenuOption = NULL ;
GtkWidget *plbTitle = NULL ;
GtkWidget *radio = NULL ;
GtkWidget *pBoxMenuButton = NULL ;
GtkWidget *pBtnMenuQuit = NULL ;
GtkWidget *pBtnMenuPlay = NULL ;

/**
 * @brief Appel selection image avec un clic souris
 * @param pWidget boxEvent qui encapsule l'image
 * @param event
 * @param pData une structure qui renferme les coordonnées du click mouse (en unité de matrice)
 */
void
OnSelect( GtkWidget *pWidget, GdkEvent *event, gpointer pData ) ;

/**
 * @brief Appel par le bouton play du menu du choix de shape
 * @param GtkWidget le bouton play
 * @param pData un bouton radion (sert à recuperer le groupe du bouton radio)
 */
void
OnPlay( GtkWidget *pWidget, gpointer pData ) ;

/**
 * @brief Appel pour fin d'application
 * @param pWidget appele par les boutons quit et fermeture fenetre
 * @param pData NULL
 */
void
OnDestroy( GtkWidget *pWidget, gpointer pData ) ;

/**
 * @ Not use (???)
 * @param pWidget
 * @param event
 * @param pData
 * @return 
 */
gboolean
OnRadioToggled( GtkWidget* pWidget, GdkEvent *event, gpointer pData ) ;

/**
 * @ determine quel bouton du groupe à option est utilisé
 * @param group groupe du bouton
 * @return int la position dans le groupe sinon 0
 */
int
which_radio_is_selected( GSList *group ) ;

/**
 * Affiche la matrice dans le pWindowMain
 * @param matrix
 */
void
_g_displayMatrix( Matrix matrix ) ;
/**
 * Met à jour l'affichage de la matrice apres une selection/prise
 * @param action type action et direction
 * @param x coord du clic ligne
 * @param y coord du clic colonne
 */
void
_g_displayUpdateMatrix( actionSelect action, const int x, const int y ) ;
/**
 * affichage du chronometre
 */
gboolean
_g_display_time( gpointer pData ) ;
/**
 * @brief reecrit le texte du label
 * @param pWidget le label
 * @param pData   le texte à écrire
 */
void
_g_labelSet(GtkWidget *pWidget, gpointer pData) ;

int
boardInit( ) {
    scoreInit( ) ;
    //do {
    //	#ifdef _LINUX_
    //		system("clear");
    //        
    //    #endif
    /***********************************************************************
     * __displayHeader() ;
     * function console
     **********************************************************************/

    //  Creation window main
    pWindowMain = gtk_window_new( GTK_WINDOW_TOPLEVEL ) ;
    gtk_window_set_position( GTK_WINDOW( pWindowMain ), GTK_WIN_POS_CENTER ) ;
    gtk_window_set_title( GTK_WINDOW( pWindowMain ), "Senku GTK Alpha 2.0" ) ;
    gtk_window_set_default_size( GTK_WINDOW( pWindowMain ), 360, 340 ) ;
    gtk_container_set_border_width( GTK_CONTAINER( pWindowMain ), 10 ) ;
    /* signal fermeture l'application sur fermeture fenetre principale */
    g_signal_connect( G_OBJECT( pWindowMain ), "destroy", G_CALLBACK( OnDestroy ), NULL ) ;

    // Creation de la grille principale container */
    pGridMain = gtk_grid_new( ) ;
    
    //    Grille du Senku
    pGridMatrix = gtk_grid_new( ) ;
    gtk_container_add( GTK_CONTAINER( pGridMain ), pGridMatrix ) ;
    gtk_grid_set_row_spacing( GTK_GRID( pGridMatrix ), 0 ) ;
    gtk_grid_set_column_spacing( GTK_GRID( pGridMatrix ), 0 ) ;
    
    //Creation grille des valeurs à droite
    GtkWidget *pGridValues = gtk_grid_new() ; 
    plbBonus = gtk_label_new( "Bonus:" ) ;
    plbBonusValue = gtk_label_new( " 0 " ) ;
    plbPegs = gtk_label_new( "Pegs:" ) ;
    plbPegsValue = gtk_label_new( " 0 " ) ;
    plbTime = gtk_label_new( "Time:" ) ;
    plbTimeValue = gtk_label_new( " 0 " ) ;
    gtk_grid_attach( GTK_GRID( pGridValues ), plbBonus,         0, 1, 1, 1 ) ;
    gtk_grid_attach( GTK_GRID( pGridValues ), plbBonusValue,    0, 2, 1, 1 ) ;
    gtk_grid_attach( GTK_GRID( pGridValues ), plbPegs,          0, 3, 1, 1 ) ;
    gtk_grid_attach( GTK_GRID( pGridValues ), plbPegsValue,     0, 4, 1, 1 ) ;
    gtk_grid_attach( GTK_GRID( pGridValues ), plbTime,          0, 5, 1, 1 ) ;
    gtk_grid_attach( GTK_GRID( pGridValues ), plbTimeValue,     0, 6, 1, 1 ) ;
    gtk_grid_set_column_homogeneous( GTK_GRID( pGridMain ), FALSE ) ;
    gtk_container_add( GTK_CONTAINER( pGridMain ), pGridValues ) ;
    
    gtk_container_add( GTK_CONTAINER( pWindowMain ), pGridMain ) ;
    /** 
     * label comments game in progress 
     */
    /* pour pouvoir ajouter en dessous la zone des commentaires*/
    gtk_orientable_set_orientation( GTK_ORIENTABLE( pGridMain ), GTK_ORIENTATION_VERTICAL ) ;
    pfrComments = gtk_frame_new( NULL ) ;
    gtk_frame_set_label( GTK_FRAME( pfrComments ), "Comments: " ) ;
    plbComments = gtk_label_new( "In progress..." ) ;
    gtk_container_add( GTK_CONTAINER( pfrComments ), plbComments ) ;
    gtk_widget_set_margin_top( GTK_WIDGET( pfrComments ), 20 ) ;
    gtk_widget_set_halign( GTK_WIDGET( plbComments ), GTK_ALIGN_START ) ;
    /* ajoute sur deux cellules horizontale du GridMain (soit la totalité) */
    gtk_grid_attach( GTK_GRID( pGridMain ), pfrComments, 0, 1, 2, 1 ) ;

    /* Button bottom  <Undo> et <Quit> */
    pHbox = gtk_box_new( GTK_ORIENTATION_HORIZONTAL, 0 ) ;
    gtk_widget_set_margin_top( GTK_WIDGET( pHbox ), 20 ) ;
    /* on ajoute à partir de la fin */
    gtk_widget_set_halign( GTK_WIDGET( pHbox ), GTK_ALIGN_END ) ;
    pButtonUndo = gtk_button_new_with_label( "Undo" ) ;
    gtk_box_pack_start( GTK_BOX( pHbox ), pButtonUndo, FALSE, FALSE, 15 ) ;
    /* bouton Quit caler à droite */
    pButtonQuit = gtk_button_new_with_label( "Quit" ) ;
    gtk_box_pack_end( GTK_BOX( pHbox ), pButtonQuit, TRUE, TRUE, 15 ) ;
    /* on ajoute les boutons */
    gtk_grid_attach( GTK_GRID( pGridMain ), pHbox, 1, 3, 1, 1 ) ;
    /* les signaux des boutons */

    g_signal_connect( G_OBJECT( pButtonQuit ), "clicked", G_CALLBACK( OnDestroy ), NULL ) ;
    /**
     * @Todo Juste un prototype pour le signal pButtonUndo --> OnUndo
     * @return 
     */
    // g_signal_connect( G_OBJECT( pButtonUndo ), "clicked", G_CALLBACK( OnUndo ), NULL ) ;

    /**
     * Dialog box Menu 
     * choix des shapes modale et sans decoration (style screen splash)
     */
    pBoxMenu = gtk_window_new( GTK_WINDOW_TOPLEVEL ) ;
    gtk_window_set_title( GTK_WINDOW( pBoxMenu ), "Shapes choice" ) ;
    gtk_window_set_modal( GTK_WINDOW( pBoxMenu ), TRUE ) ;
    gtk_window_set_position( GTK_WINDOW( pBoxMenu ), GTK_WIN_POS_CENTER ) ;
    gtk_window_set_decorated( GTK_WINDOW( pBoxMenu ), FALSE ) ;
    gtk_window_set_deletable( GTK_WINDOW( pBoxMenu ), FALSE ) ;
    /* rend la fenetre de choix dependante de la fenetre principale */
    gtk_window_set_transient_for( GTK_WINDOW( pBoxMenu ), GTK_WINDOW( pWindowMain ) ) ;
    gtk_window_resize( GTK_WINDOW( pBoxMenu ), 280, 300 ) ;

    // options
    pBoxMenuOption = gtk_box_new( GTK_ORIENTATION_VERTICAL, 20 ) ;
    gtk_box_set_homogeneous( GTK_BOX( pBoxMenuOption ), FALSE ) ;
    /* sorte d'en tete dans un frame
       ??? peut etre mettre toutes les options dans le frame ???*/
    pfrTitle = gtk_frame_new( NULL ) ;
    gtk_frame_set_label( GTK_FRAME( pfrTitle ), "   Senku GTK Alpha 2.0   (c) 2016   [°} Le KiWi   " ) ;
    plbTitle = gtk_label_new( "\n\nShapes choice\n______________" ) ;
    gtk_container_add( GTK_CONTAINER( pfrTitle ), plbTitle ) ;
    gtk_box_pack_start( GTK_BOX( pBoxMenuOption ), pfrTitle, TRUE, FALSE, 25 ) ;
    /* les boutons radios
     ??? externaliser les textes dans un tableau de char ??? */

    radio = gtk_radio_button_new_with_label( NULL, "Shape English" ) ;
    gtk_toggle_button_set_active( GTK_TOGGLE_BUTTON( radio ), TRUE ) ;
    gtk_box_pack_start( GTK_BOX( pBoxMenuOption ), radio, FALSE, FALSE, 0 ) ;
    radio = gtk_radio_button_new_with_label_from_widget( GTK_RADIO_BUTTON( radio ), "Shape German" ) ;
    gtk_box_pack_start( GTK_BOX( pBoxMenuOption ), radio, FALSE, FALSE, 0 ) ;
    radio = gtk_radio_button_new_with_label_from_widget( GTK_RADIO_BUTTON( radio ), "Shape Diamond" ) ;
    gtk_box_pack_start( GTK_BOX( pBoxMenuOption ), radio, FALSE, FALSE, 0 ) ;
    // boutons <Quit> et <Play> ben oui au moins :)) */
    pBoxMenuButton = gtk_box_new( GTK_ORIENTATION_HORIZONTAL, 20 ) ;
    pBtnMenuQuit = gtk_button_new_with_label( "Quit" ) ;
    pBtnMenuPlay = gtk_button_new_with_label( "Play" ) ;
    /* on ajoute les boutons */
    gtk_box_pack_start( GTK_BOX( pBoxMenuButton ), pBtnMenuPlay, TRUE, TRUE, 20 ) ;
    gtk_box_pack_start( GTK_BOX( pBoxMenuButton ), pBtnMenuQuit, FALSE, FALSE, 20 ) ;
    /* on ajoute box des boutons à la box des menu*/
    gtk_box_pack_start( GTK_BOX( pBoxMenuOption ), pBoxMenuButton, TRUE, FALSE, 15 ) ;
    /* on ajoute les options */
    gtk_container_add( GTK_CONTAINER( pBoxMenu ), pBoxMenuOption ) ;
    //les signaux 
    g_signal_connect( G_OBJECT( pBtnMenuQuit ), "clicked", G_CALLBACK( OnDestroy ), NULL ) ;
    g_signal_connect( G_OBJECT( pBtnMenuPlay ), "clicked", G_CALLBACK( OnPlay ), radio ) ;
    //  g_signal_connect( G_OBJECT( pBoxMenu ), "delete-event", G_CALLBACK( OnRadioToggled ), radio ) ;

    // on se la montre...
    gtk_widget_show_all( pBoxMenu ) ;

    // on lance la boucle infernale
    gtk_main( ) ;
    EXIT_SUCCESS ;

    /***************************************************************************
     * __displayMenu()  ;
     * function console
     **************************************************************************/
    /*********************************************************************
     * __getMenuChoice() ;
     * function console
     * while (!matrixLoad( num = __getMenuChoice( ) )) ;
     */

    /**
     * adresse de la matrice courante (globale)
     * @return 
     */
    onlyOneBoard.set = &currentMatrixOfBoard ;

    /* TODO: code a adapter en GTK
     * boardPlay( ) ;
     *scoreNew( ) ;
     * */

    //} while (__displayPlayAgain( )) ;
    return 1 ;
}

int
boardPlay( ) {
    int row = 0, column = 0, nbMove = 0, remainingPeg = 0 ;
    int *pRow = &row, *pColumn = &column ;
    int canDisplayBonusTimeScore = 0 ;
    double elapseTimer, totalTimer ;
    timerSetStartTimer( ) ;
    timerSetElapseTimer( ) ;
    scoreResetBonusTimeScore( ) ;
    caretakerNew( ) ;
    while (matrixCanMovePeg( )) {
        timerSetElapseTimer( ) ;
        __displaySetCoordToSelect( pRow, pColumn ) ;
        /* Appel de UNDO pour dernier mouvement */
        if (*pRow == -1 || *pColumn == -1) {
            timerSetElapseTimer( ) ;
            if (originatorRestoreFromMemento( caretakerGetMemento( 1 ) )) {
                printf( "You ask [UNDO] the last move!\n" ) ;
                matrixUpdate( UNDO ) ;
            }
            else printf( "There is no action to [UNDO] :( \n" ) ;
            canDisplayBonusTimeScore = 0 ;
        }
            /* selection normale */
        else {
            timerSetElapseTimer( ) ;
            nbMove = matrixSelectPeg( *pRow, *pColumn ) ;
            if (nbMove) {
                if (matrixUpdate( __displaySetCoordToMove( ) ))
                    canDisplayBonusTimeScore = 1 ;
            }
        }
        elapseTimer = timerGetElapseTimer( ) ;
        totalTimer = timerGetTotalTimer( ) ;
        __displayTimer( elapseTimer, totalTimer ) ;
        if (canDisplayBonusTimeScore) {
            scoreSetCalculateBonusElapseTimer( elapseTimer ) ;
            __displayBonusTimeScore( ) ;
        }
        canDisplayBonusTimeScore = 0 ;
    }/* while() */
    timerSetStopTimer( ) ;
    remainingPeg = matrixCountRemainPeg( ) ;
    scoreSetRemainingPeg( remainingPeg ) ;
    __displayResult( remainingPeg ) ;
    return 1 ;
}

void
__displayHeader( ) {
    printf( "\t       __         __ ___ _      ___\n" ) ;
    printf( "\t      / /  ___   / //_(_) | /| / (_)\n" ) ;
    printf( "\t     / /__/ -_) / ,< / /| |/ |/ / /\n" ) ;
    printf( "\t    /____/\\__/ /_/|_/_/ |__/|__/_/   présente\n" ) ;
    printf( "\t\n" ) ;
    printf( "\t       _____            __\n" ) ;
    printf( "\t      / ___/___  ____  / /____  __\n" ) ;
    printf( "\t      \\__ \\/ _ \\/ __ \\/ //_/ / / /\n" ) ;
    printf( "\t     ___/ /  __/ / / / ,< / /_/ /\n" ) ;
    printf( "\t    /____/\\___/_/ /_/_/|_|\\__,_/     (c) 2016\n" ) ;
    printf( "\t\n" ) ;
    printf( "!==  Senku ver Beta 1.3   	    (c) 2016   Le KiWi  ==!\n\n" ) ;
    printf( "\n" ) ;

}

void
__displayMenu( ) {
    printf( "!==\t\t\t\t       \t\t\t\t==!\n" ) ;
    printf( "!==\t\t\t\tM E N U\t\t\t\t==!\n" ) ;
    printf( "!==\t\t\t\t       \t\t\t\t==!\n" ) ;
    printf( "!==\t\t\t# [1] Shape English       \t\t==!\n" ) ;
    printf( "!==\t\t\t# [2] Shape German        \t\t==!\n" ) ;
    printf( "!==\t\t\t# [3] Shape Diamond       \t\t==!\n" ) ;
    printf( "!==\t\t\t# [4] Quit                \t\t==!\n" ) ;
    printf( "!==\t\t\t\t       \t\t\t\t==!\n" ) ;
}

int
__getMenuChoice( ) {
    int num = 0, c ;
    printf( "Enter a number between 1 and 4\n" ) ;
    printf( "Type your choice: " ) ;
    if (!scanf( " %2d[1-4]", &num )) {
        while (((c = getchar( )) != '\n') && c != EOF) ;
    }
    scanf( "%*[^\n]" ) ;
    getchar( ) ; // enleve '\n' restant
    return num ;
}

void
__displaySetCoordToSelect( int *numX, int *numY ) {
    int c ;
    printf( "\nSelect a peg's row and column number format like Xrow Ycol or -1 -1 to UNDO: " ) ;
    while (scanf( " %2i %2i", numX, numY ) != 2 || *numX > 9 || *numY > 9) {
        while (((c = getchar( )) != '\n') && c != EOF) ;
        *numX = 0 ;
        *numY = 0 ;
        printf( "Erreur de saisie ! try again\n" ) ;
        printf( "Select a peg's row and column number format like Xrow Ycol: " ) ;
    }
    scanf( "%*[^\n]" ) ;
    getchar( ) ; // enleve '\n' restant
}

/**
 * 
 * @return retourne le texte de la direction
 */
int
__displaySetCoordToMove( ) {
    char *sDir[] = {"", "NORTH", "EAST", "SOUTH", "WEST", "the first BY DEFAULT", "unknown!"} ;
    char dir ;
    int i = 0 ;
    printf( "\nType the first letter for the direction: " ) ;
    if (!scanf( "%1c", &dir )) {
        int c ;
        printf( "Erreur de saisie !\n" ) ;
        while (((c = getchar( )) != '\n') && c != EOF) ; //vide buffer
        exit( EXIT_FAILURE ) ;
    }
    switch (toupper( dir )) {
    case 'N':
        i = 1 ;
        break ;
    case 'E':
        i = 2 ;
        break ;
    case 'S':
        i = 3 ;
        break ;
    case 'W':
        i = 4 ;
        break ;
    case '\n':
        i = 5 ;
        break ;
    default:
        i = 6 ;
    }
    printf( "You choose direction %s\n", sDir[i] ) ;
    return i ;
}

void
__displayTimer( double elapseTimer, double totalTimer ) {
    printf( "  _\n" ) ;
    printf( " \\ /  Elapsed Time of Reflexion: %2.f sec.\n", elapseTimer ) ;
    printf( " /_\\  Total Time: %2.fmin %02.fsec\n", timerGetMktime( totalTimer )->mkt_min, timerGetMktime( totalTimer )->mkt_sec ) ;
}

static void
__displayBonusTimeScore( ) {
    printf( "\n" ) ;
    printf( "  ~~~\n" ) ;
    printf( " |@ @| Extra Bonus Time: %d\n", scoreGetBonusTimeScore( ) ) ;
    printf( "  (o)\n" ) ;
}

void
__displayResult( int remainingPegs ) {
    printf( "|-------------------------------------------------|\n" ) ;
    if (remainingPegs > 2)
        printf( "  /!\\ NO MORE MOVE Try again... /!\\\n" ) ;
    else if (remainingPegs == 2)
        printf( "  /!\\ NO MORE MOVE The victory is imminent! /!\\\n" ) ;
    else
        printf( "  Oo. Oh Yeaah! You WIN, you are a real Senku .oO\n" ) ;
    printf( "  Remaining Pegs: %d\n", remainingPegs ) ;
    printf( "|-------------------------------------------------|\n" ) ;
}

int
__displayPlayAgain( ) {
    char buffer[] = {'\0'} ;
    printf( "\n|-------------------------------------------------|\n" ) ;
    printf( "| Play again [Yes|No]? : " ) ;
    if (!scanf( "%s", buffer )) {
        int c ;
        printf( "Erreur de saisie !  Press Enter\n" ) ;
        while (((c = getchar( )) != '\n') && c != EOF) ;
    }
    getchar( ) ;
    return ( !strncmp( buffer, "Y", 1 ) || !strncmp( buffer, "y", 1 )) ? 1 : 0 ;
}

void
OnDestroy( GtkWidget *pWidget, gpointer pData ) {
    gtk_main_quit( ) ;
}

void
OnSelect( GtkWidget *pWidget, GdkEvent *event, gpointer pData ) {
    static gboolean firstSelectPeg = TRUE ;
    static Coord pOld = {0, 0} ;
    int remainingPeg = 0 ;
    double elapseTimer, totalTimer ;
    actionSelect action ;
    Coord *p = g_malloc( sizeof (Coord) ) ;
    p = (Coord *) pData ;
    _g_labelSet(plbPegsValue, GINT_TO_POINTER(matrixCountRemainPeg())) ;
    timerSetStartTimer( ) ;
    timerSetElapseTimer( ) ;
//    scoreResetBonusTimeScore( ) ;
    caretakerNew( ) ;
//    g_print( "DEBUG :: Coord Old X:%d Y:%d\n", pOld.x, pOld.y ) ;
//    g_print( "DEBUG :: Coord New X:%d Y:%d\n", p->x, p->y ) ;
    if (matrixCanMovePeg( )) {
        timerSetStartTimer( ) ;
        if (firstSelectPeg) {
            if (matrixSelectPeg( p->x, p->y )) {
                firstSelectPeg = FALSE ;
                timerSetElapseTimer( ) ;
                _g_displayUpdateMatrix( ACTION_SELECT_PEG, p->x, p->y ) ;
                if (pOld.x || pOld.y) { /* unselect si l'ancien si existe */
                    _g_displayUpdateMatrix( ACTION_SELECT_UNSELECT_PEG, pOld.x, pOld.y ) ;
                }
                pOld.x = p->x ;
                pOld.y = p->y ;
            }
        }
        else {//seconde selection cliquée
            if (matrixSelectPeg( pOld.x, pOld.y )) { //si prise possible
                int deltaX = 0, deltaY = 0, sumDelta = 0 ;
                deltaX = pOld.x - p->x ;
                deltaY = pOld.y - p->y ;
                sumDelta = deltaX + deltaY ;
                firstSelectPeg = TRUE ;
//                g_print( "\nDEBUG :: deltaX: %d deltaY: %d sumDelta: %d\n", deltaX, deltaY, sumDelta ) ;
                if(deltaX != deltaY){
                    if(sumDelta == 2)
                        action = (deltaX) ? ACTION_SELECT_TAKE_NORTH : ACTION_SELECT_TAKE_WEST ;
                    else if(sumDelta == -2)
                        action = (deltaX) ? ACTION_SELECT_TAKE_SOUTH : ACTION_SELECT_TAKE_EAST ;
                    if (matrixUpdate( action )) {
                        _g_displayUpdateMatrix( action, p->x, p->y ) ;
                        _g_labelSet(plbPegsValue, GINT_TO_POINTER(matrixCountRemainPeg())) ;
                        pOld.x = p->x ;
                        pOld.y = p->y ;
                        if (matrixSelectPeg( pOld.x, pOld.y )) {
                            firstSelectPeg = FALSE ;
                            _g_displayUpdateMatrix( ACTION_SELECT_PEG, pOld.x, pOld.y ) ;
                        }
                        elapseTimer = timerGetElapseTimer( ) ;
                        scoreSetCalculateBonusElapseTimer( elapseTimer ) ;
                        totalTimer = timerGetTotalTimer( ) ;
                        _g_labelSet(plbBonusValue, GINT_TO_POINTER(scoreGetBonusTimeScore())) ;
                    } 
                    else if (matrixSelectPeg( p->x, p->y )) { //clique changement d'avis
                        firstSelectPeg = FALSE ;
                        _g_displayUpdateMatrix( ACTION_SELECT_UNSELECT_PEG, pOld.x, pOld.y ) ;
                        _g_displayUpdateMatrix( ACTION_SELECT_PEG, p->x, p->y ) ;
                        pOld.x = p->x ;
                        pOld.y = p->y ;
                        totalTimer = timerGetTotalTimer( ) ;
                    }
                    if (!matrixCanMovePeg( )) {
                        remainingPeg = matrixCountRemainPeg( ) ;
                        gtk_label_set_text( GTK_LABEL( plbComments ),  NO_MORE_MOVE ) ;
                        g_timeout_add( 1000, _g_display_time, GINT_TO_POINTER( TRUE ) ) ;
                        timerSetStopTimer( ) ;
                    }
                    
                }
                else if (sumDelta == 0 && (deltaX != -deltaY)) { //on reclic sur le meme que le premier 
                    if (matrixSelectPeg( p->x, p->y )) {         //en excluant la cdtions particuliere sumdelta==0
                        _g_displayUpdateMatrix( ACTION_SELECT_PEG, p->x, p->y ) ;//pour une autre raison (pions coins opposes d'un carre)
                    }
                }
                else { //ni prise ni meme peg
                    g_print( "\nDEBUG :: change selection de depart\n" ) ;
                    firstSelectPeg = FALSE ;
                    if (matrixSelectPeg( p->x, p->y )) {//si une prise possible
                        _g_displayUpdateMatrix( ACTION_SELECT_UNSELECT_PEG, pOld.x, pOld.y ) ;
                        _g_displayUpdateMatrix( ACTION_SELECT_PEG, p->x, p->y ) ;
                        pOld.x = p->x ;
                        pOld.y = p->y ;
                    }
                }
            }
        }
        gtk_widget_show_all( GTK_WIDGET( pGridMain ) ) ;
    }
}

void
_g_labelSet(GtkWidget *pWidget, gpointer pData){
    gchar *display = g_strdup_printf( "%d", GPOINTER_TO_INT(pData) ) ;
    gtk_label_set_text( GTK_LABEL( pWidget ), display ) ;
    g_free( display ) ;
}

void
_g_displayUpdateMatrix( actionSelect action, const int x, const int y ) {
    gint coefRow = 0, coefColumn = 0 ; // coefficient d'effacement
    GtkWidget *imgPegDelete_1 = gtk_image_new_from_file( IMG_PEG_DELETE ) ;
    GtkWidget *imgPegDelete_2 = gtk_image_new_from_file( IMG_PEG_DELETE ) ;
    GtkWidget *imgPegMove = gtk_image_new_from_file( IMG_PEG_MOVE ) ;
    GtkWidget *imgPegUnselect = gtk_image_new_from_file( IMG_PEG_MOVE ) ;
    GtkWidget *imgPegSelect = gtk_image_new_from_file( IMG_PEG_SELECT ) ;
    switch (action) {
    case ACTION_SELECT_PEG:
        gtk_widget_destroy( gtk_grid_get_child_at( GTK_GRID( pGridMatrix ), y, x ) ) ;
        gtk_grid_attach( GTK_GRID( pGridMatrix ), imgPegSelect, y, x, 1, 1 ) ;
        break ;
    case ACTION_SELECT_UNSELECT_PEG:
        gtk_widget_destroy( gtk_grid_get_child_at( GTK_GRID( pGridMatrix ), y, x ) ) ;
        gtk_grid_attach( GTK_GRID( pGridMatrix ), imgPegUnselect, y, x, 1, 1 ) ;
        break ;
    case ACTION_SELECT_TAKE_NORTH:
        coefRow = -1 ;
        coefColumn = 0 ;
        break ;
    case ACTION_SELECT_TAKE_EAST:
        coefRow = 0 ;
        coefColumn = 1 ;
        break ;
    case ACTION_SELECT_TAKE_SOUTH:
        coefRow = 1 ;
        coefColumn = 0 ;
        break ;
    case ACTION_SELECT_TAKE_WEST:
        coefRow = 0 ;
        coefColumn = -1 ;
        break ;
    default: break ;
    }
    if (action != ACTION_SELECT_PEG && action != ACTION_SELECT_UNSELECT_PEG) {
        gtk_widget_destroy( gtk_grid_get_child_at( GTK_GRID( pGridMatrix ), y, x ) ) ;
        gtk_widget_destroy( gtk_grid_get_child_at( GTK_GRID( pGridMatrix ), y - 1 * coefColumn, x - 1 * coefRow ) ) ;
        gtk_widget_destroy( gtk_grid_get_child_at( GTK_GRID( pGridMatrix ), y - 2 * coefColumn, x - 2 * coefRow ) ) ;
        gtk_grid_attach( GTK_GRID( pGridMatrix ), imgPegMove, y, x, 1, 1 ) ;
        gtk_grid_attach( GTK_GRID( pGridMatrix ), imgPegDelete_1, y - 1 * coefColumn, x - 1 * coefRow, 1, 1 ) ;
        gtk_grid_attach( GTK_GRID( pGridMatrix ), imgPegDelete_2, y - 2 * coefColumn, x - 2 * coefRow, 1, 1 ) ;
    }
}

void
OnPlay( GtkWidget* pWidget, gpointer pData ) {
    GtkWidget *pWindow = gtk_widget_get_toplevel( GTK_WIDGET( pData ) ) ;
    GtkRadioButton *radio = GTK_RADIO_BUTTON( pData ) ;
    // equivalent while (!matrixLoad( num = __getMenuChoice( ) )) ;
    if (matrixLoad( which_radio_is_selected( gtk_radio_button_get_group( GTK_RADIO_BUTTON( radio ) ) ) )) {
        _g_displayMatrix( pMatrixLoad ) ;
        gtk_widget_show_all( pWindowMain ) ;
        /**
         * adresse de la matrice courante (globale)
         */
        onlyOneBoard.set = &currentMatrixOfBoard ;
        g_timeout_add( 1000, _g_display_time, GINT_TO_POINTER( FALSE ) ) ;
    }
    gtk_widget_destroy( pWindow ) ;
}

gboolean
_g_display_time( gpointer pData ) {
    static int i = 0 ;
    static gboolean stop = FALSE ;
    int timerStop = GPOINTER_TO_INT( pData ) ;
    stop = (timerStop)? !stop: stop ;
    if (!stop) {
        gchar *display = g_strdup_printf( "%d", i++ ) ;
        gtk_label_set_text( GTK_LABEL( plbTimeValue ), display ) ;
        g_free( display ) ;
        return TRUE ;
    }
    else return FALSE ;
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
    int i = 0, j = 0 ;
    j = g_slist_length( group ) ;
    for ( ; group != NULL ; group = group->next) {
        GtkRadioButton *radio = group->data ;
        i = g_slist_position( Group, group ) ;
        if (gtk_toggle_button_get_active( GTK_TOGGLE_BUTTON( radio ) )) {
            g_print( "Hello :)\n" ) ;
            g_print( "DEBUG :: Radio button \"%s\" is the %d active\n", gtk_button_get_label( GTK_BUTTON( radio ) ), j - i ) ;
            return (j - i) ;
        }
    }
    return 0 ;
}

void
_g_displayMatrix( Matrix matrix ) {
    gint i, k ;
    GtkWidget *imgPeg ;
    GtkWidget * pMatrix_event[HOR_MAX][VER_MAX] ;
    pEventCoord = (Coord *) g_malloc( HOR_MAX * VER_MAX * sizeof (Coord) ) ;
    pEventCoord = &eventCoord ;
    g_print( "DEBUG :: _g_displayMatrix\n" ) ;
    for (k = 0 ; k < HOR_MAX ; k++) {
        for (i = 0 ; i < VER_MAX ; i++) {
            switch (matrix[k][i]) {
            case -1:
                imgPeg = gtk_image_new_from_file( IMG_PEG_BOARD ) ;
                break ;
            case 0:
                imgPeg = gtk_image_new_from_file( IMG_PEG_DELETE ) ;
                break ;
            case 1:
                imgPeg = gtk_image_new_from_file( IMG_PEG_MOVE ) ;
                break ;
            default: ;
            }
            pMatrix_event[k][i] = gtk_event_box_new( ) ;
            gtk_grid_attach( GTK_GRID( pGridMatrix ), pMatrix_event[k][i], i, k, 1, 1 ) ;
            gtk_grid_attach( GTK_GRID( pGridMatrix ), imgPeg, i, k, 1, 1 ) ;
            pEventCoord->x = k ;
            pEventCoord->y = i ;
            g_signal_connect( G_OBJECT( pMatrix_event[k][i] ), "button_press_event", G_CALLBACK( OnSelect ), (gpointer) pEventCoord ) ;
            pEventCoord++ ;
        }
    }
}