#pragma once

#include "net_common.h"
#include "net_message.h"

using namespace boost::asio;
using boost::asio::ip::udp;
using namespace net;

constexpr int K_BUFFER_SIZE = 1024;

namespace net
{
    class UdpClient
    {
    public:
        UdpClient(io_context &io_context, udp::endpoint server_endpoint)
            : socket_(io_context),
              server_endpoint_(server_endpoint),
              stop_flag_(false)
        {
            socket_.open(udp::v4());
            start_receive();
        }

        ~UdpClient()
        {
            stop();
        }

        void stop()
        {
            if (!stop_flag_) {
                stop_flag_ = true;
                socket_.close();
            }
        }

        void send_data(const DataPacket &data)
        {

            if (socket_.is_open()) {
                // The socket is open and the file descriptor is valid.
                std::cout << "Sending data to " << server_endpoint_ << std::endl;
                std::cout << "{" << data.id << ", " << data.value << "}" << std::endl;
            }
            // std::cout << socket_ << std::endl;
            socket_.async_send_to(
                buffer(&data, sizeof(data)), server_endpoint_,
                [](boost::system::error_code ec, std::size_t /*bytes_sent*/)
                {
                    std::cout << "Data sent" << std::endl;
                    if (ec) {
                        std::cerr << "Error: " << ec.message() << std::endl;
                    }
                });
        }

    private:
        void start_receive()
        {
            socket_.async_receive_from(
                buffer(data_), sender_endpoint_,
                [this](boost::system::error_code ec, std::size_t bytes_received)
                {
                    if (!ec && bytes_received == sizeof(DataPacket)) {
                        std::thread([this]()
                                    { process_data(); })
                            .detach();
                    }

                    if (!stop_flag_) {
                        start_receive();
                    }
                });
        }

        void process_data()
        {
            DataPacket *data = reinterpret_cast<DataPacket *>(data_.data());
            std::cout << "Received data from " << sender_endpoint_ << ": id=" << data->id
                      << ", value=" << data->value << std::endl;
        }

        udp::socket socket_;
        udp::endpoint sender_endpoint_;
        udp::endpoint server_endpoint_;
        std::array<char, sizeof(DataPacket)> data_;
        bool stop_flag_;
    };
}