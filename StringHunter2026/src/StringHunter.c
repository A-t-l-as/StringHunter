#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "StringHunter.h"


void cleanSimpleBinFile(SimpleBinFile* argFile)
{
    for(int64_t i = 0; i < argFile->sizeOfFile; ++i)
    {
        if((argFile->buffer[i] < ((uint8_t)'!')) || (((uint8_t)'~') < argFile->buffer[i]) )
        {
            argFile->buffer[i] = (uint8_t)'\0';
        }
    }
}

void printAllStrings(SimpleBinFile* argFile, size_t minNumberOfChars, FILE* output)
{
    bool block = false;

    for(int64_t i = 0; i < argFile->sizeOfFile; ++i)
    {
        if((argFile->buffer[i] != ((uint8_t)'\0')) && block == false)
        {
            const char* const string = (const char* const)(&argFile->buffer[i]);
            const size_t sizeOfString = strlen(string);

            if(sizeOfString >= minNumberOfChars)
            {
                fprintf(output, "%s\n", string);
            }

            block = true;
        }

        if(argFile->buffer[i] == ((uint8_t)'\0'))
        {
            block = false;
        }

    }
}
