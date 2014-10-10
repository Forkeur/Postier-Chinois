/* 
 * File:   main.c
 * Author: maxime
 *
 * Created on 10 octobre 2014, 10:04
 */

#include <stdio.h>
#include <stdlib.h>
#include "TypVoisin.h"
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
 * La fonctionalité etc demander dans le "cahier des charges"
 */
void etc(void)
{
}

int main(int argc, char** argv)
{
    TypVoisins* lst = newTypVoisins();
    emplaceBackTypVoisins(lst, 1, 1);
    emplaceBackTypVoisins(lst, 2, 1);
    return (EXIT_SUCCESS);
}

