/*
 * Créé le 01-02-2017 12:05:00 CEST
 * 
 * xfile.c
 *
 * Copyright 2017 Le KiWi <jean@antix1>
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libxml/xmlstring.h>
#include <libxml2/libxml/tree.h>

#include "xfile.h"

static xmlDocPtr doc = NULL ;
static xmlXPathContextPtr xpathCtx = NULL ;
static xmlXPathObjectPtr xpathObj = NULL ;
static const char* fileXML;
static xmlNodePtr cur = NULL ;

/**
 * @brief positionne la variable fileXML
 * @param xfile le nom du fichier
 */
void
_setFile( const char* xfile ) ;

void
_setFile( const char* xfile ) {
    fileXML = (char*) strdup( xfile ) ;
}

xmlXPathContextPtr
xfileNew( const char* xfile ) {
    _setFile( xfile ) ;
    xmlInitParser( ) ;
    doc = xmlParseFile( fileXML ) ;
    if (doc == NULL) {
        printf( "Error: unable to parse file\n" ) ;
        return (0) ;
    }
    xpathCtx = xmlXPathNewContext( doc ) ;
    if (xpathCtx == NULL) {
        printf( "Error: unable to create new XPath context\n" ) ;
        xmlFreeDoc( doc ) ;
        return (0) ;
    }
    return xpathCtx ;
}

void
xfileRead(xmlXPathContextPtr xpc, char * buffer[], const char* xpath){
    int i = 0;
    xpathObj = xmlXPathEvalExpression( (xmlChar *)xpath, xpc ) ;
    if (xpathObj == NULL) {
        printf( "Erreur: ne peut evaluer l'expression xpath\n" ) ;
        xmlXPathFreeContext( xpc ) ;
        return (EXIT_FAILURE) ;
    }
    xmlNodeSetPtr nodes = xpathObj->nodesetval ;
    int size = (nodes) ? nodes->nodeNr : 0;
    for(i = 0; i < size; ++i) {
        cur = nodes->nodeTab[i]; 
        buffer[i] = (char *) cur->content ;
    }
    buffer[i] = '\0' ;
}