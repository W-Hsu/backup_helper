#ifndef _FILETREE_H
#define _FILETREE_H

#include <vector>
#include <filesystem>
#include <unordered_map>
#include "misc.h"

namespace fs = std::filesystem;

namespace wbackup {

template <class T>
class File_tree {
private:
    // Node [1] is root (chroot to destination or source)
    // Node [0] is unused

    // node count (max node index)
    size_t node_cnt;

    // stores children pointers
    std::vector<std::unordered_map<std::string, size_t> > children;

    // stores values
    std::vector<T> vals;

public:
    File_tree();

    size_t new_node();

    int set(char const *, const T &);
    int set(const std::string &, const T &);
    int set(const fs::path &, const T &);

    T get(char const *);
    T get(const std::string &);
    T get(const fs::path &);

    void clear();
};

} // namespace wbackup

#endif