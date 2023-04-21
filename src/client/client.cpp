
#include "client.hpp"

namespace my
{
    namespace client
    {
        TCPClient::TCPClient() :
                    socket::TCPSocket("", 0), logger("TCP Server")
        {
            logger.info("Init\n");
        }

        TCPClient::~TCPClient()
        {
            
        }

        void TCPClient::run(std::string server_ip, uint32_t server_port)
        {
            TCPSocket::connect(server_ip, server_port);

            try
            {
                for (std::string line; std::getline(std::cin, line);) {
                    if (line.empty())
                        break;
                    TCPSocket::send(line);
                }
            }
            catch (std::exception& e)
            {
                logger.debug("During sending traffic exception was caught:\n%s\n", e.what());
            }

            TCPSocket::shutdown();
        }
    }
}
