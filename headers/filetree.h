#ifndef _FILETREE_H
#define _FILETREE_H

#include <vector>
#include <filesystem>
#include "misc.h"

namespace fs = std::filesystem;

namespace wbackup {

template <class T>
class File_tree {
private:
    struct Node root;

public:
    int set(char const *, const T &);
    int set(const std::string &, const T &);
    int set(const fs::path &, const T &);

    T get(char const *);
    T get(const std::string &);
    T get(const fs::path &);

    void clear();
};

template <class T>
struct File_tree<T>::Node {
    std::map<std::string, Node*> children;
    T value;
};

} // namespace wbackup

#endif