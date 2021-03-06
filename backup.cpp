#include "backup.h"
#include "config.h"

#include <filesystem>

namespace fs = std::filesystem;

namespace wbackup {

void full_backup() {
    static fs::path destination_of_this_time = configuration.get_destination_path() / "back_data" / get_system_time();
}

void merge_backup() {
    
}

} // namespace wbackup
