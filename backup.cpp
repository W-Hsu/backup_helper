#include "backup.h"
#include "config.h"
#include "file_change_tree.h"

#include <filesystem>
#include <exception>

namespace fs = std::filesystem;

namespace wbackup {

// TODO exception handling
void full_backup() {
    static fs::path dst = configuration.get_destination_path() / "back_data" / get_system_time();
    const fs::path &src = configuration.get_source_path();
    
    fs::recursive_directory_iterator rec_iterator(src);
    for (auto &i: rec_iterator) {
        fs::path relative_child = fs::relative(i, src);
        fs::path dest_match(dst / relative_child);
        
        if (configuration.is_excluded(relative_child)) {
            continue;
        }

        if (i.is_directory()) {
            fs::create_directory(dest_match);
        } else if (i.is_regular_file()) {
            fs::copy(i, dest_match);
        }
    }
}

// TODO exception handling
void incremental_backup() {
    try {
        static fs::path dst = configuration.get_destination_path() / "backup_data";
        const fs::path &src = configuration.get_source_path();

        File_change_tree *file_change_tree = new File_change_tree();
        file_change_tree->make_tree(dst, src);

        delete file_change_tree;
    } catch (std::exception &ex) {

    }
}

void merge_backup() {
    // preparations
    //   * scan changes in the filesystem
    //   * enumerate the files to be copied
    //   * calculate the size of the new backup
    //      - if the backup is too large, merge the earlist backup
    //   * write deleted file's relative path into a file
    // 
}

} // namespace wbackup

int main() {

}
