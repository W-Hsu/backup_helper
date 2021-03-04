#include "exceptions.h"
#include <string>

#define NEW_RUNTIME_ERROR_T_CONSTRUCTORS(TYPENAME) \
TYPENAME::TYPENAME(char const *override_what_str) noexcept \ 
    : std::runtime_error(override_what_str) { } \
TYPENAME::TYPENAME(const std::string &override_what_str) noexcept \
    : std::runtime_error(override_what_str) { } \
TYPENAME::TYPENAME(const TYPENAME &other) noexcept \
    : std::runtime_error(other.what()) { }

namespace wbackup {

NEW_RUNTIME_ERROR_T_CONSTRUCTORS(File_not_found);
NEW_RUNTIME_ERROR_T_CONSTRUCTORS(Bad_permission);

} // namespace wbackup

#undef NEW_RUNTIME_ERROR_T_CONSTRUCTORS
