#include "2025/Days2025.h"
#include "FileReader.h"
#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <fstream>
#include <utility>

namespace Year2025 {

std::string Day3::handlePart1Impl(const std::string& input) {
    
    std::ifstream file("input/2025/day3.txt");
    std::string line;

    int total_joltage = 0;

    while (std::getline(file, line)) {
        int left_index = 0;
        int left_value = 0;
        int right_index = 0;
        int right_value = 0;

        // Find the highest possible left value and index
        for (int i = 0; i < line.size() - 1; i++) {
            
            // Get the int equivalent now since c++ doesnt make life easy
            int value = line[i] - '0';
            if(value > left_value) {
                left_value = value;
                left_index = i;
            }
        }
        // Now, reverse the order and find the right value
        for (int i = line.size() ; i > left_index ; i--) {

            // Get the int equivalent now since c++ doesnt make life easy
            int value = line[i] - '0';
            if(value > right_value) {
                right_value = value;
                right_index = i;
            }
        }

        int joltage = std::stoi(std::to_string(left_value) + std::to_string(right_value));
        total_joltage += joltage;
    }
    return "Total Joltage : " + std::to_string(total_joltage);
}

std::string Day3::handlePart2Impl(const std::string& input) {
   
    std::ifstream file("input/2025/day3.txt");
    std::string line;

    long long total_joltage = 0;
    int MAX_SIZE = 12;

    while (std::getline(file, line)) {

        // Keep track of the index while we loop through it,
        int start_point = 0;

        while(line.size() > 12) {

            // Set some variables before we loop through the line.
            int current_index = start_point;
            int current_value = 0;
            int gap_size = line.size() - MAX_SIZE + 1;

            // Try to find the highest value given the gap we allow
            for(int i = 0 ; i < gap_size ; i++) {
                
                // Get the int equivalent now since c++ doesnt make life easy
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
                // If not, we can remove the first entry of our gap, we will eventually hit the same condition applied removing them 1 by 1 if > 1,
                line.erase(start_point, 1);
            }

            // Escape if we exceed and just reduce to max size?
            if(start_point > line.size()) {
                line.resize(MAX_SIZE);
                break;
            }
        }

        total_joltage += std::stoll(line);
    }
    return "Total Joltage " + std::to_string(total_joltage);
}

}