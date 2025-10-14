#include "minishell.h"

int vector_setup(t_vector* vector) {
	if (vector == NULL)
        return VECTOR_ERROR;
    

	vector->args_count = 0;
	vector->args_capacity = 2;
	vector->args = malloc(sizeof(char *) * vector->args_capacity);
    if (!vector->args)
        return VECTOR_ERROR;
    return VECTOR_SUCCESS;
}

void vector_destroy(t_vector* vector) {
    int i;

    i = 0;
    if (!vector)
        return;
    while (i < vector->args_count)
    {
        free(vector->args[i]);
        i++;
    }
    if (vector->args)
        free(vector->args);
    free(vector);
}

int vector_grow(t_vector* vector) {
    void *tmp;

    tmp = ft_realloc(vector->args, sizeof(char *) * vector->args_capacity, sizeof(char *)
				* vector->args_capacity * 2);
	if (!tmp)
		return VECTOR_ERROR;
	vector->args_capacity *= 2;
	vector->args = tmp;
    return (VECTOR_SUCCESS);
}

int vector_push_back(t_vector* vector, char* element) {
    if (vector == NULL || element == NULL)
        return VECTOR_ERROR;
    
    if (vector->args_count == vector->args_capacity)
    {
        if (vector_grow(vector) == VECTOR_ERROR)
            return VECTOR_ERROR;
    }

    vector->args[vector->args_count++] = element;

	return VECTOR_SUCCESS;
}