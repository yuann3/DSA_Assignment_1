/*
 * LinkedList.hpp
 * Written by : Yiyuan Li
 * Modified   : 03/06/2024
 */

#include "browser.h"

// Constructor for Browser
// Initializes the browser with a homepage and a history limit
Browser::Browser(const std::string &homepage, int history_limit)
		: history(new LinkedList<std::string>()),		// Create a new LinkedList for history
			bookmarks(new LinkedList<std::string>()), // Create a new LinkedList for bookmarks
			history_limit(history_limit),							// Set history limit
			homepage(homepage)												// Set homepage
{
	visit(homepage); // Start with the homepage in the history
}

// Destructor for Browser
// Deletes the history and bookmarks linked lists
Browser::~Browser()
{
	delete history;		// Delete history list
	delete bookmarks; // Delete bookmarks list
}

// Get the current site being visited
const std::string &Browser::get_current_site()
{
	// If history is empty, return the homepage
	if (history->empty())
		return homepage;
	else
		return history->back(); // Return the current site from the history
}

// Visit a new URL and add it to the history
void Browser::visit(const std::string &url)
{
	// If history is empty or the current URL is not the same as the new URL
	if (history->empty() || history->get_current() != url)
	{
		// Maintain history limit by removing the oldest entry if exceeded
		if (history->size() >= history_limit)
			history->pop_front(); // Remove the oldest URL

		history->push_back(url); // Add new URL to history
		history->end();					 // Set current to the new last element
	}
}

// Go back in the history by a number of steps
void Browser::back(int steps)
{
	// If no steps to go back or the history is empty, return immediately
	if (steps <= 0 || history->empty())
		return;

	for (int i = 0; i < steps; i++)
	{
		// Stop if we reach the front of the list
		if (history->get_current() == history->front())
			break;
		history->backward(); // Move current backward in the list
	}
}

// Go forward in the history by a number of steps
void Browser::forward(int steps)
{
	// If no steps to go forward or the history is empty, return immediately
	if (steps <= 0 || history->empty())
		return;

	for (int i = 0; i < steps; i++)
	{
		// Stop if we reach the back of the list
		if (history->get_current() == history->back())
			break;
		history->forward(); // Move current forward in the list
	}
}

// Remove all instances of a URL from the history
int Browser::remove(std::string url)
{
	int count = 0;
	// While the URL is found in history
	while (history->search(url))
	{
		// Remove current node
		history->remove();
		count++; // Increment count of removed URLs
	}
	return count; // Return the number of removed URLs
}

// Bookmark or unbookmark the current site
void Browser::bookmark_current()
{
	std::string currentSite = get_current_site(); // Get the current site URL
	// Search for the current site in the bookmarks to see if it's already bookmarked
	if (bookmarks->search(currentSite))
	{
		bookmarks->remove(); // Remove from bookmarks if already bookmarked
		std::cout << "Removed " << currentSite << " from bookmarks." << std::endl;
	}
	else
	{
		bookmarks->push_back(currentSite); // Add to bookmarks if not already bookmarked
		std::cout << "Added " << currentSite << " to bookmarks." << std::endl;
	}
}

// Clear all history and return to the homepage
void Browser::clear_history()
{
	history->clear(); // Clear the history list
	visit(homepage);	// Visit the homepage
}

// Print out all the bookmarks
void Browser::print_bookmarks()
{
	// If the bookmarks list is empty
	if (bookmarks->empty())
	{
		std::cout << "Bookmark list is empty." << std::endl;
	}
	else
	{
		bookmarks->begin(); // Start at the first bookmark
		std::cout << "Bookmark List:" << std::endl;
		while (true)
		{
			std::cout << bookmarks->get_current() << std::endl; // Print the current bookmark
			bookmarks->forward();																// Move to the next bookmark
			if (bookmarks->get_current() == bookmarks->back())
			{ // Check if we've reached the end
				break;
			}
		}
	}
}

// Return the number of sites in the history
int Browser::count_history() const
{
	return history->size(); // Return the size of the history list
}

// Return the number of bookmarks
int Browser::count_bookmarks() const
{
	return bookmarks->size(); // Return the size of the bookmarks list
}

// Visit a bookmark at a given index
void Browser::visit_bookmark(int index)
{
	bookmarks->begin(); // Start at the first bookmark
	for (int i = 0; i < index; i++)
	{
		// If the index is out of bounds, print an error and return
		if (bookmarks->get_current() == bookmarks->back())
		{
			std::cout << "Invalid index." << std::endl;
			return;
		}
		bookmarks->forward(); // Move to the next bookmark
	}
	visit(bookmarks->get_current()); // Visit the bookmark at the given index
}
