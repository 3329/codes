////////////////////////////////////////////////////////////////
//
//	FileName 	:	singleList.h
//	Version		:	0.10
//	Author		:	Young
//	Date		:	2013-05-14 13:53
//	Comment		:	
//
////////////////////////////////////////////////////////////////

#ifndef __SINGLE_LIST_H__
#define __SINGLE_LIST_H__

template<typename T>
class CNode
{
public:
	T data;
	CNode<T> *next;
	CNode() : data(T()), next(NULL) {}
	CNode(const T &initdata, CNode<T> *p) : data(initdata), next(p) {}
};

template<typename T>
class CSList
{
protected:
	int m_nCount;
	CNode<T> *m_pNodeHead;

public:
	CSList();
	CSList(const T &initdata);
	~CSList();

public:
	int 	IsEmpty() const;
	int	 	GetCount() const;
	int 	InsertBefore(const int pos, const T data);
	int 	AddHead(const T data);
	int 	AddTail(const T data);
	void 	RemoveAt(const int pos);
	void	RemoveHead();

};





#endif	// __SINGLE__LIST_H__
