#ifndef LIST_NODE_H
#define LIST_NODE_H

template <typename T>
class List;

template <typename T>
class ListNode
{
	friend class List<T>;
	public:
		ListNode(T);
		T getData();
	private:
		T data;
		ListNode* next;
};

template <typename T>
ListNode<T>::ListNode(T dataIn)
{
	data = dataIn;
	next = 0;
}

template <typename T>
T ListNode<T>::getData(){
	return data;
}

#endif
