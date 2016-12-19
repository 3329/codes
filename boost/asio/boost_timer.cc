#include <iostream>
#include <boost/asio.hpp>
using namespace std;
using namespace boost::asio;


void printer(const boost::system::error_code e)
{
	if (e)
	{
		cout << e.value() << endl;
	}
}


int main()
{
	boost::asio::io_service io;
	boost::asio::deadline_timer timer(io, boost::posix_time::seconds(100));
	boost::system::error_code e;
	timer.async_wait(&printer);
cout << "1111111111111111111" << endl;
	io.run();
cout << "2222222222222222222" << endl;
	timer.cancel();
cout << "333333333333333333" << endl;

	return 0;
}

