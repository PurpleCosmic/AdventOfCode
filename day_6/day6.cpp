#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include <map>
#include <set>

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

void get_path_positions(std::vector<std::string> lines, std::pair<int, int> pos, std::pair<int, int> bounds, int direction, std::set<std::pair<int, int>> &visited) {
    if (pos.first >= bounds.first || pos.second >= bounds.second || pos.first < 0 || pos.second < 0) {
        return; 
    }

    visited.insert(pos);
    
    int next_x = pos.first;
    int next_y = pos.second;
    if (direction == 0) {
        next_y--;
    } else if (direction == 1) {
        next_x++;
    } else if (direction == 2) {
        next_y++;
    } else {
        next_x--;    
    }
    
    if (next_x < bounds.first && next_y < bounds.second && next_y >= 0 && next_x >= 0 && lines[next_y][next_x] == '#') {
        direction = (direction + 1) % 4;
        get_path_positions(lines, pos, bounds, direction, visited);
    } else {
        get_path_positions(lines, {next_x, next_y}, bounds, direction, visited);
    }
}

bool path_loops(const std::vector<std::string> &lines, const std::pair<int, int> pos, const std::pair<int, int> &bounds, int direction, const std::pair<int, int> &start_pos, const int start_direction, bool first_move, std::map<std::pair<int, int>, std::vector<int>> &visited) {
    if (pos.first >= bounds.first || pos.second >= bounds.second || pos.first < 0 || pos.second < 0) {
        return false; 
    }
    if (pos.first == start_pos.first && pos.second == start_pos.second && direction == start_direction && ! first_move) {
        return true;
    }

    for (auto dir : visited[pos]) {
        if (dir == direction) {
            return true;
        }
    }
    visited[pos].push_back(direction);
    
    int next_x = pos.first;
    int next_y = pos.second;
    if (direction == 0) {
        next_y--;
    } else if (direction == 1) {
        next_x++;
    } else if (direction == 2) {
        next_y++;
    } else {
        next_x--;    
    }
    
    if (next_x < bounds.first && next_y < bounds.second && next_y >= 0 && next_x >= 0 && lines[next_y][next_x] == '#') {
        direction = (direction + 1) % 4;
        return path_loops(lines, pos, bounds, direction, start_pos, start_direction, false, visited);
    } else {
        return path_loops(lines, {next_x, next_y}, bounds, direction, start_pos, start_direction, false, visited);
    }
}

int test_all_spots(std::vector<std::string> &lines, const std::pair<int, int> pos, const std::pair<int, int> &bounds, const int direction) {
    int res = 0;
    std::set<std::pair<int, int>> positions;
    get_path_positions(lines, pos, bounds, direction, positions);
    std::cout << positions.size() << std::endl;
    int k = 0;
    for (int i = 0; i < lines.size(); i++) {
        for (int j = 0; j < lines[i].size(); j++) {
            char orig = lines[i][j];
            lines[i][j] = '#';
            std::map<std::pair<int, int>, std::vector<int>> visited;
            bool a = path_loops(lines, pos, bounds, direction, pos, direction, true, visited);
            lines[i][j] = orig;
            if (a) {
                res++;
            }
            k++;
            std::cout << k << "/" << (lines.size() * lines[i].size()) << std::endl;
        }
    }
    return res;
}

int main(int argc, char** argv) {
    auto file = get_lines("day_6/input");

    int res = 0;

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
                res = test_all_spots(file, {j, i}, {file[0].size(), file.size()}, direction);
            }
        }
    }

    std::cout << "res: " << res << std::endl;
    return 0;
}
