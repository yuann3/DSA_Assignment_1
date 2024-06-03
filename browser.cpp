/*
 * LinkedList.hpp
 * Written by : Yiyuan Li
 * Modified   : 03/06/2024
 */

#include "browser.h"

// This is a constructor: it initializes the browser with a homepage and a history limit
Browser::Browser(const std::string &homepage, int history_limit)
		: history(new LinkedList<std::string>()),
			bookmarks(new LinkedList<std::string>()),
			history_limit(history_limit),
			homepage(homepage)
{
	visit(homepage); // start with the homepage in the history
}

Browser::~Browser()
{
	delete history;
	delete bookmarks;
}

const std::string &Browser::get_current_site()
{
	// If history is empty, return the homepage
	if (history->empty())
		return homepage;
	else
		return history->get_current(); // Return the current site
}

// Visit a new URL
void Browser::visit(const std::string &url)
{
	if (history->empty() || history->get_current() != url)
	{
		if (history->size() >= history_limit)
			history->pop_front();	 // Maintain history limit by removing the oldest entry if exceeded.
		history->push_back(url); // Add new URL to history.
		history->end();					 // Set current to the new last element
	}
}

// Command < : go back in the history
void Browser::back(int steps)
{
	if (steps <= 0 || history->empty())
		return; // If no steps to go back or the history is empty, return immediately.

	for (int i = 0; i < steps; i++)
	{
		if (history->get_current() == history->front())
			break;						 // Stop if we reach the front of the list
		history->backward(); // Move current backward in the list
	}
}

// Go forward in the history
void Browser::forward(int steps)
{
	if (steps <= 0 || history->empty())
		return; // If no steps to go forward or the history is empty, return immediately.

	for (int i = 0; i < steps; i++)
	{
		if (history->get_current() == history->back())
			break;						// Stop if we reach the back of the list
		history->forward(); // Move current forward in the list
	}
}

// Remove all instances of a URL from the history
int Browser::remove(std::string url)
{
	int count = 0;
	while (history->search(url))
	{
		// Remove current node
		history->remove();
		count++;
	}
	return count;
}

// Bookmark or unbookmark the current site
void Browser::bookmark_current()
{
	std::string currentSite = get_current_site();
	// Search for the current site in the bookmarks to see if it's already bookmarked
	if (bookmarks->search(currentSite))
	{
		std::cout << currentSite << " is already bookmarked. No action taken." << std::endl;
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
	history->clear();
	visit(homepage);
}

// Print out all the bookmarks
void Browser::print_bookmarks()
{
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
			std::cout << bookmarks->get_current() << std::endl;
			bookmarks->forward();
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
	return history->size();
}

// Return the number of bookmarks
int Browser::count_bookmarks() const
{
	return bookmarks->size();
}

// Visit a bookmark at a given index
void Browser::visit_bookmark(int index)
{
	bookmarks->begin();
	for (int i = 0; i < index; i++)
	{
		if (bookmarks->get_current() == bookmarks->back())
		{
			std::cout << "Invalid index." << std::endl;
			return;
		}
		bookmarks->forward();
	}
	visit(bookmarks->get_current()); // Visit the bookmark at the given index
}
