
#pragma comment(lib,"Ws2_32.lib")

#include "logger.hpp"
#include "client.hpp"

int main()
{
	int rc = 0;
	my::logger::Logger logger("main");
	logger.debug("TCP client version __NONE__\n");
	my::utils::init_WSA();

	my::client::TCPClient client;
	client.run("192.168.1.32", 40405);

	return rc + my::utils::cleanup_WSA();
}
