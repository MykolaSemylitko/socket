#ifndef _MY_UTILS_HPP_
#define _MY_UTILS_HPP_

#include <WinSock2.h>
#include <WS2tcpip.h>
#include <string>
#include <tchar.h>

#include "logger.hpp"

namespace my
{
	namespace utils
	{
		int init_WSA();
		int cleanup_WSA();

		namespace socket
		{
			SOCKET get_tcp_socket();
			int bind_tcp_socket(SOCKET sock, std::string ip_address, uint32_t port);
			int listen(SOCKET sock);
			SOCKET accept(SOCKET sock);
			int connect(SOCKET sock, std::string server_ip, uint16_t server_port);
			int close(SOCKET sock);
			int shutdown(SOCKET sock);
			int send(SOCKET sock, const std::string& message);
		}
	}
}

#endif // !_MY_UTILS_HPP_
