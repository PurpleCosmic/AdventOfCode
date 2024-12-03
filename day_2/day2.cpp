#include <bits/stdc++.h>
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>

bool is_safe(int n0, int n1, bool ascending) {    
    int dist = abs(n0-n1);
    return !((dist < 1 || dist > 3) || (ascending && (n0 > n1) || (!ascending && (n0 < n1))));
}

bool is_report_safe(std::vector<int> report) {
    bool safe = true;
    bool bad_level_saved = false;

    bool ascending = report[0] < report[1];
    for (int i = 0; i < report.size()-1; i++) {
        int n0 = report[i];
        int n1 = report[i+1];
        int n2;
        if (i < report.size()-2) {
            n2 = report[i+2];
        } else {
            n2 = report[i+1];
        }

        if ( !is_safe(n0, n1, ascending) ) {
            safe = false;
        }
    }
    return safe;
}

int main(int argc, char** argv) {
    std::vector<std::vector<int>> reports;

    std::string line;
    std::string strnum;
    std::fstream file("day_2/day2input");
    while (getline (file, line)) {
        std::stringstream ss(line);
        std::vector<int> report;
        while (getline(ss, strnum, ' ')) {
            if (!strnum.empty()) {
                int num = std::stoi(strnum);
                report.push_back(num);
            }
        }
        reports.push_back(report);
    }

    int res = 0;
    for ( auto report : reports ) {
        if (is_report_safe(report)) {
            res++;
        } else {
            bool can_be_safe = false;
            for (int i = 0; i < report.size(); i++) {
                std::vector<int> report_less = report;
                report_less.erase(report_less.begin()+i);
                if (is_report_safe(report_less)) {
                    can_be_safe = true;
                }
            }

            if (can_be_safe) {
                res++;
            }
        }
    }

    std::cout << res << std::endl;

    return 0;
}