#ifndef _GERRARD_NTP_CLIENT_H_
#define _GERRARD_NTP_CLIENT_H_

#include <chrono>
#include <ctime>
#include <iostream>
#include <string>

#include "boost/array.hpp"
#include "boost/asio.hpp"
#include "boost/asio/steady_timer.hpp"
#include "boost/bind/bind.hpp"

namespace gerrard {
namespace ntp {
const int kExpireSecond = 1;

bool GetNTPTime(std::time_t& time, const std::string& hostname, int max_retry = 2);

class NTPClient {
   public:
    NTPClient(boost::asio::io_service& ios, const std::string& hostname);

    void Request();

    std::time_t GetTime();

    bool Ready();

    ~NTPClient();

   private:
    void HandleReceive(const boost::system::error_code& err, size_t bytes);

    void HandleTimer(const boost::system::error_code& err);

    void StartReceive();

    NTPClient(const NTPClient&) = delete;

    NTPClient& operator=(const NTPClient&) = delete;

   private:
    bool ready_{false};
    std::string hostname_;

    std::time_t time_ = 0;

    boost::asio::steady_timer timer_;
    boost::asio::ip::udp::endpoint receiver_endpoint_;
    boost::asio::ip::udp::socket socket_;

    boost::array<unsigned long, 8> recv_buf_;
};
}  // namespace ntp
}  // namespace gerrard

#endif /* _GERRARD_NTP_CLIENT_H_ */
