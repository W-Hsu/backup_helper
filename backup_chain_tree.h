#ifndef _BACKUP_CHAIN_TREE_H
#define _BACKUP_CHAIN_TREE_H

#include <filesystem>

#include "config.h"
#include "directory_tree.h"

namespace fs = std::filesystem;

namespace wbackup {

class Backup_chain_tree: public Directory_tree {
public:
    struct Info;

private:
    std::vector<struct Info> vals;

    // father configuration structure
    // for multi-tasking
    const __config_t &fa_conf;

    size_t new_node() override;

    void add_path(const fs::path &relative);
    void delete_path(const fs::path &relative);

public:
    struct Info {
        
    };

    Backup_chain_tree(const __config_t &fa_conf, size_t initial_size);
    ~Backup_chain_tree() override = default;

    void clear() override;
    void update();

    size_t scan_changes(std::vector<fs::path> &relative) const;
};

} // namespace wbackup 

#endif
