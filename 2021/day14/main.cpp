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

int main() {
    fstream input("input.txt");
    string polymer_template ;
    input >> polymer_template;
    string line;
    vector<string> vline;
    map<string, string> pair_insertion;
    getline(input, line);
    getline(input, line);
    while (getline(input, line)) {
        vline = split(line, " -> ");
        // cout << line << endl;
        // cout << vline[0] << "-" << vline[1]<< endl;
        pair_insertion[vline[0]] = vline[1];
    }
    // cout << pair_insertion << endl;
    // int n = polymer_template.length();
    // string first ;
    // string second;
    // for (int j = 0; j < 10; j++) {
    //     for(int i =1; i < n; i++) {
    //         first.clear();
    //         second.clear();
    //         first = polymer_template[i-1];
    //         second = polymer_template[i];
    //         if (pair_insertion.find(first+second) != pair_insertion.end()) {
    //             polymer_template.insert(i, pair_insertion[first+second]);
    //             i++; n++;
    //         }
    //     }
    //     // cout << j << endl;
    // }
    // map <char, int64_t> occur;
    // for (char ltr: polymer_template) {
    //     if (occur.find(ltr) == occur.end())
    //         occur[ltr] = 0;
    //     occur[ltr]++;
    // }
    // int64_t most_common =  occur.begin()->second;
    // int64_t lest_common = occur.begin()->second;
    // for(auto it = occur.begin(); it != occur.end(); it++) {
    //     if (it->second > most_common)
    //         most_common = it->second;
    //     if (it->second < lest_common)
    //         lest_common = it->second;
    // }
    // cout << most_common << endl;
    // cout << lest_common << endl;
    // cout << most_common - lest_common<< endl;
    // part 2
    map <char, int64_t> occur;
    map<string, int64_t> all_couples;
    map<string, int64_t> temp;
    string res;
    int i;
    for (i = 1; i < polymer_template.length(); i++) {
        res.clear();
        res += polymer_template[i-1];
        res += polymer_template[i];
        occur[polymer_template[i-1]]++;
        all_couples[res]++;
    }
    occur[polymer_template[i-1]]++;
    cout << occur << endl;
    cout << all_couples << endl;
    string pair;
    for(int j = 0; j < 40; j++) {
        temp.clear();
        for(auto it = all_couples.begin(); it != all_couples.end(); it++) {
            pair.clear();
            pair = it->first[0] + pair_insertion[it->first];
            temp[pair]+= it->second;
            pair.clear();
            pair =  pair_insertion[it->first] + it->first[1];
            temp[pair] += it->second;
            occur[pair_insertion[it->first][0]]+= it->second;
        }
        all_couples = temp;
        cout << j << endl;
    }

    int64_t most_common =  occur.begin()->second;
    int64_t lest_common = occur.begin()->second;
    for(auto it = occur.begin(); it != occur.end(); it++) {
        if (it->second > most_common)
            most_common = it->second;
        if (it->second < lest_common)
            lest_common = it->second;
    }
    cout << most_common << endl;
    cout << lest_common << endl;
    cout << most_common - lest_common<< endl;
}
