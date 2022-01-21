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
#include "map_adds.h"

using namespace std;
int main() {
    fstream input("input.txt");
    stringstream data_stream;
    data_stream << input.rdbuf();
    string data = data_stream.str();
    data.pop_back();
    vector<string> v_data = split(data, ",");
    vector<int> nums;
    for(string str: v_data) {
        nums.push_back(stoi(str));
    }
    // size_t size;
    // int j;
    // for(int i = 0; i < 80; i++) {
    //     size = nums.size();
    //     for(j = 0; j < size; j++) {
    //         if (nums[j] == 0)
    //             nums.push_back(8);
    //     }
    //     for(j = 0; j < size; j++) {
    //         if (nums[j] == 0)  {
    //             nums[j] = 6;
    //         } else {
    //             nums[j]--;
    //         }
    //     }
    //     cout << i << endl;
    // }
    // cout << nums.size() << endl;
    //part 2;
    map<unsigned long long int, unsigned long long int> dico ;
    for (int i = 0; i <= 8; i++) {
        dico[i] = 0;
    }
    for(auto num: nums) {
        dico[num]++;
    }
    int j;
    unsigned long long int sum;
    map<unsigned long long int, unsigned long long int> temp_dico = dico;
    for(int i = 0; i < 256; i++) {
        for(j = 1; j <= 8; j++) {
            temp_dico[j-1] = dico[j];
        }
        temp_dico[8] = dico[0];
        temp_dico[6] += dico[0];
        dico = temp_dico;
    }
    sum = 0;
    for(auto it=dico.begin(); it!=dico.end(); it++) {
        sum+= it->second;
    }
    cout << sum << endl;
    // 1214653763
}
