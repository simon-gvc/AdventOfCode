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
        char delimiter = ',';
        std::stringstream stream(line);
        std::string value;
        std::vector<double> coord;
        while (std::getline(stream, value, delimiter)) {
            coord.push_back(std::stod(value));
        }
        Location loc{coord[0], coord[1], coord[2]};
        locations.push_back(loc);
    }
    return locations;
}

Connection connectShortest(std::vector<Location> locations, std::vector<Connection> connections) {
    // Our needle to track the lowst entry so far
    double lowest = -1;
    Connection lowest_connection;
    for(int i = 0 ; i < locations.size() ; i++) {
        Location current = locations[i];
        double shortest_distance;
        for(int j = 0 ; j < locations.size() ; j++) {
            // Skip checking itself
            if(i != j) {
                Location target = locations[j];
                double distance = getDistance(current, target);
                // Possible lower value
                if(lowest == -1 || distance < lowest) {
                    bool known = false;
                    Connection new_connection{distance, current, target};
                    // Do not double connect
                    for(Connection connection : connections) {
                        if(connection == new_connection) {
                            known = true;
                            break;
                        }
                    }
                    // Safely update the connections list
                    if(!known) {
                        lowest = distance;
                        lowest_connection = Connection{distance, current, target};
                    }
                }
            }
        }
    }
    return lowest_connection;
}

std::vector<std::set<std::string>> getCircuits(std::vector<Connection> connections) {
    // Convert and find connected circuits
    std::vector<std::set<std::string>> circuits;
    for(Connection con : connections) {
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
    }
    return circuits;
}

std::string Day8::handlePart1Impl() {
    std::vector<Location> locations = fileToLocations();
    std::vector<Connection> connections;
    // Magic number to regulate loop count
    int loop_count = 10;
    // Get the n shortest connections of all the locations, and track them
    for (int loop = 0; loop < loop_count ; loop++) {
        connections.push_back(connectShortest(locations, connections));
    }

    // Convert and find connected circuits
    std::vector<std::set<std::string>> circuits = getCircuits(connections);
    
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
    std::vector<Connection> connections;
    // Magic number to regulate loop count
    int loop_count = 6401;
    // Get the n shortest connections of all the locations, and track them
    int current_size = 1;
    int gap_check = 1;
    long long answer = 1LL;
    for (int loop = 0; loop < loop_count ; loop++) {
        gap_check--;
        Connection con = connectShortest(locations, connections);
        connections.push_back(con);
        // Yes, this is cheating, need to refactor and not manually process the data sets..... #box-of-shame
        if(loop > 6383) {
            // Check where we are at
            std::vector<std::set<std::string>> circuits = getCircuits(connections);
            int size = circuits.size();
            //std::cout << "For Iteration : " << loop << " Circuit count : " << circuits.size() << " and it has " << circuits[0].size() << " Elements but needs " << locations.size() << std::endl;
            if(size > 1) {
                current_size = size;
            } else if(size == 1 && circuits[0].size() == locations.size()) {
                //std::cout << "Found it?! " << connections.back().a.to_string() << " - " <<  connections.back().b.to_string()  <<  std::endl;
                answer *= con.a.x * con.b.x;
                break;
            }
        }
    }

    
    std::vector<std::set<std::string>> circuits = getCircuits(connections);
    int size = circuits.size();
    //std::cout << "For Iteration : " << loop_count << " Circuit count : " << circuits.size() << " and it has " << circuits[0].size() << " Elements but needs " << locations.size() << std::endl;

    return "Distance from wall = " + std::to_string(answer);
}

}