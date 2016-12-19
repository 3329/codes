// noncopyable
#include <boost/noncopyable.hpp>
#include <boost/utility.hpp>

class do_not_copy: boost::noncopyable
{
	...
};

// typeof 
#include <boost/typeof/typeof.hpp>
std::map<std::string, std::string>::iterator pos = ...;

#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/shared_ptr.hpp>

boost::shared_ptr<boost::gregorian::date> pd;
#include <boost/shared_ptr.hpp>
boost::shared_ptr<boost::gregorian::date> pd; 
typof(...) pos = ...;
auto pos = ;
auto f = _1 > 15 && _2 < 20;
using namespace boost::asio;

#include <boost/typeof.hpp>
//BOOST_TYPEOF BOOST_AUTO(typeof auto)
#include <boost/typeof/typeof.hpp>
vector<string> func()
{
	vector<string> v(10);
	return v;
}

int main()
{
	BOOST_TYPEOF(2.0 * 3) x = 2.0 * 3 ;
	BOOST_AUTO(y, 2+3);

	BOOST_AUTO(&am new double[20]); // 推导类型为double*的引用
	BOOST_AUTO(p, make_pair(1, "string"));
	BOOST_AUTO(v, func());			// 推导类型为vector<string>
}

// array, dynamic_bitset, unordered, bimap, circlular_buffer
// tuple, any, variant, multi_array, property_tree;
// array, io_state_savers
// io_state_savers
//
// thread library need date_time library to suopport
#define BOOST_DATE_TIME_SOURCE 
#define BOOST_THREAD_NO_LIB
#include <boost/thread.hpp>
using namespace boost;

this_thread::sleep(posix_time::seconds(2)); 	// sleep 2 seconds
cout << "sleep 2 seconds" << endl;

typedef boost::posix_time::ptime system_time;
get_system_time(), microsec_clock();

thread mutex
try_mutex
timed_mutex
recursive_mutex
recursive_try_mutex

class mutux: boost::noncopyable
{
public:
	void lock(); 
	bool try_lock();
	void unlock();
};
