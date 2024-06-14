#include <stdio.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
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

    return 0;
}
