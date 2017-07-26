#include <helpers.hpp>
#include <cstdio>

//////////////////////////////////////////////////////////////////
void DisplayHelp(void) {
    printf("diffTool usage:\n");
    printf("\tdiffTool baseFileName changedFileName\n");
    printf("\n");
    printf("baseFileName:       path to file which will be base for differentiation.\n");
    printf("changedFileName:    path to file contaning chnaged version of base file.\n");
}

//////////////////////////////////////////////////////////////////
void DisplayFileOpenError(const char* filePath) {
    printf("!diffTool: Could not open required file: '%s'.\n", filePath);
}

//////////////////////////////////////////////////////////////////
void DisplayAllocationError(int size, const char* name) {
    printf("!diffTool: Could not allocate buffer of size: '%dB' of name: '%s'.\n", size, name);
}

//////////////////////////////////////////////////////////////////
int LoadFileIntoBuffer(FILE* file, char* buffer, int bufferSize) {
    if (file) {
        // Get file size.
        fseek(file, 0L, SEEK_END);
        int fSize = (int)ftell(file);
        // Seek back to the beginning.
        fseek(file, 0, SEEK_SET);

        // If buffer exists, load content.
        if (buffer && bufferSize > 0) {
            // Read.
            fread(
                        file,
                        (fSize > bufferSize ? bufferSize : fSize),
                        1,
                        file
                        );

            return fSize;
        }
    }
    else
        return 0;
}
