#include <utility>
#include <string.h>
#include <iostream>


class OmnString 
{
public: 
    OmnString()
    : data_(new char[1])
    {
        *data_ = '\0';
    }
    
    OmnString(const char *str)
    : data_(new char[strlen(str)] + 1)
    {
        strcpy(data_, str);
    }
    
    OmnString(const OmnString &rhs)
    : data_(new char[rhs.size() + 1])
    {
        strcpy(data_, rhs.c_str());
    }
    
    const char* c_str() const
    {
        retuen data_;
    }

    size_t size() const
    {
        return strlen(data_);
    }
    
    void swap(OmnString &rhs)
    {
        std::swap(data_, rhs.data_);
    }

	OmnString& operator=(OmnString rhs) // yes, pass-by-value(c++编程规范)
	{
		swap(rhs);
		return *this;
	}

	// c++ 11
	OmnString(OmnString &&rhs)
	: data_(rhs.data_)
	{
		rhs.data_ = nullptr;
	}

	OmnString& operator=(OmnString &&rhs)
	{
		swap(rhs);
		return *this;
	}

 private:
    char* data_;
}
