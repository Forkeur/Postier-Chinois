/* 
 * File:   TypVoisin.h
 * Author: maxime & awaleh
 *
 * Created on 10 octobre 2014, 14:06
 */

#pragma once

#include "stdbool.h"

#ifdef	__cplusplus
extern "C"
{
#endif
typedef int voisinT;
typedef int dataT;

static const voisinT SENTINEL_VALUE = -1;

typedef struct _TypVoisins
{
    voisinT voisin;
    dataT data;
    struct _TypVoisins* voisinSuivant;
    struct _TypVoisins* voisinPrecedent;
} TypVoisins;

int getSentinelValue();

TypVoisins* newTypVoisins();
void deepDeleteTypVoisins(TypVoisins* self);

TypVoisins* createTypVoisins(voisinT voisin, dataT data);

bool isSentinelTypVoisins(TypVoisins* self);

TypVoisins* getSentinelTypVoisins(TypVoisins* self);
TypVoisins* getLastTypVoisins(TypVoisins* self);
TypVoisins* getFirstTypVoisins(TypVoisins* self);

void insertTypVoisins(TypVoisins* left, TypVoisins* incoming, TypVoisins* rigth);

TypVoisins* appendTypVoisins(TypVoisins* self, TypVoisins* incoming);
TypVoisins* prependTypVoisins(TypVoisins* self, TypVoisins* incoming);
TypVoisins* emplaceBackTypVoisins(TypVoisins* self, voisinT voisin, dataT data);

bool removeTypVoisins(TypVoisins* self);

TypVoisins* searchForVoisin(TypVoisins* self, voisinT seek);
TypVoisins* searchForData(TypVoisins* self, dataT seek);




#ifdef	__cplusplus
}
#endif

