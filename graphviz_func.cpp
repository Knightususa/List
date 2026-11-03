#include "./graphviz_func.h"

void MkDotFileList(char *file_name, List list)
{
    yaissert(file_name != NULL);
    //TODO: CheckList

    char open_mode[] = "w";
    FILE *file = safe_fopen(file_name, open_mode);

    fprintf(file,   "digraph G {\n"
                    "\tsplines = ortho;\n");

    WriteGraphSettings(file);
    WriteList(file, list);

    fprintf(file, "}\n");

    fclose(file);
}

void WriteGraphSettings(FILE *file)
{
    fprintf(file,
        "\tgraph ["
        "label = \"List\", "
        "bgcolor = white, "
        "]\n"

        "\tnode ["
        "shape = record, "
        "fontname = \"Arial\", "
        "style=rounded, "
        "fillcolor=lightblue, "
        "height=0.5, "
        "width=1"
        "]\n");
}

void WriteList(FILE *file, List list)
{
    int size = list.size;
    for(int i = 0; i < size; i++)
    {
        fprintf(file, "\t%i [label = <{index %i |prev %i |value %i |next %i}>];\n",
             i, i, list.data[i].prev, list.data[i].value, list.data[i].next);
    }
    fprintf(file, "\n");
    
    for(int i = 0; i < size; i++)
    {
        fprintf(file, "\t%i -> %i\n", i, list.data[i].next);
    }
    fprintf(file, "\n");
    
    fprintf(file, "\t{rank = same; ");
    for(int i = 0; i < size; i++)
    fprintf(file, "\t%i; ", i);
    fprintf(file, "\t}\n\n\t");

    for(int i = 0; i < size; i++)
    {
        fprintf(file, "%i", i);
        if(i < size - 1)
            fprintf(file, " -> ");
    }
    fprintf(file, "\n");
    fprintf(file, "\t[style=invis, weight=100];\n");
}

void CompileDotFile(char *inputFile, char *outputFile)
{
    char command[512];

    int len = snprintf(command, sizeof(command),
        ".\\Graphviz\\bin\\dot.exe "
        "-Tsvg %s "
        "-o %s",
        inputFile, outputFile);

    if (len < 0 || (size_t)len >= sizeof(command))
        yaiwarning(0, "Invalid len of command");

    int result = system(command);

    if (result != 0)
        yaiwarning(0, "Graphviz error!\n");

    printf("Graph generated successfully!\n");
}