#include "directory_tree.h"

namespace wbackup {

Directory_tree::Directory_tree()
    : children(default_tree_size), node_cnt(static_cast<size_t>(1)) { }

} // namespace wbackup
