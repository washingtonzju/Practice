// The C++ 11 version test with Ubuntu + G++
#include <iostream>
#include <mutex>
#include <string>
#include <chrono>
#include <thread>
#include <map>
using namespace std;

std::map<string, string> g_pages;
std::mutex g_pages_mutex;

void save_page(const string &url)
{
    std::this_thread::sleep_for(std::chrono::seconds(2));
    string result = "fake content";

    g_pages_mutex.lock();
    g_pages[url] = result;
    g_pages_mutex.unlock();
}

int main()
{
    thread *tds[10];
    for(int i=0;i<10;++i)
    {
        tds[i] = new thread(save_page, "http://www.google.com/" + string(i));
    }

    for(int i=0;i<10;++i)
    {
        tds[i]->join();
    }
        
    return 0;
}
