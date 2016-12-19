#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
using namespace boost::posix_time;
using namespace boost::gregorian;

void print(const boost::system::error_code &e)
{
	std::cout << "Hi ..." << std::endl;
	ptime now = second_clock::local_time();
cout << to_simple_string(now) << endl;
}


int main()
{
	boost::asio::io_service io; 
	ptime now = second_clock::local_time();
cout << to_simple_string(now) << endl;
	sleep(3);
	//boost::asio::deadline_timer t(io, boost::posix_time::seconds(-1));
	boost::asio::deadline_timer t(io, now);
	t.async_wait(&print);

	io.run(); 
	return 0;
}
