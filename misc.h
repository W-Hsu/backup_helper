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

template <class T>
T get_val(const std::string &s) {
    std::stringstream sstr(s);
    T ret;
    sstr >> ret;
    return ret;
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

bool is_leap_year(int year) {
    if (year%100==0) return year%400==0;
    return year%4==0;
}

}  // namespace wbackup

#endif  // _MISC_H
