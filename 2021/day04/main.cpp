#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <tuple>
#include <cassert>

#include "vector_adds.h"
#include "string_adds.h"

using namespace std;

vector<vector<vector <int>>> boards;
vector<vector<vector <bool>>> boards_sol;
int N = 5;
int winner_board;

tuple<bool, vector<vector <int>>> check_winner() {
    int k = 0;
    for(auto board: boards_sol) {
        for (int i = 0; i < N; i++) {
            bool is_row = true;
            bool is_col = true;
            for (int j = 0; j < N && (is_row || is_col) ; j++) {
                if (board[i][j] == false)
                    is_row = false;
                if (board[j][i] == false)
                    is_col = false;
            }
            if (is_row || is_col) {
                winner_board = k;
                return make_tuple(true, boards[k]);
            }
        }
        k++;
    }
    return make_tuple(false,  vector<vector <int>>());
}

void cross (int x) {
    int i = 0, j = 0, k = 0;
    for(auto board: boards) {
        j = 0;
        for (auto row : board) {
            k = 0;
            for (auto num : row) {
                if (num == x) {
                    boards_sol[i][j][k] = true;
                }
                k++;
            }
            j++;
        }
        i++;
    }
    return;
}

int main() {
    fstream input("input.txt");
    string buffer;
    stringstream data;
    data << input.rdbuf();
    buffer = data.str();
    vector<string> tmp = split(buffer, "\n\n");

    vector<int> numbers;
    vector<string> numbers_str = split(tmp[0], ",");
    for (auto num: numbers_str) {
        numbers.push_back(stoi(num));
    }

    // eof remove
    tmp.back().pop_back();

    for (size_t i = 1; i < tmp.size(); i++) {
        vector<string> v = split(tmp[i], "\n");
        vector<vector <int>> board;
        vector<vector <bool>> board_sol;
        for (auto i : v) {
            vector<string> temp_str = split(i, " ");
            vector<bool> temp_bool(N, false);
            vector<int> temp;
            for (auto i : temp_str) {
                if (i != "") {
                    temp.push_back(stoi(i));
                }
            }
            board.push_back(temp);
            board_sol.push_back(temp_bool);

        }
        boards.push_back(board);
        boards_sol.push_back(board_sol);
    }
    bool res;

    vector<vector<int>> board;
    int just_called_num;

    int num;
    std::vector<int>:: iterator last_it;
    for (auto it = begin(numbers); it != end(numbers); it++) {
        num =  *it;
        cross(num);
        tie(res, board) = check_winner();
        if (res) {
            last_it = it++;
            just_called_num = num;
            break;
        }
    }
    int i = 0, j;
    int sum = 0;
    cout << boards[winner_board];
    cout << boards_sol[winner_board];
    for (auto row: board) {
        j = 0;
        for(int num: row) {
            if (boards_sol[winner_board][i][j] == false)
                sum += num;
            j++;
        }
        i++;
    }
    cout << sum << endl;
    cout << just_called_num << endl;
    cout << sum * just_called_num << endl;

    //part2
    boards.erase(boards.begin()+winner_board);
    boards_sol.erase(boards_sol.begin()+winner_board);
    bool found = false;
    for (auto it = last_it; it != end(numbers) && !found; it++) {
        num = *it;
        cross(num);
        do {
            tie(res, board) = check_winner();
            if (res) {
                if (boards.size() == 1) {
                    just_called_num = num;
                    found = true;
                } else {
                    boards.erase(boards.begin()+winner_board);
                    boards_sol.erase(boards_sol.begin()+winner_board);
                }
            }
        } while (res == true && !found);

    }
    i = 0;
    sum = 0;
    assert(boards.size() == 1);
    cout << "size :" << boards.size() << endl;
    for (auto row: boards[0]) {
        j = 0;
        for(int num: row) {
            if (boards_sol[0][i][j] == false)
                sum += num;
            j++;
        }
        i++;
    }
    cout << endl;
    cout << sum << endl;
    cout << just_called_num << endl;
    cout << sum * just_called_num << endl;

    return 0;
}
