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

#include "vector_adds.h"
#include "string_adds.h"
#include "map_adds.h"

using namespace std;

int sum_natural(int n) {
    return (n*(n+1)/2);
}

bool comp(int i, int j) {return (i<j);}

int calculate_fuel(vector<int> & v, int pos) {
    int fuel = 0;
    for(int num : v) {
        fuel+=sum_natural(abs(num-pos));
    }
    return fuel;
}
int calculate_fuel_part1(vector<int> & v, int pos) {
    int fuel = 0;
    for(int num : v) {
        fuel+=(abs(num-pos));
    }
    return fuel;
}
int main() {
    fstream input("input.txt");
    stringstream data_stream;
    data_stream << input.rdbuf();
    string data = data_stream.str();
    data.pop_back();
    vector<string> v_data = split(data, ",");
    vector<int> numbers;
    for (string str : v_data) {
        numbers.push_back(stoi(str));
    }
    // vector<int> temp;
    // int max = 0;
    // for(auto num: numbers) {
    //     if (num > max)
    //         max = num;
    // }
    // int min = calculate_fuel(numbers, 0);
    // int curr;
    // for(int i = 1; i <=max; i++) {
    //     curr = calculate_fuel_part1(numbers, i);
    //     if (min > curr)
    //         min = curr;
    // }
    // cout << min << endl;
    sort(numbers.begin(), numbers.end(),comp);
    int med  = numbers[numbers.size()/2];
    int fuel_sum = 0;
    for(int num: numbers) {
        fuel_sum += abs(num-med);
    }
    cout << fuel_sum << endl;
}
