#ifndef _CONFIG_H
#define _CONFIG_H

#include <filesystem>
#include <map>
namespace fs = std::filesystem;

namespace wbackup {

// data structure to store configurations
class __config_t {
private:
    // backup source path and destination path
    fs::path destination;
    fs::path source;

    // files and directories excluded from the backup
    std::map<fs::path, bool> excluded;

    // maximum size of the backup
    uint64_t max_size;

public:
    __config_t(const __config_t &) = delete;
    __config_t(__config_t &&) = delete;

    // Change the backup destination path, as well as the 
    // source path associated with it, by reading config 
    // json in the new destination folder.
    int change_destination(char const *new_dest);
    int change_destination(const fs::path &new_dest);

    // change the source path of current backup
    // called on just recovered backup
    int change_source(char const *new_src);
    int change_source(const fs::path &new_dest);

    // source and destination path getter
    fs::path get_source_path();
    fs::path get_destination_path();

} configuration;

} // namespace wbackup

#endif
