#include "client.h"

#define NTPFRAC(x) (4294 * (x) + ((1981 * (x)) >> 11))
#define LI 0
#define VN 3
#define MODE 3
#define STRATUM 0
#define POLL 4
#define PREC -6

namespace gerrard {
namespace ntp {
bool GetNTPTime(std::time_t& time, const std::string& hostname, int max_retry) {
    try {
        boost::asio::io_service io_service;
        NTPClient client(io_service, hostname);
        for (auto i = 0; i < max_retry; i++) {
            client.Request();
            io_service.run_one();
            if (client.Ready()) {
                time = client.GetTime();
                return true;
            }
        }
    } catch (std::exception const& e) {
        std::cerr << "catch exception: " << e.what() << std::endl;
    }

    return false;
}

NTPClient::NTPClient(boost::asio::io_service& ios, const std::string& hostname) : hostname_(hostname), timer_(ios), socket_(ios) {
    boost::asio::ip::udp::resolver resolver(ios);
    boost::asio::ip::udp::resolver::query query(boost::asio::ip::udp::v4(), hostname_, "ntp");
    boost::asio::ip::udp::resolver::iterator iter = resolver.resolve(query);
    receiver_endpoint_ = *iter;
    socket_.open(boost::asio::ip::udp::v4());
}

NTPClient::~NTPClient() {
    socket_.close();
}

void NTPClient::StartReceive() {
    boost::asio::ip::udp::endpoint sender_endpoint;
    socket_.async_receive_from(boost::asio::buffer(recv_buf_), sender_endpoint, boost::bind(&NTPClient::HandleReceive, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));

    timer_.expires_from_now(std::chrono::seconds(kExpireSecond));
    timer_.async_wait(boost::bind(&NTPClient::HandleTimer, this, boost::asio::placeholders::error));
}

void NTPClient::Request() {
    StartReceive();
    boost::array<char, 48> send_buf = {0};
    send_buf[0] = htonl((LI << 30) | (VN << 27) | (MODE << 24) | (STRATUM << 16) | (POLL << 8) | (PREC & 0xff));
    send_buf[1] = htonl(1 << 16);
    send_buf[2] = htonl(1 << 16);

    auto now = std::chrono::system_clock::now();
    send_buf[10] = htonl(std::chrono::system_clock::to_time_t(now));
    auto micro = int((std::uint64_t)std::chrono::time_point_cast<std::chrono::microseconds>(now).time_since_epoch().count() % 1000000);
    send_buf[11] = htonl(NTPFRAC(micro));
    socket_.send_to(boost::asio::buffer(send_buf), receiver_endpoint_);
}

bool NTPClient::Ready() {
    return ready_;
}

std::time_t NTPClient::GetTime() {
    return time_;
}

void NTPClient::HandleReceive(const boost::system::error_code& err, size_t bytes) {
    timer_.cancel();
    if (err) {
        ready_ = false;
    } else {
        time_ = ntohl((time_t)recv_buf_[5]);
        // 1970-01-01
        time_ = time_ - 2208988800U;
        ready_ = true;
    }
}

void NTPClient::HandleTimer(const boost::system::error_code& err) {
    ready_ = false;
    if (err) {
        std::cerr << "handle timer message:" << err.message() << std::endl;
    }
}
}  // namespace ntp
}  // namespace gerrard
