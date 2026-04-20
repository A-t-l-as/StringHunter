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



void printAllStrings(SimpleBinFile* argInputFile, size_t minNumberOfChars, SimpleBinFile* argOutputFile)
{
    bool block = false;

    int64_t writePos = 0;

    for(int64_t i = 0; i < argInputFile->sizeOfFile; ++i)
    {
        if((argInputFile->buffer[i] != ((uint8_t)'\0')) && block == false)
        {
            const char* const string = (const char* const)(&argInputFile->buffer[i]);
            const size_t sizeOfString = strlen(string);

            if(sizeOfString >= minNumberOfChars)
            {
                memcpy(argOutputFile->buffer + writePos, string, sizeOfString);
                writePos += sizeOfString;
                argOutputFile->buffer[writePos] = '\n';
                writePos++;
            }

            block = true;
        }

        if(argInputFile->buffer[i] == ((uint8_t)'\0'))
        {
            block = false;
        }

    }
}



int64_t getSumOfStringsSizes(SimpleBinFile* argFile, size_t minNumberOfChars)
{
    bool block = false;

    int64_t sumOfSizes = 0;

    for(int64_t i = 0; i < argFile->sizeOfFile; ++i)
    {
        if((argFile->buffer[i] != ((uint8_t)'\0')) && block == false)
        {
            const char* const string = (const char* const)(&argFile->buffer[i]);
            const size_t sizeOfString = strlen(string);

            if(sizeOfString >= minNumberOfChars)
            {
                sumOfSizes += sizeOfString + 1; // +1 dla \n
            }

            block = true;
        }

        if(argFile->buffer[i] == ((uint8_t)'\0'))
        {
            block = false;
        }

    }

    return sumOfSizes;
}
