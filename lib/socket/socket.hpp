#ifndef  _MY_SOCKET_HPP_
#define _MY_SOCKET_HPP

#include <WinSock2.h>
#include <WS2tcpip.h>
#include <string>
#include <exception>

#include "utils.hpp"
#include "logger.hpp"

namespace my
{
	namespace socket
	{
		class TCPSocket
		{
		private:
			SOCKET socket;
			std::string ip;
			uint16_t port;
			my::logger::Logger logger;

		public:
			TCPSocket(std::string _ip, uint16_t port);
			~TCPSocket();

			TCPSocket() = delete;
			TCPSocket(TCPSocket&& other) = delete;
			TCPSocket(const TCPSocket& other) = delete;
			TCPSocket& operator= (TCPSocket&&) = delete;
			TCPSocket& operator= (const TCPSocket&) = delete;

			void bind();
			void listen();
			SOCKET accept();
			void connect(const std::string& ip, const uint16_t port);
			void send(const std::string& data);
			void shutdown();
		};
	}
}

#endif // ! _MY_SOCKET_HPP_
