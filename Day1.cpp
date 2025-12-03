#include "2025/Days2025.h"
#include "FileReader.h"
#include <string>
#include <iostream>

namespace Year2025 {

std::string Day1::handlePart1Impl() {
    std::ifstream file("input/2025/day1.txt");
    std::string line;

    // Define starting position
    int position = 50;
    int count = 0;

    while (std::getline(file, line)) {

        // Extract value from input line
        int value = std::stoi(line.substr(1)) % 100;

        // Update position based on instruction and value
        if(!line.empty() && line[0] == 'L'){
            position -= value;
            if(position < 0) {
                position += 100;
            }
        } else if(!line.empty() && line[0] == 'R') {
            position += value;
            if(position > 99) {
                position %= 100;
            }
        }

        // Check if we hit our target, increment count if so
        if(position == 0) {
            count++;
        }
    }

    return "Count of zeros: " + std::to_string(count);
}

std::string Day1::handlePart2Impl() {
    std::ifstream file("input/2025/day1.txt");
    std::string line;

    // Define starting position
    int position = 50;
    int count = 0;

    while (std::getline(file, line)) {

        // Get Value and Direction, use it to calcuate the Movement
        int value = std::stoi(line.substr(1));
        char direction = line[0];
        int movement = (direction == 'L') ? -value : value;

        // Add full loops to the count and remove the remainder
        count += std::abs(movement) / 100;
        movement %= 100;

        // Get next position
        int next_position = (position + movement + 100) % 100;

        // Evaluate, going Right is easy since it does not hit the landing 0 problem
        if(movement > 0 && next_position < position) {
            count++;
        } 
        // Consider landing and departing at 0 going Left, I dont like it.
        else if (movement < 0 && (next_position > position || next_position == 0) && position != 0) {
            count++;
        }

        // Update position
        position = next_position;
    }

    return "Count of zeros: " + std::to_string(count);
}

}