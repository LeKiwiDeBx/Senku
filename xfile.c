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

#include "xfile.h"

static xmlDocPtr doc = NULL ;
static xmlXPathContextPtr xpathCtx = NULL ;
static xmlXPathObjectPtr xpathObj = NULL ;
static const char* fileXML;
static xmlNodePtr cur = NULL ;
//static xmlNodeSetPtr nodes = NULL ;

static const char*
_getFile( ) ;

/**
 * @brief positionne la variable fileXML
 * @param xfile le nom du fichier
 */
void
_setFile( const char* xfile ) ;

const char*
_getFile( ) {
    return fileXML ;
}

void
_setFile( const char* xfile ) {
    fileXML = (char*) strdup( xfile ) ;
}

//int
//xfileCountNode( xmlChar* xpath ) {
//    if (xpathObj) {
//        nodes = xpathObj->nodesetval ;
//        return (nodes) ? nodes->nodeNr : 0 ;
//    }
//    return 0 ;
//}

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
//    xpathObj = xmlXPathEvalExpression( (xmlChar *)xpath, xpathCtx ) ;
//    if (xpathObj == NULL) {
//        printf( "Error: unable to evaluate xpath expression\n" ) ;
//        xmlXPathFreeContext( xpathCtx ) ;
//        xmlFreeDoc( doc ) ;
//        return (0) ;
//    }
    return xpathCtx ;
    //return  xpathObj->nodesetval ; //nodes
    //cur = nodes->nodeTab[i] ;
}

void
xfileRead(xmlXPathContextPtr xpc, char *buffer[], const char* xpath){
    int i = 0 ;
    xpathObj = xmlXPathEvalExpression( (xmlChar *)xpath, xpc ) ;
    if (xpathObj == NULL) {
        printf( "Error: unable to evaluate xpath expression\n" ) ;
    }
    xmlNodeSetPtr nodes = xpathObj->nodesetval ;
    int size = (nodes) ? nodes->nodeNr : 0;
    // fprintf(stdout, "\nResult (%d nodes):\n", size);
    int k = 0 ;
    for(i = 0; i < size; ++i) {
        cur = nodes->nodeTab[i]; 
       // fprintf(stdout, "content %s sizeof %d\n", cur->content,sizeof(cur->content));
        buffer[i] = cur->content ;
        if(nodes->nodeTab[i]->type == XML_ELEMENT_NODE) { //XML_ELEMENT_NODE
//            xmlChar * pContentProp = xmlGetProp(cur, (xmlChar *) "value");
//            xmlChar * pContentIndex = xmlGetProp(cur, (xmlChar *)"index");
//            xmlChar * pContentValue = xmlGetProp(cur, (xmlChar *)"value");
//            fprintf(stdout, " * element node \"%s\" ", xmlGetProp(cur, (xmlChar *) "value"));
            //fprintf(stdout, "%s", cur->children->content);
            //fprintf(stdout, "%s", cur->children->content);
//            fprintf(stdout, "%s\n", pContentProp);
//            fprintf(stdout, "=> value: \"%s\"\n", pContentValue);
        } else {
            //fprintf(stdout, "= node \"%s\": type %d \n", cur->name, cur->type);
        }
        
    }
    buffer[i] = NULL ;
}