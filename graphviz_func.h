#ifndef GRAPHVIZ_FUNC_H
#define GRAPHVIZ_FUNC_H

#include "./list_lib/list_func.h"


void MkDotFileList(char *file_name, List list);
void WriteGraphSettings(FILE *file);
void WriteList(FILE *file, List list);
void WriteHead(FILE *file, List list);

void CompileDotFile(char *inputFile, char *outputFile);
void MkHTMLFileList(char *htmlFileName, char *imageFileName);

#endif
//end ifndef GRAPHVIZ_FUNC_H