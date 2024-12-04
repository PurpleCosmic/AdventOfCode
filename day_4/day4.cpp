#include <bits/stdc++.h>
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>


std::vector<std::string> get_lines(std::string filename) {
    std::vector<std::string> lines;

    std::string line;
    std::fstream file(filename);
    while (getline (file, line)) {
        lines.push_back(line);
    }
    return lines;
};

int check_matches(std::vector<std::string> lines, int r, int c) {
    int res = 0;
    // check horizontal;
    std::string hoz = "";
    for (int i = c; i < c+4 && i < lines[r].size(); i++) {
        hoz += lines[r][i];
    }
    if (hoz == "XMAS" || hoz == "SAMX") {
        res++;
    }
    // check up
    std::string up = "";
    for (size_t i = r; i < r+4 && i < lines.size(); i++) {
        up += lines[i][c];
    }
    if (up == "XMAS" || up == "SAMX") {
        res++;
    }

    // check diagonal
    std::string diag1 = "";
    for (int i = r, j = c; i < r+4 && i < lines.size() && j < lines[r].size(); i++, j++) {
        diag1 += lines[i][j];
    }
    if (diag1 == "XMAS" || diag1 == "SAMX") {
        res++;
    }

    std::string diag2 = "";
    for (int i = r, j = c; i > r-4 && i >= 0 && j < lines[r].size(); i--, j++) {
        diag2 += lines[i][j];
    }
    if (diag2 == "XMAS" || diag2 == "SAMX") {
        res++;
    }

    return res;
}

int main(int argc, char** argv) {
    auto file = get_lines("2024/day_4/day4example");

    int res = 0;
    for (size_t i = 0; i < file.size(); i++) {
        std::string line = file[i];
        for (size_t j = 0; j < line.size(); j++) {
            char c = line[j];
            if (c == 'X' || c == 'S') {
                res += check_matches(file, i, j);
            }
        }
    }
    std::cout << res << std::endl;
    return 0;
}
