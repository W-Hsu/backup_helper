#include "headers/config.h"
#include "headers/json.hpp"
#include <fstream>

namespace wbackup {

int __config_t::change_destination(char const *new_dest) {
    fs::path path(new_dest);
    return change_destination(new_dest);
}

int __config_t::change_destination(const fs::path &new_dest) {
    fs::directory_entry new_dest_ent;
    
    // new_dest shall be a directoty
    if (!(new_dest_ent.is_directory())) return 1;
    
    // new_dest shall contain config.json
    fs::directory_entry new_dest_json(new_dest/"config.json");
    if (!(new_dest_json.is_regular_file())) return 2;

    // config.json shall be readable
    std::fstream json_in(new_dest_json.path(), std::ios::in);
    if (!json_in) return 3;

    // json is well-formed
    nlohmann::json j;
    try { 
        json_in >> j;
    } catch (std::exception &ex) {
        return 4;
    }

    // there is source folder info in json
    
}

}