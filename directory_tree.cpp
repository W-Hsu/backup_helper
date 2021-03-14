#include "directory_tree.h"

namespace wbackup {

Directory_tree::Directory_tree(size_t default_size=default_tree_size)
    : children(default_size), node_cnt(static_cast<size_t>(1)) { }

} // namespace wbackup
