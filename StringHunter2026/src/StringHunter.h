#ifndef STRING_HUNTER_H
#define STRING_HUNTER_H

#include "SimpleBinFile.h"
#include <stdio.h>

void cleanSimpleBinFile(SimpleBinFile* argFile);

void printAllStrings(SimpleBinFile* argFile, size_t minNumberOfChars, FILE* output);

#endif // !STRING_HUNTER_H
