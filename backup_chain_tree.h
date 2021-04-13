#ifndef _BACKUP_CHAIN_TREE_H
#define _BACKUP_CHAIN_TREE_H

#include <filesystem>

#include "config.h"
#include "directory_tree.h"
#include "datetime.h"

namespace fs = std::filesystem;

namespace wbackup {

class Backup_chain_tree: public Directory_tree {
public:
    struct Info;

private:
    std::vector<struct Info> vals;

    // allocate a node in the unused area
    // if it's out of space, this func will try to allocate more
    size_t new_node() override;

    void add_path(const fs::path &relative);
    void delete_path(const fs::path &relative);

public:
    struct Info {
        std::vector<std::string> versions_location;
    };

    Backup_chain_tree(size_t init_size);
    ~Backup_chain_tree() override = default;

    // clear the backup chain tree to its inital states
    // all nodes and the topographical info will be lost
    // tree size will shrink to initial
    void clear() override;

    // Update the backup chain tree when the destination directory is modified, or the destination path has changed 
    void update();

    // scan changes between the backup chain (tree) and the source path
    // the path of files to be copied will be stored into param relative
    // the size of files to be copied will be returned by the function
    size_t scan_changes(std::vector<fs::path> &relative) const;
};

} // namespace wbackup 

#endif
