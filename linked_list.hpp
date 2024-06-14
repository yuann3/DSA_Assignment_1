/*
 * LinkedList.hpp
 * Written by : Yiyuan Li
 * Modified   : 03/06/2024
 */

#include "empty_collection_exception.h"

// Constructor for LinkedList
// Precondition:   None
// Postcondition:  A new LinkedList is created, with all variables initialised.
template <typename T>
LinkedList<T>::LinkedList() : head(new Node<T>()), tail(new Node<T>()), count(0)
{
	head->set_next(tail); // Set head's next to tail
	tail->set_prev(head); // Set tail's previous to head
	current = head;				// Set current to head
}

// Destructor for LinkedList
// Precondition:   None
// Postcondition:  The LinkedList is destroyed and all associated memory is freed.
template <typename T>
LinkedList<T>::~LinkedList()
{
	clear();		 // Clear all nodes in the list
	delete head; // Delete head node
	delete tail; // Delete tail node
}

// Insert data at the front of the list
// Precondition:   The supplied data is valid.
// Postcondition:  The first data item is updated and current points to the new node.
template <typename T>
void LinkedList<T>::push_front(const T &data)
{
	Node<T> *newNode = new Node<T>(data); // Create a new node with the provided data
	newNode->set_next(head->get_next());	// Set new node's next to head's next
	newNode->set_prev(head);							// Set new node's previous to head
	head->get_next()->set_prev(newNode);	// Set head's next node's previous to new node
	head->set_next(newNode);							// Set head's next to new node
	count++;															// Increment node count
}

// Insert data at the end of the list
// Precondition:   The supplied data is valid.
// Postcondition:  The last data item is updated and current points to the new node.
template <typename T>
void LinkedList<T>::push_back(const T &data)
{
	Node<T> *newNode = new Node<T>(data); // Create a new node with the provided data
	newNode->set_next(tail);							// Set new node's next to tail
	newNode->set_prev(tail->get_prev());	// Set new node's previous to tail's previous
	tail->get_prev()->set_next(newNode);	// Set tail's previous node's next to new node
	tail->set_prev(newNode);							// Set tail's previous to new node
	count++;															// Increment node count
}

// Insert data before the current node
// Precondition:   Current points to the node after the insertion point.
// Postcondition:  A new node has been added and current points to the new node.
template <typename T>
void LinkedList<T>::insert(const T &data)
{
	if (current == tail) // If current is tail, do nothing
		return;
	Node<T> *newNode = new Node<T>(data);		// Create a new node with the provided data
	newNode->set_next(current->get_next()); // Set new node's next to current's next
	newNode->set_prev(current);							// Set new node's previous to current
	current->get_next()->set_prev(newNode); // Set current's next node's previous to new node
	current->set_next(newNode);							// Set current's next to new node
	count++;																// Increment node count
}

// Remove the first data element from the list
// Precondition:   The list is not empty.
// Postcondition:  The first data element has been removed, reducing the count of Nodes by 1. Current points to head.
template <typename T>
T LinkedList<T>::pop_front()
{
	if (empty()) // If list is empty, throw exception
		throw empty_collection_exception();
	Node<T> *toDelete = head->get_next(); // Node to be deleted is head's next
	T data = toDelete->get_data();				// Retrieve data from node to be deleted
	tail->set_prev(toDelete->get_prev()); // Set tail's previous to node to be deleted's previous
	toDelete->get_next()->set_prev(head); // Set node to be deleted's next node's previous to head
	delete toDelete;											// Delete node
	count--;															// Decrement node count
	return data;													// Return data from deleted node
}

// Remove the last data element from the list
// Precondition:   The list is not empty.
// Postcondition:  The last data element has been removed, reducing the count of Nodes by 1. Current points to head.
template <typename T>
T LinkedList<T>::pop_back()
{
	if (empty()) // If list is empty, throw exception
		throw empty_collection_exception();
	Node<T> *toDelete = tail->get_prev(); // Node to be deleted is tail's previous
	T data = toDelete->get_data();				// Retrieve data from node to be deleted
	tail->set_prev(toDelete->get_prev()); // Set tail's previous to node to be deleted's previous
	toDelete->get_prev()->set_next(tail); // Set node to be deleted's previous node's next to tail
	delete toDelete;											// Delete node
	count--;															// Decrement node count
	return data;													// Return data from deleted node
}

