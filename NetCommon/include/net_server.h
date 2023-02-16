#pragma once

#include "net_common.h"
#include "net_message.h"

using namespace boost::asio;
using boost::asio::ip::udp;

constexpr int K_BUFFER_SIZE = 1024;

namespace net
{
    class UdpServer
    {
    public:
        UdpServer(io_context &io_context, udp::endpoint endpoint)
            : socket_(io_context, endpoint),
              stop_flag_(false)
        {
            start_receive();
        }

        ~UdpServer()
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

        void send_data(const DataPacket &data, udp::endpoint &endpoint)
        {
            socket_.async_send_to(
                buffer(&data, sizeof(data)), endpoint,
                [](boost::system::error_code ec, std::size_t /*bytes_sent*/)
                {
                    if (ec) {
                        std::cerr << "Error: " << ec.message() << std::endl;
                    }
                });
        }

    private:
        void start_receive()
        {
            if (socket_.is_open()) {
                // The socket is open and the file descriptor is valid.
                std::cout << "Listening on " << socket_.local_endpoint() << std::endl;
            }
            socket_.async_receive_from(
                buffer(data_), sender_endpoint_,
                [this](boost::system::error_code ec, std::size_t bytes_received)
                {
                    std::cout << "Client endpoint " << sender_endpoint_ << std::endl;
                    if (!ec && bytes_received == sizeof(DataPacket)) {
                        std::thread([this](){process_data();}).detach();
                    }
                    if (!stop_flag_) {
                        start_receive();
                    }
                }
            );
        }

        void process_data()
        {
            DataPacket *data = reinterpret_cast<DataPacket *>(data_.data());
            std::cout << "Received data from " << sender_endpoint_ << ": id=" << data->id
                      << ", value=" << data->value << std::endl;

            // Send the data back to the sender
            send_data(*data, sender_endpoint_);
        }

        udp::socket socket_;
        udp::endpoint sender_endpoint_;
        std::array<char, sizeof(DataPacket)> data_;
        bool stop_flag_;
    };
}