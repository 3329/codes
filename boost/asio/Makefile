all: timer_sync timer_async

timer_sync:
	g++ -o timer_sync timer_sync.cpp -lboost_system -lboost_regex -lssl -lboost_date_time

timer_async:
	g++ -o timer_async timer_async.cpp timer_sync.cpp -lboost_system -lboost_regex -lssl -lboost_date_time -lboost_error
