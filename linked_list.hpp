/*
 * LinkedList.hpp
 * Written by : Yiyuan Li
 * Modified   : 03/06/2024
 */

#include "empty_collection_exception.h"

/*
* Precondition:    None
* Postcondition:   A new LinkedList is created, with all variables initialised.
*/
template <typename T>
LinkedList<T>::LinkedList() : head(new Node<T>()), tail(new Node<T>()), count(0)
{
	head->set_next(tail);
	tail->set_prev(head);
	current = head;
}

/*
* Precondition:    None
* Postcondition:   The LinkedList is destroyed and all associated memory is freed.
*/
template <typename T>
LinkedList<T>::~LinkedList()
{
	clear();
	delete head;
	delete tail;
}

/*
* The supplied data is inserted at the front of the list.
* 
* Precondition:    The supplied data is valid.
* Postcondition:   The first data item is updated and current points to the new node.
*/
template <typename T>
void LinkedList<T>::push_front(const T &data)
{
	Node<T> *newNode = new Node<T>(data);
	newNode->set_next(head->get_next());
	newNode->set_prev(head);
	head->get_next()->set_prev(newNode);
	head->set_next(newNode);
	count++;
}

/*
* The supplied data is inserted at the end of the list.
* 
* Precondition:    The supplied data is valid.
* Postcondition:   The last data item is updated and current points to the new node.
*/
template <typename T>
void LinkedList<T>::push_back(const T &data)
{
	Node<T> *newNode = new Node<T>(data);
	newNode->set_next(tail);
	newNode->set_prev(tail->get_prev());
	tail->get_prev()->set_next(newNode);
	tail->set_prev(newNode);
	count++;
}

/*
* The supplied data is inserted before the current node.
* 
* Precondition:    Current points to the node after the insertion point.
* Postcondition:   A new node has been added and current points to the new node.
*/
template <typename T>
void LinkedList<T>::insert(const T &data)
{
	if (current == tail)
		return;
	Node<T> newNode = new Node<T>(data);
	newNode->set_next(current->get_next());
	newNode->set_prev(current);
	current->get_next()->set_prev(newNode);
	current->set_next(newNode);
	count++;
}

/*
* Remove the first data element from the list. An exception should be thrown if the list is empty.
* 
* Precondition:    The list is not empty.
* Postcondition:   The first data element has been removed, reducing the count of Nodes by 1. Current points to head.
*/
template <typename T>
T LinkedList<T>::pop_front()
{
	if (empty())
		throw empty_collection_exception();
	Node<T> *toDelete = head->get_next();
	T data = toDelete->get_data();
	tail->set_prev(toDelete->get_prev());
	toDelete->get_next()->set_prev(head);
	delete toDelete;
	count--;
	return data;
}

/*
* Remove the last data element from the list. An exception should be thrown if the list is empty.
* 
* Precondition:    The list is not empty.
* Postcondition:   The last data element has been removed, reducing the count of Nodes by 1. Current points to head.
*/
template <typename T>
T LinkedList<T>::pop_back()
{
	if (empty())
		throw empty_collection_exception();
	Node<T> *toDelete = tail->get_prev();
	T data = toDelete->get_data();
	tail->set_prev(toDelete->get_prev());
	toDelete->get_prev()->set_next(tail);
	delete toDelete;
	count--;
	return data;
}

/*
* Remove the item pointed to by current from the list. An exception should be thrown if the list is empty or 
* if current is pointing to a sentinel node.
* 
* Precondition:    The list is not empty and the current pointer is not pointing to a sentinel node.
* Postcondition:   The data element pointed to by current has been removed, reducing the count of Nodes by 1. Current points to head.
*/
template <typename T>
T LinkedList<T>::remove()
{
	if (empty() || current == head || current == tail)
		throw empty_collection_exception();
	Node<T> *toDelete = current;
	T data = toDelete->get_data();
	toDelete->get_prev()->set_next(toDelete->get_next());
	toDelete->get_next()->set_prev(toDelete->get_prev());
	current = toDelete->get_next();
	delete toDelete;
	count--;
	return data;
}

