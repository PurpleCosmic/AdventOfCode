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

    int res = 0;
    for (int i : columns[0]) {
        int occ = 0;
        for (int e : columns[1]) {
            if (e == i) {
                occ++;
            }
        }
        res += i*occ;
    }
    std::cout << std::endl << res << std::endl;

    return 0;
}