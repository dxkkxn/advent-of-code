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
#include <iterator>
#include <set>

#include "vector_adds.h"
#include "string_adds.h"
#include "map_adds.h"

using namespace std;

bool comp(string& s, string& t) {
    return (s.length()< t.length());
}

bool comp_char(char & c, char & c2) {
    return (c<c2);
}

void replace_string(string & str, map<char, char> dico) {
    for(size_t i = 0; i < str.length(); i++) {
        str[i] = dico[str[i]];
    }
}

template <typename T, typename X>
bool in(T v, X target) {
    return (find(begin(v), end(v), target) != end(v));
}

int main() {
    fstream input("input.txt");
    stringstream data_stream;
    data_stream << input.rdbuf();
    string data = data_stream.str();
    data.pop_back();
    vector<string> v_data = split(data, "\n");
    vector<string> temp;
    vector<int> valid_values{2, 4, 3, 7};
    int count = 0;
    for(string line: v_data) {
        temp = split(line, " | ");
        temp = split(temp[1], " ");
        for(string elm: temp) {
            auto res = find(begin(valid_values), end(valid_values), elm.length());
            if (res != end(valid_values))
                count++;
        }
    }
    cout << count << endl;
    // part 2
    map<char, char> dico;
    map<int, vector<string>> length_to_string;
    vector<string> tmp;
    vector<string> calcul = { "abcefg", "cf", "acdeg", "acdfg", "bcdf",
                             "abdfg", "abdefg", "acf", "abcdefg", "abcdfg"};
    map<char, int> occurrence;
    int sum ;
    int total= 0;

    for(string line: v_data) {
        temp = split(line, " | ");
        vector<string> to_calculate = split(temp[1], " ");
        temp = split(temp[0], " ");
        dico.clear();
        occurrence.clear();
        length_to_string.clear();
        for (string  str : temp) {
            tmp.clear();
            if (length_to_string.find(str.length()) == length_to_string.end()) {
                tmp.push_back(str);
                length_to_string[str.length()] = tmp;
            } else {
                length_to_string[str.length()].push_back(str);
            }
            for(char ch: str) {
                if (occurrence.find(ch)== end(occurrence)) {
                    occurrence[ch] = 1;
                } else {
                    occurrence[ch]++;
                }
            }
        }
        for(auto it = begin(occurrence); it != end(occurrence); it++) {
            if(it->second == 4) {
                // dico['e'] = it->first;
                dico[it->first] ='e';
            } else if (it->second == 6) {
                // dico['b'] = it->first;
                dico[it->first] = 'b';
            }
        }
        string seven_s = length_to_string[3][0];
        string one_s = length_to_string[2][0];
        string four_s = length_to_string[4][0];
        string eight_s = length_to_string[7][0];
        for (char ch : seven_s) {
            if (find(begin(one_s), end(one_s), ch) == end(one_s)) {
                dico[ch] = 'a';
                // dico['a'] = ch;
            }
        }
        int count_zero = 0;
        int count_one = 0;
        for (string str: temp) {
            if( (in(str,one_s[0]) && !in(str,one_s[1]))  ) {
                count_zero++;
            } else if( (in(str,one_s[1]) && !in(str,one_s[0]))  ) {
                count_one++;
            }
        }
        dico[one_s[0]] = count_zero == 1 ? 'c' : 'f';
        dico[one_s[1]] = count_one == 2 ? 'f' : 'c';
        bool in;
        for (char ch: four_s) {
            if (dico.find(ch) == dico.end()) {
                dico[ch] = 'd';
                break;
            }
        }
        for (char ch: eight_s) {
            if (dico.find(ch) == dico.end()) {
                dico[ch] = 'g';
                break;
            }
        }
        int res;
        sum = 0;
        for (string str: to_calculate) {
            replace_string(str, dico);
            sort(str.begin(), str.end(), comp_char);
            assert(find(calcul.begin(), calcul.end(), str) != end(calcul));
            res = find(calcul.begin(), calcul.end(), str)-calcul.begin();
            sum *= 10;
            sum+=res;
        }
        total += sum;
    }
    cout << total << endl;
}
