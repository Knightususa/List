#include "./list_lib/list_func.h"
#include "./graphviz_func.h"

int main()
{
    List *list = List_init(10, -1);
    List_show(*list);
    
    List_add(list, 0, 10);
    List_show(*list);

    List_add(list, 0, 11);
    List_show(*list);

    List_add(list, 1, 12);
    List_show(*list);

    List_add(list, 1, 13);
    List_show(*list);

    List_delete(list, 2);
    List_show(*list);

    char input_file[] = "pic1.dot";
    char output_file[] = "pic1.svg";
    MkDotFileList(input_file, *list);
    CompileDotFile(input_file, output_file);
}