#ifndef _LATEST_TREE_H
#define _LATEST_TREE_H

#include "directory_tree.h"
#include <filesystem>

namespace fs = std::filesystem;

namespace wbackup {

class Latest_tree: public Directory_tree {
private:
    size_t new_node() override;

    std::vector<fs::file_type> vals;

public:
    Latest_tree(size_t init_size);

    void read();
    void permanence() const;

    // scan changes between the latest backup tree and the source path
    // the path of files to be copied will be stored into param relative
    // the size of files to be copied will be returned by the function
    size_t scan_changes(std::vector<fs::path> &relative) const;
};

} // namespace wbackup


#endif