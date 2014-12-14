#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "chinois.h"

int countEdge(TypGraphe* self)
{
    if (!self)
    {
        return 0;
    }
    int ret = 0;
    for (int i = 0; i < self->nbMaxSommets; i++)
    {
        if (checkSommetExist(self, i))
        {
            ret += 0;
        }
    }
    return ret;
}


//based on http://en.wikipedia.org/wiki/Floyd-Warshall_algorithm#Path_reconstruction

FloyrdMarshallMatrixElementT** floydWarshallWithPathReconstruction(TypGraphe* self)
{
    FloyrdMarshallMatrixElementT** ret = malloc(self->nbMaxSommets * sizeof (FloyrdMarshallMatrixElementT*));

    //init
    for (int i = 0; i < self->nbMaxSommets; ++i)
    {
        ret[i] = malloc(self->nbMaxSommets * sizeof (FloyrdMarshallMatrixElementT));
        for (int j = 0; j < self->nbMaxSommets; ++j)
        {
            ret[i][j].dist = INT_MAX;
            ret[i][j].next = -1;
        }
        if (!checkSommetExist(self, i))
        {
            continue;
        }
        TypVoisins* it = self->listesAdjacences[i];
        do
        {
            if (!isSentinelTypVoisins(it))
            {
                ret[i][it->voisin].dist = it->data;
                ret[i][it->voisin].next = it->voisin;
            }
            it = it->voisinSuivant;
        }
        while (it != self->listesAdjacences[i]);
    }


    // Floyd-Warshall implementation
    for (int k = 0; k < self->nbMaxSommets; ++k)
    {
        for (int i = 0; i < self->nbMaxSommets; ++i)
        {
            for (int j = 0; j < self->nbMaxSommets; ++j)
            {
                if (ret[i][k].dist != INT_MAX && ret[k][j].dist != INT_MAX &&
                        ret[i][k].dist + ret[k][j].dist < ret[i][j].dist)
                {
                    ret[i][j].dist = ret[i][k].dist + ret[k][j].dist;
                    ret[i][j].next = ret[i][k].next;
                }
            }
        }
    }

    return ret;
}

vector floydWarshallPath(FloyrdMarshallMatrixElementT** matrix, int u, int v)
{
    if (matrix[u][v].next == -1)
    {
        return vector_empty();
    }
    vector path;
    vector_init(&path, 10);
    do
    {
        vector_push_back(&path, u);
        u = matrix[u][v].next;
    }
    while (u != v);
    vector_push_back(&path, v);
    return path;
}

void deleteFloyrdMarshallComputedMatrix(FloyrdMarshallMatrixElementT** self, size_t size)
{
    for (int j = 0; j < size; ++j)
    {
        free(self[j]);
    }
    free(self);
}

void resetColor(TypGraphe* self)
{
    for (int i = 0; i < self->nbMaxSommets; ++i)
    {
        if (!checkSommetExist(self, i))
        {
            continue;
        }
        TypVoisins* it = self->listesAdjacences[i];
        do
        {
            it->color = 0;
            it = it->voisinSuivant;
        }
        while (it != self->listesAdjacences[i]);
    }
}

vector oddVertices(TypGraphe* g)
{
    vector ret;
    vector_init(&ret, 10);
    for (int i = 0; i < g->nbMaxSommets; ++i)
    {
        if (!checkSommetExist(g, i))
        {
            continue;
        }
        TypVoisins* it = g->listesAdjacences[i];
        unsigned int count = 0;
        do
        {
            if (!isSentinelTypVoisins(it))
            {
                count += 1;
            }
            it = it->voisinSuivant;
        }
        while (it != g->listesAdjacences[i]);

        if (count & 0x1)
        {
            vector_push_back(&ret, i);
        }
    }
    return ret;
}

TypVoisins* getNextUnmarkedTypVoisin(TypVoisins* lst)
{
    TypVoisins* it = lst;
    do
    {
        if (!isSentinelTypVoisins(it) && !it->color)
        {
            return it;
        }
        it = it->voisinSuivant;
    }
    while (it != lst);
    return NULL;
}

int searchBackForVertx(vertxvect* v, int searchFor)
{
    for (size_t i = v->size - 1; i >= 0; i -= 2)
    {
        if (vector_get(v, i) == searchFor)
        {
            return i;
        }
    }
    return -1;
}

int mergeVertxVector(vertxvect* v, vertxvect* sub)
{
    if (!sub || sub->size <= 1)
    {
        return 0;
    }
    int searchFor = vector_get(sub, 0);
    int insertindex = searchBackForVertx(v, searchFor);
    if (insertindex == -1)
    {
        return 0;
    }
    vector_resize(v, v->capacity + sub->size); // better perf
    for (int i = insertindex, j = 0; j < sub->size;)
    {
        if (j < sub->size - 1)
        {
            vector_push_back(v, vector_get(v, i + 1));
        }
        v->data[i] = vector_get(sub, j);
        j += 1;
        i += 1;
    }
    return 1;

}

TypVoisins* searchVoisinDataColor(TypVoisins* self, voisinT seek, dataT data)
{
    if (self == NULL)
    {
        return NULL;
    }
    TypVoisins* it = self;
    do
    {
        if (it->voisin == seek && it->data == data && !it->color)
        {
            return it;
        }
        it = it->voisinSuivant;
    }
    while (it != self);
    return NULL;
}

