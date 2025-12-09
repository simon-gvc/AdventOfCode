#include "2025/Days2025.h"
#include "FileReader.h"
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

namespace Year2025 {

std::string Day9::handlePart1Impl() {
    std::ifstream file("input/2025/day9.txt");
    std::string line;
    
    std::vector<std::pair<long long, long long>> points;

    // translate input to pairs
    while (std::getline(file, line)) {
        std::stringstream stream(line);
        std::string x_str, y_str;
        
        std::getline(stream, x_str, ',');
        std::getline(stream, y_str, ',');

        std::pair point{std::stoll(x_str), std::stoll(y_str)};
        points.push_back(point);
    }

    long long biggest_square = 0;

    for(int i = 0 ; i < points.size() - 1 ; i++) {
        std::pair<long long, long long> left = points[i];
        for(int j = i + 1 ; j < points.size() ; j++) {
            std::pair<long long, long long> right = points[j];
            long long size = (std::abs(left.first - right.first) + 1) * (std::abs(left.second - right.second) + 1);
            if(size > biggest_square) {
                biggest_square = size;
            }
        }
    }

    // When its this easy for P1, you know you fucked,
    return "Largest Square has size : " + std::to_string(biggest_square);
}

std::string Day9::handlePart2Impl() {    
    std::ifstream file("input/2025/day9.txt");
    std::string line;
    std::vector<std::pair<long long, long long>> points;
    std::cout << "Starting" << std::endl;

    // Translate input to pairs
    long long x_high = 0;
    long long y_high = 0;
    while (std::getline(file, line)) {
        std::stringstream stream(line);
        std::string x_str, y_str;       
        std::getline(stream, y_str, ',');
        std::getline(stream, x_str, ',');
        long long x = std::stoll(x_str);
        long long y = std::stoll(y_str);

        if(x > x_high) {
            x_high = x;
        }
        if(y > y_high) {
            y_high = y;
        }

        std::pair point{x, y};
        points.push_back(point);
    }

    // Create corresponding grid with . to work with,
    std::vector<std::vector<char>> grid(x_high + 2, std::vector<char>(y_high + 2, '.'));

    // Draw Points
    std::cout << "Drawing Points" << std::endl;
    for(std::pair<long long, long long> point : points) {
        grid[point.first][point.second] = '#';
    }
    
    // Draw lines
    std::cout << "Drawing lines" << std::endl;
    for(int i = 0 ; i < points.size() - 1 ; i++) {
        std::pair<long long, long long> point = points[i];
        int x_index = -1;
        int y_index = -1;
        for(int j = i + 1 ; j < points.size() ; j++) {
            if(points[i].first == points[j].first) {
                x_index = j;
                // HORIZONTAL Line
                long long high = std::max(points[i].second, points[j].second);
                long long low = std::min(points[i].second, points[j].second);
                for(int left = low + 1 ; left < high ; left++) {
                    grid[points[i].first][left] = 'X';
                }
            }

            if(points[i].second == points[j].second) {
                y_index = j;
                // VERTICAL Line
                long long high = std::max(points[i].first, points[j].first);
                long long low = std::min(points[i].first, points[j].first);
                for(int down = low + 1 ; down < high ; down++) {
                    grid[down][points[i].second] = 'X';
                }
            }
        }
    }

    // Filling the gap, first Row by Row
    std::cout << "Filling Map" << std::endl;
    for(int i = 0 ; i < grid.size() ; i++) {
        // We need to get some status tracking going on, 
        //  1 : empty (default state: .)
        //  2 : found an opening point
        //  3 : writing mode, enter when hitting a wall and close when leaving it,
        int state = 1;
        // Now lets go with columns
        for(int j = 0 ; j < grid[i].size() ; j++) {
            char field = grid[i][j];
            switch (field) {
                
                case '.':
                    // Empty space, we either fill or not
                    switch (state) {
                        case 3:
                            grid[i][j] = 'x';
                        default:
                            break;
                    }
                    break;
                
                    case '#':
                    // Dealing with points, first one always opens, from there we need to check how things are after closing, (should) be only 1 pair per line,
                    switch (state) {
                        case 1: 
                            // Found a corner from empty state, the rest should be filled in already,
                            state = 2;
                            break;
                        case 2:
                            // This one can get ugly, either where in empty or writing mode. lets look up 1 line and see, 
                            if(grid[i-1][j] == 'x' || (grid[i-1][j] == 'X' && grid[i-1][j-1] != 'x')) {
                                // Corner is still in writing mode, 
                                state = 3;
                            } else {
                                // Found a closing corner, lets state shift back to empty
                                state = 1;
                            }
                        default:
                            break;
                    }
                    break;
                
                // Dealing with walls, (should) be easy, basically we toggle writing an non writing mode right?!
                case 'X':
                    switch(state) {
                        case 1:
                            // Empty mode, go writing i guess
                            state = 3;
                            break;
                        case 3:
                            // Writing go to empty
                            state = 1;
                            break;
                        default:
                            break;
                    }
                    break;

                default:
                    break;
            }
        }
    }

    // Lets pray the lords of our input data,
    std::cout << "Now Pray" << std::endl;
    long long biggest_square = 0;
    for(int i = 0 ; i < points.size() - 1 ; i++) {
        std::pair<long long, long long> left = points[i];
        for(int j = i + 1 ; j < points.size() ; j++) {
            // 
            std::pair<long long, long long> right = points[j];
            long long size = (std::abs(left.first - right.first) + 1) * (std::abs(left.second - right.second) + 1);

            // Early continue before it gets messy, throw out non candidates now,
            if(size <= biggest_square) {
                continue;
            }

            // Shame, that was to optimistic, lets go check our boundaries then...
            long long row_high = std::max(left.first, right.first);
            long long row_low = std::min(left.first, right.first);
            long long col_high = std::max(left.second, right.second);
            long long col_low = std::min(left.second, right.second);

            bool valid = true;

            // Go over borders vertically, check both sides
            for(long long row = row_low ; row <= row_high ; row++) {
                if(grid[row][col_low] == '.' || grid[row][col_high] == '.') {
                    valid = false;
                }
            }
            
            // Early continue again...
            if(!valid) {
                continue;
            }

            // Go over borders horizontally, check both sides
            for(long long col = col_low ; col <= col_high ; col++) {
                if(grid[row_low][col] == '.' || grid[row_high][col] == '.') {
                    valid = false;
                }
            }

            if(valid) {
                biggest_square = size;
            }

        }
    }

    return "Largest Square has size : " + std::to_string(biggest_square);
}

}