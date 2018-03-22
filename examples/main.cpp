/*
 * Carmelo Porcelli
 */
#include <cstdlib>
#include <redis3m/redis3m.hpp>
#include <iostream>
#include <thread>

using namespace redis3m;

void subscriber()
{
    connection::ptr_t conn = connection::create();
    conn->run(command("SUBSCRIBE") << "topic");
    while(true)
    {
        reply r = conn->get_reply();
        std::cout << "Received: " << r.elements().at(2).str() << std::endl;
    }
}


void publisher()
{
    connection::ptr_t conn = connection::create();
    std::string body = "Undefined";
    reply r = conn->run(command("PUBLISH") << "topic" << body);
}


int main(int argc, char **argv)
{
    std::thread th = std::thread(subscriber);
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    publisher();
    
    th.join();
    return 1;
}

