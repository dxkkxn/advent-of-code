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
bool in(array<char, 4> arr, char ch) {
    for (char c: arr) {
        if(c==ch)
            return true;
    }
    return false;
}
bool comp(int64_t x, int64_t y) {return x<y;}
int main() {
    fstream input("input.txt");
    string buffer;
    vector<char> stack;
    array<char, 4> opener = {'[', '(', '<', '{'};
    array<char, 4> closer = {']', ')', '>', '}'};
    char tmp;
    int index;
    map<char, int> value { {')', 3},
                           {']', 57},
                           {'}', 1197},
                           {'>', 25137}
                         };
    int total = 0;
    vector<int64_t> scores;
    int64_t score = 0;
    size_t size;
    map<char, int> value2 {{'(', 1},
                           {'[', 2},
                           {'{', 3},
                           {'<', 4}
                         };
    bool corrupted;
    while(getline(input, buffer)) {
        stack.clear();
        corrupted = false;
        for(char ch: buffer) {
            if (in(opener, ch)) {
                stack.push_back(ch);
            } else {
                assert(in(closer, ch));
                auto it = find(begin(closer), end(closer), ch);
                index = it-closer.begin();
                tmp = stack.back();
                if (tmp != opener[index]) {
                    // corrupt
                    total += value[ch];
                    corrupted = true;
                    break;
                } else {
                    stack.pop_back();
                }
            }
        }
        if (not corrupted) {
            // part 2
            size = stack.size();
            score = 0;
            for(int i = (size-1); i>=0; i--) {
                score *= 5;
                score += value2[stack[i]];

            }
            scores.push_back(score);
        }
    }
    sort(scores.begin(), scores.end(), comp);
    cout << total << endl;
    cout<<scores[scores.size()/2] << endl;
}
