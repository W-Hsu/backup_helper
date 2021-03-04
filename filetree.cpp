#include "headers/filetree.h"
#include "headers/misc.h"

namespace wbackup {

template <class T>
int FileTree<T>::set(const std::string &path, const T &val) {
    size_t i = 0;
    while (path[i]!='/') ++i;

    std::string normalized_path = path.substr(i);
    std::vector<std::string> splitted;
    split(normalized_path, splitted, '/');

    Node *now = &root;
    for (auto &j : splitted) {
        Node *child = now->children[j];
        if (child==nullptr) {
            now->children = child = new FileTree<T>::Node();
        }
    }

    now->value = val;
}

}  // namespace wbackup


