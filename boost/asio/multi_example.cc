#include <iostream>
#include <boost/asio.hpp>
#include <boost/thread/thread.hpp>
#include <boost/bind.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/asio/high_resolution_timer.hpp>
#include <chrono>

class printer
{
public:
	printer(boost::asio::io_service &io)
		:	strand_(io),
			//timer1_(io, boost::posix_time::seconds(1)),
			//timer2_(io, boost::posix_time::seconds(1000)), 
			timer1_(io, chrono::seconds(1)),
			timer2_(io, chrono::seconds(1000)), 
			count_(0)
	{
		timer1_.async_wait(strand_.wrap(boost::bind(&printer::print1, this)));
		timer2_.async_wait(strand_.wrap(boost::bind(&printer::print2, this, _1)));
	}

	~printer()
	{
		std::cout << "Final count is " << count_ << std::endl;
	}

	void print1()
	{
		if (count_ < 10)
		{
			std::cout << "Timer1: " << count_ << std::endl;
			std::cout << "Timer2_ cancel: " << count_ << std::endl;
			timer2_.cancel();
			++count_;
			//timer1_.expires_at(timer1_.expires_at() + boost::posix_time::seconds(1));
			timer1_.expires_at(timer1_.expires_at() + chrono::seconds(1));
			timer1_.async_wait(strand_.wrap(boost::bind(&printer::print1, this)));
		}
	}

	void print2(const boost::system::error_code e)
	{
		if (e) 
		{
			std::cout << "55555555555555555" << e << std::endl;
		}
		if (count_ < 10)
		{
			std::cout << "Timer2: " << count_ << std::endl;
			++count_;

			//timer2_.expires_at(timer2_.expires_at() + boost::posix_time::seconds(1));
			timer2_.expires_at(timer2_.expires_at() + chrono::seconds(1));
			timer2_.async_wait(strand_.wrap(boost::bind(&printer::print2, this, _1)));
		}
	}

private:
	boost::asio::io_service::strand 		strand_;
	//boost::asio::deadline_timer				timer1_;
	//boost::asio::deadline_timer				timer2_;
	boost::asio::high_resolution_timer				timer1_;
	boost::asio::high_resolution_timer				timer2_;
	int 									count_;
};


int main()
{
	boost::asio::io_service io; 
	printer p(io);
	//boost::thread t(boost::bind(&boost::asio::io_service::run, &io));
	//boost::thread t1(boost::bind(&boost::asio::io_service::run, &io));
	//boost::thread t2(boost::bind(&boost::asio::io_service::run, &io));
	io.run();
	//t.join();
	//t1.join();
	//t2.join();

	return 0;
}
