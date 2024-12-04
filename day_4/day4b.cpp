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

    char tl = lines[r-1][c-1];
    char tr = lines[r-1][c+1];
    char bl = lines[r+1][c-1];
    char br = lines[r+1][c+1];

    if ((tl == 'M' && br == 'S') || (br == 'M' && tl == 'S') ) {
        if ((tr == 'M' && bl == 'S') || (bl == 'M' && tr == 'S') ) {
               res++;
        }    
    }

    return res;
}

int main(int argc, char** argv) {
    auto file = get_lines("2024/day_4/day4example");

    int res = 0;
    for (size_t i = 1; i < file.size()-1; i++) {
        std::string line = file[i];
        for (size_t j = 1; j < line.size()-1; j++) {
            char c = line[j];
            if (c == 'A') {
                res += check_matches(file, i, j);
            }
        }
    }
    std::cout << res << std::endl;
    return 0;
}
