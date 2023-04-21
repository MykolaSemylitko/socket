

#pragma comment(lib,"Ws2_32.lib")

#include "logger.hpp"
#include "server.hpp"

int main()
{
	int rc = 0;
	my::logger::Logger logger("main");
	logger.debug("TCP server version __NONE__\n");
	my::utils::init_WSA();

	my::server::TCPServer server("192.168.1.32", 40405);
	server.run(1000);

	return rc + my::utils::cleanup_WSA();
}

