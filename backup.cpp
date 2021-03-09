#include "backup.h"
#include "config.h"

#include <filesystem>

namespace fs = std::filesystem;

namespace wbackup {

void full_backup(fs::path now_relative) {
    static fs::path dst = configuration.get_destination_path() / "back_data" / get_system_time();
    const fs::path &src = configuration.get_source_path();

    if (configuration.is_excluded(now_relative))
        return;
    
    fs::directory_iterator di(src/now_relative);
    for (auto &every_ent: di) {
        fs::path child_relative = every_ent.path();
        fs::relative(child_relative, src);

        if (every_ent.is_directory()) {
            fs::create_directory(dst/child_relative);
            full_backup(child_relative);
        }
        else if (every_ent.is_regular_file())
            fs::copy_file(src/child_relative, dst/child_relative);  // TODO exception handling
    } 
}

void incremental_backup() {
    
}

void merge_backup() {
    
}

} // namespace wbackup
