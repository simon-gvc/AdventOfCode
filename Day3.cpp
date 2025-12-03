#include "2025/Days2025.h"
#include "FileReader.h"
#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <fstream>
#include <utility>

namespace Year2025 {

long long calculateJoltage(int MAX_SIZE) {
    std::ifstream file("input/2025/day3.txt");
    std::string line;

    long long total_joltage = 0;

    while (std::getline(file, line)) {

        // Keep track of the index while we loop through it,
        int start_point = 0;

        while(line.size() > MAX_SIZE && start_point < line.size()) {

            // Ensure starting position and gap size,
            int current_index = start_point;
            int current_value = 0;
            int gap_size = line.size() - MAX_SIZE + 1;

            // Try to find the highest value given the gap we allow
            for(int i = 0 ; i < gap_size ; i++) {

                int value = line[i + start_point] - '0';
                if(value > current_value) {
                    current_value = value;
                    current_index = i + start_point;
                }
            }

            // Evaluate the gap check
            if(current_index == start_point) {
                // If the first index of the gap is still the highest value, increment our start index and give it another try,
                start_point++;
            } else {
                // If not, we can remove the first entry of our gap,
                line.erase(start_point, 1);
            }
        }

        // Resize to ensure we dont exceed line size,
        line.resize(MAX_SIZE);

        total_joltage += std::stoll(line);
    }
    return total_joltage;
}

std::string Day3::handlePart1Impl() {
    long long total_joltage = calculateJoltage(2);
    return "Total Joltage : " + std::to_string(total_joltage);
}

std::string Day3::handlePart2Impl() {
    long long total_joltage = calculateJoltage(12);
    return "Total Joltage " + std::to_string(total_joltage);
}

}