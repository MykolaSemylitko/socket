
#ifndef _MY_SERVER_HPP_
#define _MY_SERVER_HPP_

#include "logger.hpp"
#include "socket.hpp"

#include <vector>
#include <thread>
#include <mutex>

namespace my
{
	namespace server
	{
		class TCPServer
		{
		private:
			const uint32_t max_error_number = 3;
			my::logger::Logger logger;
			my::socket::TCPSocket socket;

			std::vector<std::thread> connection_hadlers;

		protected:
			void connection_handler_func(SOCKET sock, const uint32_t connection_id);

		public:
			TCPServer(std::string ip, uint16_t port);

			TCPServer(TCPServer&&) = delete;
			TCPServer(const TCPServer&) = delete;
			TCPServer& operator= (TCPServer&&) = delete;
			TCPServer& operator= (const TCPServer&) = delete;

			void run(const uint32_t connections);
		};
	}
}

#endif // !_MY_SERVER_HPP_

