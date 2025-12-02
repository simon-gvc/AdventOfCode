#include "2025/Days2025.h"
#include "FileReader.h"
#include <string>
#include <sstream>
#include <iostream>
#include <vector>

namespace Year2025 {

std::string Day2::handlePart1Impl(const std::string& input) {
    std::ifstream file("input/2025/day2.txt");
    std::string line;
    std::vector<std::string> ranges;

    // End product
    long long product_of_invalids = 0;

    // Extract ranges
    while (std::getline(file, line)) {
        char delimiter = ','; 

        std::stringstream ss(line);
        std::string range;

        while (std::getline(ss, range, delimiter)) {
            ranges.push_back(range);
        }
    }

    // Break up the ranges into start end value pairs
    for(const std::string& range : ranges) {
        char delimiter = '-';
        
        std::stringstream ss(range);
        std::string value;

        std::vector<long long> values;

        while (std::getline(ss, value, delimiter)) {
            values.push_back(std::stoll(value));
        }

        // Iterate every value in between,
        for(long long i = values[0] ; i <= values[1] ; i++) {
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

std::string Day2::handlePart2Impl(const std::string& input) {
    std::ifstream file("input/2025/day2.txt");
    std::string line;
    std::vector<std::string> ranges;

    // End product
    long long product_of_invalids = 0;

    // Extract ranges
    while (std::getline(file, line)) {
        char delimiter = ','; 

        std::stringstream ss(line);
        std::string range;

        while (std::getline(ss, range, delimiter)) {
            ranges.push_back(range);
        }
    }

    // Break up the ranges into start end value pairs
    for(const std::string& range : ranges) {
        char delimiter = '-';
        
        std::stringstream ss(range);
        std::string value;

        std::vector<long long> values;

        while (std::getline(ss, value, delimiter)) {
            values.push_back(std::stoll(value));
        }

        // Iterate every value in between,
        for(long long i = values[0] ; i <= values[1] ; i++) {
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
