#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <tuple>
#include <cassert>
#include <map>

#include "vector_adds.h"
#include "string_adds.h"

using namespace std;

typedef struct point {
    int x;
    int y;
    friend ostream & operator<<(ostream & out, const point &p) {
        out << "x: " << p.x << " y: " << p.y;
        return out;
    }
    bool operator<(const point& p) const {
        return (y < p.y || (y == p.y && x < p.x));

    }
} point_t;


template <typename T>
ostream& operator<<(ostream& out, const tuple<T, T> & tup) {
    out <<"(" << get<0>(tup) << ", " << get<1>(tup) << ")";
    return out;
}




int main() {
    fstream input("input.txt");
    stringstream datass;
    datass << input.rdbuf();
    string data =  datass.str() ;
    vector<string> data_v = split(data, "\n");
    data_v.pop_back();
    vector<string> tmp;
    vector<int> temp;
    vector<string> tmp2;
    vector<tuple<point_t, point_t>> values;
    for (auto line: data_v) {
        tmp = split(line, " -> ");
        tuple<point_t, point_t> extremes;
        point_t p1;
        point_t p2;

        tmp2 = split(tmp[0], ",");
        p1 = {stoi(tmp2[0]), stoi(tmp2[1])};

        tmp2 = split(tmp[1], ",");
        p2 = {stoi(tmp2[0]), stoi(tmp2[1])};
        extremes = make_tuple(p1, p2);
        values.push_back(extremes);
    }
    map<point_t, int> dico;
    int min;
    int max;
    point_t p0;
    point_t p1;
    point_t res;
    for(auto tuples : values) {
        p0 = get<0>(tuples);
        p1 = get<1>(tuples);
        if (p0.x == p1.x && p0.y != p1.y) {
            min = p0.y < p1.y ? p0.y : p1.y;
            max = p0.y > p1.y ? p0.y : p1.y;
            for(int i = min; i <= max; i++) {
                res = {p0.x, i};
                if (dico.find(res) == dico.end()) {
                    dico[res] =  1;
                } else {
                    dico[res]++;
                }
            }
        } else if (p0.y == p1.y && p0.x != p1.x) {
            min = p0.x < p1.x ? p0.x : p1.x;
            max = p0.x > p1.x ? p0.x : p1.x;
            for(int i = min; i <= max; i++) {
                res = {i, p0.y};
                if (dico.find(res) == dico.end()) {
                    dico[res] =  1;
                } else {
                    dico[res]++;
                }
            }

        }
    }

    int cpt = 0;
    for(auto it = dico.begin(); it != dico.end(); it++) {
        if (it->second >= 2) {
            cpt++;
        }
    }
    cout << "part 1: " << cpt << endl;

    // //part2
    for(auto tuples : values) {
        p0 = get<0>(tuples);
        p1 = get<1>(tuples);
        if (abs(p0.x-p1.x) && (p0.y-p1.y)) {
            if (p0.y > p1.y) {
                swap(p0, p1);
            }
            if (p0.x > p1.x) {
                int j = 0;
                for(int i = p0.x; i >= p1.x; i--) {
                    res = {i, p0.y+j};
                    if (dico.find(res) == dico.end()) {
                        dico[res] =  1;
                    } else {
                        dico[res]++;
                    }
                    j++;
                }
            } else {
                for(int i = 0; p0.x+i <= p1.x; i++) {
                    res = {p0.x+i, p0.y+i};
                    if (dico.find(res) == dico.end()) {
                        dico[res] =  1;
                    } else {
                        dico[res]++;
                    }
                }
            }
        }
    }

    cpt = 0;
    for(auto it = dico.begin(); it != dico.end(); it++) {
        if (it->second >= 2) {
            cpt++;
        }
    }
    cout << "part 2: " << cpt << endl;
}
