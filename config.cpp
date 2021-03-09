#include "config.h"
#include "exceptions.h"
#include "headers/json.hpp"

#include <boost/format.hpp>
#include <fstream>

using fmt = boost::format;

namespace wbackup {

void __config_t::get_config(const nlohmann::json &j) {
    // complusory values
    //  * source directory path
    try {
        std::string new_src_str;
        nlohmann::from_json(j["source"], new_src_str);
        source = fs::path(new_src_str);
    } catch (std::exception &ex) {
        Bad_value ex1("Error: missing source path in config.json.");
        throw ex1;
    }

    // optional values
    //  * maximum backup size
    try {
        nlohmann::from_json(j["maximimSize"], max_size);
    } catch (std::exception &ex) {
        max_size = 0x1900000000ll;  // 100GB default
    }

    // optional values
    //  * excluded folders
    exclude_tree.clear();
    try {
        auto excluded_list = j["exclude"];
        for (auto &i : excluded_list) {
            std::string s;
            nlohmann::from_json(i, s);
            
            fs::path p(s);
            fs::relative(p, source);

            exclude_tree.set(p, true);
        }
    } catch (std::exception &e) {

    }
}

void __config_t::change_destination(char const *new_dest_path) {
    fs::path path(new_dest_path);
    return change_destination(new_dest_path);
}

void __config_t::change_destination(const fs::path &new_dest_path) {
    fs::directory_entry new_dest_ent;
    
    // new_dest shall be a directoty
    if (!(new_dest_ent.is_directory())) {
        File_not_found ex(
            (fmt("Error: %s: Not a directory.") % new_dest_path.c_str()).str()
        );
        throw ex;
    }
    
    // new_dest shall contain config.json
    fs::path new_dest_json_path(new_dest_path/"config.json");
    fs::directory_entry new_dest_json_ent(new_dest_json_path);

    if (!(new_dest_json_ent.is_regular_file())) {
        File_not_found ex(
            (fmt("Error: %s: Not a regular file.") % new_dest_path.c_str()).str()
        );
        throw ex;
    }

    // read config.json into nlohmann::json
    std::fstream json_in(new_dest_json_path, std::ios::in);
    if (!(json_in.good())) {
        Bad_permission ex(
            (fmt("Error: %s: Not a regular file.") % new_dest_json_path.c_str()).str()
        );
        throw ex;
    }

    nlohmann::json j;
    try {
        json_in >> j;
    } catch (std::exception &e) {
        Bad_format ex(
            (fmt("Error: %s: parse error.") % new_dest_json_path.c_str()).str()
        );
        throw ex;
    }

    get_config(j);

    destination = fs::canonical(new_dest_path);
}

bool __config_t::is_excluded(const fs::path &query_path) const {
    fs::path p(query_path);
    fs::relative(p, source);
    return exclude_tree.get(p);
}

// getters
const fs::path &__config_t::get_destination_path() const { return this->destination; }
const fs::path &__config_t::get_source_path() const { return this->source; }
const uint64_t __config_t::get_max_size() const { return this->max_size; }
bool __config_t::is_excluded(const fs::path &query_path) const { return this->exclude_tree.get(query_path); }

}