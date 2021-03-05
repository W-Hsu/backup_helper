#ifndef _EXCLUDE_TREE_H
#define _EXCLUDE_TREE_H

#include <vector>
#include <filesystem>
#include <unordered_map>
#include "misc.h"

namespace fs = std::filesystem;

namespace wbackup {

class Exclude_tree {
private:
    // Node [1] is root (chroot to destination or source)
    // Node [0] is unused

    // node count (max node index)
    size_t node_cnt;

    // stores children pointers
    std::vector<std::unordered_map<std::string, size_t> > children;

    // stores values
    std::vector<bool> vals;

public:
    Exclude_tree();

    size_t new_node();

    void set(const fs::path &, bool);

    bool get(const fs::path &);

    void clear();
};

} // namespace wbackup

#endif