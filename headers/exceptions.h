#ifndef _EXCEPTIONS_H
#define _EXCEPTIONS_H

#include <stdexcept>
#include <string>

#define NEW_RUNTIME_ERROR_T(TYPENAME) \
class TYPENAME : public std::runtime_error { \
public: \
    TYPENAME(const std::string &override_what_str) noexcept; \
    TYPENAME(char const *override_what_str) noexcept; \
    TYPENAME(const TYPENAME &other) noexcept; \
}

namespace wbackup {

NEW_RUNTIME_ERROR_T(File_not_found);

NEW_RUNTIME_ERROR_T(Bad_permission);

} // namespace wbackup

#undef NEW_RUNTIME_ERROR_T
#endif