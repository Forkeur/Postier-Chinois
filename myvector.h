#pragma once
#ifdef	__cplusplus
extern "C" {
#endif

typedef struct dynamic_array_struct
{
  int* data;
  size_t capacity; /* total capacity */
  size_t size; /* number of elements in vector */
} vector;


int vector_init(vector* v, size_t init_capacity);

int vector_resize(vector* v, size_t new_size);

int vector_push_back(vector* v, int element);

int vector_get(vector* v, size_t index);
int vector_pop(vector* v);
int vector_delete(vector* v);
size_t vector_size(vector* v);

vector vector_empty();
#ifdef	__cplusplus
}
#endif

