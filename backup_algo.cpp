#include <filesystem>

namespace fs = std::filesystem;

int backup(fs::path &path) {
    fs::directory_entry de(path);
    fs::path p;
}