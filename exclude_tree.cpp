#include "exclude_tree.h"
#include "misc.h"

#include <filesystem>
#include <stack>

namespace fs = std::filesystem;

namespace wbackup {

Exclude_tree::Exclude_tree():
    Directory_tree() { }

size_t Exclude_tree::new_node() {
    if (node_cnt+1==children.size()) {
        children.resize(2*children.max_size());
        vals.resize(children.max_size());
    }

    return ++node_cnt;
}

void Exclude_tree::clear() {
    children.clear();
    vals.clear();
    children.resize(1024);
    vals.resize(1024);

    node_cnt = 1;
}

void Exclude_tree::set(const fs::path &excluded_path_relative, bool val) {
    size_t now_node_index = 1;
    for (auto &i: excluded_path_relative) {
        size_t & child_index = children[now_node_index][i.string()];

        // Node does not exist: create required node
        if (!child_index)
            now_node_index = child_index = new_node();  // attention: child_index is a reference
        // Father node has been excluded: no need for creating new node
        else if (vals[child_index]==true) {
            now_node_index = child_index;
            break;
        }
        // Father node exists and not excluded: go there
        else
            now_node_index = child_index;
    }
    
    auto it = vals.begin();
    std::advance(it, now_node_index);
    (*it) = val;
}

bool Exclude_tree::get(const fs::path &query_path) const {
    bool ret = false;
    size_t now_node_index = 1;
    for (auto &i: query_path) {
        // std::unordered_map::operator[] is non-const, voilating const semantic
        // use std::unordered_map::at instead
        size_t child_index = children[now_node_index].at(i.string());
        
        if (!child_index)
            break;
        else if (vals[child_index]==true) {
            ret = true;
            break;
        }
        else
            now_node_index = child_index;
    }
    return ret;
}

void Exclude_tree::traverse(std::vector<std::string> &traverse_result) const {
    traverse_result.clear();
    std::stack<std::pair<fs::path, size_t> > s;

    s.push(std::make_pair(fs::path(""), 1));

    while (!s.empty()) {
        auto now = s.top(); s.pop();

        for (auto &i: children[now.second]) {
            fs::path child = now.first / i.first;

            if (vals[i.second]==true)
                traverse_result.push_back(child.string());
            else
                s.push(std::make_pair(child, i.second));
        }
    }
    // TODO
}

}  // namespace wbackup