vertxvect subEulerianPath(const TypGraphe* g, int startVertex)
{
    vertxvect ret;
    vertxvect remaining;
    vector_init(&remaining, 6);
    vector_init(&ret, 10);

    int vertex = startVertex;
    //init ret vector with startVertex
    vector_push_back(&ret, startVertex);
    bool pathEnd = false;
    while (!pathEnd)
    {
        TypVoisins* edge = getNextUnmarkedTypVoisin(g->listesAdjacences[vertex]);
        //if we don't found another edge in the current vertex
        if (!edge)
        {
            // if there's remaining unmarked edge in the vector
            if (vector_size(&remaining))
            {
                while (vector_size(&remaining))
                {
                    int vertex2 = vector_pop(&remaining);
                    //perform a recursive call
                    vertxvect sub = subEulerianPath(g, vertex2);
                    //then merge result into return value
                    mergeVertxVector(&ret, &sub);
                    vector_delete(&sub);
                }
            }
            else
            {
                pathEnd = true;
            }
        }
        else
        {
            vector_push_back(&ret, edge->data);
            vector_push_back(&ret, edge->voisin);
            //increment color
            edge->color += 1;
            //increment target color too
            TypVoisins* unmarkedVoisin = searchVoisinDataColor(g->listesAdjacences[edge->voisin], vertex, edge->data);
            unmarkedVoisin->color += 1;

            // if there's remaining uncolored edge within vertex
            if (getNextUnmarkedTypVoisin(g->listesAdjacences[vertex]))
            {
                vector_push_back(&remaining, vertex);
            }

            vertex = edge->voisin;
        }
    }

    vector_delete(&remaining);
    return ret;
}

bool CPP(TypGraphe* g)
{
    if (!g)
    {
        return false;
    }
    vector sommetImpair = oddVertices(g);
    FloyrdMarshallMatrixElementT** matrix = floydWarshallWithPathReconstruction(g);


    vector couplages = listeCouplage(&sommetImpair);
    //now find the shorstest path between vertices
    int couplage = -1;
    int minValue = INT_MAX;
    for (int i = 0; i < couplages.size; i += sommetImpair.size)
    {
        int sum = 0;
        for (int j = 0; j < sommetImpair.size; j += 2)
        {
            int left = vector_get(&couplages, i + j);
            int right = vector_get(&couplages, i + j + 1);
            if (matrix[left][right].dist == INT_MAX)
            {
                sum = INT_MAX;
                continue;
            }
            sum += matrix[left][right].dist;
        }

        if (sum < minValue)
        {
            minValue = sum;
            couplage = i;
        }
    }

    if (couplage == -1)
    {
        return false;
    }

    vector couplagevect = {.data = couplages.data + couplage, .size = sommetImpair.size};
    for (int j = 0; j < couplagevect.size; j += 2)
    {
        vector path = floydWarshallPath(matrix, vector_get(&couplagevect, j), vector_get(&couplagevect, j + 1));
        int from = vector_get(&path, 0);
        for (int i = 1; i < path.size; ++i)
        {
            int to = vector_get(&path, i);
            insertionAreteTypGraphe(g, from, to, matrix[from][to].dist);
            insertionAreteTypGraphe(g, to, from, matrix[to][from].dist);
            from = to;
        }
        vector_delete(&path);
    }


    deleteFloyrdMarshallComputedMatrix(matrix, g->nbMaxSommets);
    vector_delete(&sommetImpair);
    vector_delete(&couplages);
    return true;
}

void _listeCouplage(vector* sommetsImpairs, vector* result, vector* accu)
{
    if (!sommetsImpairs->size)
    {
        for (int i = 0; i < accu->size; ++i)
        {
            vector_push_back(result, vector_get(accu, i));
        }
    }
    else
    {
        int x = vector_get(sommetsImpairs, 0);
        for (int i = 1; i < sommetsImpairs->size; ++i)
        {
            int y = sommetsImpairs->data[i];
            sommetsImpairs->data[i] = sommetsImpairs->data[1];
            sommetsImpairs->data[1] = y;
            vector_push_back(accu, x);
            vector_push_back(accu, y);
            vector subset = {.data = sommetsImpairs->data + 2, .size = sommetsImpairs->size - 2};
            _listeCouplage(&subset, result, accu);
            accu->size -= 2;
        }
    }
}

vector listeCouplage(vector* sommetsImpairs)
{
    vector accu;
    vector_init(&accu, 10);
    vector ret;
    vector_init(&ret, 10);
    _listeCouplage(sommetsImpairs, &ret, &accu);
    vector_delete(&accu);
    return ret;
}

vertxvect parcoursEulerien(TypGraphe* g, struct exception* error)
{
    vector sommetImpair = oddVertices(g);
    size_t sommetImpairSize = vector_size(&sommetImpair);
    if (sommetImpairSize > 2 || sommetImpairSize == 1)
    {
        //can't resolve that
        vector_delete(&sommetImpair);
        if (error)
        {
            error->line = __LINE__;
            error->msg = "can't resolve that, you should use the CPP algo.";
        }
        return vector_empty();
    }

    int startVertex = -1;
    //compute startVertex
    if (sommetImpairSize == 2)
    {
        startVertex = vector_get(&sommetImpair, 0);
    }
    else
    {
        for (int i = 0; i < g->nbMaxSommets; ++i)
        {
            if (checkSommetExist(g, i))
            {
                startVertex = i;
                break;
            }
        }
    }

    vector_delete(&sommetImpair);

    if (startVertex == -1)
    {
        if (error)
        {
            error->line = __LINE__;
            error->msg = "no vertex";
        }
        return vector_empty();
    }

    resetColor(g);


    return subEulerianPath(g, startVertex);
}



