#include "net_client.h"

using namespace boost::asio;

int main(int argc, char* argv[])
{
    try {
        // if (argc != 3)
        // {
        //   std::cerr << "Usage: udp_client <host> <port>" << std::endl;
        //   return 1;
        // }

        io_context io_context;
        udp::resolver resolver(io_context);
        // udp::endpoint server_endpoint = *resolver.resolve(udp::v4(), argv[1], argv[2]).begin();
        udp::endpoint server_endpoint = *resolver.resolve(udp::v4(), "127.0.0.1", "12345").begin();

        net::UdpClient client(io_context, server_endpoint);
        std::thread([&io_context]() { io_context.run(); }).detach();

        while (true) {
          int id, value;
          std::cin >> id;
          if (std::cin.eof()) {
            break;
          }
          DataPacket data{10, 10};
          client.send_data(data);
        }

        client.stop();
    } catch (std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}