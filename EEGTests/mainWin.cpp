#include <boost/asio/serial_port.hpp>
#include <boost/asio.hpp>

using namespace boost;

char read_char(){
	asio::io_service io;
	asio::serial_port port(io);

	port.open("COM3");
	port.set_option(asio::serial_port_base::baud_rate(115200));

	char c;

	//read 1 character into c, this will block forever if no character arrives
	asio::read(port,asio::buffer(&c,1));

	port.close();

	return c;
}

int main(){

	cout << "Hello World!" << endl;

	return 0;
}