/*
 * Créé le 20-09-2016 15:47:19 CEST
 */
/*
 * matrix.c
 *
 * Copyright 2016 Le KiWi <jean@antix1>
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h> /* memcpy() */
#include "matrix.h"
#include "peg.h"
#include "memento.h"
#include "xfile.h"
/**
 * headers GTK/Glib
 */
#include <gtk/gtk.h>
#include <glib.h>

/**
 * structure du noeud matrix selectionné de matrix.xml 
 */
typedef struct s_NodeMatrix {
    char * name ;
    Matrix data ;
} NodeMatrix ;
NodeMatrix *pCurrentNodeMatrix ;
NodeMatrix currentNodeMatrix ;

static void
__displayMatrix( Matrix ) ;

static char
*__selectItem( int ) ;

/*
static void
__displayPegFromTo(int, int, int, Peg_Direction, int);
 */

static int
__getCoordPegWhereWeGo( int ) ;

/**
 * @brief rotation de la matrice de 90°
 * @param pMatrixRotate le pointeur sur la matrice à faire tourner
 * @comment merci le web pour ces fucks d'indices :)
 */
void
matrixRotate( Matrix pMatrixRotate ) {
    int tmp = 0 ;
    int n = HOR_MAX, i, j ; //matrice carrée
    for (i = 0 ; i < n / 2 ; i++)
        for (j = i ; j < n - i - 1 ; j++) {
            tmp = pMatrixRotate[i][j] ;
            pMatrixRotate[i][j] = pMatrixRotate[n - j - 1][i] ;
            pMatrixRotate[n - j - 1][i] = pMatrixRotate[n - 1 - i][n - 1 - j] ;
            pMatrixRotate[n - 1 - i][n - 1 - j] = pMatrixRotate[j][n - 1 - i] ;
            pMatrixRotate[j][n - 1 - i] = tmp ;
        }
}

/**
 * @brief liste les matrix shape du fichier xml
 * @param ns tableau pour recueillir les noms des shapes
 * @param size nombre de shapes trouvées
 */
void
matrixListMatrix( char **ns, int *size ) {
    const char * rqst = "//matrix/name/text()" ;
    char * bufferNs[128] ;
    int k = 0 ;
    void *pXfile = xfileNew( PX_FILE ) ;
    xfileRead( pXfile, bufferNs, rqst ) ;
    while (bufferNs[*size]) (*size)++ ;
    for (k = 0 ; k < *size ; k++) ns[k] = bufferNs[k] ;
}

/*
 *
 * @brief: Charge la matrice
 * @param int choice numéro choisit de selection du shape
 * @return 1 si Ok, 0 si Nok
 *
 */
int
matrixLoad( int choice ) {
    void* pXfile ;
    char * bufferNames[128] ;
    char * bufferMatrix[255] ;
    char * bufferName[128] ;
    pXfile = xfileNew( PX_FILE ) ;
    int i = 0, k = 0 ;
    /** On veut tous les noms */
    xfileRead( pXfile, bufferNames, "//matrix/name/text()" ) ;
    char * nameShape[128] = {NULL} ;
    while (bufferNames[i] != NULL) i++ ;
    nameShape[0] = g_strdup( "Unknown" ) ;
    for (k = 0 ; k < i ; k++) nameShape[k + 1] = g_strdup( bufferNames[k] ) ;
    /** on veut les valeurs du matrix choisi */
    xfileRead( pXfile, bufferMatrix, g_strdup_printf( "//matrix[%d]/row/column/text()", choice ) ) ;
    i = 0 ;
    char c ;
    int j, value ;
    Matrix xmlMatrix ;
    for (j = 0 ; j < VER_MAX ; j++) {
        for (i = 0 ; i < HOR_MAX ; i++) { //les colonnes de la ligne
            c = *bufferMatrix[j]++ ;
            value = atoi( &c ) ;
            xmlMatrix[j][i] = (value == 0 || value == 1) ? value : -1 ;
        }
    }
    /** On veut le nom de la matrice */
    xfileRead( pXfile, bufferName, g_strdup_printf( "//matrix[%d]/name/text()", choice ) ) ;
    currentMatrixOfBoard.pShape = &xmlMatrix ;
    currentMatrixOfBoard.name = g_strdup( nameShape[choice] ) ;
    currentMatrixOfBoard.id = choice ;
    if (memcpy( &matrixCopy, currentMatrixOfBoard.pShape, HOR_MAX * VER_MAX * sizeof (int) ))
        pMatrixLoad = matrixCopy ;
    //		__displayMatrix(matrixCopy) ;
    return 1 ;
}

