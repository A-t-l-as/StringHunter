#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "SimpleBinFile.h"

SimpleBinFile* newSimpleBinFile(const char* const argPath, int* error)
{
    FILE* inputFile = fopen(argPath, "rb");

    // Handling an error when opening the source file.
    if(!inputFile)
    {
        perror("Error opening the source file");
        *error = CODE_FAILURE;
        return NULL;
    }

    SimpleBinFile* binFile = (SimpleBinFile*)malloc( sizeof(*binFile) );

    // Calculating size of file
    *error = fseek(inputFile, 0, SEEK_END);
    binFile->sizeOfFile = ftell(inputFile);

    // I'm going back to the beginning of the file.
    *error = fseek(inputFile, 0, SEEK_SET);

    // Positioning error.
    if(*error != CODE_SUCCESS || binFile->sizeOfFile == EOF)
    {
        perror("Positioning error");
        *error = CODE_FAILURE;
        free(binFile);
        fclose(inputFile);
        return NULL;
    }

    // Displaying additional information about the file.
    printf("Opened file: %s\n", argPath);
    printf("Size of file: 0x%" PRIx64 "\n", binFile->sizeOfFile);

    // Create buffer for file.
    binFile->buffer = (uint8_t*)malloc(binFile->sizeOfFile * sizeof(uint8_t));

    if(binFile->buffer == NULL)
    {
        perror("Memory allocation error");
        *error = CODE_FAILURE;
        free(binFile);
        fclose(inputFile);
        return NULL;
    }

    size_t nReadBytes = fread(binFile->buffer, sizeof(uint8_t), binFile->sizeOfFile, inputFile);

    if(nReadBytes != (size_t)binFile->sizeOfFile)
    {
        perror("Error reading source file");
        *error = CODE_FAILURE;
        free(binFile->buffer);
        free(binFile);
        fclose(inputFile);
        return NULL;
    }

    if( fclose(inputFile) == EOF)
    {
        perror("File close error");
        *error = CODE_FAILURE;
        free(binFile->buffer);
        free(binFile);
        return NULL;
    }

    return binFile;
}

SimpleBinFile* destroySimpleBinFile(SimpleBinFile* argFile)
{
    free(argFile->buffer);
    free(argFile);
    return NULL;
}
