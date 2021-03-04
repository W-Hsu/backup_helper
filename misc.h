#ifndef _MISC_H
#define _MISC_H

#include <string>
#include <vector>
#include <sstream>

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

}  // namespace wbackup

#endif  // _MISC_H
