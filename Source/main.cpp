#include <Include/diffTool/helpers.hpp>
#include <cstdio>
#include <vector>
#include <map>

using namespace std;

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
    LoadFileIntoBuffer(baseFile, baseFileBuffer, bufferSize);
    bufferSize = LoadFileIntoBuffer(changedFile, NULL, 0);
    char* changedFileBuffer = new char[bufferSize];
    // Check for errors.
    if (!changedFileBuffer) {
        DisplayAllocationError(bufferSize, "changedFileBuffer");
        return -3;
    }
    LoadFileIntoBuffer(changedFile, changedFileBuffer, bufferSize);

    // Close opened files.
    fclose(baseFile);
    fclose(changedFile);

    // Tokens.
    vector<string> baseFileLines;
    vector<string> changedFileLines;
    TokenizeFileContent(baseFileLines, baseFileBuffer);
    TokenizeFileContent(changedFileLines, changedFileBuffer);

    // Free buffers.
    delete[] baseFileBuffer;
    delete[] changedFileBuffer;

    ////////////////////////////////////////////////////////////////////
    std::vector<Pair> diffMap;
    GenerateDiffMap(diffMap, baseFileLines, changedFileLines);
    SortDiffMap(diffMap);

    // Show map.
    //for (const auto& ref : diffMap)
      //  printf("%d : %d\n", ref.first, ref.second);

    DisplayDiffResult(diffMap, baseFileLines, changedFileLines);
}
