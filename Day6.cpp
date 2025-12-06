#include "2025/Days2025.h"
#include "FileReader.h"
#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <fstream>
#include <utility>
#include <set>

namespace Year2025 {

// Get start and end values from a range string
std::vector<std::vector<std::string>> makeGrid() {
    std::vector<std::vector<std::string>> grid;
    std::ifstream file("input/2025/day6.txt");
    std::string line;

    while (std::getline(file, line)) {
        char delimiter = ' ';
        std::stringstream stream(line);
        std::vector<std::string> row;
        std::string value;
        while (std::getline(stream, value, delimiter)){
            // Only leave characters in our return value
            if (value.empty()) continue;
            row.push_back(value);
        }
        grid.push_back(row);
    }
    return grid;
}

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
    return indexes;
}

std::vector<std::vector<std::string>> gridToChuncks(std::vector<std::string> grid) {
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

    // REFACTOR THIS, DONT FORGET LAST ONE
    std::vector<std::string> chunk;
    for(int i = 0; i < grid.size() ; i++) {
        std::string row;
        for(int j = start ; j < grid[0].size() ; j++) {
            row.push_back(grid[i][j]);
        }
        chunk.push_back(row);
    }
    chunks.push_back(chunk);
    return chunks;
}

long long processChunk(std::vector<std::string> chunk) {
    int row_count = chunk.size();
    int col_count = chunk[0].size();

    std::vector<long long> values;

    for(int i = 0 ; i < col_count ; i++) {
        std::string value_string;
        for(int j = 0 ; j < row_count - 1 ; j++) {
            if(chunk[j][i] != ' ') {
                value_string.push_back(chunk[j][i]);
            }
        }
        values.push_back(std::stoll(value_string));
    }

    long long result = 0;
    char operation = chunk[chunk.size()-1][0];
    if(operation == '*') {
        // Multiplication with 0 would not be very usefull.
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

std::string Day6::handlePart1Impl() {
    // Get our variables to start
    std::vector<std::vector<std::string>> grid = makeGrid();
    int row_count = grid.size();
    int col_count = grid[0].size();
    long long grand_total;

    // Change the approach and go for columns first
    for(int i = 0; i < col_count ; i++) {
        std::vector<long long> values;
        long long result = 0;
        
        // Get all values from the column, skip the operation value
        for(int j = 0 ; j < row_count - 1 ; j++) {
            values.push_back(std::stoll(grid[j][i]));
        }

        // Get the operation and execute the calculation on the values
        std::string operation = grid[row_count-1][i];
        if(operation[0] == '*') {
            // Multiplication with 0 would not be very usefull.
            result = 1;
            for(long long value : values) {
                result *= value;
            }
        } else if (operation[0] == '+') {
            for(long long value : values) {
                result += value;
            }
        }
        // Add to grand total
        grand_total += result;
    }

    return "Grand total : " + std::to_string(grand_total);
}

std::string Day6::handlePart2Impl() {    
    std::ifstream file("input/2025/day6.txt");
    std::string line;

    // Transrom to a grid of strings
    std::vector<std::string> grid;
    while(std::getline(file, line)) {
        grid.push_back(line);
    }

    // Chop up the grid in chunks, based on empty columns,
    std::vector<std::vector<std::string>> chunks = gridToChuncks(grid);
    
    // Process all chunks, and get a grand total
    long long grand_total = 0;
    for(std::vector<std::string> chunk : chunks) {
        long long result = processChunk(chunk);
        grand_total += result;
    }
    return "Grand total : " + std::to_string(grand_total);
}

}