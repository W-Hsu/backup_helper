#ifndef _BACKUP_CHAIN_TREE_H
#define _BACKUP_CHAIN_TREE_H

#include <filesystem>

#include "config.h"
#include "directory_tree.h"
#include "datetime.h"
#include "file_info.h"
#include "latest_tree.h"

namespace fs = std::filesystem;

namespace wbackup {

// store the backup chain information
// 
// it represents the changing history of every file 
//    i.e. when is the file created, modified, or deleted
// the info is for recovering backup and viewing backup
//
// TODO only load data when needed
class Backup_chain_tree: public Directory_tree {
private:
    std::vector<File_info> vals;

    // allocate a node in the unused area
    // if it's out of space, this func will try to allocate more
    size_t new_node() override;

    void add_path(const fs::path &relative);
    void delete_path(const fs::path &relative);

public:
    Backup_chain_tree(size_t init_size);
    ~Backup_chain_tree() override = default;

    // show info of a file/folder
    void lsfile(const fs::path &relative_path, DateTime time_point, std::vector<std::pair<fs::path, fs::file_type> > &vec);

    // clear the backup chain tree to its inital states
    // all nodes and the topographical info will be lost
    // tree size will shrink to initial
    void clear() override;

    // Update the backup chain tree when the destination directory is modified, or the destination path has changed 
    void rebuild();

    // Reconstruct Latest tree on backup error
    Latest_tree rebuild_latest_tree();
};

} // namespace wbackup 

#endif
