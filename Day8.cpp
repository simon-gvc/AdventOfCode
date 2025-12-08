#include "2025/Days2025.h"
#include "FileReader.h"
#include <string>
#include <vector>
#include <chrono>
#include <iostream>
#include <utility>
#include <cmath>
#include <set>

namespace Year2025 {

struct Location {
    double x, y, z;

    bool operator==(const Location& other) const {
        return x == other.x && y == other.y && z == other.z;
    }

    std::string to_string() const {
        std::ostringstream stream;
        stream << x << "x" << y << "x" << z;
        return stream.str();
    }
};

struct Connection {
    double distance;
    Location a, b;

    bool operator==(const Connection& other) const {
        return (a == other.a && b == other.b) || (a == other.b && b == other.a);
    }
    
    bool operator<(const Connection& other) const {
        return distance < other.distance;
    }
};

double getDistance(Location one, Location two) {
    double x = two.x - one.x;
    double y = two.y - one.y;
    double z = two.z - one.z;

    return std::sqrt(x*x + y*y + z*z);
}

std::vector<Location> fileToLocations() {
    std::ifstream file("input/2025/day8.txt");
    std::string line;
    std::vector<Location> locations;

    // Convert input file into x,y,z locations
    while (std::getline(file, line)) {
        std::stringstream stream(line);
        std::string x_str, y_str, z_str;
        
        std::getline(stream, x_str, ',');
        std::getline(stream, y_str, ',');
        std::getline(stream, z_str, ',');
        
        Location loc{std::stod(x_str), std::stod(y_str), std::stod(z_str)};
        locations.push_back(loc);
    }
    return locations;
}

std::vector<Connection> getAllConnectionsSortedByDistance(std::vector<Location> locations) {
    std::vector<Connection> connections;
    // Loop the Locations and collect all possible connections between the nodes
    for(int i = 0 ; i < locations.size() - 1 ; i++) {
        Location a = locations[i];
        for(int j = i + 1 ; j < locations.size() ; j++) {
            Location b = locations[j];
            double distance = getDistance(a, b);
            Connection connection{distance, a, b};
            connections.push_back(connection);
        }
    }
    
    std::sort(connections.begin(), connections.end());
    return connections;
}

std::vector<std::set<std::string>> updateCircuits(std::vector<std::set<std::string>> circuits, Connection con) {
    Location a = con.a;
    bool a_known = false;
    int a_circuit = 0;
    Location b = con.b;
    bool b_known = false;
    int b_circuit = 0;
    for(int i = 0 ; i < circuits.size() ; i++) {
        std::set<std::string> circuit = circuits[i];
        for(std::string value : circuit) {
            if(value == a.to_string()) {
                a_known = true;
                a_circuit = i;
            }
            if(value == b.to_string()) {
                b_known = true;
                b_circuit = i;
            }
        }
    }
    if(!a_known && !b_known) {
        std::set<std::string> new_set{a.to_string(), b.to_string()};
        circuits.push_back(new_set);
    } else if (a_known && !b_known) {
        circuits[a_circuit].insert(b.to_string());
    } else if (!a_known && b_known) {
        circuits[b_circuit].insert(a.to_string());
    } else if (b_known && a_known && a_circuit != b_circuit) {
        std::set<std::string> new_set = circuits[a_circuit];
        std::set<std::string> old_set = circuits[b_circuit];
        new_set.insert(old_set.begin(), old_set.end());
        circuits[a_circuit] = new_set;
        circuits.erase(circuits.begin() + b_circuit);
        
    }
    return circuits;
}

std::string Day8::handlePart1Impl() {
    std::vector<Location> locations = fileToLocations();
    std::vector<Connection> connections = getAllConnectionsSortedByDistance(locations);
    std::vector<std::set<std::string>> circuits;

    // Magic number to regulate loop count
    int loop_count = 1000;
    for(int i = 0 ; i < loop_count ; i++) {
        circuits = updateCircuits(circuits, connections[i]);
    }

    // Get the highest 3 circuits and calculate output
    std::sort(circuits.begin(), circuits.end(),
              [](const std::set<std::string>& a, const std::set<std::string>& b) {
                  return a.size() > b.size();
              });
    long long largest_size = 1LL;
    int count = 0;
    for(std::set<std::string> circuit : circuits) {
        largest_size *= circuit.size();
        count++;
        if(count == 3) {
            break;
        }
    }

    return "Circuit Size = " + std::to_string(largest_size);
}

std::string Day8::handlePart2Impl() {     
    std::vector<Location> locations = fileToLocations();
    std::vector<Connection> connections = getAllConnectionsSortedByDistance(locations);
    std::vector<std::set<std::string>> circuits;
    int first_circuit_count = 0;
    int iteration = 0;
    
    while(first_circuit_count != locations.size()) {
        circuits = updateCircuits(circuits, connections[iteration]);
        iteration++;
        first_circuit_count = circuits[0].size();
    }

    iteration--;
    long long answer = 1LL * connections[iteration].a.x * connections[iteration].b.x;

    return "Distance from wall = " + std::to_string(answer);
}
}
