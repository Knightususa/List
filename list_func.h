#ifndef LIST_FUNC_H
#define LIST_FUNC_H

#include <stdio.h>
#include <stdlib.h>

#include "./common.h"

typedef int List_elem_t;

typedef struct
{
    List_elem_t value;
    int prev;
    int next;
}List_element;

typedef struct
{
    List_element *data;
    List_elem_t poison;
    int size;
    int freehead;
}List;

List List_init(int list_size, List_elem_t poison);
void List_add(List *list, int insert_index, List_elem_t element_value);
void List_delete(List *list, int delete_index);
void List_show(List list);

#endif