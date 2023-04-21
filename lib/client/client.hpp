#ifndef __MY_CLIENT_HPP__
#define __MY_CLIENT_HPP__

#include "logger.hpp"
#include "socket.hpp"

#include <iostream>
#include <exception>

namespace my
{
    namespace client
    {
        class TCPClient: protected socket::TCPSocket
        {
        private:
			my::logger::Logger logger;

		protected:

		public:
			TCPClient();

			TCPClient(TCPClient&&) = delete;
			TCPClient(const TCPClient&) = delete;
			TCPClient& operator= (TCPClient&&) = delete;
			TCPClient& operator= (const TCPClient&) = delete;

			virtual ~TCPClient();

			void run(std::string server_ip, uint32_t server_port);
        };
    }
}

#endif
