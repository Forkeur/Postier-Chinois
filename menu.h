/* 
 * File:   menu.h
 * Author: maxime & awaleh
 *
 * Created on 24 octobre 2014, 21:05
 */

#pragma once

#include "TypVoisin.h"
#include "TypGraphe.h"

#ifdef	__cplusplus
extern "C"
{
#endif

static void cleanup_stdin();
static char* scanf_format_path_max();
void handle_error_code(errorcode err);

void MenuGraph();
void MenuPrincipale();

void quitter();



#ifdef	__cplusplus
}
#endif

