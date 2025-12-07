#include "2025/Days2025.h"
#include "FileReader.h"
#include <string>
#include <vector>
#include <chrono>
#include <iostream>

namespace Year2025 {

std::vector<std::vector<char>> getMap() {
    std::ifstream file("input/2025/day7.txt");
    std::string line;

    std::vector<std::vector<char>> map;

    // Transform to a grid of strings
    while(std::getline(file, line)) {
        std::vector<char> row;
        for(char c : line) {
            row.push_back(c);
        }
        map.push_back(row);
    }
    return map;
}

long long beam(int row, int col, std::vector<std::vector<char>>& map, std::vector<std::vector<long long>>& memo) {
    // Return one when we reached the bottom
    if(row >= map.size() - 1) {
        return 1;
    }

    // Check memo first to not double compute
    if(memo[row][col] != -1) {
        return memo[row][col];
    }

    long long count = 0;
    char next_character = map[row + 1][col];
    switch(next_character) {
        case '.' :
            count += beam(row + 1, col, map, memo);
            break;
        case '^' :
            count += beam(row + 2, col - 1, map, memo);
            count += beam(row + 2, col + 1, map, memo);
            break;
        default :
            break;
    }

    // Post the memo and return the value
    memo[row][col] = count;
    return count;
}

std::string Day7::handlePart1Impl() {
    std::vector<std::vector<char>> map = getMap();
    int row_count = map.size();
    int col_count = map[0].size();

    // Just draw the map like the example and look at the result
    for(int row = 0 ; row < row_count - 1 ; row++) {
        // Wont get pretty from here
        for(int col = 0 ; col < col_count ; col++) {
            char current_char = map[row][col];
            switch(current_char) {
                case 'S':
                    map[row+1][col] = '|';
                    break;
                case '|':
                    if(map[row+1][col] == '.') {
                        map[row+1][col] = '|';
                    }
                    break;
                case '^':
                    // Check if we got an incoming beam
                    if(map[row-1][col] == '|') {
                        if(map[row + 1][col - 1] == '.') {
                            map[row + 1][col - 1] = '|';
                        }
                        // Check right,
                        if(map[row + 1][col + 1] == '.') {
                            map[row + 1][col + 1] = '|';
                        }
                    }
                    break;
                default:
                    break;
            }
        }
    }

    // Count score, ^ without | above is invalid.
    int valid = 0;
    for(int row = 0 ; row < row_count ; row++) {
        for(int col = 0 ; col < col_count ; col++) {
            if(map[row][col] == '^') {
                if(map[row - 1][col] == '|') {
                    valid++;
                }
            }
        }
    }

    return "Activated Switches : " + std::to_string(valid);
}

std::string Day7::handlePart2Impl() {        
    std::vector<std::vector<char>> map = getMap();
    std::vector<std::vector<long long>> memo(map.size(),std::vector<long long>(map[0].size(), -1));

    // Find the start,
    int start_col = 0;
    long long count = 0;
    for(int i = 0 ; i < map[0].size() ; i++) {
        if(map[0][i] == 'S') {
            count = beam(1, i, map, memo);
            break;
        }
    }

    return "Total Beams : " + std::to_string(count);
}

}