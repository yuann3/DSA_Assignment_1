#include "browser.h"

// this is a counstructor: it initializes the browser with a homepage and a history limit
Browser::Browser(const std::string& homepage, int history_limit)
    : homepage(homepage), history_limit(history_limit), history(new LinkedList<std::string>()), 
    bookmarks(new LinkedList<std::string>()) {
    visit(homepage); // start with the homepage in the history
}
Browser::~Browser()
{
    delete history;
    delete bookmarks;
}

const std::string& Browser::get_current_site()
{
    // if history is empty, return the homepage
    if (history->empty()) 
        return homepage;
    return history->back(); // otherwise, return the last site visited
}

// visit a new url
void Browser::visit(const std::string& url)
{   
    // If the url is the same as the last one, do noting
    if (!history->empty() && history->back() == url) 
        return;
    while (history->size() >= history_limit)
        history->pop_front();
    // add the url to the history
    history->push_back(url); 
}

// go back in the history
void Browser::back(int steps)
{
    // move the pointer forward steps times, but not beyond the front of the history
    while (steps-- > 0 && history->get_current() != history->front())
        history->backward();
}

// go forward in the history
void Browser::forward(int steps)
{
    // move the pointer backward steps times, but not beyond the back of the history
    while (steps-- > 0 && history->get_current() != history->back())
        history->forward();
}

// remove all instances of a url from the history
int Browser::remove(std::string url)
{
    int count = 0;
    while (history->search(url)) // while url is empty
    {
        // remove current node
        history->remove();
        count++;
    }
    return count;
}

// bookmark or unbookmark the current site
void Browser::bookmark_current()
{
    std::string currentSite = get_current_site();
    // if the current site is already bookmarked
    if (bookmarks->search(currentSite)){
        bookmarks->remove(); // remove it
        std::cout << currentSite << " removed from bookmarks." << std::endl;
    }
    else
    {
        bookmarks->push_back(currentSite); // otherwise, add it
        std::cout << "added " << currentSite << " to bookmarke." << std::endl;
    }
}

// clear all history, and back to homepage
void Browser::clear_history()
{
    history->clear();
    visit(homepage);
}

// printout all the bookmarks
void Browser::print_bookmarks()
{
    if (bookmarks->empty()) // if there are no bookmarks
    {
        std::cout << "No bookmarke in the list" << std::endl;
    }
    else
    {
        bookmarks->begin();
        std::cout << "Bookmark List:" << std::endl;
        while (bookmarks->get_current() != bookmarks->back())
        {
            std::cout << bookmarks->get_current() << std::endl;
            bookmarks->forward();
        }
        // print the last bookmark
        std::cout << bookmarks->get_current() << std::endl;
    }
    
}

// return the number of sites in the history
int Browser::count_history() const
{
    return history->size();
}

// return the number of bookmarks
int Browser::count_bookmarks() const
{
    return bookmarks->size();
}

// visit a bookmark at a given index
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
    visit(bookmarks->get_current()); // visit the bookmark at the given index   
}