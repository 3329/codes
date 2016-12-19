#include <boost/dynamic_bitset.hpp>
using namespace boost;

dynamic_bitset& set(); 
dynamic_bitset& reset(); 
dynamic_bitset& flip();


bool test(size_type n) const;
bool any() const;
bool none() const;
dynamic_bitset operator~()const;
size_type count() const;

bool operator[](size_type pos) const;

size_type size() const;
size_type num_blocks() const;
size_type max_size() const;
bool empty() const;

bool is_subset_of(const dynamic_bitset& a) const;
bool is_proper_subset_of(const dynamic_bitset& a) const;

size_type find_first() const;
size_type fing_next(size_type pos) const;


dynamic_bitset<> db1; 
dynamic_bitset<> db2(10);
dynamic_bitset<> db3(String("jslll"));
