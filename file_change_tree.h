#ifndef _FILE_CHANGE_TREE_H
#define _FILE_CHANGE_TREE_H

#include <vector>
#include <unordered_map>
#include <filesystem>

#include "config.h"
#include "directory_tree.h"

namespace fs = std::filesystem;

namespace wbackup {

// This data structure stores the filesystem differences of two paths
// Specificly, file modifications, deletions, and additions
//
// Used for incremental backup
class File_change_tree: public Directory_tree {
public:
    struct Info;

private:
    std::vector<struct Info> vals;

    size_t new_node() override;

    void read_backup_chain(const fs::path &dst);
    void add_path(const fs::path &relative_path);
    void delete_path(const fs::path &relative_path);

public:
    ~File_change_tree() override = default;

    struct Info {
        enum Status: int {
            unchanged = 0,
            modified,
            deleted
        } status;

        size_t size;
    };

    File_change_tree();
    void clear() override;

    void make_tree(const fs::path &dst, const fs::path &src);
};

}

#endif
