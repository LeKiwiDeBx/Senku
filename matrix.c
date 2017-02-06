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
#include <glib/gprintf.h>
#include <glib-2.0/glib/gprintf.h>


/**
 * Header XML
 *
 */

//#include <libxml/parser.h>
//#include <libxml/xpath.h>
//#include <libxml/xpathInternals.h>
//#include <libxml/xmlmemory.h>
//#include <libxml/tree.h>


// Matrix matrixEnglish = {  // TEST TEST TEST
//	0  1  2  3  4  5  6  7  8  9  10
//	{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1}, //0
//	{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},	//1
//	{-1,-1,-1,-1, 0, 1, 0,-1,-1,-1,-1},	//2
//	{-1,-1,-1,-1, 0, 1, 0,-1,-1,-1,-1},	//3
//    {-1,-1, 0, 0, 1, 0, 1, 0, 0,-1,-1},	//4
//    {-1,-1, 0, 0, 0, 1, 1, 0, 0,-1,-1},	//5
//    {-1,-1, 0, 0, 0, 1, 0, 0, 0,-1,-1},	//6
//    {-1,-1,-1,-1, 0, 1, 0,-1,-1,-1,-1},	//7
//	{-1,-1,-1,-1, 0, 0, 0,-1,-1,-1,-1},	//8
//	{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},	//9
//	{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1}	//10
//} ;
/**
 * @brief schema du shape dit Anglais
 *         matrice carrée 11 x 11
 * @Matrix type de tableau 2D de integer (int)
 */
Matrix matrixEnglish = {
    //0  1  2  3  4  5  6  7  8  9  10
    {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1}, //0
    {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1}, //1
    {-1, -1, -1, -1, 1, 1, 1, -1, -1, -1, -1}, //2
    {-1, -1, -1, -1, 1, 1, 1, -1, -1, -1, -1}, //3
    {-1, -1, 1, 1, 1, 1, 1, 1, 1, -1, -1}, //4
    {-1, -1, 1, 1, 1, 0, 1, 1, 1, -1, -1}, //5
    {-1, -1, 1, 1, 1, 1, 1, 1, 1, -1, -1}, //6
    {-1, -1, -1, -1, 1, 1, 1, -1, -1, -1, -1}, //7
    {-1, -1, -1, -1, 1, 1, 1, -1, -1, -1, -1}, //8
    {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1}, //9
    {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1} //10
} ;

Matrix matrixGerman = {
    //0  1  2  3  4  5  6  7  8  9  10
    {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1}, //0
    {-1, -1, -1, -1, 1, 1, 1, -1, -1, -1, -1}, //1
    {-1, -1, -1, -1, 1, 1, 1, -1, -1, -1, -1}, //2
    {-1, -1, -1, -1, 1, 1, 1, -1, -1, -1, -1}, //3
    {-1, 1, 1, 1, 1, 1, 1, 1, 1, 1, -1}, //4
    {-1, 1, 1, 1, 1, 0, 1, 1, 1, 1, -1}, //5
    {-1, 1, 1, 1, 1, 1, 1, 1, 1, 1, -1}, //6
    {-1, -1, -1, -1, 1, 1, 1, -1, -1, -1, -1}, //7
    {-1, -1, -1, -1, 1, 1, 1, -1, -1, -1, -1}, //8
    {-1, -1, -1, -1, 1, 1, 1, -1, -1, -1, -1}, //9
    {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1} //10
} ;

Matrix matrixDiamond = {
    //0  1  2  3  4  5  6  7  8  9  10
    {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1}, //0
    {-1, -1, -1, -1, -1, 1, -1, -1, -1, -1, -1}, //1
    {-1, -1, -1, -1, 1, 1, 1, -1, -1, -1, -1}, //2
    {-1, -1, -1, 1, 1, 1, 1, 1, -1, -1, -1}, //3
    {-1, -1, 1, 1, 1, 1, 1, 1, 1, -1, -1}, //4
    {-1, 1, 1, 1, 1, 0, 1, 1, 1, 1, -1}, //5
    {-1, -1, 1, 1, 1, 1, 1, 1, 1, -1, -1}, //6
    {-1, -1, -1, 1, 1, 1, 1, 1, -1, -1, -1}, //7
    {-1, -1, -1, -1, 1, 1, 1, -1, -1, -1, -1}, //8
    {-1, -1, -1, -1, -1, 1, -1, -1, -1, -1, -1}, //9
    {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1} //10
} ;

/**
 * structure du noeud matrix selectionné de matrix.xml 
 */
typedef struct s_NodeMatrix {
    char * name ;
    Matrix data ;
} NodeMatrix ;

NodeMatrix *pCurrentNodeMatrix ;
NodeMatrix currentNodeMatrix ;

// Matrix matrixCopy ;

