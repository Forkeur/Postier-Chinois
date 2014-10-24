#include <stdio.h>
#include <stdlib.h>
#include "TypVoisin.h"

static TypVoisins* createSentinelTypVoisins();

int getSentinelValue()
{
    return SENTINEL_VALUE;
}

TypVoisins* createTypVoisins(voisinT voisin, dataT data)
{
    TypVoisins* ret = calloc(1, sizeof (TypVoisins));
    ret->voisin = voisin;
    ret->data = data;
    return ret;
}

bool isSentinelTypVoisins(TypVoisins* self)
{
    return self && self->voisin == SENTINEL_VALUE;
}

static TypVoisins* createSentinelTypVoisins()
{
    return createTypVoisins(SENTINEL_VALUE, -1);
}

void deepDeleteTypVoisins(TypVoisins* self)
{
    if (self == NULL)
    {
        return;
    }
    TypVoisins* it = self;
    TypVoisins* next;
    do
    {
        next = it->voisinSuivant;
        free(it);
        it = next;
    }
    while (it != self);
}

TypVoisins* getSentinelTypVoisins(TypVoisins* self)
{
    TypVoisins* it = self;
    while (it && !isSentinelTypVoisins(it))
    {
        it = it->voisinPrecedent;
    }
    return it ? it : NULL;
}

TypVoisins* getLastTypVoisins(TypVoisins* self)
{
    TypVoisins* it = getSentinelTypVoisins(self);
    return it ? it->voisinPrecedent : NULL;
}

TypVoisins* getFirstTypVoisins(TypVoisins* self)
{
    TypVoisins* it = getSentinelTypVoisins(self);
    return it ? it->voisinSuivant : NULL;
}

void insertTypVoisins(TypVoisins* left, TypVoisins* incoming, TypVoisins* rigth)
{
    left->voisinSuivant = incoming;
    rigth->voisinPrecedent = incoming;
    incoming->voisinPrecedent = left;
    incoming->voisinSuivant = rigth;
}

TypVoisins* newTypVoisins()
{
    TypVoisins* ret = createSentinelTypVoisins();
    insertTypVoisins(ret, ret, ret);
    return ret;
}

TypVoisins* appendTypVoisins(TypVoisins* self, TypVoisins* incoming)
{
    TypVoisins* last = getLastTypVoisins(self);
    if (last == NULL)
    {
        return NULL;
    }
    TypVoisins* sentinel = last->voisinSuivant;
    insertTypVoisins(last, incoming, sentinel);
    return self;
}

TypVoisins* prependTypVoisins(TypVoisins* self, TypVoisins* incoming)
{
    TypVoisins* first = getFirstTypVoisins(self);
    if (first == NULL)
    {
        return NULL;
    }
    TypVoisins* sentinel = first->voisinPrecedent;
    insertTypVoisins(sentinel, incoming, first);
    return self;
}

TypVoisins* emplaceBackTypVoisins(TypVoisins* self, voisinT voisin, dataT data)
{
    TypVoisins* ret = createTypVoisins(voisin, data);
    appendTypVoisins(self, ret);
    return ret;
}

bool removeTypVoisins(TypVoisins* self)
{
    if (self == NULL || isSentinelTypVoisins(self))
    {
        return false;
    }
    TypVoisins* left = self->voisinPrecedent;
    TypVoisins* rigth = self->voisinSuivant;
    left->voisinSuivant = rigth;
    rigth->voisinPrecedent = left;
    free(self);
    return true;
}

TypVoisins* searchForVoisin(TypVoisins* self, voisinT seek)
{
    if (self == NULL)
    {
        return NULL;
    }
    TypVoisins* it = self;
    do
    {
        if (it->voisin == seek)
        {
            return it;
        }
        it = it->voisinSuivant;
    }
    while (it != self);
    return NULL;
}

TypVoisins* searchForData(TypVoisins* self, dataT seek)
{
    if (self == NULL)
    {
        return NULL;
    }
    TypVoisins* it = self;
    do
    {
        if (it->data == seek)
        {
            return it;
        }
        it = it->voisinSuivant;
    }
    while (it != self);
    return NULL;
}