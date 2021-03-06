#ifndef _MISC_H
#define _MISC_H

#include <string>
#include <vector>
#include <sstream>
#include <chrono>
#include <ctime>
#include <filesystem>
#include <boost/format.hpp>

namespace cron = std::chrono;
namespace fs = std::filesystem;
using fmt = boost::format;

namespace wbackup {

void split(const std::string &s, std::vector<std::string> &splitted, char delim = ',') {
    splitted.clear();
    std::stringstream sstream(s);

    std::string split_part;
    splitted.clear();
    while (std::getline(sstream, split_part, delim)) {
        splitted.push_back(split_part);
    }
}

std::string get_system_time() {
    time_t now_timestamp = cron::system_clock::to_time_t(cron::system_clock::now());
    struct tm *ptm = gmtime(&now_timestamp);

    return (
        //    y    m    d    h    m    s
        fmt("%d_%02d_%02d_%02d_%02d_%02d")
            % ptm->tm_year % ptm->tm_mon % ptm->tm_mday % ptm->tm_hour % ptm->tm_min % ptm->tm_sec
    ).str();
}

bool is_same(const fs::path &a, const fs::path &b) {
    fs::directory_entry a_ent(a), b_ent(b);

    if (a_ent.is_regular_file() && b_ent.is_regular_file()) {
        return
            (a_ent.last_write_time()==b_ent.last_write_time()) &&
            (a_ent.file_size()==b_ent.file_size());
    }
    else
        return false;
}

}  // namespace wbackup

#endif  // _MISC_H
