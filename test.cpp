#include <filesystem>
#include <iostream>
#include <fstream>
#include <map>
#include "headers/json.hpp"
#include "config.h"
namespace fs = std::filesystem;

int main() {
    fs::path p("./Users/whsu/Programming");
    for (auto &i : p) {
        std::cout << i.c_str() << std::endl;
    }
    return 0;
}

int main4() {
    std::map<int, int*> m;
    std::cout << std::boolalpha << (m[2]==nullptr) << std::endl;
    return 0;
}

int main3() {
    fs::path p("/Users");
    fs::canonical(p);
    return 0;
}

class www2 {
public:
    int r;
    www2() { r=1; }
    int getr() { return r; }
    int getr_c() const { return r; }
};

int main2() {
    www2 xxx;
    const www2 &yyy = xxx;
    yyy.getr_c();
}

int main1() {
    std::string s;
    try {
        nlohmann::json j = "{\"abc\": \"def\""_json;

        nlohmann::from_json(j["abc"], s);
    } catch (std::exception &ex) {
        std::cerr << ex.what() << std::endl;
    }
    return 0;
}