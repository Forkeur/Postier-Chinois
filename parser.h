/* 
 * File:   parser.h
 * Author: maxime & awaleh
 *
 * Created on 24 octobre 2014, 22:36
 */

#pragma once


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TypVoisin.h"
#include "TypGraphe.h"

#define PARSER_LINE_BUFFER_SIZE 4096

#ifdef	__cplusplus
extern "C"
{
#endif
static char *trimwhitespace(char *str);
TypGraphe* parse(FILE* f);


#ifdef	__cplusplus
}
#endif

