RALL(Resource Acquisition Is Initialization):资源获取即初始化
new/delete以及指针的不恰当运用是C++中造成资源获取/释放问题的根源, 能否正确而明智地运用delete是区分C++新手与熟手的关键所在. 

smart pointer(boost 6种)
scoped_ptr, scoped_array, shared_ptr, shared_array, weak_ptr, intrusive_ptr

#include <boost/smart_ptr.hpp>
using namespace boost;
scoped_ptr<string> sp(new string("text"));
cout << *sp << endl;
cout << sp->size() << endl;

scoped_ptr不允许拷贝, 赋值, 只能在scoped_ptr被声明的作用域内使用, 除了*和->外scoped_ptr也没有定义其他的操作符. 与普通指针相比只有很小的接口, 因此使指针的使用更加安全, 更容易使用同时更不容易被使用.


scoped_ptr 也具有auto_ptr同样的缺陷-----(不能用作容器的元素), 但原因不同:
auto_ptr是因为它的转移语义, 而scoped_ptr则是因为不支持拷贝和赋值, 不符合容器对元素类型的要求.

scoped_array 
scoped_ptr
template<class T> class scoped_array	// noncopyable
{
public: 
	explicit scoped_array(T *p = 0);
	~scoped_array();

	void reset(T *p = 0);
	T & operator[](std::ptrdiff_t i) const;
	T * get() const;

	operator unspecified-bool-type() const;
	void swap(scoped_array &b);
};

#include <boost/make_shared.hpp>
#include <boost/shared_ptr.hpp>
using namespace boost::make_shared;
using namespace boost::shared_ptr;

int main()
{
	shared_ptr<string> sp = make_shared<string>("make_shared");
	shared_ptr<vector<int> > spv = make_shared<vector<int> > (10, 2);
}

make_shared, allocate_shared
allocate_shared
标准容器不能容纳auto_ptr, 只是C++标准特别规定的


///////////////////////////////////
shared_ptr<void *>
static_pointer_cast<T>
///////////////////////////////////


void any_func(void *p)
{
	cout << "some operate" << endl;
}

int main()
{
	shared_ptr<void> p((void*)0, any_func);
}
weak_ptr
use_count(); expired(), intrusive_ptr, memory pool

内存池预先分配了一块大的内存空间, 然后可以在其中使用某种算法实现高效快速的制定制内存分配
boost.pool
pool, object_pool, singleton_pool, pool_alloc
#include <boost/pool/pool.hpp>
using namespace boost;

template <typename UserAllocator = ...>
class pool 
{
public:
	explicit pool(size_type requested_size);
	~pool();

	size_type get_requested_size() const;
	void * malloc(); 
	void * ordered_malloc();
	void * ordered_malloc(size_type n);
};

int main()
{
	pool<> pl(sizeof(int));
	int *p = (int *)pl.malloc();
	assert_r(pl.is_from(p));

	pl.free(p);
	for (int i = 0; i < 100; i++)
}


