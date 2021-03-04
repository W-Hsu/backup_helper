#include "headers/config.h"
#include "headers/json.hpp"
#include <fstream>

namespace wbackup {

int __config_t::get_config() {
    fs::path new_dest_json = destination / "config.json";

    // config.json shall be readable
    std::fstream json_in(new_dest_json, std::ios::in);
    if (!json_in) return 1;

    // json is well-formed
    nlohmann::json j;
    try {
        json_in >> j;
    } catch (std::exception &ex) {
        return 2;
    }

    // complusory values
    //  * source directory path
    try {
        std::string new_src_str;
        nlohmann::from_json(j["source"], new_src_str);
        source = fs::path(new_src_str);
    } catch (std::exception &ex) {
        return 3;
    }

    // optional values
    //  * maximum backup size
    try {
        nlohmann::from_json(j["maximimSize"], max_size);
    } catch (std::exception &ex) {
        max_size = 0x280000000ll;  // 10GB
    }

    // optional values
    //  * excluded folders
    excluded.clear();
    try {
        auto excluded_list = j["exclude"];
        for (auto &i : excluded_list) {
            std::string s;
            nlohmann::from_json(i, s);
            excluded[s] = true;
        }
    } catch (std::exception &e) {
        
    }
}

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

}

}