#include <filesystem>

#include "filetree.h"
#include "misc.h"

namespace fs = std::filesystem;

namespace wbackup {

template <class T>
File_tree<T>::File_tree()
    : children(1024), vals(1024) { }

template <class T>
int File_tree<T>::set(const std::string &path_str, const T &val) {
    fs::path p(path_str);

    size_t now_node = 1;
    for (auto &i : p) {
        if (!(children.))
        if (!(children[now_node][i.string()])) {
            now_node = children[now_node][i.string()] = new_node();
        }
    }
}

}  // namespace wbackup


