#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "parser.h"
#include "menu.h"


/**
 * Taken from http://stackoverflow.com/questions/122616/how-do-i-trim-leading-trailing-whitespace-in-a-standard-way
 * @param str
 * @return 
 */
static char *trimwhitespace(char *str)
{
    char *end;

    // Trim leading space
    while (isspace(*str)) str++;

    if (*str == 0) // All spaces?
        return str;

    // Trim trailing space
    end = str + strlen(str) - 1;
    while (end > str && isspace(*end)) end--;

    // Write new null terminator
    *(end + 1) = 0;

    return str;
}



TypGraphe* parse(FILE* f)
{
    char buf[PARSER_LINE_BUFFER_SIZE];
    char* read;
    size_t line = 0;
    long int sommet, sommetParent, poids;

    bool orienter;
    TypGraphe* res = NULL;
    errorcode err;
    if (f)
    {
        //read #
        line += 1;
        read = fgets(buf, sizeof (buf), f);
        if (read)
        {
            read = trimwhitespace(buf);
            if (!read || *read != '#')
            {
                printf("erreur parsage line %u; '%s' attendu, on a : '%s'", line,
                       "#", read ? read : "EOF");
                return NULL;
            }
        }
        else
        {
            printf("erreur parsage line %u; EOF", line);
            return NULL;
        }

        //read nombre maximum de sommets
        line += 1;
        read = fgets(buf, sizeof (buf), f);
        if (read)
        {
            read = trimwhitespace(buf);
            sommet = strtol(read, NULL, 0);
            if (!sommet)
            {
                printf("erreur parsage line %u; '%s' attendu, on a : '%s'", line,
                       "CHIFFRE", read ? read : "EOF");
                return NULL;
            }
        }
        else
        {
            printf("erreur parsage line %u; EOF", line);
            return NULL;
        }

        //read #
        line += 1;
        read = fgets(buf, sizeof (buf), f);
        if (read)
        {
            read = trimwhitespace(buf);
            if (!read || *read != '#')
            {
                printf("erreur parsage line %u; '%s' attendu, on a : '%s'", line,
                       "#", read ? read : "EOF");
                return NULL;
            }
        }
        else
        {
            printf("erreur parsage line %u; EOF", line);
            return NULL;
        }

        //read 'o' ou 'n'
        line += 1;
        read = fgets(buf, sizeof (buf), f);
        if (read)
        {
            read = trimwhitespace(buf);
            if (!read || !(*read == 'o' || *read == 'n'))
            {
                printf("erreur parsage line %u; '%s' attendu, on a : '%s'", line,
                       "o|n", read ? read : "EOF");
                return NULL;
            }
            orienter = *read == 'o';
        }
        else
        {
            printf("erreur parsage line %u; EOF", line);
            return NULL;
        }

        res = newTypGraphe(sommet, orienter);
        if (!res)
        {
            return NULL;
        }

        //read #
        line += 1;
        read = fgets(buf, sizeof (buf), f);
        if (read)
        {
            read = trimwhitespace(buf);
            if (!read || *read != '#')
            {
                printf("erreur parsage line %u; '%s' attendu, on a : '%s'", line,
                       "#", read ? read : "EOF");
                return NULL;
            }
        }
        else
        {
            printf("erreur parsage line %u; EOF", line);
            return NULL;
        }

        //maintenant on parse les sommets et les arretes
        do
        {
            line += 1;
            read = fgets(buf, sizeof (buf), f);
            if (read)
            {
                read = trimwhitespace(buf);
                char* token = strtok(read, ":");
                read = trimwhitespace(token);
                char *endptr;
                sommetParent = strtol(read, &endptr, 0);
                if (read == endptr)
                {
                    printf("erreur parsage line %u; '%s' attendu, on a : '%s'", line,
                           "CHIFFRE", read ? read : "EOF");
                    return NULL;
                }
                err = insertionSommetTypGraphe(res, sommetParent);
                if (err < 0 && err != -2)
                {
                    handle_error_code(err);
                    return NULL;
                }

                token = strtok(NULL, ","); //les arretes
                while (token)
                {
                    int scanfres = sscanf(token, " ( %u / %u ) ", &sommet, &poids);
                    if (scanfres != 2)
                    {
                        printf("erreur parsage line %u; une definition d'arrete est attendue", line);
                    }
                    if (!checkSommetExist(res, sommet))
                    {
                        //crée automatiquement le sommet
                        insertionSommetTypGraphe(res, sommet);
                    }
                    err = insertionAreteTypGraphe(res, sommetParent, sommet, poids);
                    if (err < 0 && !err == -5)
                    {
                        handle_error_code(err);
                        return NULL;
                    }
                    token = strtok(NULL, ",");
                }
            }
        }
        while (read);

    }
    return res;
}



