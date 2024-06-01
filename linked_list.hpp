/*
* LinkedList.hpp
* Written by : SENG1120 Staff (c1234567)
* Modified   : 03/08/2023
*
* This class represents the template implementation for a LinkedList class.
* This file should be used in conjunction with Assignment 1 for SENG1120.
*/ 

template <typename T>
LinkedList<T>::LinkedList() 
{
	head->set_next(tail);
	tail->set_prev(head);
	current = head;
}

template <typename T>
LinkedList<T>::~LinkedList() 
{
	clear();
	delete head;
	delete tail;
}

template <typename T>
void LinkedList<T>::push_front(const T& data) 
{
	Node<T>* newNode = new Node<T>(data);
	newNode->set_next(head->get_next());
	newNode->set_prev(head);
	head->get_next()->set_prev(newNode);
	head->set_next(newNode);
	count++;
}

template <typename T>
void LinkedList<T>::push_back(const T& data) 
{
	Node<T>* newNode = new Node<T>(data);
	newNode->set_next(tail);
	newNode->set_prev(tail->get_prev());
	tail->get_prev()->set_next(newNode);
	tail->set_prev(newNode);
	count++;
}

template <typename T>
void LinkedList<T>::insert(const T& data) 
{
	if (current == tail) return;
	Node<T> newNode = new Node<T>(data);
	newNode->set_next(current->get_next());
	newNode->set_prev(current);
	current->get_next()->set_prev(newNode);
	current->set_next(newNode);
	count++;
}

template <typename T>
T LinkedList<T>::pop_front()
{
	if (empty()) throw empty_collection_exception();
	Node<T>* toDelete = head->get_next();	
	T data = toDelete->get_data();
	tail->set_prev(toDelete->get_prev());
	toDelete->get_next()->set_prev(head);
	delete toDelete;
	count--;
	return data;
}

template <typename T>
T LinkedList<T>::pop_back()
{
	if (empty()) throw empty_collection_exception();
	Node<T>* toDelete = tail->get_prev();
	T data = toDelete->get_data();
	tail->set_prev(toDelete->get_prev());
	toDelete->get_prev()->set_next(tail);
	delete toDelete;
	count--;
	return data;
}

template <typename T>
T LinkedList<T>::remove()
{
	if (empty() || current == head || current == tail) throw empty_collection_exception();
	Node<T>* toDelete = current;
	T data = toDelete->get_data();
	toDelete->get_prev()->set_next(toDelete->get_next());
	toDelete->get_next()->set_prev(toDelete->get_prev());
	current = toDelete->get_next();
	delete toDelete;
	count--;
	return data;
}

template <typename T>
void LinkedList<T>::clear()
{
	Node<T>* iter = head->get_next();
	while (iter != tail) {
		Node<T>* toDelete = iter;
		iter = iter->get_next();
		delete;
	}
	head->set_next(tail);
	tail->set_prev(head);
	count = 0;
}

template <typename T>
T& LinkedList<T>::front() const
{
	if (empty()) throw empty_collection_exception();
	return head->get_next()->get_data();
}

template <typename T>
T& LinkedList<T>::back() const
{
	if (empty()) throw empty_collection_exception();
	return tail->get_prev()->get_data();
}

template <typename T>
T& LinkedList<T>::get_current() const
{
	
}


template <typename T>
void LinkedList<T>::begin() 
{
    
}

template <typename T>
void LinkedList<T>::end() 
{
    
}

template <typename T>
void LinkedList<T>::forward() 
{

}

template <typename T>
void LinkedList<T>::backward() 
{

}

template <typename T>
int LinkedList<T>::size() const
{
	return 0;
}

template <typename T>
bool LinkedList<T>::empty() const
{
	return false;
}

template <typename T>
bool LinkedList<T>::search(const T& target)
{
	return false;
}