/*
 * test si coord est un Peg selectionnable pour prendre un pion
 * */
int
matrixSelectPeg( int row, int column ) {
    Peg_Direction direction ;
    int nbMove = 0 ; // nombre de mouvement possible
    int row_arrival, column_arrival ;
    int PegGoTo = 0 ; //indice du trou tab_Peg[] ou aller
    pegFlushPeg( ) ;
    if (pMatrixLoad[row][column] == 1) {
        for (direction = NORTH ; direction <= WEST ; direction++) {//determine pour les 4 directions
            row_arrival = row ; // par defaut
            column_arrival = column ;
            switch (direction) {
            case NORTH: //conditions pour prendre un peg
                if (pMatrixLoad[row - 1][column] == 1 && pMatrixLoad[row - 2][column] == 0)
                    row_arrival = row - 2 ;
                break ;
            case SOUTH:
                if (pMatrixLoad[row + 1][column] == 1 && pMatrixLoad[row + 2][column] == 0)
                    row_arrival = row + 2 ;
                break ;
            case WEST:
                if (pMatrixLoad[row][column - 1] == 1 && pMatrixLoad[row][column - 2] == 0)
                    column_arrival = column - 2 ;
                break ;
            case EAST:
                if (pMatrixLoad[row][column + 1] == 1 && pMatrixLoad[row][column + 2] == 0)
                    column_arrival = column + 2 ;
                break ;
            case DEFAULT:case CENTER:case UNDO:
            default:
                ;
                break ;
            }
            if (row_arrival != row || column_arrival != column) {
                nbMove++ ;
                PegGoTo = pegBuildPeg( row_arrival, column_arrival, direction ) ;
                //__displayPegFromTo(PegGoTo, row, column, direction, nbMove);
            }
            else {
                pegFirstPeg( row, column ) ;
            }
        }
    }
    return nbMove ;
}

int
matrixUpdate( Peg_Direction where ) {
    int i ;
    int coefRow = 0, coefColumn = 0 ;
    int row, column ;
    if (where == DEFAULT) {
        i = pegReturnDefaultPeg( ) ;
        where = tab_Peg[i].direction ;
    }
    else if (where == UNDO) {
        return 0 ;
    }
    else {
        i = __getCoordPegWhereWeGo( where ) ;
        if (!i) return 0 ; //Is not a valid direction, do NOTHING !
    }
    row = tab_Peg[i].coord.row ;
    column = tab_Peg[i].coord.column ;
    switch (where) {
    case NORTH:
        coefRow = 1 ;
        coefColumn = 0 ; // coefficient d'effacement
        break ;
    case SOUTH:
        coefRow = -1 ;
        coefColumn = 0 ;
        break ;
    case WEST:
        coefRow = 0 ;
        coefColumn = 1 ;
        break ;
    case EAST:
        coefRow = 0 ;
        coefColumn = -1 ;
        break ;
    case NO_MOVE:
        row = column = coefRow = coefColumn = 0 ;
    default:
        return 0 ;
    }
    pMatrixLoad[row][column] = 1 ;
    pMatrixLoad[row + coefRow][column + coefColumn] = 0 ; //erase
    pMatrixLoad[row + 2 * coefRow][column + 2 * coefColumn] = 0 ; //
    //mecanisme memento UNDO:: memorisation
    Peg_Memento pegMemento = {
        {row + 2 * coefRow, column + 2 * coefColumn},
        {row + 1 * coefRow, column + 1 * coefColumn},
        {row, column}
    } ;
    originatorSet( pegMemento ) ;
    caretakerAddMemento( originatorSaveToMemento( ) ) ;
    //	__displayMatrix(pMatrixLoad);
    return 1 ;
}

