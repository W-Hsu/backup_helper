#include "file_change_tree.h"

#include <filesystem>
#include <vector>
#include <iterator>
#include <algorithm>
#include <fstream>

namespace fs = std::filesystem;

namespace wbackup {

File_change_tree::File_change_tree():
    Directory_tree(), vals(default_tree_size) { }

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
    std::vector<fs::path> backup_directory_list;
    std::copy(fs::directory_iterator(dst), fs::directory_iterator(), std::back_inserter(backup_directory_list));
    std::sort(backup_directory_list.begin(), backup_directory_list.end());

    for (auto &i: backup_directory_list) {
        if (fs::is_directory(i/"full")) {
            this->clear();
            for (const auto &j: fs::recursive_directory_iterator(i/"full")) {
                this->add_path(fs::relative(i/"full", fs::canonical(j)));
            }
            continue;
        }

        else if (fs::is_directory(i/"incremental")) {
            std::fstream fin(i/"incremental/deleted.info");
            if (fin.good()) {
                std::string s;
                std::getline(fin, s);
                this->delete_path(fs::path(s));
            }

            for (const auto &j: fs::recursive_directory_iterator(i/"incremental")) {
                this->add_path(fs::relative(i/"incremental", fs::canonical(j)));
            }
        }
    }
}

void File_change_tree::make_tree(const fs::path &dst, const fs::path &src) {
    this->read_backup_chain(dst);
    this->get_difference(src);
    
    std::vector<fs::path> result;
    this->traverse(result);
}

} // namespace wbackup