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

map<string, bool> vertex_check;

bool string_is_upper_case(string  str) {
    for(char c: str) {
        if (!isupper(c))
            return false;
    }
    return true;
}

map<string, vector<string>> graph;

vector<string> run;
int cpt;
void all_path(string curr_vertex, vector<string> run) {
    if(curr_vertex == "end") {
        cpt++;
        return;
    }
    for(string neighbor : graph[curr_vertex]) {
        if (vertex_check[neighbor] == false) {
            run.push_back(neighbor);
            if(!string_is_upper_case(neighbor))
                vertex_check[neighbor] = true;
            all_path(neighbor, run);
            run.pop_back();
            vertex_check[neighbor] = false;
        }
    }
    return;
}

void start() {
    cpt = 0;
    vertex_check["start"] = true;
    run.push_back("start");
    all_path("start", run);
}


map<string, char> vertex_visits;
bool tcav; // twice_cave_already_visited;
void all_path2(string curr_vertex, vector<string> run) {
    if(curr_vertex == "end") {
        cpt++;
        return;
    }
    for(string neighbor : graph[curr_vertex]) {
        if (vertex_check[neighbor] == false ) {
            run.push_back(neighbor);
            if(!string_is_upper_case(neighbor))
                vertex_check[neighbor] = true;
            all_path2(neighbor, run);
            run.pop_back();
            vertex_check[neighbor] = false;
        } else if ((vertex_check[neighbor] == true and !tcav
                    and neighbor != "start" and neighbor != "end")) {
            tcav = true;
            run.push_back(neighbor);
            if(!string_is_upper_case(neighbor))
                vertex_check[neighbor] = true;
            all_path2(neighbor, run);
            tcav = false;
            run.pop_back();
        }
    }
    return;
}

void start2() {
    cpt = 0;
    tcav = false;
    vertex_check["start"] = true;
    run.push_back("start");
    all_path2("start", run);
}



int main() {
    fstream input("input.txt");
    string buffer;
    vector<vector<int>> grid;
    vector<int> tmp;
    vector<string> tmp2;
    while (getline(input, buffer)) {
        vector<string> temp =  split(buffer, "-");
        if (graph.find(temp[0]) == graph.end()) {
            tmp2.clear();
            tmp2.push_back(temp[1]);
            graph[temp[0]] = tmp2;
        } else {
            graph[temp[0]].push_back(temp[1]);
        }
        if (graph.find(temp[1]) == graph.end()) {
            tmp2.clear();
            tmp2.push_back(temp[0]);
            graph[temp[1]] = tmp2;
        } else {
            graph[temp[1]].push_back(temp[0]);
        }
    }
    for (auto it= graph.begin(); it!= graph.end(); it++) {
        vertex_check[it->first] = false;
    }
    for (auto it= graph.begin(); it!= graph.end(); it++) {
        vertex_visits[it->first] = 0;
    }
    start();
    cout << graph << endl;
    cout << vertex_check << endl;
    cout << cpt<< endl;
    start2();
    cout << cpt<< endl;
}
