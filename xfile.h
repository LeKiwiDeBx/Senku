/* 
 * File:   xfile.h
 * Author: Administrateur
 *
 * Created on 1 février 2017, 13:07
 */

#ifndef XFILE_H
#define XFILE_H

#include <libxml/parser.h>
#include <libxml/xpath.h>
#include <libxml/xpathInternals.h>
#include <libxml/xmlmemory.h>
#include <libxml/tree.h>

/**
 * @brief construit xfile
 * @param xfile le fichier à parser
 * @param xpath la requete xpath
 *  
 */
xmlXPathContextPtr
xfileNew(const char* xfile) ;

/**
 * @brief lit le fichier selon la requete path
 * @param nodes noeud qui pinte sur le fichier obtenu par xFileNew
 * @param xpath la requete XPath
 */
void
xfileRead(xmlXPathContextPtr xpc,char * buffer[], const char* xpath) ;
#endif /* XFILE_H */

