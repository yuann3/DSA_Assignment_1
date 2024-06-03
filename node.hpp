/*
 * Node.hpp
 * Written by : Yiyuan Li (C3434681)
 * Modified   : 01/06/2024
 */

template <typename T>
Node<T>::Node() : data(), next(nullptr), prev(nullptr) {}

template <typename T>
Node<T>::Node(const T &new_data) : data(new_data), next(nullptr), prev(nullptr) {}

template <typename T>
Node<T>::~Node() {}

// ---- Mutators --------
template <typename T>
void Node<T>::set_data(T &new_data)
{
	data = new_data;
}

template <typename T>
void Node<T>::set_next(Node<T> *const new_next)
{
	next = new_next;
}

template <typename T>
void Node<T>::set_prev(Node<T> *const new_prev)
{
	prev = new_prev;
}

// ---- Accessors --------
template <typename T>
Node<T> *Node<T>::get_next()
{
	return next;
}

template <typename T>
Node<T> *Node<T>::get_prev()
{
	return prev;
}

template <typename T>
T &Node<T>::get_data()
{
	return data;
}

template <typename T>
const Node<T> *Node<T>::get_next() const
{
	return next;
}

template <typename T>
const Node<T> *Node<T>::get_prev() const
{
	return prev;
}

template <typename T>
const T &Node<T>::get_data() const
{
	return data;
}