#pragma once

#include "server.hpp"

namespace my
{
	namespace server
	{
		TCPServer::TCPServer(std::string ip, uint16_t port) :
			socket(ip, port), logger("TCP Server")
		{
			logger.info("Init\n");
		}

		void TCPServer::run(const uint32_t connections)
		{
			logger.info("Server started\n");

			socket.bind();
			socket.listen();

			this->connection_hadlers.reserve(connections);

			for (uint32_t i = 0; i < connections; ++i)
			{
				SOCKET connection_socket = socket.accept();

				this->connection_hadlers.push_back(std::move(std::thread(&TCPServer::connection_handler_func, this, connection_socket, i)));
			}

			for (auto&& t : this->connection_hadlers)
				if (t.joinable())
					t.join();

			logger.info("Server done after hadling %d connections\n", connections);
		}

		void TCPServer::connection_handler_func(SOCKET sock, const uint32_t connection_id)
		{
			int rc;
			char buffer[1024] = {'\0'};
			uint32_t message_size;
			uint32_t errors_cnt = 0;

			while (true)
			{
				rc = recv(sock, buffer, 1024, 0);

				logger.info("rc == % d\n", rc);

				if (rc == 0)
				{
					logger.info("Connection %d closed\n", connection_id);
					return;
				}
				else if (rc > 0)
				{
					if (rc <= 1023)
						buffer[rc] = '\0';

					logger.info("Connection %d received msg:\n%s\n", connection_id, buffer);
				}
				else
				{
					logger.error("RC failed with code %d\n", rc);
					if (++errors_cnt == max_error_number)
					{
						logger.info("Connection %d reached max number of errors: %d, closing connection\n", connection_id, max_error_number);
						break;
					}
				}
			}
		}
	}
}