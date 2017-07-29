#include <helpers.hpp>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

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
        rewind(file);

        // If buffer exists, load content.
        if (buffer && bufferSize > 0)
            // Read.
            fread(
                        buffer,
                        1,
                        (fSize > bufferSize ? bufferSize : fSize),
                        file
                        );


        return fSize;
    }
    else
        return 0;
}

//////////////////////////////////////////////////////////////////
void TokenizeFileContent(std::vector<std::string>& output, char* content) {
    char* token = strtok(content, "\n");
    while(token) {
        output.push_back(token);
        token = strtok(NULL, "\n");
    }
}

bool operator<(const Pair& a, const Pair& b) {
    return (a.first < b.first && a.second < b.second);
}

//////////////////////////////////////////////////////////////////
void GenerateDiffMap(
        std::vector<Pair>& output,
        const std::vector<std::string>& base,
        const std::vector<std::string>& change
        )
{
    // Pointers to current lines.
    int currentBaseLine = 0;
    int currentChangeLine = 0;

    // Array containg states of usage of lines.
    bool* baseLineUsage = new bool[base.size()];
    memset(baseLineUsage, 0, base.size());
    bool* changeLineUsage = new bool[change.size()];
    memset(changeLineUsage, 0, change.size());

    // Iterate over base.
    for (unsigned int i = 0; i < base.size(); ++i) {
        auto it = find(change.begin(), change.end(), base[i]);
        // If we found.
        if (it != change.end()) {
            // Set chnage usage flag.
            changeLineUsage[it - change.begin()] = true;
            // Add ref.
            output.push_back({i + 1, it - change.begin() + 1});
        }
        // If  not insert delete ref.
        else
            output.push_back({i + 1, 0});
    }

    // Add add refs from change version.
    for (int i = 0; i < change.size(); ++i){
        if (!changeLineUsage[i])
            output.push_back({0, i + 1});
    }

    // Start interating over base version.
    /*for (currentBaseLine; currentBaseLine < base.size(); ++currentBaseLine) {
        // Find base counterpart in change.
        for (int i = currentChangeLine; i < change.size(); ++i) {
            // If we found and it was not used before.
            if (base[currentBaseLine] == change[i] && !changeLineUsage[i]) {
                // Set usage flag.
                baseLineUsage[currentBaseLine] = true;
                changeLineUsage[i] = true;
                // Add ref.
                output.insert({currentBaseLine, i});
            }
        }
    }

    // Start interating over base version.
    for (currentBaseLine; currentBaseLine < base.size(); ++currentBaseLine) {
        // Copmare with changed counterpart only if it was not used yet.
        if (base[currentBaseLine] == change[currentChangeLine]) {
            // Set flag that we already used that line.
            baseLineUsage[currentBaseLine] = true;
            changeLineUsage[currentChangeLine] = true;
            // Add reference to map.
            // And move to next line.
            output.insert({currentBaseLine++, currentChangeLine++});
            // Continue loop.
            continue;
        }
        else {
            bool found = false;
            // Try to find counterpart in changed version.
            for (int i = currentChangeLine++; i < change.size(); ++i) {
                // Compare only if current change line was not used yet.
                if (!changeLineUsage[i] && base[currentBaseLine] == change[i]) {
                    // Set flag that we already used that line.
                    baseLineUsage[currentBaseLine] = true;
                    changeLineUsage[i] = true;
                    // Add reference.
                    output.insert({currentBaseLine++, i});
                    // Set flag.
                    found = true;
                    break;
                }
            }

            // If we did not find counterpart in chage, add delete reference.
            if (!found) {
                // Set usage flag.
                baseLineUsage[currentBaseLine] = true;
                output.insert({currentBaseLine++, 0});
            }
        }

        // If we are here that means that current change line does not have counterpart found yet.
        // Need to find one.
        // Iterate over base lines.
        for (int i = currentBaseLine; i < base.size(); ++i) {
            // Compare only if current base line was not used yet.
            if (!baseLineUsage[i] && chnage[currentChangeLine] == base[i]) {
                // Set usage flag.
                baseLineUsage[i] = true;
                // Add reference.
                output.insert({i, })
            }
        }
    }*/
}

//////////////////////////////////////////////////////////////////
void DisplayDiffResult(
        const std::vector<Pair>& diffMap,
        const std::vector<std::string>& base,
        const std::vector<std::string>& change
        )
{
    for (int i = 0; i < diffMap.size(); ++i) {
        // If both values are greater then 0, then no change.
        if (diffMap[i].first > 0 && diffMap[i].second > 0)
            cout <<"\033[0m"<<" "<<base[diffMap[i].first - 1]<<"\n";
           // printf("\033[0m %s\n", base[i]);
        // If second is 0, then we have deletion.
        else if (diffMap[i].second == 0)
            cout <<"\033[0;31m"<<"-"<<base[diffMap[i].first - 1]<<"\n";
            //printf("\033[0;31m-%s\n", base[i]);
        // If first is 0, then we have additoon.
        else if (diffMap[i].first == 0)
            cout <<"\033[0;32m"<<"+"<<change[diffMap[i].second - 1]<<"\n";
            //printf("\033[0;32m+%s\n", change[i]);
    }

    // reset.
    cout <<"\033[0m";
}

//////////////////////////////////////////////////////////////////
void SortDiffMap(std::vector<Pair>& diffMap) {
    // We bouble sort only pairs which have one 0.
    // We start from last element.

    // This variable says if we swaped elements.
    bool swapped;
    do {
       // Reset.
        swapped = false;

        for (int i = (diffMap.size() - 1); i > 0; --i) {
            // Do only if lower element contains 0.
            if (diffMap[i].first == 0 || diffMap[i].second == 0) {
                // Compare if first.
                if (diffMap[i].first != 0) {
                    if (diffMap[i].first < diffMap[i - 1].first) {
                        std::swap(diffMap[i], diffMap[i - 1]);
                        swapped = true;
                    }
                }
                // Compare if second.
                else {
                    if (diffMap[i].second < diffMap[i - 1].second) {
                        std::swap(diffMap[i], diffMap[i - 1]);
                        swapped = true;
                    }
                }
            }
        }
    }
    while(swapped);
}
