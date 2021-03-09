#ifndef _FILE_CHANGE_TREE_H
#define _FILE_CHANGE_TREE_H

#include <vector>
#include <unordered_map>
#include <filesystem>

#include "config.h"

namespace fs = std::filesystem;

namespace wbackup {

// This data structure stores the filesystem differences of two paths
// Specificly, file modifications, deletions, and additions
//
// Used for incremental backup
class File_change_tree {
private:
    // node[0] is unused, node[1] is root node
    // node count(max node index)
    size_t node_cnt;

    // children pointers
    std::vector<std::unordered_map<std::string, size_t> > children;

    // change infos
    std::vector<struct Info> info;

public:
    struct Info {
        enum Status: int {
            modified = 0,
            deleted
        } status;

        size_t size;
    };

    void make_tree(fs::path);
};

}

#endif