int
matrixCanMovePeg( ) {
    Peg_Direction direction ;
    int row, column ;
    for (row = 0 ; row < HOR_MAX ; row++) {
        for (column = 0 ; column < VER_MAX ; column++) {
            if (pMatrixLoad[row][column] == 1) {
                for (direction = NORTH ; direction <= WEST ; direction++) {
                    switch (direction) {//conditions pour prendre un peg
                    case NORTH:
                        if (pMatrixLoad[row - 1][column] == 1 && pMatrixLoad[row - 2][column] == 0)
                            return 1 ;
                        break ;
                    case SOUTH:
                        if (pMatrixLoad[row + 1][column] == 1 && pMatrixLoad[row + 2][column] == 0)
                            return 1 ;
                        break ;
                    case WEST:
                        if (pMatrixLoad[row][column - 1] == 1 && pMatrixLoad[row][column - 2] == 0)
                            return 1 ;
                        break ;
                    case EAST:
                        if (pMatrixLoad[row][column + 1] == 1 && pMatrixLoad[row][column + 2] == 0)
                            return 1 ;
                        break ;
                    case DEFAULT:case CENTER:case UNDO:
                    default:
                        ;
                        break ;
                    }
                }
            }
        }//for column
    }//for row
    return 0 ;
}

int
matrixCountRemainPeg( ) {
    int row, column, count = 0 ;
    for (row = 0 ; row < HOR_MAX ; row++)
        for (column = 0 ; column < VER_MAX ; column++)
            if (pMatrixLoad[row][column] == 1) count++ ;
    return count ;
}

/*
void
__displayPegFromTo(int whereToGo,int row, int column, Peg_Direction direction, int nbMove){
    char *sDir[] = {"","[N|n]ORTH","[E|e]AST","[S|s]OUTH","[W|w]EST"} ;
    sDir[0] = (nbMove == 1)? "by default, type Enter":"";
    printf("|----------------------------------------------------|\n") ;
    printf("| From Peg [row: %d column: %d] direction: %s\n",row,column,sDir[direction]);
    printf("| => Go to [row: %d column: %d] %s\n",tab_Peg[whereToGo].coord.row,tab_Peg[whereToGo].coord.column, sDir[0]);
    printf("|----------------------------------------------------|\n") ;
}
 */

int
__getCoordPegWhereWeGo( int where ) {
    int i ;
    for (i = 0 ; i < 5 ; i++) {
        if (tab_Peg[i].direction == (unsigned int) where)
            return i ;
    }
    return 0 ;
}

void
__displayMatrix( Matrix matrix ) {
    int row, column ;
    char *sign ;
    printf( "\n%2s", " " ) ;
    for (column = 0 ; column < VER_MAX ; column++) {
        printf( "%- 3d|", column ) ;
    }
    printf( "\n" ) ;
    for (row = 0 ; row < HOR_MAX ; row++) {
        printf( "%2d", row ) ;
        for (column = 0 ; column < VER_MAX ; column++) {
            sign = __selectItem( matrix[row][column] ) ;
            printf( "%2s|", sign ) ;
        }
        printf( "\n" ) ;
    }
}

char*
__selectItem( int item ) {
    char *ret ;
    static int num = 1 ;
    char buff[255] ;
    switch (item) {
    case -1:
        ret = "   " ;
        break ;
    case 0:
        ret = " . " ;
        break ;
    case 1:
        sprintf( buff, "<%2d>", num++ ) ;
        ret = buff ;
        ret = " O " ;
        break ;
    case 2:
        ret = "<0>" ;
        break ;
    default:
        break ;
    }
    return ret ;
}