// Remove the item pointed to by current from the list
// Precondition:   The list is not empty and the current pointer is not pointing to a sentinel node.
// Postcondition:  The data element pointed to by current has been removed, reducing the count of Nodes by 1. Current points to head.
template <typename T>
T LinkedList<T>::remove()
{
	if (empty() || current == head || current == tail) // If list is empty or current is a sentinel node, throw exception
		throw empty_collection_exception();
	Node<T> *toDelete = current;													// Node to be deleted is current
	T data = toDelete->get_data();												// Retrieve data from node to be deleted
	toDelete->get_prev()->set_next(toDelete->get_next()); // Set node to be deleted's previous node's next to node to be deleted's next
	toDelete->get_next()->set_prev(toDelete->get_prev()); // Set node to be deleted's next node's previous to node to be deleted's previous
	current = toDelete->get_next();												// Move current to the next node
	delete toDelete;																			// Delete node
	count--;																							// Decrement node count
	return data;																					// Return data from deleted node
}

// Clear all data elements from the list, leaving the sentinel nodes intact
// Precondition:   None
// Postcondition:  All data elements have been removed. Sentinels should not be removed. Count should be reset.
template <typename T>
void LinkedList<T>::clear()
{
	Node<T> *iter = head->get_next(); // Start iterating from head's next
	while (iter != tail)
	{
		Node<T> *toDelete = iter; // Node to be deleted is current node
		iter = iter->get_next();	// Move to the next node
		delete toDelete;					// Delete current node
	}
	head->set_next(tail); // Set head's next to tail
	tail->set_prev(head); // Set tail's previous to head
	count = 0;						// Reset node count
}

// Return a reference to the first data element in the list - not the sentinel
// Precondition:   The list is not empty.
// Postcondition:  A reference to the first data element is returned.
template <typename T>
T &LinkedList<T>::front() const
{
	if (empty()) // If list is empty, throw exception
		throw empty_collection_exception();
	return head->get_next()->get_data(); // Return data of head's next node
}

// Return a reference to the last data element in the list - not the sentinel
// Precondition:   The list is not empty.
// Postcondition:  A reference to the last data element is returned.
template <typename T>
T &LinkedList<T>::back() const
{
	if (empty()) // If list is empty, throw exception
		throw empty_collection_exception();
	return tail->get_prev()->get_data(); // Return data of tail's previous node
}

// Return a reference to the data element pointed to by current
// Precondition:   The list is not empty and the current pointer is not pointing to a sentinel node.
// Postcondition:  A reference to the current data element is returned.
template <typename T>
T &LinkedList<T>::get_current() const
{
	if (empty() || current == head || current == tail) // If list is empty or current is a sentinel node, throw exception
		throw empty_collection_exception();
	return current->get_data(); // Return data of current node
}

// Set the current pointer to the node after head, even if this is tail
// Precondition:   None
// Postcondition:  The current pointer is set to the node after head.
template <typename T>
void LinkedList<T>::begin()
{
	current = head->get_next(); // Set current to head's next node
}

// Set the current pointer to the node before tail head, even if this is head
// Precondition:   None
// Postcondition:  The current pointer is set to the node before tail.
template <typename T>
void LinkedList<T>::end()
{
	current = tail->get_prev(); // Set current to tail's previous node
}

// Move the current pointer forward, if valid. Otherwise, nothing happens
// Precondition:   None
// Postcondition:  The current pointer is set to the next node, if applicable.
template <typename T>
void LinkedList<T>::forward()
{
	if (current != tail && current->get_next() != tail) // If current is not tail and current's next is not tail
		current = current->get_next();										// Move current to the next node
}

// Move the current pointer backward, if valid. Otherwise, nothing happens
// Precondition:   None
// Postcondition:  The current pointer is set to the previous node, if applicable.
template <typename T>
void LinkedList<T>::backward()
{
	if (current != head->get_next() && current->get_prev() != head) // If current is not head's next node
		current = current->get_prev(); // Move current to the previous node
}

// Return the count of the number of nodes in the list, excluding sentinels
// Precondition:   None
// Postcondition:  The number of (true) nodes is returned.
template <typename T>
int LinkedList<T>::size() const
{
	return count; // Return node count
}

// Return true if the list is empty, false otherwise
// Precondition:   None
// Postcondition:  None
template <typename T>
bool LinkedList<T>::empty() const
{
	return count == 0; // Return true if count is 0, otherwise false
}

// Set the current pointer to the node containing the supplied data. Otherwise, nothing happens
// Precondition:   None
// Postcondition:  current points to the first node storing the target, and true is returned.
template <typename T>
bool LinkedList<T>::search(const T &target)
{
	Node<T> *node = head->get_next(); // Start searching from head's next node
	while (node != tail)
	{
		if (node->get_data() == target) // If node's data matches target
		{
			current = node; // Set current to the found node
			return true;		// Return true
		}
		node = node->get_next(); // Move to the next node
	}
	return false; // Return false if target not found
}