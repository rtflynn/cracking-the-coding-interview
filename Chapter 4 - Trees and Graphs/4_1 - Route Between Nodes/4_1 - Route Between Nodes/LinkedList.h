#ifndef LINKEDLIST_H
#define LINKEDLIST_H

template <class T>
struct Node {
	T m_data;
	Node<T> * m_next;
	Node<T> * m_prev;

	Node<T>(T data) { m_data = data; m_prev = nullptr; m_next = nullptr; }
	~Node<T>() {
		m_prev = nullptr;
		m_next = nullptr;
	}
};


template <class T>
class LinkedList {
private:
	Node<T> * m_head;
	Node<T> * m_tail;

public:
	LinkedList<T>() { m_head = nullptr; m_tail = nullptr; }
	Node<T> * getHead() { return m_head; }
	Node<T> * getTail() { return m_tail; }

	void pushHead(T newData);
	void pushTail(T newData);
	void deleteHead();
	void deleteTail();
	T getItem(int index);
};



template<class T>
inline void LinkedList<T>::pushHead(T newData) {
	Node<T> * temp = new Node<T>(newData);
	if (m_head == nullptr) {
		m_head = temp;
		m_tail = temp;
		temp = nullptr;
	}
	else {
		temp->m_next = m_head;
		m_head->m_prev = temp;
		m_head = temp;
		temp = nullptr;
	}
}

template<class T>
inline void LinkedList<T>::pushTail(T newData) {
	Node<T> * temp = new Node<T>(newData);
	if (m_head == nullptr) {
		m_head = temp;
		m_tail = temp;
		temp = nullptr;
	}
	else {
		temp->m_prev = m_tail;
		m_tail->m_next = temp;
		m_tail = temp;
		temp = nullptr;
	}
}

template<class T>
inline void LinkedList<T>::deleteHead() {
	if (m_head == nullptr) { return; }
	else if (m_head == m_tail) {
		delete m_head;
		m_head = nullptr;
		m_tail = nullptr;
	}
	else {
		Node<T> * temp = m_head->m_next;
		temp->m_prev = nullptr;
		delete m_head;
		m_head = temp;
		temp = nullptr;
	}
}

template<class T>
inline void LinkedList<T>::deleteTail() {
	if (m_head == nullptr) { return; }
	else if (m_head == m_tail) {
		delete m_head;
		m_head = nullptr;
		m_tail = nullptr;
	}
	else {
		Node<T> * temp = m_tail->m_prev;
		temp->m_next = nullptr;
		delete m_tail;
		m_tail = temp;
		temp = nullptr;
	}
}



template<class T>
inline T LinkedList<T>::getItem(int index)
{
	if ((index < 0) or (m_head == nullptr))
		throw - 1;
	Node<T> * current = m_head;
	int counter = 0;
	while (counter < index)
	{
		counter++;
		current = current->m_next;
		if (current == nullptr)
			throw - 2;		// Maybe just return the last item in the list if we go out of bounds
	}

	return current->m_data;
}




#endif