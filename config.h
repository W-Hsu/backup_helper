#ifndef _CONFIG_H
#define _CONFIG_H

#include <filesystem>
#include <map>

#include "headers/json.hpp"
#include "exclude_tree.h"

namespace fs = std::filesystem;

namespace wbackup {

// data structure to store configurations
class __config_t {
private:
    // backup destination path (canonical)
    // all information in this structure is read from
    // config.json in this directory
    fs::path destination;

    // backup source path (canonical)
    fs::path source;

    // files and directories excluded from the backup
    Exclude_tree exclude_tree;

    // maximum size of the backup
    uint64_t max_size;

    // read configuration from the destination selected now
    // called on change_destination()
    //
    // throws Bad_value
    void get_config(const nlohmann::json &j);

public:
    __config_t() = default;
    __config_t(const __config_t &) = delete;
    __config_t(__config_t &&) = delete;

    // Change the backup destination path, and read config.json
    // associated with it into (*this)
    //
    // throws File_not_found on:
    //      (1) new_dest_path is not a directory
    //      (2) no config.json under new_dest_path
    // 
    // throws Bad_format on:
    //      (1) bad json format
    // 
    // throws Bad_value on:
    //      (1) missing complusory value in config.json
    //      (2) illegal compulsory value in config.json
    void change_destination(char const *new_dest);
    void change_destination(const fs::path &new_dest);

    // change the source path of current backup
    // called on just recovered backup
    int change_source(char const *new_src);
    int change_source(const fs::path &new_src);

    // getters
    const fs::path &get_destination_path() const;
    const fs::path &get_source_path() const;
    const uint64_t get_max_size() const;
    bool is_excluded(const fs::path &query_path) const;
};

extern __config_t configuration;

} // namespace wbackup

#endif
