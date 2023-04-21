#pragma once

#include "socket.hpp"

namespace my
{
	namespace socket
	{
		TCPSocket::TCPSocket(std::string _ip_addr, uint16_t _port) : ip(_ip_addr), port(_port), logger("TCP socket")
		{
			logger.info("Init\n");

			socket = my::utils::socket::get_tcp_socket();
		}

		TCPSocket::~TCPSocket()
		{
			if (socket != INVALID_SOCKET)
			{
				logger.debug("Closing socket\n");
				my::utils::socket::close(socket);
			}
		}

		void TCPSocket::bind()
		{
			logger.info("Bind\n");

			if (my::utils::socket::bind_tcp_socket(socket, ip, port))
			{
				throw std::runtime_error("Failed to bind socket");
			}
		}

		void TCPSocket::listen()
		{
			logger.info("Listen\n");

			if (my::utils::socket::listen(socket))
			{
				throw std::runtime_error("Listen failed");
			}
		}

		SOCKET TCPSocket::accept()
		{
			logger.info("accept\n");

			SOCKET connection_sock = my::utils::socket::accept(socket);
			if (connection_sock == INVALID_SOCKET)
			{
				throw std::runtime_error("Failed to accept a connection");
			}

			return connection_sock;
		}

		void TCPSocket::connect(const std::string& ip, const uint16_t port)
		{
			logger.info("connect\n");

			if (my::utils::socket::connect(socket, ip, port))
			{
				throw std::runtime_error("Failed to connect");
			}
		}

		void TCPSocket::send(const std::string& data)
		{
			logger.debug("sending %s\n", data.c_str());

			int rc = my::utils::socket::send(this->socket, data);
			if (rc == SOCKET_ERROR)
			{
				throw std::runtime_error("Failed to send data. rc=" + std::to_string(WSAGetLastError()));
			}
		}

		void TCPSocket::shutdown()
		{
			logger.debug("shudown connection\n");

			int rc = my::utils::socket::shutdown(this->socket);
			if (rc)
			{
				throw std::runtime_error("Failed to shutdown the connection. rc=" + std::to_string(rc));
			}
		}
	}
}
