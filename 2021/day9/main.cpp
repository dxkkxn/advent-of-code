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
#include <set>

#include "vector_adds.h"
#include "string_adds.h"
#include "map_adds.h"

using namespace std;
typedef struct point_t {
    int i;
    int j;
    point_t(int line, int col) {
        i = line;
        j = col;
    }
    point_t() {
        i = 0;
        j = 0;
    }
    bool operator<(const point_t & p) const {
        return (i<p.i || (i == p.i && j<p.j));
    }
    bool operator==(const point_t &p) const {
        return (i==p.i && j==p.j);
    }

} point_t;
ostream& operator<<(ostream & out, point_t point) {
    out << "{"<<point.i<<", "<< point.j << "}";
    return out;
}
bool comp(int i, int j) {
    return (i < j);
}

int main() {
    fstream input("input.txt");
    stringstream data_stream;
    data_stream << input.rdbuf();
    string data = data_stream.str();
    data.pop_back();
    vector<string> v_data = split(data, "\n");
    vector<vector<int>> possible_positions {{0,1}, {1,0}, {-1, 0}, {0, -1}};
    size_t line;
    size_t col;
    size_t n_vector = v_data.size();
    size_t n_str = v_data[0].length();
    int lower_points;
    int times_entered;
    int risk = 0;
    vector<point_t> low_points;
    for(size_t i = 0; i < n_vector; i++) {
        for(size_t j = 0; j < n_str; j++) {
            lower_points = 0;
            times_entered = 0;
            for(auto pos: possible_positions) {
                line = i+pos[0];
                col = j+pos[1];
                if(line >= 0 and line < n_vector and col >=0 and col <n_str){
                    times_entered++;
                    if (v_data[line][col] > v_data[i][j])
                        lower_points++;
                }
            }
            if (lower_points == times_entered) {
                risk += int(v_data[i][j])-'0' +1;
                point_t tmp;
                tmp.i = i;
                tmp.j = j;
                low_points.push_back(tmp);
            }
        }
    }
    cout << risk << endl;
    //part 2
    int curr_size;
    int total_size = 1;;
    vector<int> sizes_of_bassins;
    int i;
    int j;
    vector<point_t> to_check;
    map<point_t, bool> checked;
    for (point_t point: low_points) {
        to_check.push_back(point);
        curr_size = 1;
        while(to_check.size() > 0) {
            i = to_check[0].i;
            j = to_check[0].j;
            for (auto pos: possible_positions) {
                line = i+pos[0];
                col = j+pos[1];
                if(line >= 0 and line < n_vector and col >=0 and col <n_str){
                    if (v_data[line][col] > v_data[i][j] and
                        v_data[line][col]!='9' and
                        checked[point_t(line, col)] == false and
                        find(to_check.begin(), to_check.end(), point_t(line, col)) == end(to_check)) {
                        to_check.emplace_back(point_t(line, col));
                        curr_size++;
                    }
                }
            }
            checked[to_check[0]] = true;
            to_check.erase(to_check.begin());
            // cout << point << " -> "<< to_check << endl;
        }
        to_check.clear();
        sizes_of_bassins.push_back(curr_size);
    }
    sort(rbegin(sizes_of_bassins), rend(sizes_of_bassins), comp);
    cout << sizes_of_bassins[0] * sizes_of_bassins[1] * sizes_of_bassins[2] << endl;
}
