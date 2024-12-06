#include <bits/stdc++.h>
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include <unordered_map>

class coord {
    public:
        coord(int, int);
        int x;
        int y;
};
coord::coord(int x, int y): x(x), y(y) {};

class counter {
    public:
        int n;
        void increment();
};
void counter::increment() { n++; };

std::vector<std::string> get_lines(std::string filename) {
    std::vector<std::string> lines;

    std::string line;
    std::fstream file(filename);
    while (getline (file, line)) {
        lines.push_back(line);
    }
    return lines;
};

static std::vector<coord> visited;
void trace_path(std::vector<std::string> lines, coord pos, coord bounds, int direction, counter& c) {
    if (pos.x >= bounds.x || pos.y >= bounds.y || pos.x < 0 || pos.y < 0) { 
        std::cout << "oob!!! (" << pos.x << "," << pos.y << ")" << std::endl; 
        return; 
    }

    bool already_visited = false;
    for (auto point : visited) {
        if (point.x == pos.x && point.y == pos.y) {
            already_visited = true;
        }
    }
    if (! already_visited) {
        c.increment();
    }

    visited.push_back(pos);

    int next_x = pos.x;
    int next_y = pos.y;
    if (direction == 0) {
        next_y--;
    } else if (direction == 1) {
        next_x++;
    } else if (direction == 2) {
        next_y++;
    } else {
        next_x--;    
    }

    if (next_x < bounds.x && next_y < bounds.y && next_y >= 0 && next_x >= 0 && lines[next_y][next_x] == '#') {
        std::cout << "turn" << std::endl;
        direction = (direction + 1) % 4;
        trace_path(lines, pos, bounds, direction, c);
    } else {
        std::cout << "move" << std::endl;
        trace_path(lines, coord(next_x, next_y), bounds, direction, c);
    }
}

int main(int argc, char** argv) {
    auto file = get_lines("day_6/input");

    int res = 0;

    counter count = counter();
    for (int i = 0; i < file.size(); i++) {
        for (int j = 0; j < file[0].size(); j++) {
            int direction = -1;
            if (file[i][j] == '^') {
                direction = 0;
            }
            if (file[i][j] == '>') {
                direction = 1;
            }
            if (file[i][j] == 'v') {
                direction = 2;
            }
            if (file[i][j] == '<') {
                direction = 3;
            }

            if (direction > -1) {
                trace_path(file, coord(j, i), coord(file[0].size(), file.size()) , direction, count);
            }
        }
    }

    res = count.n;

    std::cout << res << std::endl;
    return 0;
}
