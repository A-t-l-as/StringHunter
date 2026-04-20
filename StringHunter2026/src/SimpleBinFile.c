#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "SimpleBinFile.h"

SimpleBinFile* loadSimpleBinFile(const char* const argPath, int* error)
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

    if(binFile == NULL)
    {
        perror("Memory allocation error");
        *error = CODE_FAILURE;
        fclose(inputFile);
        return NULL;
    }

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
        fclose(inputFile);
        free(binFile);
        return NULL;
    }

    // Displaying additional information about the file.
    printf("Opened file: %s\n", argPath);
    printf("Size of file: 0x%" PRIx64 "\n", binFile->sizeOfFile);
    printf("-----------------\n");

    // Create buffer for file.
    binFile->buffer = (uint8_t*)malloc(binFile->sizeOfFile * sizeof(uint8_t));

    if(binFile->buffer == NULL)
    {
        perror("Memory allocation error");
        *error = CODE_FAILURE;
        fclose(inputFile);
        free(binFile);
        return NULL;
    }

    size_t nReadBytes = fread(binFile->buffer, sizeof(uint8_t), binFile->sizeOfFile, inputFile);

    if(nReadBytes != (size_t)binFile->sizeOfFile)
    {
        perror("Error reading source file");
        *error = CODE_FAILURE;
        fclose(inputFile);
        binFile = destroySimpleBinFile(binFile);
        return binFile;
    }

    if( fclose(inputFile) == EOF)
    {
        perror("File close error");
        *error = CODE_FAILURE;
        binFile = destroySimpleBinFile(binFile);
        return binFile;
    }

    return binFile;
}

SimpleBinFile* newSimpleBinFile(const char* const tempName, int64_t argSizeOfFile, int* error)
{
    if(argSizeOfFile <= 0)
    {
        fprintf(stderr, "You cannot allocate a negative or zero number of bytes!");
        *error = CODE_FAILURE;
        return NULL;
    }

    SimpleBinFile* binFile = (SimpleBinFile*)malloc( sizeof(*binFile) );

    if(binFile == NULL)
    {
        perror("Memory allocation error");
        *error = CODE_FAILURE;
        return NULL;
    }

    binFile->sizeOfFile = argSizeOfFile;

    // Displaying additional information about the file.
    printf("Created file: %s\n", tempName);
    printf("Size of file: 0x%" PRIx64 "\n", binFile->sizeOfFile);
    printf("-----------------\n");

    // Create buffer for file.
    binFile->buffer = (uint8_t*)calloc(binFile->sizeOfFile, sizeof(uint8_t));

    if(binFile->buffer == NULL)
    {
        perror("Memory allocation error");
        *error = CODE_FAILURE;
        free(binFile);
        return NULL;
    }

    return binFile;
}

SimpleBinFile* saveSimpleBinFile(SimpleBinFile* argFile, const char* const argPath, int* error)
{
    if(!argFile)
    {
        perror("The simpleBinFile object passed as an argument is null!");
        *error = CODE_FAILURE;
        return NULL;
    }

    if(!argFile->buffer)
    {
        perror("The simpleBinFile->buffer is null!");
        *error = CODE_FAILURE;
        argFile = destroySimpleBinFile(argFile);
        return argFile;
    }

    FILE* outputFile = fopen(argPath, "wb");

    if(!outputFile)
    {
        perror("Error opening the destination file");
        *error = CODE_FAILURE;
        argFile = destroySimpleBinFile(argFile);
        return argFile;
    }

    size_t nWritedBytes = fwrite((char*)argFile->buffer, sizeof(uint8_t), argFile->sizeOfFile, outputFile);

    if(nWritedBytes != (size_t)argFile->sizeOfFile)
    {
        perror("Error writing file");
        *error = CODE_FAILURE;
        fclose(outputFile);
        argFile = destroySimpleBinFile(argFile);
        return argFile;
    }

    if( fclose(outputFile) == EOF)
    {
        perror("File close error");
        *error = CODE_FAILURE;
        argFile = destroySimpleBinFile(argFile);
        return argFile;
    }

    return argFile;
}


SimpleBinFile* destroySimpleBinFile(SimpleBinFile* argFile)
{
    if(argFile == NULL)
      return NULL;

    free(argFile->buffer);
    free(argFile);
    return NULL;
}
