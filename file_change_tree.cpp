#include "file_change_tree.h"

#include <filesystem>

namespace fs = std::filesystem;

namespace wbackup {

File_change_tree::File_change_tree():
    Directory_tree() { }

size_t File_change_tree::new_node() {
    if (node_cnt+1==children.size()) {
        children.resize(2*children.max_size());
        vals.resize(children.max_size());
    }

    return ++node_cnt;
}

void File_change_tree::clear() {
    children.clear();
    vals.clear();
    children.resize(1024);
    vals.resize(1024);

    node_cnt = 1;
}

void File_change_tree::read_backup_chain(const fs::path &dst) {

}

void File_change_tree::make_tree(const fs::path &dst, const fs::path &src) {

}

} // namespace wbackup