#include "backup_chain_tree.h"
#include "misc.h"

#include <stack>
#include <string>
#include <fstream>

namespace wbackup {

Backup_chain_tree::Backup_chain_tree(size_t init_size=default_tree_size):
    Directory_tree(init_size), vals(init_size) { }

size_t Backup_chain_tree::new_node() {
    if (node_cnt+1==children.size()) {
        children.resize(2*children.max_size());
        vals.resize(children.max_size());
    }
    return ++node_cnt;
}

void Backup_chain_tree::clear() {
    Directory_tree::clear();
    vals.clear();
    vals.resize(initial_tree_size);
}

void Backup_chain_tree::update() {
    // clear the old tree, prepare to rebuild the tree
    this->clear();

    // get all the names of the backup time point
    std::vector<std::string> backup_time_point_list;
    configuration.get_backup_time_point_list(backup_time_point_list);

    // get destination path
    const fs::path &destination = configuration.get_destination_path();

    // find the last full backup, then build the backup chain tree from that point
    auto it = backup_time_point_list.begin();
    auto last_full_backup = backup_time_point_list.end();
    while (it!=backup_time_point_list.end()) {
        if (fs::exists(fs::path(destination/"..."/(*it)/"full")))
            last_full_backup = it;
        ++it;
    }

    // build the tree according to the last full backup first
    it = last_full_backup;
    for (const auto &i: fs::recursive_directory_iterator(destination/"..."/(*it)/"full")) {
        fs::path relative_i = fs::relative(destination, i);
        add_path(relative_i);
    }
    ++it;

    // scan the incremental backups orderly, to update the backup chain tree
    // iterate over the sublist (remaining incremental backup points) after the last full backup
    while (it!=backup_time_point_list.end()) {
        fs::path backup_point(destination/"..."/(*it));

        // step 1: read the deleted file/dirs from "deleted.info"
        // "deleted.info" is a regular file recording deletions to the files/dirs
        fs::path deleted_info = backup_point/"deleted.info";
        if (fs::exists(deleted_info) && fs::is_regular_file(deleted_info)) {
            std::fstream delete_in(deleted_info, std::ios::in);
            if (delete_in.good()) while (!(delete_in.eof())) {
                std::string s;
                std::getline(delete_in, s);
                delete_path(fs::path(s));
            }
        }
        
        // step 2: scan the changes between the tree and the backup being iterated over
        for (const auto &i: fs::recursive_directory_iterator(destination/"..."/(*it)/"incremental")) {
            fs::path relative_i = fs::relative(destination, i);
            add_path(fs::path(relative_i));
        }
        
        // step 3: completed merging a backup point into the tree
        // go to next backup point
        ++it;
    }
}

size_t Backup_chain_tree::scan_changes(std::vector<fs::path> &addition) const {
    addition.clear();
    size_t backup_size = static_cast<size_t>(0u);
    
    const fs::path &source = configuration.get_source_path();
    const fs::path &destination = configuration.get_destination_path();

    // additions
    for (const auto &i: fs::recursive_directory_iterator(source)) {
        // enumerate only regular files
        // TODO symlinks
        if (!(i.is_regular_file())) {
            continue;
        }

        fs::path relative_path = fs::relative(i, source);
        fs::path destination_correspond = destination / "..." / relative_path;

        // if file is excluded or unchanged, then skip the file
        if (
            (configuration.is_excluded(relative_path)) ||
            (fs::exists(destination_correspond) && is_same(i, destination_correspond))
        ) {
            continue;
        } else {
            addition.push_back(relative_path);
            backup_size += fs::file_size(i);
        }
    }

    // deletions
    // traverse over the backup_chain_tree, see if the corresponding files are deleted in source
    std::vector<fs::path> deletions;
    std::stack<std::pair<fs::path, size_t> > s;
    s.push(std::make_pair(fs::path(""), static_cast<size_t>(1u)));

    while (!s.empty()) {
        auto now = s.top(); s.pop();

        for (auto &i: children[now.second]) {
            fs::path child = now.first / i.first;

            if (fs::exists(source/child))
                s.push(std::make_pair(child, i.second));
            else
                deletions.push_back(child);
        }
    }

    return backup_size;
}

} // namespace wbackup 
