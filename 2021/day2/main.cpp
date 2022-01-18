#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char *argv[]) {
    int depth = 0;
    int x = 0;
    std::string buffer;
    std::fstream input("input.txt");
    std::string mov;
    int val;
    size_t pos;
    while (input) {
        std::getline(input, buffer);
        if (input.good()) {
            pos = buffer.find(' ');
            mov = buffer.substr(0, pos);
            val = std::stoi(buffer.substr(pos+1));
            if (mov == "forward") {
                x+= val;
            } else if (mov == "down") {
                depth+=val;
            } else if (mov == "up") {
                depth-=val;
            }
        }
    }
    std::cout << x << " " << depth << std::endl;
    std::cout << x*depth << std::endl;

    // part 2

    input.clear();
    input.seekg(0);
    int aim = 0;
    depth = 0;
    x = 0;
    while(input) {
        std::getline(input, buffer);
        if (input.good()) {
            pos = buffer.find(' ');
            mov = buffer.substr(0, pos);
            val = std::stoi(buffer.substr(pos+1));
            if (mov == "forward") {
                x+= val;
                depth+= aim * val;
            } else if (mov == "down") {
                aim+=val;
            } else if (mov == "up") {
                aim-=val;
            }
        }
    }
    std::cout << depth * x << std::endl;
    input.close();
    return 0;
}
