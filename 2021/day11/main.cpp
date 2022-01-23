#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <tuple>
#include <cassert>
#include <map>
#include <cmath>
#include <algorithm>
#include <array>

#include "vector_adds.h"
#include "string_adds.h"
#include "map_adds.h"

using namespace std;

typedef struct point_t {
    int x;
    int y;
    point_t(int x_, int y_) {
        x = x_;
        y = y_;
    }
    point_t() {
        x = 0;
        y = 0;
    }
    bool operator<(const point_t & p) const {
        return (y<p.y || (y == p.y && x<p.x));
    }
    bool operator==(const point_t &p) const {
        return (x==p.x && y==p.y);
    }

} point_t;

ostream& operator<<(ostream & out, point_t point) {
    out << "{"<<point.x<<", "<< point.y << "}";
    return out;
}
bool in(vector<point_t> & checked, point_t p) {
    for(auto it = checked.begin(); it != checked.end(); it++) {
        if(*it == p)
            return true;
    }
    return false;
}

int main() {
    fstream input("input.txt");
    string buffer;
    vector<vector<int>> grid;
    vector<int> tmp;
    while (getline(input, buffer)) {
        tmp.clear();
        for(char ch: buffer) {
            tmp.push_back(int(ch)-'0');
        }
        grid.push_back(tmp);
    }
    size_t n_line = grid[0].size();
    size_t size = grid.size();
    array<int, 8> move_x {0,1, 0,-1, 1,-1, 1, -1};
    array<int, 8> move_y {1,0,-1, 0,-1,1, 1, -1};
    int flashes = 0;
    bool check = true;
    int i_i;
    int i_j;
    int step = 0;
    vector<point_t> checked;
    vector<vector<int>> initial_grid = grid;
    while (step < 100) {
        check = false;
        checked.clear();
        for(size_t i = 0; i<size; i++) {
            for(size_t j = 0; j<n_line; j++) {
                grid[i][j]++;
                if (grid[i][j] > 9)
                    check = true;
            }
        }
        while (check) {
            check = false;
            for(size_t i = 0; i<size; i++) {
                for(size_t j = 0; j<n_line; j++) {
                    if (grid[i][j] > 9) {
                        grid[i][j] = 0;
                        checked.push_back(point_t(i, j));
                        flashes++;
                        for(size_t k = 0; k < 8; k++) {
                            i_i = i+move_x[k];
                            i_j = j+move_y[k];
                            if(i_i>=0 and i_i <size and i_j>=0 and i_j<n_line) {
                                if(!in(checked,point_t(i_i, i_j))) {
                                    grid[i_i][i_j]++;
                                    if(grid[i_i][i_j] > 9) {
                                        check = true;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        step++;
    }
    cout << flashes << endl;

    // part 2
    int flashing_simultaneously = 0;
    int all_octopuses = size*n_line;
    while (flashing_simultaneously != all_octopuses) {
        flashing_simultaneously = 0;
        check = false;
        checked.clear();
        for(size_t i = 0; i<size; i++) {
            for(size_t j = 0; j<n_line; j++) {
                grid[i][j]++;
                if (grid[i][j] > 9)
                    check = true;
            }
        }
        while (check) {
            check = false;
            for(size_t i = 0; i<size; i++) {
                for(size_t j = 0; j<n_line; j++) {
                    if (grid[i][j] > 9) {
                        grid[i][j] = 0;
                        checked.push_back(point_t(i, j));
                        flashing_simultaneously++;
                        for(size_t k = 0; k < 8; k++) {
                            i_i = i+move_x[k];
                            i_j = j+move_y[k];
                            if(i_i>=0 and i_i <size and i_j>=0 and i_j<n_line) {
                                if(!in(checked,point_t(i_i, i_j))) {
                                    grid[i_i][i_j]++;
                                    if(grid[i_i][i_j] > 9) {
                                        check = true;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        step++;
    }
    cout << step << endl;
}
