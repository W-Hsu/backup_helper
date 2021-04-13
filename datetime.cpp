#include "datetime.h"
#include "misc.h"

#include <boost/format.hpp>
#include <sstream>

using fmt = boost::format;

namespace wbackup {

DateTime::DateTime(time_t timestamp) {
    struct tm time_info;
    gmtime_r(&timestamp, &time_info);
    this->year   = time_info.tm_year + 1900;
    this->month  = time_info.tm_mon;
    this->day    = time_info.tm_mday;
    this->hour   = time_info.tm_hour;
    this->minute = time_info.tm_min;
    this->second = time_info.tm_sec;
}

DateTime::operator time_t() {
    struct tm time_info;
    time_info.tm_year = this->year - 1900;
    time_info.tm_mon  = this->month ;
    time_info.tm_mday = this->day   ;
    time_info.tm_hour = this->hour  ;
    time_info.tm_min  = this->minute;
    time_info.tm_sec  = this->second;
    return mktime(&time_info);
}

bool operator<(const DateTime &a, const DateTime &b) {
    return
        a.year   < b.year   ? true :
        a.month  < b.month  ? true :
        a.day    < b.day    ? true :
        a.hour   < b.hour   ? true :
        a.minute < b.minute ? true :
        a.second < b.second ? true :
    false;
}

} // namespace wbackup
