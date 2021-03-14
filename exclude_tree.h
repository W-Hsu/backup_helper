#ifndef _EXCLUDE_TREE_H
#define _EXCLUDE_TREE_H

#include <vector>
#include <filesystem>
#include <unordered_map>

#include "directory_tree.h"
#include "misc.h"

namespace fs = std::filesystem;

namespace wbackup {

class Exclude_tree: public Directory_tree {
private:
    // stores values
    std::vector<bool> vals;

    size_t new_node() override;

public:
    Exclude_tree(size_t initial_size);
    ~Exclude_tree() override = default;
    void clear() override;

    void set(const fs::path &, bool);
    bool get(const fs::path &) const;
    void traverse(std::vector<std::string> &traverse_result) const;
};

} // namespace wbackup

#endif