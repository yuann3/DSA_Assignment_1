/*
 * Node.hpp
 * Written by : Yiyuan Li (C3434681)
 * Modified   : 01/06/2024
 */

// Default constructor for Node, initializes data to its default value and next and prev pointers to nullptr
template <typename T>
Node<T>::Node()
{
	// The constructor initializes the node with default values.
	// The data member of the node is initialized with the default value of the type T.

	// Initialize data to its default value
	data = T();

	// The next and previous pointers of the node are initialized to nullptr,
	// indicating that the node does not point to any other node in the list.

	// Initialize next pointer to nullptr
	next = nullptr;

	// Initialize previous pointer to nullptr
	prev = nullptr;
}

template <typename T>
Node<T>::Node(const T &new_data)
{
	// This is an overloaded constructor that initializes the node with a given value.
	// The data member of the node is initialized with the value passed as an argument.

	// Initialize data to new_data
	data = new_data;

	// The next and previous pointers of the node are initialized to nullptr,
	// indicating that the node does not point to any other node in the list.

	// Initialize next pointer to nullptr
	next = nullptr;

	// Initialize previous pointer to nullptr
	prev = nullptr;
}
template <typename T>
Node<T>::~Node()
{
	// Destructor doesn't need to do anything, as we don't have any dynamically allocated memory
}

// ---- Mutators --------

template <typename T>
// Function to set the data of the Node to new_data
void Node<T>::set_data(T &new_data)
{
	data = new_data;
}

template <typename T>
// Function to set the next pointer of the Node to new_next
void Node<T>::set_next(Node<T> *const new_next)
{
	next = new_next;
}

template <typename T>
// Function to set the prev pointer of the Node to new_prev
void Node<T>::set_prev(Node<T> *const new_prev)
{
	prev = new_prev;
}

// ---- Accessors --------

template <typename T>
// Function to get the next pointer of the Node
Node<T> *Node<T>::get_next()
{
	return next;
}

template <typename T>
// Function to get the prev pointer of the Node
Node<T> *Node<T>::get_prev()
{
	return prev;
}

template <typename T>
// Function to get the data of the Node
T &Node<T>::get_data()
{
	return data;
}

template <typename T>
// Function to get the next pointer of the Node, const version
const Node<T> *Node<T>::get_next() const
{
	return next;
}

template <typename T>
// Function to get the prev pointer of the Node, const version
const Node<T> *Node<T>::get_prev() const
{
	return prev;
}

template <typename T>
// Function to get the data of the Node, const version
const T &Node<T>::get_data() const
{
	return data;
}