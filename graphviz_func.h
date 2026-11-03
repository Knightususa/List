#ifndef GRAPHVIZ_FUNC_H
#define GRAPHVIZ_FUNC_H

#include "./list_lib/list_func.h"


void MkDotFileList(char *file_name, List list);
void WriteGraphSettings(FILE *file);
void WriteList(FILE *file, List list);

void CompileDotFile(char *inputFile, char *outputFile);

#endif
//end ifndef GRAPHVIZ_FUNC_H