#ifndef HELPERS_HPP
#define HELPERS_HPP

#include <cstdio>
#include <vector>
#include <string>
#include <map>
#include <set>

//////////////////////////////////////////////////////////////////
// This function displays help in console.
void DisplayHelp(void);

//////////////////////////////////////////////////////////////////
void DisplayFileOpenError(const char*);

//////////////////////////////////////////////////////////////////
void DisplayAllocationError(int, const char*);

//////////////////////////////////////////////////////////////////
// This function loads file's content into buffer.
// As result returns file content's length.
int LoadFileIntoBuffer(FILE*, char*, int);

//////////////////////////////////////////////////////////////////
void TokenizeFileContent(std::vector<std::string>&, char*);

struct Pair {
    int first;
    int second;
};

//////////////////////////////////////////////////////////////////
void GenerateDiffMap(std::vector<Pair>&, const std::vector<std::string>&, const std::vector<std::string>&);

//////////////////////////////////////////////////////////////////
void SortDiffMap(std::vector<Pair>&);

//////////////////////////////////////////////////////////////////
void DisplayDiffResult(const std::vector<Pair>&, const std::vector<std::string>&, const std::vector<std::string>&);

#endif // HELPERS_HPP
