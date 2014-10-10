/* 
 * File:   main.c
 * Author: maxime
 *
 * Created on 10 octobre 2014, 10:04
 */

#include <stdio.h>
#include <stdlib.h>

typedef int voisinT;
typedef int dataT;

static const voisinT SENTINEL_VALUE = -1;

typedef enum _bool
{
    false = 0, true = 1
} bool;

typedef struct _TypVoisins
{
    voisinT voisin;
    dataT data;
    struct _TypVoisins* voisinSuivant;
    struct _TypVoisins* voisinPrecedent;
} TypVoisins;

typedef struct
{
    bool estOriente : 1;
    int nbMaxSommets;
    TypVoisins* listesAdjacences[];
} TypGraphe;

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
    return self->voisin == SENTINEL_VALUE;
}

TypVoisins* createSentinelTypVoisins()
{
    return createTypVoisins(SENTINEL_VALUE, 0);
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

/**
 * Retourne le dernier element de la liste.
 * @param self
 * @return 
 */
TypVoisins* getLastTypVoisins(TypVoisins* self)
{
    TypVoisins* it = getSentinelTypVoisins(self);
    return it ? it->voisinPrecedent : NULL;
}

/**
 * Retourne le premier element de la list.
 * @param self
 * @return 
 */
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
    if (isSentinelTypVoisins(self))
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


// LIST END
// LIST END
// LIST END
// LIST END
// LIST END
// LIST END
// LIST END
// LIST END
// LIST END
// LIST END

/**
 * La fameuse fonctionalité etc demander dans le "cahier des charges"
 */
void etc(void)
{
}

int main(int argc, char** argv)
{

    return (EXIT_SUCCESS);
}