/*
* Clears all data elements from the list, leaving the sentinel nodes intact.
* 
* Precondition:    None
* Postcondition:   All data elements have been removed. Sentinels should not be removed. Count should be reset.
*/
template <typename T>
void LinkedList<T>::clear()
{
	Node<T> *iter = head->get_next();
	while (iter != tail)
	{
		Node<T> *toDelete = iter;
		iter = iter->get_next();
		delete toDelete;
	}
	head->set_next(tail);
	tail->set_prev(head);
	count = 0;
}

/*
* Return a reference to the first data element in the list - not the sentinel. An exception should be thrown if the list is empty.
* 
* Precondition:    The list is not empty.
* Postcondition:   A reference to the first data element is returned.
*/
template <typename T>
T &LinkedList<T>::front() const
{
	if (empty())
		throw empty_collection_exception();
	return head->get_next()->get_data();
}

/*
* Return a reference to the last data element in the list - not the sentinel. An exception should be thrown if the list is empty.
* 
* Precondition:    The list is not empty.
* Postcondition:   A reference to the last data element is returned.
*/
template <typename T>
T &LinkedList<T>::back() const
{
	if (empty())
		throw empty_collection_exception();
	return tail->get_prev()->get_data();
}

/*
* Return a reference to the data element pointed to by current. An exception should be thrown if the list is empty or current points to a sentinel.
* 
* Precondition:    The list is not empty and the current pointer is not pointing to a sentinel node.
* Postcondition:   A reference to the current data element is returned.
*/
template <typename T>
T &LinkedList<T>::get_current() const
{
	if (empty() || current == head || current == tail)
		throw empty_collection_exception();
	return current->get_data();
}

/*
* Set the current pointer to the node after head, even if this is tail.
* 
* Precondition:    None
* Postcondition:   The current pointer is set to the node after head.
*/
template <typename T>
void LinkedList<T>::begin()
{
	current = head->get_next();
}

/*
* Set the current pointer to the node before tail head, even if this is head.
* 
* Precondition:    None
* Postcondition:   The current pointer is set to the node before tail.
*/
template <typename T>
void LinkedList<T>::end()
{
	current = tail->get_prev();
}

 /*
* Move the current pointer forward, if valid. Otherwise, nothing happens.
* 
* Precondition:    None
* Postcondition:   The current pointer is set to the next node, if applicable.
*/
template <typename T>
void LinkedList<T>::forward()
{
	if (current != tail && current->get_next() != tail)
		current = current->get_next();
}

/*
* Move the current pointer backward, if valid. Otherwise, nothing happens.
* 
* Precondition:    None
* Postcondition:   The current pointer is set to the previous node, if applicable.
*/  
template <typename T>
void LinkedList<T>::backward()
{
	if (current != head->get_next())
		current = current->get_prev();
}

/*
* Return the count of the number of nodes in the list, excluding sentinels.
* 
* Precondition:    None
* Postcondition:   The number of (true) nodes is returned.
*/ 
template <typename T>
int LinkedList<T>::size() const
{
	return count;
}

/*
* Return true if the list is empty, false otherwise.
* 
* Precondition:    None
* Postcondition:   None
*/  
template <typename T>
bool LinkedList<T>::empty() const
{
	return count == 0;
}

/*
* Set the current pointer to the node containing the supplied data. Otherwise, nothing happens.
* 
* Precondition:    None
* Postcondition:   current points to the first node storing the target, and true is returned.
*/ 
template <typename T>
bool LinkedList<T>::search(const T &target)
{
	Node<T> *node = head->get_next();
	while (node != tail)
	{
		if (node->get_data() == target)
		{
			current = node;
			return true;
		}
		node = node->get_next();
	}

	return false;
}
