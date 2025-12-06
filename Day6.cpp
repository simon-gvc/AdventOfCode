#include "2025/Days2025.h"
#include "FileReader.h"
#include <string>
#include <vector>

namespace Year2025 {

std::vector<int> getChunkIndexes(std::vector<std::string> grid) {
    std::vector<int> indexes;
    int row_count = grid.size();
    
    // Go over the first row
    for(int i = 0 ; i < grid[0].size() ; i++) {
        // Try to see if we hit an empty column by looking down
        bool empty = true;
        for(int j = 0 ; j < row_count ; j++) {
            if(grid[j][i] != ' ') {
                empty = false;
                break;
            }
        }
        if(empty) {
            indexes.push_back(i);
        }
    }
    // Add in a final one to to ensure we later catch all chunks
    indexes.push_back(grid[0].size());
    return indexes;
}

std::vector<std::vector<std::string>> fileToChunks() {
    std::ifstream file("input/2025/day6.txt");
    std::string line;

    // Transrom to a grid of strings
    std::vector<std::string> grid;
    while(std::getline(file, line)) {
        grid.push_back(line);
    }

    // Split in chunks
    std::vector<int> indexes = getChunkIndexes(grid);
    std::vector<std::vector<std::string>> chunks;
    int start = 0;
    for(int index : indexes) {
        std::vector<std::string> chunk;
        for(int i = 0; i < grid.size() ; i++) {
            std::string row;
            for(int j = start ; j < index ; j++) {
                row.push_back(grid[i][j]);
            }
            chunk.push_back(row);
        }
        start = index + 1;
        chunks.push_back(chunk);
    }
    return chunks;
}

long long computeChunk(std::vector<long long> values, char operation) {
    long long result = 0;
    if(operation == '*') {
        result = 1;
        for(long long value : values) {
            result *= value;
        }
    } else if (operation == '+') {
        for(long long value : values) {
            result += value;
        }
    }

    return result;
}

long long processChunk(std::vector<std::string> chunk, char operation, bool angle) {
    int row_count = chunk.size();
    int col_count = chunk[0].size();
    std::vector<long long> values;
    // Still not great but better i guess
    if(angle) {
        for(int i = 0 ; i < col_count ; i++) {
            std::string value_string;
            for(int j = 0 ; j < row_count ; j++) {
                if(chunk[j][i] != ' ') {
                    value_string.push_back(chunk[j][i]);
                }
            }
            values.push_back(std::stoll(value_string));
        }
    } else {
        for(int i = 0 ; i < row_count ; i++) {
            std::string value_string;
            for(int j = 0 ; j < col_count ; j++) {
                if(chunk[i][j] != ' ') {
                    value_string.push_back(chunk[i][j]);
                }
            }
            values.push_back(std::stoll(value_string));
        }
    }
    return computeChunk(values, operation);
}

std::string Day6::handlePart1Impl() {
    std::vector<std::vector<std::string>> chunks = fileToChunks();
    
    long long grand_total = 0;
    for(std::vector<std::string> chunk : chunks) {
        char operation = chunk[chunk.size()-1][0];
        chunk.pop_back();
        long long result = processChunk(chunk, operation, false);
        grand_total += result;
    }
    return "Grand total : " + std::to_string(grand_total);
}

std::string Day6::handlePart2Impl() {    
    std::vector<std::vector<std::string>> chunks = fileToChunks();
    
    long long grand_total = 0;
    for(std::vector<std::string> chunk : chunks) {
        char operation = chunk[chunk.size()-1][0];
        chunk.pop_back();
        long long result = processChunk(chunk, operation, true);
        grand_total += result;
    }
    return "Grand total : " + std::to_string(grand_total);
}

}
