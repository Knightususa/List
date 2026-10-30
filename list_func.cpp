#include "./list_func.h"

List List_init(int list_size, List_elem_t poison)
{
    List list;
    list.size = list_size;
    list.poison = poison;
    list.data = (List_element *)safe_calloc(list_size, sizeof(List_element));
    list.tail = 0;
    list.head = 0;
    list.freehead = 0;

    for(int i = 0; i < list_size; i++)
    {
        list.data[i].value = poison;

        if(i == 0)
        {
            list.data[i].prev = poison;
            list.data[i].next = i + 1;
            continue;
        }
        else if(i == list_size)
        {
            list.data[i].next = poison;
            list.data[i].prev = i - 1;
            continue;
        }

        list.data[i].next = i + 1;
        list.data[i].prev = i - 1;
    }

    return list;
}

void List_add(List *list, int insert_index, List_elem_t element_value)
{
    int index = list->tail;
    for(int i = 0; i < insert_index; i++)
    {
        index = list->data[index].next;
        yaissert(index != list->poison);
    }
    //index - индекс элемента после которого надо вставить
    //free_index - свободный элемент
    //index_next - индекс элемента после index
    int free_index = list->freehead;
    int index_next = list->data[index].next;

    //Сдвигаем все для головы free
    if(index == list->head)
        list->head = free_index;
    list->freehead = list->data[list->freehead].next;
    list->data[list->freehead].prev = list->poison;

    //Сдвигаем для free_index
    list->data[free_index].value = element_value;
    list->data[free_index].prev = index;
    list->data[free_index].next = index_next;
    list->data[index].next = free_index;

    //Сдвигаем для index_next
    list->data[index_next].prev = free_index;
}

void List_delete(List *list, int delete_index)
{
    int index = list->tail;
    for(int i = 0; i < delete_index; i++)
    {
        index = list->data[index].next;
        yaissert(index != list->poison);
    }
    //index - индекс удаляемого елемента
    //prev_index - индекс элемента перед index
    //next_index - индекс элемента после index
    int prev_index = list->data[index].prev;
    int next_index = list->data[index].next;

    //Меняем предыдущий
    if(index == list->head)
        list->head = prev_index;
    list->data[prev_index].next = next_index;

    //Меняем значение и голову free
    list->data[index].value = list->poison;
    list->data[index].next = list->freehead;
    list->data[list->freehead].prev = index;
    list->data[index].prev = list->poison;
    list->freehead = index;

    //Меняем следующий
    list->data[next_index].prev = prev_index;
}


void List_show(List list)
{
    int list_size = list.size;
    const char *str_index  = "index";
    const char *str_prev   = "prev";
    const char *str_value  = "value";
    const char *str_next   = "next";
    printf("%10s | %10s | %10s | %10s\n", str_index, str_prev, str_value, str_next);
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 15; j++)
            printf("-");
    printf("\n");
    for(int i = 0; i < list_size; i++)
    {
        if(i == list.tail)
            printf(_RED);

        if(i == list.head)
            printf(_GREEN);

        if(i == list.freehead)
            printf(_BLUE);

        printf("%10i | %10i | %10i | %10i\n" _RESET, i, list.data[i].prev, list.data[i].value, list.data[i].next);
    }
    printf("\n\n");
}