#include <iostream>
#include <vector>

#include "boost/date_time/posix_time/conversion.hpp"
#include "boost/date_time/posix_time/ptime.hpp"
#include "boost/date_time/posix_time/time_formatters.hpp"
#include "client.h"

int main() {
    std::vector<std::string> ntp_servers = {"ntp.ntsc.ac.cn", "ntp.aliyun.com", "cn.ntp.org.cn"};

    boost::posix_time::ptime ntp_time;
    std::time_t time;
    for (auto it = ntp_servers.begin(); it != ntp_servers.end(); it++) {
        if (gerrard::ntp::GetNTPTime(time, *it)) {
            ntp_time = boost::posix_time::from_time_t(time) + boost::posix_time::hours(8);
            break;
        }
    }
    std::cout << "ntp ptime: " << boost::posix_time::to_iso_extended_string(ntp_time) << std::endl;
    return 0;
}
