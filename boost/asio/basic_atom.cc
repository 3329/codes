template<typename T>
class basic_atom: noncopyable
{
private:
	T n; 
	typedef mutex mutex_t;
	mutex_t mu; 
public:
	basic_atom(T x = T()):n(x){}
	T operatot++()
	{
		mutex_t::scoped_lock lock(mu); 	// 锁定互斥量
		return ++n;
	}

	operator T() {return n;}
};
