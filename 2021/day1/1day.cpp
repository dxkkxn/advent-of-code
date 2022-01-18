#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using std::cout;
using std::string;
using std::endl;
using std::vector;

using list_t = std::vector<int>;

std::ostream& operator<<(std::ostream & out, const list_t& v) {
    out << '[';
    int n = v.size();
    for(int i=0; i < n-1; i++) {
        out << v[i] << ',';
    }
    out << v[n-1] << ']' << endl;
    return out;
}

int main() {
    std::ifstream input("1input.txt");
    string tmp;
    // while(getline(input, tmp)) {
    //     cout << tmp;
    // }
    list_t list;

    while(input) {
        input >> tmp;
        if (!input.eof())
            list.push_back(std::stoi(tmp));
    }
    int inc_count = 0;
    int n = list.size();
    int prec = list[0];
    for(int i = 1; i < n; i++) {
        if(list[i] > prec) {
            inc_count++;
        }
        prec = list[i];
    }
    cout << list;
    cout << inc_count << endl;

    inc_count = 0;
    prec = list[0] + list[1] + list[2];
    int sum;
    for(int i = 1; i <= n-3; i++) {
        sum = list[i] + list[i+1] + list[i+2];
        if(sum > prec) {
            inc_count++;
        }
        prec = sum;
        cout << inc_count<< endl;
    }
    cout << inc_count;

    input.close();

    return 0;
}
