class thread
{
public:
	// construct 
	thread();
	template <class F> explicit thread(F f);
	template <class F, class A1, class A2, ...>
		thread(F f, A1 a1, A2 a2, ...);

	// thread manager
	bool joinable() const;
	void join(); 
	bool timed_join(const system_time& wait_until);

	// 支持各种比较符
	// id get_id() const;
	// bool operator==(const thread& other) const;
};

int main()
{
	atom_int x; 

	// 使用临时thread对象启动线程
	thread(printing, ref(x), "Hello");	// 向函数传递多个参数
	thread(printing, ref(x), "boost");	// 使用ref库传递引用
	this_thread::slepp(posix_time::seconds(2)); // 等待2秒钟

}


joinable
join/timed_join 

t1.timed_join(posix_time::seconds(1));
t2.join();
thread t1(printing, ref(x), "hello");	// 启动线程
t1.detach();							// 与线程执行体分离, 但线程继续运行
thread t(to_interrupt, ref(x), "hello");
this_thread::slepp(posix_time::seconds(2));
t.interrupt();
t.join();
thread_group
add_thread
remove_thread
join_all, interrupt_all,size()const 

thread_group tg; 
tg.create_thread(bind(printing, ref(x), "C++"));
tg.create_thread(bind(printing, ref(x), "boost"));
tg.join_all();
typedef singleton_default<thread_group> thread_pool; 
thread_pool::instance().create_thread(...);
condition_variable
condition_variable_any
alss condition_variable_any
{
public:
	void notify_one();
	void notify_all();
};

interrupt();
