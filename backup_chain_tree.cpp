#include "backup_chain_tree.h"
#include "misc.h"

#include <stack>
#include <string>
#include <fstream>

namespace wbackup {

Backup_chain_tree::Backup_chain_tree(const __config_t &fa_conf, size_t initial_size=default_tree_size):
    Directory_tree(initial_size), vals(initial_size), fa_conf(fa_conf) { }

size_t Backup_chain_tree::new_node() {
    if (node_cnt+1==children.size()) {
        children.resize(2*children.max_size());
        vals.resize(children.max_size());
    }
    return ++node_cnt;
}

void Backup_chain_tree::update() {
    this->clear();

    std::vector<std::string> backup_list;
    fa_conf.get_backup_list(backup_list);
    const fs::path &destination = fa_conf.get_destination_path();

    // find the last full backup, start at that point
    auto it = backup_list.begin();
    auto last_full_backup = backup_list.end();
    while (it!=backup_list.end()) {
        if (fs::exists(fs::path(destination/"..."/(*it)/"full")))
            last_full_backup = it;
        ++it;
    }

    // read full backup first
    it = last_full_backup;
    for (const auto &i: fs::recursive_directory_iterator(destination/"..."/(*it)/"full")) {
        fs::path relative_i = fs::relative(destination, i);
        add_path(relative_i);
    }
    ++it;

    // read incremental backup
    while (it!=backup_list.end()) {
        fs::path backup_point(destination/"..."/(*it));

        // read deleted file/directories
        fs::path deleted_info = backup_point/"deleted.info";
        if (fs::exists(deleted_info) && fs::is_regular_file(deleted_info)) {
            std::fstream delete_in(deleted_info, std::ios::in);
            if (delete_in.good()) while (!(delete_in.eof())) {
                std::string s;
                std::getline(delete_in, s);
                delete_path(fs::path(s));
            }
        }
        
        // read added/modified file/directories
        for (const auto &i: fs::recursive_directory_iterator(destination/"..."/(*it)/"incremental")) {
            fs::path relative_i = fs::relative(destination, i);
            add_path(fs::path(relative_i));
        }
        
        ++it;
    }
}

size_t Backup_chain_tree::scan_changes(std::vector<fs::path> &addition) const {
    addition.clear();
    size_t backup_size = static_cast<size_t>(0u);
    
    const fs::path &source = fa_conf.get_source_path();
    const fs::path &destination = fa_conf.get_destination_path();

    // Additions
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
            (fa_conf.is_excluded(relative_path)) ||
            (fs::exists(destination_correspond) && is_same(i, destination_correspond))
        ) {
            continue;
        } else {
            addition.push_back(relative_path);
            backup_size += fs::file_size(i);
        }
    }

    // deletions
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
