#ifndef SIMPLE_BIN_FILE_H
#define SIMPLE_BIN_FILE_H

#include <stdint.h>

#define CODE_FAILURE 1
#define CODE_SUCCESS 0

typedef struct SimpleBinFile
{
    uint8_t* buffer;
    int64_t  sizeOfFile;
}
SimpleBinFile;

SimpleBinFile* loadSimpleBinFile(const char* const argPath, int* error);
SimpleBinFile* newSimpleBinFile(const char* const tempName, int64_t argSizeOfFile, int* error);
SimpleBinFile* saveSimpleBinFile(SimpleBinFile* argFile, const char* const argPath, int* error);

SimpleBinFile* destroySimpleBinFile(SimpleBinFile* argFile);

#endif // !SIMPLE_BIN_FILE_H
