#include <filesystem>
#include <iostream>
#include <fstream>
#include <map>
#include <iterator>

#include "headers/json.hpp"
// #include "config.h"
namespace fs = std::filesystem;

class TestForeachContainer {
private:
    int *a;
    size_t size;

public:
    TestForeachContainer(size_t s) { a = new int[s]; size = s; }
    ~TestForeachContainer() { delete[] a; }
    void set(size_t pos, int val) { a[pos] = val; }
    int at(size_t pos) const { return a[pos]; }
    
    int *begin() { return a; }
    int *end() { return a+size; }
};

int main() {
    TestForeachContainer c(5);
    for (int i=0 ; i<5 ; i++) c.set(i, 91+i);
    for (auto &i: c) {
        std::cout << i << std::endl;
    }
    return 0;
}

int main7() {
    std::vector<bool> vb({true, true, true});
    return 0;
}

int main6() {
    fs::path p("/Users/whsu");
    fs::path pr("We/sdd");
    fs::relative(pr, p);
    std::cout << pr.string() << std::endl;
    return 0;
}

int main5() {
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
    return 0;
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