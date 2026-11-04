#include "./graphviz_func.h"

void MkDotFileList(char *file_name, List list)
{
    // list.data[1].prev = 4; //For testing red arrows
    yaissert(file_name != NULL);
    //TODO: CheckList

    char open_mode[] = "w";
    FILE *file = safe_fopen(file_name, open_mode);

    fprintf(file,   "digraph G {\n"
                    "splines = curved\n");

    WriteGraphSettings(file);
    WriteList(file, list);
    WriteHead(file, list);

    fprintf(file, "}\n");

    fclose(file);
}

void WriteGraphSettings(FILE *file)
{
    fprintf(file,
        "\tgraph ["
        "bgcolor = \"#5B8298\""
        "]\n"

        "\tnode ["
        "shape = record, "
        "fontname = \"Consolas\", "
        "style = \"rounded, filled\", "
        "height = 0.5, "
        "width = 1, "
        "color = \"#86BBD8\", "
        "fontcolor = \"#E8F1F5\", "
        "penwidth = 3"
        "]\n"
    
        "\tedge ["
        "color = \"#2F4858\", "
        "fontcolor = \"#2F4858\", "
        "penwidth = 2, "
        "arrowsize = 0.6"
        "];\n\n");


}

void WriteList(FILE *file, List list)
{
    int size = list.size;
    bool is_0_elem = 0;
    for(int i = 0; i < size; i++)
    {
        if(i == 0)
        {
            fprintf(file, "\tnode [fillcolor = \"#c5285c74\"]\n");
            is_0_elem = 1;
        }
        else if(is_0_elem)
        {
            fprintf(file, "\n\tnode [fillcolor = \"#478d9a8a\"]\n");
            is_0_elem = 0;
        }
        
        char value[32];

        if (list.data[i].value == list.poison)
            snprintf(value, sizeof(value), "%s", "POISON");
        else
            snprintf(value, sizeof(value), "%d", list.data[i].value);

        fprintf(file, "\t%i [label = \"{<index> index %i | %s |{<prev> prev %i|<next> next %i}}\"];\n",
            i, i, value, list.data[i].prev, list.data[i].next);
    }
    fprintf(file, "\n\tnode [fillcolor = \"#78a5728b\"]\n");
    fprintf(file, "\thead\n");
    fprintf(file, "\ttail\n");
    fprintf(file, "\tfree_head\n");
    fprintf(file, "\n");
    
    for(int i = 0; i < size; i++)
    {
        int index_next = list.data[i].next;
        int index_prev = list.data[i].prev;
        bool isValid_next = list.data[index_next].prev == i;
        bool isValid_prev = list.data[index_prev].next == i;
        if(index_next != list.poison)
        {
            if(isValid_next)
                fprintf(file, "\t%i:next:e -> %i:prev:w [color = \"#eaacef\"];\n", i, list.data[i].next);
            else
                fprintf(file, "\t%i:next:e -> %i:prev:w [color = \"#fc0d0d\"];\n", i, list.data[i].next);
            
        }
        if(list.data[i].prev != list.poison && !isValid_prev)
        {
            if(!isValid_prev)
                fprintf(file, "\t%i:prev:s -> %i:next:s [color = \"#fc0d0d\"];\n", i, list.data[i].prev);
        }
    }
    fprintf(file, "\n");
    
    fprintf(file, "\t{rank = same; ");
    for(int i = 0; i < size; i++)
        fprintf(file, "%i; ", i);
    fprintf(file, "}\n\n\t");

    for(int i = 0; i < size; i++)
    {
        fprintf(file, "%i", i);
        if(i < size - 1)
            fprintf(file, " -> ");
    }
    fprintf(file, "\n");
    fprintf(file, "\t[style=invis, weight=100];\n\n");
}

void WriteHead(FILE *file, List list)
{
    fprintf(file, "\t{rank = sink}\n");
    fprintf(file, "\thead -> %i\n", list.data[0].next);
    fprintf(file, "\ttail -> %i\n", list.data[0].prev);
    fprintf(file, "\tfree_head -> %i\n", list.freehead);
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

void MkHTMLFileList(char *htmlFileName, char *imageFileName)
{
    yaissert(htmlFileName != NULL);
    yaissert(imageFileName != NULL);

    char open_mode[] = "w";
    FILE *file = safe_fopen(htmlFileName, open_mode);

    fprintf(file,
        "<!DOCTYPE html>\n"
        "<html lang=\"ru\">\n"
        "<head>\n"
        "    <meta charset=\"UTF-8\">\n"
        "    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n"
        "    <title>List visualization</title>\n"
        "    <style>\n"
        "        body {\n"
        "            background-color: #5B8298;\n"
        "            display: flex;\n"
        "            justify-content: center;\n"
        "            align-items: center;\n"
        "            min-height: 100vh;\n"
        "            margin: 0;\n"
        "        }\n"
        "        img {\n"
        "            max-width: 95%%;\n"
        "            max-height: 95vh;\n"
        "            object-fit: contain;\n"
        "        }\n"
        "    </style>\n"
        "</head>\n"
        "<body>\n"
        "    <img src=\"%s\" alt=\"List visualization\">\n"
        "</body>\n"
        "</html>\n",
        imageFileName
    );

    fclose(file);
}