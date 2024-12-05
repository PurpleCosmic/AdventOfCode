#include <bits/stdc++.h>
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include <unordered_map>
// oh my goodness gracious this is code so much worse than the last one oh my god I need to END it!!!!
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


bool less_than(int i, int j) {
    auto rules = before_rules[i];
    for (int k : rules) {
        if (j == k) {
            return false;
        }
    }
    return true;
};

bool is_sorted_line(std::vector<int> line) {
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
    return valid;
}

std::vector<int> rule_sort(std::vector<int> line, std::unordered_map<int, std::vector<int>> rules) {
    std::vector<int> sorted;
    for (int i : line) {
        for (int j : line) {
            if (!less_than(i, j)) {
                if (std::count(sorted.begin(), sorted.end(), j) <= 0 ) {
                    sorted.push_back(j);  
                }
            }
        }
        if (std::count(sorted.begin(), sorted.end(), i) <= 0 ) {
            sorted.push_back(i);  
        }
    }
    if (!is_sorted_line(sorted)) {
        return (rule_sort(sorted, rules));
    } else {
        return sorted;
    }
}


int main(int argc, char** argv) {
    auto file = get_lines("2024/day_5/input");

    int res = 0;

    std::vector<std::vector<int>> invalid_lines;
    for (auto line : file) {
         if (!is_sorted_line(line)) {
            invalid_lines.push_back(line);
        }
    }

    for (auto line : invalid_lines) {
        auto sorted = rule_sort(line, before_rules);
        for (auto i : sorted) {
            std::cout << i << " ";
        }
        std::cout << std::endl;
        res += sorted[sorted.size()/2];
    }

    std::cout << res << std::endl;
    return 0;
}
