#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <inttypes.h>
#include <stdlib.h>
#include <stdbool.h>

size_t file_bytes(FILE *file, uint8_t **buffer)
{
#define BUFFER_SIZE 1024
    uint8_t *inner_buffer = *buffer;
    inner_buffer = malloc(BUFFER_SIZE * sizeof(uint8_t));
    size_t read = fread(inner_buffer, sizeof(uint8_t), BUFFER_SIZE, file);
    size_t patchs_read = 0;
    for (size_t i = 2; read == BUFFER_SIZE; i++)
    {
        patchs_read += 1;
        inner_buffer = realloc(inner_buffer, BUFFER_SIZE * sizeof(uint8_t) * i);
        read = fread(inner_buffer + BUFFER_SIZE * (i - 1), sizeof(uint8_t), BUFFER_SIZE, file);
    }

    *buffer = inner_buffer;

    return patchs_read * BUFFER_SIZE + read;
}

int main(int argc, char const *argv[])
{

    printf("Hello, World");

    if (argc != 2)
    {
        printf("Expected file to compress/decompress\n");
        return 1;
    }

    char const *file_name = argv[1];
    if (access(file_name, F_OK) != 0)
    {
        printf("Couldn't find file %s\n", file_name);
        return 1;
    }

    if (access(file_name, R_OK) != 0)
    {
        printf("Lacking permission to read file.\n");
        return 1;
    }

    FILE *file = fopen(file_name, "r");
    if (file == NULL)
    {
        printf("Failed to open file\n");
        return 1;
    }

    uint8_t *buffer;
    size_t read = file_bytes(file, &buffer);

    return 0;
}
