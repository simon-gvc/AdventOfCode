#include "2025/Days2025.h"
#include "FileReader.h"
#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <fstream>
#include <utility>

namespace Year2025 {

// Parse ranges from input file
std::vector<std::string> parseRangesFromFile(const std::string& filepath) {
    std::ifstream file(filepath);
    std::string line;
    std::vector<std::string> ranges;

    while (std::getline(file, line)) {
        char delimiter = ','; 
        std::stringstream stream(line);
        std::string range;

        while (std::getline(stream, range, delimiter)) {
            ranges.push_back(range);
        }
    }

    return ranges;
}

// Get start and end values from a range string
std::pair<long long, long long> getRangeValues(const std::string& range) {
    char delimiter = '-';
    std::stringstream stream(range);
    std::string value;
    std::vector<long long> values;

    while (std::getline(stream, value, delimiter)) {
        values.push_back(std::stoll(value));
    }

    return {values[0], values[1]};
}

std::string Day2::handlePart1Impl() {
    // Extract ranges from file
    std::vector<std::string> ranges = parseRangesFromFile("input/2025/day2.txt");

    // End product
    long long product_of_invalids = 0;

    // Process each range
    for(const std::string& range : ranges) {
        auto [start, end] = getRangeValues(range);

        // Iterate every value in between
        for(long long i = start; i <= end; i++) {
            std::string value_string = std::to_string(i);

            // Only care about even digit numbers?
            if(value_string.size() % 2 == 0) {
                int half = value_string.size() / 2;
                std::string left = value_string.substr(0, half);
                std::string right = value_string.substr(half, half);
                if(left == right) {
                    product_of_invalids += i;
                }
            } 
        }
    }
    
    return "Product of all invalid numbers : " + std::to_string(product_of_invalids);
}

std::string Day2::handlePart2Impl() {
    // Extract ranges from file
    std::vector<std::string> ranges = parseRangesFromFile("input/2025/day2.txt");

    // End product
    long long product_of_invalids = 0;

    // Process each range
    for(const std::string& range : ranges) {
        auto [start, end] = getRangeValues(range);

        // Iterate every value in between
        for(long long i = start; i <= end; i++) {
            std::string value_string = std::to_string(i);
            
            // Find the halfway point
            int half = value_string.size() / 2;
            for (int j = 1 ; j <= half ; j++) {

                // Make sure we can fit in the pattern
                if(value_string.size() % j == 0) {
                    std::string needle = value_string.substr(0, j);
                    std::string proposed_pattern;
                    
                    // Build the predicted pattern based on the needle and total size of the string
                    for(int k = 0 ; k < value_string.size() / j; k++) {
                        proposed_pattern += needle;
                    }

                    // If it matches, we got it, make sure to not recheck the same j though, 
                    if (proposed_pattern == value_string) {
                        product_of_invalids += i;
                        break;
                    }
                }
            }
        }
    }
    
    return "Product of all invalid numbers : " + std::to_string(product_of_invalids);
}

}