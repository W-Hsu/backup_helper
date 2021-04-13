#ifndef _DATETIME_H
#define _DATETIME_H

#include <string>
#include <ctime>

namespace wbackup {
    
struct DateTime {
    int year, month, day;
    int hour, minute, second;

    DateTime() = default;
    DateTime(const DateTime &other) = default;
    DateTime(time_t timestamp);

    void set(time_t timestamp);
    operator time_t();
};

bool operator<(const DateTime &a, const DateTime &b);

} // namespace wbackup

#endif