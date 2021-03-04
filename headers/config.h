#ifndef _CONFIG_H
#define _CONFIG_H

#include <filesystem>
#include <map>
namespace fs = std::filesystem;

namespace wbackup {

// data structure to store configurations
class __config_t {
private:
    // backup destination path (canonical)
    // all information in this structure is read from
    // config.json in this directory
    fs::path destination;

    // denotes whether the destination has correct 
    // config.json
    bool available;

    // backup source path (canonical)
    fs::path source;

    // files and directories excluded from the backup
    std::map<fs::path, bool> excluded;

    // maximum size of the backup
    uint64_t max_size;

    // read configuration from the destination selected now
    // called on change_destination()
    int get_config();

public:
    __config_t(const __config_t &) = delete;
    __config_t(__config_t &&) = delete;

    // Change the backup destination path, as well as the 
    //
    // information associated with it, by reading config 
    // json in the new destination folder.
    //
    // checks if new_dest exists and json file exists
    int change_destination(char const *new_dest);
    int change_destination(const fs::path &new_dest);

    // change the source path of current backup
    // called on just recovered backup
    int change_source(char const *new_src);
    int change_source(const fs::path &new_dest);

    // source and destination path getter
    const fs::path &get_source_path() const;
    const fs::path &get_destination_path() const;

    // check the selected backup is available
    bool is_available() const;

} configuration;

} // namespace wbackup

#endif
