#include <filesystem>
#include <iostream>
#include <fstream>
#include "headers/json.hpp"
namespace fs = std::filesystem;

int main() {
    std::string s;
    try {
        nlohmann::json j = "{\"abc\": \"def\""_json;

        nlohmann::from_json(j["abc"], s);
    } catch (std::exception &ex) {
        std::cerr << ex.what() << std::endl;
    }
    return 0;
}