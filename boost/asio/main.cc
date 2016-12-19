#include <iostream>
#include <boost/asio.hpp>

using namespace std; 
using namespace boost::asio;


int main()
{
	//io_service service;
	//ip::tcp::endpoint ep(ip::address::from_string("127.0.0.1"), 80);
	//ip::tcp::socket sock(service);
	//sock.connect(ep);

	//// 1. write 
	//sock.write_some(buffer("Get /index.html\n"));
	//cout << "bytes available " << sock.available() << endl;

	//// 2. read
	//char buf[1024];
	//size_t read = sock.read_some(buffer(buf));
	//cout << "read size: " << read << endl;
	//cout << buf << endl;


	io_service service; 
	ip::udp::socket sock(service);
	sock.open(ip::udp::v4());
	ip::udp::endpoint receiver_ep(ip::address::from_string("192.168.99.184"), 33445);
	sock.send_to(buffer("testing\n"), receiver_ep);

	char buff[1024];
	ip::udp::endpoint sender_ep;
	sock.receive_from(buffer(buff), sender_ep);

	return 0;
}	
