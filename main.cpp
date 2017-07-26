#include <helpers.hpp>
#include <cstdio>

int main(int argc, char** argv) {
    // As app parameters we pass 2 file names.
    if (argc < 3) {
        DisplayHelp();
        return -1;
    }

    FILE* baseFile = fopen(argv[1], "r+");
    FILE* changedFile = fopen(argv[2], "r+");

    // Check if we successfully opened required files.
    if (!baseFile) {
        DisplayFileOpenError(argv[1]);
        return -2;
    }
    if (!changedFile) {
        DisplayFileOpenError(argv[2]);
        return -2;
    }

    // Allocate 2 buffers of size of files.
    int bufferSize = LoadFileIntoBuffer(baseFile, NULL, 0);
    char* baseFileBuffer = new char[bufferSize];
    // Check for errors.
    if (!baseFileBuffer) {
        DisplayAllocationError(bufferSize, "baseFileBuffer");
        return -3;
    }
    bufferSize = LoadFileIntoBuffer(file, NULL, 0);
    char* changedFileBuffer = new char[];
}
