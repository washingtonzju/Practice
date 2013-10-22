#include <iostream>
#include <mutex>
#include <string>
#include <chrono>
#include <thread>
#include <map>
#include <pthread.h>
using namespace std;

map<string, string> g_pages;
pthread_mutex_t g_pages_mutex = PTHREAD_MUTEX_INITIALIZER;

void *save_page(void *url)
{
    
    pthread_mutex_lock( &g_pages_mutex );
    
    g_pages[*((string *)url)] = "Beauty";
    cout << *((string *)url) << " " << g_pages[*((string *)url)] << endl;
    pthread_mutex_unlock( &g_pages_mutex );
}

int main()
{
    pthread_t ths[10];
    string url[10];
    for(int i=0;i<10;++i)
    {
        url[i] = "www.google.com/" + to_string(i);
        cout << " url " << url[i] << endl;
        pthread_create(&ths[i], NULL, save_page, &url[i]);
    }

    for(int i=0;i<10;++i)
    {
        pthread_join( ths[i], NULL);
    }
    return 0;
}
