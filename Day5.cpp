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
std::pair<long long, long long> getRangesValues(const std::string& range) {
    char delimiter = '-';
    std::stringstream stream(range);
    std::string value;
    std::vector<long long> values;

    while (std::getline(stream, value, delimiter)) {
        values.push_back(std::stoll(value));
    }

    return {values[0], values[1]};
}

std::string Day5::handlePart1Impl() {
    std::ifstream file("input/2025/day5.txt");
    std::string line;

    // Parse input file
    std::vector<std::pair<long long, long long>> ranges;
    std::vector<long long> values;
    bool getting_ranges = true;
    while (std::getline(file, line)) {
        if (line == "") {
            getting_ranges = false;
        } else if(getting_ranges) {
            std::pair<long long, long long> range = getRangesValues(line);
            ranges.push_back(range);
        } else {
            values.push_back(std::stoll(line));
        }
    }

    // Check all ranges, break when we hit something to not extra count,
    int valid_ingredients = 0;
    for(const long long& value : values){
        for(std::pair<long long, long long> range : ranges) {
            if(value >= range.first && value <= range.second) {
                valid_ingredients++;
                break;
            }
        }
    }

    return "Amount of valid ingredients : " + std::to_string(valid_ingredients);
}

std::string Day5::handlePart2Impl() {    
    std::ifstream file("input/2025/day5.txt");
    std::string line;

    // Parse input file
    std::vector<std::pair<long long, long long>> ranges;
    while (std::getline(file, line)) {
        if (line == "") {
            break;
        } else {
            std::pair<long long, long long> range = getRangesValues(line);
            ranges.push_back(range);
        }
    }

    // Simplify things a bit by sorting before we start,
    sort(ranges.begin(), ranges.end());
    for(int i = 0 ; i < ranges.size() ; i++) {
        // Keep track of the initial range so we can start expanding it
        std::pair<long long, long long> current_range = {ranges[i].first, ranges[i].second};
        for(int j = i + 1 ; j < ranges.size() ; j++) {
            // Check on overlap
            if (current_range.second >= ranges[j].first && current_range.first <= ranges[j].second) {
                // Update current range with low and high points
                current_range.first = current_range.first < ranges[j].first ? current_range.first : ranges[j].first;
                current_range.second = current_range.second > ranges[j] . second ? current_range.second : ranges[j].second;

                // Not the cleanest but it works, remove the entry we just combined and reduce our iterator a step.
                ranges.erase(ranges.begin() + j);
                j--;
            } else {
                // Since where sorted, just get outta here,
                break;
            }
        }
        // Update the initial value,
        ranges[i] = current_range;
    }

    // Now its a matter of some simple calculations iso iterating every entry and put it to 
    long long valid_ingredients = 0;
    for(std::pair<long long, long long> range : ranges) {
        valid_ingredients += range.second - range.first + 1;
    }
    
    return "Amount of valid ingredients : " + std::to_string(valid_ingredients);
}

}