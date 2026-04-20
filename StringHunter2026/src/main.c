#include <stdio.h>
#include <stdlib.h>
#include <errno.h>


#include "SimpleBinFile.h"
#include "StringHunter.h"


#define ARGC_MAX                   4

#define PROGRAM_NAME_INDEX         0
#define SRC_FILE_PATH_INDEX        1
#define MIN_NUMBER_OF_CHARS_INDEX  2
#define DST_FILE_PATH_INDEX        3

#define DEC_BASE                   10

int main(int argc, char* argv[])
{
    if(argc < ARGC_MAX)
    {
        printf("Not enough arguments. Use:\n");

        printf
        (
          "%s <source file> <min size of string> <destination file>\n",
          argv[PROGRAM_NAME_INDEX]
        );

        exit(CODE_FAILURE);
    }

    char* endPtr;
    errno = 0;
    int64_t n = strtoll(argv[MIN_NUMBER_OF_CHARS_INDEX], &endPtr, DEC_BASE);

    if (errno != 0 || endPtr == argv[MIN_NUMBER_OF_CHARS_INDEX] || *endPtr != '\0' || n <= 0)
    {
        printf("Error: Invalid minimum string length in the input!\n");
        exit(CODE_FAILURE);
    }


    int error = CODE_SUCCESS;

    SimpleBinFile* inputBinFile = loadSimpleBinFile(argv[SRC_FILE_PATH_INDEX], &error);
    if(error == CODE_FAILURE)
        exit(CODE_FAILURE);

    cleanSimpleBinFile(inputBinFile);
    const int64_t sizeOfOutputFile = getSumOfStringsSizes(inputBinFile, (size_t)n);

    SimpleBinFile* outputBinFile = newSimpleBinFile(argv[DST_FILE_PATH_INDEX], sizeOfOutputFile, &error);
    if(error == CODE_FAILURE)
    {
        inputBinFile = destroySimpleBinFile(inputBinFile);
        exit(CODE_FAILURE);
    }

    printAllStrings(inputBinFile, (size_t)n, outputBinFile);

    outputBinFile = saveSimpleBinFile(outputBinFile, argv[DST_FILE_PATH_INDEX], &error);

    inputBinFile  = destroySimpleBinFile(inputBinFile);
    outputBinFile = destroySimpleBinFile(outputBinFile);

    printf("The program completed successfully.");

    exit(error);
}
