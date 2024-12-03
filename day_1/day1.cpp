#include <bits/stdc++.h>
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>

int main(int argc, char** argv) {
    std::vector<std::vector<int>> columns(2);

    std::string line;
    std::string strnum;
    std::fstream file("day1input");
    while (getline (file, line)) {
        std::stringstream ss(line);
        int col = 0;
        while (getline(ss, strnum, ' ')) {
            if (!strnum.empty()) {
                int num = std::stoi(strnum);
                columns[col].push_back(num);
                col++;
            }
        }
    }

    for (auto &col : columns) {
        std::cout << col[0] << std::endl;
        std::sort(col.begin(), col.end());
    }

    std::cout << std::endl;
    
    int res = 0;

    for (int i = 0; i < columns[0].size(); i++) {
        std::cout << columns[0][i] << "\t" << columns[1][i] << std::endl;
        res += abs(columns[0][i] - columns[1][i]);
    }
    std::cout << std::endl << res << std::endl;

    return 0;
}