/*
static void
__displayMatrix(Matrix) ;

static char
 *__selectItem(int) ;

static void
__displayLoadChoice(const char *) ;

static void
__displayPegFromTo(int, int, int, Peg_Direction, int);
 */

static int
__getCoordPegWhereWeGo( int ) ;

//static int
//_xpathNodes(const char* filename, const xmlChar* xpathExpr) ;

//static int
//_xpathNodes(const char* filename, const xmlChar* xpathExpr){
//    xmlDocPtr doc;
//    xmlXPathContextPtr xpathCtx; 
//    xmlXPathObjectPtr xpathObj; 
//    xmlInitParser();
//    doc = xmlParseFile(filename);
//    if (doc == NULL) {
//        g_print("Error: unable to parse file \"%s\"\n", filename);
//        return(-1);
//    }
//    else{
////        g_print("Success: ok to parse file \"%s\"\n", filename);
//    }
//    xpathCtx = xmlXPathNewContext(doc);
//    if(xpathCtx == NULL) {
//        g_print("Error: unable to create new XPath context\n");
//        xmlFreeDoc(doc); 
//        return(-1);
//    }
//    xpathObj = xmlXPathEvalExpression(xpathExpr, xpathCtx);
//    if(xpathObj == NULL) {
//        g_print("Error: unable to evaluate xpath expression \"%s\"\n", xpathExpr);
//        xmlXPathFreeContext(xpathCtx); 
//        xmlFreeDoc(doc); 
//        return(-1);
//    }
//    xmlNodePtr cur;
//    int size;
//    int i;
//    xmlNodeSetPtr nodes = xpathObj->nodesetval ;
//    size = (nodes) ? nodes->nodeNr : 0;
//    fprintf(stdout, "Result (%d nodes):\n", size);
//    for(i = 0; i < size; ++i) {
//        if(nodes->nodeTab[i]->type == XML_ELEMENT_NODE) {
//            cur = nodes->nodeTab[i]; 
//            xmlChar * pContentName = xmlGetProp(cur, (xmlChar *)"name");
//            xmlChar * pContentIndex = xmlGetProp(cur, (xmlChar *)"index");
//            xmlChar * pContentValue = xmlGetProp(cur, (xmlChar *)"value");
//            fprintf(stdout, " * element node \"%s index %s\" ", cur->name, pContentIndex);
//            fprintf(stdout, "=> name: \"%s\"", pContentName);
//            fprintf(stdout, "=> value: \"%s\"\n", pContentValue);
//        } else {
//            cur = nodes->nodeTab[i];    
//            fprintf(stdout, "= node \"%s\": type %d \n", cur->name, cur->type);
//        }
//    }
//    xmlCleanupParser();
//    return(1) ;
//}
/**
 * @brief DRAFT liste les matrices existantes
 */
