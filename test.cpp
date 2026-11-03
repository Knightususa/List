#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    // 1. Создаём DOT-файл
    FILE *file = fopen("graph.dot", "w");

    if (file == NULL)
    {
        perror("Cannot create DOT file");
        return 1;
    }

    fprintf(file,
        "digraph G\n"
        "{\n"
        "    %i -> B -> C;\n"
        "    A -> C;\n"
        "}\n"
    , 1);

    fclose(file);

    // 2. Запускаем локальный Graphviz
    const char *command =
        ".\\Graphviz\\bin\\dot.exe -Ksfdp "
        "-Tsvg graph.dot "
        "-o graph.svg";

    int result = system(command);

    if (result != 0)
    {
        printf("Graphviz error!\n");
        return 1;
    }

    printf("Graph generated successfully!\n");

    return 0;
}