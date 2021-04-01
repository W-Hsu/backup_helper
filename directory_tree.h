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
    //
    // the size of default-constructed tree
    // see Constructor
    static constexpr size_t default_tree_size = static_cast<size_t>(1024);
    
    // initial tree size
    //
    // record initial size of the tree
    // if the tree is default-constructed, it is equal with default_tree_size
    // if there's a param given in the constructor, it is set by the param
    size_t const initial_tree_size;

    // node count (max node index)
    //
    // Node [1] is the root/chroot node
    // Node [0] is unused
    size_t node_cnt;

    // stores children pointers
    // TODO map or unordered_map, that is a question
    std::vector<std::unordered_map<std::string, size_t> > children;

    // create new node in the tree
    virtual size_t new_node() = 0;

public:
    Directory_tree(size_t default_size);
    virtual ~Directory_tree() = default;

    virtual void clear();
};

} // namespace wbackup

#endif