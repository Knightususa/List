#include "./list_func.h"

List *List_init(int list_size, List_elem_t poison)
{
    List *list1 = (List *)safe_calloc(1, sizeof(List)); 
    List list;
    list.size = list_size;
    list.poison = poison;

    list.data = (List_element *)safe_calloc(list_size, sizeof(List_element));
    list.data[0].value = list.poison;
    list.data[0].next = 0;
    list.data[0].prev = 0;

    list.freehead = 1;

    for(int i = 0; i < list_size; i++)
    {
        list.data[i].value = poison;

        if(i == 0)
        {
            list.data[i].prev = 0;
            list.data[i].next = 0;
            continue;
        }
        else if(i == list_size - 1)
        {
            list.data[i].prev = i - 1;
            list.data[i].next = 0;
            continue;
        }

        list.data[i].next = i + 1;
        list.data[i].prev = i - 1;
    }
    *list1 = list;
    return list1;
}

void List_add(List *list, int insert_index, List_elem_t element_value)
{
    List_element *data = list->data;
    int index = list->data[0].next;

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

    list->freehead = list->data[free_index].next;
    data[list->freehead].prev = list->poison;

    //Сдвигаем для free_index
    data[free_index].value = element_value;
    data[free_index].prev = index;
    data[free_index].next = index_next;
    data[index].next = free_index;

    //Сдвигаем для index_next
    data[index_next].prev = free_index;
}

void List_delete(List *list, int delete_index)
{
    List_element *data = list->data;
    int index = list->data[0].next;

    for(int i = 0; i < delete_index; i++)
    {
        index = list->data[index].next;
        yaissert(index != list->poison);
    }
    //index - индекс удаляемого елемента
    //prev_index - индекс элемента перед index
    //next_index - индекс элемента после index
    int prev_index = data[index].prev;
    int next_index = data[index].next;

    data[prev_index].next = next_index;

    //Меняем значение и голову free
    data[index].value = list->poison;
    data[index].next = list->freehead;
    data[list->freehead].prev = index;
    data[index].prev = list->poison;
    list->freehead = index;

    //Меняем следующий
    data[next_index].prev = prev_index;
}


void List_show(List list)
{
    int list_size = list.size;
    const char *str_index  = "index";
    const char *str_prev   = "prev";
    const char *str_value  = "value";
    const char *str_next   = "next";
    const char *str_name   = "name";
    printf("%10s | %10s | %10s | %10s | %10s\n", str_index, str_prev, str_value, str_next, str_name);
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 15; j++)
            printf("-");
    printf("\n");
    for(int i = 0; i < list_size; i++)
    {
        if(i == list.data[0].next)
            printf(_RED);

        else if(i == list.data[0].prev)
            printf(_GREEN);

        else if(i == list.freehead)
            printf(_BLUE);

        printf("%10i | %10i | %10i | %10i |" _RESET, i, list.data[i].prev, list.data[i].value, list.data[i].next);

        if(i == list.data[0].next)
            printf("%10s", "head");

        else if(i == list.data[0].prev)
            printf("%10s", "tail");

        else if(i == list.freehead)
            printf("%10s", "free_head");
        printf("\n");
    }
    printf("\n\n");
}