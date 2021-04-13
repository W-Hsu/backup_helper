#ifndef _FILE_INFO_H
#define _FILE_INFO_H

#include <vector>
#include <filesystem>

#include "datetime.h"

namespace fs = std::filesystem;

namespace wbackup {

enum File_operation: int {
    modify = 0,
    remove
};

struct File_info {
    std::vector<std::pair<DateTime, File_operation> > file_op;
    fs::file_type file_type;
};

} // namespace wbackup

#endif