#include <stdio.h>
#include <stdlib.h>

#include "myvector.h"

int vector_init(vector* v, size_t init_capacity)
{
    v->data = malloc(init_capacity * sizeof (int));
    if (!v->data) return -1;

    v->size = 0;
    v->capacity = init_capacity;

    return 1;
}

int vector_resize(vector* v, size_t new_size)
{
    if (new_size <= v->capacity)
    {
        return 0;
    }
    int* newdata = realloc(v->data, new_size * sizeof (int));
    if (newdata)
    {
        v->data = newdata;
    }
    else
    {
        return 0;
    }
    v->capacity = new_size;
    return 1;
}

int vector_push_back(vector* v, int element)
{
    if (v->size == v->capacity)
    {
        if (!vector_resize(v, v->capacity * 2)) return 0;
    }
    v->data[v->size] = element;
    v->size += 1;
    return 1;
}

int vector_get(vector* v, size_t index)
{
    if (index >= v->size)
    {
        return 0; //error
    }
    return v->data[index];
}

int vector_pop(vector* v)
{
    if (!v->size)
    {
        return 0; // error
    }
    int ret = v->data[v->size - 1];
    v->size -= 1;
    return ret;
}

int vector_delete(vector* v)
{
    if (!v ||!v->data){
        return 0;
    }
    free(v->data);
    v->data = NULL;
    v->capacity = 0;
    v->size = 0;
    return 1;
}


size_t vector_size(vector* v)
{
    return v->size;
}

vector vector_empty()
{
    vector ret = {NULL, 0, 0};
    return ret;
}