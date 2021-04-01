#include "directory_tree.h"

namespace wbackup {

Directory_tree::Directory_tree(size_t init_size=default_tree_size)
    : children(init_size), initial_tree_size(init_size), node_cnt(static_cast<size_t>(1)) { }

void Directory_tree::clear() {
    node_cnt = static_cast<size_t>(1u);
    
    children.clear();
    children.resize(initial_tree_size);
}

} // namespace wbackup