void
matrixListMatrix(char **ns , int *size ){
    const char * rqst = "//matrix/name/text()" ;
    char * bufferNs[128] ;
    void * pXfile ;
    int i = 0, k = 0 ;
    pXfile = xfileNew("matrix.xml") ;
    xfileRead( pXfile, bufferNs, rqst) ;
    g_print("retour ns OK\n") ;
    while (bufferNs[i] != NULL) {
        i++ ;
    }
    *size = i ;
    g_print("retour ns size = %d\n", *size) ;
    for (k = 0 ; k < i ; k++) {
       ns[k] = bufferNs[k] ;
       //g_print("retour ns %s", ns[k]) ;
    }
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
    pXfile = xfileNew( "matrix.xml" ) ;
    int i = 0, k = 0 ;
    /**
     *  
     * on veut tous les noms
     *      
     */
    xfileRead( pXfile, bufferNames, "//matrix/name/text()" ) ;
    char * nameShape[128] = {NULL} ;
    while (bufferNames[i] != NULL) {
        //g_print( "\ndebug:: buffer name :%s\n", buffer[i] ) ;
        i++ ;
    }
    nameShape[0] = g_strdup( "Unknown" );
    for (k = 0 ; k < i ; k++) {
        nameShape[k + 1] = g_strdup(bufferNames[k] ) ;
        //g_print( "\ndebug:: nameShape :%s\n", nameShape[k + 1]) ;
    }
    /**
     *  
     * on veut les valeurs du matrix choisie
     *      
     */
    xfileRead( pXfile, bufferMatrix, g_strdup_printf( "//matrix[%d]/row/column/text()", choice ) ) ;
    i = 0 ;
    while (bufferMatrix[i] != NULL) {
        //g_print( "\ndebug:: buffer matrix :%s\n", bufferMatrix[i] ) ;
        i++ ;
    }
    char c ;
    int j , value ;
    Matrix  xmlMatrix  ;
    for (j = 0 ; j < VER_MAX ; j++) {
        for (i = 0 ; i < HOR_MAX ; i++) { //les colonnes de la ligne
            c = *bufferMatrix[j]++ ;
            value = atoi(&c) ;
            //value = (value == 0 || value == 1)? value: -1 ;
            //g_print( "%2d ", value ) ;
            xmlMatrix[j][i] = (value == 0 || value == 1)? value: -1 ;
            //g_print( "%2d \n", xmlMatrix[j][i] ) ;
        }
        //g_print( "\n" ) ;
    }
    
    /**
     *  
     * on veut le nom de la matrice
     *      
     */
    xfileRead( pXfile, bufferName, g_strdup_printf( "//matrix[%d]/name/text()", choice ) ) ;
//    i = 0 ;
//    while (bufferName[i] != NULL) {
//        g_print( "\ndebug:: buffer name choisit :%s\n", bufferName[i] ) ;
//        i++ ;
//    }
   
    //DEBUG XLM char *nameShape[] = {"Unknown", "Shape English", "Shape German", "Shape Diamond"} ;
    //          Matrix * matrixType[] = {NULL, matrixEnglish, matrixGerman, matrixDiamond} ;
    
    if (choice >= 0 && choice <= 4) {
        switch (choice) {
        case 1:case 2:case 3:case 4:
          //currentMatrixOfBoard.pShape = matrixType[choice] ;
          currentMatrixOfBoard.pShape = &xmlMatrix ;
            break ;
        //case 4:
        //	printf("\n Thank you, Good bye! ;)" );
        //  exit( EXIT_SUCCESS ) ;
        //  break ;
        default:
            return 0 ;
        }
        
        currentMatrixOfBoard.name = g_strdup( nameShape[choice] ) ;
        //g_print("\nDEBUG +--------> nom choisit %s", currentMatrixOfBoard.name ) ;
        //		__displayLoadChoice(currentMatrixOfBoard.name) ;
        currentMatrixOfBoard.id = choice ;
        memcpy( matrixCopy, currentMatrixOfBoard.pShape, HOR_MAX * VER_MAX * sizeof (int) ) ;
       // memcpy( matrixCopy, xmlMatrix, HOR_MAX * VER_MAX * sizeof (int) ) ;
        pMatrixLoad = matrixCopy ;
        //		__displayMatrix(matrixCopy) ;
        return 1 ;
    }
    return 0 ;
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
                //				__displayPegFromTo(PegGoTo, row, column, direction, nbMove);
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
    Peg_Memento pegMemento ;

    if (where == DEFAULT) {
        i = pegReturnDefaultPeg( ) ;
        where = tab_Peg[i].direction ;
    }
    else if (where == UNDO) {
        //        __displayMatrix(pMatrixLoad);
        return 0 ;
    }
    else {
        i = __getCoordPegWhereWeGo( where ) ;
        if (!i) {
            //			printf("Is not a valid direction, do NOTHING ! :((\n");
            //			__displayMatrix(pMatrixLoad);
            return 0 ;
        }
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
    pegMemento.coordStart.row = row + 2 * coefRow ;
    pegMemento.coordStart.column = column + 2 * coefColumn ;
    pegMemento.coordBetween.row = row + coefRow ;
    pegMemento.coordBetween.column = column + coefColumn ;
    pegMemento.coordEnd.row = row ;
    pegMemento.coordEnd.column = column ;
    originatorSet( pegMemento ) ;
    caretakerAddMemento( originatorSaveToMemento( ) ) ;
    //fin memento UNDO
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
                    switch (direction) {
                    case NORTH: //conditions pour prendre un peg
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
    for (row = 0 ; row < HOR_MAX ; row++) {
        for (column = 0 ; column < VER_MAX ; column++) {
            if (pMatrixLoad[row][column] == 1) count++ ;
        }
    }
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

/*
void
__displayLoadChoice(const char * shapeName){
//	printf("Loading %s...\n", shapeName);
    g_print("DEBUG :: Loading %s...\n", shapeName);
}
 */

/*
void
__displayMatrix(Matrix matrix){
    int row, column;
    char *sign ;
    printf("\n%2s", " ");
    for(column = 0 ; column < VER_MAX ; column++){
        printf("%- 3d|", column) ;
    }
    printf("\n");
    for(row = 0 ; row < HOR_MAX ; row++){
    printf("%2d",row);
        for(column = 0; column <VER_MAX ; column++){
            sign = __selectItem(matrix[row][column]);
            printf("%2s|", sign);
            }
    printf("\n");
    }
}
 */

/*
char
 *__selectItem(int item){
    char *ret ;
    static int num = 1;
    char buff[255] ;
    switch (item)
    {
        case -1:
        ret = "   ";
            break;
        case 0:
        ret = " . ";
            break;
        case 1:
        sprintf(buff, "<%2d>", num++);
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
 */
