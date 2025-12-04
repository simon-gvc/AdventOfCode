#include "2025/Days2025.h"
#include "FileReader.h"
#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <fstream>
#include <utility>

namespace Year2025 {

int checkAllNeighbours(std::vector<std::vector<char>> grid, int row, int col) {
    // We know we will count the current position so start negative 1,
    int count = -1;
    for (int i = row - 1 ; i <= row + 1 ; i++) {
        for (int j = col - 1; j <= col + 1 ; j++) {
            try {
                char neighbour = grid.at(i).at(j);
                if(neighbour == '@') {
                    count++;
                }
            }
            // Out of bounds
            catch(const std::exception& e) {}
        }
    }
    return count;
}

std::vector<std::vector<char>> createGrid() {
    std::ifstream file("input/2025/day4.txt");
    std::string line;

    std::vector<std::vector<char>> grid;
    while (std::getline(file, line)) {
        grid.emplace_back(line.begin(), line.end());
    }

    return grid;
}

std::string Day4::handlePart1Impl() {
    // Setup for main loop
    std::vector<std::vector<char>> grid = createGrid();
    int rolls = 0;
    for(int i = 0; i < grid.size() ; i++) {
        for(int j = 0 ; j < grid[i].size() ; j++) {
            // Only check packages
            if(grid[i][j] == '@') {
                // Check for the count of neighbours and pick up if there is room
                int count = checkAllNeighbours(grid, i, j);
                if(count < 4) {
                    rolls++;
                }
            }
        }
    }
    return "Total rolls of paper taken : " + std::to_string(rolls);
}

std::string Day4::handlePart2Impl() {
    // Setup for main loop
    std::vector<std::vector<char>> grid = createGrid();
    int rolls = 0;
    int last_round = -1;

    while (rolls != last_round) {
        last_round = rolls;

        for(int i = 0; i < grid.size() ; i++) {
            for(int j = 0 ; j < grid[i].size() ; j++) {
                // Only check packages
                if(grid[i][j] == '@') {
                    // Check for the count of neighbours and pick up if there is room
                    int count = checkAllNeighbours(grid, i, j);
                    if(count < 4) {
                        rolls++;
                        grid[i][j] = '.';
                    }
                }
            }
        }
    }

    return "Total rolls of paper taken : " + std::to_string(rolls);
}

}