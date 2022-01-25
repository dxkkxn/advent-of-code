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
#include <stdio.h>

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

int main() {
    fstream input("input.txt");
    stringstream buffer_stream;
    int max_x = 0;
    int max_y = 0;
    int x;
    int y;
    buffer_stream << input.rdbuf();
    string buf = buffer_stream.str();
    vector<string> buffer = split(buf, "\n\n");
    vector<string> line_point = split(buffer[0], "\n");
    map<point_t, bool> points;

    for(string line: line_point) {
        vector<string> tmp = split(line, ",");
        x = stoi(tmp[0]);
        y = stoi(tmp[1]);
        points[point_t(x, y)] = true;
        if (x > max_x)
            max_x = x;
        if (y > max_y)
            max_y = y;
    }
    vector<string> tmp = split(buffer[1], "\n");
    tmp.pop_back();
    vector<tuple<char, int>> fold;
    for(string line : tmp) {
        buffer = split(line, " ");
        vector<string> tmp = split(buffer.back(), "=");
        fold.push_back(make_tuple(tmp[0][0], stoi(tmp[1])));
    }
    char c;
    map<point_t, bool> next_points;
    cout << max_x << " "<< max_y << endl;
    for(auto tup: fold) {
        c = get<0>(tup);
        x = get<1>(tup);
        if (c == 'y') {
            for(int i_y = x+1, i_yr = x-1; i_y <= max_y; i_y++, i_yr--) {
                for (int i_x = 0; i_x <= max_x; i_x++) {
                    if(points.find(point_t(i_x, i_y)) != points.end()
                       || points.find(point_t(i_x, i_yr)) != points.end()) {
                        next_points[point_t(i_x, i_yr)] = true;
                    }
                }
            }
        } else if (c=='x') {
            for(int i_x = x+1, i_xr = x-1; i_x <= max_x; i_x++, i_xr--) {
                for (int i_y = 0; i_y <= max_y; i_y++) {
                    if(points.find(point_t(i_x, i_y)) != points.end()
                       || points.find(point_t(i_xr, i_y)) != points.end()) {
                        next_points[point_t(i_xr, i_y)] = true;
                    }
                }
            }
        }

        points = next_points;
        next_points.clear();
        cout << points.size() << endl;
    }

    // part2
    // draw
    max_y = 0;
    max_x = 0;
    for(auto it = points.begin(); it != points.end(); it++) {
        if (max_y < it->first.y)
            max_y =  it->first.y;
        if (max_x < it->first.x)
            max_x = it->first.x;
        }
    vector<vector<char>> v(max_y+1, vector<char>(max_x+1));
    for(auto it = points.begin(); it != points.end(); it++) {
        v[it->first.y][it->first.x] = '#';
    }
    for (auto v2 :v) {
        for (int i = 0; i <v2.size(); i++) {
            if (v2[i] =='#') {
                cout << '#';
            } else {
                cout << " ";
            }
        }
        cout << endl;
    }
}
