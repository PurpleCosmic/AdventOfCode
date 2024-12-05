#include <bits/stdc++.h>
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include <unordered_map>
// I LOVE GOOD CODE !!!!!
static std::unordered_map<int, int> after_rules = {};
static std::unordered_map<int, std::vector<int>> before_rules = {};

std::vector<std::vector<int>> get_lines(std::string filename) {
    std::vector<std::vector<int>> lines;

    std::string line;
    std::fstream file(filename);
    bool adding_rules = true;
    while (getline (file, line)) {
        std::stringstream ss(line);
        if (line.empty()) {
            adding_rules = false;
        } else if (adding_rules) {
            int pos = line.find('|');
            std::string pre = line.substr(0, pos);
            line.erase(0, pos+1);

            after_rules.insert({std::stoi(pre) , std::stoi(line)});
            before_rules[std::stoi(line)].push_back(std::stoi(pre));

            std::cout << line << ": " << pre << std::endl;
        } else {
            std::string num_str;
            std::vector<int> report;
            while ( getline (ss, num_str, ',') ) {
                report.push_back( std::stoi(num_str) );
            }
            lines.push_back(report);
        }

    }
    return lines;
};

int main(int argc, char** argv) {
    auto file = get_lines("2024/day_5/input");

    int res = 0;

    std::vector<std::vector<int>> valid_lines;
    for (auto line : file) {
        bool valid = true;

        for (int i = 0; i < line.size(); i++) {

            auto rules = before_rules[line[i]];

            for (int c : rules) {
                bool before_valid = true;
                for (int j = i+1; j < line.size(); j++) {
                    if (line[j] == c) {
                        before_valid = false;
                    }
                }

                if (!before_valid) {
                    valid = false;
                }
            }        
        }
        if (valid) {
            valid_lines.push_back(line);
        } else {
            std::cout << "invalid line: ";
            for (int k : line) {
                std::cout << k << " ";
            }
            std::cout << std::endl;
        }
    }

    for (auto line : valid_lines) {
        res += line[line.size()/2];
    }

    std::cout << res << std::endl;
    return 0;
}
