#ifndef _DIRECTORY_TREE_H
#define _DIRECTORY_TREE_H

#include <vector>
#include <unordered_map>
#include <filesystem>

namespace fs = std::filesystem;

namespace wbackup {

class Directory_tree {
protected:
    // default tree size
    static constexpr size_t default_tree_size = static_cast<size_t>(1024);

    // Node [1] is root (chroot to destination or source)
    // Node [0] is unused

    // node count (max node index)
    size_t node_cnt;

    // stores children pointers
    // map or unordered_map, that is a question
    std::vector<std::unordered_map<std::string, size_t> > children;

    // create new node in the tree
    virtual size_t new_node() = 0;

public:
    Directory_tree();
    virtual ~Directory_tree() = default;

    virtual void clear() = 0;
};

} // namespace wbackup

#endif