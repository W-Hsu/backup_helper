#ifndef _BACKUP_H
#define _BACKUP_H

#include <filesystem>

namespace fs = std::filesystem;

namespace wbackup {

int backup();

void full_backup();
void incremental_backup();
void merge_backup();

void recover_backup(const fs::path &source);

} // namespace wbackup

#endif // _BACKUP_H
