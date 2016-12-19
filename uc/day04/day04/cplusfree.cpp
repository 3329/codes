#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
class A
{	
public:
	A(){
		printf("A constructor!\n");
	}

	~A(){
		printf("A destructor!\n");
	}
	virtual void display()
	{
		assert(0);
	}
};
class B : public A
{

};
int main()
{
	//A *p=new A[3];
	//free(p);
	B *b=new B();
	b->display();
	return 0;
}

