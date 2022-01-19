#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cmath>
#include <cassert>

#include "vector_additions.h"
#include "bits.h"

int most_common(std::vector<std::string> v, int index) {
    int ones = 0;
    int zeros = 0;
    for(std::size_t i = 0; i < v.size(); i++) {
        if (v[i][index] == '1') {
            ones++;
        } else {
            zeros++;
        }
    }
    if (ones > zeros) {
        return 1;
    } else if (zeros > ones) {
        return 0;
    } else {
        return -1;
    }

}

int least_common(std::vector<std::string> v, int index) {
    int ones = 0;
    int zeros = 0;
    for(std::size_t i = 0; i < v.size(); i++) {
        if (v[i][index] == '1') {
            ones++;
        } else {
            zeros++;
        }
    }
    if (ones < zeros) {
        return 1;
    } else if (zeros < ones) {
        return 0;
    } else {
        return -1;
    }

}

int main() {
    std::fstream input("input.txt");
    std::string buf;
    getline(input, buf);
    std::size_t n = buf.length();
    std::vector<int> ones(n, 0);
    std::vector<int> zeros(n, 0);


    input.seekg(0);
    while (getline(input, buf)) {
        for (std::string::size_type i = 0; i < buf.length(); i++) {
            if (buf[i] == '0') {
                zeros[i]++;
            } else {
                ones[i]++;
            }
        }
    }
    std::vector<int> gamma(n, 0);
    std::vector<int> epsilon(n, 0);
    for (std::size_t i = 0; i < n; i++) {
        if (ones[i] > zeros[i]) {
            gamma[i] = 1;
            epsilon[i] = 0;
        } else {
            gamma[i] = 0;
            epsilon[i] = 1;
        }
    }
    std::cout << "gamma : " << vector_bin_to_int(gamma) << std::endl;
    std::cout << "epsion: " << vector_bin_to_int(epsilon) << std::endl;
    std::cout << vector_bin_to_int(gamma) * vector_bin_to_int(epsilon) <<std::endl;

    // part 2
    input.clear();
    input.seekg(0);

    std::vector<std::string> oxygen;
    std::vector<std::string> co2;

    assert(ones[0]!=zeros[0]);
    char keep = ones[0] > zeros[0] ? '1' : '0';
    while (getline(input, buf)) {
        if (buf[0]==keep) {
            oxygen.push_back(buf);
        } else {
            co2.push_back(buf);
        }
    }

    std::vector<std::string> tmp;
    for (std::size_t i = 1; i < n; i++) {
        assert(oxygen.size()>0);
        if (most_common(oxygen, i) == 1 || most_common(oxygen,i) == -1) {
            for (std::size_t j = 0; j < oxygen.size(); j++) {
                if (oxygen[j][i] == '1') {
                    tmp.push_back(oxygen[j]);
                }
            }
        } else {
            for (std::size_t j = 0; j < oxygen.size(); j++) {
                if (oxygen[j][i] == '0') {
                    tmp.push_back(oxygen[j]);
                }
            }
        }
        oxygen.clear();
        oxygen = tmp;
        tmp.clear();
    }

    for (std::size_t i = 1; i < n && co2.size() > 1; i++) {
        if (least_common(co2, i) == 0 || least_common(co2,i) == -1) {
            for (std::size_t j = 0; j < co2.size(); j++) {
                if (co2[j][i] == '0') {
                    tmp.push_back(co2[j]);
                }
            }
        } else {
            for (std::size_t j = 0; j < co2.size(); j++) {
                if (co2[j][i] == '1') {
                    tmp.push_back(co2[j]);
                }
            }
        }
        co2.clear();
        co2= tmp;
        tmp.clear();
    }
    assert(oxygen.size() == 1);
    assert(co2.size() == 1);
    std::cout << std::endl;

    std::cout << "oxygen : " << oxygen[0]<<std::endl;
    std::cout << "co2 : " <<  co2[0]<<std::endl;
    std::cout << str_bin_to_int(oxygen[0]) * str_bin_to_int(co2[0]) << std::endl;

    return 0;
}
