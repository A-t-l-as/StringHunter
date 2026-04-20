#ifndef STRING_HUNTER_H
#define STRING_HUNTER_H

#include "SimpleBinFile.h"
#include <stdio.h>

void cleanSimpleBinFile(SimpleBinFile* argFile);

void printAllStrings(SimpleBinFile* argInputFile, size_t minNumberOfChars, SimpleBinFile* argOutputFile);

int64_t getSumOfStringsSizes(SimpleBinFile* argFile, size_t minNumberOfChars);

#endif // !STRING_HUNTER_H
