#include "latest_tree.h"

namespace wbackup {

/*size_t Latest_tree::scan_changes(std::vector<fs::path> &addition) const {
    addition.clear();
    size_t backup_size = static_cast<size_t>(0u);
    
    const fs::path &source = configuration.get_source_path();
    const fs::path &destination = configuration.get_destination_path();

    // additions
    for (const auto &i: fs::recursive_directory_iterator(source)) {
        // enumerate only regular files
        // TODO symlinks
        if (!(i.is_regular_file())) {
            continue;
        }

        fs::path relative_path = fs::relative(i, source);
        fs::path destination_correspond = destination / "..." / relative_path;

        // if file is excluded or unchanged, then skip the file
        if (
            (configuration.is_excluded(relative_path)) ||
            (fs::exists(destination_correspond) && is_same(i, destination_correspond))
        ) {
            continue;
        } else {
            addition.push_back(relative_path);
            backup_size += fs::file_size(i);
        }
    }

    // deletions
    // traverse over the backup_chain_tree, see if the corresponding files are deleted in source
    std::vector<fs::path> deletions;
    std::stack<std::pair<fs::path, size_t> > s;
    s.push(std::make_pair(fs::path(""), static_cast<size_t>(1u)));

    while (!s.empty()) {
        auto now = s.top(); s.pop();

        for (auto &i: children[now.second]) {
            fs::path child = now.first / i.first;

            if (fs::exists(source/child))
                s.push(std::make_pair(child, i.second));
            else
                deletions.push_back(child);
        }
    }

    return backup_size;
}*/


} // namespace wbackup