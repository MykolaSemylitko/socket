#include "utils.hpp"

namespace my
{
	namespace utils
	{
		my::logger::Logger logger("Utils");

		int init_WSA()
		{
			logger.debug("Init WSA\n");
			WSADATA wsaData;

			if (WSAStartup(MAKEWORD(2, 2), &wsaData))
			{
				logger.error("WSA init failed\n");
				return 1;
			}

			return 0;
		}

		int cleanup_WSA()
		{
			logger.debug("WSA cleanup\n");

			return WSACleanup();

		}

		namespace socket
		{
			SOCKET get_tcp_socket()
			{
				logger.debug("Create socket\n");

				int iResult = 0;
				SOCKET sock = INVALID_SOCKET;

				sock = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
				if (sock == INVALID_SOCKET) {
					logger.error("socket function failed with error: %ld\n", WSAGetLastError());
					return INVALID_SOCKET;
				}

				return sock;
			}

			int bind_tcp_socket(SOCKET sock, std::string ip_address, uint32_t port)
			{
				logger.debug("Bind socket to %s:%d\n", ip_address.c_str(), port);

				int iResult;
				sockaddr_in service;
				service.sin_family = AF_INET;
				service.sin_addr.s_addr;
				service.sin_port = htons(port);
				InetPton(AF_INET, ip_address.c_str(), &service.sin_addr.s_addr);

				iResult = bind(sock, (SOCKADDR*)&service, sizeof(service));
				if (iResult == SOCKET_ERROR) {
					logger.error("bind function failed with error %d\n", WSAGetLastError());
					return 1;
				}

				return 0;
			}

			int listen(SOCKET sock)
			{
				logger.debug("Socket listen\n");

				if (::listen(sock, SOMAXCONN) == SOCKET_ERROR)
				{
					logger.error("listen function failed with error: %d\n", WSAGetLastError());
					return 1;
				}

				return 0;
			}

			SOCKET accept(SOCKET sock)
			{
				logger.info("Accepting connection\n");

				SOCKET accept_socket;
				accept_socket = ::accept(sock, NULL, NULL);

				if (accept_socket == INVALID_SOCKET) {
					logger.error("accept failed with error: %d\n", WSAGetLastError());
					return INVALID_SOCKET;
				}

				return accept_socket;
			}

			int connect(SOCKET sock, std::string server_ip, uint16_t server_port)
			{
				logger.debug("Connecting to %s:%d\n", server_ip.c_str(), server_port);

				int iResult;
				sockaddr_in clientService;
				clientService.sin_family = AF_INET;
				clientService.sin_port = htons(server_port);
				InetPton(AF_INET, server_ip.c_str(), &clientService.sin_addr.s_addr);

				iResult = ::connect(sock, (SOCKADDR*)&clientService, sizeof(clientService));
				if (iResult == SOCKET_ERROR) {
					logger.error("connect function failed with error: %d\n", WSAGetLastError());
					iResult = closesocket(sock);
					return 1;
				}

				return 0;
			}

			int close(SOCKET sock)
			{
				return ::closesocket(sock);
			}

			int shutdown(SOCKET sock)
			{
				int iResult = ::shutdown(sock, SD_SEND);
				if (iResult == SOCKET_ERROR)
				{
					logger.error("Shutdown failed with rc %d", WSAGetLastError());
					return 1;
				}

				return 0;
			}

			int send(SOCKET sock, const std::string& message)
			{
				int rc = ::send(sock, message.c_str(), message.length(), 0);
				if (rc == SOCKET_ERROR)
				{
					logger.error("Failed to send data. rc=%d\n", WSAGetLastError());
					return 1;
				}

				return 0;
			}
		}
	}
}