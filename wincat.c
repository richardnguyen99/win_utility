#include "base.h"

int main(int argc, const char *argv[])
{
    if (argc < 2)
    {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    HANDLE hFile;
    char buffer[1024];
    UINT bytesRead, bytesWritten;

    hFile = CreateFile(argv[1], GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE)
    {
        fprintf(stderr, "Error opening file %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    while (TRUE)
    {
        if (!ReadFile(hFile, buffer, sizeof(buffer), &bytesRead, NULL))
            ErrorExit("ReadFile");

        if (bytesRead == 0)
        {
            break;
        }

        if (!WriteFile(GetStdHandle(STD_OUTPUT_HANDLE), buffer, bytesRead, &bytesWritten, NULL) || bytesWritten == 0)
            ErrorExit("WriteFile");
    }

    CloseHandle(hFile);

    return 0;
}
