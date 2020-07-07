//
//  Task client in C++
//  Connects PUSH socket to tcp://localhost:5558
//  Sends messages to server via that socket
//
//#include "zhelpers.hpp"
#include <zmq.hpp>
#include <time.h>
#include <sys/time.h>
#include <iostream>
#include <sstream>
#include <string>
#include <chrono>
#include <thread>

int main (int argc, char *argv[])
{
    int i = 0, num = 0;
    zmq::context_t context(1);

    //  Socket to send messages to
    zmq::socket_t sender(context, ZMQ_PUSH);
    sender.connect("tcp://localhost:5558");

    if(argc>1) {
        try {
            std::stringstream(std::string(argv[1])) >> num;
            //std::stringstream ss(std::string(argv[1])); ss.exceptions(std::ios::failbit); ss >> num;
            std::cout << "got " << argv[1] << " num:" << num << std::endl;
            num = num % 10;
        }
        catch (std::ios_base::failure &fail) {
            std::cout << std::fixed << num;
        }
        catch(std::exception &e)
        {
            std::cout << e.what();
        }

    }

    zmq::message_t message(20);
    memset(message.data(),0,20);
    std::string client_msg = "C" + std::to_string(num) + ": Hello";
    memcpy(message.data(), client_msg.c_str(), 10);
    memcpy(static_cast<void*>(static_cast<char*>(message.data())+10), std::to_string(i).c_str(),std::to_string(i).size());

    //  Process tasks forever
    while (i++ < 10000) {
        int workload;           //  Workload in msecs

        std::istringstream iss(std::string("10"));
        iss >> workload;

        std::cout << "sleep for " << workload << " ..." << std::endl;
	    std::this_thread::sleep_for(std::chrono::milliseconds(workload));

        //  Send to server:
        std::string smessage(static_cast<char*>(message.data()), message.size());
        std::cout << "msg send: " << smessage << " (" << message.size() << ")" << std::endl;

        sender.send(message);
        message.rebuild(20);
        memset(message.data(),0,20);
        memcpy(message.data(), client_msg.c_str(), 10);
        memcpy(static_cast<void*>(static_cast<char*>(message.data())+10), std::to_string(i).c_str(), std::to_string(i).size());

        //  Simple progress indicator for the viewer
        std::cout << std::flush;
    }
    return 0;
}
